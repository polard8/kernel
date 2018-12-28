

//Conflito. O certo é 'int'
//#ifndef _SIZE_T
//#define _SIZE_T
//typedef unsigned int size_t;
//#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef int ssize_t;
#endif

#ifndef _TIME_T
#define _TIME_T
typedef long time_t;		   /* time in sec since 1 Jan 1970 0000 GMT */
#endif

#ifndef _CLOCK_T
#define _CLOCK_T
typedef long clock_t;		   /* unit for system accounting */
#endif



/* 
 Process IDentifier 
 posix.  
 */
#ifndef __PID_T
#define __PID_T 
typedef int pid_t;
#endif 




