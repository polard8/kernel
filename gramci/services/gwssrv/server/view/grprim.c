	// gramado 3d primitives.


#include <gws.h>


// See:
// https://wiki.osdev.org/3D_Renderer_Basics
// http://members.chello.at/easyfilter/bresenham.html
// ...



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



int grPlot0 (int z, int x, int y, unsigned long color)
{

    unsigned long zBaseX=0;
    unsigned long zBaseY=0;

    unsigned long X=0;
    unsigned long Y=0;




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
        
        pixelBackBufferPutpixel ( color, X, Y );  
        return 0;
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
        
        pixelBackBufferPutpixel ( color, X, Y );  
        return 0;
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

void plotLine3d(int x0, int y0, int z0, int x1, int y1, int z1, unsigned long color)
{
   int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
   int dz = abs(z1-z0), sz = z0<z1 ? 1 : -1; 
   
   //#bugbug: This macro is wrong?!
   int dm = grMAX3 (dx,dy,dz), i = dm; /* maximum difference */
   
   x1 = y1 = z1 = dm/2; /* error offset */
 
   for(;;) {  /* loop */
      
      //setPixel(x0,y0,z0);
      grPlot0 ( z0, x0, y0, color);
      
      if (i-- == 0) break;
      x1 -= dx; if (x1 < 0) { x1 += dm; x0 += sx; } 
      y1 -= dy; if (y1 < 0) { y1 += dm; y0 += sy; } 
      z1 -= dz; if (z1 < 0) { z1 += dm; z0 += sz; } 
   }
}

 
//Circle
//This is an implementation of the circle algorithm.

void plotCircle (int xm, int ym, int r, unsigned long color)
{
   int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
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
      if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
      if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
   } while (x < 0);
}
  



//Ellipse
//This program example plots an ellipse inside a specified rectangle.

void plotEllipseRect(int x0, int y0, int x1, int y1, unsigned long color)
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
       
       
       
       e2 = 2*err;
       if (e2 <= dy) { y0++; y1--; err += dy += a; }  /* y step */ 
       if (e2 >= dx || 2*err > dy) { x0++; x1--; err += dx += b1; } /* x step */
   } while (x0 <= x1);
   
   while (y0-y1 < b) {  /* too early stop of flat ellipses a=1 */
       
       //setPixel(x0-1, y0); /* -> finish tip of ellipse */
       //setPixel(x1+1, y0++); 
       //setPixel(x0-1, y1);
       //setPixel(x1+1, y1--); 
   
       grPlot0 ( 0, x0-1,    y0, color);
       grPlot0 ( 0, x1+1,  y0++, color);
       grPlot0 ( 0, x0-1,    y1, color);
       grPlot0 ( 0, x1+1,  y1--, color);
   }
}
  


















