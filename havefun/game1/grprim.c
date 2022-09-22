/*
 * File: grprim.c 
 *     Primitives.
 * History:
 *     2020 - Created by Fred Nora.
 */

#include "gws.h"



// See:
// https://wiki.osdev.org/3D_Renderer_Basics
// http://members.chello.at/easyfilter/bresenham.html
// http://math.hws.edu/graphicsbook/c2/s3.html
// http://math.hws.edu/graphicsbook/index.html
// ...

// ================================
// Viewport 2d:
// A origem normalmente fica em top/left.
// É o 'raster', para fazer rasterização.
// Viewport is a rectangular display area 
// on the application window, which is measured 
// in screen's coordinates 
// (in pixels, with origin at the top-left corner). A viewport defines the size and shape of the display area to map the projected scene captured by the camera onto the application window. 
// It may or may not occupy the entire screen.
// Viewport 3d:
// Então o viewpoint agora possui 3 coordenadas.
// In 3D graphics, a viewport is 3-dimensional 
// to support z-ordering, which is needed for 
// situations such as ordering of overlapping windows.
// Object world:
// O objeto tem seu proprio mundo e a origem fica 
// no centro da tela.
// Each object (or model or avatar) in a 3D scene 
// is typically drawn in its own coordinate system, 
// known as its model space (or local space, or object space). 
// See: https://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_BasicsTheory.html
// =============================


// #todo
// Create some configuration globals here
// int gUseSomething = TRUE;
// int gUseRaytracing = TRUE;
// ...


// ====
/*
 * Transformations: 
 *     Ex: Scaling, translation and rotation ...
 * 
 */

// translation
// x1 = x + e
// y1 = y + f
// translate( e, f )

// Scaling
// inflate, deflate.
// x1 = a * x
// y1 = d * y

// affine transform
// x1 = a*x + b*y + e
// y1 = c*x + d*y + f
// T(x,y) = ( a*x + b*y + e, c*x + d*y + f )

// Rotation
//x1 = cos(r) * x - sin(r) * y
//y1 = sin(r) * x + cos(r) * y

// shearing transform.
// tosquear, podar.
//x1 = x + b * y
//y1 = y
//---------
//x1 = x
//y1 = c * x + y


//Combining Transformations
//translate(4,0)
//rotate(90)

//Window-to-Viewport
//scale( width / (right-left), height / (bottom-top) );
//translate( -left, -top )
//-------
//x1 = width / (right-left) * (x-left)
//y1 = height / (bottom-top) * (y-top)


// =============================================================
// #projection:
// For orthographics projection there is no scaling factor.
// For perspective, we do have scaling.

// Camera and Perspective 
// camera:
// location, pointing at, pointing to top.
// .., lookat(view vector), top (upvector).
// perspective:
// view frustrum
// near, far ...
// from, to


// Device hotspot.
static unsigned long HotSpotX=0;
static unsigned long HotSpotY=0;

// Window hotspot.
//static unsigned long WindowHotSpotX=0;
//static unsigned long WindowHotSpotY=0;


static int 
__transform_from_viewspace_to_screespace(
    int *res_x,
    int *res_y,
    int _x, int _y, int _z,
    int left_hand,
    int _hotspotx, int _hotspoty );
    
// =============================

/*
 * grInit:
 *     Initialize the 3d support.
 *     Create the hotspot to normalize the screen.
 *     The device context was created in the beginning of
 * of the initialization.
 *     To handle the device context we have the structures:
 * 'display' and 'screen'. The clients will use the data in these
 *  structures.
 */

int grInit (void)
{
    unsigned long deviceWidth  = gws_get_device_width();
    unsigned long deviceHeight = gws_get_device_height();

    gwssrv_debug_print ("grInit:\n");

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        gwssrv_debug_print ("grInit: [FAIL] w h\n");
        printf             ("grInit: [FAIL] w h\n");
        exit(1);
    }

// center of the screen.
// #todo: 
// We need the option to put the hotspot 
// at the center of the window.
    
    HotSpotX = (deviceWidth>>1);
    HotSpotY = (deviceHeight>>1);



// == Projection =========
// Initialize the current projection.
// Change the view for the current projection.

    gwssrv_debug_print ("grInit: projection\n");
    projection_initialize();
    // Changing the view for the current projection.
    gr_depth_range(CurrentProjection,0,40);


// == world
    world_initialize();

// == Camera ==========
// Initialize the current camera.
// Change some attributes for the current camera.
// The projection is a field in the camera's structure.

    gwssrv_debug_print ("grInit: camera\n");
    camera_initialize();
    
    //camera ( 
    //    -40, -40, 0,     // position vector
    //    -40,  40, 0,     // upview vector
    //     10,  10, 10 );  // lookat vector

    camera ( 
        0, 0, 0,     // position vector
        0, 0, 0,     // upview vector
        0, 0, 0 );   // lookat vector

    // ...

    gwssrv_debug_print ("grInit: done\n");
    return 0;
}


int world_initialize(void)
{
    CurrentWorld = 
        (void *) malloc( sizeof( struct gr_world_d ) );

    if ( (void*) CurrentWorld == NULL ){
        printf("world_initialize: fail\n");
        exit(1);
    }

    CurrentWorld->center.x = (unsigned int) 0;
    CurrentWorld->center.y = (unsigned int) 0;
    CurrentWorld->center.z = (unsigned int) 0;
    CurrentWorld->center.color = COLOR_BLACK;

    CurrentWorld->x_size = (unsigned int) 200;
    CurrentWorld->y_size = (unsigned int) 200;
    CurrentWorld->z_size = (unsigned int) 200;

    CurrentWorld->used = TRUE;
    CurrentWorld->magic = 1234;
    CurrentWorld->initialized = TRUE;

    return 0;
}

int camera_initialize(void)
{
    CurrentCamera = 
        (void *) malloc( sizeof( struct gr_camera_d ) );

    if ( (void*) CurrentCamera == NULL ){
        printf("camera_initialize: fail\n");
        exit(1);
    }
    
    CurrentCamera->initialized = FALSE;

    CurrentCamera->used = TRUE;
    CurrentCamera->magic = 1234;

    // position
    CurrentCamera->position.x = 0;
    CurrentCamera->position.y = 0;
    CurrentCamera->position.z = 0;

    // upview
    CurrentCamera->upview.x = 0;
    CurrentCamera->upview.y = 0;
    CurrentCamera->upview.z = 0;

    // lookat. target point origin.
    CurrentCamera->lookat.x = 0;
    CurrentCamera->lookat.y = 0;
    CurrentCamera->lookat.z = 0;
    
    if( (void*) CurrentProjection != NULL )
    {
        if (CurrentProjection->initialized == TRUE){
            CurrentCamera->projection = 
                (struct gr_projection_d *) CurrentProjection;
        }
    }

    CurrentCamera->initialized = TRUE;

    return 0;
}


// #test
// line-line intersaction point.
// IN: Wall point 1, wall point 2, ray point1, ray point 2
// OUT: pointer or NULL.
struct gr_vec2D_d *gr_cast2D (
    struct gr_vec2D_d *wp1, struct gr_vec2D_d *wp2,
    struct gr_vec2D_d *rp1, struct gr_vec2D_d *rp2 )
{

// check pointers
    if( (void*) wp1 == NULL )
        return NULL;
    if( (void*) wp2 == NULL )
        return NULL;
    if( (void*) rp1 == NULL )
        return NULL;
    if( (void*) rp2 == NULL )
        return NULL;


// Building the wall.
// Pega os pontos do wall.
    int wx1 = (int) wp1->x;
    int wy1 = (int) wp1->y;
    int wx2 = (int) wp2->x;
    int wy2 = (int) wp2->y;

// check pointer
    //if( (void*) CurrentCamera == NULL )
    //    return NULL;

// Buiding the ray.
// Position and direction from camera structure.
    int rx3 = (int) rp1->x;
    int ry3 = (int) rp1->y;
    int rx4 = (int) rp1->x + rp2->x;
    int ry4 = (int) rp1->y + rp2->y;

// the denominator
// Can't be '0'. :)
    int den = (int) (wx1 - wx2) * (ry3 - ry4) - (wy1 - wy2) * (rx3 - rx4);
    if (den == 0){
      return NULL;   // No point.
    }

    int t = (int)  ((wx1 - rx3) * (ry3 - ry4) - (wy1 - ry3) * (rx3 - rx4)) / den;
    int u = (int) -((wx1 - wx2) * (wy1 - ry3) - (wy1 - wy2) * (wx1 - rx3)) / den;

// Not a pointer.
    struct gr_vec2D_d magic_pointer; 

    if ( t > 0 && 
         t < 1 && 
         u > 0 ){
        //const pt = createVector();
      magic_pointer.x = (int) wx1 + t * (wx2 - wx1);
      magic_pointer.y = (int) wy1 + t * (wy2 - wy1);
      
      //printf("ok\n");
      return (struct gr_vec2D_d *) &magic_pointer;

    } else {
      return NULL;
    };
}


int 
camera ( 
    int x, int y, int z,
    int xUp, int yUp, int zUp,
    int xLookAt, int yLookAt, int zLookAt )
{
        
    if ( (void*) CurrentCamera == NULL ){
        return -1;
    }
    if (CurrentCamera->magic != 1234){
        return -1;
    }

// ----------------
// EYE:
// position
    CurrentCamera->position.x = x;
    CurrentCamera->position.y = y;
    CurrentCamera->position.z = z;

// ----------------
// UP:
// upview
    CurrentCamera->upview.x = xUp;
    CurrentCamera->upview.y = yUp;
    CurrentCamera->upview.z = zUp;

// ----------------
// AT:
// lookat. target point origin.
    CurrentCamera->lookat.x = xLookAt;
    CurrentCamera->lookat.y = yLookAt;
    CurrentCamera->lookat.z = zLookAt;

    return 0;
}


int unveil_world(void)
{
    // object window
    struct gws_window_d *ow;
    ow = NULL;
    //#todo
    // use the demo window if it is possible
    if( (void*) __demo_window != NULL ){
       if(__demo_window->magic==1234)
        ow = __demo_window;
    }


    if ( (void*) CurrentWorld == NULL )
        return -1;
    if(CurrentWorld->magic != 1234)
        return -1;
    if(CurrentWorld->initialized!=TRUE)
        return -1;

// --------------------------------
// #test:
// The horizon.
// The camera is a vanishing point in this line.
    CurrentWorld->h1.x = CurrentWorld->center.x;
    CurrentWorld->h1.y = CurrentWorld->center.y + CurrentWorld->z_size;
    CurrentWorld->h1.z = CurrentWorld->center.z;
    CurrentWorld->h2.x = CurrentWorld->center.x + (CurrentWorld->x_size << 1);
    CurrentWorld->h2.y = CurrentWorld->center.y + CurrentWorld->z_size;
    CurrentWorld->h2.z = CurrentWorld->center.z;
    plotLine3d ( 
        ow,
        CurrentWorld->h1.x,  CurrentWorld->h1.y, CurrentWorld->h1.z, 
        CurrentWorld->h2.x,  CurrentWorld->h2.y, CurrentWorld->h2.z, 
        COLOR_PURPLE ); 
// --------------------------------
// vanishing point
    CurrentWorld->vp1.x = (CurrentWorld->h1.x + CurrentWorld->h2.x)/2;
    CurrentWorld->vp1.y = (CurrentWorld->h1.y + CurrentWorld->h2.y)/2;
    CurrentWorld->vp1.z = CurrentWorld->h1.z;
    plotCircleZ ( 
        ow,
        CurrentWorld->vp1.x,    //x
        CurrentWorld->vp1.y,    //y
        4,        //r
        COLOR_PURPLE,  //color 
        CurrentWorld->vp1.z );   // z 


// ==========================
// Draw the 3 axis
// Draw line
    //int off=100;
    // y
    plotLine3d ( 
        ow,
        CurrentWorld->center.x,  
        CurrentWorld->center.y - CurrentWorld->y_size,
        CurrentWorld->center.z, 
        CurrentWorld->center.x,
        CurrentWorld->center.y + CurrentWorld->y_size, 
        CurrentWorld->center.z,
        COLOR_RED ); 
    // x
    plotLine3d ( 
        ow,
        CurrentWorld->center.x - CurrentWorld->x_size,
        CurrentWorld->center.y,
        CurrentWorld->center.z, 
        CurrentWorld->center.x + CurrentWorld->x_size,  
        CurrentWorld->center.y,  
        CurrentWorld->center.z,
        COLOR_GREEN ); 
    // z
    plotLine3d ( 
        ow,
        CurrentWorld->center.x + CurrentWorld->z_size,
        CurrentWorld->center.y + CurrentWorld->z_size,
        CurrentWorld->center.z, 
        CurrentWorld->center.x - CurrentWorld->z_size,  
        CurrentWorld->center.y - CurrentWorld->z_size,
        CurrentWorld->center.z, 
        COLOR_BLUE ); 

    return 0;
}


