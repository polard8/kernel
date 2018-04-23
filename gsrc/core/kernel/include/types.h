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


/*
 *  Ints 
 */ 
typedef char  int8_t;
typedef short int16_t;
typedef int   int32_t;


/*
 *  Unsigned Ints
 */ 
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;


/*
//Linux types.

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;
*/

//
// Fim.
//

