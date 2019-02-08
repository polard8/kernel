

//stdint.h

// Definição de tipos de dados inteiros.

//typedef uint64_t uintmax_t
typedef uint32_t uintmax_t;

//#bugbug hack hack
#define uint64_t uint32_t


#define INT8_MIN    (-0x7f - 1)
#define INT16_MIN   (-0x7fff - 1)
#define INT32_MIN   (-0x7fffffff - 1)
#define INT64_MIN   INT32_MIN //(-0x7fffffffffffffff - 1)


#define INT8_MAX    0x7f 
#define INT16_MAX   0x7fff 
#define INT32_MAX   0x7fffffff 
#define INT64_MAX   INT32_MAX  //   0x7fffffffffffffff 

#define UINT8_MAX   0xff 
#define UINT16_MAX  0xffff 
#define UINT32_MAX  0xffffffff 
#define UINT64_MAX  UINT32_MAX //0xffffffffffffffff 





