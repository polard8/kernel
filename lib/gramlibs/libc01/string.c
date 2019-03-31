/*
 * File: string.c
 *
 * Descrição:
 *     Operações com strings.
 *     Parte da biblioteca da linguagem C.
 *
 * Ambiente:
 *     User mode.
 *
 * Versão: 1.0, 2016 - Created.
 */

 
#include <stddef.h>
#include <string.h>
#include <inttypes.h>


/*
 #todo
 
void *memsetw (void *dst, int val, size_t count);
void *memsetw (void *dst, int val, size_t count){
	
	unsigned short *temp = (unsigned short *) dst;

	for ( ; count != 0; count--)
		*temp++ = val;
	return dst;
}
*/


/*
 * Compare memory regions.
 */

int memcmp (const void *s1, const void *s2, size_t n){
	
	if (n != 0) 
	{
		const unsigned char *p1 = s1, *p2 = s2;

		do {
			if (*p1++ != *p2++)
				return (*--p1 - *--p2);
		} while (--n != 0);
	}
	
	return (0);
}



/*
 * strdup --
 *
 * PUBLIC: #ifndef HAVE_STRDUP
 * PUBLIC: char *strdup __P((const char *));
 * PUBLIC: #endif
 */

char *strdup (const char *str){
	
	size_t len;
	char *copy;

	len = strlen(str) + 1;
	
	if (!(copy = (char *) malloc( ( size_t ) len ) ))
		return (NULL);
	memcpy(copy, str, len);
	return (copy);
}


char *strndup(const char *s, size_t n)
{
	size_t l = strnlen (s, n);
	
	char *d;
	d = (char *) malloc (l + 1);
	
	if (!d)
		return NULL;
	memcpy(d, s, l);
	d[l] = '\0';
	return d;
}


/*
 * strrchr --
 *
 * PUBLIC: #ifndef HAVE_STRRCHR
 * PUBLIC: char *strrchr __P((const char *, int));
 * PUBLIC: #endif
 */

char *strrchr(const char *p, int ch){
	
	char *save;
	char c;

	c = ch;
	
	for ( save = NULL;; ++p ) 
	{
		if (*p == c)
			save = (char *) p;
		if (*p == '\0')
			return (save);
	}
	/* NOTREACHED */
}


//definido em inttypes.h
intmax_t strtoimax (const char* str, char** endptr, int base)
{
   return 0;
}

//definido em inttypes.h
uintmax_t strtoumax (const char* str, char** endptr, int base)
{
   return 0;
}


/*
 * strcasecmp --
 *	Do strcmp(3) in a case-insensitive manner.
 *
 * PUBLIC: #ifndef HAVE_STRCASECMP
 * PUBLIC: int strcasecmp __P((const char *, const char *));
 * PUBLIC: #endif
 */

int strcasecmp (const char *s1, const char*s2){
	
	unsigned char s1ch, s2ch;

	for (;;) {
		s1ch = *s1++;
		s2ch = *s2++;
		if (s1ch >= 'A' && s1ch <= 'Z')		/* tolower() */
			s1ch += 32;
		if (s2ch >= 'A' && s2ch <= 'Z')		/* tolower() */
			s2ch += 32;
		if (s1ch != s2ch)
			return (s1ch - s2ch);
		if (s1ch == '\0')
			return (0);
	}
	/* NOTREACHED */
}


/* ANSI sez:
 *   The `strncpy' function copies not more than `n' characters (characters
 *   that follow a null character are not copied) from the array pointed to
 *   by `s2' to the array pointed to by `s1'.  If copying takes place between
 *   objects that overlap, the behavior is undefined.
 *   If the array pointed to by `s2' is a string that is shorter than `n'
 *   characters, null characters are appended to the copy in the array
 *   pointed to by `s1', until `n' characters in all have been written.
 *   The `strncpy' function returns the value of `s1'.  [4.11.2.4]
 */

char *strncpy(char *s1, const char *s2, size_t n){
	
    char *s = s1;
    while (n > 0 && *s2 != '\0') {
	*s++ = *s2++;
	--n;
    }
    while (n > 0) {
	*s++ = '\0';
	--n;
    }
    return s1;
}


/*
 * strcmp:
 *     Compara duas strings. */

int strcmp (char * s1, char * s2){
	
	int i;
	
	for ( i=0; s1[i] == s2[i]; i++ ){
		
		if ( s1[i] == '\0' ){ 
		
		    return (int) 0; 
		}
	};
	
	return ( (int) ( s1[i] - s2[i] ) );
};


/*
 * strncmp:
 *     Compara duas strings.
 *     Obs: Essa tem funcionado bem. */

