// a place for demos.


#include <gws.h>


void setupCatModel(int eyes, int whiskers, int mouth )
{
    CatModel.eyesVisible     = eyes;
    CatModel.whiskersVisible = whiskers;
    CatModel.mouthVisible    = mouth;
}

void demoCat (void)
{
    register int i=0;
    int j=0;
    int count = 20;

    //
    // Setup model
    //

    // eyes, whiskers, mouth
    setupCatModel(TRUE,TRUE,TRUE);

    //
    // Loop
    //

    while (count>0){
    
    for (i=0; i<8; i++){

       rectBackbufferDrawRectangle ( 
           0, 0, 320, 200, COLOR_BLACK, 1 );
    // head
    plotCircleZ ( 0, 12, 25, COLOR_WHITE, 0); 

    // eyes
    if ( CatModel.eyesVisible == TRUE ){
    plotCircleZ ( -10, 20, 1+i, COLOR_WHITE, 0); 
    plotCircleZ (  10, 20, 1+i, COLOR_WHITE, 0); 
    }

    // whiskers
    if ( CatModel.whiskersVisible == TRUE ){
    // =
    plotLine3d ( -40, 8,0, -4, 5,0, COLOR_WHITE); 
    plotLine3d ( -40, 5,0, -4, 4,0, COLOR_WHITE); 
    plotLine3d ( -40, 2,0, -4, 3,0, COLOR_WHITE); 

    // =
    plotLine3d ( 4, 5,0, 40, 8,0, COLOR_WHITE); 
    plotLine3d ( 4, 4,0, 40, 5,0, COLOR_WHITE); 
    plotLine3d ( 4, 3,0, 40, 2,0, COLOR_WHITE); 
    }

    // mouth
    if ( CatModel.mouthVisible == TRUE ){
    plotLine3d ( -10, -2,0, 10, -2,0, COLOR_WHITE); 
    }
    
    gws_refresh_rectangle(0,0,320,200);
    for (j=0; j<200; j++){ gwssrv_yield();}
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

    gws_refresh_rectangle(0,0,320,200);
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


//demo
//start up animation
//matrix multiplication
void demoSA1(void)
{
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



void demoTriangle(void)
{
    struct gr_triandle_d *triangle;


    //printf("demoTriangle:\n");

    triangle = (void *) malloc( sizeof( struct gr_triandle_d ) );
    if ( (void*) triangle != NULL )
    {

        triangle->p[0].x = 0;
        triangle->p[0].y = 0;
        triangle->p[0].z = 0;
        triangle->p[0].color = COLOR_RED;

        triangle->p[1].x = 80;
        triangle->p[1].y = 80;
        triangle->p[1].z = 0;
        triangle->p[1].color = COLOR_GREEN;

        triangle->p[2].x = -80;
        triangle->p[2].y = 80;
        triangle->p[2].z = 0;
        triangle->p[2].color = COLOR_BLUE;

        rectBackbufferDrawRectangle ( 0, 0, 320, 200, COLOR_BLACK, 1 );
        xxxTriangleZ(triangle);
    }

    gws_refresh_rectangle(0,0,320,200);
     
     //Debug
     //exit(0);

    //printf("demoTriangle: done\n");
}


void demoPolygon(void)
{
    struct gr_polygon_d *p;
    unsigned long polygon_list[8];
    
    struct gr_vec3D_d *v0;
    struct gr_vec3D_d *v1;
    struct gr_vec3D_d *v2;
    struct gr_vec3D_d *v3;
    struct gr_vec3D_d *v4;

    // ...

    int i=0;

    p = (struct gr_polygon_d *) malloc( sizeof( struct gr_polygon_d ) );
    if((void*)p==NULL){return;}
    
    p->n = 6;
    p->list_address = (void*) polygon_list;

    for(i=0; i<8; i++)
        polygon_list[i] = 0;


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


    polygon_list[0] = (unsigned long) v0;
    polygon_list[1] = (unsigned long) v1;
    polygon_list[2] = (unsigned long) v2;
    polygon_list[3] = (unsigned long) v3;
    polygon_list[4] = (unsigned long) v4;
    polygon_list[5] = (unsigned long) v0;  //circular
    
    
    int Offset=0;
    int j=0;

    // loop
    while(1){
    Offset=0;
    for (i=0; i<10; i++){

        rectBackbufferDrawRectangle ( 
            0, 0, 320, 200, COLOR_BLACK, 1 );

    Offset = Offset+i;
    
    v0->x = -(20);
    v0->y =  (20+Offset);
    v0->z =   0;
    v0->color = COLOR_WHITE;

    // fixed
    v1->x = (0);
    v1->y = (0+Offset);
    v1->z = 0;
    v1->color = COLOR_WHITE;

    v2->x = (20);
    v2->y = (20+Offset);
    v2->z =  0;
    v2->color = COLOR_WHITE;

    v3->x =   (0);
    v3->y = -(20-Offset);  
    v3->z =   0;
    v3->color = COLOR_WHITE;

    v4->x = -(20);
    v4->y =  (20+Offset);  
    v4->z =  0;
    v4->color = COLOR_WHITE;
        
    gwssrv_debug_print("calling xxxPolygonZ\n");
    xxxPolygonZ(p);
    
    gws_refresh_rectangle(0,0,320,200);
    
    for (j=0; j<20; j++){ gwssrv_yield();}
    };
    };   //while

    
    gwssrv_debug_print("DONE\n");
    //printf ("DONE\n");
}




// inflate varias vezes.
//only on jail
void demoCube1(void)
{
    register int i=0;
    register int j=0;


    struct gr_cube_d *cube;
    cube = (void *) malloc( sizeof( struct gr_cube_d ) );
    if ( (void*) cube != NULL )
    {
        // marcador.
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
void demoCube2 (void)
{
    register int i=0;
    register int j=0;
 
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
    }
}


void demoCurve(void)
{
    register int i=0;
    register int j=0;

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


        //string! char by char
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


void demoMatrix1(void)
{
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

    
    int count=4;
    
    while (count>0){

    count--;

    for (i=0; i<8; i++){

       rectBackbufferDrawRectangle ( 
           0, 0, 320, 200, COLOR_BLACK, 1 );
       
       // See: Where is this projection?
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
    
    case 10: demoTriangle(); break;

    case 11: demoPolygon(); break;
    
    case 12: demoLine1(); break;
    
    default: break;
    };
}




