/*
 * File: mp.h 
 * 
 *     Multi-processor (MP) support.
 *     Symmetric multiprocessing (SMP) 
 */



#ifndef ____MP_H
#define ____MP_H


// See:
// https://en.wikipedia.org/wiki/Symmetric_multiprocessing
// ...

// List for pointer of ProcessorBlock_d struture.
// See: hal/cpu.h

//#define MAX_PROCESSOR_COUNT 32

unsigned long processorList[32]; 



#endif   



//
// End.
//


