

#ifndef __GWSSRV_GLOBALS_H
#define __GWSSRV_GLOBALS_H



// ## button support ##
#define GWS_COLOR_BUTTONFACE            0x00F0F0F0
#define GWS_COLOR_BUTTONFACE2           0x00E0E0E0
#define GWS_COLOR_BUTTONFACE3           0x00D0D0D0
#define GWS_COLOR_BUTTONHIGHLIGHT       0x00FFFFFF
#define GWS_COLOR_BUTTONHIGHLIGHT2      0x00404040
#define GWS_COLOR_BUTTONHIGHLIGHT3      0x00008080
#define GWS_COLOR_BUTTONHIGHLIGHTTEXT   COLOR_WHITE
#define GWS_COLOR_BUTTONHIGHLIGHTTEXT2  COLOR_WHITE 
#define GWS_COLOR_BUTTONSHADOW          0x00A0A0A0
#define GWS_COLOR_BUTTONSHADOW2         0x00303030 
#define GWS_COLOR_BUTTONSHADOW3         0x00202020 
#define GWS_COLOR_BUTTONTEXT            COLOR_TEXT


// #ordem
// hadware, software

unsigned long  ____BACKBUFFER_VA;
unsigned long  ____FRONTBUFFER_VA;  //#test

unsigned long SavedBootBlock;
unsigned long SavedLFB;   // ??? pa va ???
unsigned long SavedX;
unsigned long SavedY;
unsigned long SavedBPP; 

unsigned long __device_width;
unsigned long __device_height;



#endif   



