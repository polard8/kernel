/*
 * File: grprim.h 
 *     Header for primitives.
 * History:
 *     2020 - Created by Fred Nora.
 */

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



// 2D integer point.
struct gr_vec2D_d
{
    int x;
    int y;
    unsigned int color;
};

// 3D integer point.
struct gr_vec3D_d
{
    int x;
    int y;
    int z;
    unsigned int color;
};


// 2D float point.
// #todo: Maybe in the future.
struct gr_vecF2D_d
{
    float x;
    float y;
    unsigned int color;
};


// 3D float point.
struct gr_vecF3D_d
{
    float x;
    float y;
    float z;
    unsigned int color;
};

// ---------------------------------------

// 3D line
struct gr_line_d
{
    struct gr_vec3D_d p[2];
};

// 3D triangle
struct gr_triangle_d
{
    int used;
    int magic;
    int initialized;
    struct gr_vec3D_d p[3];
    // mesh support.
    struct gr_triangle_d *last;
    struct gr_triangle_d *next;
};

// float 3D triangle
struct gr_triangleF3D_d
{
    int used;
    int magic;
    int initialized;
    struct gr_vecF3D_d p[3];
    // mesh support.
    struct gr_triangleF3D_d *last;
    struct gr_triangleF3D_d *next;
};


// 3D rectangle.
struct gr_rectangle_d
{
    struct gr_vec3D_d p[4];
    // mesh support.
    struct gr_rectangle_d *last;
    struct gr_rectangle_d *next;
};

// 3D rectangle. float falues.
struct gr_rectangleF3D_d
{
    struct gr_vecF3D_d p[4];
    // mesh support.
    struct gr_rectangleF3D_d *last;
    struct gr_rectangleF3D_d *next;
};



// Cube
struct gr_cube_d
{
    struct gr_vec3D_d p[8];
};

// Polygon
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


// float
struct gr_mat4x4_d
{
    float m[4][4];  // = { 0 };
};


//
// == mesh =============================================
//

struct gr_mesh_point_d
{
// raw color
    unsigned int color;
// cada número representa um 
// índice num vetor de indices.
    int n[1];
};

struct gr_mesh_line_d
{
// raw color
    unsigned int color;
// cada número representa um 
// índice num vetor de indices.
    int n[2];
};

// tri mesh
struct gr_mesh_triangle_d
{
    int n;
    struct gr_triangle_d *first_triangle;
    struct gr_triangle_d *last_triangle;
};

// quad mesh
struct gr_mesh_rectangle_d
{
    int n;
    struct gr_rectangle_d *first_rectangle;
    struct gr_rectangle_d *last_rectangle;   
};

struct gr_mesh_d
{
// Quantos bytes tem a face list.
    int facelist_size_in_bytes;   // bytes
    int facelist_size_in_dwords;  // ints
// lista de indices.
// cada indice representa um vetor.
    void *facelist;
// Se o tipo for triangulo, então
// na facelist os indices serão agrupados de 3 em 3.
// Se for quad, então serão agrupados de 4 em 4.
// 1=TRIANGLE
// 2=QUAD
    int type;
// contando os triangulos na lista caso o mesh seja de quad.
    int tri_count;
// contando os quads na lista caso o mesh seja de quad.
    int quad_count; 
// quantos pontos no total.
// Cada indice vai usar 4 bytes da lista.
    int vertex_count;

// Navegation.
    //struct gr_mesh_d *last;
    struct gr_mesh_d *next;
};


struct gr_mesh_list_d
{
// number of elements in the linked list.
    int n;
    struct gr_mesh_d *first_mesh;
    struct gr_mesh_d *last_mesh;
};


// #define RAY_TYPE_LIGHT    1
// #define RAY_TYPE_??       2

#define RAY_ORIGIN  0
#define RAY_TARGET  1
// todo: aliases

