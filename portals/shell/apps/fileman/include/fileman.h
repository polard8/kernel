
/*
 * File: gwm.h 
 * 
 *     Main header file for the gwm.
 *     It uses the libgws library.
 * 
 */



unsigned long gScreenWidth;
unsigned long gScreenHeight;



#define WINDOW_COUNT_MAX 1024

unsigned long windowList[WINDOW_COUNT_MAX];


int gwm_init_globals(void);

int gwm_init_windows(void);


