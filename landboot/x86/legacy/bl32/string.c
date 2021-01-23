/*
 * File: string.c
 *
 * Descrição:
 *     Rotinas com string.
 *     Parte da biblioteca C para o Boot Loader.
 *
 * Versão 1.0, 2015.
 */
 
 
#include <bootloader.h>


/* 
 * strcmp: 
 *     Compara duas strings. 
 */

int strcmp (char *s1, char *s2){

    register int i=0;

    for ( i=0; s1[i] == s2[i]; i++ )
    {
        if (s1[i] == '\0') { return 0; }
    };

    return ( (int) (s1[i] - s2[i]) );
}


/* strncmp: 
 *     Compara duas strings. */

int strncmp (char *s1, char *s2, int len){

    // copy
    register int n = len;

    while (n > 0)
    {
        n--;
        
        if (*s1 != *s2){
            return (int) 1;
        }

		*s1++;
		*s2++;
    };


    if (*s1 != '\0' || *s2 != '\0')
    {
        return (int) 2;
    };

    return 0;
}


/*
 * str_cmp: 
 *     Compara strings.
 */

int str_cmp (unsigned char *str1, unsigned char *str2){

    while ( *str1 == *str2 && 
            *str1 != 0 && 
            *str2 != 0 )
    { 
        str1++; 
        str2++; 
    };

 
	// Mesma quantidade de chars iguais.
    if (*str1 == *str2) 
        return 0;


    if (*str1 > *str2) 
        return (int) 1;


    if (*str1 < *str2) 
        return (int) -1;


//Done.

    return (int) -1;
}


/*
 * memcpy:
 *     Copia uma área de memória. 
 */

void *memcpy ( void *v_dst, const void *v_src, unsigned long c ){

    const char *src = v_src;
    char *dst = v_dst;

	//Simple, byte oriented memcpy.

    while (c--)
        *dst++ = *src++;


//done:
    return v_dst;
}


/*
 * strlen:
 *     Obtem o tamanho de uma string. 
 */

size_t strlen (const char *s)
{
    //loop
    register int i=0;

    for ( i=0; s[i] != '\0'; i++ ){ ; };

    return (size_t) i;
}


/*
 * strcpy: 
 *     Copia uma string 
 */

char *strcpy (char *to, const char *from)
{
    //loop
    register int i=0;

    while (to[i] = from[i])
    {
        i += 1;
    };

    return (to);
}


/*
 * strcat:
 *     Acrescenta uma string ao fim de outra. 
 */

char *strcat (char *to, const char *from){
	
	char *ret = to;

	while (*to)
	{
		to += 1;
	};

	strcpy (to, from);
	
	return (ret);
}


/*
 * bcopy:
 *     Copia uma quantidade de bytes. 
 */

void bcopy (char *from, char *to, int len){
	
	while (len--)
	{
		*to++ = *from++;
	};
}


/*
 *  bzero:
 *     Preenche com zeros. 
 */

void bzero (char *cp, int len){

	while (len--)
	{
		*(cp + len) = 0;
	};
}


//
// End.
//