// a vector with a starting point.
struct gr_ray_d
{
    int used;
    int magic;

// Type of ray.
// primary ray, reflection ray, shadow ray.

    int type;

    //int intensity;

    //int gradation;

    //int interpolation;

    // ...

// direction:
// The starting point is the source of light.
// #define RAY_ORIGIN  0
// #define RAY_TARGET  1
// 0 = origin. starting point
// 1 = direction. vector
    struct gr_vec3D_d p[2];

// Distance between 
// the starting point and the target.
    int distance;
};


//================================================

// The Perspective Calculation

// we can calculate the location of a 3D vertex in a 
// 2D viewing window with a multiplication and a division like this:
// x' = (x*near)/z
// y' = (y*near)/z
// x' = (x*near)/(-z)
// y' = (y*near)/(-z)


// array of chars.
struct gr_bitmap_d
{
    int type;
    
    unsigned long width;
    unsigned long height;

// 64 falgs.
    unsigned long flags;

    unsigned int color;

// Translation.
    int x;
    int y;
    int z;

// buffer
    char *body;
};

// struct gr_bitmap_d *bitmap_screen;
// ...



//
// ===========================================
//

// matrix

/*
static int projection4x4[4][4] = { 
        {1,0,0,0}, 
        {0,1,0,0},
        {0,0,0,0},
        {1,1,0,0}
        };
*/

// #ugly
void 
multiply4(
    int mat1[4][4], 
    int mat2[4][4], 
    int res[4][4] );

void 
gr_MultiplyMatrixVector(
    struct gr_vecF3D_d *i, 
    struct gr_vecF3D_d *o, 
    struct gr_mat4x4_d *m );



int 
gr_rotate_x(
    struct gr_triangleF3D_d *in_tri,
    struct gr_triangleF3D_d *out_tri,   // rotated 
    float angle, 
    float fElapsedTime );

int 
gr_rotate_y(
    struct gr_triangleF3D_d *in_tri,
    struct gr_triangleF3D_d *out_tri,   // rotated 
    float angle, 
    float fElapsedTime );

int 
gr_rotate_z(
    struct gr_triangleF3D_d *in_tri,
    struct gr_triangleF3D_d *out_tri,   // rotated 
    float angle, 
    float fElapsedTime );

//
// ===========================================================
//

int grInit(void);

//
// projection
//

//extern struct gr_mat4x4_d matProj;

// alternative.
int 
__transform_from_viewspace_to_screespace(
    int *res_x, int *res_y,
    int _x, int _y, int _z,
    int left_hand,
    int _hotspotx, int _hotspoty );


void 
gwsViewport(
    int topleft_x, 
    int topleft_y, 
    int width, 
    int height);

int 
gr_set_ray_info(
    struct gr_ray_d *r,
    struct gr_vec3D_d *origin,
    struct gr_vec3D_d *direction );

int gr_reset_ray_info(struct gr_ray_d *r);
struct gr_ray_d *ray_object(void);

void gr_dc_extents_init( struct dc_d *dc );
int gr_dc_refresh_screen( struct dc_d *dc );
int gr_dc_fill( struct dc_d *dc, unsigned int bg_color );

int 
gr_dc_plot0(
    struct dc_d *dc,
    int x,
    int y );

int 
grPlot2D ( 
    unsigned int color, 
    int x, 
    int y,
    unsigned long rop );

// Point. 
int 
grPlot0 ( 
    struct gws_window_d *clipping_window,   
    int z, int x, int y, 
    unsigned int color,
    unsigned long rop );

int 
grPlot1 ( 
    struct gws_window_d *clipping_window,   
    int x, int y, int z, 
    unsigned int color,
    unsigned long rop,
    unsigned long flags );

int serviceGrPlot0(void);

//
// == Line ==============================================
//

int 
plotLine3d (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned int color );

void 
plotLine3dEx (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned int color );

