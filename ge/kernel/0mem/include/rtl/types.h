/*
 * Arquivo: types.h 
 * 
 * Descrição:
 *     Define tipos de variáveis.
 *     Obs: System types. 
 */
 
 

#ifndef ____TYPES_H
#define ____TYPES_H    1 





#define NULL ((void *)0)
 
#define FALSE 0
#define TRUE 1

/* Void */
typedef void VOID; 

// It will help us to find the irq handlers.
typedef void __VOID_IRQ; 


/* Basics */
typedef char  CHAR;
typedef short SHORT;
typedef int INT;        //32bit
typedef long  LONG;     //32bit


/* Unsigned Basics */
typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned int   UINT;      //32bit
typedef unsigned long  ULONG;     //32bit

/* sysv - unix system v */
typedef unsigned char   unchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef unsigned long   ulong;

/* bsd */
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;


/* bsd - Basic integral types. */ 
typedef char            int8_t;
typedef unsigned char   uint8_t;
typedef short           int16_t;
typedef unsigned short  uint16_t;
typedef int             int32_t;
typedef unsigned int    uint32_t;
//typedef	long long		  int64_t;
//typedef	unsigned long long	u_int64_t;

/* Windows CE virtual address */
typedef uint32_t		vaddr_t;
typedef uint32_t		vsize_t;
/* Physical address */
typedef uint32_t		paddr_t;
typedef uint32_t		psize_t;

/* kernel virtual address */
typedef uint32_t		kaddr_t;
typedef uint32_t	ksize_t;


//
// System types.
//
//typedef int tid_t;   //Thread id type.
//typedef int pid_t;   //Process id type.
//typedef int ppid_t;  //Parent process id type.
//typedef int uid_t;   //User id type.
//typedef int gid_t;   //Group id type.
//...


//
// pool
//

//tipo array de strings
typedef char **poll;
typedef char **POLL;

//array de unsigned longs contendo ponteiros 
//para pools de strings;
typedef unsigned long pool_list_t;
typedef unsigned long POOLLIST;


/*
 *  HANDLE
 */
typedef void *HANDLE;              //Generic handle.
typedef void *HPROCESS;            //Process.
typedef void *HTHREAD;             //Thread.
typedef void *HUSERSESSION;        // *User Session.
typedef void *HWINDOWSTATION;      // *Window Station.
typedef void *HDESKTOP;            // *Desktop.
typedef void *HWINDOW;             // *Window.
typedef void *HMENU;               //Menu.
//typedef void *KHANDLE;             //Kernel Handle.
//typedef void *OHANDLE;             //Object Handle. 
//typedef void *RPC_HANDLE;            //Remote Procedure Call Handle.
//typedef void *LPC_HANDLE;            //Local Procedure Call Handle.
//...


//??
typedef  unsigned long  vm_offset_t;
typedef  unsigned long  vm_size_t;



// Parent Process IDentifier 
typedef  int  ppid_t;


// Thread IDentifier. linux,  
typedef  int  tid_t; 


//
// types used for the ELF support.
//

// See: exec_elf.h
typedef  signed char         __int8_t;
typedef  unsigned char       __uint8_t;
typedef  short               __int16_t;
typedef  unsigned short      __uint16_t;
typedef  int                 __int32_t;
typedef  unsigned int        __uint32_t;
//typedef  long long           __int64_t;
//typedef  unsigned long long  __uint64_t;
//...




#endif    //____TYPES_H



//
// End
//

