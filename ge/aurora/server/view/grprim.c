/*
 * File: grprim.c 
 * 
 *     Primitives.
 * 
 * 
 * History:
 *     2020 - Created by Fred Nora.
 */



#include <gws.h>


// See:
// https://wiki.osdev.org/3D_Renderer_Basics
// http://members.chello.at/easyfilter/bresenham.html
// ...


// ====
/*
 * Transformations: 
 *     Ex: Scaling, translation and rotation ...
 * 
 */

// =============================================================
// #projection:
// For orthographics projection there is no scaling factor.
// For perspective, we do have scaling.


static unsigned long HotSpotX=0;
static unsigned long HotSpotY=0;


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

    if ( w == 0 || h == 0 ){
        printf ("grInit: [FAIL] w h\n");
        exit(1);
    }

    HotSpotX = (w/2);
    HotSpotY = (h/2);
    
    // ...

    return 0;
}





/*
 ******************************* 
 * grPlot0:
 *      Plot into a normalized screen. kinda.
 */

// low level plot.
// History:
//     2020 - Created by Fred Nora.


int grPlot0 (int z, int x, int y, unsigned long color){

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

    unsigned long X=0;
    unsigned long Y=0;



    // #debug
    if ( (void *) DeviceScreen == NULL ){
        printf("grPlot0: DeviceScreen\n");
        exit(1);
    }


    // z negativo
    if (z < 0)
    {
        //positivo, para direita.
        if (x >= 0 )
        {
            z = abs(z);
            zBaseX = (unsigned long) (HotSpotX - (unsigned long) z);
            
            X = (unsigned long) (zBaseX + (unsigned long) x);
        }
        
        // negativo, para esquerda.
        if (x < 0 )
        {
            z = abs(z);
            zBaseX = (unsigned long) (HotSpotX - (unsigned long) z);
            x = abs(x);   
            X = (unsigned long) (zBaseX - (unsigned long) x);
        }

        //positivo, para cima.
        if ( y >= 0 )
        {
            z = abs(z);
            zBaseY = (unsigned long) (HotSpotY + (unsigned long) z);
            
            Y = (unsigned long) (zBaseY - (unsigned long) y); 
        }

        // negativo, para baixo
        if ( y < 0 )
        {
            z = abs(z);
            zBaseY = (unsigned long) (HotSpotY + (unsigned long) z);
            y = abs(y);
            Y = (unsigned long) (zBaseY + (unsigned long) y);           
        }
        
        // ??
        // Device screen.
        // #todo: 
        // In the future we will have a situation when we are plotting
        // inside a valid screen, inside a window. and the 'origin'
        // will be in the center of the window and not in the center 
        // of the device screen. 
        
        if ( 0 <= X < DeviceScreen->width && 
             0 <= Y < DeviceScreen->height )
        {
            pixelBackBufferPutpixel ( color, X, Y ); 
            return 0;
        }
        return -1;
    }
    
    
    // z maior que zero.
    if (z >= 0)
    {
         
        //positivo, para direita.
        if (x >= 0 )
        {
            zBaseX = (unsigned long) (HotSpotX + (unsigned long) z);
            
            X = (unsigned long) (zBaseX + (unsigned long) x);
        }
        
        // negativo, para esquerda.
        if (x < 0 )
        {
            zBaseX = (unsigned long) (HotSpotX + (unsigned long) z);
            x = abs(x);   
            X = (unsigned long) (zBaseX - (unsigned long) x);
        }

        //positivo, para cima.
        if ( y >= 0 )
        {
            zBaseY = (unsigned long) (HotSpotY - (unsigned long) z);
            
            Y = (unsigned long) (zBaseY - (unsigned long) y); 
        }

        // negativo, para baixo
        if ( y < 0 )
        {
            zBaseY = (unsigned long) (HotSpotY - (unsigned long) z);
            y = abs(y);
            Y = (unsigned long) (zBaseY + (unsigned long) y);           
        }

        // ??
        // Device screen.
        // #todo: 
        // In the future we will have a situation when we are plotting
        // inside a valid screen, inside a window. and the 'origin'
        // will be in the center of the window and not in the center 
        // of the device screen. 

        if ( 0 <= X < DeviceScreen->width && 
             0 <= Y < DeviceScreen->height )
        {
            pixelBackBufferPutpixel ( color, X, Y );  
            return 0;
        }
        return -1;
    }

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
    
    grPlot0 ( 
        (int) z, (int) x, (int) y, 
        (unsigned long) color );


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
   int i = dm;
   
    // x1 = y1 = z1 = dm/2; /* error offset */
 
    x1 = (dm >> 1);
    y1 = x1;
    z1 = x1;
 
 
    for (;;) {  /* loop */

      grPlot0 ( z0, x0, y0, color);
      
      if (i-- == 0) break;
      x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; } 
      y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; } 
      z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; } 
   }
}


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
    int i = dm;
   
    // x1 = y1 = z1 = dm/2; /* error offset */
 
    x1 = (dm >> 1);
    y1 = x1;
    z1 = x1;
    
    
    //nothing for now;
    //interpolation flag.
    flag=0;
    
    
 
    //
    // Loop 
    //
       
    for (;;) {  

        grPlot0 ( z0, x0, y0, color1);
        //grPlot0 ( z0, x0, y0, color2);
      
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



// The upper-left corner and lower-right corner. 
void
ras_rectangleZ (
    int left, int top, int z0,
    int right, int bottom, int z1,
    unsigned long color )
{

     int h=0;

     // COmewça com a linha de cima.
     for ( h=top; h >= bottom; h-- ){
         plotLine3d ( left,  h, z0, right, h, z1, color );
    }
}



int xxxInflateCubeZ ( struct gr_cube_d *cube, int value )
{
    if ( (void*) cube == NULL )
        return -1;

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

        //north points ==========================================
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


int xxxDeflateCubeZ ( struct gr_cube_d *cube, int value )
{
    if ( (void*) cube == NULL )
        return -1;

    


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


// #test
// cube mesh
int xxxCubeZ ( struct gr_cube_d *cube )
{

    int h=0; 
    int d=0;
    int i=0;


    if ( (void*) cube == NULL )
        return -1;
    
 
    //north
    //primeiro desenha o north porque ele sera sobreposto pelo sul nessa camera.

    // north;
    plotLine3d (cube->p[4].x, cube->p[4].y, cube->p[4].z, 
                cube->p[5].x, cube->p[5].y, cube->p[5].z, cube->p[4].color );
    plotLine3d (cube->p[5].x, cube->p[5].y, cube->p[5].z, 
                cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[5].color );
    plotLine3d (cube->p[7].x, cube->p[7].y, cube->p[7].z, 
                cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[6].color );
    plotLine3d (cube->p[4].x, cube->p[4].y, cube->p[4].z, 
                cube->p[7].x, cube->p[7].y, cube->p[7].z, cube->p[7].color );

    ras_rectangleZ ( 
        cube->p[4].x, cube->p[4].y, cube->p[4].z, 
        cube->p[6].x, cube->p[6].y, cube->p[6].z,
        cube->p[4].color  );
 
    //=================================================================
    
    // 1st line 
    plotLine3d (cube->p[0].x, cube->p[0].y, cube->p[0].z, 
                cube->p[4].x, cube->p[4].y, cube->p[4].z, cube->p[0].color );
    // 2nd line
    plotLine3d (cube->p[1].x, cube->p[1].y, cube->p[1].z, 
                cube->p[5].x, cube->p[5].y, cube->p[5].z, cube->p[1].color );
    // 3rd line
    plotLine3d (cube->p[2].x, cube->p[2].y, cube->p[2].z, 
                cube->p[6].x, cube->p[6].y, cube->p[6].z, cube->p[2].color );
    // 4th line 
    plotLine3d (cube->p[3].x, cube->p[3].y, cube->p[3].z, 
                cube->p[7].x, cube->p[7].y, cube->p[7].z, cube->p[3].color );

    //=================================================================

    //left ok
    ras_rectangleZ ( 
        cube->p[0].x, cube->p[0].y, cube->p[0].z, 
        cube->p[7].x, cube->p[7].y, cube->p[7].z,
        cube->p[0].color  );


    //right ok
    ras_rectangleZ ( 
        cube->p[1].x, cube->p[1].y, cube->p[1].z, 
        cube->p[6].x, cube->p[6].y, cube->p[6].z,
        cube->p[1].color  );


    //bottom fail
    //ras_rectangleZ ( 
    //    cube->p[3].x, cube->p[3].y, cube->p[3].z, 
    //    cube->p[6].x, cube->p[6].y, cube->p[6].z,
    //    cube->p[2].color  );

    // top fail
    //ras_rectangleZ ( 
    //    cube->p[4].x, cube->p[4].y, cube->p[4].z, 
    //    cube->p[0].x, cube->p[0].y, cube->p[0].z,
    //    cube->p[3].color  );

       
    //south
    plotLine3d (cube->p[0].x, cube->p[0].y, cube->p[0].z, 
                cube->p[1].x, cube->p[1].y, cube->p[1].z, cube->p[0].color );
    plotLine3d (cube->p[1].x, cube->p[1].y, cube->p[1].z, 
                cube->p[2].x, cube->p[2].y, cube->p[2].z, cube->p[1].color );
    plotLine3d (cube->p[3].x, cube->p[3].y, cube->p[3].z, 
                cube->p[2].x, cube->p[2].y, cube->p[2].z, cube->p[2].color );
    plotLine3d (cube->p[0].x, cube->p[0].y, cube->p[0].z, 
                cube->p[3].x, cube->p[3].y, cube->p[3].z, cube->p[3].color );

   ras_rectangleZ (  
       cube->p[0].x, cube->p[0].y, cube->p[0].z,   //y=top? 
       cube->p[2].x, cube->p[2].y, cube->p[2].z,
       cube->p[0].color );
}


//sevice 2041
int serviceGrCubeZ(void)
{
    // #todo:
    // Vamos pegar os vertices do cubo nos argumentos
    // e completar a estrtutura local.
    // entao passamos o endereço da estrutura para a funçao helper.

    unsigned long *message_address = (unsigned long *) &__buffer[0];
    
    
    gwssrv_debug_print("serviceGrCubeZ: [2041]\n");
    
    struct gr_cube_d cube;
   
    //south     
    cube.p[0].x = message_address[10];
    cube.p[0].y = message_address[11];
    cube.p[0].z = message_address[12];
    cube.p[0].color = message_address[13];
        
    cube.p[1].x = message_address[14];
    cube.p[1].y = message_address[15];
    cube.p[1].z = message_address[16];
    cube.p[1].color = message_address[17];
        
    cube.p[2].x = message_address[18];
    cube.p[2].y = message_address[19];
    cube.p[2].z = message_address[20];
    cube.p[2].color = message_address[21];
        
    cube.p[3].x = message_address[22];
    cube.p[3].y = message_address[23];
    cube.p[3].z = message_address[24];
    cube.p[3].color = message_address[25];

    //north
    cube.p[4].x = message_address[26];
    cube.p[4].y = message_address[27];
    cube.p[4].z = message_address[28];
    cube.p[4].color = message_address[29];
       
    cube.p[5].x = message_address[30];
    cube.p[5].y = message_address[31];
    cube.p[5].z = message_address[32];
    cube.p[5].color = message_address[33];
        
    cube.p[6].x = message_address[34];
    cube.p[6].y = message_address[35];
    cube.p[6].z = message_address[36];
    cube.p[6].color = message_address[37];
        
    cube.p[7].x = message_address[38];
    cube.p[7].y = message_address[39];
    cube.p[7].z = message_address[40];
    cube.p[7].color = message_address[41];
    
   
    //#test
    //Temos que passar corretamente o endereço da estrutura.
    xxxCubeZ ( (struct gr_cube_d *) &cube );
   
   return 0;
}



//sevice 2042
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



// inflate varias vezes.
//only on jail
void cube_demo1(void)
{
    int i=0;
    int j=0;
   
    struct gr_cube_d *cube;
    cube = (void *) malloc( sizeof( struct gr_cube_d ) );
    if ( (void*) cube != NULL )
    {
		//marcador.
		noraDrawingStuff3 (0,0,0);
		
		//while(1){

        //south     
        cube->p[0].x = 0;
        cube->p[0].y = 40;
        cube->p[0].z = 0;
        cube->p[0].color = COLOR_WHITE;
        
        cube->p[1].x = 40;
        cube->p[1].y = 40;
        cube->p[1].z = 0;
        cube->p[1].color = COLOR_WHITE;
        
        cube->p[2].x = 40;
        cube->p[2].y = 0;
        cube->p[2].z = 0;
        cube->p[2].color = COLOR_WHITE;
        
        cube->p[3].x = 0;
        cube->p[3].y = 0;
        cube->p[3].z = 0;
        cube->p[3].color = COLOR_WHITE;

        //north
        cube->p[4].x = 0;
        cube->p[4].y = 40;
        cube->p[4].z = 40;
        cube->p[4].color = COLOR_BLACK;
        
        cube->p[5].x = 40;
        cube->p[5].y = 40;
        cube->p[5].z = 40;
        cube->p[5].color = COLOR_BLACK;
        
        cube->p[6].x = 40;
        cube->p[6].y = 0;
        cube->p[6].z = 40;
        cube->p[6].color = COLOR_BLACK;
        
        cube->p[7].x = 0;
        cube->p[7].y = 0;
        cube->p[7].z = 40;
        cube->p[7].color = COLOR_BLACK;
                


        //rectBackbufferDrawRectangle ( 
        //   0, 0, 320, 200, COLOR_BLACK, 1 );
        xxxCubeZ(cube);
        //gws_refresh_rectangle(0,0,320,200);
        //for(i=0;i<16;i++){ gwssrv_yield(); }

        //for(j=0; j<30; j++){        
        //rectBackbufferDrawRectangle ( 
        //   0, 0, 320, 200, COLOR_BLACK, 1 );        
        //xxxInflateCubeZ (cube, 1);
        //xxxCubeZ(cube);
        //gws_refresh_rectangle(0,0,320,200);
        //for(i=0;i<16;i++){ gwssrv_yield(); }
        //}
        
        //}
       
        
        //xxxInflateCubeZ (cube, 10);
        //xxxCubeZ(cube);

        //xxxInflateCubeZ (cube, 20);
        //xxxCubeZ(cube);

        //xxxDeflateCubeZ (cube, 5);
        //xxxCubeZ(cube);
        
        //xxxDeflateCubeZ (cube, 10);
        //xxxCubeZ(cube);

        //plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x,  cube->p[0].y, COLOR_BLACK, 'G', cube->p[0].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[1].x,  cube->p[1].y, COLOR_BLACK, 'R', cube->p[1].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[2].x,  cube->p[2].y, COLOR_BLACK, 'A', cube->p[2].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[3].x,  cube->p[3].y, COLOR_BLACK, 'M', cube->p[3].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[4].x,  cube->p[4].y, COLOR_BLACK, 'A', cube->p[4].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[5].x,  cube->p[5].y, COLOR_BLACK, 'D', cube->p[5].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[6].x,  cube->p[6].y, COLOR_BLACK, '0', cube->p[6].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[7].x,  cube->p[7].y, COLOR_BLACK, '*', cube->p[7].z );
    }


}


// inflate varias vezes.
// only on jail
void cube_demo2 (void)
{
    int i=0;
    int j=0;
    static int action = 1000; // inflate.
    
    
    int count=4;
   
    struct gr_cube_d *cube;
    cube = (void *) malloc( sizeof( struct gr_cube_d ) );
    if ( (void*) cube != NULL )
    {
        //marcador.
        noraDrawingStuff3 (0,0,0);

        while (count>0) {

        count--;

        //south     
        cube->p[0].x = 0;
        cube->p[0].y = 40;
        cube->p[0].z = 0;
        cube->p[0].color = COLOR_WHITE;
        
        cube->p[1].x = 40;
        cube->p[1].y = 40;
        cube->p[1].z = 0;
        cube->p[1].color = COLOR_WHITE;
        
        cube->p[2].x = 40;
        cube->p[2].y = 0;
        cube->p[2].z = 0;
        cube->p[2].color = COLOR_WHITE;
        
        cube->p[3].x = 0;
        cube->p[3].y = 0;
        cube->p[3].z = 0;
        cube->p[3].color = COLOR_WHITE;

        //north
        cube->p[4].x = 0;
        cube->p[4].y = 40;
        cube->p[4].z = 40;
        cube->p[4].color = COLOR_YELLOW;
        
        cube->p[5].x = 40;
        cube->p[5].y = 40;
        cube->p[5].z = 40;
        cube->p[5].color = COLOR_YELLOW;
        
        cube->p[6].x = 40;
        cube->p[6].y = 0;
        cube->p[6].z = 40;
        cube->p[6].color = COLOR_YELLOW;
        
        cube->p[7].x = 0;
        cube->p[7].y = 0;
        cube->p[7].z = 40;
        cube->p[7].color = COLOR_YELLOW;
                

        rectBackbufferDrawRectangle ( 0, 0, 320, 200, COLOR_BLACK, 1 );
        xxxCubeZ(cube);
        //string!
        plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*0), cube->p[0].y, COLOR_RED, 'G', cube->p[0].z );
        plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*1), cube->p[0].y, COLOR_RED, 'R', cube->p[0].z );   
        plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*2), cube->p[0].y, COLOR_RED, 'A', cube->p[0].z );
        plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*3), cube->p[0].y, COLOR_RED, 'M', cube->p[0].z );
        plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*4), cube->p[0].y, COLOR_RED, 'A', cube->p[0].z );
        plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*5), cube->p[0].y, COLOR_RED, 'D', cube->p[0].z );
        plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*6), cube->p[0].y, COLOR_RED, 'O', cube->p[0].z );
        gws_refresh_rectangle(0,0,320,200);
        for(i=0;i<16;i++){ gwssrv_yield(); }

        //porque o z eh reduzido duas vezes.
        //entao esse eh o limite da reduçao.
        for (j=0; j<(40/2); j++){        
            rectBackbufferDrawRectangle ( 0, 0, 320, 200, COLOR_BLACK, 1 );        
            if (action==1000){
                xxxInflateCubeZ (cube, 1);
            }else{
                xxxDeflateCubeZ (cube, 1);
            };
            xxxCubeZ(cube);
            
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*0), cube->p[0].y, COLOR_RED, 'G', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*1), cube->p[0].y, COLOR_RED, 'R', cube->p[0].z );   
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*2), cube->p[0].y, COLOR_RED, 'A', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*3), cube->p[0].y, COLOR_RED, 'M', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*4), cube->p[0].y, COLOR_RED, 'A', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*5), cube->p[0].y, COLOR_RED, 'D', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*6), cube->p[0].y, COLOR_RED, 'O', cube->p[0].z );
            gws_refresh_rectangle(0,0,320,200);
            for(i=0;i<32;i++){ gwssrv_yield(); }
        }
        switch (action){
            case 1000: action = 2000; break;
            case 2000: action = 1000; break;
            default:   action = 1000; break;
        };
        }; //while--
       
        
        //xxxInflateCubeZ (cube, 10);
        //xxxCubeZ(cube);

        //xxxInflateCubeZ (cube, 20);
        //xxxCubeZ(cube);

        //xxxDeflateCubeZ (cube, 5);
        //xxxCubeZ(cube);
        
        //xxxDeflateCubeZ (cube, 10);
        //xxxCubeZ(cube);

        //plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x,  cube->p[0].y, COLOR_BLACK, 'G', cube->p[0].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[1].x,  cube->p[1].y, COLOR_BLACK, 'R', cube->p[1].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[2].x,  cube->p[2].y, COLOR_BLACK, 'A', cube->p[2].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[3].x,  cube->p[3].y, COLOR_BLACK, 'M', cube->p[3].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[4].x,  cube->p[4].y, COLOR_BLACK, 'A', cube->p[4].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[5].x,  cube->p[5].y, COLOR_BLACK, 'D', cube->p[5].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[6].x,  cube->p[6].y, COLOR_BLACK, '0', cube->p[6].z );
        //plotCharBackbufferDrawcharTransparentZ ( cube->p[7].x,  cube->p[7].y, COLOR_BLACK, '*', cube->p[7].z );
    }
}


