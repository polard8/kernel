
// demos.c
// A place for demos.

#include "gramado.h"

struct gws_window_d *__demo_window;

int gUseDemos = TRUE;
static int game_update_taskbar=TRUE;
static int frames=0;
static int hits=0;


struct cube_model_d
{
    float fThetaAngle;

    struct gr_vecF3D_d vecs[32];
    int colors[32];

// left or right
    float model_move;

    float model_initial_distance;
    float model_distance;
};
struct cube_model_d  Cube1;


// local
/*
static int __projection4x4[4][4] = { 
        {1,0,0,0}, 
        {0,1,0,0},
        {0,0,0,0},
        {1,1,0,0}
        };
static int __m1[4][4] = { 
        {0,0,0,0}, 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
        };
static int __r[4][4] = { 
        {0,0,0,0}, 
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
        };
*/


static void __draw_cat(int eye_scale, int cat_x, int cat_y, int cat_z);
static void __draw_demo_curve1(int position, int model_z);
static void __draw_model1(int step, int target_axis);

struct gws_window_d *__create_demo_window (
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height );

void drawFlyingCube(float fElapsedTime);

void drawRectangle0(float modelz);

//======================


void drawRectangle0(float modelz)
{
    struct gr_rectangleF3D_d r;
    
    r.p[0].x = (float) -0.02f;  
    r.p[0].y = (float)  0.02f;  
    r.p[0].z = (float) modelz;  
    r.p[0].color = COLOR_WHITE;
    
    r.p[1].x = (float)  0.02f;  
    r.p[1].y = (float)  0.02f;  
    r.p[1].z = (float) modelz;  
    r.p[1].color = COLOR_WHITE;
    
    r.p[2].x = (float)  0.02f;  
    r.p[2].y = (float) -0.02f;  
    r.p[2].z = (float) modelz;  
    r.p[2].color = COLOR_WHITE;
    
    r.p[3].x = (float) -0.02f;  
    r.p[3].y = (float) -0.02f;  
    r.p[3].z = (float) modelz;  
    r.p[3].color = COLOR_WHITE;
    
    drawRectangleF( (struct gr_rectangleF3D_d *) &r );
}


// Draw the cube.
// Elapsed time means the amount of time between two events.
void drawFlyingCube(float fElapsedTime)
{
    char string0[16];

// Matrices
    struct gr_mat4x4_d  matRotZ; 
    struct gr_mat4x4_d  matRotX;
// Triangles
    struct gr_triangleF3D_d  tri;            // triângulo original.
    struct gr_triangleF3D_d  triRotatedZ; 
    struct gr_triangleF3D_d  triRotatedZX;

    int sequence[3*16];  //cube
    int cull=FALSE;

    register int i=0;  //loop
    int j=0;
    int off=0;
    int v=0;
// ---------

// Initialize 4x4 matrices.
// see: gprim.h
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            matRotZ.m[i][j] = (float) 0.0f;
            matRotX.m[i][j] = (float) 0.0f;
        };
    };

// ---------

// Building the transformation matrices.

    Cube1.fThetaAngle = (float) (Cube1.fThetaAngle + fElapsedTime);
    //Cube1.fThetaAngle = (float) (Cube1.fThetaAngle + 1.0f * fElapsedTime);

// Rotation Z
	matRotZ.m[0][0] = (float) cosf(Cube1.fThetaAngle);
	matRotZ.m[0][1] = (float) -sinf(Cube1.fThetaAngle);
	matRotZ.m[1][0] = (float) sinf(Cube1.fThetaAngle);
	matRotZ.m[1][1] = (float) cosf(Cube1.fThetaAngle);
	matRotZ.m[2][2] = (float) 1.0f;
	matRotZ.m[3][3] = (float) 1.0f;
// Rotation X
	matRotX.m[0][0] = (float) 1.0f;
	matRotX.m[1][1] = (float) cosf(Cube1.fThetaAngle * 0.5f);
	matRotX.m[1][2] = (float) -sinf(Cube1.fThetaAngle * 0.5f);
	matRotX.m[2][1] = (float) sinf(Cube1.fThetaAngle * 0.5f);
	matRotX.m[2][2] = (float) cosf(Cube1.fThetaAngle * 0.5f);
	matRotX.m[3][3] = (float) 1.0f;
//------------------------------------------------

// 12 faces
// Order: north, top, south, bottom, east, west.
// clockwise
    sequence[0]  = (int) 1; sequence[1]  = (int) 2;  sequence[2] = (int) 4; //f 1 2 4 // north bottom  n
    sequence[3]  = (int) 1; sequence[4]  = (int) 4;  sequence[5] = (int) 3; //f 1 4 3 // north top     n
    sequence[6]  = (int) 3; sequence[7]  = (int) 4;  sequence[8] = (int) 6; //f 3 4 6 // top right     s
    sequence[9]  = (int) 3; sequence[10] = (int) 6; sequence[11] = (int) 5; //f 3 6 5 // top left      s   
    sequence[12] = (int) 5; sequence[13] = (int) 6; sequence[14] = (int) 8; //f 5 6 8 // south right   s
    sequence[15] = (int) 5; sequence[16] = (int) 8; sequence[17] = (int) 7; //f 5 8 7 // south left    s
    sequence[18] = (int) 7; sequence[19] = (int) 8; sequence[20] = (int) 2; //f 7 8 2 // bottom right  n
    sequence[21] = (int) 7; sequence[22] = (int) 2; sequence[23] = (int) 1; //f 7 2 1 // bottom left   n
    sequence[24] = (int) 2; sequence[25] = (int) 8; sequence[26] = (int) 6; //f 2 8 6 // east bottom   s
    sequence[27] = (int) 2; sequence[28] = (int) 6; sequence[29] = (int) 4; //f 2 6 4 // east top      n  
    sequence[30] = (int) 7; sequence[31] = (int) 1; sequence[32] = (int) 3; //f 7 1 3 // west bottom   n
    sequence[33] = (int) 7; sequence[34] = (int) 3; sequence[35] = (int) 5; //f 7 3 5 // west top      s 

