	// gramado 3d primitives.


#include <gws.h>


// See:
// https://wiki.osdev.org/3D_Renderer_Basics
// http://members.chello.at/easyfilter/bresenham.html
// ...


// =============================================================
// #projection:
// For orthographics projection there is no scaling factor.
// For perspective, we do have scaling.


static unsigned long HotSpotX=0;
static unsigned long HotSpotY=0;


int grInit(void)
{

    unsigned long w = gws_get_device_width();
    unsigned long h = gws_get_device_height();

    if ( w == 0 || h == 0 ){
        printf ("grInit: [FAIL] w h\n");
        exit(1);
    }

    HotSpotX = (w/2);
    HotSpotY = (h/2);

    return 0;
}


// low level plot.
int grPlot0 (int z, int x, int y, unsigned long color)
{

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



    //#debug: Exagero?!
    if ( (void*) CurrentScreen == NULL )
    {
        printf("grPlot0: CurrentScreen\n");
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
        
        
        if ( 0 <= X < CurrentScreen->width && 0 <= Y < CurrentScreen->height )
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

        if ( 0 <= X < CurrentScreen->width && 0 <= Y < CurrentScreen->height )
        {
            pixelBackBufferPutpixel ( color, X, Y );  
            return 0;
        }
        return -1;
    }

    return -1;
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
        if (e2 <= dx) {                                       // e_xy+e_y < 0 
            if (y0 == y1) break;
            err += dx; y0 += sy;
        }
    }
}
*/



//Bresenham in 3D
//The algorithm could be extended to three (or more) dimensions.

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
      
      //setPixel(x0,y0,z0);
      grPlot0 ( z0, x0, y0, color);
      
      if (i-- == 0) break;
      x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; } 
      y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; } 
      z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; } 
   }
}


void
rectangle (
    int left, int top, 
    int right, int bottom,
    unsigned long color )
{

     //cima
     plotLine3d ( 
         left, top,   0,
         right, top,  0,
         color );

     //baixo
     plotLine3d ( 
         left, bottom,   0,
         right,bottom,  0,
         color );

     //esquerda
     plotLine3d ( 
         left, top,   0,
         left, bottom,  0,
         color );

     //direita
     plotLine3d ( 
         right,    top,   0,
         right, bottom,  0,
         color );
}
 

void
rectangleZ (
    int left, int top, 
    int right, int bottom,
    unsigned long color,
    int z )
{

     //cima
     plotLine3d ( 
         left, top,   z,
         right, top,  z,
         color );

     //baixo
     plotLine3d ( 
         left, bottom,   z,
         right,bottom,  z,
         color );

     //esquerda
     plotLine3d ( 
         left, top,   z,
         left, bottom,  z,
         color );

     //direita
     plotLine3d ( 
         right,    top,   z,
         right, bottom,  z,
         color );
}



void
ras_rectangleZ (
    int left, int top, 
    int right, int bottom,
    unsigned long color,
    int z )
{

     int h=0;
     
     for (h=top;h<bottom; h++){

     //cima
     plotLine3d ( 
         left, h,   z,
         right, h,  z,
         color );
    }
    
     //baixo
     //plotLine3d ( 
         //left, bottom,   z,
         //right,bottom,  z,
         //color );

     //esquerda
     //plotLine3d ( 
         //left, top,   z,
         //left, bottom,  z,
         //color );

     //direita
     //plotLine3d ( 
         //right,    top,   z,
         //right, bottom,  z,
         //color );
}





void 
cube ( 
    int bx0, int by0, int bx1, int by1,  //back rect
    int fx0, int fy0, int fx1, int fy1,  //front rect 
    unsigned long color)
{

    //back
    //1st rectangle
    //rectangle(100,200,200,300, color );
    rectangle ( bx0, by0, bx1, by1, color );
    
    //front
    //2nd rectangle
    //rectangle(150,250,250,350, color);
    rectangle ( fx0, fy0, fx1, fy1, color );
    
    
    // 1st line
    plotLine3d (bx0, by0, 0, fx0, fy0, 0, color);
    // 2nd line
    plotLine3d (bx1, by1, 0, fx1, fy1, 0, color);
    // 3rd line
    plotLine3d (bx0, by1, 0, fx0, fy1, 0, color);
    // 4th line
    plotLine3d (bx1, by0, 0, fx1, fy0, 0, color);
}



