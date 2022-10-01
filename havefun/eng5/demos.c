
// demos.c
// A place for demos.

#include "gramado.h"

struct gws_window_d *__demo_window;


int gUseDemos = TRUE;

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

struct gws_window_d *
__create_demo_window (
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height );
//======================



void gr_embedded_setup(void)
{
    __setupCatModel(TRUE,TRUE,TRUE);
}

void gr_embedded_draw(void)
{
    demoCat();
}



struct gws_window_d *__create_demo_window (
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height )
{

    struct gws_window_d *w;

    if( (void*) __root_window == NULL )
        return NULL;

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


    if ( (void *) w == NULL )
    {
        return NULL;
    }

    if ( w->used != TRUE || 
         w->magic != 1234 )
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

// Start surface
void demoClearSurface(struct gws_window_d *clipping_window, unsigned int color)
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

// Limpa em mostra na resolução 320x200
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
    if( (void*) __demo_window != NULL ){
       if(__demo_window->magic==1234)
        ow = __demo_window;
    }



// model
    int model_x = (int) cat_x;
    int model_y = (int) cat_y;
    int model_z = (int) cat_z;

// eyes
    int eye1_x = model_x -10;
    int eye1_y = model_y +20;
    int eye2_x = model_x +10;
    int eye2_y = model_y +20;
    int eye_radius = (int) (1*eye_scale);
//---

// head
// IN: x,y,r,color,z
    grCircle3 ( 
        ow,
        model_x + 0,    //x
        model_y + 12,   //y
        25,   //r
        GRCOLOR_LIGHTBLACK,  //color 
        model_z );   // z 

// eyes
    if ( CatModel.eyesVisible == TRUE )
    {
        grCircle3 ( 
            ow,
            eye1_x, 
            eye1_y, 
            eye_radius, 
            GRCOLOR_LIGHTBLACK, 
            model_z );  //z 
        grCircle3 ( 
            ow,
            eye2_x, 
            eye2_y, 
            eye_radius, 
            GRCOLOR_LIGHTBLACK, 
            model_z );  //z 
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
       if(dw->magic==1234)
       {
           __demo_window = dw;
       }
    }



//---------------------

// depth cliping
    gr_depth_range(
        CurrentProjection,   // projection
        0,                   // zNear
        100 );               // zFar

// The camera for the cat.
    camera ( 
        0, 0, 0,   // position vector
        0, 0, 0,     // upview vector
        0, 0, 0 );   // lookat vector

// Setup model
// eyes, whiskers, mouth
    __setupCatModel(TRUE,TRUE,TRUE);



// #test
// Testing fpu
    //long r9 = (long) power4(9,3);
    //printf("9^3 = %d\n",(long)r9);
    //while(1){}


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


void demoLine1(void)
{

    // #bugbug
    // Needs to be a square ?

    if (current_mode != GRAMADO_JAIL)
        return;

    //int width = getWidth();
    //int height = getHeight();
    int width  = 200/2;  //320/2;
    int height = 200/2;

    int x1 = 0, y1 = 0,
        x2 = 0, y2 = height;
    
    while (y1 < height) {
        //g.drawLine(x1, y1, x2, y2);
        plotLine3d ( NULL, x1,y1,0, x2,y2,0, COLOR_WHITE); 
            y1+=8;                 //You should modify this if
            x2+=8;                 //it's not an equal square (like 250x250)
    };

    demoFlushSurface(NULL);  
}



void demo34567(void)
{
    int i=0;
    for(i=0; i<1001; i++)
    {
        //IN: window, z, x, y, color
        grPlot0 ( NULL, 0, i, i%2, COLOR_WHITE );
    };
}

//
// == fred demo ========================================
//


void demoFred0(void)
{
    register int i=0;

    for (i=0; i<100; i++)
    {

        if( (i%3) == 0 ||
            (i%4) == 0 ||
            (i%5) == 0 ||
            (i%6) == 0 ||
            (i%7) == 0 )
        {
            noraDrawingStuff3 (-i,-i,0);
            grCircle3 ( 
                NULL,
                -i % 55,    // x 
                -i % 55,    // y
                i % 55,     // r
                COLOR_GREEN, 
                i % 55);    // z
        }
        
        //noraDrawingStuff3 (i,i,0);

        //rectangle(8,8,i,i,COLOR_BLUE);
        //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
        //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);



        //grCircle3 ( NULL,-i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
        //cool
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
        //igual o de cima.
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
        //grCircle3 ( NULL,-i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
        //grEllipse ( i, i, i*5, i*5, COLOR_BLUE);
        //grEllipse3 ( i%20, i%20, i, i, COLOR_BLUE,i%20);
            
        //rtl_invalidate_screen();
    };

    refresh_screen();
}


void demoFred1(void)
{
    register int i=0;

    for (i=0; i<100; i++){
    
        //noraDrawingStuff3 (i,i,0);
        noraDrawingStuff3 (-i,-i,0);
        //rectangle(8,8,i,i,COLOR_BLUE);
        //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
        //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);
        //grCircle3 ( NULL,-i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);  //save this
        //grCircle3 ( NULL,-i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
        //cool
        grCircle3 ( NULL,-i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
        //igual o de cima.
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
        //grCircle3 ( NULL,-i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
        //grEllipse ( i, i, i*5, i*5, COLOR_BLUE);
        //grEllipse3 ( i%20, i%20, i, i, COLOR_BLUE,i%20);
    };
  
    refresh_screen();
}


void demoFred2(void)
{
    register int i=0;

    if(current_mode != GRAMADO_HOME)
        return;

    for (i=1; i< (800-600); i++){

        //noraDrawingStuff3 (i,i,0);
        noraDrawingStuff3 (-i,-i,0);
        //rectangle(8,8,i,i,COLOR_BLUE);
        //rectangleZ(i,i,i+20,i+20,COLOR_BLUE,i);
        //plotCircle ( -i % 20, -i % 20, i%20, COLOR_GREEN);
        //grCircle3 ( NULL,-i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);  //save this
        //grCircle3 ( NULL,-i % 20, -i % 20, i % 20, COLOR_GREEN, i % 20);   //save this
        //cool
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i % fib(20), COLOR_GREEN, i % fib(20) );
            
        //IN: x,y,r,color,z
        grCircle3 ( NULL,-i % fib(20), -i % fib(20), i % (1024-768), COLOR_RED, i % fib(20) );
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i %  fib(20/3), COLOR_GREEN, i % fib(20) );
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i %  fib(20/5), COLOR_BLUE, i % fib(20) );
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i %  fib(20/7), COLOR_YELLOW, i % fib(20) );
            
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i %  fib(20/), COLOR_GREEN, i % fib(20) );
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i %  fib(20/3), COLOR_YELLOW, i % fib(20) );
            
        //igual o de cima.
        //grCircle3 ( NULL,-i % fib(20), -i % fib(20), i, COLOR_GREEN, i % fib(20) );
        //grCircle3 ( NULL,-i % fib(7), -i % fib(7), i % fib(7), COLOR_GREEN, i % fib(7) );
        //grEllipse ( i, i, i*5, i*5, COLOR_BLUE);
        //grEllipse3 ( i%20, i%20, i, i, COLOR_BLUE,i%20);
    };
    refresh_screen();
}