// ---------
// #test
// draw a rectangle
   //drawRectangle0((float) 0.08f);

// ---------
// draw a cube

    //cull=FALSE;

    for (i=1; i<=12; i++)
    {
        cull=FALSE;

        off = (int) ((i-1)*3);
        
        v = (int) sequence[off+0];
        tri.p[0].x = (float) Cube1.vecs[v].x;
        tri.p[0].y = (float) Cube1.vecs[v].y;
        tri.p[0].z = (float) Cube1.vecs[v].z;
        tri.p[0].color = COLOR_PINK;
        if(i >= 1 && i < 12){
            tri.p[0].color = Cube1.colors[i-1];  // rectangle color
        }
        v = (int) sequence[off+1];
        tri.p[1].x = (float) Cube1.vecs[v].x;
        tri.p[1].y = (float) Cube1.vecs[v].y;
        tri.p[1].z = (float) Cube1.vecs[v].z;
        tri.p[1].color = COLOR_WHITE;  // not used

        v = (int) sequence[off+2];
        tri.p[2].x = (float) Cube1.vecs[v].x;
        tri.p[2].y = (float) Cube1.vecs[v].y;
        tri.p[2].z = (float) Cube1.vecs[v].z;
        tri.p[2].color = COLOR_WHITE;  // not used

        //-----------------------------    
        // Rotate in Z-Axis
        gr_MultiplyMatrixVector(
            (struct gr_vecF3D_d *) &tri.p[0], 
            (struct gr_vecF3D_d *) &triRotatedZ.p[0], 
            (struct gr_mat4x4_d *) &matRotZ);
        gr_MultiplyMatrixVector(
            (struct gr_vecF3D_d *) &tri.p[1], 
            (struct gr_vecF3D_d *) &triRotatedZ.p[1], 
            (struct gr_mat4x4_d *) &matRotZ);
        gr_MultiplyMatrixVector(
            (struct gr_vecF3D_d *) &tri.p[2], 
            (struct gr_vecF3D_d *) &triRotatedZ.p[2], 
            (struct gr_mat4x4_d *) &matRotZ);
        //-----------------------------    
        // Rotate in X-Axis
        gr_MultiplyMatrixVector(
            (struct gr_vecF3D_d *) &triRotatedZ.p[0], 
            (struct gr_vecF3D_d *) &triRotatedZX.p[0], 
            (struct gr_mat4x4_d *) &matRotX);
        gr_MultiplyMatrixVector(
            (struct gr_vecF3D_d *) &triRotatedZ.p[1], 
            (struct gr_vecF3D_d *) &triRotatedZX.p[1], 
            (struct gr_mat4x4_d *) &matRotX);
        gr_MultiplyMatrixVector(
            (struct gr_vecF3D_d *) &triRotatedZ.p[2], 
            (struct gr_vecF3D_d *) &triRotatedZX.p[2], 
            (struct gr_mat4x4_d *) &matRotX);


        triRotatedZX.p[0].color = tri.p[0].color;
        triRotatedZX.p[1].color = tri.p[1].color;
        triRotatedZX.p[2].color = tri.p[2].color;


        // Translate in z.

        // Increment distance
        Cube1.model_distance = (float) (Cube1.model_distance + 0.002f);
        // Restart distance
        if (Cube1.model_distance > 10.0f){
            Cube1.model_distance = (float) 0.8f;
            //hits++;
            //memset(string0,0,16);  //clear
            //itoa(hits,string0);
            //wm_Update_TaskBar((char *)string0,FALSE);
            //wm_Update_TaskBar("hit",FALSE);
        }

        triRotatedZX.p[0].z =
            (float) (
            triRotatedZX.p[0].z + 
            Cube1.model_initial_distance +
            Cube1.model_distance ); 
        triRotatedZX.p[1].z = 
            (float) (
            triRotatedZX.p[1].z + 
            Cube1.model_initial_distance +
            Cube1.model_distance ); 

        triRotatedZX.p[2].z = 
            (float) (
            triRotatedZX.p[2].z + 
            Cube1.model_initial_distance +
            Cube1.model_distance ); 

        // Translate in x.
        // left or right

        triRotatedZX.p[0].x = 
            (float) (triRotatedZX.p[0].x + Cube1.model_move); 
        triRotatedZX.p[1].x = 
            (float) (triRotatedZX.p[1].x + Cube1.model_move); 
        triRotatedZX.p[2].x = 
            (float) (triRotatedZX.p[2].x + Cube1.model_move); 


        //----------------------------------------------------
        // Use Cross-Product to get surface normal
        struct gr_vecF3D_d normal; 
        struct gr_vecF3D_d line1; 
        struct gr_vecF3D_d line2;

        line1.x = (float) triRotatedZX.p[1].x - triRotatedZX.p[0].x;
        line1.y = (float) triRotatedZX.p[1].y - triRotatedZX.p[0].y;
        line1.z = (float) triRotatedZX.p[1].z - triRotatedZX.p[0].z;

        line2.x = (float) triRotatedZX.p[2].x - triRotatedZX.p[0].x;
        line2.y = (float) triRotatedZX.p[2].y - triRotatedZX.p[0].y;
        line2.z = (float) triRotatedZX.p[2].z - triRotatedZX.p[0].z;

        normal.x = (float) (line1.y * line2.z - line1.z * line2.y);
        normal.y = (float) (line1.z * line2.x - line1.x * line2.z);
        normal.z = (float) (line1.x * line2.y - line1.y * line2.x);

        // It's normally normal to normalise the normal
        float l = 
            (float) sqrt( (double)
                        ( normal.x*normal.x + 
                          normal.y*normal.y + 
                          normal.z*normal.z) );

        normal.x = (float) (normal.x/l); 
        normal.y = (float) (normal.y/l); 
        normal.z = (float) (normal.z/l);

        //#ok
        //if ( (float) normal.z <  0.0f){ cull=FALSE;}  //pinta
        //if ( (float) normal.z >= 0.0f){ cull=TRUE; }  //não pinta

        // #test
        // Considering the camera position.
        if (CurrentCameraF.initialized == FALSE){ return; }
        float tmp = 
             (float) (
             normal.x * (triRotatedZX.p[0].x - CurrentCameraF.position.x) + 
             normal.y * (triRotatedZX.p[0].y - CurrentCameraF.position.y) +
             normal.z * (triRotatedZX.p[0].z - CurrentCameraF.position.z) );
        if( (float) tmp <  0.0f){ cull=FALSE; }
        if( (float) tmp >= 0.0f){ cull=TRUE;  }
        //----------------------------------------------------

        // We need a valid window, 
        // to use the rasterization features.
        // #test: Testing rasterization.
        // #todo: Return the number of changed pixels.
        int fill_triangle = TRUE;
        if ( (void*) __root_window != NULL )
        {
            if (cull==FALSE){
                plotTriangleF(
                    (struct gws_window_d *) __root_window, 
                    (struct gr_triangleF3D_d *) &triRotatedZX,
                    fill_triangle ); 
            }
        }
    };
}


