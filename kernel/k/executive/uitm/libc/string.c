/*
 * File: string.c
 *
 * Descrição:
 *     Operações com strings.
 *     Parte da biblioteca da linguagem C.
 *
 * Versão 1.0, 2015.
 */

 
#include <kernel.h>


/*
 * strcmp:
 *     Compara duas strings.
 */
int strcmp(char * s1, char * s2)
{
	int i;

	for(i = 0; s1[i] == s2[i]; ++i){
		if( s1[i] == '\0' ){
			return (0);
		};
	};
	return((int) (s1[i] - s2[i]));
};




/*
 * strncmp:
 *     Compara duas strings.
 *
 */
int strncmp(char *s1, char *s2, int len)
{
	int n = len;
	
	while(n > 0)
	{	
	    n--;
        
		if(*s1 != *s2){
            return 1;
        };
		
		*s1++;
		*s2++;
	};		
			
			
	if (*s1 != '\0' || *s2 != '\0' ){	
	    return 2;
	};
	return 0;
};


/*
 * str_cmp:
 *     Compara strings.
 */
int str_cmp(unsigned char *str1, unsigned char *str2)
{
	while(*str1 == *str2 && *str1 != 0 && *str2 != 0) 
    { 
        str1++; 
        str2++; 
    };
    
	// mesma quantidade de chars iguais
    if(*str1 == *str2) 
	    return 0;
	
	if(*str1 > *str2) 
	    return 1;
		
	if(*str1 < *str2) 
	    return -1;
	
    return -1;
};

 
 
 
 
/*
 * memcpy:
 *
 *
 */
void *memcpy(void *v_dst, const void *v_src, unsigned long c)
{
	const char *src = v_src;
	char *dst = v_dst;

	/* Simple, byte oriented memcpy. */
	while (c--)
		*dst++ = *src++;

	return v_dst;
};


/*
 * strcpy - copia uma string
 *
 *
 */
char *strcpy(char *to, const char *from)
{
	int i = 0;

	while( to[i] = from[i] ){
		i += 1;
	};
	return (to);
};


/*
 * strcat - acrescenta uma string ao fim de outra.
 *
 *
 */
char *strcat(char *to, const char *from)
{
	char *ret = to;

	while(*to) {
		to += 1;
	};
	
	strcpy(to, from);
	return (ret);
};


/*
 *  bcopy:
 *
 *
 */
void bcopy(char *from, char *to, int len)
{
	while(len--) {
		*to++ = *from++;
	};
    return;
};


/*
 *  bzero:
 *      Preenche com zeros.
 *
 */
void  bzero(char *cp, int len)
{
	while (len--) {
		*(cp + len) = 0;
	};
    return;
};

/*
 * strlen:
 *     Calcula o tamanho de uma string.
 *
 */ 
size_t strlen(const char *s)
{	
    size_t i = 0;
	
	for (i = 0; s[i] != '\0'; ++i) {
	;
	};
	
done:
	return ( (size_t) i );
};


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



