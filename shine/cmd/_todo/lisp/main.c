/* lisp interpreter  */

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

#include "lisp.h"


typedef unsigned int uint32_t;


typedef uint32_t native_t;
#define CELL_SIZE  sizeof (native_t) * 2
#define KEEP 0
#define TERMINATE 1
#define SKIP 2
static char rt[0x80];
static int look; /* look ahead character */
static char value[16]; /* token */
static native_t *heap_base = 0,  *heap_ptr = 0,  *sym_ptr = 0,  *toplevel = 0;
#define num_tag  0x0 /* 000 */
#define pair_tag 0x1 /* 001 */
#define sym_tag  0x3 /* 011 */
#define proc_tag 0x7 /* 111 */
#define is_pair(x)  (((long)x & 7) == pair_tag)
#define is_sym(x)   (((long)x & 7) == sym_tag)
#define is_num(x)   (((long)x & 7) == num_tag)
#define is_proc(x)  (((long)x & 7) == proc_tag)
#define set_pair(x) ((long)x | pair_tag)
#define set_sym(x)  (((long)x << 3) | sym_tag)
#define set_num(x)  (x << 3)
#define set_proc(x) (((long)x << 3) | proc_tag)
#define car(x)      *(native_t**) ((long)x - 1)
#define cdr(x)      *(native_t**) ((long)x + 7)


static void read_table_default (){
  
  int c;
  
  for( c = 0 ; c < 0x7f ; c++ ) rt[c] = KEEP;
  rt['(']=rt[')']=rt['.']=rt[';']=rt['\'']=rt['"']=rt['#']=rt[',']=rt['`']= TERMINATE;
  rt[' ']=rt['\t']=rt['\r']=rt['\n']= SKIP;
}


static void lookahead ()
{   
  look = getchar (); 
}


static void gettoken (){
  
  int value_index = 0;
  
  while(rt[look] == SKIP) lookahead();
  if (rt[look] == TERMINATE)
  {
    value[value_index++] = look; lookahead();
    return;
  }
  
    while (rt[look] == KEEP)
    {
        value[value_index++] = look; 
        lookahead ();
        if (look == EOF) break;
    };
  
    value[value_index] = '\0';
}


static native_t *g_define, *g_cond, *g_nil, *g_begin, *g_true, *g_atom, *g_quote,
                *g_eq, *g_car, *g_cdr, *g_cons, *g_cond, *g_label, *g_lambda;

native_t *cons (native_t *a, native_t *b){
  
    native_t **cell = (native_t **) heap_ptr;

    cell[0] = a; cell[1] = b;
    heap_ptr += CELL_SIZE;
    
    return (native_t *) set_pair(cell);
}



native_t *proc (native_t * (*fn ) (native_t *) ) {

    native_t **cell = (native_t **) heap_ptr;

    cell[0] = *(native_t **) &fn;
    
    heap_ptr += CELL_SIZE;

    return (native_t *) set_proc(cell);
}



static native_t * findsym (char *val, native_t *list){
  
    for ( ; list ; list = cdr(list) )
    {
        native_t *a = car(list);

        if (is_sym(a) && strcmp( (char *) ((long) a >> 3), val) == 0)
           return a;
    }
  
    return 0;
}


native_t * intern(char *val) {

    native_t *base = heap_ptr;

    char *p = (char *) findsym(val, sym_ptr);

    if (p) return (native_t *) p;
    for( p = (char *)heap_ptr ; (*p++ = *val++) ; heap_ptr++ ) /* empty for body */;
    heap_ptr = (native_t*) ((long)heap_ptr + (CELL_SIZE) - (long)heap_ptr % (CELL_SIZE));
    base = (native_t *)set_sym(base);
    sym_ptr = cons(base, sym_ptr);

    return base;
}



native_t * getlist();
native_t * getobj(int have_token) {

    if (have_token == 0) gettoken();
    if (look==EOF) return g_nil;
    if (value[0]=='(') {
        
        return getlist();
    } else if (value[0]=='\'') {
        
        return cons(g_quote, cons(getobj(0), 0));
    } else if (value[0]>='0' && value[0] <='9') {
        
        long *l = (long *) heap_ptr;
        *l = atoi(value);
        heap_ptr = (native_t*) ((long)heap_ptr + sizeof (native_t *) * 2);
    
        return (native_t *) set_num(*l); /* immediate type */
    };
    
    return intern(value);
}



native_t * getlist (){
  
  native_t *tmp;
  
  gettoken ();
  
  if (value[0]==')') return 0;
  else if (value[0]=='.') 
       {
           tmp = getobj(0);
           gettoken();
           if (value[0]==')') return tmp;
               return tmp; /* error */
       }
       tmp = getobj(1);
       return cons(tmp, getlist());
}


