/*
 * File: floppy.h
 * 
 *     Why not ?
 *
 * 2015 - Created by Fred Nora.
 */


#ifndef ____FLOPPY_H
#define ____FLOPPY_H


//FDD ports.
#define DOR1  0x3F2    /* Digital Output Register */
#define DOR2  0x372  
#define MSR1  0x3F4    /* Main Status Register */
#define MSR2  0x374  
#define DR1   0x3F5    /* Data Register */
#define DR2   0x375
#define DIR1  0x3F7    /* Digital Input Register */
#define DIR2  0x377
#define CCR1  0x3F7    /* Configuration Contorol Register */
#define CCR2  0x377
#define DOR   DOR1
#define DSR   MSR1


typedef struct floppy_d floppy_t;
struct floppy_d
{
	//...
    //@todo fdd struct
    int dummy;	
};



typedef struct fdd_d fdd_t;
struct fdd_d
{
	//...
    int dummy;
};



#endif



//
// End.
//