int strncmp ( char *s1, char *s2, int len ){
	
	int n = len;
	
	while (n > 0)
	{	
	    n--;
        
		if ( *s1 != *s2 )
		{ 
		    return (int) 1; 
		}
		
		*s1++; 
		*s2++;
	};		
			
	if ( *s1 != '\0' || *s2 != '\0' )
	{	
	    return (int) 2;
	};
	
	return (int) 0;
};


/*linux style
void *memset(void *s, int c, size_t count)
{
	char *xs = s;

	while (count--)
		*xs++ = c;
	return s;
}
*/


/*
 * memset:
 * */

void *memset ( void *ptr, int value, int size ){
	
    if ( ptr != NULL && size > 0 )
    {
        unsigned char *temp = ptr;

        int i = 0;

        for ( i = 0; i < size; i++ )
        {
            *temp++ = (unsigned char) value;
        }

    };
		
    return (void *) ptr;
}


//#todo: mover para memory.c ??
void *memoryZeroMemory ( void* ptr, size_t cnt ){
	
    volatile char *vptr = (volatile char *) ptr;
    
	while (cnt)
	{
        *vptr = 0;
        
		vptr++;
        cnt--;
    };
	
    return (void *) ptr;
};


/*
 * memcpy:
 *     ?? #todo: mover para memory.c ?? 
 */

void *memcpy ( void *v_dst, const void *v_src, unsigned long c ){
	
	const char *src = v_src;
	char *dst = v_dst;

	// Simple, byte oriented memcpy. 
	while (c--){
		
        *dst++ = *src++; 
	};
	
	//#todo: Tipar o retorno.
	return v_dst;
}


/*
 * strcpy: 
 *     Copia uma string. */

char *strcpy ( char *to, const char *from ){
	
	int i=0;

	while ( to[i] = from[i] )
	{ 
        i += 1; 
	};

	//#todo: Tipar o retorno.
	return (to);
}


/*
size_t strlcpy(char *dst, const char *src, size_t size)
size_t strlcpy(char *dst, const char *src, size_t size)
{
	size_t bytes = 0;
	char *q = dst;
	const char *p = src;
	char ch;
	while ((ch = *p++)) {
		if (bytes + 1 < size)
			*q++ = ch;
		bytes++;
	}
	// If size == 0 there is no space for a final null... 
	if (size)
		*q = '\0';
	return bytes;
}
*/




/*
 * strcat:
 *     Acrescenta uma string ao fim de outra. */

char *strcat ( char *to, const char *from ){
	
	char *ret = to;

	while ( *to )
	{ 
        to += 1; 
	};
	
	strcpy ( to, from );
	
	//#todo: Tipar o retorno.	
	return (ret);
}

/*
size_t strlcat(char *dst, const char *src, size_t size)
size_t strlcat(char *dst, const char *src, size_t size)
{
	size_t bytes = 0;
	char *q = dst;
	const char *p = src;
	char ch;
	while (bytes < size && *q) {
		q++;
		bytes++;
	}
	if (bytes == size)
		return (bytes + strlen(src));
	while ((ch = *p++)) {
		if (bytes + 1 < size)
			*q++ = ch;
		bytes++;
	}
	*q = '\0';
	return bytes;
}
*/

/*
char *strncat(char *dst, const char *src, size_t n);
char *strncat(char *dst, const char *src, size_t n)
{
	char *q = strchr(dst, '\0');
	const char *p = src;
	char ch;
	while (n--) {
		*q++ = ch = *p++;
		if (!ch)
			return dst;
	}
	*q = '\0';
	return dst;
}
*/


/* 
 * bcopy: Copia. */

void bcopy ( char *from, char *to, int len ){
	
	//if ( len < 0 )
	//    return;
	
	while ( len-- )
	{ 
        *to++ = *from++; 
	};
}


/*
 *  bzero:
 *      Preenche com zeros. */

void  bzero ( char *cp, int len ){
	
	//if ( len < 0 )
	//    return;	
	
	while ( len-- )
	{ 
        *(cp + len) = 0; 
	};
}


/*
 * strlen:
 *     Tamanho de uma string.
 */ 
size_t strlen ( const char *s ){
	
    size_t i = 0;
	
	for ( i=0; s[i] != '\0'; i++ )
	{ 
        ; 
	};

	return (size_t) i;
};


/*
static size_t strlen (const char *s){
	
	size_t l = 0;
	while (*s++)
		l++;
	return l;
};
*/

/* 
 * strnlen:
   Find the length of S, but scan at most MAXLEN characters.  
   If no '\0' terminator is found within the first MAXLEN characters, return MAXLEN. 
 */

size_t strnlen ( const char *s, size_t maxlen ){
	
    const char *e;
    size_t n;

    for (e = s, n = 0; *e && n < maxlen; e++, n++)
    ;
    return n;
}


/*
 * strcspn:
 *     ??
 * Credits: 
 *     Copyright (c) 2011, 2012 Jonas 'Sortie' Termansen.
 */