int 
unveil_camera(
    int model_x, int model_y, int model_z )
{

    // object window
    struct gws_window_d *ow;
    ow = NULL;
    //#todo
    // use the demo window if it is possible
    if( (void*) __demo_window != NULL ){
       if(__demo_window->magic==1234)
        ow = __demo_window;
    }


    struct gr_ray_d r;

    r.used = TRUE;
    r.magic = 1234;

// origin
// reset
    r.p[RAY_ORIGIN].x = 0;
    r.p[RAY_ORIGIN].y = 0;
    r.p[RAY_ORIGIN].z = 0;
    r.p[RAY_ORIGIN].color = COLOR_WHITE;

// --------------------------------
// where is our camera?
    if( (void*) CurrentCamera == NULL ){
        return -1;
    }
    if (CurrentCamera->magic != 1234){
        return -1;
    }
    if(CurrentCamera->initialized != TRUE){
        return -1;
    }

//
// Ray
//

// --------------------------------
//ray: 0.0.0 ---> banco

// --------------------------------
// change the look at vector.
    CurrentCamera->lookat.x = model_x;
    CurrentCamera->lookat.y = model_y;
    CurrentCamera->lookat.z = model_z;


// --------------------------------
// draw the camera (circle)
    // camera circle
    plotCircleZ ( 
        ow,
        CurrentCamera->position.x,  //x
        CurrentCamera->position.y,  //y
        8,        //r
        COLOR_RED,  //color 
        0 );   // z 
    //upview. (small circle).
    plotCircleZ ( 
        ow,
        CurrentCamera->upview.x,    //x
        CurrentCamera->upview.y,  //y
        4,        //r
        COLOR_RED,  //color 
        0 );   // z 

// ---------------
// origin
// The position of the camera.
    r.p[RAY_ORIGIN].x = (int) CurrentCamera->position.x;
    r.p[RAY_ORIGIN].y = (int) CurrentCamera->position.y;
    r.p[RAY_ORIGIN].z = (int) CurrentCamera->position.z;
    r.p[RAY_ORIGIN].color = COLOR_WHITE;

// ==========================
// Draw the 3 axis
// Draw line (canonical in Gramado)
    int off=20;
    // y
    plotLine3d ( 
        ow,
        r.p[0].x,  r.p[0].y,        r.p[0].z, 
        r.p[0].x,  r.p[0].y + off,  r.p[0].z, 
        COLOR_RED ); 
    // x
    plotLine3d ( 
        ow,
        r.p[0].x,       r.p[0].y, r.p[0].z, 
        r.p[0].x + off, r.p[0].y, r.p[0].z, 
        COLOR_GREEN ); 
    // z
    plotLine3d ( 
        ow,
        r.p[0].x,       r.p[0].y,       r.p[0].z, 
        r.p[0].x -off,  r.p[0].y -off,  r.p[0].z, 
        COLOR_BLUE ); 

// ---------------
// look at vector
// target
    r.p[RAY_TARGET].x = (int) CurrentCamera->lookat.x; 
    r.p[RAY_TARGET].y = (int) CurrentCamera->lookat.y; 
    r.p[RAY_TARGET].z = (int) CurrentCamera->lookat.z;
    r.p[RAY_TARGET].color = COLOR_WHITE;


// Draw line (ray)
// The target is the model.

    plotLine3d ( 
        ow,
        r.p[RAY_ORIGIN].x,  r.p[RAY_ORIGIN].y, r.p[RAY_ORIGIN].z, 
        r.p[RAY_TARGET].x,  r.p[RAY_TARGET].y, r.p[RAY_TARGET].z, 
        r.p[0].color ); 


    return 0;
}

// ------------

int 
gr_set_ray_info(
    struct gr_ray_d *r,
    struct gr_vec3D_d *origin,
    struct gr_vec3D_d *direction )
{

    if( (void*) r == NULL )
        return -1;
    if (r->magic != 1234)
        return -1;

    if( (void*) origin == NULL )
        return -1;
    if( (void*) direction == NULL )
        return -1;


// origin
    r->p[0].x = (int) origin->x;
    r->p[0].y = (int) origin->y;
    r->p[0].z = (int) origin->z;

// direction
    r->p[1].x = (int) direction->x;
    r->p[1].y = (int) direction->y;
    r->p[1].z = (int) direction->z;

// ok
    return 0;
}


int gr_reset_ray_info(struct gr_ray_d *r)
{
    if( (void*) r == NULL )
        return -1;
    if (r->magic != 1234)
        return -1;

    r->type = 0;

// origin
    r->p[0].x = 0;  r->p[0].y = 0;  r->p[0].z = 0;
// direction
    r->p[1].x = 0;  r->p[1].y = 0;  r->p[1].z = 0;

    r->distance = 0;

    r->used = TRUE;
    r->magic = 1234;

// ok
    return 0;
}


struct gr_ray_d *ray_object(void)
{
    struct gr_ray_d *tmp;
    
    tmp = (struct gr_ray_d *) malloc( sizeof(struct gr_ray_d) );
    if ( (void*) tmp == NULL )
        return NULL;
    tmp->used = TRUE;
    tmp->magic = 1234;

    //if(reset)
    //gr_reset_ray_info(tmp);

    return (struct gr_ray_d *) tmp;
}


// d<0: (negative) "Raiz de número negativo em Baskara"
// d=0: (null)     duas raizes reais iguais.
// d>0: (positive) duas raizes reais diferentes.
int gr_discriminant_int(int a, int b, int c)
{
    int d = (int) ((b*b) - (4*a*c));
    return (int) d;
}


/*
float gr_discriminant(float a, float b, float c);
float gr_discriminant(float a, float b, float c)
{
    float d = (float) ((b*b) - (4*a*c));
    return (float) d;
}
*/

// See:
int projection_initialize(void)
{

// See: 
// gr_projection_d

    CurrentProjection = 
        (void *) malloc ( sizeof( struct gr_projection_d ) );
    
    if ( (void*) CurrentProjection == NULL )
    {
        printf("projection_initialize: CurrentProjection\n");
        exit(1);
    }

    if( (void*) gr_dc == NULL)
    {
        printf("projection_initialize: gr_dc\n");
        exit(1);
    }
    
    if (gr_dc->initialized != TRUE)
    {
        printf("projection_initialize: gr_dc->initialized\n");
        exit(1);
    }

    // Use the default dc.
    CurrentProjection->dc = gr_dc;


    CurrentProjection->initialized = FALSE;

    // #todo: Perspective or orthogonal
    CurrentProjection->type = 1; 

//
// Orthographic projection plane
//

// #importante:
// Podemos alterar as informações do plano de projeção
// mas o plano obtido pelas características do dispositivo
// são dependentes do dispositivos.
// Do mesmo modo que podemos ter uma tela virtual.

    CurrentProjection->l = gr_dc->left;
    CurrentProjection->t = gr_dc->top;
    CurrentProjection->w = gr_dc->width;
    CurrentProjection->h = gr_dc->height;

    CurrentProjection->r = gr_dc->right;
    CurrentProjection->b = gr_dc->bottom;

// z range.
    CurrentProjection->zNear  = gr_dc->znear;
    CurrentProjection->zFar   = gr_dc->zfar;
    CurrentProjection->zRange = gr_dc->zrange;



    //CurrentProjection->angle_of_view = ?;
    //CurrentProjection->ar = ?;
    //CurrentProjection->frustrum_apex = ?;
    //CurrentProjection->frustrum_view = ?;

    //...
    
    CurrentProjection->used = TRUE;
    CurrentProjection->magic = 1234;

    CurrentProjection->initialized = TRUE;
 
    return 0;
}

int 
gr_depth_range(
    struct gr_projection_d *projection, 
    int near, 
    int far)
{
    return (int) view(projection,near,far);
}

// Changing the view for a given projection.
int view (struct gr_projection_d *projection, int near, int far)
{

    if ( (void*) projection == NULL ){
        printf("view: projection\n");
        return -1;
    }

    if (projection->initialized != TRUE){
        printf("view: initialized\n");
        return -1;
    }

    CurrentProjection->zNear  = (int) near;
    CurrentProjection->zFar   = (int) far;
    CurrentProjection->zRange = 
         (int) (CurrentProjection->zFar - CurrentProjection->zNear);

    return 0;
}



/*
// #bugbug
// Not tested.
// negative numbers ??
// #todo: inclue libc file.
void 
gr_clamp( 
    struct gr_vec3D_d *vect, 
    int min_value, 
    int max_value);
void 
gr_clamp( 
    struct gr_vec3D_d *vect, 
    int min_value, 
    int max_value)
{
    if ( (void*) vect == NULL ){
        return;
    }

    vect->x = max(min_value, vect->x);
    vect->y = max(min_value, vect->y);
    vect->z = max(min_value, vect->z);
        
    vect->x = min(max_value, vect->x);
    vect->y = min(max_value, vect->y);
    vect->z = min(max_value, vect->z);
}
*/


// Configurando o viewport.
// Isso determina os limites onde podemos
// pintar com 2d. Esse é nosso 'raster'.
// See: projection_initialize
void 
gwsViewport(
    int topleft_x, 
    int topleft_y, 
    int width, 
    int height)
{
    // Esses valores não podem ser maiores
    // que os valores da tela.
    
    if (topleft_x<0)
        topleft_x=0;
    if(topleft_y<0)
        topleft_y=0;

    if (width<0)
        width=0;
    if(height<0)
        width=0;

    // ...
    
    // #todo
    // call that routine.
    //projection_initialize(...)
}



// Limites da profundidade usada pelo raster.
// See: view().
void 
gwsDepthRange(
    int minZ,     // near
    int maxZ)     // far
{
// Changing the view for the current projection
    gr_depth_range(CurrentProjection,minZ,maxZ);
}


// Transforme from the (x,y,z) coordinates of the 'view space'
// to the (x,y) coordinates of the 2d screen space.
// Hand-made. No projection matrix.
// Using the left-hand style. The same found in Direct3D.
// Not normalized screen.
// Called by grPlot0().
// (This is a not standard method).
// (0,0) represents the top/left corner in a 2D screen.
// The center of the screen in 2D is the hotspot.
// (0,0,0) represents the center of the screen in 3D viewspace
// (0,0,0) in 3D is also the hotspot.
// OUT: 
// Return the 2D screen coordinates in res_x and res_y.

static int 
__transform_from_viewspace_to_screespace(
    int *res_x,
    int *res_y,
    int _x, int _y, int _z,
    int left_hand,
    int _hotspotx, int _hotspoty )
{

// 3d
// save parameters. (++)
    int x  = (int) _x;  //1
    int y  = (int) _y;  //2
    //int x2 = (int) _y;  //3 #crazy
    int z  = (int) _z;  //4

// The given hotspot.
// The center os our surface.
    int hotspotx = (int) (_hotspotx & 0xFFFFFFFF);
    int hotspoty = (int) (_hotspoty & 0xFFFFFFFF);

// 2d:
// final result.
    int X=0;
    int Y=0;

    // Register z value into the z buffer.
    //int RegisterZValue=FALSE;

// The world space.
// (HotSpotX,HotSpotY,0)
// This is the origin of the 'world space'.
// model space.
// Been the reference for all the 'object spaces'.


// ===================================================
// X::

// --------------------
// z maior ou igual a zero.
//    |
//    ----
//
    if (z >= 0)
    {
        // x positivo, para direita.
        if (x >= 0 ){
            X = (int) ( hotspotx + x );
        }
        // x negativo, para esquerda.
        if (x < 0 ){ x = abs(x);   
            X = (int) ( hotspotx - x );
        }
        goto done;
    }

// --------------------
// z negativo
//  _
//   |
//
    if (z < 0)
    {
        // x positivo, para direita.
        if (x >= 0){
            X = (int) (hotspotx + x);
        }
        // x negativo, para esquerda.
        if (x < 0){  x = abs(x); 
            X = (int) (hotspotx - x);
        }
        goto done;
    }

done:

// ===================================================
// Y::
     // y positivo, para cima.
     if ( y >= 0 ){
         Y = (int) ( hotspoty - y );
     }
     // y negativo, para baixo
     if ( y < 0 ){ y = abs(y);
         Y = (int) ( hotspoty + y );
     }

// ===================================================
// Z::
// Posição canônica do eixo z.
// Usado para projeção em 2D depois de feita
// as transformações.

    // LEFT-HAND
    if (left_hand == TRUE)
    {
        // z é positivo para todos os casos 
        // onde z é maior igual a 0.
        if(z >= 0)
        { 
            X = (X + z);  //para direita
            Y = (Y - z);  //para cima
        }
        // z é módulo para todos os casos 
        // em que z é menor que 0.
        if(z < 0){ z = abs(z);
            X = (X - z);   // para esquerda
            Y = (Y + z);   // para baixo
        }
    }

    // RIGHT-HAND
    if (left_hand != TRUE)
    {
        // z é positivo para todos os casos 
        // onde z é maior igual a 0.
        if(z >= 0)
        { 
            X = (X - z);  //para esquerda
            Y = (Y + z);  //para baixo
        }
        // z é módulo para todos os casos 
        // em que z é menor que 0.
        if(z < 0){ z = abs(z);
            X = (X + z);   // para esquerda
            Y = (Y - z);   // para baixo
        }
    }



// ===================================================
// Return values:

    // fail
    if ( (void*) res_x == NULL ){ return (int) -1; }
    if ( (void*) res_y == NULL ){ return (int) -1; }

    *res_x = (int) X;
    *res_y = (int) Y;

    // ok
    return 0;
}


