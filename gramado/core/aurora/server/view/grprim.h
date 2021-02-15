/*
 * File: grprim.h 
 * 
 *     Header for primitives.
 * 
 * 
 * History:
 *     2020 - Created by Fred Nora.
 */



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


// Cube
struct gr_cube_d
{
    struct gr_vec3D_d p[8];
};


struct gr_polygon_d 
{
    // number of elements.
    int n;
    
    // List of vectors.
    void *list_address;
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



// Camera
struct gr_camera_d
{
    // position
    struct gr_vec3D_d position;
    struct gr_vec3D_d upview;
    struct gr_vec3D_d lookat;
    // ...
    
    
    struct gr_projection_d *projection;

    // Next node in the linked list.
    //struct gr_camera_d *next;
};

struct gr_camera_d *CurrentCamera;


// ??
// graphical projection perspective
// See:
// https://en.wikipedia.org/wiki/Perspective_(graphical)
struct gr_projection_d
{
    // perspective or orthographic
    int type;


    // fovy   Number The angle between the upper and lower sides of the viewing frustum.
    // aspect Number The aspect ratio of the viewing window. (width/height).
    
 
    // The frustrum:   
    // The rectangle that the can see.
    // The limits in z axis. zmin and zmax;
    
    struct gr_rectangle_d *frustrum_view;   // projection window.
    
    int zNear;   // Distance to the near clipping plane along the -Z axis.
    int zFar;    // Distance to the far clipping plane along the -Z axis.
    int zRange;  // zRange = zNear - zFar;


    // fov: field of view.
    int angle_of_view;
    

    // The apex.
    // mid_x = (left + right) * 0.5;
    // mid_y = (bottom + top)  * 0.5;
    struct gr_vec3D_d *frustrum_apex;



    // apsect ratio
    // ar = screen width / screen height
    // #bugbug: We are using int, not float.
    int ar;


    // talvez precisamos aqui uma matrix de transformaçao.
};

struct gr_projection_d *CurrentProjection;


// The Perspective Calculation

// we can calculate the location of a 3D vertex in a 
// 2D viewing window with a multiplication and a division like this:
// x' = (x*near)/z
// y' = (y*near)/z
// x' = (x*near)/(-z)
// y' = (y*near)/(-z)



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


// Camera
int camera_initialize(void);
int 
camera ( 
    int x, int y, int z,
    int xUp, int yUp, int zUp,
    int xLookAt, int yLookAt, int zLookAt );


int projection_initialize(void);


// chaging the view for the current projection
int view(int near, int far);


// Point.
int grPlot0 (int z, int x, int y, unsigned long color);


int serviceGrPlot0(void);


//
// == Line ==============================================
//

void 
plotLine3d (
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned long color );


// plot line given two colors.
// interpolation ?
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


void rectangleZZ( struct gr_rectangle_d *rect );

void
ras_rectangleZ (
    int left, int top, int z0,
    int right, int bottom, int z1,
    unsigned long color );


//sevice 2042
int serviceGrRectangle(void);




//
// == triangle =====================================================
//

int xxxTriangleZ ( struct gr_triandle_d *triangle );


//
// == polygon =====================================================
//

int xxxPolygonZ ( struct gr_polygon_d *polygon );



//
// == Cube ========================================================
//

int xxxInflateCubeZ ( struct gr_cube_d *cube, int value );
int xxxDeflateCubeZ ( struct gr_cube_d *cube, int value );
int xxxCubeZ ( struct gr_cube_d *cube );
//sevice 2041
int serviceGrCubeZ(void);




//
// == Circle =================================================
//

void plotCircle (int xm, int ym, int r, unsigned long color);
void 
plotCircleZ ( 
    int xm, 
    int ym, 
    int r, 
    unsigned long color, 
    int z );


//
// == Ellipse =================================================
//

void plotEllipseRect(int x0, int y0, int x1, int y1, unsigned long color);
void 
plotEllipseRectZ (
    int x0, int y0, 
    int x1, int y1, 
    unsigned long color,
    int z );



//
// Fred Nora's algo. Prime stuff;
//

void noraDrawingStuff(void);
void noraDrawingStuff3(int x, int y, int z);



// Fibonacci Series using Recursion 
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





