/*
 * File: string.c
 *
 * Descrição:
 *     Operações com strings.
 *     Parte da biblioteca da linguagem C.
 *
 * Ambiente:
 *     User mode.
 */

 
#include <ctype.h>
#include <stddef.h>

#include <string.h>
#include <strings.h>

#include <inttypes.h>




/*
 Credits: Apple chameleon 
void * stosl(void * dst, long val, long len);
void * stosl(void * dst, long val, long len)
{
    asm volatile ( "rep; stosl"
       : "=c" (len), "=D" (dst)
       : "0" (len), "1" (dst), "a" (val)
       : "memory" );

    return dst;
}
*/


int strcoll (const char *s1, const char *s2)
{
    return (int) strcmp ( (char *) s1, (char *) s2);
}



/**
 * linux style.
 * strncasecmp - Case insensitive, length-limited string comparison
 * @s1: One string
 * @s2: The other string
 * @len: the maximum number of characters to compare
 */
/*
int strncasecmp(const char *s1, const char *s2, size_t len); 
int strncasecmp(const char *s1, const char *s2, size_t len)
{
	//Yes, Virginia, it had better be unsigned 
	unsigned char c1, c2;

	if (!len)
		return 0;

	do {
		c1 = *s1++;
		c2 = *s2++;
		if (!c1 || !c2)
			break;
		if (c1 == c2)
			continue;
		c1 = tolower(c1);
		c2 = tolower(c2);
		if (c1 != c2)
			break;
	} while (--len);
	return (int)c1 - (int)c2;
}
*/


// musl
/*
int strncasecmp(const char *_l, const char *_r, size_t n);
int strncasecmp(const char *_l, const char *_r, size_t n)
{
	const unsigned char *l=_l, *r=_r;
	if (!n--) return 0;
	for (; *l && *r && n && (*l == *r || tolower(*l) == tolower(*r)); l++, r++, n--);
	return tolower(*l) - tolower(*r);
}
*/

void *memsetw (void *dst, int val, size_t count){

    unsigned short *temp = (unsigned short *) dst;

    for ( ; count != 0; count--)
        *temp++ = val;

    return (void *) dst;
}


/*
 * memcmp:
 *     Compare memory regions.
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

    return 0;
}


/*
 * strdup:
 *
 * PUBLIC: #ifndef HAVE_STRDUP
 * PUBLIC: char *strdup __P((const char *));
 * PUBLIC: #endif
 */

char *strdup (const char *str){

    char *copy;
    size_t len;

    len = strlen(str) + 1;

    if (!(copy = (char *) malloc( ( size_t ) len ) ))
        return (NULL);

    memcpy (copy, str, len);
    
    return (copy);
}


char *strndup (const char *s, size_t n){

    char *d;

    size_t l = strnlen (s, n);

    d = (char *) malloc (l + 1);

    if (!d)
        return NULL;

    memcpy (d, s, l);

    d[l] = '\0';

    return (char *) d;
}


/**
 * skip_spaces - Removes leading whitespace from @str.
 * @str: The string to be stripped.
 *
 * Returns a pointer to the first non-whitespace character in @str.
 */
/* 
char *skip_spaces(const char *str); 
char *skip_spaces(const char *str)
{
	while (isspace(*str))
		++str;
	return (char *)str;
}
*/


/*linux style*/
/**
 * strim - Removes leading and trailing whitespace from @s.
 * @s: The string to be stripped.
 *
 * Note that the first trailing whitespace is replaced with a %NUL-terminator
 * in the given string @s. Returns a pointer to the first non-whitespace
 * character in @s.
 */

//#bugbug
//Talvez o arquivo string.c deva ter sua própria implementação
//de isspace. 
 
/* 
char *strim(char *s); 
char *strim(char *s)
{
	size_t size;
	char *end;

	size = strlen(s);
	if (!size)
		return s;

	end = s + size - 1;
	while (end >= s && isspace(*end))
		end--;
	*(end + 1) = '\0';

	return skip_spaces(s);
}
*/



