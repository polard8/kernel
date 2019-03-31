

//inttypes.h

// Conversão precisa entre tipos inteiros.

//long long??
typedef unsigned long uintptr_t;

typedef unsigned int uintmax_t;
typedef int intmax_t;

intmax_t strtoimax (const char* str, char** endptr, int base);
uintmax_t strtoumax (const char* str, char** endptr, int base);






