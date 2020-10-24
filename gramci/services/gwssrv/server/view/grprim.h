



#ifndef __GRPRIM_H
#define __GRPRIM_H   1




struct gr_vec3D_d
{
    int x;
    int y;
    int z;
    
    // for interpolation.
    unsigned long color;
};

struct gr_line_d
{
    struct gr_vec3D_d p[2];
};

struct gr_triandle_d
{
    struct gr_vec3D_d p[3];
};

struct gr_rectangle_d
{
    struct gr_vec3D_d p[4];
};

struct gr_cube_d
{
    struct gr_vec3D_d p[8];
};



/*
struct gr_mat4x4_d 
{
    int m[4][4];
};
*/


/*
struct gr_mesh_d 
{
    void *list;
};
*/


//
// ===========================================
//

// matrix


static int projection4x4[4][4] = { 
        {1,0,0,0}, 
        {0,1,0,0},
        {0,0,0,0},
        {1,1,0,0}
        };


void multiply4 (int mat1[][4], int mat2[][4], int res[][4]);

// function to multiply two matrices
void 
multiplyMatrices (
    int  first[][10],
    int second[][10],
    int result[][10],
    int r1, int c1,   // rows and columns for the first matrix
    int r2, int c2,   // rows and columns for the second matrix
    int rr, int cr );


void matrix_demo1(void);

//
// ===========================================================
//


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
ras_rectangleZ (
    int left, int top, int z0,
    int right, int bottom, int z1,
    unsigned long color );


int xxxInflateCubeZ ( struct gr_cube_d *cube, int value );
int xxxDeflateCubeZ ( struct gr_cube_d *cube, int value );
int xxxCubeZ ( struct gr_cube_d *cube );


void cube_demo1(void);


void plotCircle (int xm, int ym, int r, unsigned long color);
void 
plotCircleZ ( 
    int xm, 
    int ym, 
    int r, 
    unsigned long color, 
    int z );


void plotEllipseRect(int x0, int y0, int x1, int y1, unsigned long color);

void 
plotEllipseRectZ (
    int x0, int y0, 
    int x1, int y1, 
    unsigned long color,
    int z );


//#test
void noraDrawingStuff(void);
void noraDrawingStuff3(int x, int y, int z);

// Fibonacci Series using Recursion 
int fib(int n);


void 
plotCharBackbufferDrawcharTransparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c );

void 
plotCharBackbufferDrawcharTransparentZ ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c,
    int z );


// substitui cor no lfb
void grDCMono (
    struct gws_display_d *dc,
    unsigned char subpixel_quest,         //I64 quest=COLOR_TRANSPARENT,
    unsigned char subpixel_true_color,    //I64 true_color=0,
    unsigned char subpixel_false_color );  //I64 false_color=COLOR_MONO)


// substitui cor no lfb
void grDCColorChg ( 
    struct gws_display_d *dc,
    unsigned char subpixel_src_color,
    unsigned char subpixel_dst_color );  // dst_color=COLOR_TRANSPARENT )

#endif    





