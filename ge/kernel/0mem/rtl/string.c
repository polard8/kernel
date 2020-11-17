/*
 * File: string.c
 *
 * Descrição:
 *     Operações com strings.
 *     Parte da biblioteca da linguagem C.
 *
 * 2015 - Created by Fred Nora.
 */


#include <kernel.h>


//test.
//#define tolower(c)  ((int)((c) & ~0x20))
//#define toupper(c)  ((int)((c) | 0x20))


/* 
 * strcmp:
 *     Compara duas strings. 
 */

int strcmp (char * s1, char * s2){

    register int i=0;

    for ( i=0; s1[i] == s2[i]; i++ )
    {
        if ( s1[i] == '\0' ){  return (0);  }
    };

    return ((int) (s1[i] - s2[i]));
}


/* 
 * strncmp:
 *     Compara duas strings. 
 */

int strncmp ( char *s1, char *s2, int len ){

    register int n = len;

    while ( n > 0 )
    {
        n--;
        
        if ( *s1 != *s2 ){  return (int) 1;  }

		//#bugbug:
		//Esse incremento está errado.
		
		*s1++;
		*s2++;
		
		//#bugbug:
		//Testar sem o asterísco, tanto em user mode(libc) quanto em kernel mode.
		//s1++;
		//s2++;
		
		
	};		


    if (*s1 != '\0' || *s2 != '\0' )
    {
        return 2;
    }

    return 0;
}


/*
 * str_cmp:
 *     Compara strings.
 */

int str_cmp(unsigned char *str1, unsigned char *str2)
{
    
    while ( *str1 == *str2 && 
            *str1 != 0     && 
            *str2 != 0) 
    { 
        str1++;  str2++; 
    };


	// mesma quantidade de chars iguais
    if (*str1 == *str2) 
	    return 0;
	
	if (*str1 > *str2) 
	    return 1;
		
	if (*str1 < *str2) 
	    return -1;


    return -1;
}

 
 
/*
 * memcpy: 
 */

void *memcpy ( void *v_dst, const void *v_src, unsigned long c ){

    const char *src = v_src;
    char *dst = v_dst;

    register unsigned long Copy=c;

    /* Simple, byte oriented memcpy. */
    //#danger.
    
    while (Copy--)
    {
        *dst++ = *src++;
    };

    return v_dst;
}


void *memcpy32 ( void *v_dst, const void *v_src, unsigned long c ){
	
	//const char *src = v_src;
	//char *dst = v_dst;

	long *src = (long *) v_src;
	long *dst = (long *) v_dst;

    register unsigned long Copy=c;
    
	/* Simple, byte oriented memcpy. */
    //danger
    
    while (Copy--)
    {
        *dst++ = *src++;
    };

    return v_dst;
}


/*
 * strcpy - copia uma string 
 */

char *strcpy ( char *to, const char *from ){

    register int i=0;

    while ( to[i] = from[i] )
    {
        i += 1;
    };

    return (to);
}


/*
 * strcat - acrescenta uma string ao fim de outra. 
 */

char *strcat (char *to, const char *from){
	
    char *ret = to;

    while (*to) 
    {
        to += 1;
    };
	
	strcpy(to, from);
	return (ret);
}


 /* strcat */
/* 
 char *(strcat)(char *restrict s1, const char *restrict s2);
 char *(strcat)(char *restrict s1, const char *restrict s2)
 {
     char *s = s1;
     //Move s so that it points to the end of s1.  
     while (*s != '\0')
         s++;
     //Copy the contents of s2 into the space at the end of s1.  
     strcpy(s, s2);
     return s1;
 }
*/


/*
 *  bcopy: */

void bcopy (char *from, char *to, int len)
{

    //danger
	while(len--) 
	{
		*to++ = *from++;
	};
    //return;
}


/*
 *  bzero:
 *      Preenche com zeros. */

void bzero (char *cp, int len){

    //danger
	while(len--)
	{
		*(cp + len) = 0;
	};
    //return;
}


/*
 * strlen:
 *     Calcula o tamanho de uma string. 
 */

size_t strlen (const char *s){

    register size_t i=0;

    //#todo
    //if ( (void *) s == NULL ){ return -1; }

    for ( i=0; s[i] != '\0'; ++i )
    {
        ;
    };

    return ( (size_t) i );
}


/*
    Outra opção:
int strlen(const char * s)
{
	int n = 0;
	while (*s++) n++;
	return(n);
}
*/

