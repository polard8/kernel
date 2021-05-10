/*
 * File: grprim.c 
 * 
 *     Primitives.
 *
 * History:
 *     2020 - Created by Fred Nora.
 */


#include <gws.h>


// See:
// https://wiki.osdev.org/3D_Renderer_Basics
// http://members.chello.at/easyfilter/bresenham.html
// http://math.hws.edu/graphicsbook/c2/s3.html
// http://math.hws.edu/graphicsbook/index.html
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



/*
 ********************************** 
 * grInit:
 * 
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
    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();


    gwssrv_debug_print ("grInit:\n");

    if ( w == 0 || h == 0 ){
        printf ("grInit: [FAIL] w h\n");
        exit(1);
    }

    //HotSpotX = (w/2);
    //HotSpotY = (h/2);
    HotSpotX = (w>>1);
    HotSpotY = (h>>1);

//
// == Camera ==========
//

    gwssrv_debug_print ("grInit: camera\n");
        
    // initialize the current camera.
    camera_initialize();
    
    
    // change some attributes for the current camera.
    camera ( 
        -40, -40, 0,     // position vector
        -40,  40, 0,     // upview vector
         10,  10, 10 );  // lookat vector


//
// == Projection =========
//

    gwssrv_debug_print ("grInit: projection\n");
    
    // initialize the current projection.
    projection_initialize();

    // change the view for the current projection.
    view(0,40);
     
    // ...

    gwssrv_debug_print ("grInit: done\n");
    return 0;
}



int camera_initialize(void)
{
    CurrentCamera = (void *) malloc ( sizeof( struct gr_camera_d ) );
    
    if ( (void*) CurrentCamera == NULL )
    {
        printf("camera_initialize fail\n");
        exit(1);
    }
    
    // position
    CurrentCamera->position.x = -40;
    CurrentCamera->position.y = -40;
    CurrentCamera->position.z = 0;

    // upview
    CurrentCamera->upview.x = -40;
    CurrentCamera->upview.y = +40;
    CurrentCamera->upview.z = 0;

    // lookat. target point origin.
    CurrentCamera->lookat.x = 0;
    CurrentCamera->lookat.y = 0;
    CurrentCamera->lookat.z = 0;
    
    
    CurrentCamera->projection = NULL;
    
    return 0;
}

int 
camera ( 
    int x, int y, int z,
    int xUp, int yUp, int zUp,
    int xLookAt, int yLookAt, int zLookAt )
{
        
    if ( (void*) CurrentCamera == NULL )
    {
        printf("camera: fail\n");
        return -1;
        //exit(1);
    }
    
    // position
    CurrentCamera->position.x = x;
    CurrentCamera->position.y = y;
    CurrentCamera->position.z = z;

    //upview
    CurrentCamera->upview.x = xUp;
    CurrentCamera->upview.y = yUp;
    CurrentCamera->upview.z = zUp;

    //lookat. target poit origin.
    CurrentCamera->lookat.x = xLookAt;
    CurrentCamera->lookat.y = yLookAt;
    CurrentCamera->lookat.z = zLookAt;
    
    return 0;
}



int projection_initialize(void)
{


    CurrentProjection = (void *) malloc ( sizeof( struct gr_projection_d ) );
    
    if ( (void*) CurrentProjection == NULL ){
        printf("projection_initialize fail\n");
        exit(1);
    }

    // #todo: Perspective or orthogonal
    CurrentProjection->type = 1; 

    // ??
    CurrentProjection->zNear   =  0;
    CurrentProjection->zFar    = 40;
    CurrentProjection->zRange  = (CurrentProjection->zFar - CurrentProjection->zNear);

    //CurrentProjection->angle_of_view = ?;
    //CurrentProjection->ar = ?;
    //CurrentProjection->frustrum_apex = ?;
    //CurrentProjection->frustrum_view = ?;

    //...
 
    return 0;
}


// Changing the view for the current projection.
int view (int near, int far)
{
    if ( (void*) CurrentProjection == NULL )
    {
        printf("view: fail\n");
        return -1;
        //exit(1);
    }
    CurrentProjection->zNear  = near;
    CurrentProjection->zFar   = far;
    CurrentProjection->zRange = (CurrentProjection->zFar - CurrentProjection->zNear);
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



/*
 ******************************* 
 * grPlot0:
 *      plot pixel.
 *      Plot into a normalized screen. kinda.
 */

