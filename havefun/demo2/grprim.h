/*
 * File: grprim.h 
 *     Header for primitives.
 * History:
 *     2020 - Created by Fred Nora.
 */


#ifndef __GRPRIM_H
#define __GRPRIM_H   1


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

/*
// 2D long point.
struct gr_vecL2D_d
{
    long x;
    long y;
    unsigned int color;
};
*/

/*
// 3D long point.
struct gr_vecL3D_d
{
    long x;
    long y;
    long z;
    unsigned int color;
};
*/

/*
// 2D float point.
// #todo: Maybe in the future.
struct gr_vecF2D_d
{
    float x;
    float y;
    unsigned int color;
};
*/

/*
// 3D float point.
// #todo: Maybe in the future.
struct gr_vecF3D_d
{
    float x;
    float y;
    float z;
    unsigned int color;
};
*/

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

// 3D representqation of the triangle.
    struct gr_vec3D_d p[3];
// 2D representation of the triangle
// Good for rasterization. Maybe for texture.
    struct gr_vec2D_d pt2D[3];

    // mesh support.
    struct gr_triangle_d *last;
    struct gr_triangle_d *next;
};

// 3D rectangle.
struct gr_rectangle_d
{

// 3D representation of the rectangle.
    struct gr_vec3D_d p[4];
// 2D representation of the rectangle.
// Good for rasterization. Maybe for texture.
    struct gr_vec2D_d pt2D[4];

    // mesh support.
    struct gr_rectangle_d *last;
    struct gr_rectangle_d *next;
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


//
// == mesh =============================================
//

struct gr_mesh_point_d
{
// raw color
    unsigned int color;
// Cada número representa um índice num array de vetores.
    int n[1];
};

struct gr_mesh_line_d
{
// raw color
    unsigned int color;
// Cada número representa um índice num array de vetores.
    int n[2];
};

// tri mesh
struct gr_mesh_triangle_d
{
// raw color
    unsigned int color;
// Cada número representa um índice num array de vetores.
    int n[3];
};

/*
struct gr_mesh_triangle_queue_d
{
    void *base;
// raw color
    unsigned int color;
// Cada número representa um índice num array de vetores.
    int n[3];
// navigation
    struct gr_mesh_triangle_queue_d *next;
    struct gr_mesh_triangle_queue_d *last;
};
*/


// quad mesh
struct gr_mesh_rectangle_d
{
// raw color
    unsigned int color;
// Cada número representa um índice num array de vetores.
    int n[4];
};

/*
struct gr_mesh_rectangle_queue_d
{
    void *base;
// raw color
    unsigned int color;
// Cada número representa um índice num array de vetores.
    int n[4];
// navigation
    struct gr_mesh_rectangle_queue_d *next;
    struct gr_mesh_rectangle_queue_d *last;
};
*/



struct gr_mesh_d
{
// Quantos bytes tem a face list.
    int facelist_size_in_bytes;   // bytes
    int facelist_size_in_dwords;  // ints


// lista de triangulos
    struct gr_mesh_triangle_d *tris;
// lista de retângulos.
    struct gr_mesh_rectangle_d *rects;


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


// ??
// graphical projection perspective
// See:
// https://en.wikipedia.org/wiki/Perspective_(graphical)
struct gr_projection_d
{
    int used;
    int magic;
    int initialized;

    // perspective or orthographic
    int type;

// fovy   Number The angle between the upper and lower 
// sides of the viewing frustum.
// aspect Number The aspect ratio of the viewing window. (width/height).
 
// The frustrum:   
// The rectangle that the can see.
// The limits in z axis. zmin and zmax;
// projection window.

    //struct gr_rectangle_d frustrum_view;

// orthographic projection plane
    int l;  //left
    int t;  //top
    int w;  //width
    int h;  //height

    int r;  //right
    int b;  //bottom


// Distance to the near clipping plane along the -Z axis.
    int zNear;
// Distance to the far clipping plane along the -Z axis.
// In other words, the larger the z, the further is the object. 
// After the flip, the coordinate system is no longer a 
    int zFar; 
// zRange = zNear - zFar;
    int zRange;

// ?
// fov: field of view.
    int angle_of_view;

// The apex.
// O pico.
    // mid_x = (left + right) * 0.5;
    // mid_y = (bottom + top)  * 0.5;
    struct gr_vec3D_d  frustrum_apex;

 // aspect ratio
    // ar = screen width / screen height
    // #bugbug: We are using int, not float.
    int ar;

    // matrix de transformaçao?

// ------------------
// viewport: 
// All the view port information is found 
// the local device context.