//Circle
//This is an implementation of the circle algorithm.

void 
plotCircle ( 
    int xm, 
    int ym, 
    int r, 
    unsigned long color )
{

    /* II. Quadrant */ 
   //int x = -r, y = 0, err = 2-2*r; 
   
   int x = -r;
   int y = 0;
   int err = (2-(2*r));

   do {
      
      //setPixel(xm-x, ym+y); /*   I. Quadrant */
      //setPixel(xm-y, ym-x); /*  II. Quadrant */
      //setPixel(xm+x, ym-y); /* III. Quadrant */
      //setPixel(xm+y, ym+x); /*  IV. Quadrant */
      
      grPlot0 ( 0, xm-x, ym+y, color);
      grPlot0 ( 0, xm-y, ym-x, color);
      grPlot0 ( 0, xm+x, ym-y, color);
      grPlot0 ( 0, xm+y, ym+x, color);
      
      r = err;
      
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
    int xm, 
    int ym, 
    int r, 
    unsigned long color, 
    int z )
{

    /* II. Quadrant */ 
   //int x = -r, y = 0, err = 2-2*r; 
   
   int x = -r;
   int y = 0;
   int err =  (2-(2*r));

   do {
      
      //setPixel(xm-x, ym+y); /*   I. Quadrant */
      //setPixel(xm-y, ym-x); /*  II. Quadrant */
      //setPixel(xm+x, ym-y); /* III. Quadrant */
      //setPixel(xm+y, ym+x); /*  IV. Quadrant */
      
      grPlot0 ( z, xm-x, ym+y, color);
      grPlot0 ( z, xm-y, ym-x, color);
      grPlot0 ( z, xm+x, ym-y, color);
      grPlot0 ( z, xm+y, ym+x, color);
      
      r = err;
      
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
       grPlot0 ( 0, x1, y0, color);  //   I. Quadrant
       grPlot0 ( 0, x0, y0, color);  //  II. Quadrant
       grPlot0 ( 0, x0, y1, color);  // III. Quadrant
       grPlot0 ( 0, x1, y1, color);  //  IV. Quadrant
       
       e2 = (2*err);
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    
    } while (x0 <= x1);


    /* too early stop of flat ellipses a=1 */
    while (y0-y1 < b) {

        grPlot0 ( 0, x0-1,    y0, color);  //-> finish tip of ellipse
        grPlot0 ( 0, x1+1,  y0++, color);
        grPlot0 ( 0, x0-1,    y1, color);
        grPlot0 ( 0, x1+1,  y1--, color);
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
       grPlot0 ( z, x1, y0, color);  //   I. Quadrant
       grPlot0 ( z, x0, y0, color);  //  II. Quadrant
       grPlot0 ( z, x0, y1, color);  // III. Quadrant
       grPlot0 ( z, x1, y1, color);  //  IV. Quadrant
       
       
       e2 = (2*err);
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    
    } while (x0 <= x1);


    /* too early stop of flat ellipses a=1 */
    while (y0-y1 < b) {
   
        grPlot0 ( z, x0-1,    y0, color);  // -> finish tip of ellipse
        grPlot0 ( z, x1+1,  y0++, color);
        grPlot0 ( z, x0-1,    y1, color);
        grPlot0 ( z, x1+1,  y1--, color);
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
    int x=0;
    int y=0;


    // colunas.
    for (x=0; x< SavedX; x++)    
    {
        for (y=0; y<SavedY; y++)
        {
            if ( x != 0 ){
                if ( y % x == 0 ){
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
    int _x=0;
    int _y=0;
    int _z = z;


    int limitX = SavedX/2;
    int limitY = SavedY/2;    


    // colunas.
    for (_x=x; _x<limitX; _x++)    
    {
        for (_y=y; _y<limitY; _y++)
        {
            if ( _x != 0 ){
                if ( _y % _x == 0 ){
                    grPlot0 (_z, _x, _y,COLOR_BLACK);
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
    int i, j, k;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            res[i][j] = 0;
            for (k = 0; k < 4; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];
        }
    }
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
   int i=0;
   int j=0;
   int k=0;


   // Initializing elements of matrix mult to 0.
   for (i = 0; i < rr; ++i) 
   {
      for (j = 0; j < cr; ++j) 
      {
         result[i][j] = 0;
      }
   }


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


    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (k = 0; k < c1; k++)
                result[i][j] += first[i][k] * second[k][j];
        }
    }
    
}



void matrix_demo1(void)
{

     //#define N 4
   
    /*
    int mat1[4][4] = { { 1, 1, 1, 1 },
                        { 2, 2, 2, 2 },
                        { 3, 3, 3, 3 },
                        { 4, 4, 4, 4 } };
 
    int mat2[4][4] = { { 1, 1, 1, 1 },
                       { 2, 2, 2, 2 },
                       { 3, 3, 3, 3 },
                       { 4, 4, 4, 4 } };
    
    int res[4][4]; // To store result
    */


    int mat1[4][4] = {  { 1, 1, 1, 1 },
                        { 2, 2, 2, 2 },
                        { 3, 3, 3, 3 },
                        { 4, 4, 4, 4 } };
 
    int mat2[4][4] = { { -5, -5, 0, 0 },
                       { 5,  -5, 0, 0 },
                       { 5,   5, 0, 0 },
                       { -5,  5, 0, 0 } };
    
    int res[4][4]; // To store result

    //int m1[10][10];
    //int m2[10][10];
    //int m2[3][1];
    //int  r[10][10];


    //grPlot0 ( 0, -50, -50, COLOR_WHITE ); 
    //grPlot0 ( 0, 50, -50, COLOR_WHITE ); 
    //grPlot0 ( 0, 50, 50, COLOR_WHITE ); 
    //grPlot0 ( 0, -50, 50, COLOR_WHITE ); 
   
    // rows and columns for the first matrix
    // rows and columns for the second matrix
    //multiplyMatrices(m1, m2, r, r1, c1, r2, c2);
    //multiplyMatrices(m1, m2, r, 
    //    2, 3, 3, 1 );

    // multiplicando um dos pontos pela projeçao.
    //m2[0][0] = 50;   // x
    //m2[1][0] = 50;   // y
    //m2[3][0] = 0;    // z
    
    //multiplyMatrices ( mat1, mat2, res, 
    //    4, 4, 4, 4 , 4, 4);
    


    

    //x,y,z,?
    //printf ("%d | %d | %d | %d \n",res[0][0], res[0][1], res[0][2], res[0][3]);
    //printf ("%d | %d | %d | %d \n",res[1][0], res[1][1], res[1][2], res[1][3]);
    //printf ("%d | %d | %d | %d \n",res[2][0], res[2][1], res[2][2], res[2][3]);
    //printf ("%d | %d | %d | %d \n",res[3][0], res[3][1], res[3][2], res[3][3]);



    
    int i=0;
    
    int count=4;
    
    while (count>0){

    count--;

    for (i=0; i<8; i++){

       rectBackbufferDrawRectangle ( 
           0, 0, 320, 200, COLOR_BLACK, 1 );
                
       multiply4 ( projection4x4, mat2, res );
       
       //z,x,y
       grPlot0 ( res[0][2], res[0][0], res[0][1], COLOR_WHITE); 
       grPlot0 ( res[1][2], res[1][0], res[1][1], COLOR_WHITE); 
       grPlot0 ( res[2][2], res[2][0], res[2][1], COLOR_WHITE); 
       grPlot0 ( res[3][2], res[3][0], res[3][1], COLOR_WHITE); 
   
       
       projection4x4[0][0] = i%5;
       projection4x4[0][1] = 0;
       // projection4x4[0][2] = 0;
       // projection4x4[0][3] = 0;

       
        projection4x4[1][0] = 0;
        projection4x4[1][1] = i%5;
       // projection4x4[1][2] = 0;
       // projection4x4[1][3] = 0;

       
        projection4x4[2][0] = 0;
        projection4x4[2][1] = 0;
       // projection4x4[2][2] = 0;
       // projection4x4[2][3] = 0;

       
        projection4x4[3][0] = i%5;
        projection4x4[3][1] = i%5;
       // projection4x4[3][2] = 0;
       // projection4x4[3][3] = 0;
   
	    //{i,0,0,0}, 
	    //{0,i,0,0},
	    //{0,0,0,0},
	    //{i,i,0,0}
	    
	        gws_show_backbuffer();  
	        gwssrv_yield();
	        gwssrv_yield();            
	    
        };
    };
}



//start up animation
//matrix multiplication
void sa_1(void)
{
    int mat1[4][4] = {  { 1, 1, 1, 1 },
                        { 2, 2, 2, 2 },
                        { 3, 3, 3, 3 },
                        { 4, 4, 4, 4 } };
 
    int mat2[4][4] = { { -5, -5, 0, 0 },
                       { 5,  -5, 0, 0 },
                       { 5,   5, 0, 0 },
                       { -5,  5, 0, 0 } };
    
    int res[4][4]; // To store result

    

    int i=0;
        
    
    if (current_mode != GRAMADO_JAIL)
        return;
    
    
    int count=3;    
    while ( count>0){

        for (i=0; i<8; i++){
        
            // black background.
            rectBackbufferDrawRectangle ( 
               0, 0, 320, 200, COLOR_BLACK, 1 );
            
            // transform.
            multiply4 ( projection4x4, mat2, res );
       
            // PLot for dots.
            // z,x,y
            grPlot0 ( res[0][2], res[0][0], res[0][1], COLOR_WHITE); 
            grPlot0 ( res[1][2], res[1][0], res[1][1], COLOR_WHITE); 
            grPlot0 ( res[2][2], res[2][0], res[2][1], COLOR_WHITE); 
            grPlot0 ( res[3][2], res[3][0], res[3][1], COLOR_WHITE); 
          
            // New projection matrix.
            
            projection4x4[0][0] = i%5;
            projection4x4[0][1] = 0;
            // projection4x4[0][2] = 0;
            // projection4x4[0][3] = 0;

            projection4x4[1][0] = 0;
            projection4x4[1][1] = i%5;
            // projection4x4[1][2] = 0;
            // projection4x4[1][3] = 0;

            projection4x4[2][0] = 0;
            projection4x4[2][1] = 0;
            // projection4x4[2][2] = 0;
            // projection4x4[2][3] = 0;
       
            projection4x4[3][0] = i%5;
            projection4x4[3][1] = i%5;
            // projection4x4[3][2] = 0;
            // projection4x4[3][3] = 0;
  
            // Refresh and yield.
            refresh_device_screen(); 
            gwssrv_yield();
            gwssrv_yield();
            gwssrv_yield();
            gwssrv_yield();
            // ...
        };
        
        count--;
    };
}


// Rotina usada para rodar rotinas demo na inicializaçao.
// Seleciona a rotina demo a ser executada.
void window_server_startup_animation(int i)
{
    switch (i){
    case 1: sa_1(); break;
    case 2: fredDemo0(); break;
    case 3: fredDemo1(); break;
    case 4: fredDemo2(); break;
    case 5: cube_demo1(); break;
    case 6: cube_demo2(); break;
    case 7: curveDemo(); break;
    case 8: matrix_demo1(); break;
    //case 9: xxx(); break;
    default: break;
    };
}


// Fibonacci Series using Recursion 
int fib (int n){ 

    int a=0;
    int b=0;

    if (n <= 1){ return n; }
    
    a = fib(n - 1); 
    b = fib(n - 2);

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

    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {

           // Put pixel. 
            if ( ( *work_char & bit_mask ) ){
 
                // IN: z,x,y,color.
                grPlot0 ( 0, x + x2, y, color ); 
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
                grPlot0 ( z, x + x2, (y + gcharWidth), color ); 
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
    long dx, dy, err, cur = xx*sy-yy*sx;

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
      grPlot0(x0,y0,z0,color);

      if (x0 == x2 && y0 == y2) return;  /* last pixel -> curve finished */
      y1 = 2*err < dx;                  /* save value for test of y step */
      if (2*err > dy) { x0 += sx; dx -= xy; err += dy += yy; } /* x step */
      if (    y1    ) { y0 += sy; dy -= xy; err += dx += xx; } /* y step */
    } while (dy < dx );           /* gradient negates -> algorithm fails */
    
    
    }
    
    /* plot remaining part to end */
    //plotLine(x0,y0, x2,y2);   
    plotLine3d(x0,y0,z0, x2,y2,z2, color); 
}  
  


void curveDemo(void)
{
    int i=0;
    int j=0;
 
 
    int count=4;
    
    while (count>0){
        count--;

    for (i=0; i<10; i++){
        // line

        rectBackbufferDrawRectangle ( 
            0, 0, 320, 200, COLOR_BLACK, 1 );
        
        //a variaçao de y2 me pareceu certa.
        plotQuadBezierSeg ( 
            0,   0,  0,      //x0, y0, z0, 
            40,  40, 0,      //x1, y1, z1,
           100,  20+i+i, 0,  //x2, y2, z2, 
           COLOR_YELLOW );

        //string! funny
        plotCharBackbufferDrawcharTransparentZ ( 40+ (8*0), 20+i+i, COLOR_RED, 'G', 0 );
        plotCharBackbufferDrawcharTransparentZ ( 40+ (8*1), 20+i+i, COLOR_RED, 'R', 0 );   
        plotCharBackbufferDrawcharTransparentZ ( 40+ (8*2), 20+i+i, COLOR_RED, 'A', 0 );
        plotCharBackbufferDrawcharTransparentZ ( 40+ (8*3), 20+i+i, COLOR_RED, 'M', 0 );
        plotCharBackbufferDrawcharTransparentZ ( 40+ (8*4), 20+i+i, COLOR_RED, 'A', 0 );
        plotCharBackbufferDrawcharTransparentZ ( 40+ (8*5), 20+i+i, COLOR_RED, 'D', 0 );
        plotCharBackbufferDrawcharTransparentZ ( 40+ (8*6), 20+i+i, COLOR_RED, 'O', 0 );

        gws_refresh_rectangle(0,0,320,200);
        
        for (j=0; j<80; j++){ gwssrv_yield();}
    };
    
    }

}



//
// == fred demo ========================================
//


void fredDemo0(void)
{
    int i=0;
    for (i=0; i<100; i++){
            //noraDrawingStuff3 (i,i,0);
            noraDrawingStuff3 (-i,-i,0);
            //rectangle(8,8,i,i,COLOR_BLUE);
            //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
            //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);
            
            plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);  //save this
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
            //cool
            //plotCircleZ ( -i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
            //igual o de cima.
            //plotCircleZ ( -i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
            //plotCircleZ ( -i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
            //plotEllipseRect ( i, i, i*5, i*5, COLOR_BLUE);
            //plotEllipseRectZ ( i%20, i%20, i, i, COLOR_BLUE,i%20);
    };

}


void fredDemo1(void)
{
    int i=0;
    for (i=0; i<100; i++){
            //noraDrawingStuff3 (i,i,0);
            noraDrawingStuff3 (-i,-i,0);
            //rectangle(8,8,i,i,COLOR_BLUE);
            //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
            //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);  //save this
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
            //cool
            plotCircleZ ( -i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
            //igual o de cima.
            //plotCircleZ ( -i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
            //plotCircleZ ( -i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
            //plotEllipseRect ( i, i, i*5, i*5, COLOR_BLUE);
            //plotEllipseRectZ ( i%20, i%20, i, i, COLOR_BLUE,i%20);
    };

}


void fredDemo2(void)
{
    int i=0;
    for (i=1; i< (1024-768); i++){
            //noraDrawingStuff3 (i,i,0);
            noraDrawingStuff3 (-i,-i,0);
            //rectangle(8,8,i,i,COLOR_BLUE);
            //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
            //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);  //save this
            //plotCircleZ ( -i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
            //cool
            //plotCircleZ ( -i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
            
            //IN: x,y,r,color,z
            plotCircleZ ( -i % fib(20), -i % fib(20), i % (1024-768), COLOR_RED, i % fib(20) );
            //plotCircleZ ( -i % fib(20), -i % fib(20), i %  fib(20/3), COLOR_GREEN, i % fib(20) );
            //plotCircleZ ( -i % fib(20), -i % fib(20), i %  fib(20/5), COLOR_BLUE, i % fib(20) );
            //plotCircleZ ( -i % fib(20), -i % fib(20), i %  fib(20/7), COLOR_YELLOW, i % fib(20) );
            
            //plotCircleZ ( -i % fib(20), -i % fib(20), i %  fib(20/), COLOR_GREEN, i % fib(20) );
            //plotCircleZ ( -i % fib(20), -i % fib(20), i %  fib(20/3), COLOR_YELLOW, i % fib(20) );
            
            //igual o de cima.
            //plotCircleZ ( -i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
            //plotCircleZ ( -i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
            //plotEllipseRect ( i, i, i*5, i*5, COLOR_BLUE);
            //plotEllipseRectZ ( i%20, i%20, i, i, COLOR_BLUE,i%20);
    };

}




















