
// protocol.h

#ifndef  __LIBGWS_PROTOCOL_H
#define  __LIBGWS_PROTOCOL_H    1


// =======================================
// Protocol request constants
//
// #todo:
// Create a consistent interface.
// See: xxxHandleNextClientRequest() and gwsProcedure on aurora/server/main.c 
// See: 
// All the standar messages, just like MSG_SYSKEYUP ...
// There are some old messages below 369.

#define GWS_GetInputMessage        369
#define GWS_Hello                 1000
#define GWS_CreateWindow          1001
#define GWS_BackbufferPutPixel    1002
#define GWS_DrawHorizontalLine    1003
#define GWS_DrawChar              1004
#define GWS_DrawText              1005
#define GWS_RefreshWindow         1006
#define GWS_RedrawWindow          1007
#define GWS_ResizeWindow          1008
#define GWS_ChangeWindowPosition  1009
#define GWS_BackbufferPutPixel2   2000
#define GWS_Disconnect            2010
#define GWS_RefreshScreen         2020
#define GWS_RefreshRectangle      2021
//#define GWS_GetSendEvent          2030  // send event #

// The server will return an event from the its client's event queue.
#define GWS_GetNextEvent          2031

#define GWS_GrPlot0               2040
#define GWS_GrCubeZ               2041
#define GWS_GrRectangle           2042
#define GWS_AsyncCommand          2222

#define GWS_SetText  2240
#define GWS_GetText  2241

// Quit the process if it's possible.
//#define GWS_Quit    4080


#define GWS_DrainInput            8080

#define GWS_HotKey  8888

//#todo
//#define GWS_SwitchFocus    9090

//#todo
// Called by the kernel x times per second.
//#define GWS_RefreshDirtyRectangles  9091
//#define GWS_Compositor     9091    

//#todo
// Redraw all the windows. Back to front.
//#define GWS_UpdateDesktop  9092

#define GWS_GetWindowInfo   9093

#define GWS_CloneAndExecute  9099

// ...

#endif    