void gr_dc_extents_init( struct dc_d *dc )
{
    if ( (void*) dc == NULL )
        return;
    if (dc->magic != 1234)
        return;

    //dc->flags |= DCF_RECORD_EXTENTS;

    dc->min_x = ULONG_MIN;
    dc->max_x = ULONG_MAX;
    dc->min_y = ULONG_MIN;
    dc->max_y = ULONG_MAX;
}


int gr_dc_refresh_screen( struct dc_d *dc )
{

    if ( (void*) dc != NULL )
    {
        if (dc->magic == 1234)
        {
            if( dc->initialized == TRUE )
            {
                gws_refresh_rectangle(
                    dc->left, 
                    dc->top, 
                    dc->width, 
                    dc->height );

                return 0;
            }
        }
    }

    return -1;
}


int gr_dc_fill( struct dc_d *dc, unsigned int bg_color )
{
    if ( (void*) dc == NULL )
        return -1;
    if (dc->magic != 1234)
        return -1;

    dc->bg_color = (unsigned int) bg_color;

    rectBackbufferDrawRectangle ( 
        dc->left, 
        dc->top, 
        dc->width,
        dc->height, 
        dc->bg_color, 
        TRUE,           // fill
        dc->rop );

    return 0;
}


// plot point
// 2d
// not tested!
int 
gr_dc_plot0(
    struct dc_d *dc,
    int x,
    int y )
{
// Print a pixel with the color in the given dc.
// No clipping window.
    if ( (void*) dc == NULL )
        return -1;
    if (dc->magic != 1234)
        return -1;
    if (dc->initialized != TRUE)
        return -1;


    if (x<0)
        return -1;

    if (y<0)
        return -1;

    unsigned long color = dc->color;
    unsigned long finalx = (unsigned long) (x & 0xFFFFFFFF);
    unsigned long finaly = (unsigned long) (y & 0xFFFFFFFF);
    unsigned long rop = dc->rop;

    finalx += dc->left;
    finaly += dc->top;

    grBackBufferPutpixel(
        (unsigned int) color, 
        finalx, 
        finaly, 
        (unsigned long) rop );

    return 0;
}


/*
 ******************************* 
 * grPlot0:
 *      plot pixel.
 *      Viewport Transformation.
 * 
 *      Low level routine.
 *      Origin at center of the device screen. 
 *      #todo: Plot into a 'normalized' 2d rater screen. 
 *      #new: Plotting into a clipping window.
 * low level plot.
 * History:
 *      2020 - Created by Fred Nora.
 */

// Ortographic view volume.

// Transformation:
// Estamos tranformando de um 'object space' com origem 
// no centro da tela para um viewport que ocupa a tela toda, 
// com origem no canto superior esquerdo.

// left hand orientation
// z+ on top/right corner.
// We use:
// Left-hand System (LHS) 
// LHS is clockwise (CW).
// Same as Microsoft Direct3D.
// See: https://en.wikipedia.org/wiki/Direct3D

// window ?
// Essa rotina pode pintar em qualquer posição 
// da tela do dispositivo. 
// Com origem no centro da tela.

// Aceitamos valores negativos e positivos.
// O limite máximo será modular.

// 3D fullscreen, origin in center.
// ==================================================
//
// O 'object space' esta no centro da tela. (0,0,0). 
// Essa rotina plota o pixel considerando o viewport com 
// a origem no canto superior esquerdo da tela. (0,0).
// Cada objeto pode ter seu proprio 'object space'
// e o 'world' pode ter seu 'world space' no centro do
// viewport.
// Por enquanto tanto o 'object space' quanto o 'world space'
// estão no centro da tela, em (0,0,0), e o viewport
// é o proprio raster que compreende a tela toda.

// Screen Coordinate System - 
// This 2D coordinate system refers to the physical coordinates 
// of the pixels on the computer screen, based on 
// current screen resolution. ( E.g. 1024x768 )
// Viewport Coordinate System - This coordinate system refers 
// to a subset of the screen space where the model window 
// is to be displayed. Typically the viewport will occupy 
// the entire screen window, or even the entire screen, 
// but it is also possible to set up multiple smaller viewports 
// within a single screen window.
// See:
// https://www.cs.uic.edu/~jbell/CourseNotes/ComputerGraphics/Coordinates.html
//


// #important
// The main goal here is transforming
// the ortographic view volume into
// a canonical view volume, without 
// using matrices operations.
// See: https://www.youtube.com/watch?v=U0_ONQQ5ZNM


// #todo
// Qual dc estamos usando.
// Se os argumentos não indicarem um, então devemos usar
// o dc default.

// #todo
// Devemos interagir com as rotinas de janela
// e transformarmos tudo em uma coisa só.
// E as rotinas de janela são rotinas 2d,
// mas pode levar em conta apenas o dc padrão
// ou outro destinado a pintar em lugares especificos.

// #bugbug
// Não sei se essa coisa da transformação está certa,
// mas é divertido.
// O z-buffer no dc ou na janela vai nos ajudar a decidirmos
// se devemos ou não pintar o pixel, para economizarmos pixels.


// #
// Not standard ortographic projection.
// Once the camera is positioned and oriented, 
// we need to decide what it can see 
// (analogous to choosing the camera's field of view 
// by adjusting the focus length and zoom factor), and 
// how the objects are projected onto the screen. 
// This is done by selecting a projection mode 
// (perspective or orthographic) and specifying a 
// viewing volume or clipping volume. 
// Objects outside the clipping volume are clipped out 
// of the scene and cannot be seen.
// see:
// https://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_BasicsTheory.html

// IN:
// clipping window near: Near window.
// clipping window far: Far window.
// x,y,z
// color

int 
grPlot0 ( 
    struct gws_window_d *clipping_window,   
    int z, int x, int y, 
    unsigned int color )
{
// Viewport Transform: (mapping)
// depth buffer?
// In 3D graphics, a viewport is 3-dimensional 
// to support z-ordering, which is needed for 
// situations such as ordering of overlapping windows.
// #todo
// We can use a 'clipping window' and draw only inside this window.
// If the clipping window is NULL, so we need to use the root window.
// #todo
// This is a work in progress

    // Final 2D screen coordenates.
    int X=0;
    int Y=0;

    // Draw flag.
    int Draw = TRUE;

    int UsingDepthBuffer = FALSE;
    int UsingAlphaBlending = FALSE;

// clipping window support.
    struct gws_window_d *w;
    int UseClipping = FALSE;


// #todo
// We can set this in the global configuration.
// see: globals.c
    int UseLeftHand = gUseLeftHand;
    //#test
    //UseLeftHand = TRUE; // left
    //UseLeftHand = FALSE;  //right

//
// Device screen structure
//

// See: screen.h

    // #debug
    if ( (void *) DeviceScreen == NULL )
    {
        Draw = FALSE;
        printf("grPlot0: DeviceScreen\n");
        exit(1);
    }

// #todo
// precisamos checar algumas globais, como HotSpotX e HotSpotY.
// Usaremos a janela chamada screen se nenhuma outra foi indicada.
//gui->screen



//-------------------------------------
// tmp: zNear zFar
// Clipping z
// The projection is an element of the camera structure.
// 'CurrentCamera->CurrentProjection'
// Clipping into the projection field.

     int zNear =  0; 
     int zFar  =  80;

     if ( (void*) CurrentProjection != NULL )
     {
          zNear = (int) CurrentProjection->zNear;
          zFar  = (int) CurrentProjection->zFar;
     }

     if (z < zNear)
         return 0;
     if (z >= zFar)
         return 0;

//-------------------------------------


//-------------------------------------
// #todo
// We need a z-buffer or (depth buffer)
// it is used to depth testing.
// it discards some unnecessary covered plots. 
    
// Normalized Device Coordinates (NDC)
// We are using or own ndc style.
// Maybe it is different for diferent systems.
    
//      +y  +z
// -x   +   +x
// -z   -y
    
// We use:
// Left-hand System (LHS) 
// LHS is clockwise (CW).
// Same as Microsoft Direct3D.
// See: https://en.wikipedia.org/wiki/Direct3D
    
// Another way is:
// Right-Hand Coordinate System (RHS).
// RHS is counter-clockwise (CCW).

//
// The clipping window.
//

// #todo
// If the clipping window is invalid, 
// so we're gonna use the root window.
// #todo:
// Maybe we need to use the device context structure,
// or something like that.

    //#test: dangeours
    //clipping_window = __root_window;

    if ( (void*) clipping_window != NULL )
    {
        if ( clipping_window->used  == TRUE && 
             clipping_window->magic == 1234 )
        {
            UseClipping = TRUE;
            w = (struct gws_window_d *) clipping_window;
        }
    }

// Transformation:
// Estamos tranformando de um 'object space' com origem 
// no centro da tela para um viewport que ocupa a tela toda, 
// com origem no canto superior esquerdo.
// IN: 
// return x, return y, x, y, z, fix_orientation,

// #todo:
// Podemos usar o hotspot do dc pra fazermos a transformações.

    // Como não temos uma janela,
    // então fazemos a transformação usando
    // o hotspot da tela.
    if (UseClipping==FALSE)
    {
        __transform_from_viewspace_to_screespace( 
            (int *) &X, (int *) &Y, x, y, z,
            UseLeftHand, 
            HotSpotX, 
            HotSpotY ); 
    }

    // Se temos uma clipping window válida,
    // então usamos o hot spot dela.
    if (UseClipping==TRUE)
    {
        //#todo: precisamos de variaveis de hotspot dentro da estrutura
        // de janela ... o hotspot não fica no centro da janela
        // e sim no centro da área de cliente da janela.
        // o dc atual deve ser a área de cliente da janela.
        __transform_from_viewspace_to_screespace( 
            (int *) &X, (int *) &Y, x, y, z,
            UseLeftHand,
            w->left + (w->width /2), 
            w->top  + (w->height /2) ); 
    }

// Draw and clipping.
// #todo
// Talvez possamos retornar '0'
// se a flag indicar que não precisava desenhar.

    if (Draw != TRUE)
        return -1;

// #todo: 
// We need to check the window limits
// if we are drawing inside a given window.

// Checking the device screen limits.

// #bugbug
// Já fizemos isso logo acima?

    if (X<0){ return -1; }
    if (Y<0){ return -1; }


// fake depth buffer:

/*
    if (db = dc->depth_buf) 
    {
        // Adiciona o deslocamento do pixel.
        // assim obtemos a posição final.
        db += d;
        // Se a próxima profundiade for menor que
        // a que ja tínhamos salvo, então substituimos.
        // Caso contrário, deixe a profundidade anterior.
        if (0 <= dc->db_z <= *db ){
            // Atualizamos a profundidade salva 
            // numa dada posição do z-buffer.
            *db = dc->db_z;
        }else{
            // não precisamos pintar.
            return TRUE;
        }
    }
*/


    if ( 0 <= X < DeviceScreen->width && 
         0 <= Y < DeviceScreen->height )
    {

        if ( UsingAlphaBlending == TRUE )
        {
            // #todo
            // Get the color and modify it.
            //color = get??()
        }

        // Se NÃO temos uma janela válida.
        // device screen
        // 2D, No clipping or transformation.
        // Plot pixel into the raster.
        // The origin is top/left of the viewport. (0,0).
        // IN: color, x, y, rop
        if ( UseClipping == FALSE )
        {
            // #todo
            // O rop pode vir do dc.
            grBackBufferPutpixel( (unsigned int) color, X, Y, 0 ); 
            return 0;
        }

        // Se temos uma janela válida.
        // Plot pixel into the raster.
        // The origin is top/left of the viewport. (0,0).
        // IN: color, x, y, rop
        if ( UseClipping == TRUE )
        {
            // Esta dentro da janela.
            if ( X >= w->left && X <= w->right &&
                 Y >= w->top  && Y <= w->bottom )
                 {
                     // #todo
                     // O rop pode vir do dc.
                     grBackBufferPutpixel((unsigned int) color, X, Y, 0 ); 
                     return 0;
                 }
        }

        // #todo
        // This is a work in progress
            
        //if( UsingDepthBuffer == TRUE )
        //{
        //    depth_buffer[ offset ] = Z;
        //}
            
        return 0;
    }

// Fail 
    return (-1);
}


