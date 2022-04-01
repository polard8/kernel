
// demos.c
// A place for demos.


#include "gws.h"


int gUseDemos = TRUE;


/*
static int projection4x4[4][4] = { 
        {1,0,0,0}, 
        {0,1,0,0},
        {0,0,0,0},
        {1,1,0,0}
        };
*/

void demoLines(void)
{
    int i=0;
    for (i=0; i<320; i+=5)
    {
        //3d
        plotLine3d ( 
            0,i,0,      //x,y,z 
            320-i,0,0,  //x,y,z 
            COLOR_WHITE); 

        //3d
        plotLine3d ( 
            0,i,0,      //x,y,z 
            -(320-i),0,0,  //x,y,z 
            COLOR_WHITE); 
      
        // ====

        //3d
        plotLine3d ( 
            -i,0,0,      //x,y,z 
            0,-(320-i),0,  //x,y,z 
            COLOR_WHITE); 

        //3d
        plotLine3d ( 
            i,0,0,      //x,y,z 
           0, -(320-i),0,  //x,y,z 
            COLOR_WHITE); 


    };
    refresh_screen();
}


// Start surface
void demoClearSurface(unsigned int color)
{
    // #todo
    // We can do this for more resolutions. 

    //asm("cli");
    // Limpa em mostra na resolução 320x200
    rectBackbufferDrawRectangle ( 
           0, 0, 320, 200, color, 1, 0 );
    //asm("sti");
}


// #todo
// We can do this for more resolutions. 
// mostra na resolução 320x200
void demoFlushSurface(void)
{
    gws_refresh_rectangle(0,0,320,200);
    //rtl_invalidate_screen();
}

void setupCatModel(int eyes, int whiskers, int mouth )
{
    CatModel.eyesVisible     = eyes;
    CatModel.whiskersVisible = whiskers;
    CatModel.mouthVisible    = mouth;
}


//worker
void __draw_cat(int eye_scale)
{
//---
    // head
    plotCircleZ ( 0, 12, 25, GRCOLOR_LIGHTBLACK, 0); 

    // eyes
    if ( CatModel.eyesVisible == TRUE )
    {
        plotCircleZ ( -10, 20, 1+eye_scale, GRCOLOR_LIGHTBLACK, 0); 
        plotCircleZ (  10, 20, 1+eye_scale, GRCOLOR_LIGHTBLACK, 0); 
    }

    // whiskers
    if ( CatModel.whiskersVisible == TRUE ){
        // =
        plotLine3d ( -40, 8,0, -4, 5,0, GRCOLOR_LIGHTBLACK); 
        plotLine3d ( -40, 5,0, -4, 4,0, GRCOLOR_LIGHTBLACK); 
        plotLine3d ( -40, 2,0, -4, 3,0, GRCOLOR_LIGHTBLACK); 

        // =
        plotLine3d ( 4, 5,0, 40, 8,0, GRCOLOR_LIGHTBLACK); 
        plotLine3d ( 4, 4,0, 40, 5,0, GRCOLOR_LIGHTBLACK); 
        plotLine3d ( 4, 3,0, 40, 2,0, GRCOLOR_LIGHTBLACK); 
    }

    // mouth
    if ( CatModel.mouthVisible == TRUE ){
        plotLine3d ( -10, -2,0, 10, -2,0, GRCOLOR_LIGHTBLACK); 
    }
//---
}