struct gws_window_d *__create_demo_window (
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height )
{

    struct gws_window_d *w;

    if( (void*) __root_window == NULL ){
        return NULL;
    }

// Create window.

    w = 
        (struct gws_window_d *) CreateWindow ( 
                                    WT_SIMPLE, 
                                    0, //style
                                    1, //status 
                                    1, //view
                                    "DemoWin",  
                                    left, top, width, height,   
                                    __root_window, 0, 
                                    COLOR_BLACK, 
                                    COLOR_BLACK );


    if ( (void *) w == NULL ){
        return NULL;
    }

    if ( w->used != TRUE ||  w->magic != 1234 )
    {
        return NULL;
    }

// Register the window.
    int WindowId= -1;
    WindowId = (int) RegisterWindow(w);
    if (WindowId<0)
    {
         return NULL;
    }

// ok
    return (struct gws_window_d *)  w;
}


static void __draw_model1(int step, int target_axis)
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


    //int gd = DETECT; 
    int gd = 0;
    int gm; 
    int i = step;
    int a;
    int max_x = 800/2;
    // Path of the program
    //initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
    //int floor_max = (800/2)-(405/2); 

// scene increment.
// all the objects in the scene will be incremented
// when this value turns bigger ...
// the objects are moving in the z line.
    int increment = 0;

    int ShowCamera=TRUE;

    //1=x | 2=y | 3=z
    int over=1;
    if ( target_axis >= 1 && target_axis <= 3 )
        over = target_axis;

//-------------------------------------

// -----------------------------------------------
// Draw the world

    int wstatus=-1;
    wstatus = (int) unveil_world();
    if(wstatus<0)
        return;

//
// Draw
//

// -----------------------------------------------
// Road (bg) yellow (grid)

    struct gr_line_d floorline;
    int w=320;  //terrain width
    int h=240;  //terrain height
    int start_at=20; // distance from vp1.
    int initial_wheel_radius = ((h+start_at)/2);
    int scl=4; //scale
    int col = w/scl; // numero de colunas
    int row = h/scl; // numero de linhas
    //int floor_max=800/2;
    unsigned int floor_final_color = 0;
    int l=0;
    for (l=0; l<row; l++)
    {
        floorline.p[0].x = CurrentWorld->h1.x -(l*scl) -start_at;
        floorline.p[0].y = CurrentWorld->h1.y -(l*scl) -start_at;
        floorline.p[0].z = CurrentWorld->h1.z;
        //floorline.p[0].color = 0xFEE135;  // yellow

        floorline.p[1].x = CurrentWorld->h2.x -(l*scl) -start_at;
        floorline.p[1].y = CurrentWorld->h2.y -(l*scl) -start_at;
        floorline.p[1].z = CurrentWorld->h2.z;
        //floorline.p[1].color = 0x567d46;  // green
        
        floor_final_color = 0x567d46;
        //floor_final_color = 
        //    (unsigned int) interpolate_color(
        //        floorline.p[0].color,
        //        floorline.p[1].color,
        //        l );
                 
        plotLine3d ( 
            ow,
            floorline.p[0].x, floorline.p[0].y, floorline.p[0].z, 
            floorline.p[1].x, floorline.p[1].y, floorline.p[1].z, 
            floor_final_color ); 
     };

// -----------------------------------------------
// The vehicle. (hehe)