/*
int kstrlen(const char *s);
int kstrlen(const char *s)
{	
    int i = 0;
	
	for (i = 0; s[i] != '\0'; ++i) {
	;
	};
	
done:
	return((int) i);
};
*/



/*
// Compares two strings. 
//Returns -1 if str1 < str2, 
//0 if they are equal or 
//1 otherwise.
int strcmp(char *str1, char *str2)
{
    int i = 0;
    
    int failed = 0;
    
    while( str1[i] != '\0' && str2[i] != '\0' )
    {
        if(str1[i] != str2[i])
        {
            failed = 1;
            break;
        }
        i++;
    }
 
 
   // why did the loop exit?
    if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') )
    {    
	    failed = 1;
    }; 
 
	
	return failed;
};

 

int strcmp(const char *a, const char *b)
{
    while(*a && *b) 
	{
        if(*a++ != *b++) 
		    return 1;
    }
    
	if(*a || *b) 
	    return 1;
		
    return 0;
}
*/


/*
 //strchr
 char *(strchr)(const char *s, int c)
 {
     char ch = c;
     // Scan s for the character.  When this loop is finished,
     //   s will either point to the end of the string or the
     //   character we were looking for.  
     while (*s != '\0' && *s != ch)
         s++;
     return (*s == ch) ? (char *) s : NULL;
 }
*/


/*

 //memmove 
 void *(memmove)(void *s1, const void *s2, size_t n) 
 {
    //note: these don't have to point to unsigned chars 
    char *p1 = s1;
    const char *p2 = s2;
    // test for overlap that prevents an ascending copy 
    if (p2 < p1 && p1 < p2 + n) {
        // do a descending copy 
        p2 += n;
        p1 += n;
        while (n-- != 0) 
            *--p1 = *--p2;
    } else 
        while (n-- != 0) 
            *p1++ = *p2++;
    return s1; 
 }

*/



/*
 // memchr 
 void *(memchr)(const void *s, int c, size_t n)
 {
     const unsigned char *src = s;
     unsigned char uc = c;
     while (n-- != 0) {
         if (*src == uc)
             return (void *) src;
         src++;
     }
     return NULL;
 }


*/




/*
 //strcspn 
 size_t (strcspn)(const char *s1, const char *s2)
 {
     const char *sc1;
     for (sc1 = s1; *sc1 != '\0'; sc1++)
         if (strchr(s2, *sc1) != NULL)
             return (sc1 - s1);
     return sc1 - s1;            // terminating nulls match 
 }

*/


/*
 //strpbrk 
 char *(strpbrk)(const char *s1, const char *s2)
 {
     const char *sc1;
     for (sc1 = s1; *sc1 != '\0'; sc1++)
         if (strchr(s2, *sc1) != NULL)
             return (char *)sc1;
     return NULL;                // terminating nulls match 
 }
*/

/*
// strspn 
 size_t (strspn)(const char *s1, const char *s2)
 {
     const char *sc1;
     for (sc1 = s1; *sc1 != '\0'; sc1++)
         if (strchr(s2, *sc1) == NULL)
             return (sc1 - s1);
     return sc1 - s1;            // terminating nulls don't match 
 }

*/


/*
// strstr 
 char *(strstr)(const char *haystack, const char *needle)
 {
     size_t needlelen;
     //Check for the null needle case.  
     if (*needle == '\0')
         return (char *) haystack;
     needlelen = strlen(needle);
     for (; (haystack = strchr(haystack, *needle)) != NULL; haystack++)
         if (memcmp(haystack, needle, needlelen) == 0)
             return (char *) haystack;
     return NULL;
 }

*/



//#bugbug:
//Isso ainda não foi testado.

void *memset ( void *ptr, int value, int size ){

    register int i=0;
        
    if ( ptr != NULL && size > 0 )
    {
        //#bugbug.
        unsigned char *temp = ptr;

        for ( i = 0; i < size; i++ )
        {
            *temp++ = (unsigned char) value;
        };
    };

    return (void *) ptr;
}
 