void demoCat (void)
{
    register int i=0;
    int j=0;
    int count = 8;

// Setup model
// eyes, whiskers, mouth
    setupCatModel(TRUE,TRUE,TRUE);

// Loop
    while (count>0)
    {
        for (i=0; i<8; i++)
        {
            validate_background();                 //begin paint
            demoClearSurface(GRCOLOR_LIGHTCYAN);   // Clear surface
            __draw_cat(i);                         // IN: eye scale
            invalidate_background();               // end paint
            //demoFlushSurface();                  // Flush surface
            for (j=0; j<8; j++){ gwssrv_yield();}  // Delay
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
        plotLine3d ( x1,y1,0, x2,y2,0, COLOR_WHITE); 
            y1+=8;                 //You should modify this if
            x2+=8;                 //it's not an equal square (like 250x250)
    };

    //gws_refresh_rectangle(0,0,320,200);
    demoFlushSurface();  
}


//
// == fred demo ========================================
//


void demoFred0(void)
{
    register int i=0;

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
            
        //rtl_invalidate_screen();
    };
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


void demoFred2(void)
{
    register int i=0;

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

           demoClearSurface(COLOR_BLACK);
             
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
            demoFlushSurface();
            
            gwssrv_yield();
            gwssrv_yield();
            gwssrv_yield();
            gwssrv_yield();
            gwssrv_yield();
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
    struct gr_triandle_d *triangle;

    //printf("demoTriangle:\n");

    triangle = (void *) malloc( sizeof( struct gr_triandle_d ) );

    if ( (void*) triangle == NULL )
        return;


    // down
    triangle->p[0].x = 0; 
    triangle->p[0].y = 0;
    triangle->p[0].z = 0;
    triangle->p[0].color = COLOR_RED;

    // right
    triangle->p[1].x = 80; 
    triangle->p[1].y = 80;
    triangle->p[1].z =  0;
    triangle->p[1].color = COLOR_GREEN;

    // left
    triangle->p[2].x = -80;
    triangle->p[2].y =  80;
    triangle->p[2].z =   0;
    triangle->p[2].color = COLOR_BLUE;


    int i=0;
    int T=0;

    for(i=0; i<10; i++)
    {

        // clear
        demoClearSurface(COLOR_BLACK);

        // Draw
        xxxTriangleZ(triangle);
        
        // translation
        triangle->p[0].x++;
        triangle->p[1].x++;
        triangle->p[2].x++;

        // flush surface
        demoFlushSurface();  
        
        T++;
    };
}


// Build a mesh o triangles.
// IN: Number of elements: (it needs to be 80 for now.
struct gr_mesh_triangle_d *__demoMesh1_worker(int number_of_elements)
{

// #bugbug
// We do not free the memory

    struct gr_mesh_triangle_d *m;

    int N = number_of_elements;

    struct gr_triandle_d *last_tri;
    struct gr_triandle_d *tmp_tri;

    int i=0;
    int value=0;

    // 1=esq | 2=right
    int sentido=1;
    //int sentido=2;

    debug_print("__demoMesh1_worker:\n");


// The mesh structure.
    m = (void *) malloc( sizeof( struct gr_mesh_triangle_d ) );
    if( (void*) m == NULL ){
        return NULL;
    }

// quantidade
    m->n = N;


// loop: 
// Compose
// Vamos criar os triangulos e atribuir valores a eles.

    for(i=0; i<N; i++){

    // Create a temporary triangle structure.
    tmp_tri = (void *) malloc( sizeof( struct gr_triandle_d ) );
    
    if( (void*) tmp_tri == NULL ){
        return NULL;
    }

    if ( (void*) tmp_tri != NULL )
    {
        // Se ele foi o primeiro a ser criado.
        if(i==0){
            m->first_triangle = (struct gr_triandle_d *) tmp_tri;
            m->last_triangle  = (struct gr_triandle_d *) tmp_tri;
        }
        
        // Se ja existe um criado anteriormente.
        if ( (void*) last_tri != NULL ){
            last_tri->next = (struct gr_triandle_d *) tmp_tri;
            last_tri = last_tri->next;
            
        // Se for o primeiro
        }else if ( (void*) last_tri == NULL ){
            m->last_triangle  = (struct gr_triandle_d *) tmp_tri;
            last_tri          = (struct gr_triandle_d *) tmp_tri;
            last_tri->next = NULL;
        }; 

        // split: 
        // fatia e muda o sentido da pintura.
        //if(value>40){sentido=2;}

        // down
        if(sentido==1){ tmp_tri->p[0].x = (0 - (value) ); }
        if(sentido==2){ tmp_tri->p[0].x = (0 + (value) ); }
        tmp_tri->p[0].y = 0;
        tmp_tri->p[0].z = 0;
        tmp_tri->p[0].color = GRCOLOR_LIGHTRED; 

        // left
        if(sentido==1){ tmp_tri->p[2].x = (-80 - (value) ); }
        if(sentido==2){ tmp_tri->p[2].x = (-80 + (value) ); }
        tmp_tri->p[2].y = 80;
        tmp_tri->p[2].z =  0;
        tmp_tri->p[2].color = GRCOLOR_LIGHTGREEN; 

        // right
        if(sentido==1){ tmp_tri->p[1].x = (80 - (value) ); }
        if(sentido==2){ tmp_tri->p[1].x = (80 + (value) ); }
        tmp_tri->p[1].y = 80;
        tmp_tri->p[1].z =  0;
        tmp_tri->p[1].color = GRCOLOR_LIGHTBLUE; 

        value++;
    }
    };


// finaliza a lista
    last_tri->next = NULL;

    debug_print("__demoMesh1_worker: done\n");
    
    return (struct gr_mesh_triangle_d *) m;
}


void __demoMesh1_transformation(struct gr_mesh_triangle_d *mesh)
{
    int i=0;
    int n=0;

    debug_print("__demoMesh1_transformation:\n");
    
    if ( (void *) mesh == NULL )
        return;
    
    n = mesh->n;

    struct gr_triandle_d *tmp_tri;
    
    tmp_tri = (struct gr_triandle_d *) mesh->first_triangle;
        
    for( i=0; i<n; i++)
    {
        if((void*) tmp_tri == NULL)
            break;
        
        // transformation

        // down 
        tmp_tri->p[0].x = tmp_tri->p[0].x + 1;
        tmp_tri->p[0].y = tmp_tri->p[0].y + 1;

        // left
        tmp_tri->p[2].x = tmp_tri->p[2].x + 1;
        tmp_tri->p[2].y = tmp_tri->p[2].y - 1;

        // right
        tmp_tri->p[1].x = tmp_tri->p[1].x - 1;
        tmp_tri->p[1].y = tmp_tri->p[1].y + 1;


        // próximo
        tmp_tri = (struct gr_triandle_d *) tmp_tri->next;
    };

    debug_print("__demoMesh1_transformation: done\n");
}


void 
__draw_mesh1(
    struct gr_mesh_triangle_d *mesh, 
    int number_of_elements )
{

    struct gr_mesh_triangle_d *m;
    
    m = (struct gr_mesh_triangle_d *) mesh;

    if( (void*) m == NULL )
        return;

//
    struct gr_triandle_d *tmp_tri;

    int i=0;
    int N=number_of_elements;

    //--
    tmp_tri = (struct gr_triandle_d *) m->first_triangle;
            
    for(i=0; i<N; i++)
    {
        if( (void*) tmp_tri == NULL )
            break;
        
        // Draw a valid triangle.
        if( (void*) tmp_tri != NULL )
        {
            xxxTriangleZ(tmp_tri);        
            tmp_tri = (struct gr_triandle_d *) tmp_tri->next;
        }
    };
    //--
}



// #todo
// Describe the routine.
// This builds and show a mesh o triangles.
void demoMesh1(void)
{
    struct gr_mesh_triangle_d *m;

    int i=0;
    int j=0;
    int w=0;
    static int N=80;

    debug_print("demoMesh1:\n");

    m = (struct gr_mesh_triangle_d *) __demoMesh1_worker(N);

    if( (void*) m == NULL )
        return;

    if (m->n != 80)
        return;

    //if (m->n != N)
        //return;

    struct gr_triandle_d *tmp_tri;


//Quais elementos teremos no gato.
    setupCatModel(TRUE,TRUE,TRUE);

// loop: 
// Draw all the triangles.

    for(j=0; j<80; j++)
    {
        validate_background();  // Begin paint
        
        demoClearSurface(GRCOLOR_LIGHTYELLOW);

        __draw_mesh1(m,N);  // Draw the mesh1
        __draw_demo_curve1(j>>3);
        __draw_cat(j>>3);   // Draw the cat. IN: eye scale.
                        
        // Show the frame.
        //demoFlushSurface();
        //#bugbug: The compositor is flushing the backbuffer
        // into the lfb during the painting routine.
        invalidate_background();  //End Paint

        // transforma o mesh
        __demoMesh1_transformation(m);
        
        for (w=0; w<8; w++){ gwssrv_yield();}
    };

    debug_print("demoMesh1: done\n");
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

    //rectBackbufferDrawRectangle ( 
        //0, 0, 320, 200, COLOR_BLACK, 1,0 );
    
    demoClearSurface(COLOR_BLACK);
           
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

    gwssrv_debug_print("calling xxxPolygonZ\n");

    // Draw

    xxxPolygonZ(p);

    // Show
    demoFlushSurface();  
    
    for (j=0; j<8; j++){ gwssrv_yield(); }

    };
    };   //while

    
    gwssrv_debug_print("DONE\n");
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
    demoClearSurface(COLOR_BLACK);
    
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

    gwssrv_debug_print("calling xxxPolygonZ\n");


    // Draw


    //p->type = POLYGON_POLYPOINT;
    //xxxPolygonZ(p);
    //gws_refresh_rectangle(0,0,320,200);

    p->type = POLYGON_POLYLINE;
    xxxPolygonZ(p);

    // flush surface.
    demoFlushSurface();  
    
    //delay
    for (j=0; j<20; j++){ gwssrv_yield();}

    };
    };   //while

    gwssrv_debug_print("DONE\n");
    //printf ("DONE\n");
}