// -----------------------------------------------
//  guidão
    int g1x= 0; int g1y= 0; int g1z= 0;
    int g2x= 0; int g2y= 0; int g2z= 0;

    if(over==1){
    g1x= CurrentWorld->center.x -20 +i;
    g1y= CurrentWorld->center.y +45;
    g1z= CurrentWorld->center.z;
    g2x= CurrentWorld->center.x -10 +i;
    g2y= CurrentWorld->center.y +45;
    g2z= CurrentWorld->center.z;
    }
    if(over==2){
    g1x= CurrentWorld->center.x -20;
    g1y= CurrentWorld->center.y +45 +i;
    g1z= CurrentWorld->center.z;
    g2x= CurrentWorld->center.x -10;
    g2y= CurrentWorld->center.y +45 +i;
    g2z= CurrentWorld->center.z;
    }
    if(over==3){
    g1x= CurrentWorld->center.x -20;
    g1y= CurrentWorld->center.y +45;
    g1z= CurrentWorld->center.z +i;
    g2x= CurrentWorld->center.x -10;
    g2y= CurrentWorld->center.y +45;
    g2z= CurrentWorld->center.z +i;
    }
    plotLine3d ( 
         ow,
         g1x, g1y, g1z,
         g2x, g2y, g2z, 
         COLOR_BLACK); 

// -----------------------------------------------
// garfo (barra de direção)
    int b1x= 0; int b1y= 0; int b1z= 0;
    int b2x= 0; int b2y= 0; int b2z= 0;

    if(over==1){
    b1x= CurrentWorld->center.x -10 +i;
    b1y= CurrentWorld->center.y +45;
    b1z= CurrentWorld->center.z;
    b2x= CurrentWorld->center.x +i;
    b2y= CurrentWorld->center.y;
    b2z= CurrentWorld->center.z;
    }
    if(over==2){
    b1x= CurrentWorld->center.x -10;
    b1y= CurrentWorld->center.y +45 +i;
    b1z= CurrentWorld->center.z;
    b2x= CurrentWorld->center.x;
    b2y= CurrentWorld->center.y +i;
    b2z= CurrentWorld->center.z;
    }
    if(over==3){
    b1x= CurrentWorld->center.x -10;
    b1y= CurrentWorld->center.y +45;
    b1z= CurrentWorld->center.z +i;
    b2x= CurrentWorld->center.x;
    b2y= CurrentWorld->center.y;
    b2z= CurrentWorld->center.z +i;
    }
    plotLine3d ( 
         ow,
         b1x, b1y, b1z,
         b2x, b2y, b2z, 
         COLOR_BLACK); 


// -----------------------------------------
// wheel
// #todo: We do not have a structure for circles yet.

    int wheelx=0;
    int wheely=0;
    int wheelz=0;
    // O raio diminui a cada step.
    int wheelr = 0;
    
    // x
    if (over==1)
        wheelr = (initial_wheel_radius); 
    // y
    if (over==2)
        wheelr = (initial_wheel_radius); 
    // z
    if (over==3)
        wheelr = (initial_wheel_radius - (i>>1) ); 


    if (over==1){
        wheelx = CurrentWorld->center.x+i;
        wheely = CurrentWorld->center.y;
        wheelz = CurrentWorld->center.z;
    }
    if (over==2){
        wheelx = CurrentWorld->center.x;
        wheely = CurrentWorld->center.y+i;
        wheelz = CurrentWorld->center.z;
    }
    if (over==3){
        wheelx = CurrentWorld->center.x;
        wheely = CurrentWorld->center.y;
        wheelz = CurrentWorld->center.z+i;
    }
    grCircle3 ( 
        ow,
        wheelx, wheely, wheelr,
        GRCOLOR_LIGHTBLACK, 
        wheelz ); 

// -----------------------------------------------
// The cat. :)
    // in: eye scale, x,y,z
    __draw_cat( 
        1,
        wheelx, wheely, wheelz);

// -----------------------------------------------
// Where is our camera?
// Seguindo o guidão.
// IN: modelx, modely, modelz
    if(ShowCamera==TRUE){
         unveil_camera (g1x,g1y,g1z);
    }

    // again
    wstatus = (int) unveil_world();
    if(wstatus<0)
        return;

    //#test
    // It's dangeours, but a very cool effect.
    //gr_dc->width -= 1;
    //gr_dc->height -= 1;
}


void demoModel1(void)
{
    register int i=0;
    int max_step = 200; //800/2;

    if(current_mode != GRAMADO_HOME)
         return;

// ---------------
// Create a demo window
    struct gws_window_d *dw;
    dw = NULL;
    dw = (struct gws_window_d *) __create_demo_window(8,8,480,400);
    if( (void*) dw != NULL )
    {
       if(dw->magic==1234)
       {
           __demo_window = dw;
       }
    }

// ---------------
// The camera for the bike.
// floor.
// (world: left hand)
    camera ( 
        -150, 80, 0,    // position vector
        -150, 90, 0,    // upview vector
         0,   0, 0 );   // lookat vector

// ---------------
// The depth clipping
// Clipping z
    gr_depth_range(
        CurrentProjection,   // projection
        -(800/2),            // zNear
         (800/2) );          // zFar


// -----------------------------------
// Setup model
// eyes, whiskers, mouth
    __setupCatModel(TRUE,TRUE,TRUE);
    
// -----------------------------------
// Move the cycle
    int round=0;
    int target_axis=1;  //1~3
    while(1){

    for (i=0; i<max_step; i++)
    {
        // bg light blue
            demoClearSurface(dw,0x87ceeb);
        //IN: step, switch axis
            __draw_model1(i,target_axis);
        // Clear the screen
        demoFlushSurface(dw);
    };

    //1~3
    target_axis++;
    if(target_axis > 3){
        target_axis=1;
    }
    round++;
    if(round >= 8)
        break;
    };
}