// demo
// start up animation
// matrix multiplication
// #testing:
// Sometimes it fails.
void demoSA1(void)
{
    return;
/*
    int useClippingWindow = FALSE;
    //int useClippingWindow = TRUE;

//++
//=================
    struct gws_window_d *w;
    int wid=-1;

    if ( useClippingWindow == TRUE )
    {
        w = (struct gws_window_d *) CreateWindow ( 
                                    WT_SIMPLE, 
                                    0,  //style
                                    1,  //status
                                    1,  //view
                                    "demoSA1", 
                                    100, 120, 100, 100, 
                                    __root_window, 0, 
                                    COLOR_PINK, COLOR_YELLOW ); 
    
        if ( (void*) w == NULL ){
            printf ("demoSA1: w\n");
            //useClippingWindow = FALSE;
            return;
        }
        
        wid = RegisterWindow(w);

        if (wid<0){
            printf ("demoSA1: wid\n");
            //useClippingWindow = FALSE;
            return;
        }

        gws_show_window_rect(w);
    }
//=================
//--


    register int i=0;

    // To store result
    int res[4][4];  

    int mat1[4][4] = {  { 1, 1, 1, 1 },
                        { 2, 2, 2, 2 },
                        { 3, 3, 3, 3 },
                        { 4, 4, 4, 4 } };
 
    int mat2[4][4] = { { -5, -5, 0, 0 },
                       {  5, -5, 0, 0 },
                       {  5,  5, 0, 0 },
                       { -5,  5, 0, 0 } };
    

        
    
    if (current_mode != GRAMADO_JAIL){
        return;
    }
    

    int count=8;    

// loop
    while ( count>0 )
    {

        for (i=0; i<8; i++){

           demoClearSurface(NULL,COLOR_BLACK);
             
            // Plot four dots.
            // z,x,y
            if ( useClippingWindow == TRUE){
            grPlot0 ( w, res[0][2], res[0][0], res[0][1], COLOR_WHITE); 
            grPlot0 ( w, res[1][2], res[1][0], res[1][1], COLOR_WHITE); 
            grPlot0 ( w, res[2][2], res[2][0], res[2][1], COLOR_WHITE); 
            grPlot0 ( w, res[3][2], res[3][0], res[3][1], COLOR_WHITE); 
            }

            // NO clipping window
            if ( useClippingWindow == FALSE){
            grPlot0 ( NULL, res[0][2], res[0][0], res[0][1], COLOR_WHITE); 
            grPlot0 ( NULL, res[1][2], res[1][0], res[1][1], COLOR_WHITE); 
            grPlot0 ( NULL, res[2][2], res[2][0], res[2][1], COLOR_WHITE); 
            grPlot0 ( NULL, res[3][2], res[3][0], res[3][1], COLOR_WHITE); 
            }
          
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
  
            // transform
            multiply4 ( projection4x4, mat2, res );

            // Refresh and yield.
            demoFlushSurface(NULL);
            
            gwssrv_yield();
            gwssrv_yield();
            // ...
        };
        
        count--;
    };
*/
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
       if(dw->magic==1234)
       {
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

    // structure

    p = (struct gr_polygon_d *) malloc( sizeof( struct gr_polygon_d ) );
    if((void*)p==NULL){return;}
    
    // polygon type
    
    p->type = POLYGON_POLYLINE;
    
    // number of elements
    
    p->n = 6;
    p->list_address = (void*) vecList;


// clear vecList.
// This is a local list.

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


//
// loop
//

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

    //gwssrv_debug_print("DONE\n");
    //printf ("DONE\n");
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
    if((void*)p==NULL){return;}
    
    // polygon type
    
    p->type = POLYGON_POLYPOINT;
    //p->type = POLYGON_POLYLINE;
    
    // number of elements
    
    p->n = 6;
    p->list_address = (void*) vecList;


    // clear vecList.
    // This is a local list.

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


//
// loop
//

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

    //gwssrv_debug_print("calling xxxPolygonZ\n");


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

    //gwssrv_debug_print("DONE\n");
    //printf ("DONE\n");
}

// IN: ?
static void __draw_demo_curve1(int position, int model_z)
{

    int yOffset = position + position;
    
    //int modelz = 0;
    int modelz = (int) model_z;

    // line
    //a variaçao de y2 me pareceu certa.
    //IN: ??
    plotQuadBezierSeg ( 
        0,   0,  modelz,          //x0, y0, z0, //ponto inicial
        40,  40, modelz,          //x1, y1, z1, //?
       100,  20+yOffset, modelz,  //x2, y2, z2, //ponto final
       GRCOLOR_LIGHTBLACK );

    //string! char by char
    //IN: x,y,color,c,z
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

// curva e string.
void demoCurve(void)
{
    register int i=0;
    register int j=0;

    int count=8;

    gr_depth_range(
        CurrentProjection,
        0,      //near
        100 );  //far

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


// Rotina usada para rodar rotinas demo na inicializaçao.
// Seleciona a rotina demo a ser executada.
void demos_startup_animation(int i)
{
    switch (i){
    case 1: demoSA1();  break;
    case 2: demoFred0();  break;
    case 3: demoFred1();  break;
    case 4: demoFred2();  break;
    case 5:
        break;
    case 6:
        break;
    case 7: demoCurve();  break;
    case 8:
        break;
    case 9: demoCat();  break;
    case 10: demoTriangle();  break;
    case 11:
        break;
    case 12: demoLine1();  break;
    case 13:  
        break;
    case 14: demoPolygon();  break; 
    case 15: demoPolygon2();  break;
    default:
        break;
    };
}