void demoCube1(void)
{
    register int i=0;
    register int j=0;

    struct gr_cube_d *cube;
    cube = (void *) malloc( sizeof( struct gr_cube_d ) );
    
    if ( (void*) cube == NULL )
        return;

// marcador.
//#bugbug: Esse nao eh momento de pintura,
// apenas estamos setando os valores dos vertices.

    //noraDrawingStuff3 (0,0,0);

// =========
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

// =========
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


    // clear
    demoClearSurface(GRCOLOR_LIGHTCYAN);
    
    // draw
    xxxDrawCubeZ(cube);

    // show
    demoFlushSurface();  
}


// inflate varias vezes.
// only on jail
void demoCube2 (void)
{
    register int i=0;
    register int j=0;
 
    static int action = 1000; // inflate.

    int count=4;

    int modelX=0;
    int modelY=0;
    int modelZ=0;
    
    int zNear=0;
    int zFar=0;
    int zMaxModulus=0; // máximo em qualquer das direções.

    struct gr_cube_d *cube;
    cube = (void *) malloc( sizeof( struct gr_cube_d ) );

    if ( (void*) cube == NULL )
        return;

// =========
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

// =========
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


//marcador.
//    noraDrawingStuff3 (0,0,0);

    while (count>0)
    {
        count--;

        // =============================
        // Drawing 20 times while inflate or while deflating.
        
        zNear       = -(40/2);  // max negative z.
        zFar        =  (40/2);  // max positive z.
        zMaxModulus =  (40/2);  // max z, negative or positive.
        
        //porque o z eh reduzido duas vezes.
        //entao esse eh o limite da reduçao.

        for (j=0; j < zMaxModulus; j++)
        {
            //rectBackbufferDrawRectangle ( 0, 0, 320, 200, COLOR_BLACK, 1,0 ); 
            demoClearSurface(GRCOLOR_LIGHTCYAN);
            if (action==1000){
                modelZ = (modelZ-j);    // o objeto se aproxima.
                //if (modelZ > zNear)
                    xxxInflateCubeZ (cube, 1);  // go near
            }else{
                modelZ = (modelZ+j);   // o objeto se afasta.
                //if (modelZ < zFar)     // se nos afastamos mas não chegamos no limite.
                    xxxDeflateCubeZ (cube, 1);  // go far
            };
            
            // draw cube
            xxxDrawCubeZ(cube);
            
            // draw string
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*0), cube->p[0].y, COLOR_RED, 'G', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*1), cube->p[0].y, COLOR_RED, 'R', cube->p[0].z );   
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*2), cube->p[0].y, COLOR_RED, 'A', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*3), cube->p[0].y, COLOR_RED, 'M', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*4), cube->p[0].y, COLOR_RED, 'A', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*5), cube->p[0].y, COLOR_RED, 'D', cube->p[0].z );
            plotCharBackbufferDrawcharTransparentZ ( cube->p[0].x + (8*6), cube->p[0].y, COLOR_RED, 'O', cube->p[0].z );
            
            //gws_refresh_rectangle(0,0,320,200);
            demoFlushSurface();  
            for(i=0;i<8;i++){ gwssrv_yield(); }
        };
        
        // Switch action.
        // Alternating between inflate and deflate.
        
        switch (action){
            case 1000: action = 2000; break;
            case 2000: action = 1000; break;
            default:   action = 1000; break;
        };

        // 'count' times
    
    }; //while--
}