void demoLines(void)
{
    int i=0;
    for (i=0; i<320; i+=5)
    {
        //3d
        plotLine3d ( 
            NULL,
            0,i,0,      //x,y,z 
            320-i,0,0,  //x,y,z 
            COLOR_WHITE); 

        //3d
        plotLine3d ( 
            NULL,
            0,i,0,      //x,y,z 
            -(320-i),0,0,  //x,y,z 
            COLOR_WHITE); 
      
        // ====

        //3d
        plotLine3d ( 
            NULL,
            -i,0,0,      //x,y,z 
            0,-(320-i),0,  //x,y,z 
            COLOR_WHITE); 

        //3d
        plotLine3d ( 
           NULL,
            i,0,0,      //x,y,z 
           0, -(320-i),0,  //x,y,z 
            COLOR_WHITE); 


    };
    refresh_screen();
}


// We can use a NULL window.
void gramado_clear_surface(struct gws_window_d *clipping_window, unsigned int color)
{
    demoClearSurface(clipping_window,color);
}

// Start surface.
// only the working area.
void demoClearWA(unsigned int color)
{
// IN: l,t,w,h,color,fill,rop
    rectBackbufferDrawRectangle ( 
           WindowManager.wa_left, 
           WindowManager.wa_top, 
           WindowManager.wa_width, 
           WindowManager.wa_height, 
           color, 
           1,   //fill 
           0 ); //rop
}

// Start surface
void 
demoClearSurface(
    struct gws_window_d *clipping_window, 
    unsigned int color)
{
    // #todo
    // We can do this for more resolutions. 

// Se a clipping window é válida.
// ONLY ONE TYPE FOR NOW.
    if ( (void*) clipping_window != NULL )
    {
        if(clipping_window->magic==1234)
        {
            if (clipping_window->type == WT_SIMPLE)
            {
                rectBackbufferDrawRectangle ( 
                    clipping_window->left, 
                    clipping_window->top, 
                    clipping_window->width, 
                    clipping_window->height,
                    color, 1, 0 );
                return;
            }
        }
    }


// device context
    if ( (void*) gr_dc != NULL )
    {
        if (gr_dc->magic == 1234)
        {
            if( gr_dc->initialized == TRUE )
            {
                rectBackbufferDrawRectangle ( 
                    gr_dc->left, 
                    gr_dc->top, 
                    gr_dc->width, 
                    gr_dc->height,
                    color, 1, 0 );
                
                return;
            }
        }
    }

    unsigned int fail_color = COLOR_RED;

// Limpa na resolução 320x200
// IN: l,t,w,h,color,fill,rop
    rectBackbufferDrawRectangle ( 
           0, 0, 320, 200, 
           fail_color, 1, 0 );
}



void gramado_flush_surface(struct gws_window_d *clipping_window)
{
    demoFlushSurface(clipping_window);
}

// #todo
// We can do this for more resolutions. 
// mostra na resolução 320x200
void demoFlushSurface(struct gws_window_d *clipping_window)
{
// Flush the surface.


// Se a clipping window é válida.
// ONLY ONE TYPE FOR NOW.
    if ( (void*) clipping_window != NULL )
    {
        if(clipping_window->magic==1234)
        {
            if (clipping_window->type == WT_SIMPLE)
            {
                gws_show_window_rect(clipping_window);
                return;
            }
        }
    }

// default dc
    if ( (void*) gr_dc != NULL )
    {
        if (gr_dc->magic == 1234)
        {
            if( gr_dc->initialized == TRUE )
            {
                gws_refresh_rectangle(
                    gr_dc->left, 
                    gr_dc->top, 
                    gr_dc->width, 
                    gr_dc->height );

                return;
            }
        }
    }

    gws_refresh_rectangle(
        0, 0, 320, 200 );
}


void __setupCatModel(int eyes, int whiskers, int mouth )
{
    CatModel.eyesVisible     = eyes;
    CatModel.whiskersVisible = whiskers;
    CatModel.mouthVisible    = mouth;
}


//worker
static void __draw_cat(int eye_scale, int cat_x, int cat_y, int cat_z)
{
    // object window
    struct gws_window_d *ow;
    ow = NULL;
    //#todo
    // use the demo window if it is possible
    if( (void*) __demo_window != NULL )
    {
       if (__demo_window->magic==1234){
           ow = __demo_window;
       }
    }

// model
    int model_x = (int) cat_x;
    int model_y = (int) cat_y;
    int model_z = (int) cat_z;
    int model_radius = 25;

// eyes
    int eye1_x = model_x -10;
    int eye1_y = model_y +20;
    int eye2_x = model_x +10;
    int eye2_y = model_y +20;
    int eye_radius = (int) (1*eye_scale);
//---

// head
// IN: window,x,y,r,color,z
    grCircle3 ( 
        ow,
        model_x + 0,
        model_y + 12,
        model_radius,
        GRCOLOR_LIGHTBLACK,
        model_z );

// eyes
    if ( CatModel.eyesVisible == TRUE )
    {
        grCircle3 ( 
            ow,
            eye1_x, 
            eye1_y, 
            eye_radius, 
            GRCOLOR_LIGHTBLACK, 
            model_z );
        grCircle3 ( 
            ow,
            eye2_x, 
            eye2_y, 
            eye_radius, 
            GRCOLOR_LIGHTBLACK, 
            model_z );
    }

// whiskers
    if ( CatModel.whiskersVisible == TRUE ){
        // =
        plotLine3d ( 
            ow,
            model_x -40, model_y +8, model_z, 
            model_x -4,  model_y +5, model_z, 
            GRCOLOR_LIGHTBLACK); 
        plotLine3d ( 
            ow,
            model_x -40, model_y +5, model_z, 
            model_x -4,  model_y +4, model_z, 
            GRCOLOR_LIGHTBLACK); 
        plotLine3d ( 
            ow,
            model_x -40, model_y +2, model_z, 
            model_x -4,  model_y +3, model_z, 
            GRCOLOR_LIGHTBLACK); 

        // =
        plotLine3d ( 
            ow,
            model_x + 4,  model_y +5, model_z, 
            model_x + 40, model_y +8, model_z, 
            GRCOLOR_LIGHTBLACK); 
        plotLine3d ( 
            ow,
            model_x + 4,  model_y +4, model_z, 
            model_x + 40, model_y +5, model_z, 
            GRCOLOR_LIGHTBLACK); 
        plotLine3d ( 
            ow,
            model_x + 4,  model_y +3, model_z, 
            model_x + 40, model_y +2, model_z, 
            GRCOLOR_LIGHTBLACK); 
    }

// mouth
    if ( CatModel.mouthVisible == TRUE )
    {
        plotLine3d ( 
            ow,
            model_x -10, model_y -2, model_z, 
            model_x +10, model_y -2, model_z, 
             GRCOLOR_LIGHTBLACK); 
    
        unveil_camera ( -10, -2, model_z );
    }
//---
}


