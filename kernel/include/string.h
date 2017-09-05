/*
 * Arquivo: string.h
 *
 * Descrição:
 *     Operações com strings. Padrão C.
 */
 
 

//@todo: void *memcpy(void *dst, const void *src, size_t c);  
void *memcpy(void *v_dst, const void *v_src, unsigned long c);

//@todo: Deve ser const char.
int strcmp(char *s1, char *s2);
int strncmp(char *s1, char *s2, int len);

int str_cmp(unsigned char *str1, unsigned char *str2);

size_t strlen(const char *s);

char *strcpy(char *to, const char *from);
char *strcat(char *to, const char *from);
void bcopy(char *from, char *to, int len);
void  bzero(char *cp, int len);