/*linux-style*/
/**
 * strnchr - Find a character in a length limited string
 * @s: The string to be searched
 * @count: The number of characters to be searched
 * @c: The character to search for
 */


char *strnchr (const char *s, size_t count, int c){

    for (; count-- && *s != '\0'; ++s)
        if (*s == (char)c)
            return (char *) s;

    return NULL;
}


/*
 * strrchr:
 *
 * PUBLIC: #ifndef HAVE_STRRCHR
 * PUBLIC: char *strrchr __P((const char *, int));
 * PUBLIC: #endif
 */

char *strrchr (const char *p, int ch){

    char *save;
    char c;

    c = ch;

    for ( save = NULL;; ++p ) 
    {
        if (*p == c)
            save = (char *) p;

        if (*p == '\0')
            return (char *) save;
    }
	/* NOTREACHED */
}


//#todo
//definido em inttypes.h
intmax_t strtoimax (const char *str, char **endptr, int base)
{
    debug_print ("strtoimax: [TODO]\n");
    return 0;
}


//#todo
//definido em inttypes.h
uintmax_t strtoumax (const char *str, char **endptr, int base)
{
    debug_print ("strtoumax: [TODO]\n");
    return 0;
}


/*
 * credits: Serenity OS
static char foldcase(char ch);
static char foldcase(char ch)
{
    if (isalpha(ch))
        return tolower(ch);
    return ch;
}
*/


/*
 * credits: Serenity OS
int strcasecmp2(const char* s1, const char* s2);
int strcasecmp2(const char* s1, const char* s2)
{
    for (; foldcase(*s1) == foldcase(*s2); ++s1, ++s2) {
        if (*s1 == 0)
            return 0;
    }
    return foldcase(*(const unsigned char*)s1) < foldcase(*(const unsigned char*)s2) ? -1 : 1;
}
*/


/*
 * credits: Serenity OS
int strncasecmp(const char* s1, const char* s2, size_t n);
int strncasecmp(const char* s1, const char* s2, size_t n)
{
    if (!n)
        return 0;
    do {
        if (foldcase(*s1) != foldcase(*s2++))
            return foldcase(*(const unsigned char*)s1) - foldcase(*(const unsigned char*)--s2);
        if (*s1++ == 0)
            break;
    } while (--n);
    return 0;
}
*/





/*
 *********************************************************
 * strcasecmp:
 *     Do strcmp(3) in a case-insensitive manner.
 *
 * PUBLIC: #ifndef HAVE_STRCASECMP
 * PUBLIC: int strcasecmp __P((const char *, const char *));
 * PUBLIC: #endif
 */