// #todo
// It has an orthogonal projection
// cubeZOrtho(

void 
cubeZ ( 
    int bx0, int by0, int bx1, int by1,  //back rect
    int fx0, int fy0, int fx1, int fy1,  //front rect 
    unsigned long color, int z )
{

    int h=0; 
    int d=0;
    int i=0;

    // aspect ratio = height/width
    // sem float isso da zero.
    
    // remember: we can't divide by zero.
    //int scale = 0;
    //scale = z; 


    //#todo
    // a rasterizaçao deve ser opcional
    // colocar uma flag nos argumentos.
    
    // We need to check the limits and do not paint what is
    // out of the limits.

    //back (NORTH) PROJECTED!!!
    //1st rectangle
    //rectangle(100,200,200,300, color );
    rectangleZ     ( bx0, by0, bx1, by1, color, z );
    ras_rectangleZ ( bx0, by0, bx1, by1, color, z );
    
    //front
    //2nd rectangle
    //rectangle(150,250,250,350, color);
    //rectangleZ ( fx0, fy0, fx1, fy1, color,z );
    //ras_rectangleZ ( fx0, fy0, fx1, fy1, color,z ); 

    //
    // lines
    //
    
    // 1st line esq baixo
    plotLine3d (bx0, by0, z, fx0, fy0, z, color);
    // 2nd line
    plotLine3d (bx1, by1, z, fx1, fy1, z, color);
    // 3rd line
    plotLine3d (bx0, by1, z, fx0, fy1, z, color);
    // 4th line dir baixo
    plotLine3d (bx1, by0, z, fx1, fy0, z, color);
    
    
    //
    // right
    //
    
    //ras diagonal
    //rectangleZ ( bx1, by1, fx1, fy0, COLOR_RED,z ); //marcador.
    i=0;
    for (h=by0; h<by1; h++){
        plotLine3d (bx1, h, z, fx1, fy0+i, z, color);
        i++;
    }

    //
    // left
    //

    //ras diagonal
    //rectangleZ ( bx0, by1, fx0, fy0, COLOR_RED,z ); //marcador.
    i=0;
    for (h=by0; h<by1; h++){
        plotLine3d (bx0, h, z, fx0, fy0+i, z, color);
        i++;
    }
    
    //
    // front
    //
    
     //front   (SOUTH)
    //2nd rectangle
    //rectangle(150,250,250,350, color);
    rectangleZ     ( fx0, fy0, fx1, fy1, color, z );
    ras_rectangleZ ( fx0, fy0, fx1, fy1, color, z ); 
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
   int err =  (2-(2*r));

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
       //setPixel(x1, y0); /*   I. Quadrant */
       //setPixel(x0, y0); /*  II. Quadrant */
       //setPixel(x0, y1); /* III. Quadrant */
       //setPixel(x1, y1); /*  IV. Quadrant */
       
       
       grPlot0 ( 0, x1, y0, color);
       grPlot0 ( 0, x0, y0, color);
       grPlot0 ( 0, x0, y1, color);
       grPlot0 ( 0, x1, y1, color);
       
       
       e2 = (2*err);
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    
    } while (x0 <= x1);


    /* too early stop of flat ellipses a=1 */
    while (y0-y1 < b) 
    {
       //setPixel(x0-1, y0); /* -> finish tip of ellipse */
       //setPixel(x1+1, y0++); 
       //setPixel(x0-1, y1);
       //setPixel(x1+1, y1--); 
   
        grPlot0 ( 0, x0-1,    y0, color);
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
       //setPixel(x1, y0); /*   I. Quadrant */
       //setPixel(x0, y0); /*  II. Quadrant */
       //setPixel(x0, y1); /* III. Quadrant */
       //setPixel(x1, y1); /*  IV. Quadrant */
       
       
       grPlot0 ( z, x1, y0, color);
       grPlot0 ( z, x0, y0, color);
       grPlot0 ( z, x0, y1, color);
       grPlot0 ( z, x1, y1, color);
       
       
       e2 = (2*err);
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
    
    } while (x0 <= x1);


    /* too early stop of flat ellipses a=1 */
    while (y0-y1 < b) 
    {
       //setPixel(x0-1, y0); /* -> finish tip of ellipse */
       //setPixel(x1+1, y0++); 
       //setPixel(x0-1, y1);
       //setPixel(x1+1, y1--); 
   
        grPlot0 ( z, x0-1,    y0, color);
        grPlot0 ( z, x1+1,  y0++, color);
        grPlot0 ( z, x0-1,    y1, color);
        grPlot0 ( z, x1+1,  y1--, color);
    };
}