// plot with graphics effects. use flags.
int 
grPlot1 ( 
    struct gws_window_d *clipping_window,   
    int x, 
    int y, 
    int z, 
    unsigned int color,
    unsigned long flags )
{

//#todo
//Describe the flags.

    int xValue = 0;
    int yValue = 0;
    int zValue = 0;
    unsigned int colorValue=0;


    int fBlack=FALSE;  // black pixel
    int fNoZBuffer = FALSE;
    // ...

    // No graphics effects;
    if ( flags == 0 )
    {
        xValue = x;
        yValue = y;
        zValue = z;
        colorValue = (unsigned int) color;
        goto PlotPixel;
    }

    // #todo #test
    // plot pixel using the caes in fx.
    
    if ( flags & 0x00000001 )
    {
        fBlack = TRUE;
        colorValue = (unsigned int) 0x00000000;
    }

    if ( flags & 0x00000020 )
    {
        fNoZBuffer = TRUE;
        zValue = 0;
    }

    // ...

PlotPixel:

    return (int) grPlot0 ( 
                     clipping_window, 
                     zValue, xValue, yValue, 
                     (unsigned int) colorValue );
}


// #todo
// See: gwsProcedure(), service 2040 in main.c

int serviceGrPlot0 (void){

    unsigned long *message_address = (unsigned long *) &__buffer[0];

    unsigned long x=0;
    unsigned long y=0;
    unsigned long z=0;
    unsigned long color=0;

    gwssrv_debug_print("serviceGrPlot0: [TODO] \n");


    // =================================
    
    // Arguments:
    // Sempre começa do 10 para rotinas 3D.
    
    x      = message_address[10];
    y      = message_address[11];
    z      = message_address[12]; 
    color  = message_address[13];
    
    
    // =================================


    // #todo:
    // pegar os argumentos no buffer e chamar a rotina de plotagem de pixel.
    // Acho que esse serviço nao retorna uma mensagem ao cliente.
    
    grPlot0 ( NULL, (int) z, (int) x, (int) y, (unsigned long) color );

    return 0;
}




/*
void plotLine(int x0, int y0, int x1, int y1);
void plotLine(int x0, int y0, int x1, int y1)
{
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2;                                  // error value e_xy 

    for (;;) {                                                  // loop 
        setPixel(x0,y0);
        e2 = 2*err;
        if (e2 >= dy) {                                       // e_xy+e_x > 0
            if (x0 == x1) break;
            err += dy; x0 += sx;
        }
        if (e2 <= dx) {                                // e_xy+e_y < 0 
            if (y0 == y1) break;
            err += dx; y0 += sy;
        }
    }
}
*/


// Draw a not filled rectangle.
// IN: window, (left/top), (right/bottom), color.
void
grLineRect4 ( 
    struct gws_window_d *window,
    int x1, int y1, 
    int x2, int y2,
    unsigned int color )
{
    if ( (void*)window==NULL){
        return;
    }
    if(window->magic!=1234){
        return;
    }
    plotLine3d (window, x1,y1,0, x2,y1,0, color);
    plotLine3d (window, x2,y1,0, x2,y2,0, color);
    plotLine3d (window, x2,y2,0, x1,y2,0, color);
    plotLine3d (window, x1,y2,0, x1,y1,0, color);
}


/*
 * plotLine3d:  
 */
// Bresenham in 3D
// The algorithm could be extended to three (or more) dimensions.
// #todo: color is unsigned int.

void 
plotLine3d (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned int color )
{
   int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 
   
   //#bugbug: This macro is wrong?!
   //int dm = grMAX3 (dx,dy,dz), i = dm; /* maximum difference */

   int dm = grMAX3(dx,dy,dz);
   register int i = dm;

    // x1 = y1 = z1 = dm/2; /* error offset */
 
    x1 = (dm >> 1);
    y1 = x1;
    z1 = x1;

    for (;;) {

        grPlot0 ( window, z0, x0, y0, color );
     
        if (i-- == 0) { break; }
        
        x1 -= dx; 
        if (x1 < 0) 
        { x1 += dm; x0 += sx; }
        
        y1 -= dy; 
        if (y1 < 0) 
        { y1 += dm; y0 += sy; }
        
        z1 -= dz; 
        if (z1 < 0) 
        { z1 += dm; z0 += sz; }
    };
}


// print line and line tracker.
// track the last-1 vector.
void 
plotLine3dLT (
    struct gws_window_d *window,
    int x0, int y0, int z0, 
    int x1, int y1, int z1,
    int *x2, int *y2, int *z2, 
    unsigned int color )
{
   int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 
   
   //#bugbug: This macro is wrong?!
   //int dm = grMAX3 (dx,dy,dz), i = dm; /* maximum difference */
   
   int dm = grMAX3(dx,dy,dz);
   register int i = dm;

    // x1 = y1 = z1 = dm/2; /* error offset */
 
    x1 = (dm >> 1);
    y1 = x1;
    z1 = x1;

    for (;;) {

        grPlot0 ( window, z0, x0, y0, color );

        // (n-1)?
        if (i == 1)
        {
            if ( (void*) x2 != NULL ){ *x2 = x0; }
            if ( (void*) y2 != NULL ){ *y2 = y0; }
            if ( (void*) z2 != NULL ){ *z2 = z0; }
            
            break;
        }

        if (i == 0){
            break;
        }
        
        x1 -= dx; 
        if (x1 < 0) 
        { x1 += dm; x0 += sx; }
        
        y1 -= dy; 
        if (y1 < 0) 
        { y1 += dm; y0 += sy; }
        
        z1 -= dz; 
        if (z1 < 0) 
        { z1 += dm; z0 += sz; }
        
        i--;
    };
}


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
    int draw )
{
    int ResultNumberOfVectors=0;

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 

   //#bugbug: This macro is wrong?!
   //int dm = grMAX3 (dx,dy,dz), i = dm; /* maximum difference */
   
   int dm = grMAX3(dx,dy,dz);
   register int i = dm;
   ResultNumberOfVectors = (int) i;

    // x1 = y1 = z1 = dm/2; /* error offset */
 
    x1 = (dm >> 1);
    y1 = x1;
    z1 = x1;

    for (;;) {

        if(draw){
            grPlot0 ( window, z0, x0, y0, color );
        }
        
        //
        if (i == n)
        {
            if ( (void*) x2 != NULL ){ *x2 = x0; }
            if ( (void*) y2 != NULL ){ *y2 = y0; }
            if ( (void*) z2 != NULL ){ *z2 = z0; }
            // Do not break.
        }

        // End of line.
        if (i == 0){
            break;
        }

        x1 -= dx;
        if (x1 < 0) { x1 += dm; x0 += sx; }
        y1 -= dy; 
        if (y1 < 0) { y1 += dm; y0 += sy; }
        z1 -= dz;
        if (z1 < 0) { z1 += dm; z0 += sz; }

        i--;
    };

    return (int) ResultNumberOfVectors;
}


// #todo
// plot line given two colors.
// interpolation ?
void 
plotLine3d2 (
    int x0, int y0, int z0, unsigned long color1,
    int x1, int y1, int z1, unsigned long color2, 
    int flag )
{

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 
   
    //#bugbug: This macro is wrong?!
    //int dm = grMAX3 (dx,dy,dz), i = dm; /* maximum difference */
   
    int dm = grMAX3(dx,dy,dz);
    register int i = dm;
   
    // x1 = y1 = z1 = dm/2; /* error offset */
 
    x1 = (dm >> 1);
    y1 = x1;
    z1 = x1;

// nothing for now;
// interpolation flag.

    flag=0;


//
// Loop 
//

    for (;;) {  

        grPlot0 ( NULL, z0, x0, y0, color1 );
        //grPlot0 ( NULL, z0, x0, y0, color2 );
      
        if (i-- == 0) break;
        x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; } 
        y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; } 
        z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; } 
    };
}




// IN:
// The upper-left corner
// lower-right corner. 
// color
void
rectangle_from_two_points (
    int left, int top, 
    int right, int bottom,
    unsigned int color )
{

    // #todo
    // Check validation
    // if (left<0 ...

// cima
    plotLine3d ( 
        NULL,
        left,top,0, 
        right,top,0, 
        color );

// baixo
    plotLine3d ( 
        NULL,
        left,bottom,0, 
        right,bottom,0, 
        color );

// esquerda
    plotLine3d ( 
        NULL,
        left,top,0, 
        left,bottom,0, 
        color );

// direita
    plotLine3d ( 
        NULL,
        right,top,0, 
        right,bottom,0, 
        color );
}


// worker
// 4 3d lines, not filled.
void __rectangleZZ ( struct gr_rectangle_d *rect )
{
    if ( (void*) rect == NULL ){
        return;
    }

    // #todo
    // Check the validation of the values in the structure.

    // points
    //  0  1
    //  3  2

    //#bugbug
    // We need to create a routine with colors in both points.

//
// Draw 4 lines.
//

// cima
    //plotLine3d2 ( left, top,  z, right, top, z, color, flag );
    plotLine3d2 ( 
        rect->p[0].x, rect->p[0].y, rect->p[0].z, rect->p[0].color,
        rect->p[1].x, rect->p[1].y, rect->p[1].z, rect->p[1].color, 
        0 );

// baixo
     //plotLine3d2 ( left, bottom, z, right,bottom, z, color, flag );
     plotLine3d2 ( 
         rect->p[3].x, rect->p[3].y, rect->p[3].z, rect->p[3].color,
         rect->p[2].x, rect->p[2].y, rect->p[2].z, rect->p[2].color, 
         0 );

// esquerda
     //plotLine3d2 ( left, top, z, left, bottom, z, color, flag );
     plotLine3d2 ( 
         rect->p[0].x, rect->p[0].y, rect->p[0].z, rect->p[0].color,
         rect->p[3].x, rect->p[3].y, rect->p[3].z, rect->p[3].color, 
         0 ); 

// direita
     //plotLine3d2 ( right,  top, z, right, bottom, z, color, flag );
     plotLine3d2 ( 
         rect->p[1].x, rect->p[1].y, rect->p[1].z, rect->p[1].color,
         rect->p[2].x, rect->p[2].y, rect->p[2].z, rect->p[2].color, 
         0 );
}


int grRectangle( struct gr_rectangle_d *rect )
{

    if( (void*) rect == NULL )
        return -1;

// #todo
// Use options
// Create a flag in the fuction's parameters.

// Option 1:
// worker
// 4 3d lines, not filled.
    __rectangleZZ(rect);

// Option 2:
// ...

    return 0;
}


// Rectangle rasterization using 3d lines.
// It's not the standard quad rasterization routine
// using the viewport 2d coordenates.
// It uses the model 3d coordenates.
// It applies only on few cases.
// IN:
// upper-left corner, 
// lower-right corner,
// color
// #bugbug:
// Essa rotina é boa somente para alguns casos.
// depende da inclinação.

void
rectangle_ras3D (
    int left,  int top,    int z0,
    int right, int bottom, int z1,
    unsigned int color )
{
    register int Line=0;

// #todo
// No caso de inclinações da linha,
// precisamos considerar que temos dois 'top' diferentes.
// precisamos receber mais parâmetros de função,
// ou criarmos uma outra funções que tenha tais parâmetros,
// ficando essa somente para retângulos não inclinados.

// #todo
// isso ta bem confuso.
// Estamos no eixo y, para cima, maior que 0.
// Entao top tem um valor maior que bottom.

    if (top  <= bottom){return;} 
    if (left >= right) {return;}

// #todo
// device limits.

// Começa com a linha de cima.
// Estamos no eixo y, para cima, maior que zero.
// Enquanto for maior que o bottom.

//top:     y da linha superior do retangulo
//bottom:  y da linha inferior do retangulo

// Pintamos uma linha por vez, horizontalmente.
// IN: 
// x0,y0,z0, x1,y1,z1, color.
        
    for ( Line = top;
          Line >= bottom; 
          Line-- )
    {
        plotLine3d ( 
            NULL,
            left,  Line, z0,   // vertex 1 (left vertex)
            right, Line, z1,   // vertex 2 (right vertex) 
            color );
    };
}


