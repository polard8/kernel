/*
 * File: types.h 
 * 
 * Descrição:
 *     Define tipos de variáveis.
 *     Tipos usados na biblioteca C99 32bit em user mode.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */

 
#define TRUE 1
#define FALSE 0
#define NULL ((void *)0)


//HANDLE.
typedef void *HANDLE;

//Void.
typedef void VOID; 
 
//Basics.
typedef char   CHAR;
typedef short  SHORT;
typedef int    INT;     // 32bit
typedef long   LONG;    // 32bit


//Unsigned Basics.
typedef unsigned char   UCHAR;
typedef unsigned short  USHORT;
typedef unsigned int    UINT;      // 32bit
typedef unsigned long   ULONG;     // 32bit


//Ints.  
typedef char     int8_t;
typedef short    int16_t;
typedef int      int32_t;

//Unsigned Ints. 
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned int      uint32_t;



// bsd stuff
/* 7.18.1.1 Exact-width integer types */
typedef	signed char     __int8_t;
typedef	unsigned char   __uint8_t;
typedef	short           __int16_t;
typedef	unsigned short  __uint16_t;
typedef	int             __int32_t;
typedef	unsigned int    __uint32_t;
//typedef	long long		__int64_t;
//typedef	unsigned long long	__uint64_t;



/* BSD-style unsigned bits types */
typedef __uint8_t   u_int8_t;
typedef __uint16_t  u_int16_t;
typedef __uint32_t  u_int32_t;
//typedef	__uint64_t	u_int64_t;


// i like this
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
//typedef unsigned long long  u64;



#define __packed        __attribute__((packed))
#define __aligned(x)    __attribute__((aligned(x)))
#define __optional      __attribute__((weak))



//
//End.
//

