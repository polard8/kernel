
// stdarg.h 
// status: Criando uma versão simplificada, que funcione no sistema 
// operacional Gramado, na arquitetura x86.
// Fred Nora


//cria um tipo 'char *', usado em strings.
typedef char * va_list;
typedef char * gramado_va_list;

//typedef char *__gnuc_va_list;
//typedef va_list __gnuc_va_list;
//typedef __gnuc_va_list __builtin_va_list ;

//todo:
//va_start	Start iterating arguments with a va_list	C89
//va_arg	Retrieve an argument	C89
//va_end	Free a va_list	C89
//va_copy	Copy contents of one va_list to another	C99

/*
Data Type: 
va_list
The type va_list is used for argument pointer variables.

Macro: 
void va_start (va_list ap, last-required)
This macro initializes the argument pointer variable ap to point 
to the first of the optional arguments of the current function; 
last-required must be the last required argument to the function.
See section Old-Style Variadic Functions, for an alternate 
definition of va_start found in the header file `varargs.h'.

Macro: 
type va_arg (va_list ap, type)
The va_arg macro returns the value of the next optional argument, 
and modifies the value of ap to point to the subsequent argument. 
Thus, successive uses of va_arg return successive optional arguments.
The type of the value returned by va_arg is type as specified in the call. 
type must be a self-promoting type 
(not char or short int or float) that matches the type of the actual argument.

Macro: 
void va_end (va_list ap)
This ends the use of ap. After a va_end call, 
further va_arg calls with the same ap may not work. 
You should invoke va_end before returning from the 
function in which va_start was invoked with the same ap argument.
*/




//rotina de suporte.
#define __va_rounded_size(TYPE)  \
    ( ( ( sizeof(TYPE) + sizeof(int) - 1) / sizeof(int) ) * sizeof(int) )
	
/*
 * rotina de suporte. (obs: igual a anterior)
 * Amount of space required in an argument list (ie. the stack) for an
 * argument of type t.
 */
#define __va_argsiz(t)	\
	(((sizeof(t) + sizeof(int) - 1) / sizeof(int)) * sizeof(int))
	


/*
 *****************************************************************
 *  ## va_start ##
 *
 * For a simple minded compiler this should work 
 * (it works in GNU too for vararg lists that don't follow shorts and such).
 */
#define va_start(ap, pN)  \
	( (ap) = ( (va_list) (&pN) + __va_argsiz(pN) ) )

	
//#bugbug (dependência)	
//@todo
//#define va_start(AP, LASTARG)  \
//    (__builtin_saveregs (),       \
//    AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))



//#bugbug 
//@todo:
/* Defined in gnulib */
//void va_end(va_list);		
//#define va_end(AP)

/*
 * #bugbug
 * End processing of variable argument list. In this case we do nothing.
 */
//#define va_end(ap)	( (void) 0 )


/*
 ***************************************
 * ## va_arg ##
 *
 * Increment ap to the next argument in the list while returing a
 * pointer to what ap pointed to first, which is of type t.
 *
 * We cast to void* and then to t* because this avoids a warning about
 * increasing the alignment requirement.
 */

#define va_arg( ap, t )  \
    ( ( (ap) = (ap) + __va_argsiz(t) ),  \
	           *( (t *) (void *) ( (ap) - __va_argsiz(t) ) ) )
	  
//#define va_arg( AP, TYPE )  \
//    ( AP += __va_rounded_size(TYPE), \
//    *((TYPE *) (AP - __va_rounded_size (TYPE))) )

//void __va_end(va_list* ap);
//#define va_end(ap) \
//	(__va_end(&(ap)))	  
	  
  
  
  
  
  
  
  
  
  