int strcasecmp (const char *s1, const char *s2){

    unsigned char s1ch, s2ch;

    for (;;){

        s1ch = *s1++;
        s2ch = *s2++;

		//tolower
		
		if (s1ch >= 'A' && s1ch <= 'Z')
			s1ch += 32;
		
		if (s2ch >= 'A' && s2ch <= 'Z')
			s2ch += 32;
		
		if (s1ch != s2ch)
			return (int) (s1ch - s2ch);
		
		if (s1ch == '\0')
			return 0;
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

char *strncpy (char *s1, const char *s2, size_t n){

    char *s = s1;

    while (n > 0 && *s2 != '\0')
    {
        *s++ = *s2++;
        n--;
    }

    while (n > 0)
    {
        *s++ = '\0';
        n--;
    }

    return (char *) s1;
}


/*
 * strcmp:
 *     Compare two strings. 
 */

// See:
// http://man7.org/linux/man-pages/man3/strcmp.3.html

int strcmp(const char *s1, const char *s2){

    int i=0;

    for ( i=0; s1[i] == s2[i]; i++ )
    {
        if ( s1[i] == '\0' ){ 
            return 0; 
        }
    };


    return (int) ( s1[i] - s2[i] );
}


/*
 * strncmp:
 * compare two strings
 */

// See:
// http://man7.org/linux/man-pages/man3/strcmp.3.html

int strncmp (const char *s1, const char *s2, size_t n){

    while (n > 0)
    {
        n--;

        if ( *s1 != *s2 ){ 
            return (int) 1; 
        }

        *s1++; 
        *s2++;
    };

    if ( *s1 != '\0' || *s2 != '\0' )
    {
        return (int) 2;
    }


    return 0;
}


/*
 * memset:
 *    #todo: rever tipos;
 */

void *memset ( void *ptr, int value, int size ){

    if ( ptr != NULL && size > 0 )
    {
        unsigned char *temp = ptr;

        int i = 0;

        for ( i=0; i < size; i++ ){
            *temp++ = (unsigned char) value;
        }

    }


    return (void *) ptr;
}


//#todo: mover para memory.c ??
void *memoryZeroMemory ( void *ptr, size_t cnt ){

    volatile char *vptr = (volatile char *) ptr;

    while (cnt)
    {
        *vptr = 0;
        
        vptr++;
        cnt--;
    };

    return (void *) ptr;
}


/*
 * memcpy:
 *     ?? #todo: mover para memory.c ?? 
 */

// Simple, byte oriented memcpy. 

void *memcpy ( void *v_dst, const void *v_src, unsigned long c ){

    const char *src = v_src;

    char *dst = v_dst;

    while (c--)
    {
        *dst++ = *src++; 
    };

    return (void *) v_dst;
}


/*
 * strcpy: 
 *     Copy a string. 
 */

char *strcpy ( char *to, const char *from ){

    int i=0;

    while ( to[i] = from[i] )
    { 
        i += 1; 
    };

    return (char *) to;
}


/*
 //#test
char* strcpy(char* to, const char* from);
char* strcpy(char* to, const char* from)
{
    char *dest_ptr = to;
    const char *src_ptr = from;
    while ((*dest_ptr++ = *src_ptr++) != '\0')
        ;
    return to;
}
*/


size_t strlcpy (char *dst, const char *src, size_t size){

    size_t bytes = 0;
    char *q = dst;
    const char *p = src;
    char ch;

    while ( (ch = *p++) )
    {
		if (bytes + 1 < size)
			*q++ = ch;
		bytes++;
    }

	// If size == 0 there is no space for a final null... 
    if (size)
        *q = '\0';

    return bytes;
}


/*
 *************************
 * strcat:
 *     Concatenate strings. 
 */

char *strcat ( char *to, const char *from ){

    char *ret = to;

    while ( *to )
    { 
        to += 1; 
    };

    strcpy ( to, from );
    
    return (char *) ret;
}


/*linux style*/
/**
 * strchrnul - Find and return a character in a string, or end of string
 * @s: The string to be searched
 * @c: The character to search for
 *
 * Returns pointer to first occurrence of 'c' in s. If c is not found, then
 * return a pointer to the null byte at the end of s.
 */


char *strchrnul (const char *s, int c){

	while (*s && *s != (char)c)
		s++;
	return (char *) s;
}


size_t strlcat (char *dst, const char *src, size_t size){

    size_t bytes = 0;
    char *q = dst;
    const char *p = src;
    char ch;

    //#bugbug
    //E se size for menor que zero.?

    while (bytes < size && *q)
    {
		q++;
		bytes++;
    };

    if (bytes == size)
        return (bytes + strlen(src));

    while ((ch = *p++)){

		if (bytes + 1 < size)
			*q++ = ch;
		bytes++;
    };

	*q = '\0';
	return bytes;
}


char *strncat (char *dst, const char *src, size_t n){

    char *q = strchr (dst, '\0');

    const char *p = src;

    char ch;

    // #bugbug
    // E se n for menor que zero?

    while (n--)
    {
        *q++ = ch = *p++;
        if (!ch)
            return dst;
    };

    *q = '\0';

    return (char *) dst;
}


/* 
 * bcopy: Copia. 
 */

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
 *      zeros. 
 */

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
 *     Get the size of a string.
 */ 

size_t strlen (const char *s){

    size_t i=0;

    for ( i=0; s[i] != '\0'; i++ )
    { ; };

    return (size_t) i;
}


/* 
 * strnlen:
 *  Find the length of S, but scan at most MAXLEN characters.  
 *  If no '\0' terminator is found within the first MAXLEN characters, 
 *  return MAXLEN. 
 */

size_t strnlen ( const char *s, size_t maxlen ){

    size_t n=0;
    const char *e;
    
    //#bugbug
    // E se maxlen for negativo.

    //if ( maxlen <=0 )
        //return -1;

    for (e = s, n = 0; *e && n < maxlen; e++, n++)
    { ; };


    return (size_t) n;
}


char *strpbrk (const char *cs, const char *ct){

    const char *sc1, *sc2;

    for ( sc1 = cs; *sc1 != '\0'; ++sc1 )
    {
        for ( sc2 = ct; *sc2 != '\0'; ++sc2 )
        {
            if (*sc1 == *sc2)
                return (char *) sc1;
        };
    };


    return NULL;
}


/*linux style*/
/**
 * strsep - Split a string into tokens
 * @s: The string to be searched
 * @ct: The characters to search for
 *
 * strsep() updates @s to point after the token, ready for the next call.
 *
 * It returns empty tokens, too, behaving exactly like the libc function
 * of that name. In fact, it was (*stolen) from glibc2 and de-fancy-fied.
 * Same semantics, slimmer shape. ;)
 */

char *strsep(char **s, const char *ct){

    char *sbegin = *s;
    char *end;

    if (sbegin == NULL)
        return NULL;

    end = strpbrk (sbegin, ct);

	if (end)
		*end++ = '\0';
	*s = end;

    return (char *) sbegin;
}


/*linux style*/
/**
 * sysfs_streq - return true if strings are equal, modulo trailing newline
 * @s1: one string
 * @s2: another string
 *
 * This routine returns true iff two strings are equal, treating both
 * NUL and newline-then-NUL as equivalent string terminations.  It's
 * geared for use with sysfs input strings, which generally terminate
 * with newlines but are compared against values without newlines.
 */
//mudar esse bool.
/* 
bool sysfs_streq(const char *s1, const char *s2)/ 
bool sysfs_streq(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2) {
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return true;
	if (!*s1 && *s2 == '\n' && !s2[1])
		return true;
	if (*s1 == '\n' && !s1[1] && !*s2)
		return true;
	return false;
}
*/


/*linux stuff*/
/**
 * match_string - matches given string in an array
 * @array:	array of strings
 * @n:		number of strings in the array or -1 for NULL terminated arrays
 * @string:	string to match with
 *
 * Return:
 * index of a @string in the @array if matches, or %-EINVAL otherwise.
 */

// #todo: O valor de retorno. 
 
/*
int match_string(const char * const *array, size_t n, const char *string); 
int match_string(const char * const *array, size_t n, const char *string)
{
	int index;
	const char *item;

	for (index = 0; index < n; index++) {
		item = array[index];
		if (!item)
			break;
		if (!strcmp(item, string))
			return index;
	}

	return -EINVAL;
}
*/


/**
 * memset16() - Fill a memory area with a uint16_t
 * @s: Pointer to the start of the area.
 * @v: The value to fill the area with
 * @count: The number of values to store
 *
 * Differs from memset() in that it fills with a uint16_t instead
 * of a byte.  Remember that @count is the number of uint16_ts to
 * store, not the number of bytes.
 */
 
//#todo: incluir o header que permite usar esse tipo aí.
/* 
void *memset16(uint16_t *s, uint16_t v, size_t count); 
void *memset16(uint16_t *s, uint16_t v, size_t count)
{
	uint16_t *xs = s;

	while (count--)
		*xs++ = v;
	return s;
}
*/


/**
 * memset32() - Fill a memory area with a uint32_t
 * @s: Pointer to the start of the area.
 * @v: The value to fill the area with
 * @count: The number of values to store
 *
 * Differs from memset() in that it fills with a uint32_t instead
 * of a byte.  Remember that @count is the number of uint32_ts to
 * store, not the number of bytes.
 */

//#todo: incluir o header que permite usar esse tipo aí.
/*
void *memset32 (uint32_t *s, uint32_t v, size_t count); 
void *memset32 (uint32_t *s, uint32_t v, size_t count)
{
    uint32_t *xs = s;

	while (count--)
		*xs++ = v;
    return (void *) s;
}
*/


// ??
// Não é padrão. Mas deixe aqui.
static void *
check_bytes8 ( 
    const char *start, 
    char value, 
    unsigned int bytes )
{

    while (bytes)
    {
		if (*start != value)
			return (void *)start;
		start++;
		bytes--;
    };

    return NULL;
}



/**
 * strreplace - Replace all occurrences of character in string.
 * @s: The string to operate on.
 * @old: The character being replaced.
 * @new: The character @old is replaced with.
 *
 * Returns pointer to the nul byte at the end of @s.
 */

char *strreplace (char *s, char old, char new){

	for (; *s; ++s)
		if (*s == old)
			*s = new;

    return (char *) s;
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
}


/*
 * strspn:
 *   Gets the length of a substring.
 * Credits: 
 * Copyright (c) 2011, 2012 Jonas 'Sortie' Termansen.
 */
 
size_t strspn ( const char *str, const char *accept ){

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
}


/*
 **************************************
 * strtok_r:
 *     Usada por strtok.
 *
 * Credits: 
 *     Apple. (Open Source)
 */

char *strtok_r ( char *s, const char *delim, char **last ){

    char *spanp;
    int c, sc;
    char *tok;

    if ( s == NULL && (s = *last) == NULL )
    {
        return NULL;
    }

    // Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	
cont:
    
    c = *s++;
    
    for ( spanp = (char *) delim; (sc = *spanp++) != 0; )
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
                if ( c == 0 ){
                    s = NULL;

                }else{

                    char *w = s -1;

                    *w = '\0';
                };

		        *last = s;
				
		        return tok;
	        };
			
        } while( sc != 0 );
        
		//Nothing.

    };
    // NOTREACHED 
}


