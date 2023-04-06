
// libgr.c

#include "include/libgr.h"

int coisolibgr=0;


void multiply4 (int mat1[4][4], int mat2[4][4], int res[4][4])
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


// Fibonacci Series using Recursion 
// ??: slow.
int fib (int n)
{ 
    register int Copy = n;
    int a=0;
    int b=0;

    if (Copy <= 1){ return Copy; }

    a = fib(Copy - 1); 
    b = fib(Copy - 2);

    return (int) (a+b);
} 

/*
// print fibonacci
void __print_fib(int max);
void __print_fib(int max)
{
    int i=0;
    int a=0;
    int b=1;
    int c;
    
    if (max<0)
        return;
    
    while(a<max)
    {
        printf("%d\n,a");
        c = a+b;
        a = b;
        b = c;
    };
}
*/


//#todo: Explain it better.
unsigned int 
interpolate_color(
    unsigned int color1, 
    unsigned int color2, 
    unsigned int fraction )
{
    unsigned int final_color=0;
    unsigned char r1 = (unsigned char) (color1 >> 16) & 0xff;
    unsigned char r2 = (unsigned char) (color2 >> 16) & 0xff;
    unsigned char g1 = (unsigned char) (color1 >> 8) & 0xff;
    unsigned char g2 = (unsigned char) (color2 >> 8) & 0xff;
    unsigned char b1 = (unsigned char) color1 & 0xff;
    unsigned char b2 = (unsigned char) color2 & 0xff;

    final_color = 
        (unsigned int) (    
        (unsigned int) ( (r2 - r1) * fraction + r1 ) << 16 | 
        (unsigned int) ( (g2 - g1) * fraction + g1 ) <<  8 | 
        (unsigned int) ( (b2 - b1) * fraction + b1 )
    );
    
    return (unsigned int) final_color;
}

//??
//#todo: Explain it better.
unsigned int invert_color(unsigned int color)
{
    unsigned int Color = (unsigned int) (color ^ 0x00FFFFFF);
    return (unsigned int) Color;
}

// dot product
int dot_product( struct gr_vec3D_d *v1, struct gr_vec3D_d *v2 )
{
// Dot product.
// The dot product describe the 
// relationship between two vectors.
// Positive: Same direction
// negative: Opposite direction
// 0:        Perpendicular.

    int scalar=0;

// Fake perpendicular.
    if ( (void*) v1 == NULL ){ return 0; }
    if ( (void*) v2 == NULL ){ return 0; }

// (x*x + y*y + z*z)
    scalar  = (v1->x * v2->x);
    scalar += (v1->y * v2->y);
    scalar += (v1->z * v2->z);

    return (int) (scalar & 0xFFFFFFFF );
}

// inline?
int gr_triangle_area_int (int base, int height)
{
    return (int) ((base*height) >> 1);
}

int gr_magic_volume (int x, int y, int z)
{
    return (int) (x*y*z);
}

// ??
// wrong? Explain it better.
int gr_magic_area (int x, int y, int z)
{
    int area = 
        (int) ( (2*x*y) +
                (2*y*z) +
                (2*x*z) );

    return (int) area;
}

// Get delta for bhaskara.
// d<0: (negative) "Raiz de número negativo em Baskara"
// d=0: (null)     duas raizes reais iguais.
// d>0: (positive) duas raizes reais diferentes. (Intersection)
int gr_discriminant_int(int a, int b, int c)
{
// Discriminant: Delta da função em bhaskara.
    int Discriminant = (int) ((b*b) - (4*a*c));
    return (int) Discriminant;
}

int 
gr_find_obj_height_int ( 
    int *obj_height, int obj_distance,
    int img_height, int img_distance )
{
// #todo: This is a work in progress.
// ih/_oh      = (id/od)
// ih         = _oh*(id/od)
// ih/(id/od) = _oh

// ------------
// Razão entre a distância da imagem e a distância do objeto.
    if (obj_distance == 0){
        return -1;  //fail
    }
    int tmp = (int) (img_distance/obj_distance);

// ------------
// Altura da imagem dividida pela
// razão entre a distância da imagem e a distância do objeto.
    if (tmp==0){
        return -1;  //fail
    }
    int resOH = (int) (img_height / tmp);

// ------------
// done:
// Return the object height
// Check pointer validation

    if( (int*) obj_height == NULL){
        return -1;  //fail
    }
    
    *obj_height = (int) resOH;
    
    return 0; //ok
}

int 
gr_find_img_height_int ( 
    int obj_height, int obj_distance,
    int *img_height, int img_distance )
{
// #todo: This is a work in progress.
// _ih/oh      = (id/od)
// _ih         = oh*(id/od)

// ------------
// Razão entre a distância da imagem e a distância do objeto.
    if (obj_distance == 0){
        return -1;  //fail
    }
    int tmp = (int) (img_distance/obj_distance);

    int resIH = (int) (obj_height*tmp);

// ------------
// done:
// Return the image height
// Check pointer validation

    if ( (int*) img_height == NULL){
        return -1;  //fail
    }

    *img_height = (int) resIH;

    return 0; //ok
}

void gr_scale_vec( struct gr_vec3D_d *v, int scale )
{
    if ( (void*) v == NULL )
        return;

    v->x *= scale;
    v->y *= scale;
    v->z *= scale;
}

// Scaling: Inflate cube.
int 
xxxInflateCubeZ ( 
    struct gr_cube_d *cube, 
    int value )
{
    if ( (void*) cube == NULL ){
        return (-1);
    }

    //int value = z;
    //int value = z*2;

// South points =====================================
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

// North points ================================
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
int 
xxxDeflateCubeZ ( 
    struct gr_cube_d *cube, 
    int value )
{
    if ( (void*) cube == NULL ){
        return -1;
    }

// South points ==========================
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

// North points =========================
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