void __draw_demo_curve1(int position)
{
    int i=position;

    // line
    //a variaçao de y2 me pareceu certa.
    //IN: ??
    plotQuadBezierSeg ( 
        0,   0,  0,      //x0, y0, z0, //ponto inicial
        40,  40, 0,      //x1, y1, z1, //?
       100,  20+i+i, 0,  //x2, y2, z2, //ponto final
       GRCOLOR_LIGHTBLACK );

    //string! char by char
    //IN: ??
    plotCharBackbufferDrawcharTransparentZ ( 40+ (8*0), 20+i+i, GRCOLOR_LIGHTRED, 'G', 0 );
    plotCharBackbufferDrawcharTransparentZ ( 40+ (8*1), 20+i+i, GRCOLOR_LIGHTRED, 'R', 0 );   
    plotCharBackbufferDrawcharTransparentZ ( 40+ (8*2), 20+i+i, GRCOLOR_LIGHTRED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ ( 40+ (8*3), 20+i+i, GRCOLOR_LIGHTRED, 'M', 0 );
    plotCharBackbufferDrawcharTransparentZ ( 40+ (8*4), 20+i+i, GRCOLOR_LIGHTRED, 'A', 0 );
    plotCharBackbufferDrawcharTransparentZ ( 40+ (8*5), 20+i+i, GRCOLOR_LIGHTRED, 'D', 0 );
    plotCharBackbufferDrawcharTransparentZ ( 40+ (8*6), 20+i+i, GRCOLOR_LIGHTRED, 'O', 0 );
}


void demoCurve(void)
{
    register int i=0;
    register int j=0;
    int count=4;

    while (count>0){

        count--;

    for (i=0; i<10; i++)
    {
        validate_background();
        demoClearSurface(GRCOLOR_LIGHTYELLOW);

        __draw_demo_curve1(i);

        invalidate_background();
        //demoFlushSurface();          // flush surface
        
        // delay  
        for (j=0; j<8; j++){ gwssrv_yield();}
    };
    }
}


// #bugbug
// It's not working.
// page fault.
void demoMatrix1(void)
{
/*

    register int i=0;
    
     //#define N 4

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


    //int m1[10][10];
    //int m2[10][10];
    //int m2[3][1];
    //int  r[10][10];


    //grPlot0 ( NULL,  0, -50, -50, COLOR_WHITE ); 
    //grPlot0 ( NULL,  0, 50, -50, COLOR_WHITE ); 
    //grPlot0 ( NULL,  0, 50, 50, COLOR_WHITE ); 
    //grPlot0 ( NULL,  0, -50, 50, COLOR_WHITE ); 
   
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

    
    int count=4;
    
    while (count>0){

    count--;

    for (i=0; i<8; i++){

       // Clear surface
       demoClearSurface(COLOR_BLACK);
        
       // See: Where is this projection?
       multiply4 ( projection4x4, mat2, res );
       
       //z,x,y
       grPlot0 ( NULL, res[0][2], res[0][0], res[0][1], COLOR_WHITE); 
       grPlot0 ( NULL, res[1][2], res[1][0], res[1][1], COLOR_WHITE); 
       grPlot0 ( NULL, res[2][2], res[2][0], res[2][1], COLOR_WHITE); 
       grPlot0 ( NULL, res[3][2], res[3][0], res[3][1], COLOR_WHITE); 
   
       
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

       // Flush surface
       demoFlushSurface();

       // delay
       gwssrv_yield();
       gwssrv_yield(); 
       };
    };
*/
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
    case 5: demoCube1();  break;
    case 6: demoCube2();  break;
    case 7: demoCurve();  break;
    case 8: demoMatrix1();  break;
    case 9: demoCat();  break;
    case 10: demoTriangle();  break;
    case 11: demoMesh1();  break;
    case 12: demoLine1();  break;
    case 13: demoTerry();  break;  //See: window.c
    case 14: demoPolygon();  break; 
    case 15: demoPolygon2();  break;
    default:  break;
    };
}