/*
 *********************************************
 * strtok:
 *     strtok 
 */

char *strtok ( char *s, const char *delim ){

    static char *last;

    return strtok_r ( s, delim, &last );
}



/*
 * strchr:
 * linux style 
 */

char *strchr (const char *s, int c){

	for (; *s != (char) c; ++s)
		if (*s == '\0')
			return NULL;

    return (char *) s;
}


/*linux style*/
void *memmove (void *dest, const void *src, size_t count){

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
    };

    return dest;
}



/*
 //linux style 
 * memscan - Find a character in an area of memory.
 * @addr: The memory area
 * @c: The byte to search for
 * @size: The size of the area.
 *
 * returns the address of the first occurrence of @c, or 1 byte past
 * the area if @c is not found
 */
 
void *memscan (void *addr, int c, size_t size){

    unsigned char *p = addr;

    while (size){

		if (*p == c)
			return (void *)p;
		p++;
		size--;
    };


    return (void *) p;
}


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
	
    while (l1 >= l2)
    {
		l1--;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1++;
    };


    return NULL;
}



/*
 ** Concatenate two given string, creating a mark space at the beginning.
 ** Return the new string pointer.
 */
/*
// It's a test.
// Credits: lua 1.0.
static char *__strconc (char *l, char *r);
static char *__strconc (char *l, char *r){

    char *s = calloc ( strlen(l) + strlen(r) +2, sizeof(char) );
 
    if (s == NULL)
    {
        printf ("Not enough memory \n");
        return NULL;
    }

    // Create mark space.
    *s++ = 0; 			
    
    return strcat ( strcpy(s,l),r );
}
*/