// Scaling: Inflate cube.
int 
xxxInflateCubeZ ( 
    struct gr_cube_d *cube, 
    int value )
{

    if ( (void*) cube == NULL ){
        return (-1);
    }

    //int value = z;
    //int value = z*2;

    // south points =====================================
    cube->p[0].x = (cube->p[0].x - value);
    cube->p[0].y = (cube->p[0].y + value);
    cube->p[0].z = (cube->p[0].z - value);
        
    cube->p[1].x = (cube->p[1].x + value);
    cube->p[1].y = (cube->p[1].y + value);
    cube->p[1].z = (cube->p[1].z - value);
        
    cube->p[2].x = (cube->p[2].x + value);
    cube->p[2].y = (cube->p[2].y - value);
    cube->p[2].z = (cube->p[2].z - value);
        
    cube->p[3].x = (cube->p[3].x - value);
    cube->p[3].y = (cube->p[3].y - value);
    cube->p[3].z = (cube->p[3].z - value);

    //north points ================================
    cube->p[4].x = (cube->p[4].x - value);
    cube->p[4].y = (cube->p[4].y + value);
    cube->p[4].z = (cube->p[4].z + value);
        
    cube->p[5].x = (cube->p[5].x + value);
    cube->p[5].y = (cube->p[5].y + value);
    cube->p[5].z = (cube->p[5].z + value);
        
    cube->p[6].x = (cube->p[6].x + value);
    cube->p[6].y = (cube->p[6].y - value);
    cube->p[6].z = (cube->p[6].z + value);
        
    cube->p[7].x = (cube->p[7].x - value);
    cube->p[7].y = (cube->p[7].y - value);
    cube->p[7].z = (cube->p[7].z + value);

    return 0;
}

// Scaling: Deflate cube.
int 
xxxDeflateCubeZ ( 
    struct gr_cube_d *cube, 
    int value )
{
    if ( (void*) cube == NULL ){
        return -1;
    }


    // south points ==========================
    cube->p[0].x = (cube->p[0].x + value);
    cube->p[0].y = (cube->p[0].y - value);
    cube->p[0].z = (cube->p[0].z + value);
        
    cube->p[1].x = (cube->p[1].x - value);
    cube->p[1].y = (cube->p[1].y - value);
    cube->p[1].z = (cube->p[1].z + value);
        
    cube->p[2].x = (cube->p[2].x - value);
    cube->p[2].y = (cube->p[2].y + value);
    cube->p[2].z = (cube->p[2].z + value);
        
    cube->p[3].x = (cube->p[3].x + value);
    cube->p[3].y = (cube->p[3].y + value);
    cube->p[3].z = (cube->p[3].z + value);

    // north points =========================
    cube->p[4].x = (cube->p[4].x + value);
    cube->p[4].y = (cube->p[4].y - value);
    cube->p[4].z = (cube->p[4].z - value);
        
    cube->p[5].x = (cube->p[5].x - value);
    cube->p[5].y = (cube->p[5].y - value);
    cube->p[5].z = (cube->p[5].z - value);
        
    cube->p[6].x = (cube->p[6].x - value);
    cube->p[6].y = (cube->p[6].y + value);
    cube->p[6].z = (cube->p[6].z - value);
        
    cube->p[7].x = (cube->p[7].x + value);
    cube->p[7].y = (cube->p[7].y + value);
    cube->p[7].z = (cube->p[7].z - value);
       
    return 0;
}

int grTriangleScale0( struct gr_triangle_d *t);
int grTriangleScale0( struct gr_triangle_d *t)
{
    return 0;
}

// Triangle
// Draw a not filled triangle
// using 3D parameters.
int 
xxxTriangleZ(
    struct gws_window_d *window, 
    struct gr_triangle_d *triangle )
{

    if ( (void*) triangle == NULL ){
        return -1;
    }

// Draw:
// Circular, 
// sentido horario, 
// começando pelo ponto de cima.

    plotLine3d (
        window,
        triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
        triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
        triangle->p[1].color );
    plotLine3d (
        window,
        triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
        triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
        triangle->p[2].color );
    plotLine3d (
        window,
        triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
        triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
        triangle->p[0].color );

    return 0;
}



int 
xxxFillTriangle0(
    struct gws_window_d *window, 
    struct gr_triangle_d *triangle )
{

    int tmpx=0;
    int tmpy=0;


    if ( (void*) triangle == NULL ){
        return -1;
    }

    if ( (void*) window == NULL ){
        return -1;
    }
    if(window->magic != 1234)
        return -1;


// -------------------------------------------
// Draws a not filled triangle.
// 3d coordinates

    plotLine3d (
        window,
        triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
        triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
        triangle->p[1].color );
    plotLine3d (
        window,
        triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
        triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
        triangle->p[2].color );
    plotLine3d (
        window,
        triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
        triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
        triangle->p[0].color );
//-------------------------------------------

    int i=0;
    int res_lt0x=0;
    int res_lt0y=0;
    int res_lt0z=0;
    int res_lt1x=0;
    int res_lt1y=0;
    int res_lt1z=0;

    // Number of vectors.
    int nov1=0;
    int nov2=0;

// #test
// 3 'demãos' de tinta, porque pintar na diagonal
// não fica tão perfeitinho quanto pintar na horizontal,
// ou vertical.
// Mas no futuro vamos criar alguma solução que 
// pinte na horizontal pra ficar pefeitinho.


//--------------------------------------------------
// first time

    // muitas vezes.
    // mas quebra quando termina o retangulo.
    for (i=0; i<1000; i++)
    {
        // track 0
        // plot a line and track a given vector.
        nov1 = (int) plotLine3dLT2 (
            window,
            triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
            triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
            &res_lt0x, &res_lt0y, &res_lt0z,
            i,
            COLOR_RED,
            FALSE );  //do not draw

        // track 1
        nov2 = (int) plotLine3dLT2 (
            window,
            triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
            triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
            &res_lt1x, &res_lt1y, &res_lt1z,
            i,
            COLOR_RED,
            FALSE );  // do not draw

        if ( i >= nov1 || i >= nov2 )
            break;
            
        // line cutting the two lines.
        plotLine3d (
           window,
           res_lt0x, res_lt0y, res_lt0z, 
           res_lt1x, res_lt1y, res_lt1z, 
           COLOR_YELLOW );
     };

//--------------------------------------------------
// second time

    // muitas vezes.
    // mas quebra quando termina o retangulo.
    for (i=0; i<1000; i++)
    {
        // track 0
        // plot a line and track a given vector.
        nov1 = (int) plotLine3dLT2 (
            window,
            triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
            triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
            &res_lt0x, &res_lt0y, &res_lt0z,
            i,
            COLOR_RED,
            FALSE );  //do not draw

        // track 1
        nov2 = (int) plotLine3dLT2 (
            window,
            triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
            triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
            &res_lt1x, &res_lt1y, &res_lt1z,
            i,
            COLOR_RED,
            FALSE );  // do not draw

        if ( i >= nov1 || i >= nov2 )
            break;
            
        // line cutting the two lines.
        plotLine3d (
           window,
           res_lt0x, res_lt0y, res_lt0z, 
           res_lt1x, res_lt1y, res_lt1z, 
           COLOR_YELLOW );
     };

//--------------------------------------------------
// third time

    // muitas vezes.
    // mas quebra quando termina o retangulo.
    for (i=0; i<1000; i++)
    {
        // track 0
        // plot a line and track a given vector.
        nov1 = (int) plotLine3dLT2 (
            window,
            triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
            triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
            &res_lt0x, &res_lt0y, &res_lt0z,
            i,
            COLOR_RED,
            FALSE );  //do not draw

        // track 1
        nov2 = (int) plotLine3dLT2 (
            window,
            triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
            triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
            &res_lt1x, &res_lt1y, &res_lt1z,
            i,
            COLOR_RED,
            FALSE );  // do not draw

        if ( i >= nov1 || i >= nov2 )
            break;
            
        // line cutting the two lines.
        plotLine3d (
           window,
           res_lt0x, res_lt0y, res_lt0z, 
           res_lt1x, res_lt1y, res_lt1z, 
           COLOR_YELLOW );
     };



/*
//-------------------------------------------
// deltas absolutos

    // y
    int d1 = triangle->p[0].y - triangle->p[1].y;
    int abs_d1 = abs(d1);
    int d2 = triangle->p[0].y - triangle->p[2].y;
    int abs_d2 = abs(d2);
    int abs_d1d2 = d1 + d2;
    
    // x
    int d3 = triangle->p[0].x - triangle->p[1].x;
    int abs_d3 = abs(d3);
    int d4 = triangle->p[0].x - triangle->p[2].x;
    int abs_d4 = abs(d4);
    int abs_d3d4 = d3 + d4;

    int tmp;
    
    // dy <= dx
    if ( abs_d1d2 <= abs_d1d2 )
    {
        if (triangle->p[2].x < triangle->p[1].x)
        {
            tmp = triangle->p[2].x;
            triangle->p[2].x = triangle->p[1].x;
            triangle->p[1].x = tmp;
        }
        if (triangle->p[1].x < triangle->p[0].x)
        {
            tmp = triangle->p[1].x;
            triangle->p[1].x = triangle->p[0].x;
            triangle->p[0].x = tmp;
        }

        if (triangle->p[2].y < triangle->p[1].y)
        {
            tmp = triangle->p[2].y;
            triangle->p[2].y = triangle->p[1].y;
            triangle->p[1].y = tmp;
        }
        if (triangle->p[1].y < triangle->p[0].y)
        {
            tmp = triangle->p[1].y;
            triangle->p[1].y = triangle->p[0].y;
            triangle->p[0].y = tmp;
        }

        plotLine3d(
            window,
            triangle->p[0].x, triangle->p[0].y, 0,
            triangle->p[1].x, triangle->p[1].y, 0,
            COLOR_WHITE );

        plotLine3d(
            window,
            triangle->p[1].x, triangle->p[1].y, 0,
            triangle->p[2].x, triangle->p[2].y, 0,
            COLOR_WHITE );

        plotLine3d(
            window,
            triangle->p[2].x, triangle->p[2].y, 0,
            triangle->p[0].x, triangle->p[0].y, 0,
            COLOR_WHITE );
            

    }
    else{
    };
*/


    return 0;
}

// This routine uses a crazy rasterization routine.
int 
xxxTriangleZ1(
    struct gws_window_d *window, 
    struct gr_triangle_d *triangle )
{
    return (int) xxxFillTriangle0(window,triangle);
}


int grTriangle( struct gr_triangle_d *triangle )
{
    int Status=0;
    
    if ( (void*) triangle == NULL )
        return -1;

    // #todo
    // something
  
    Status = (int) xxxTriangleZ(NULL,triangle);
    
    return Status;
}



// Polyline
// O segundo ponto da linha 
// vira o primeiro ponto da próxima linha.
int xxxPolygonZ ( struct gr_polygon_d *polygon )
{
    int i=0;
    
    int NumberOfElements=0;
    int Max = 32;

    // list of polygon pointers.
    unsigned long *list = (unsigned long *) polygon->list_address;


    // two vectors to create a line.
    struct gr_vec3D_d *v1;
    struct gr_vec3D_d *v2;

    int PolygonType=0;



    // structure

    if ( (void*) polygon == NULL ){
        goto fail;
    }

    // list
 
    if ( (void*) list == NULL ){
        goto fail;
    }

    // number of elements

    NumberOfElements = polygon->n;

    if ( NumberOfElements > Max ){
        goto fail;
    }

    // polygon type

    PolygonType = polygon->type;

    switch(PolygonType){
    case POLYGON_POLYPOINT:  goto do_polypoint;  break;
    case POLYGON_POLYLINE:   goto do_polyline;   break;
    default:
        goto fail;
        break;
    };


    // Draw polypoint
do_polypoint:

    // #todo
    // Nothing for now

    for ( i=0; i<NumberOfElements; i++ )
    {
        v1 = (struct gr_vec3D_d *) list[i];
        if ( (void*) v1 == NULL ){ 
            gwssrv_debug_print(">>>> BREAK\n");
            break; 
        }

        // draw

        grPlot0 ( NULL, v1->z, v1->x, v1->y, v1->color );
    };
    return 0;

    // Draw polyline
do_polyline:

    for ( i=0; i<NumberOfElements; i++ )
    {
        // get the first element of two.
        v1 = (struct gr_vec3D_d *) list[i];
        // get the second element of two.
        v2 = (struct gr_vec3D_d *) list[i+1];
    
        if ( (void*) v1 == NULL || 
             (void*) v2 == NULL )
        { 
            gwssrv_debug_print(">>>> BREAK\n");
            break; 
        }

        gwssrv_debug_print(">>>> DRAW LINE\n");
    
        // Plot
        
        plotLine3d (
            NULL,
            v1->x, v1->y, v1->z,  // first point
            v2->x, v2->y, v2->z,  // second point
            v1->color );
    };
    return 0;

fail:
    gwssrv_debug_print("xxxPolygonZ: fail\n");
    return -1;
}



