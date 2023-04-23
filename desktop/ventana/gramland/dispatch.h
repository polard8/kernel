
// dispatch.h
// The handlers for the requests.
// See:
// protocol.h, 
// main.c

#ifndef __DISPATCH_H
#define __DISPATCH_H    1

// 1001
// See: window.c
int serviceCreateWindow(int client_fd);

// 1002
// put pixel

// 1003
// Horizontal line
int servicelineBackbufferDrawHorizontalLine(void);

// 1004
// See: char.c
int serviceDrawChar(void);

// 1005
int serviceDrawText(void);

// 1006
int serviceRefreshWindow(void);

// 1007
int serviceRedrawWindow(void);

// 1008
int serviceResizeWindow(void);

// 1009
int serviceChangeWindowPosition(void);

// 2021
int serviceRefreshRectangle(void);

// 2031
// When a client get the next event from it's own queue.
int serviceNextEvent(void);

// 2041
int serviceGrCubeZ(void);

// 2042
int serviceGrRectangle(void);

// 2222
int serviceAsyncCommand(void);
// 2222: service 1
void serviceExitGWS(void);

// 2223
int servicePutClientMessage(void);

// 2224
int serviceGetClientMessage(void);

// #todo: No number yet. 2240
int serviceSetText(void);
// #todo: No number yet. 2241
int serviceGetText(void); 


// 2030 ?
// When a client send us an event
int serviceClientEvent(void);


// 9093
// See: main.c
int serviceGetWindowInfo(void);

// 9099
void serviceCloneAndExecute(void);

// ??
// Button
int serviceDrawButton (void); 

// ??
// Get a message given the Index and the Restart flag.
int serviceNextEvent2(void);

// ??
int serviceGrPlot0(void);

// ??
// Pixel
int servicepixelBackBufferPutpixel(void);


#endif    