void demoCat (void)
{
    register int i=0;
    int j=0;
    int count = 8;
    int scale_max = 100;

// ---------------
// Create a demo window
    struct gws_window_d *dw;
    dw = NULL;
    dw = (struct gws_window_d *) __create_demo_window(8,8,200,140);
    if( (void*) dw != NULL )
    {
       if(dw->magic==1234){
           __demo_window = dw;
       }
    }
//---------------------

// depth clipping
// IN: projection, znear, zfar.
    gr_depth_range( CurrentProjection, 0, 100 );

// The camera for the cat.
// 'int' values.
// IN: Position vector, upview vector, lookat vector.
    camera ( 
        0,0,0,
        0,0,0,
        0,0,0 );

// Setup model
// IN: eyes, whiskers, mouth
    __setupCatModel(TRUE,TRUE,TRUE);


// Loop
    while (count>0)
    {
        for (i=0; i<scale_max; i++)
        {
            validate_background();                 //begin paint
            demoClearSurface(dw,GRCOLOR_LIGHTCYAN);   // Clear surface
            // IN: eye scale, x,y,z
            __draw_cat(1,0,0,i);
            demoFlushSurface(dw);
            //invalidate_background();               // end paint
            //gr_dc_refresh_screen(gr_dc);

            // good for qemu,
            //for (j=0; j<8; j++){ gwssrv_yield();}  // Delay
            // good for kvm,
            //for (j=0; j<80; j++){ gwssrv_yield();}  // Delay
            
            //rtl_yield();
        };

        count--;
    };
}


void demoTriangle(void)
{

// ---------------
// Create a demo window
    struct gws_window_d *dw;
    dw = NULL;
    dw = (struct gws_window_d *) __create_demo_window(8,8,200,140);
    if( (void*) dw != NULL )
    {
       if(dw->magic==1234){
           __demo_window = dw;
       }
    }
//------------------------------------------

    struct gr_triangle_d *triangle;

    int line_size = 40;


// Create the triangle.
    triangle = (void *) malloc( sizeof( struct gr_triangle_d ) );
    if ( (void*) triangle == NULL )
        return;
    triangle->used = TRUE;
    triangle->magic = 1234;
    triangle->initialized = FALSE;
// down
    triangle->p[0].x = 0; 
    triangle->p[0].y = 0;
    triangle->p[0].z = 0;
    triangle->p[0].color = COLOR_RED;
// right
    triangle->p[1].x = (line_size>>1); 
    triangle->p[1].y = (line_size>>1);
    triangle->p[1].z =  0;
    triangle->p[1].color = COLOR_GREEN;
// left
    triangle->p[2].x = -(line_size>>1);
    triangle->p[2].y =  (line_size>>1);
    triangle->p[2].z =   0;
    triangle->p[2].color = COLOR_BLUE;

    triangle->initialized = TRUE;

    int i=0;
    int j=0;
    int max = 150;
    //int T=0;

    for(i=0; i<max; i++)
    {
        // clear
        demoClearSurface(dw,COLOR_BLACK);
        // Draw a lot of triangles.
        //for(j=0; j<max; j++)
        //{
            // translation
            triangle->p[0].x++;
            triangle->p[1].x++;
            triangle->p[2].x++;
            grTriangle3(dw,triangle);
        //};

        // flush surface
        demoFlushSurface(dw);
        rtl_yield();
        //T++;
    };
}

// demo: polygon type polyline
// asteroids space ship like.
void demoPolygon(void)
{
    struct gr_polygon_d *p;
    unsigned long vecList[8];
    
    struct gr_vec3D_d *v0;
    struct gr_vec3D_d *v1;
    struct gr_vec3D_d *v2;
    struct gr_vec3D_d *v3;
    struct gr_vec3D_d *v4;

    // ...

    int i=0;
    int TranslationOffset=0;
    int j=0;

// Structure
    p = (struct gr_polygon_d *) malloc( sizeof( struct gr_polygon_d ) );
    if ((void*)p==NULL){
        return;
    }

// polygon type
    p->type = POLYGON_POLYLINE;
// number of elements
    p->n = 6;

// clear vecList.
// This is a local list.

    p->list_address = (void*) vecList;

    for(i=0; i<8; i++){
        vecList[i] = 0;
    };

// Creating some points.
// 5 vectors

    v0 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v0==NULL){return;}

    v1 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v1==NULL){return;}

    v2 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v2==NULL){return;}

    v3 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v3==NULL){return;}

    v4 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v4==NULL){return;}

    vecList[0] = (unsigned long) v0;
    vecList[1] = (unsigned long) v1;
    vecList[2] = (unsigned long) v2;
    vecList[3] = (unsigned long) v3;
    vecList[4] = (unsigned long) v4;
    vecList[5] = (unsigned long) v0;  //circular