/*
 ** Duplicate a string,  creating a mark space at the beginning.
 ** Return the new string pointer.
 */
/*
// Credits: lua 1.0.
char *__strdup (char *l);
char *__strdup (char *l){
    
    char *s = calloc ( strlen(l)+2, sizeof(char) );
    
    if (s == NULL)
    {
        printf ("Not enough memory \n");
        return NULL;
    }

    //Create mark space.
    *s++ = 0; 			
    
    return strcpy (s,l);
}
*/



char *index (const char *s, int c){

    do {
		if (*s == c)
			return (char *) (s);
    } while (*s++);

    return(NULL);
}


char *rindex (const char *s, int c)
{
    return (char *) strrchr (s, c);
}



/*
 * Transform src, storing the result in dst, such that
 * strcmp() on transformed strings returns what strcoll()
 * on the original untransformed strings would return.
 */
 
// Credits: apple open source 

size_t strxfrm (char *dst, const char *src, size_t n){

    size_t srclen, copysize;

	// Since locales are unimplemented, this is just a copy.

    srclen = strlen (src);

    if (n != 0)
    {
		copysize = srclen < n ? srclen : n - 1;
		
		//(void) memcpy (dst, src, copysize);
		memcpy (dst, src, copysize);
		
		dst[copysize] = 0;
    }

    return (srclen);
}



