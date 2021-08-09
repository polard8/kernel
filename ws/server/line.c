/*
 * File: line.c 
 * 
 * 
 */


#include <gws.h>


//#bugbug: use ul for 'color'.
void 
plotLineRect4 ( 
    int x1, int y1, 
    int x2, int y2, 
    int color )
{
    plotLine3d ( x1,y1,0, x2,y1,0, color );
    plotLine3d ( x2,y1,0, x2,y2,0, color );
    plotLine3d ( x2,y2,0, x1,y2,0, color );
    plotLine3d ( x1,y2,0, x1,y1,0, color );
}


//#bugbug: use ul for 'color'.
void 
plotLineRectZ ( 
    int x1, int y1, int z1, 
    int x2, int y2, int z2, 
    int color )
{
    plotLine3d ( x1,y1,z1, x2,y1,z2, color );
    plotLine3d ( x2,y1,z1, x2,y2,z2, color );
    plotLine3d ( x2,y2,z1, x1,y2,z2, color );
    plotLine3d ( x1,y2,z1, x1,y1,z2, color );
}

//#bugbug: use ul for 'color'.
//ok triangulo invertido.
void 
testLines ( 
    int x1, int y1, 
    int x2, int y2, 
    int color )
{
   int dx = x2-x1;
   int dy = y2-y1;
     
  plotLine3d(   x1,  y1-dy, 0,   x1+dx, y1   , 0, color);
  plotLine3d(x1+dx,     y1, 0,     x1, y1+dy , 0, color);
  plotLine3d(   x1,  y1+dy, 0,  x1-dx, y1    , 0, color);
  plotLine3d(x1-dx,     y1, 0,     x1, y1-dy , 0, color);
}


//#bugbug: use ul for 'color'.
//ok triangulo invertido.
void 
testLinesZ ( 
    int x1, int y1, int z1, 
    int x2, int y2, int z2, 
    int color )
{
    int dx = (x2-x1);
    int dy = (y2-y1);

    plotLine3d (   x1,  y1-dy, z1,   x1+dx, y1   , z2, color);
    plotLine3d (x1+dx,     y1, z1,     x1, y1+dy , z2, color);
    plotLine3d (   x1,  y1+dy, z1,  x1-dx, y1    , z2, color);
    plotLine3d (x1-dx,     y1, z1,     x1, y1-dy , z2, color);
}



// ...
//dx = x2 − x1
//dy = y2 − y1
//for x from x1 to x2 do
//    y = y1 + dy × (x − x1) / dx
//    plot(x, y)
// See: https://en.wikipedia.org/wiki/Line_drawing_algorithm

void
A_naive_line_drawing_algorithm(
    unsigned long x1,
    unsigned long x2, 
    unsigned long y1, 
    unsigned long y2, 
    unsigned long color)
{

    //loop
    register unsigned long x=0;
    register unsigned long y=0;

    unsigned long dx =  (x2 - x1);
    unsigned long dy =  (y2 - y1);


    for ( x = x1; x < x2; x++ )
    {
         // ugly
         y = (y1 + dy * (x - x1) / dx);
         
         pixelBackBufferPutpixel ( color, x, y );
    }; 
    
    //gwssrv_show_backbuffer();
}


//test1
void test_draw_line(void)
{
    register int g=0;

    for( g=0; g<400; g++ )
    {
            A_naive_line_drawing_algorithm ( 
                8, 750,                 //x1,x2
                8, (50 + (g*4)) ,       //y1,y2
                COLOR_YELLOW );
     };

    gwssrv_show_backbuffer();
}


// test2
// illusion
void test_draw_line2(void)
{
    register int g=0;
    
    unsigned long vertex1[2];
    unsigned long vertex2[2]; 

    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();

    // #todo
    // Check the w h validation.

    // horizontal
    for ( g=0; g<h; g=g+10 )
    {
            vertex1[0]=0;  //x1
            vertex1[1]=g;  //y1

            vertex2[0]=g;  //x2
            vertex2[1]=g;  //y2
            
            A_naive_line_drawing_algorithm ( 
                vertex1[0], vertex2[0],   //x1,x2
                vertex1[1], vertex2[1],   //y1,y2
                COLOR_YELLOW );
     };

    // horizontal
    for ( g=0; g<h; g=g+10 )
    {
            vertex1[0]=g;  //x1
            vertex1[1]=g;  //y1

            vertex2[0]=w;  //x2
            vertex2[1]=g;  //y2
            
            A_naive_line_drawing_algorithm ( 
                vertex1[0], vertex2[0],   //x1,x2
                vertex1[1], vertex2[1],   //y1,y2
                COLOR_BLUE );
     };

    gwssrv_show_backbuffer();
}


// O buffer é uma global nesse documento.
int servicelineBackbufferDrawHorizontalLine (void)
{
    unsigned long *message_address = (unsigned long *) &__buffer[0];

    // x1,y,x2,color
    unsigned long x1,y,x2,color;
      
    x1    = message_address[4];
    y     = message_address[5];
    x2    = message_address[6];
    color = message_address[7];

    lineBackbufferDrawHorizontalLine ( x1, y, x2, color );
    
    gws_show_backbuffer(); // for debug   
    return 0;
}



/* 
 * lineBackbufferDrawHorizontalLine:
 *     Draw a horizontal line on backbuffer. 
 */

void 
lineBackbufferDrawHorizontalLine ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2,  
    unsigned int color )
{

    unsigned long __x1 = x1;
    unsigned long __x2 = x2;
    unsigned long __y  = y;
    
    //debug_print("Line\n");
    
    if (__x1 > __x2){
        debug_print("lineBackbufferDrawHorizontalLine: __x1 > __x2\n");
        return;
    }

    if (__x2 > 800){
        debug_print("lineBackbufferDrawHorizontalLine: __x2 > 800\n");
        return;
    }
    
    while (__x1 < __x2)
    {
        pixelBackBufferPutpixel ( color, __x1, __y );
        __x1++;  
    };

    //debug_print("Line done\n");
}


//
// End.
//






