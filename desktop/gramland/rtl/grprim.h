
// grprim.h 
// Header for primitives.

#ifndef __GRPRIM_H
#define __GRPRIM_H   1

#define grMIN2(a, b)  (((a) < (b)) ? (a) : (b))
#define grMAX2(a, b)  (((a) > (b)) ? (a) : (b))
#define grMIN3(x,y,z)    (x < y  ? (x < z ? x : z) : (y < z ? y : z))
#define grMAX3(x,y,z)    ( (x>y) ? ((x>z)?x:z)     : ((y>z)?y:z) )
/*
#define MIN2(v0,v1) ((v0<v1)?v0:v1)
#define MAX2(v0,v1) ((v0>v1)?v0:v1)
#define MIN3(v0,v1,v2) ((v0<v1)?((v0<v2)?v0:v2):((v1<v2)?v1:v2))
#define MAX3(v0,v1,v2) ((v0>v1)?((v0>v2)?v0:v2):((v1>v2)?v1:v2))
*/
//#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

// 2D integer vector.
struct gr_vec2D_d
{
    int x;
    int y;
    unsigned int color;
};

// 3D integer vector.
struct gr_vec3D_d
{
    int x;
    int y;
    int z;
    unsigned int color;
};

// 3D line
struct gr_line_d
{
    struct gr_vec3D_d p[2];
};

// 3D triangle
struct gr_triangle_d
{
    struct gr_vec3D_d p[3];
    struct gr_triangle_d *last;
    struct gr_triangle_d *next;
};

// 3D rectangle
struct gr_rectangle_d
{
    struct gr_vec3D_d p[4];
    struct gr_rectangle_d *last;
    struct gr_rectangle_d *next;
};

// 3D Cube
struct gr_cube_d
{
    struct gr_vec3D_d p[8];
};


#define POLYGON_POLYPOINT    1
#define POLYGON_POLYLINE     2

struct gr_polygon_d 
{
// type: POLYLINE, POLYPOINT
    int type;
// number of elements.
    int n;
// List of vectors.
    void *list_address;
};


// #define RAY_TYPE_LIGHT    1
// #define RAY_TYPE_??       2

#define RAY_ORIGIN  0
#define RAY_TARGET  1
// todo: aliases

// a vector with a starting point.
struct gr_ray_d
{
// Type of ray.
// primary ray, reflection ray, shadow ray.
    int type;

    //int intensity;
    //int gradation;
    //int interpolation;
    // ...

// The starting point is the source of light.
//#define RAY_ORIGIN  0
//#define RAY_TARGET  1

    // 0 = starting point
    // 1 = vector
    struct gr_vec3D_d p[2];

    // Distance between the starting point and
    // the target.
    int distance;
};




// The Perspective Calculation

// we can calculate the location of a 3D vertex in a 
// 2D viewing window with a multiplication and a division like this:
// x' = (x*near)/z
// y' = (y*near)/z
// x' = (x*near)/(-z)
// y' = (y*near)/(-z)

//
// camera
//


// array of chars.
struct gr_bitmap_d
{
    int type;
    unsigned long width;
    unsigned long height;
// 64 falgs.
    unsigned long flags;
    unsigned int color;
// Translation
    int x;
    int y;
    int z;
// buffer
    char *body;
};

// struct gr_bitmap_d *bitmap_screen;
// ...


//
// ===========================================================
//

int grInit(void);


// See: view()
void 
gwsDepthRange(
    int minZ, 
    int maxZ);

void 
gwsViewport(
    int topleft_x, 
    int topleft_y, 
    int width, 
    int height);

// Point. 
// #todo: maybe we can ues the structure dc.
int 
grPlot0 (
    struct gws_window_d *clipping_window,   
    int z, 
    int x, 
    int y, 
    unsigned int color,
    unsigned long rop );

int 
grPlot1 ( 
    struct gws_window_d *clipping_window,   
    int x, 
    int y, 
    int z, 
    unsigned int color,
    unsigned long rop,
    unsigned long flags );

//
// == Line ==============================================
//

void 
plotLine3d (
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned int color );

void 
plotLine3dEx (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned int color,
    unsigned long rop );

// plot line given two colors.
// interpolation?
void 
plotLine3d2 (
    int x0, int y0, int z0, unsigned long color1,
    int x1, int y1, int z1, unsigned long color2, int flag );
    
void 
plotQuadBezierSeg ( 
    int x0, int y0, int z0, 
    int x1, int y1, int z1,
    int x2, int y2, int z2, unsigned long color );

//
// == rectangle =======================================
//

void
rectangle_from_two_points (
    int left, int top, 
    int right, int bottom,
    unsigned int color );

void __rectangleZZ( struct gr_rectangle_d *rect );
int grRectangle( struct gr_rectangle_d *rect );

void
rectangle_ras3D (
    int left, int top, int z0,
    int right, int bottom, int z1,
    unsigned int color );


//
// == triangle ==========================
//

int xxxTriangleZ ( struct gr_triangle_d *triangle );
int grTriangle( struct gr_triangle_d *triangle);

//
// == polygon ===========================
//

int xxxPolygonZ(struct gr_polygon_d *polygon);

//
// == Cube ============================
//

int xxxInflateCubeZ ( struct gr_cube_d *cube, int value );
int xxxDeflateCubeZ ( struct gr_cube_d *cube, int value );
int xxxDrawCubeZ(struct gr_cube_d *cube);


//
// == Circle ===========================
//

void 
plotCircle(
    int xm, 
    int ym, 
    int r, 
    unsigned int color );

void 
plotCircleZ ( 
    int xm, 
    int ym, 
    int r, 
    unsigned int color, 
    int z );

//
// == Ellipse ====================================
//

void 
plotEllipseRect(
    int x0, 
    int y0, 
    int x1, 
    int y1, 
    unsigned long color );

void 
plotEllipseRectZ (
    int x0, int y0, 
    int x1, int y1, 
    unsigned long color,
    int z );

// Fibonacci Series using Recursion 
// #todo: Create fib_int and fib_long
int fib(int n);

//
// == Char ========================================
//

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

// interpolation
unsigned int 
interpolate_color(
    unsigned int color1, 
    unsigned int color2, 
    unsigned int fraction );

unsigned int invert_color(unsigned int color);

#endif    