// loop
// animation loop.

    int times=0;

    while(1){

    times++;
    if(times>8){break;}
    
    // translation in Y
    TranslationOffset=0;
    
    // animation loop: 
    // clear the screen and draw the the model 10 times.
    
    for (i=0; i<10; i++){

    demoClearSurface(NULL,COLOR_BLACK);
           
    TranslationOffset = (TranslationOffset+i);
    
    v0->x = -(20);
    v0->y =  (20+TranslationOffset);
    v0->z =   0;
    v0->color = COLOR_WHITE;

    // fixed
    v1->x = (0);
    v1->y = (0+TranslationOffset);
    v1->z = 0;
    v1->color = COLOR_WHITE;

    v2->x = (20);
    v2->y = (20+TranslationOffset);
    v2->z =  0;
    v2->color = COLOR_WHITE;

    v3->x =   (0);
    v3->y = -(20-TranslationOffset);  
    v3->z =   0;
    v3->color = COLOR_WHITE;

    v4->x = -(20);
    v4->y =  (20+TranslationOffset);  
    v4->z =  0;
    v4->color = COLOR_WHITE;


// Draw
    xxxPolygonZ(p);
// Show
    demoFlushSurface(NULL);  
    
    for (j=0; j<8; j++){ gwssrv_yield(); }

    };
    };   //while
}


void demoPolygon2(void)
{
    struct gr_polygon_d *p;
    unsigned long vecList[8];
    
    struct gr_vec3D_d *v0;
    struct gr_vec3D_d *v1;
    struct gr_vec3D_d *v2;
    struct gr_vec3D_d *v3;
    struct gr_vec3D_d *v4;

    // ...

    int i=0;
    int TranslationOffset=0;
    int j=0;

// structure

    p = (struct gr_polygon_d *) malloc( sizeof( struct gr_polygon_d ) );
    if((void*)p==NULL){
        return;
    }

// polygon type
    p->type = POLYGON_POLYPOINT;
    //p->type = POLYGON_POLYLINE;
// number of elements
    p->n = 6;

// clear vecList.
// This is a local list.

    p->list_address = (void*) vecList;

    for(i=0; i<8; i++){
        vecList[i] = 0;
    };

// Creating some points.

    v0 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v0==NULL){return;}

    v1 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v1==NULL){return;}

    v2 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v2==NULL){return;}

    v3 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v3==NULL){return;}

    v4 = (struct gr_vec3D_d *) malloc( sizeof( struct gr_vec3D_d ) );
    if((void*)v4==NULL){return;}

    vecList[0] = (unsigned long) v0;
    vecList[1] = (unsigned long) v1;
    vecList[2] = (unsigned long) v2;
    vecList[3] = (unsigned long) v3;
    vecList[4] = (unsigned long) v4;
    vecList[5] = (unsigned long) v0;  //circular

// loop
// animation loop

    int times=0;

    while(1){

    times++;
    if(times>8){break;}
    
    // translation in Y
    TranslationOffset=0;
    
    // animation loop: 
    // clear the screen and draw the the model 10 times.
    
    for (i=0; i<10; i++){

    // clear surface
    demoClearSurface(NULL,COLOR_BLACK);
    
    TranslationOffset = (TranslationOffset+i);
    
    v0->x = -(20);
    v0->y =  (10+TranslationOffset);
    v0->z =   0;
    v0->color = COLOR_WHITE;

    // fixed
    v1->x = (20);
    v1->y = (10+TranslationOffset);
    v1->z =  0;
    v1->color = COLOR_WHITE;

    v2->x =  30;
    v2->y = (0+TranslationOffset);
    v2->z =  0;
    v2->color = COLOR_WHITE;

    v3->x = 0;
    v3->y = -(10-TranslationOffset);  
    v3->z =  0;
    v3->color = COLOR_WHITE;

    v4->x = -30;
    v4->y = (0+TranslationOffset);  
    v4->z = 0;
    v4->color = COLOR_WHITE;

// Draw

    //p->type = POLYGON_POLYPOINT;
    //xxxPolygonZ(p);
    //gws_refresh_rectangle(0,0,320,200);

    p->type = POLYGON_POLYLINE;
    xxxPolygonZ(p);

    // flush surface.
    demoFlushSurface(NULL);  
    
    //delay
    for (j=0; j<20; j++){ gwssrv_yield();}

    };
    };   //while
}


// IN: ?
static void __draw_demo_curve1(int position, int model_z)
{
    int yOffset = (position + position);
    //int modelz = 0;
    int modelz = (int) model_z;

// line
// a variaçao de y2 me pareceu certa.
// IN: ??
    
    plotQuadBezierSeg ( 
        0,   0,  modelz,          //x0, y0, z0, //ponto inicial
        40,  40, modelz,          //x1, y1, z1, //?
       100,  20+yOffset, modelz,  //x2, y2, z2, //ponto final
       GRCOLOR_LIGHTBLACK );

// String! char by char.
// IN: x,y,color,c,z

    plotCharBackbufferDrawcharTransparentZ ( 
        40+ (8*0), 
        20+yOffset, 
        GRCOLOR_LIGHTRED, 'G', modelz );
    plotCharBackbufferDrawcharTransparentZ ( 
        40+ (8*1), 
        20+yOffset, 
        GRCOLOR_LIGHTRED, 'R', modelz );   
    plotCharBackbufferDrawcharTransparentZ ( 
        40+ (8*2), 
        20+yOffset, 
        GRCOLOR_LIGHTRED, 'A', modelz );
    plotCharBackbufferDrawcharTransparentZ ( 
        40+ (8*3), 
        20+yOffset, 
        GRCOLOR_LIGHTRED, 'M', modelz );
    plotCharBackbufferDrawcharTransparentZ ( 
        40+ (8*4), 
        20+yOffset, 
        GRCOLOR_LIGHTRED, 'A', modelz );
    plotCharBackbufferDrawcharTransparentZ ( 
        40+ (8*5), 
        20+yOffset, 
        GRCOLOR_LIGHTRED, 'D', modelz );
    plotCharBackbufferDrawcharTransparentZ ( 
        40+ (8*6), 
        20+yOffset, 
        GRCOLOR_LIGHTRED, 'O', modelz );
}