void print_obj (native_t *ob, int head_of_list){
  
  if (is_num(ob) ) {
    printf("%ld", ((long) ob) >> 3);
    
  } else if (is_sym(ob) ) {
    printf ("%s", (char *) ((long) ob >> 3));
    
  } else if (is_pair(ob) ){
    
    if (head_of_list) printf("(");
    print_obj(car(ob), 1);
    if (cdr(ob) != 0) {
      if (is_pair(cdr(ob)) == 0) {
        printf(" . ");
        print_obj(cdr(ob), 0);
        printf(")");
      } else if (is_pair(cdr(ob)) == 1) {
        printf(" ");
        print_obj(cdr(ob), 0);
      }
    } else {
      printf(")");
    }
    
  } else if (is_proc(ob)) {
        
        printf("<procedure %p>", (void *) ob);
    
  } else {
    
        printf ("<%p>", (void *)ob);
    }
}


#define debug(OBJ) printf("%s:%d ", __FILE__, __LINE__); print_obj(OBJ,1); printf("\n");

native_t * assoc(native_t *v, native_t *e) {
  for ( ; e; e = cdr(e))
    if (v == car(car(e))) return car(e);
  return g_nil;
}

native_t * eval(native_t *ob, native_t *en);

native_t *evlist(native_t *l, native_t *e) {
  return l == 0 ? 0 : cons(eval(car(l),e), evlist(cdr(l), e));
}





// Eval.

native_t *eval (native_t *ob, native_t *en){


    if (is_sym(ob)) {

        native_t *a = assoc(ob, en);
        return is_pair(a) == 0 ? g_nil : car(cdr(a)); /* (a b ...) -> b */

    } else if (is_pair(ob)) {

        native_t *a = car(ob), *b = cdr(ob);
        if (a == g_nil) return a;
        else if (a == g_label || a == g_define) 
             {
                 toplevel = cons(b, toplevel);
             } else if (a == g_quote) {
                  return car(cdr(ob));
             } else if (a == g_atom) {
                  return  is_pair( eval(car(cdr(ob)), en) ) == 0 ? g_true : g_nil;
             } else if (a == g_eq) {
                  return eval(car(cdr(ob)), en) == eval(car(cdr(cdr(ob))), en) ? g_true : g_nil;
             } else if (a == g_car) {
                  return car( eval(car(cdr(ob)), en) );
             } else if (a == g_cdr) {
                 return cdr( eval(car(cdr(ob)), en) );
             } else if (a == g_cons) {
                 return cons( eval(car(cdr(ob)), en) , eval(car(cdr(cdr(ob))), en) );
             } else if (a == g_cond) {
                 for ( ; b ; b = cdr(b) )
                     if (eval(car(car(b)), en) != g_nil) return eval(car(cdr(car(b))), en);
                 return g_nil;
             } else if (a == g_lambda) { /* evaluates to itself */
             
             } else if (is_sym(a)) {
                 native_t *r = eval(a,en);
                 if (is_proc(r)) {
                     native_t *fn = *(native_t **) ((long)r >> 3), *al = evlist(b, en);
                 return ((native_t * (*) (native_t *)) fn) (al);
                 } else {
                     return eval(cons(r, b), en);
                 }
                 
                 
        } else if (is_pair(a) && car(a) == g_lambda) {
            /* eval arguments, add to environment, eval body */
            native_t *x = car(cdr(a));
            for ( ; x ; x = cdr(x), b = cdr(b) )
                en = cons(cons(car(x), cons(eval(car(b),en), 0)), en);
            return eval(car(cdr(cdr(a))), en);
        }
    
    
    };


    return ob; /* anything else evaluates to itself */
}



#define make_proc(NAME,OP) \
native_t * NAME (native_t *args) { \
  long r = ((long) car(args) >> 3); \
  for ( args = cdr(args) ; args ; args = cdr(args) ) \
    r = r OP ((long) car(args) >> 3); \
  return (native_t *) set_num(r); }

make_proc(add,+)
make_proc(sub,-)
make_proc(mul,*)




/*
 ************************** 
 * main: 
 * 
 */
 
int main (int argc, char *argv[]){

    printf ("Initializing Lisp ...\n");
  
    heap_ptr = heap_base = malloc (8192);
  
    // #todo
    // Check pointer.
    
    g_nil    = intern("()"),    
    g_true   = intern("t"),      
    g_begin  = intern("begin"),
    g_quote  = intern("quote"), 
    g_atom   = intern("atom"),   
    g_eq     = intern("eq"),
    g_car    = intern("car"),   
    g_cdr    = intern("cdr"),    
    g_cons   = intern("cons"),
    g_cond   = intern("cond"),  
    g_label  = intern("label"),  
    g_lambda = intern("lambda"),
    g_define = intern("define");
    
    toplevel = cons(cons(intern("+"), cons(proc(add), 0)), toplevel);
    toplevel = cons(cons(intern("-"), cons(proc(sub), 0)), toplevel);
    toplevel = cons(cons(intern("*"), cons(proc(mul), 0)), toplevel);


	//#debug
    printf ("read table default\n");
    read_table_default ();

	//#debug
    printf ("look ahead\n");
    lookahead ();


	//#debug
    printf ("for:\n");
    for ( ; look != EOF ; ) 
    {
        print_obj ( eval(getobj(0), toplevel), 1 ); 
        printf ("\n");
    };


    printf ("done\n");
    return 0;
}


//
// End.
//






