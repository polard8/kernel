/*
 * Arquivo: types.h 
 * 
 * Descrição:
 *     Define tipos de variáveis.
 *     Obs: System types. 
 */


#define NULL ((void *)0)
 
#define FALSE 0
#define TRUE 1


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
typedef char ** poll;
typedef char ** POLL;

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




/*
 *  Void
 */
typedef void VOID; 
 

/*
 *  Basics
 */
typedef char  CHAR;
typedef short SHORT;
typedef int INT;        //32bit
typedef long  LONG;     //32bit


/*
 *  Unsigned Basics
 */
typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned int   UINT;      //32bit
typedef unsigned long  ULONG;     //32bit



typedef	unsigned long  vm_offset_t;
typedef	unsigned long  vm_size_t;

/*
 * Basic integral types.
 * (BSD style)
 *
 */ 
 
typedef char  int8_t;
typedef unsigned char  uint8_t;
typedef short  int16_t;
typedef unsigned short  uint16_t;
typedef int  int32_t;
typedef unsigned int  uint32_t;
//typedef	long long		  int64_t;
//typedef	unsigned long long	u_int64_t;


//
// End
//