// low level plot.
// History:
//     2020 - Created by Fred Nora.

// window ?
// Essa rotina pode pintar em qualquer posição 
// da tela do dispositivo. 
// Com origem no centro da tela.

// Aceitamos valores negativos e positivos.
// O limite máximo será modular.

// 3D fullscreen, origin in center.


int 
grPlot0 ( 
    struct gws_window_d *clipping_window,   
    int z, 
    int x, 
    int y, 
    unsigned long color )
{

// #todo
// We can use a 'clipping window' and draw only inside this window.
// If the clipping window is NULL, so we need to use the root window.

    // #todo
    // This is a work in progress


    // Draw flag.
    int Draw = TRUE;
    int UseClipping = FALSE;


    int UsingDepthBuffer = FALSE;
    
    int UsingAlphaBlending = FALSE;

    // left hand orientation
    // z+ on top/right corner.
    
    int FixOrientation = TRUE;



    // #todo
    // We need a z-buffer or (depth buffer)
    // it is used to depth testing.
    // it discards some unnecessary covered plots. 
    
    // Normalized Device Coordinates (NDC)
    // We are using or own ndc style.
    // Maybe it is different for diferent systens.
    
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
    
    
    unsigned long zBaseX=0;
    unsigned long zBaseY=0;

     // #bugbug
     // Precisa ser 'int', nao podemos enviar 
     // valores negativos para putpixel.
     int X=0;
     int Y=0;


//
// The clippping window.
//

    struct gws_window_d *w;

    // #todo
    // If the clipping window is invalid, 
    // so we're gonna use the root window.
    // #todo:
    // Maybe we need to use the device context structure,
    // or something like that.
    
    UseClipping = FALSE;
    
    if ( (void*) clipping_window != NULL )
    {
        if ( clipping_window->used  == TRUE && 
             clipping_window->magic == 1234 )
        {
            UseClipping = TRUE;
            w = (struct gws_window_d *) clipping_window;
        }
    }


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


    // z negativo
    //  _
    //   |

    if (z < 0)
    {
        // z é módulo para todos os casos em que z é menor que 0.
        z = abs(z);

        // positivo, para direita.
        // Desloca a base x para esquerda, onde fica o z negativo
        if (x >= 0 )
        {
            X = (unsigned long) ( (unsigned long)HotSpotX  + (unsigned long)x);
        }

        // negativo, para esquerda.
        // Desloca a base x para esquerda, onde fica o z negativo
        if (x < 0 )
        {
            x = abs(x); 
            X = (unsigned long) (  (unsigned long)HotSpotX - (unsigned long)x );
        }

        // positivo, para cima.
        // Desloca a base y para baixo, onde fica o z negativo
        if ( y >= 0 )
        {
            Y = (unsigned long) ( (unsigned long)HotSpotY - (unsigned long)y );
        }

        // negativo, para baixo
        // Desloca a base y para baixo, onde fica o z negativo
        if ( y < 0 )
        {
            y = abs(y);
            Y = (unsigned long) ( (unsigned long) HotSpotY + (unsigned long) y );
        }

        if (FixOrientation == TRUE){
            X = ( (unsigned long) X - (unsigned long) z );
            Y = ( (unsigned long) Y + (unsigned long) z );
        }
        
        //if (Draw == FALSE){ return -1; }
        goto draw;
    }


    // z maior ou igual a zero.
    //    |
    //    ----
    //
    if (z >= 0)
    {
        // z é positivo para todos os casos onde z é maior igual a 0.
        
        // positivo, para direita.
        // Desloca a base x para direita, onde fica o z positivo
        if (x >= 0 )
        {
            X = (unsigned long) ( (unsigned long) HotSpotX + (unsigned long) x );
        }
        
        // negativo, para esquerda.
        // Desloca a base x para direita, onde fica o z positivo
        if (x < 0 )
        {
            x = abs(x);   
            X = (unsigned long) ( (unsigned long)HotSpotX - (unsigned long)x  );
        }

        // positivo, para cima.
        // Desloca a base y para cima, onde fica o z positivo
        if ( y >= 0 )
        {
            Y = (unsigned long) ( (unsigned long)HotSpotY - (unsigned long)y );
        }

        // negativo, para baixo
        // Desloca a base y para cima, onde fica o z positivo
        if ( y < 0 )
        {
            y = abs(y);
            Y = (unsigned long) ( (unsigned long)HotSpotY + (unsigned long)y );
        }

        if (FixOrientation == TRUE){
            X = ( (unsigned long) X + (unsigned long) z );
            Y = ( (unsigned long) Y - (unsigned long) z );
        }
        
        //if (Draw == FALSE){ return -1; }
        goto draw;
    }

    //
    // fail
    //
    
    Draw = FALSE;
    
    return -1;

    //
    // draw
    //
    
draw:
    
    //
    // Clipping
    //
    
    // #todo: 
    // We need to check the window limits
    // if we are drawing inside a given window.

    // Checking the device screen limits.
        
    if ( 0 <= X < DeviceScreen->width && 
         0 <= Y < DeviceScreen->height )
    {
        if (Draw == TRUE)
        {
            // #bugbug
            // Já fizemos isso logo acima.
            
            if (X<0){ return -1; }
            if (Y<0){ return -1; }
            
            if ( UsingAlphaBlending == TRUE )
            {
                // #todo
                // Get the color and modify it.
                
                //color = get??()
            }
            
            // Se NÃO temos uma janela válida.
            if ( UseClipping == FALSE ){
                // device screen
                // 2D, No clipping or transformation.
                pixelBackBufferPutpixel ( color, X, Y ); 
            }

            // Se temos uma janela válida.
            if ( UseClipping == TRUE ){
                if ( X >= w->left  &&
                     X <= w->right &&
                     Y >= w->top  &&
                     Y <= w->bottom )
                 {
                     pixelBackBufferPutpixel ( color, X, Y ); 
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
        return -1;
    }
    
    // fail 
    
    return -1;
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



/*
 ************************************************ 
 * plotLine3d: 
 * 
 */
 
// Bresenham in 3D
// The algorithm could be extended to three (or more) dimensions.

void 
plotLine3d (
    int x0, int y0, int z0, 
    int x1, int y1, int z1, 
    unsigned long color )
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

        grPlot0 ( NULL, z0, x0, y0, color );
     
        if (i-- == 0) { break; }
        x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; }
        y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; }
        z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; }
    };
}