// #test
// >>>> wired cube <<<< 
// "with ugly rasterization in some of the fazes"
// This rasterization uses lines and applies only in the faces
// with not inclination.
// #todo
// Create function parameters to select if we will use some
// kind of rasterization or not.
// #todo
// We can create a function only for wired cube, 
// and another one for cube with some kind of rasterization.


int xxxDrawCubeZ ( struct gr_cube_d *cube )
{

// #todo: 
// Comment these variables.

    int h=0;
    int d=0;
    int i=0;

// #todo
// Maybe we will receive a function parameter for that.
    int UseRasterization = TRUE;

    if ( (void*) cube == NULL )
    {
        return -1;
    }

// #todo
// Temos que rever a forma em que estamos usado os parâmetros
// para pintarmos o objeto cubo.
// Tudo aqui ainda está bem improvisado.


// ===========
// north
// Primeiro desenha o north porque ele sera sobreposto 
// pelo sul nessa camera.
// -- back face ----------------------------------------
// north - back
// Retângulo com os 4 pontos de trás.

    plotLine3d (  // cima
        NULL,
        cube->p[4].x, cube->p[4].y, cube->p[4].z, 
        cube->p[5].x, cube->p[5].y, cube->p[5].z, cube->p[4].color );
    plotLine3d (  // direita
        NULL,
        cube->p[5].x, cube->p[5].y, cube->p[5].z, 
        cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[5].color );
    plotLine3d (  // baixo 
        NULL,
        cube->p[7].x, cube->p[7].y, cube->p[7].z, 
        cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[7].color );
    plotLine3d (  // esquerda
        NULL,
        cube->p[4].x, cube->p[4].y, cube->p[4].z, 
        cube->p[7].x, cube->p[7].y, cube->p[7].z, cube->p[4].color );

// #improviso: 
// Isso é um teste de rasterização, não usando triangulo.
// #todo:
// Temos que criar a tasterização via retângulos.
// Isso só funciona para retângulos não inclinados.
// p4 = left top 
// p6 = right bottom
    
    // north rasterization
    if (UseRasterization == TRUE)
    {
        rectangle_ras3D ( 
            cube->p[4].x, cube->p[4].y, cube->p[4].z, 
            cube->p[6].x, cube->p[6].y, cube->p[6].z, 
            (unsigned int) cube->p[4].color  );
    }

//====================
// -- top face ----------------------------------------
    // 1st line 
    plotLine3d ( NULL,
                cube->p[0].x, cube->p[0].y, cube->p[0].z, 
                cube->p[4].x, cube->p[4].y, cube->p[4].z, cube->p[0].color );
    // 2nd line
    plotLine3d (NULL,
                cube->p[1].x, cube->p[1].y, cube->p[1].z, 
                cube->p[5].x, cube->p[5].y, cube->p[5].z, cube->p[1].color );

//====================
// -- bottom face -------------------------------------
    // 1rd line
    plotLine3d (NULL,
                cube->p[2].x, cube->p[2].y, cube->p[2].z, 
                cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[2].color );
    // 2th line 
    plotLine3d (NULL,
                cube->p[3].x, cube->p[3].y, cube->p[3].z, 
                cube->p[7].x, cube->p[7].y, cube->p[7].z, cube->p[3].color );

//=================================================================

// left 
// Isso só funciona para retângulos não inclinados.
// p0 = left top da frente 
// p7 = left bottom de trás
    //left raterization?
    if (UseRasterization == TRUE)
    {
        rectangle_ras3D ( 
            cube->p[0].x, cube->p[0].y, cube->p[0].z, 
            cube->p[7].x, cube->p[7].y, cube->p[7].z, 
            cube->p[0].color  );

    }

// right
// Isso só funciona para retângulos não inclinados.
// p1 = right top da frente 
// p7 = right bottom de trás
    // right rasterization?
    if (UseRasterization == TRUE)
    {
        rectangle_ras3D( 
            cube->p[1].x, cube->p[1].y, cube->p[1].z, 
            cube->p[6].x, cube->p[6].y, cube->p[6].z, 
            cube->p[1].color  );
    }

    // tampa de baixo
    //bottom fail
    //rectangle_ras3D ( 
    //    cube->p[3].x, cube->p[3].y, cube->p[3].z, 
    //    cube->p[6].x, cube->p[6].y, cube->p[6].z,
    //    cube->p[2].color  );

    // tampa de cima.
    // top fail
    //rectangle_ras3D ( 
    //    cube->p[4].x, cube->p[4].y, cube->p[4].z, 
    //    cube->p[0].x, cube->p[0].y, cube->p[0].z,
    //    cube->p[3].color  );

//==========
// -- front face ----------------------------------------
// south - front
// Retângulo com os 4 pontos da frente.
    plotLine3d (  // cima
        NULL,
        cube->p[0].x, cube->p[0].y, cube->p[0].z, 
        cube->p[1].x, cube->p[1].y, cube->p[1].z, cube->p[0].color );
    plotLine3d (  // direita
        NULL,
        cube->p[1].x, cube->p[1].y, cube->p[1].z, 
        cube->p[2].x, cube->p[2].y, cube->p[2].z, cube->p[1].color );
    plotLine3d (  // baixo
        NULL,
        cube->p[3].x, cube->p[3].y, cube->p[3].z,
        cube->p[2].x, cube->p[2].y, cube->p[2].z, cube->p[3].color );
    plotLine3d (  // esquerda
        NULL,
        cube->p[0].x, cube->p[0].y, cube->p[0].z, 
        cube->p[3].x, cube->p[3].y, cube->p[3].z, cube->p[0].color );

// #improviso: 
// Isso é um teste de rasterização, não usando triangulo.
// #todo:
// Temos que criar a tasterização via retãngulos.
// Isso só funciona para retângulos não inclinados.
// p0 = left top 
// p2 = right bottom

    // south rasterization
    if (UseRasterization == TRUE){
        rectangle_ras3D (  
            cube->p[0].x, cube->p[0].y, cube->p[0].z, 
            cube->p[2].x, cube->p[2].y, cube->p[2].z, 
            cube->p[0].color );
    }

    // ok
    return 0;
}



// sevice 2041
// Called by gwsProcedure.
int serviceGrCubeZ(void)
{
    //#deprecated
    return -1;
}


// sevice 2042
int serviceGrRectangle(void)
{
    //#deprecated
    return -1;
}



//Circle
//This is an implementation of the circle algorithm.
// ?? what means 'm' ???
void 
plotCircle ( 
    int xm, 
    int ym, 
    int r, 
    unsigned int color )
{

    /* II. Quadrant */ 
   //int x = -r, y = 0, err = 2-2*r; 
   
    //loop
    register int x = -r;
   
    int y = 0;
    int err = (2-(2*r));


    do {
      
      //setPixel(xm-x, ym+y); /*   I. Quadrant */
      //setPixel(xm-y, ym-x); /*  II. Quadrant */
      //setPixel(xm+x, ym-y); /* III. Quadrant */
      //setPixel(xm+y, ym+x); /*  IV. Quadrant */

      grPlot0 ( NULL, 0, xm-x, ym+y, color);
      grPlot0 ( NULL, 0, xm-y, ym-x, color);
      grPlot0 ( NULL, 0, xm+x, ym-y, color);
      grPlot0 ( NULL, 0, xm+y, ym+x, color);
      
      r = err;
      
      // #ugly routine.
      
      /* e_xy+e_y < 0 */
      if (r <= y) 
      { 
           err += ++y * 2 + 1; 
      }           
      
      /* e_xy+e_x > 0 or no 2nd y-step */
      if (r > x || err > y) 
      { 
          err += ++x * 2+1; 
      }
      
    } while (x < 0);
}


void 
plotCircleZ ( 
    struct gws_window_d *window,
    int xm, 
    int ym, 
    int r, 
    unsigned int color, 
    int z )
{
    /* II. Quadrant */ 
    //int x = -r, y = 0, err = 2-2*r; 

    register int x = (int) -r;
             int y=0;

    // decrementa o diâmetro.
    int err = (int) (2-(2*r));
    int tmp=0;

    do {

      grPlot0 ( window, z, xm-x, ym+y, color);//d  /*   I. Quadrant */
      grPlot0 ( window, z, xm-y, ym-x, color);//c  /*  II. Quadrant */
      grPlot0 ( window, z, xm+x, ym-y, color);//e  /* III. Quadrant */
      grPlot0 ( window, z, xm+y, ym+x, color);//b  /*  IV. Quadrant */

      r = err;
      
      //e_xy+e_y < 0
      if (r <= y) 
      {
           tmp = ++y * 2+1;
           err += tmp; 
      }
      
      // e_xy+e_x > 0 or no 2nd y-step
      if (r > x || err > y) 
      {
          tmp = ++x * 2+1;
          err += tmp; 
      }
      
    } while (x < 0);
}
 


// Retorna vetor do n ponto partindo da reta data.
// n não pode ser maior que o raio.
// anti-horário?
// 1=c | 2=e | 3=b | 4=d
// OUT:
// -1 on error | 0 if ok.
int
plotCircleZLT0 ( 
    struct gws_window_d *window,
    int xm, 
    int ym, 
    int r, 
    unsigned int color, 
    int z,
    int axis_n,                           // qual eixo?   
    int n,                                // number of the target pointer.
    int *res_x, int *res_y, int *res_z,   // return vector.
    int draw )                            // draw or not.  
{
    /* II. Quadrant */ 
    //int x = -r, y = 0, err = 2-2*r; 

    register int x = (int) -r;
             int y=0;

    // decrementa o diâmetro.
    int err = (int) (2-(2*r));
    int tmp=0;

// qual eixo?
    if( axis_n < 1 || axis_n > 4){
        return -1;
    }

// Não pode ser maior que o raio.
    if(n>r){
        return -1;
    }

    if ( (void*) res_x == NULL ||
         (void*) res_y == NULL ||
         (void*) res_z == NULL )
    {
        return -1;
    }

    do {
      // anti-horário?
      // 1=c | 2=e | 3=b | 4=d
      
      if( n == (-x) )
      {
          if (axis_n==1){  //c
          *res_x = (int) xm-x;
          *res_y = (int) ym+y;
          *res_z = (int) z;
          }
          if (axis_n==2){  //e
          *res_x = (int) xm-y;
          *res_y = (int) ym-x;
          *res_z = (int) z;
          }
          if (axis_n==3){  //b
          *res_x = (int) xm+x;
          *res_y = (int) ym-y;
          *res_z = (int) z;
          }
          if (axis_n==4){  //d
          *res_x = (int) xm+y;
          *res_y = (int) ym+x;
          *res_z = (int) z;
          }
      }
      
      if (draw){
          grPlot0 ( window, z, xm-x, ym+y, color);//c  /*   I. Quadrant */
          grPlot0 ( window, z, xm-y, ym-x, color);//e  /*  II. Quadrant */
          grPlot0 ( window, z, xm+x, ym-y, color);//b  /* III. Quadrant */
          grPlot0 ( window, z, xm+y, ym+x, color);//d  /*  IV. Quadrant */
      }
      
      r = err;
      
      //e_xy+e_y < 0
      if (r <= y) 
      {
           tmp = ++y * 2+1;
           err += tmp; 
      }
      
      // e_xy+e_x > 0 or no 2nd y-step
      if (r > x || err > y) 
      {
          tmp = ++x * 2+1;
          err += tmp; 
      }
      
    } while (x < 0);

// ok
    return 0;
}
 

 
/* 
 //credits: uVGA
void __fillCircle(int xm, int ym, int r, int color)
{
	int x, y;

	for (y = -r; y <= r; y++)
	{
		for (x = -r; x <= r; x++)
		{
			if ((x * x) + (y * y) <= (r * r))
			{
				drawHLine(ym + y, xm + x, xm - x, color);
				if(y != 0)
					drawHLine(ym - y, xm + x, xm - x, color);
				break;
			}
		}
	}
}
*/

