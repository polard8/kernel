/*
 * File: string.h
 *
 * Descrição:
 *     Operações com strings. Padrão C.
 */

//@todo: Deve ser const char.
int strcmp(char *s1, char *s2);
int strncmp(char *s1, char *s2, int len);


//#bugbug deletando porque tá errado.
//int str_cmp(unsigned char *str1, unsigned char *str2);

void *memoryZeroMemory(void* ptr, size_t cnt);
void *memcpy(void *v_dst, const void *v_src, unsigned long c);
//@todo: void *memcpy(void *dst, const void *src, size_t c); 
char *strcpy(char *to, const char *from);
char *strcat(char *to, const char *from);
void bcopy(char *from, char *to, int len);
void  bzero(char *cp, int len);
size_t strlen(const char *s);


/* Copyright (c) 2011, 2012 Jonas 'Sortie' Termansen. */
size_t strcspn(const char* str, const char* reject);
size_t strspn(const char* str, const char* accept);
//char* strtok_r(char* str, const char* delim, char** saveptr);
//char* strtok(char* str, const char* delim);


/*apple*/
char *
strtok_r(char *s, const char *delim, char **last);
char *
strtok(char *s, const char *delim);

//
// End.
//