// #todo
// plot line given two colors.
// interpolation ?

void 
plotLine3d2 (
    int x0, int y0, int z0, unsigned long color1,
    int x1, int y1, int z1, unsigned long color2, int flag )
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
    }
}




// The upper-left corner and lower-right corner. 
void
rectangle (
    int left, int top, 
    int right, int bottom,
    unsigned long color )
{

    // cima
    plotLine3d ( left, top, 0, right, top, 0, color );
    // baixo
    plotLine3d ( left, bottom, 0, right,bottom, 0, color );
    // esquerda
    plotLine3d ( left, top, 0, left, bottom, 0, color );
    // direita
    plotLine3d ( right, top, 0, right, bottom, 0, color );
}


// The upper-left corner and lower-right corner. 
void
rectangleZ (
    int left, int top, 
    int right, int bottom,
    unsigned long color,
    int z )
{
    // cima
    plotLine3d ( left, top,  z, right, top, z, color );
    // baixo
    plotLine3d ( left, bottom, z, right,bottom, z, color );
    // esquerda
    plotLine3d ( left, top, z, left, bottom, z, color );
    // direita
    plotLine3d ( right,  top, z, right, bottom, z, color );
}


void rectangleZZ ( struct gr_rectangle_d *rect )
{
    if ( (void*) rect == NULL )
        return -1;


      // points
      //  0  1
      //  3  2

     //#bugbug
     // We need to create a routine with colors in both points.

     // cima
     //plotLine3d ( left, top,  z, right, top, z, color );
     plotLine3d2 ( rect->p[0].x, rect->p[0].y, rect->p[0].z, rect->p[0].color,
                   rect->p[1].x, rect->p[1].y, rect->p[1].z, rect->p[1].color, 0 );

     // baixo
     //plotLine3d ( left, bottom, z, right,bottom, z, color );
     plotLine3d2 ( rect->p[3].x, rect->p[3].y, rect->p[3].z, rect->p[3].color,
                   rect->p[2].x, rect->p[2].y, rect->p[2].z, rect->p[2].color, 0 );

     // esquerda
     //plotLine3d ( left, top, z, left, bottom, z, color );
     plotLine3d2 ( rect->p[0].x, rect->p[0].y, rect->p[0].z, rect->p[0].color,
                   rect->p[3].x, rect->p[3].y, rect->p[3].z, rect->p[3].color, 0 ); 
     // direita
     //plotLine3d ( right,  top, z, right, bottom, z, color );
     plotLine3d2 ( rect->p[1].x, rect->p[1].y, rect->p[1].z, rect->p[1].color,
                   rect->p[2].x, rect->p[2].y, rect->p[2].z, rect->p[2].color, 0 );
}