// plot line given two colors.
// interpolation ?
void 
plotLine3d2 (
    int x0, int y0, int z0, unsigned long color1,
    int x1, int y1, int z1, unsigned long color2, int flag );

int
plotLine3dLT2 (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1,
    int *x2, int *y2, int *z2, 
    int n,   // track this vector.
    unsigned int color,
    int draw );

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

void drawRectangleF(struct gr_rectangleF3D_d *rectangle);
void __rectangleZZ( struct gr_rectangle_d *rect );
int grRectangle( struct gr_rectangle_d *rect );

void
rectangle_ras3D (
    int left, int top, int z0,
    int right, int bottom, int z1,
    unsigned int color );

//sevice 2042
int serviceGrRectangle(void);

//
// == triangle ==========================
//

int 
grTriangle3(
    struct gws_window_d *window, 
    struct gr_triangle_d *triangle );

int grTriangle( struct gr_triangle_d *triangle);

int 
fillTriangle0(
    int x1, int y1,
    int x2, int y2,
    int x3, int y3, 
    unsigned int c);

int 
fillTriangle(
    struct gws_window_d *window, 
    struct gr_triangle_d *triangle,
    int hotspotx, int hotspoty );

int 
plotTriangleF(
    struct gws_window_d *window,
    struct gr_triangleF3D_d *t,
    int fill );

// Plot a single pixel.
int 
plotPixelF(
    struct gws_window_d *window,
    struct gr_vecF3D_d *vec );

//
// == polygon ===========================
//

int xxxPolygonZ ( struct gr_polygon_d *polygon );

//
// == Cube ============================
//

int xxxInflateCubeZ( struct gr_cube_d *cube, int value );
int xxxDeflateCubeZ( struct gr_cube_d *cube, int value );
int xxxDrawCubeZ( struct gr_cube_d *cube );
//sevice 2041
int serviceGrCubeZ(void);

//
// == Circle ===========================
//

// 2D
void 
plotCircle(
    int xm, 
    int ym, 
    int r, 
    unsigned int color );

// 3D
void 
grCircle3 ( 
    struct gws_window_d *window,
    int xm, 
    int ym, 
    int r, 
    unsigned int color, 
    int z );

//
// == Ellipse ====================================
//

// 2D
void 
grEllipse(
    int x0, 
    int y0, 
    int x1, 
    int y1, 
    unsigned int color );

// 3D
void 
grEllipse3 (
    int x0, int y0, 
    int x1, int y1, 
    unsigned int color,
    int z );

// Fred Nora's algo. 
// Prime stuff.
void noraDrawingStuff(void);
void noraDrawingStuff3(int x, int y, int z);

struct gr_vecF3D_d *grVectorCrossProduct(
    struct gr_vecF3D_d *v1, 
    struct gr_vecF3D_d *v2 );

float dot_productF( struct gr_vecF3D_d *v1, struct gr_vecF3D_d *v2 );
int dot_product( struct gr_vec3D_d *v1, struct gr_vec3D_d *v2 );

int gr_discriminant_int(int a, int b, int c);
float gr_discriminant(float a, float b, float c);

int gr_triangle_area_int (int base, int height);

int gr_magic_volume (int x, int y, int z);
int gr_magic_area (int x, int y, int z);

int 
gr_find_obj_height_int ( 
    int *obj_height, int obj_distance,
    int img_height, int img_distance );
int 
gr_find_img_height_int ( 
    int obj_height, int obj_distance,
    int *img_height, int img_distance );


// Fibonacci Series using Recursion 
// #todo: Create fib_int and fib_long
// This thing is very slow.
int fib(int n);

void gr_scale_vec( struct gr_vec3D_d *v, int scale );

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

// Pixel
int servicepixelBackBufferPutpixel (void);

// interpolation
unsigned int 
interpolate_color(
    unsigned int color1, 
    unsigned int color2, 
    unsigned int fraction );

unsigned int invert_color(unsigned int color);

#endif    

