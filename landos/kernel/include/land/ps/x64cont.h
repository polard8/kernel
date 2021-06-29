// x64cont.h
// x86_64 context support.
//

#ifndef __X64COUNT_H
#define __X64COUNT_H    1

// #todo
// functions to 'save' and 'restore' context.


//
// == prototypes ==============
//

void save_current_context (void);
void restore_current_context (void);

int contextCheckThreadRing3Context (int tid);

#endif    