// Rectangle rasterization using lines.
// It applies only on few cases.
// The upper-left corner and lower-right corner.
 
void
ras_rectangleZ (
    int left, int top, int z0,
    int right, int bottom, int z1,
    unsigned long color )
{
    register int Line=0;

    // #todo
    // No caso de inclinações da linha,
    // precisamos considerar que temos dois 'top' diferentes.
    // precisamos receber mais paâmetros de função,
    // ou criarmos uma outra funções que tenha tais parâmetros,
    // ficando essa somente para retâmgulos não inclinados.

    // Começa com a linha de cima.
    for ( Line=top; Line >= bottom; Line-- )
    {
        // IN: 
        // x0,y0,z0, x1,y1,z1, color.
        plotLine3d ( 
            left,  Line, z0, 
            right, Line, z1, 
            color );
    };
}


// Scaling: Inflate cube.
int xxxInflateCubeZ ( struct gr_cube_d *cube, int value )
{

    if ( (void*) cube == NULL ){
        return -1;
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
int xxxDeflateCubeZ ( struct gr_cube_d *cube, int value )
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



// Triangle.
int xxxTriangleZ ( struct gr_triandle_d *triangle )
{

    if ( (void*) triangle == NULL ){
        return -1;
    }

    // Circular, sentido horario, começando pelo ponto de cima.

    plotLine3d (
        triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
        triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
        triangle->p[1].color );

    plotLine3d (
        triangle->p[1].x, triangle->p[1].y, triangle->p[1].z, 
        triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
        triangle->p[2].color );

    plotLine3d (
        triangle->p[2].x, triangle->p[2].y, triangle->p[2].z, 
        triangle->p[0].x, triangle->p[0].y, triangle->p[0].z, 
        triangle->p[0].color );

    return 0;
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


int xxxCubeZ ( struct gr_cube_d *cube )
{
    int h=0;
    int d=0;
    int i=0;

    // #todo
    // Maybe we will receive a function parameter for that.
    
    int UseRasterization = TRUE;


    if ( (void*) cube == NULL ){
        return -1;
    }


    // #todo
    // Temos que rever a forma em que estamos usado os parâmetros
    // para pintarmos o objeto cubo.
    // Tudo aqui ainda está bem improvisado.

    // north
    // Primeiro desenha o north porque ele sera sobreposto 
    // pelo sul nessa camera.

    // -- back face ----------------------------------------
    // north - back
    // Retângulo com os 4 pontos de trás.
    plotLine3d (  // cima
        cube->p[4].x, cube->p[4].y, cube->p[4].z, 
        cube->p[5].x, cube->p[5].y, cube->p[5].z, cube->p[4].color );
    plotLine3d (  // direita
        cube->p[5].x, cube->p[5].y, cube->p[5].z, 
        cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[5].color );
    plotLine3d (  // baixo 
        cube->p[7].x, cube->p[7].y, cube->p[7].z, 
        cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[7].color );
    plotLine3d (  // esquerda
        cube->p[4].x, cube->p[4].y, cube->p[4].z, 
        cube->p[7].x, cube->p[7].y, cube->p[7].z, cube->p[4].color );

    // #improviso: 
    // Isso é um teste de rasterização, não usando triangulo.
    // #todo:
    // Temos que criar a tasterização via retângulos.
    // Isso só funciona para retângulos não inclinados.

    // p4 = left top 
    // p6 = right bottom
    if (UseRasterization == TRUE){
    ras_rectangleZ ( 
        cube->p[4].x, cube->p[4].y, cube->p[4].z, 
        cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[4].color  );
    }

    //=================================================================
    
    // -- top face ----------------------------------------
        
    // 1st line 
    plotLine3d (cube->p[0].x, cube->p[0].y, cube->p[0].z, 
                cube->p[4].x, cube->p[4].y, cube->p[4].z, cube->p[0].color );
    // 2nd line
    plotLine3d (cube->p[1].x, cube->p[1].y, cube->p[1].z, 
                cube->p[5].x, cube->p[5].y, cube->p[5].z, cube->p[1].color );

    // -- bottom face ----------------------------------------
    
    // 1rd line
    plotLine3d (cube->p[2].x, cube->p[2].y, cube->p[2].z, 
                cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[2].color );
    // 2th line 
    plotLine3d (cube->p[3].x, cube->p[3].y, cube->p[3].z, 
                cube->p[7].x, cube->p[7].y, cube->p[7].z, cube->p[3].color );

    //=================================================================

    // left ok
    // Isso só funciona para retângulos não inclinados.
    // p0 = left top da frente 
    // p7 = left bottom de trás
    if (UseRasterization == TRUE){
    ras_rectangleZ ( 
        cube->p[0].x, cube->p[0].y, cube->p[0].z, 
        cube->p[7].x, cube->p[7].y, cube->p[7].z, cube->p[0].color  );
    }

    // right ok
    // Isso só funciona para retângulos não inclinados.
    // p1 = right top da frente 
    // p7 = right bottom de trás
    if (UseRasterization == TRUE){
    ras_rectangleZ ( 
        cube->p[1].x, cube->p[1].y, cube->p[1].z, 
        cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[1].color  );
    }

    // tampa de baixo
    //bottom fail
    //ras_rectangleZ ( 
    //    cube->p[3].x, cube->p[3].y, cube->p[3].z, 
    //    cube->p[6].x, cube->p[6].y, cube->p[6].z,
    //    cube->p[2].color  );

    // tampa de cima.
    // top fail
    //ras_rectangleZ ( 
    //    cube->p[4].x, cube->p[4].y, cube->p[4].z, 
    //    cube->p[0].x, cube->p[0].y, cube->p[0].z,
    //    cube->p[3].color  );


    // -- front face ----------------------------------------
    // south - front
    // Retângulo com os 4 pontos da frente.
    plotLine3d (  // cima
        cube->p[0].x, cube->p[0].y, cube->p[0].z, 
        cube->p[1].x, cube->p[1].y, cube->p[1].z, cube->p[0].color );
    plotLine3d (  // direita
        cube->p[1].x, cube->p[1].y, cube->p[1].z, 
        cube->p[2].x, cube->p[2].y, cube->p[2].z, cube->p[1].color );
    plotLine3d (  // baixo
        cube->p[3].x, cube->p[3].y, cube->p[3].z,
        cube->p[2].x, cube->p[2].y, cube->p[2].z, cube->p[3].color );
    plotLine3d (  // esquerda
        cube->p[0].x, cube->p[0].y, cube->p[0].z, 
        cube->p[3].x, cube->p[3].y, cube->p[3].z, cube->p[0].color );

    // #improviso: 
    // Isso é um teste de rasterização, não usando triangulo.
    // #todo:
    // Temos que criar a tasterização via retãngulos.
    // Isso só funciona para retângulos não inclinados.

    // p0 = left top 
    // p2 = right bottom
    if (UseRasterization == TRUE){
    ras_rectangleZ (  
        cube->p[0].x, cube->p[0].y, cube->p[0].z, 
        cube->p[2].x, cube->p[2].y, cube->p[2].z, cube->p[0].color );
    }
}



// sevice 2041
// Called by gwsProcedure.
int serviceGrCubeZ(void)
{
    // #todo:
    // Vamos pegar os vertices do cubo nos argumentos
    // e completar a estrtutura local.
    // entao passamos o endereço da estrutura para a funçao helper.

    unsigned long *message_address = (unsigned long *) &__buffer[0];
    
    
    gwssrv_debug_print("serviceGrCubeZ: [2041]\n");

    struct gr_cube_d cube;

    // Circular, sentido horário.

    // south
    cube.p[0].x     = message_address[10];
    cube.p[0].y     = message_address[11];
    cube.p[0].z     = message_address[12];
    cube.p[0].color = message_address[13];

    cube.p[1].x     = message_address[14];
    cube.p[1].y     = message_address[15];
    cube.p[1].z     = message_address[16];
    cube.p[1].color = message_address[17];

    cube.p[2].x     = message_address[18];
    cube.p[2].y     = message_address[19];
    cube.p[2].z     = message_address[20];
    cube.p[2].color = message_address[21];

    cube.p[3].x     = message_address[22];
    cube.p[3].y     = message_address[23];
    cube.p[3].z     = message_address[24];
    cube.p[3].color = message_address[25];

    // north
    cube.p[4].x     = message_address[26];
    cube.p[4].y     = message_address[27];
    cube.p[4].z     = message_address[28];
    cube.p[4].color = message_address[29];

    cube.p[5].x     = message_address[30];
    cube.p[5].y     = message_address[31];
    cube.p[5].z     = message_address[32];
    cube.p[5].color = message_address[33];

    cube.p[6].x     = message_address[34];
    cube.p[6].y     = message_address[35];
    cube.p[6].z     = message_address[36];
    cube.p[6].color = message_address[37];

    cube.p[7].x     = message_address[38];
    cube.p[7].y     = message_address[39];
    cube.p[7].z     = message_address[40];
    cube.p[7].color = message_address[41];

    // #test
    // Temos que passar corretamente o endereço da estrutura.

    xxxCubeZ ( (struct gr_cube_d *) &cube );

    return 0;
}


// sevice 2042
int serviceGrRectangle(void)
{
    // #todo:
    // Vamos pegar os vertices do cubo nos argumentos
    // e completar a estrtutura local.
    // entao passamos o endereço da estrutura para a funçao helper.

    unsigned long *message_address = (unsigned long *) &__buffer[0];
    
    
    gwssrv_debug_print("serviceGrRectangle: [2042]\n");
    
    struct gr_rectangle_d rect;
   
    //south     
    rect.p[0].x = message_address[10];
    rect.p[0].y = message_address[11];
    rect.p[0].z = message_address[12];
    rect.p[0].color = message_address[13];
        
    rect.p[1].x = message_address[14];
    rect.p[1].y = message_address[15];
    rect.p[1].z = message_address[16];
    rect.p[1].color = message_address[17];
        
    rect.p[2].x = message_address[18];
    rect.p[2].y = message_address[19];
    rect.p[2].z = message_address[20];
    rect.p[2].color = message_address[21];

    rect.p[3].x = message_address[22];
    rect.p[3].y = message_address[23];
    rect.p[3].z = message_address[24];
    rect.p[3].color = message_address[25];
   
    //#test
    //Temos que passar corretamente o endereço da estrutura.
    rectangleZZ ( (struct gr_rectangle_d *) &rect );
   
    gwssrv_debug_print("serviceGrRectangle: [2042] DONE << \n");
    
    return 0;
}




//Circle
//This is an implementation of the circle algorithm.
// ?? what means 'm' ???
void 
plotCircle ( 
    int xm, 
    int ym, 
    int r, 
    unsigned long color )
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
   


// ?? what means 'm' ???
void 
plotCircleZ ( 
    int xm, 
    int ym, 
    int r, 
    unsigned long color, 
    int z )
{

    /* II. Quadrant */ 
   //int x = -r, y = 0, err = 2-2*r; 
   
    //loop
    register int x = -r;
   
    int y = 0;
    int err =  (2-(2*r));

    do {
      
      //setPixel(xm-x, ym+y); /*   I. Quadrant */
      //setPixel(xm-y, ym-x); /*  II. Quadrant */
      //setPixel(xm+x, ym-y); /* III. Quadrant */
      //setPixel(xm+y, ym+x); /*  IV. Quadrant */
      
      grPlot0 ( NULL, z, xm-x, ym+y, color);
      grPlot0 ( NULL, z, xm-y, ym-x, color);
      grPlot0 ( NULL, z, xm+x, ym-y, color);
      grPlot0 ( NULL, z, xm+y, ym+x, color);

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
 ********************************************************
 * noraDrawingStuff: 
 *    Lot of dots in the right place. (prime stuff)
 *    2020 - Created by Fred Nora. 
 */

void noraDrawingStuff(void)
{
    register int x=0;
    register int y=0;

    // colunas.
    for (x=0; x< SavedX; x++)
    {
        for (y=0; y<SavedY; y++)
        {
            if ( x != 0 ){
                if ( (y % x) == 0 ){
                    pixelBackBufferPutpixel ( COLOR_BLACK, x, y ); 
                }
            }
        };
        
        if ( x >= SavedY ) { break; }
    };
}

/*
 ********************************************************
 * noraDrawingStuff3: 
 *    Lot of dots in the right place. (prime stuff)
 *    2020 - Created by Fred Nora. 
 */

void noraDrawingStuff3 (int x, int y, int z)
{
    register int _x=0;
    register int _y=0;
    register int _z = z;

    //int limitX = SavedX/2;
    //int limitY = SavedY/2;

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


void multiply4 (int mat1[][4], int mat2[][4], int res[][4])
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


// function to multiply two matrices
void 
multiplyMatrices (
    int  first[][10],
    int second[][10],
    int result[][10],
    int r1, int c1,   // rows and columns for the first matrix
    int r2, int c2,   // rows and columns for the second 
    int rr, int cr)
{

   register int i=0;
   register int j=0;
   register int k=0;


   // Initializing elements of matrix mult to 0.
   for (i = 0; i < rr; ++i) 
   {
      for (j = 0; j < cr; ++j){  result[i][j] = 0;  };
   };


   /*
   // Multiplying first and second matrices and storing it in result
   for (i = 0; i < r1; ++i) 
   {
      for (j = 0; j < c2; ++j) 
      {
         for ( k = 0; k < c1; ++k) 
         {
            result[i][j] += first[i][k] * second[k][j];
         }
      }
   }
   */

    for (i = 0; i < r1; i++) 
    {
        for (j = 0; j < c2; j++) 
        {
            result[i][j] = 0;
            
            //slow
            for (k = 0; k < c1; k++){
                result[i][j] += first[i][k] * second[k][j];
            };
        };
    };
    
}


// Fibonacci Series using Recursion 
int fib (int n){ 

    register int Copy = n;
    
    int a=0;
    int b=0;

    if (Copy <= 1){ return Copy; }
    
    a = fib(Copy - 1); 
    b = fib(Copy - 2);

    return (int) (a+b);
} 



/*
 ******************************************************
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

    work_char = (void *) gws_currentfont_address + (c * gcharHeight);


    //
    // Draw.
    //

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
 ******************************************************
 * plotCharBackbufferDrawcharTransparentZ:
 *     Desenha um caractere sem alterar o pano de fundo.
 *     >> no backbuffer.
 */

// #bugbug
// Nessa função estamos usando globais.
// Talvez devamos pegá-las antes e não 
// referenciá-las diretamente.

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

    work_char = (void *) gws_currentfont_address + (c * gcharHeight);


    //
    // Draw.
    //
    
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

    // Device context
    if ( (void *) dc == NULL )
    {
        printf ("dc\n");
        return;
     }

    if (dc->used != 1 || dc->magic != 1234 )
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

    if (Screen->used != 1 || Screen->magic != 1234 ){
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




//Bézier curve
//This program example plots a quadratic Bézier curve limited to gradients without sign change.

void 
plotQuadBezierSeg ( 
    int x0, int y0, int z0, 
    int x1, int y1, int z1,
    int x2, int y2, int z2, unsigned long color )
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
        x0,y0,z0, 
        x2,y2,z2, 
        color ); 
}



//
// End.
//