    struct dc_d *dc;
};

struct gr_projection_d  *CurrentProjection;


//================================================

// Camera
struct gr_camera_d
{
    int used;
    int magic;
    int initialized;

// EYE: Position of the camera.
    struct gr_vec3D_d position;
// UP: Orientation.
    struct gr_vec3D_d upview;
// AT: target point.
// The object distance.
// Consider znear and zfar. 
// This way we know the if the model 
// is becoming bigger or smaller.
    struct gr_vec3D_d lookat;

// ?
    struct gr_projection_d *projection;



// Next node in the linked list.
    // int id;
    // struct gr_camera_d *next;
};

struct gr_camera_d  *CurrentCamera;


struct gr_world_d
{
    int used;
    int magic;
    int initialized;

    int x_size;
    int y_size;
    int z_size;
    struct gr_vec3D_d center;

// ==========================
// horizon
    struct gr_vec3D_d h1;
    struct gr_vec3D_d h2;
// vanishing points
    struct gr_vec3D_d vp1;
    struct gr_vec3D_d vp2;
};

struct gr_world_d  *CurrentWorld;

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



int 
__transform_from_viewspace_to_screespace(
    int *res_x,
    int *res_y,
    int _x, int _y, int _z,
    int left_hand,
    int _hotspotx, int _hotspoty );

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

void grInitializematrix0 (long *r);

void 
grSetTranslation4x4 (
    long *r,   // matrix base.
    long *_x, long *_y, long *_z );
//#test
void 
grRot4x4 (
    long *r,   // matrix base.
    long *_x, long *_y, long *_z );

//
// ===========================================================
//


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



int grInit(void);


//
// projection
//

int projection_initialize(void);

int gr_depth_range(struct gr_projection_d *projection, int near, int far);
// Chaging the view for a given projection
int view (struct gr_projection_d *projection, int near, int far);

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



int world_initialize(void);

//
// Camera
//

int camera_initialize(void);

// three vectors:
// position vector, up vector and look at vector.
int 
camera ( 
    int x, int y, int z,
    int xUp, int yUp, int zUp,
    int xLookAt, int yLookAt, int zLookAt );


int unveil_world(void);

int 
unveil_camera(
    int model_x, int model_y, int model_z );



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

// Point. 
int 
grPlot0 (
    struct gws_window_d *clipping_window,   
    int z, int x, int y, 
    unsigned int color );

int 
grPlot1 ( 
    struct gws_window_d *clipping_window,   
    int x, 
    int y, 
    int z, 
    unsigned int color,
    unsigned long flags );

int serviceGrPlot0(void);


//
// == Line ==============================================
//

struct gr_vec2D_d *gr_cast2D (
    struct gr_vec2D_d *wp1, struct gr_vec2D_d *wp2,
    struct gr_vec2D_d *rp1, struct gr_vec2D_d *rp2 );


void
grLineRect4 ( 
    struct gws_window_d *window,
    int x1, int y1, 
    int x2, int y2,
    unsigned int color );

void 
plotLine3d (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned int color );

void 
plotLine3dLT (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1,
    int *x2, int *y2, int *z2, 
    unsigned int color );

// track a given vector.
// OUT: the number of vectors in this line.
int 
plotLine3dLT2 (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1,
    int *x2, int *y2, int *z2, 
    int n,   // track this vector.
    unsigned int color,
    int draw );

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


//sevice 2042
int serviceGrRectangle(void);



//
// == triangle ==========================
//

int grTriangleScale0( struct gr_triangle_d *t, int factor);

int 
xxxTriangleZ(
    struct gws_window_d *window, 
    struct gr_triangle_d *triangle );


int 
xxxFillTriangle0(
    struct gws_window_d *window, 
    struct gr_triangle_d *triangle );

// #test
int 
xxxTriangleZ1(
    struct gws_window_d *window, 
    struct gr_triangle_d *triangle );

int grTriangle( struct gr_triangle_d *triangle);

//
// == polygon ===========================
//

int xxxPolygonZ ( struct gr_polygon_d *polygon );


//
// == Cube ============================
//

int xxxInflateCubeZ ( struct gr_cube_d *cube, int value );
int xxxDeflateCubeZ ( struct gr_cube_d *cube, int value );

int xxxDrawCubeZ ( struct gr_cube_d *cube );

//sevice 2041
int serviceGrCubeZ(void);

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
    struct gws_window_d *window,
    int xm, 
    int ym, 
    int r, 
    unsigned int color, 
    int z );


int
plotCircleZLT0 ( 
    struct gws_window_d *window,
    int xm, 
    int ym, 
    int r, 
    unsigned int color, 
    int z,
    int axis_n,                           // qual eixo.
    int n,                                // number of the target pointer.
    int *res_x, int *res_y, int *res_z,   // return vector.
    int draw );                           // draw or not.  


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


// Fred Nora's algo. 
// Prime stuff.
void noraDrawingStuff(void);
void noraDrawingStuff3(int x, int y, int z);


int scalar_product( struct gr_vec3D_d *v1, struct gr_vec3D_d *v2 );

int gr_discriminant_int(int a, int b, int c);


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





