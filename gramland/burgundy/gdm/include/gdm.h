
// gwm.h 
// Main header file for the gwm.
// It uses the libgws library.

#ifndef __GDM_H
#define __GDM_H    1

#define WINDOW_COUNT_MAX  1024
unsigned long windowList[WINDOW_COUNT_MAX];

extern unsigned long gScreenWidth;
extern unsigned long gScreenHeight;

// ---------------

int gwm_init_globals(void);
int gwm_init_windows(void);

#endif    



