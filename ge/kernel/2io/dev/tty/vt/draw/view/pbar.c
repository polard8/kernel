/*
 * File: pbar.c
 */


#include <kernel.h>


//
// == progress bar.
//

unsigned long progressbar_left;
unsigned long progressbar_top;
unsigned long progressbar_width;
unsigned long progressbar_height;
unsigned long progressbar_offset;


// #bugbug
// This is a 'designer' thing.
// We can move this to the view/ folder.

void CreateProgressBar (void)
{

    if ( gdefShowProgressBar == FALSE ){
        return;
    }
    
    // 5 = full gui
    if ( current_runlevel != 5 ){
        return;
    }

    //isso nao funciona ainda.
    //unsigned long screenWidth  = systemGetSystemMetrics(1);
    //unsigned long screenHeight = systemGetSystemMetrics(2);

    // 3 fases marcadas.: [0,1,2]
    // a fase 3 nao sera marcada pois eh o logon
    progressbar_width = (32 * 3);
    progressbar_height = 8;

    progressbar_left = 8;
    progressbar_top  = 8;
    
    progressbar_offset=0;
    
    drawDataRectangle ( 
        progressbar_left, progressbar_top, 
        progressbar_width, progressbar_height, COLOR_WHITE );
   
   refresh_screen();
}


void IncrementProgressBar(void)
{
    if ( gdefShowProgressBar == FALSE ){
        return;
    }

    // 5 = full gui
    if ( current_runlevel != 5 ){
        return;
    }

    drawDataRectangle ( 
        progressbar_left + progressbar_offset, progressbar_top, 
        32, 8, COLOR_GREEN );
   
   progressbar_offset = (progressbar_offset + 32);
   
   refresh_screen();
}



//
// End.
//