/*
 
 // strtok_r 
 char *(strtok_r)(char *s, const char *delimiters, char **lasts); 
 char *(strtok_r)(char *s, const char *delimiters, char **lasts)
 {
     char *sbegin, *send;
     sbegin = s ? s : *lasts;
     sbegin += strspn(sbegin, delimiters);
     if (*sbegin == '\0') {
         *lasts = "";
         return NULL;
     }
     send = sbegin + strcspn(sbegin, delimiters);
     if (*send != '\0')
         *send++ = '\0';
     *lasts = send;
     return sbegin;
 }
*/
 
 /*
 //strtok 
 char *(strtok)(char *restrict s1, const char *restrict delimiters); 
 char *(strtok)(char *restrict s1, const char *restrict delimiters)
 {
     static char *ssave = "";
     return strtok_r(s1, delimiters, &ssave);
 }
*/



/* Copyright (c) 2011, 2012 Jonas 'Sortie' Termansen. */
size_t strcspn(const char* str, const char* reject)
{

    register int i=0;

    //bool matches = 0;
    int matches = 0;

	//size_t reject_length = 0;
    register int reject_length = 0;

    while ( reject[reject_length] )
    {
        reject_length++;
    };


	//for ( size_t result = 0; 1; result++ )
    register int result=0;
    for ( result=0; result = 1; result++ )
    {
        char c = str[result];

        if ( !c ){  return (size_t) result; }

        for ( i=0; i < reject_length; i++ )
        {
			if ( str[result] != reject[i] )
				continue;
			matches = 1;
			break;
        };

        if ( matches ){  return (size_t) result;  }
    };
}


/* Copyright (c) 2011, 2012 Jonas 'Sortie' Termansen. */
size_t strspn (const char* str, const char* accept)
{
	//size_t accept_length = 0;
    register int accept_length = 0; 
    while ( accept[accept_length] ){
        accept_length++;
    };

	
	//for ( size_t result = 0; true; result++ )
    register int result=0;
    for ( result = 0; result = 1; result++ )
	{
		char c = str[result];
		if ( !c )
			return (size_t) result;
		
		//bool matches = false;
		int matches = 0;
		int i;
		//for ( size_t i = 0; i < accept_length; i++ )
		for( i=0; i<accept_length; i++ )
		{
			if ( str[result] != accept[i] )
				continue;
			matches = 1;
			break;
		}
		if ( !matches )
			return (size_t) result;
	}
}




/* Copyright (c) 2011, 2012 Jonas 'Sortie' Termansen. */
/*
char* strtok_r(char* str, const char* delim, char** saveptr)
{
	if ( !str && !*saveptr )
		return NULL;
	if ( !str )
		str = *saveptr;
	str += strspn(str, delim); // Skip leading
	if ( !*str )
		return *saveptr = NULL;
	size_t amount = strcspn(str, delim);
	if ( str[amount] )
		*saveptr = str + amount + 1;
	else
		*saveptr = NULL;
	str[amount] = '\0';
	return str;
}
*/



/* Copyright (c) 2011, 2012 Jonas 'Sortie' Termansen. */
/*
char* strtok(char* str, const char* delim)
{
	static char* lasttokensaveptr = NULL;
	return strtok_r(str, delim, &lasttokensaveptr);
}
*/


/*apple*/
char *strtok_r (char *s, const char *delim, char **last)
{

    register int sc=0;
    register int c=0;

    char *spanp;
    char *tok;


    if (s == NULL && (s = *last) == NULL)
    {
        return NULL;
    }

    /*
     * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
     */
cont:
    c = *s++;
    for (spanp = (char *)delim; (sc = *spanp++) != 0; )
    {
        if (c == sc){  goto cont;  }
    }

    if (c == 0)		/* no non-delimiter characters */
    {
        *last = NULL;
        return NULL;
    }
    tok = s - 1;

    /*
     * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
     * Note that delim must have one NUL; we stop if we see that, too.
     */
    
    for (;;)
    {
        c = *s++;
        spanp = (char *)delim;
        
        do
        {
            if ((sc = *spanp++) == c)
	    {
		if (c == 0)
		{
		    s = NULL;
		}
		else
		{
		    char *w = s - 1;
		    *w = '\0';
		}
		*last = s;
            return tok;
            }

        } while (sc != 0);
    }
    /* NOTREACHED */
}

/*apple*/
char *strtok(char *s, const char *delim)
{
    static char *last;

    return strtok_r (s, delim, &last);
}


// Duplicate a string.
char *strdup (const char *str){

    char *copy;
    size_t len=0;

    len = strlen(str) + 1;

    // #todo:
    //  simplify this thing.
    if ( !(copy = (char *) kmalloc( ( size_t ) len ) ) )
    {
        return (NULL);
    }

    memcpy (copy, str, len);
 
    return (char *) copy;
}