size_t strcspn ( const char *str, const char *reject ){
	
	int result;
	
	//size_t reject_length = 0;
	int reject_length = 0;
	
	while ( reject[reject_length] )
		reject_length++;
	
	
	// ?? Não seria "result==1" ??
	//for ( size_t result = 0; 1; result++ )
    for ( result=0; result=1; result++ )
	{
		char c = str[result];
		
		if ( !c )
			return (size_t) result;
		
		//bool matches = 0;
		int matches = 0;
		int i;
		
		for ( i=0; i < reject_length; i++ )
		{
			if ( str[result] != reject[i] )
				continue;
			matches = 1;
			break;
		};
		
		if ( matches )
			return (size_t) result;
	};
	
	//??
};


/*
 * strspn:
 *   ??
 * Credits: 
 * Copyright (c) 2011, 2012 Jonas 'Sortie' Termansen.
 */
size_t strspn ( const char* str, const char* accept ){
	
	int result;
	
	//size_t accept_length = 0;
	int accept_length = 0; 
	
	while ( accept[accept_length] )
		accept_length++;
	
	
	// ?? Não seria "result==1" ??
	//for ( size_t result = 0; true; result++ )
    
    for ( result = 0; result = 1; result++ )
	{
		char c = str[result];
		
		if ( !c )
			return (size_t) result;
		
		//bool matches = false;
		int matches = 0;
		int i;
		
		//for ( size_t i = 0; i < accept_length; i++ )
		
	    for ( i=0; i<accept_length; i++ )
		{
			if ( str[result] != accept[i] )
				continue;
			matches = 1;
			break;
		};
		
		if ( !matches )
			return (size_t) result;
	};
	
	//??
};


/*
 **************************************
 * strtok_r:
 *     Usada em strtok.
 *
 * Credits: 
 *     Apple. (Open Source)
 */
char *strtok_r ( char *s, const char *delim, char **last ){
	
    char *spanp;
    int c, sc;
    char *tok;

    if ( s == NULL && (s = *last) == NULL ){
		
	    return NULL;
    };

    
    // Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	
cont:
    
	c = *s++;
    
	for ( spanp = (char *)delim; (sc = *spanp++) != 0; )
    {
	    if (c == sc){
	        goto cont;
	    }
    };

	// No non-delimiter characters. 
    if ( c == 0 )		
    {
	    *last = NULL;
	    return NULL;
    };
	
    tok = s -1;

    // Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
    // Note that delim must have one NUL; we stop if we see that, too.
	 
    for (;;)
    {
	    c = *s++;
	    spanp = (char *) delim;
	    
		do
	    {
	        if ( (sc = *spanp++) == c )
	        {
		        if ( c == 0 )
				{
		            s = NULL;
					
		        }else{
					
		            char *w = s -1;
		            
					*w = '\0';
		        };
				
		        *last = s;
				
		        return tok;
	        };
			
	    }while( sc != 0 );
        
		//Nothing.
		
	};
	
    // NOTREACHED 
};


/*
 *********************************************
 * strtok:
 *     Credits: Apple. (Open Source) */

char *strtok ( char *s, const char *delim ){
	
    static char *last;
	
    return strtok_r ( s, delim, &last );
}


/*
char *strchr(const char *s, int c)
char *strchr(const char *s, int c)
{
	while (*s != (char)c) {
		if (!*s)
			return NULL;
		s++;
	}
	return (char *)s;
}
*/

/*
 * strchr:
 * linux style */

char *strchr (const char *s, int c){
	
	for (; *s != (char)c; ++s)
		if (*s == '\0')
			return NULL;
	return (char *)s;
}



/*linux style
void *memmove(void *dest, const void *src, size_t count)
{
	char *tmp;
	const char *s;

	if (dest <= src) {
		tmp = dest;
		s = src;
		while (count--)
			*tmp++ = *s++;
	} else {
		tmp = dest;
		tmp += count;
		s = src;
		s += count;
		while (count--)
			*--tmp = *--s;
	}
	return dest;
}
*/



/*
 //linux style 
 * memscan - Find a character in an area of memory.
 * @addr: The memory area
 * @c: The byte to search for
 * @size: The size of the area.
 *
 * returns the address of the first occurrence of @c, or 1 byte past
 * the area if @c is not found
 void *memscan(void *addr, int c, size_t size)
{
	unsigned char *p = addr;

	while (size) {
		if (*p == c)
			return (void *)p;
		p++;
		size--;
	}
  	return (void *)p;
}
*/


/**
 *linux style
 * strstr - Find the first substring in a %NUL terminated string
 * @s1: The string to be searched
 * @s2: The string to search for
 */

char *strstr (const char *s1, const char *s2){
	
	size_t l1, l2;

	l2 = strlen(s2);
	
	if (!l2)
		return (char *)s1;
	l1 = strlen(s1);
	
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1++;
	}
	return NULL;
}


//
// End.
//