void noraDrawingStuff(void)
{
    int x=0;
    int y=0;


    // colunas.
    for (x=0; x< SavedX; x++)    
    {
        for (y=0; y<SavedY; y++)
        {
            if ( x != 0 )
            {
                if ( y % x == 0 ){
                    pixelBackBufferPutpixel ( COLOR_BLACK, x, y );  
                }
            }
        };
        
        if ( x >= SavedY) { 
            break; 
        }
    };
}


void noraDrawingStuff3(int x, int y, int z)
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
            if ( _x != 0 )
            {
                if ( _y % _x == 0 ){
                    //pixelBackBufferPutpixel ( COLOR_BLACK, x, y );  
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
    
    while (1){

    for (i=0; i<100; i++){

       rectBackbufferDrawRectangle ( 
           0, 0, 
           320, 200, 
           COLOR_BLACK, 1 );
                
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


// Fibonacci Series using Recursion 
int fib(int n) 
{ 

    int a=0;
    int b=0;

    if (n <= 1){ 
        return n; 
    }
    
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
 
                //pixelBackBufferPutpixel ( color, x + x2, y );  
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

    for ( y2=0; y2 < gcharHeight; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2 < gcharWidth; x2++ )
        {

           // Put pixel. 
            if ( ( *work_char & bit_mask ) ){
 
                //pixelBackBufferPutpixel ( color, x + x2, y );  
                grPlot0 ( z, x + x2, y, color ); 
            }

            // Rotate bitmask.
            bit_mask = (bit_mask >> 1);  
        };

        // Próxima linha da 8 linhas do caractere.
        y++; 
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

    struct gws_screen_d *screen;


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
    // Screen
    //

    screen = dc->screen;

    if ( (void*) screen == NULL )
    {
        printf ("screen\n");
        return;
     }


    if (screen->used != 1 || screen->magic != 1234 )
    {
        printf ("screen validation\n");
        return;
     }



    // 3 BPP
    if (screen->bpp == 24) {
        
        dst = (unsigned char *) screen->frontbuffer;  //dst = dc->body;
        i = (int) (screen->height * screen->pitch);   //i = dc->width_internal*dc->height;

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

    struct gws_screen_d *screen;


    printf ("grDCColorChg:\n");

    // Device context
    if ( (void *) dc == NULL )
        return;

    if (dc->used != 1 || dc->magic != 1234 )
        return;    



    //
    // Screen
    //

    screen = dc->screen;

    if ( (void*) screen == NULL )
        return;

    if (screen->used != 1 || screen->magic != 1234 )
        return;    


    if (screen->bpp == 24) {    
        
        dst = (unsigned char *) screen->frontbuffer;
        i = (int) (screen->height * screen->pitch);
        
        while (i--){
            
            if (*dst == subpixel_src_color){
                *dst++ = subpixel_dst_color;
            }else{
                dst++;
            };
        };
    }
}














