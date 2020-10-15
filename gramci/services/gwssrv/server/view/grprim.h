



#ifndef __GRPRIM_H
#define __GRPRIM_H   1


#define grMIN2(a, b)  (((a) < (b)) ? (a) : (b))
#define grMAX2(a, b)  (((a) > (b)) ? (a) : (b))


#define grMIN3(x,y,z)     (x < y  ? (x < z ? x : z) : (y < z ? y : z))
#define grMAX3(x,y,z)     ( (x>y) ? ((x>z)?x:z)     : ((y>z)?y:z) )


/*
#define MIN2(v0,v1) ((v0<v1)?v0:v1)
#define MAX2(v0,v1) ((v0>v1)?v0:v1)
#define MIN3(v0,v1,v2) ((v0<v1)?((v0<v2)?v0:v2):((v1<v2)?v1:v2))
#define MAX3(v0,v1,v2) ((v0>v1)?((v0>v2)?v0:v2):((v1>v2)?v1:v2))
*/


// define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

int grInit(void);
int grPlot0 (int z, int x, int y, unsigned long color);



void plotLine3d(int x0, int y0, int z0, int x1, int y1, int z1, unsigned long color);


void
rectangle (
    int left, int top, 
    int right, int bottom,
    unsigned long color );

void
rectangleZ (
    int left, int top, 
    int right, int bottom,
    unsigned long color,
    int z );
    
    
void 
cube ( 
    int bx0, int by0, int bx1, int by1,  //back rect
    int fx0, int fy0, int fx1, int fy1,  //front rect 
    unsigned long color );
    
void 
cubeZ ( 
    int bx0, int by0, int bx1, int by1,  //back rect
    int fx0, int fy0, int fx1, int fy1,  //front rect 
    unsigned long color, int z );



void plotCircle (int xm, int ym, int r, unsigned long color);

void plotEllipseRect(int x0, int y0, int x1, int y1, unsigned long color);

#endif    