// Curva e string.
void demoCurve(void)
{
    register int i=0;
    register int j=0;
    int count=8;

    // IN: ?, near, far
    gr_depth_range( CurrentProjection, 0, 100 );

// loop

    while (count>0){

    count--;

    for (i=0; i<10; i++)
    {
        validate_background();
        demoClearSurface(NULL,GRCOLOR_LIGHTYELLOW);

        // IN: position, modelz
        __draw_demo_curve1(i,0);
        //__draw_demo_curve1(i,i*4);

        //invalidate_background();
        demoFlushSurface(NULL);      // flush surface
        
        // delay  
        //for (j=0; j<8; j++){ gwssrv_yield();}
    };
    }
}


// Control + arrow key
void FlyingCubeMove(int left_right, float value)
{
    // left
    if(left_right == 1){
        Cube1.model_move = (float) (Cube1.model_move - value); 
    }
    // right
    if(left_right == 2){
        Cube1.model_move = (float) (Cube1.model_move + value); 
    }
}


void demoFlyingCubeSetup(void)
{

//----------------
// Cube1
    register int i=0;

    Cube1.fThetaAngle = (float) 0.0f;
    Cube1.model_initial_distance = (float) 1.0f;
    Cube1.model_distance = (float) 0.0f;
    Cube1.model_move = (float) 0.0f;// left or right

// Initialize vectors.
    for (i=0; i<32; i++)
    {
        Cube1.vecs[i].x = (float) 0.0f;
        Cube1.vecs[i].y = (float) 0.0f;
        Cube1.vecs[i].z = (float) 0.0f;
    };

    Cube1.vecs[1].x = (float) -0.2f;  Cube1.vecs[1].y = (float) -0.2f;  Cube1.vecs[1].z = (float) 0.2f;
    Cube1.vecs[2].x = (float)  0.2f;  Cube1.vecs[2].y = (float) -0.2f;  Cube1.vecs[2].z = (float) 0.2f;
    Cube1.vecs[3].x = (float) -0.2f;  Cube1.vecs[3].y = (float)  0.2f;  Cube1.vecs[3].z = (float) 0.2f;
    Cube1.vecs[4].x = (float)  0.2f;  Cube1.vecs[4].y = (float)  0.2f;  Cube1.vecs[4].z = (float) 0.2f;

    Cube1.vecs[5].x = (float) -0.2f;  Cube1.vecs[5].y = (float)  0.2f;  Cube1.vecs[5].z = (float) -0.2f;
    Cube1.vecs[6].x = (float)  0.2f;  Cube1.vecs[6].y = (float)  0.2f;  Cube1.vecs[6].z = (float) -0.2f;
    Cube1.vecs[7].x = (float) -0.2f;  Cube1.vecs[7].y = (float) -0.2f;  Cube1.vecs[7].z = (float) -0.2f;
    Cube1.vecs[8].x = (float)  0.2f;  Cube1.vecs[8].y = (float) -0.2f;  Cube1.vecs[8].z = (float) -0.2f;

    Cube1.colors[0] = GRCOLOR_LIGHTYELLOW;
    Cube1.colors[1] = GRCOLOR_LIGHTMAGENTA;
    Cube1.colors[2] = GRCOLOR_DARKBLUE;
    Cube1.colors[3] = GRCOLOR_DARKGREEN;
    Cube1.colors[4] = GRCOLOR_DARKRED;
    Cube1.colors[5] = GRCOLOR_DARKCYAN;
    Cube1.colors[6] = GRCOLOR_DARKMAGENTA;
    Cube1.colors[7] = GRCOLOR_DARKYELLOW;
    Cube1.colors[8] = GRCOLOR_DARKWHITE;
    Cube1.colors[9] = GRCOLOR_LIGHTBLACK;
    Cube1.colors[10] = GRCOLOR_LIGHTBLUE;
    Cube1.colors[11] = GRCOLOR_LIGHTGREEN;

//----------------
// Taskbar
    //demoClearWA(COLOR_BLACK);
    //wm_Update_TaskBar("Hello",TRUE);
    game_update_taskbar = FALSE;
}

void demoFlyingCube(void)
{
    //float time = 0.02f;
    //float time = 0.04f;
    float time = 0.08f;

    frames++;

    //demoClearWA(COLOR_BLACK);                //clear surface
    gramado_clear_surface(NULL,COLOR_BLACK);   //clear surface
    drawFlyingCube( (float) time );
    //yellowstatus0("test",FALSE);  //draw but don't refresh
    //if(game_update_taskbar){
    //    wm_Update_TaskBar("53$",FALSE); //redraw, but not refresh
    //    game_update_taskbar = FALSE;
    //}
    gramado_flush_surface(NULL);
}