/*
 * credits: Serenity OS.
size_t strxfrm(char* dest, const char* src, size_t n);
size_t strxfrm(char* dest, const char* src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; ++i)
        dest[i] = src[i];
    for (; i < n; ++i)
        dest[i] = '\0';
    return i;
}
*/



 
 /*
 The swab() function copies n bytes from the array pointed to by from
 to the array pointed to by to, exchanging adjacent even and odd
 bytes.  This function is used to exchange data between machines that
 have different low/high byte ordering.
 See: http://man7.org/linux/man-pages/man3/swab.3.html
 Credits: Apple open source.  
 */
/*
void swab (const void *from, void *to, size_t len);
void swab (const void *from, void *to, size_t len){
	
	register unsigned long temp;
	register int n;
	register char *fp, *tp;

	n = (len >> 1) + 1;
	fp = (char *)from;
	tp = (char *)to;
#define	STEP	temp = *fp++,*tp++ = *fp++,*tp++ = temp
	//round to multiple of 8
	while ((--n) & 07)
		STEP;
	n >>= 3;
	while (--n >= 0) {
		STEP; STEP; STEP; STEP;
		STEP; STEP; STEP; STEP;
	}
}
*/




char *strerror (int errnum)
{
    debug_print ("strerror: [TODO]\n");
    return 0; 
}


/* XSI-compliant */
int strerror_r (int errnum, char *buf, size_t buflen)
{
    char *msg = strerror (errnum);

    if (strlen(msg) >= buflen)
        return -1;  //return ERANGE;


    strcpy(buf, msg);

    return 0;
}


/* GNU-specific */
/*
char *strerror_r(int errnum, char *buf, size_t buflen)
{ 
    debug_print ("strerror_r: GNU-specific \n");
    return 0; 
}
*/




/*
char *strerror_l(int errnum, locale_t locale);
char *strerror_l(int errnum, locale_t locale)
{ return 0; }
*/



char *strsignal (int sig)
{
    debug_print ("strsignal: [TODO]\n");
    return 0; 
}


//isso ja existe no atacama.
//#define tolower(c)	(isupper(c) ? c + 'a' - 'A' : c)
//#define toupper(c)	(islower(c) ? c + 'A' - 'a' : c)

// Converte a string para tudo maiusculo.
void strtoupper (char *src){

    char *c;

    if (!src){
        return;
    }

    c = src;
  
    while ((*c)!='\0')
    {
        (*c) = toupper (*c);
        c++;
    };
}


//
// End.
//

