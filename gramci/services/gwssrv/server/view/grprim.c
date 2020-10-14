	// gramado 3d primitives.


#include <gws.h>


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