/*
void uVGA::fillEllipse(int x0, int y0, int x1, int y1, int color)
{
	int x;
	int y;
	int half_height = abs(y0 - y1) / 2;
	int half_width = abs(x0 - x1) / 2;
	int center_x = (x0 < x1 ? x0 : x1) + half_width;
	int center_y = (y0 < y1 ? y0 : y1) + half_height;

	for(y = -half_height; y <= 0; y++)
	{
		for(x = -half_width; x <= 0; x++)
		{
			if( (x * x * half_height * half_height + y * y * half_width * half_width) <= (half_height * half_height * half_width * half_width))
			{
				drawHLine(center_y + y, center_x + x, center_x - x, color);
				if(y != 0)
					drawHLine(center_y - y, center_x + x, center_x - x, color);
				break;
			}
		}
	}
}
*/

//Ellipse
//This program example plots an ellipse inside a specified rectangle.

void 
plotEllipseRect (
    int x0, int y0, 
    int x1, int y1, 
    unsigned long color )
{

   int a = abs(x1-x0), b = abs(y1-y0), b1 = b&1; /* values of diameter */
   long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
   long err = dx+dy+b1*a*a, e2; /* error of 1.step */

   if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
   if (y0 > y1) y0 = y1; /* .. exchange them */
   y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
   a *= 8*a; b1 = 8*b*b;


    do {
       grPlot0 ( NULL, 0, x1, y0, color);  //   I. Quadrant
       grPlot0 ( NULL, 0, x0, y0, color);  //  II. Quadrant
       grPlot0 ( NULL, 0, x0, y1, color);  // III. Quadrant
       grPlot0 ( NULL, 0, x1, y1, color);  //  IV. Quadrant
       
       e2 = (2*err);
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    
    } while (x0 <= x1);


    /* too early stop of flat ellipses a=1 */
    while (y0-y1 < b) {
        grPlot0 ( NULL, 0, x0-1,    y0, color);  //-> finish tip of ellipse
        grPlot0 ( NULL, 0, x1+1,  y0++, color);
        grPlot0 ( NULL, 0, x0-1,    y1, color);
        grPlot0 ( NULL, 0, x1+1,  y1--, color);
    };
}


void 
plotEllipseRectZ (
    int x0, int y0, 
    int x1, int y1, 
    unsigned long color,
    int z )
{

   int a = abs(x1-x0), b = abs(y1-y0), b1 = b&1; /* values of diameter */
   long dx = 4*(1-a)*b*b, dy = 4*(b1+1)*a*a; /* error increment */
   long err = dx+dy+b1*a*a, e2; /* error of 1.step */

   if (x0 > x1) { x0 = x1; x1 += a; } /* if called with swapped points */
   if (y0 > y1) y0 = y1; /* .. exchange them */
   y0 += (b+1)/2; y1 = y0-b1;   /* starting pixel */
   a *= 8*a; b1 = 8*b*b;


    do {
       grPlot0 ( NULL, z, x1, y0, color);  //   I. Quadrant
       grPlot0 ( NULL, z, x0, y0, color);  //  II. Quadrant
       grPlot0 ( NULL, z, x0, y1, color);  // III. Quadrant
       grPlot0 ( NULL, z, x1, y1, color);  //  IV. Quadrant
       
       e2 = (2*err);
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    
    } while (x0 <= x1);


    /* too early stop of flat ellipses a=1 */
    
    while (y0-y1 < b) {
        grPlot0 ( NULL, z, x0-1,    y0, color);  // -> finish tip of ellipse
        grPlot0 ( NULL, z, x1+1,  y0++, color);
        grPlot0 ( NULL, z, x0-1,    y1, color);
        grPlot0 ( NULL, z, x1+1,  y1--, color);
    };
}

/*
 * noraDrawingStuff: 
 *    Lot of dots in the right place. (prime stuff)
 *    2020 - Created by Fred Nora. 
 */

void noraDrawingStuff(void)
{
    register int x=0;
    register int y=0;
    unsigned int color = COLOR_BLACK;

// Colunas.
    for (x=0; x<SavedX; x++)
    {
        for (y=0; y<SavedY; y++)
        {
            if ( x != 0 )
            {
                if ( (y % x) == 0 )
                {
                    // IN: color, x, y,rop
                    grBackBufferPutpixel(color,x,y,0); 
                }
            }
        };
        
        if ( x >= SavedY ) { break; }
    };
}


/*
 * noraDrawingStuff3: 
 *    Lot of dots in the right place. (prime stuff)
 *    2020 - Created by Fred Nora. 
 */

void noraDrawingStuff3 (int x, int y, int z)
{
    register int _x=0;
    register int _y=0;
    register int _z = z;

    int limitX = (SavedX >> 1);
    int limitY = (SavedY >> 1);

    // colunas.
    for (_x=x; _x<limitX; _x++)    
    {
        for (_y=y; _y<limitY; _y++)
        {
            if ( _x != 0 )
            {
                if ( _y % _x == 0 ){
                    grPlot0 ( NULL, _z, _x, _y,COLOR_BLACK );
                }
            }
        };
        
        if ( _x >= limitY) { break; }
    };
}


/* 
// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]

void 
matrix_multiply_2x3 ( 
    int mat1[2][3], 
    int mat2[2][3], 
    int res[2][3])
{

    int N1 = 2;
    int N2 = 3;
    
    int i, j, k;
    
    
    for (i = 0; i < N1; i++) 
    {
        for (j = 0; j < N2; j++) 
        {
            res[i][j] = 0;
            
            //for (k = 0; k < N1; k++)
            for (k = 0; k < N2; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
}
*/

// #ugly
void multiply4 (int mat1[4][4], int mat2[4][4], int res[4][4])
{
    register int i=0; 
    register int j=0; 
    register int k=0;

    for (i = 0; i < 4; i++) 
    {
        for (j = 0; j < 4; j++) 
        {
            res[i][j] = 0;
            
            // slow
            for (k = 0; k < 4; k++){
                res[i][j] += mat1[i][k] * mat2[k][j];
            };
        };
    };
}


// IN: matrix base.
void grInitializematrix0 (long *r)
{
// Invalid buffer.
    if ( (void*)  r == NULL ){return;}

    r[0]  = (long) 1;
    r[1]  = (long) 0;
    r[2]  = (long) 0;
    r[3]  = (long) 0;

    r[4]  = (long) 0;
    r[5]  = (long) 1;
    r[6]  = (long) 0;
    r[7]  = (long) 0;

    r[8]  = (long) 0;
    r[9]  = (long) 0;
    r[10]  = (long) 1;
    r[11]  = (long) 0;

    r[12]  = (long) 0;
    r[13]  = (long) 0;
    r[14]  = (long) 0;
    r[15]  = (long) 0;
}


void 
grSetTranslation4x4 (
    long *r,   // matrix base.
    long *_x, long *_y, long *_z )
{
// Invalid buffer.
    if ( (void*)  r == NULL ){return;}
    if ( (void*) _x == NULL ){return;}
    if ( (void*) _y == NULL ){return;}
    if ( (void*) _z == NULL ){return;}

    r[3]  = (long) *_x;
    r[7]  = (long) *_y;
    r[11] = (long) *_z;
    r[15] = (long) 1;
}


//#test
void 
grRot4x4 (
    long *r,   // matrix base.
    long *_x, long *_y, long *_z )
{
// fixed-point

    long x1=0; 
    long y1=0; 
    long z1=0;

// Invalid buffer.
    if ( (void*)  r == NULL ){return;}
    if ( (void*) _x == NULL ){return;}
    if ( (void*) _y == NULL ){return;}
    if ( (void*) _z == NULL ){return;}

    long xx = (long) *_x; 
    long yy = (long) *_y; 
    long zz = (long) *_z;

//----------------------
// x1
    x1 = 
        (long) ( (r[0] * xx) + 
                 (r[1] * yy) + 
                 (r[2] * zz) + 
                  r[3] );
    //x1 = (long) (x1 >> 32);

//----------------------
// y1
    y1 = 
        (long) ( (r[4] * xx) + 
                 (r[5] * yy) + 
                 (r[6] * zz) + 
                  r[7] );
    //y1 = (long) (y1 >> 32);

//----------------------
// z1
    z1 = 
        (long) ( (r[8]  * xx) + 
                 (r[9]  * yy) + 
                 (r[10] * zz) +
                  r[11] );
    //z1 = (long) (z1 >> 32);


  *_x = (long) x1; 
  *_y = (long) y1;
  *_z = (long) z1;
}




int scalar_product( struct gr_vec3D_d *v1, struct gr_vec3D_d *v2 )
{
// Dot product.
// The dot product describe the 
// relationship between two vectors.
// Positive: Same direction
// negative: Opposite direction
// 0:        Perpendicular.

    int scalar=0;

// Fake perpendicular.
    if( (void*) v1 == NULL ){ return 0; }
    if( (void*) v2 == NULL ){ return 0; }

    scalar  = (v1->x * v2->x);
    scalar += (v1->y * v2->y);
    scalar += (v1->z * v2->z);

    return (int) (scalar & 0xFFFFFFFF );
}


int gr_triangle_area_int (int base, int height)
{
    return (int) ((base*height) >> 1);
}


int gr_magic_volume (int x, int y, int z)
{
    return (int) (x*y*z);
}


int gr_magic_area (int x, int y, int z)
{
    int area = 
        (int) ( (2*x*y) +
                (2*y*z) +
                (2*x*z) );

    return (int) area;
}


int 
gr_find_obj_height_int ( 
    int *obj_height, int obj_distance,
    int img_height, int img_distance )
{
// #todo: This is a work in progress.
// ih/_oh      = (id/od)
// ih         = _oh*(id/od)
// ih/(id/od) = _oh

// ------------
// Razão entre a distância da imagem e a distância do objeto.
    if (obj_distance == 0){
        return -1;  //fail
    }
    int tmp = (int) (img_distance/obj_distance);

// ------------
// Altura da imagem dividida pela
// razão entre a distância da imagem e a distância do objeto.
    if (tmp==0){
        return -1;  //fail
    }
    int resOH = (int) (img_height / tmp);

// ------------
// done:
// Return the object height
// Check pointer validation

    if( (int*) obj_height == NULL){
        return -1;  //fail
    }
    
    *obj_height = (int) resOH;
    
    return 0; //ok
}

int 
gr_find_img_height_int ( 
    int obj_height, int obj_distance,
    int *img_height, int img_distance )
{
// #todo: This is a work in progress.
// _ih/oh      = (id/od)
// _ih         = oh*(id/od)

// ------------
// Razão entre a distância da imagem e a distância do objeto.
    if (obj_distance == 0){
        return -1;  //fail
    }
    int tmp = (int) (img_distance/obj_distance);

    int resIH = (int) (obj_height*tmp);

// ------------
// done:
// Return the image height
// Check pointer validation

    if( (int*) img_height == NULL){
        return -1;  //fail
    }
    
    *img_height = (int) resIH;
    
    return 0; //ok
}




// Fibonacci Series using Recursion 
// ??: slow.
int fib (int n)
{ 
    register int Copy = n;
    int a=0;
    int b=0;

    if (Copy <= 1){ return Copy; }
    
    a = fib(Copy - 1); 
    b = fib(Copy - 2);

    return (int) (a+b);
} 

/*
// print fibonacci
void __print_fib(int max);
void __print_fib(int max)
{
    int i=0;
    int a=0;
    int b=1;
    int c;
    
    if (max<0)
        return;
    
    while(a<max)
    {
        printf("%d\n,a");
        c = a+b;
        a = b;
        b = c;
    };
}
*/


void gr_scale_vec( struct gr_vec3D_d *v, int scale )
{
    if( (void*) v == NULL )
        return;

    v->x *= scale;
    v->y *= scale;
    v->z *= scale;
}



/*
 * plotCharBackbufferDrawcharTransparent:
 *     Desenha um caractere sem alterar o pano de fundo.
 *     >> no backbuffer.
 */

// #bugbug
// Nessa função estamos usando globais.
// Talvez devamos pegá-las antes e não 
// referenciá-las diretamente.

void 
plotCharBackbufferDrawcharTransparent ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c )
{

    //loop
    register int y2=0;
    register int x2=0;

    char *work_char;
    unsigned char bit_mask = 0x80;

    //int CharWidth;
    //int CharHeight;


    /*
	 * Get the font pointer.
	 *
	 * @todo:
     *     usar variavel g8x8fontAddress.
	 *     + Criar e usar uma estrutura para fonte.
	 *     + Usar o ponteiro para a fonte atual que foi carregada.
	 *     + Criar um switch para o tamanho da fonte.
	 *     isso deveria estar na inicialização do módulo char.
	 *     ...
	 */

    if ( gws_currentfont_address == 0 || 
         gcharWidth <= 0 || 
         gcharHeight <= 0 )
    {
	    //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		//gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		//gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.
		
		// #debug
		// Estamos parando para testes.
		
        printf ("gws_drawchar_transparent : Initialization fail\n");
        while(1){}
    }

    // #todo: 
    // Criar essas variáveis e definições.

    switch (gfontSize){

		//case FONT8X8:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
		    //gcharWidth = 8;
		    //gcharHeight = 8;
		    //set_char_width(8);
			//set_char_height(8);
			//break;
		
		//case FONT8X16:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
		    //gcharWidth = 8;
		    //gcharHeight = 16;
		    //set_char_width(8);
			//set_char_height(16);			
		    //break;
		 
		//#todo: 
		//Criar opções
		//...
		
		// #importante:
		// #BUGBUG
		// Se não temos um tamanho selecionado então teremos 
		// que usar o tamanho padrão.
		
        default:
		    //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		    
			//set_char_width(8);
			//set_char_height(8);	
            //gfontSize = FONT8X8;  //#todo: fução para configurar isso.

            break;
    };

// O caractere sendo trabalhado.
    work_char = 
        (void *) gws_currentfont_address + (c * gcharHeight);

// Draw

    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {

           // Put pixel. 
            if ( ( *work_char & bit_mask ) ){
 
                // IN: z,x,y,color.
                grPlot0 ( NULL, 0, x + x2, y, color ); 
            }

            // Rotate bitmask.
            bit_mask = (bit_mask >> 1);  
        };

        // Próxima linha da 8 linhas do caractere.
        y++; 
        work_char++; 
    };
}


/*
 * plotCharBackbufferDrawcharTransparentZ:
 *     Desenha um caractere sem alterar o pano de fundo.
 *     >> no backbuffer.
 */

// #bugbug
// Nessa função estamos usando globais.
// Talvez devamos pegá-las antes e não 
// referenciá-las diretamente.

// root surface?

void 
plotCharBackbufferDrawcharTransparentZ ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c,
    int z )
{

    char *work_char;
    unsigned char bit_mask = 0x80;

    int x2=0;
    int y2=0;

    //int CharWidth;
    //int CharHeight;

/*
 * Get the font pointer.
 * @todo:
 *     usar variavel g8x8fontAddress.
 *     + Criar e usar uma estrutura para fonte.
 *     + Usar o ponteiro para a fonte atual que foi carregada.
 *     + Criar um switch para o tamanho da fonte.
 *     isso deveria estar na inicialização do módulo char.
 */

    if ( gws_currentfont_address == 0 || 
         gcharWidth <= 0 || 
         gcharHeight <= 0 )
    {
	    //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		//gcharWidth = DEFAULT_CHAR_WIDTH;               //8.
		//gcharHeight = DEFAULT_CHAR_HEIGHT;             //8.
		
		// #debug
		// Estamos parando para testes.

        printf ("gws_drawchar_transparent : Initialization fail\n");
        while(1){}
    }

    // #todo: 
    // Criar essas variáveis e definições.

    switch (gfontSize){

		//case FONT8X8:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //getFontAddress(...)
		    //gcharWidth = 8;
		    //gcharHeight = 8;
		    //set_char_width(8);
			//set_char_height(8);
			//break;
		
		//case FONT8X16:
	        //gws_currentfont_address = (unsigned long) BIOSFONT8X16;    //getFontAddress(...)
		    //gcharWidth = 8;
		    //gcharHeight = 16;
		    //set_char_width(8);
			//set_char_height(16);			
		    //break;
		 
		//#todo: 
		//Criar opções
		//...
		
		// #importante:
		// #BUGBUG
		// Se não temos um tamanho selecionado então teremos 
		// que usar o tamanho padrão.
		
        default:
		    //gws_currentfont_address = (unsigned long) BIOSFONT8X8;    //ROM bios.
		    
			//set_char_width(8);
			//set_char_height(8);	
            //gfontSize = FONT8X8;  //#todo: fução para configurar isso.

            break;
    };

// O caractere sendo trabalhado.

    work_char = 
        (void *) gws_currentfont_address + (c * gcharHeight);

// Draw
// #todo
// We need a flat to invert or not.
// invert

    // ok. it works
    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {

           // Put pixel. 
            if ( ( *work_char & bit_mask ) )
            {
                // começa do fim
                // IN: z,x,y,color.
                grPlot0 ( NULL, z, x + x2, (y + gcharWidth), color ); 
            }

            // Rotate bitmask.
            bit_mask = (bit_mask >> 1);  
        };

        // Próxima linha da 8 linhas do caractere.
        //y++; 
        y--;
        work_char++; 
    };
}


// substitui cor no lfb
void grDCMono (
    struct gws_display_d *dc,
    unsigned char subpixel_quest,         //I64 quest=COLOR_TRANSPARENT,
    unsigned char subpixel_true_color,    //I64 true_color=0,
    unsigned char subpixel_false_color )  //I64 false_color=COLOR_MONO)
{

    int i=0;
    unsigned char *dst;

    struct gws_screen_d *Screen;


    printf ("grDCMono:\n");


//
// Device context
//

    if ( (void *) dc == NULL ){
        printf ("dc\n");
        return;
    }

    if (dc->used != TRUE || dc->magic != 1234 )
    {
        printf ("dc validation\n");
        return;
    }

//
// Device screen
//

    Screen = dc->device_screen;

    if ( (void*) Screen == NULL ){
        printf ("Screen\n");
        return;
    }

    if (Screen->used != TRUE || Screen->magic != 1234 ){
        printf ("Screen validation\n");
        return;
    }


    // 3 BPP
    if (Screen->bpp == 24) {
        
        dst = (unsigned char *) Screen->frontbuffer;  //dst = dc->body;
        i = (int) (Screen->height * Screen->pitch);   //i = dc->width_internal*dc->height;

        //if (i<0)
            //return;
                   
        while (i--){
            
            if ( *dst == subpixel_quest ){
                *dst++ = subpixel_true_color;
            }else{
                *dst++ = subpixel_false_color;
            };
        };
    }

    //??
    if (Screen->bpp != 24) {
        printf ("not 24bpp\n");
    }
}



// substitui cor no lfb
void grDCColorChg ( 
    struct gws_display_d *dc,
    unsigned char subpixel_src_color,
    unsigned char subpixel_dst_color )  // dst_color=COLOR_TRANSPARENT )
{

    int i=0;
    unsigned char *dst;

    struct gws_screen_d *Screen;


    printf ("grDCColorChg:\n");

// Device context

    if ( (void *) dc == NULL )
        return;

    if (dc->used != 1 || dc->magic != 1234 )
        return;    


//
// Screen
//

    Screen = dc->device_screen;

    if ( (void*) Screen == NULL )
        return;

    if (Screen->used != 1 || Screen->magic != 1234 )
        return;    


    if (Screen->bpp == 24) {    
        
        dst = (unsigned char *) Screen->frontbuffer;
        i = (int) (Screen->height * Screen->pitch);
        
        while (i--){
            
            if (*dst == subpixel_src_color){
                *dst++ = subpixel_dst_color;
            }else{
                dst++;
            };
        };
    }
}


// Bézier curve
// This program example plots a quadratic Bézier curve 
// limited to gradients without sign change.
// IN: ?? #todo: explain the input values.
// IN: ponto inicial, ?? , ponto final.
void 
plotQuadBezierSeg ( 
    int x0, int y0, int z0, 
    int x1, int y1, int z1,
    int x2, int y2, int z2, 
    unsigned long color )
{
    int  sx = x2-x1, sy = y2-y1;
    long xx = x0-x1, yy = y0-y1, xy;         /* relative values for checks */
    //double dx, dy, err, cur = xx*sy-yy*sx;                    /* curvature */
    
    //loop
    register long dx=0; 
    register long dy=0;
    
    long err=0; 
    long cur = xx*sy-yy*sx;


    /* sign of gradient must not change */
    //assert(xx*sx <= 0 && yy*sy <= 0);  

    if ( xx*sx <= 0 && 
         yy*sy <= 0 )
    {
        printf("plotQuadBezierSeg: [TODO] assert\n");
        exit(1);
    }

     /* begin with longer part */
    if (sx*(long)sx+sy*(long)sy > xx*xx+yy*yy)
    {  
        //swap P0 P2
        x2 = x0; 
        x0 = sx+x1; 
        y2 = y0; 
        y0 = sy+y1; 
        cur = -cur;  
    }  
    
    if (cur != 0) {                                    /* no straight line */

    xx += sx; xx *= sx = x0 < x2 ? 1 : -1;           /* x step direction */
    yy += sy; yy *= sy = y0 < y2 ? 1 : -1;           /* y step direction */
    xy = 2*xx*yy; xx *= xx; yy *= yy;          /* differences 2nd degree */
    if (cur*sx*sy < 0) {                           /* negated curvature? */
      xx = -xx; yy = -yy; xy = -xy; cur = -cur;
    }
    
    //dx = 4.0*sy*cur*(x1-x0)+xx-xy;             /* differences 1st degree */
    //dy = 4.0*sx*cur*(y0-y1)+yy-xy;

    dx = 4*sy*cur*(x1-x0)+xx-xy;             /* differences 1st degree */
    dy = 4*sx*cur*(y0-y1)+yy-xy;
    
    xx += xx; yy += yy; err = dx+dy+xy;                /* error 1st step */    
    do {                              
      
      /* plot curve */
      //setPixel(x0,y0); 
      grPlot0( NULL, x0, y0, z0, color );

      if (x0 == x2 && y0 == y2) return;  /* last pixel -> curve finished */
      y1 = 2*err < dx;                  /* save value for test of y step */
      if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
      if (    y1    ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
    
    } while (dy < dx );           /* gradient negates -> algorithm fails */
    
    
    }

    /* plot remaining part to end */
    //plotLine(x0,y0, x2,y2);   
    plotLine3d (
        NULL,
        x0,y0,z0, 
        x2,y2,z2, 
        color ); 
}


/*
 #todo
 substitui uma cor por outra dentro de uma janela.
void 
xxxFindReplaceColor( 
    struct gws_window_d *window, 
    unsigned long color1, 
    unsigned long color2);
void 
xxxFindReplaceColor( 
    struct gws_window_d *window, 
    unsigned long color1, 
    unsigned long color2)
{
}
*/

int servicepixelBackBufferPutpixel(void)
{
    unsigned long *message_address = (unsigned long *) &__buffer[0];
    unsigned long x,y,color,rop;

    x = message_address[4];
    y = message_address[5];
    color = (unsigned int) message_address[6];
    //rop = message_address[?];

    if (x<0){ return -1; }
    if (y<0){ return -1; }

    grBackBufferPutpixel(color,x,y,0);

    return 0;
}


//#todo: Explain it better.
unsigned int 
interpolate_color(
    unsigned int color1, 
    unsigned int color2, 
    unsigned int fraction )
{
    unsigned int final_color=0;

    unsigned char r1 = (unsigned char) (color1 >> 16) & 0xff;
    unsigned char r2 = (unsigned char) (color2 >> 16) & 0xff;
    unsigned char g1 = (unsigned char) (color1 >> 8) & 0xff;
    unsigned char g2 = (unsigned char) (color2 >> 8) & 0xff;
    unsigned char b1 = (unsigned char) color1 & 0xff;
    unsigned char b2 = (unsigned char) color2 & 0xff;

    final_color = 
        (unsigned int) (    
        (unsigned int) ( (r2 - r1) * fraction + r1 ) << 16 | 
        (unsigned int) ( (g2 - g1) * fraction + g1 ) <<  8 | 
        (unsigned int) ( (b2 - b1) * fraction + b1 )
    );
    
    return (unsigned int) final_color;
}

//??
//#todo: Explain it better.
unsigned int invert_color(unsigned int color)
{
    unsigned int Color = (unsigned int) (color ^ 0x00FFFFFF);

    return (unsigned int) Color;
}


//
// End.
//


