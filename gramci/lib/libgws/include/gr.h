

// #todo
// 3d graphics support.


#ifndef __GR_H
#define __GR_H   1

struct gr_vec3D_d
{
    int x;
    int y;
    int z;
    
    // for interpolation.
    unsigned long color;
};

struct gr_line_d
{
    struct gr_vec3D_d p[2];
};

struct gr_triandle_d
{
    struct gr_vec3D_d p[3];
};

struct gr_rectangle_d
{
    struct gr_vec3D_d p[4];
};


// Cube
struct gr_cube_d
{
    struct gr_vec3D_d p[8];
};


//#define grMIN2(a, b)  (((a) < (b)) ? (a) : (b))
//#define grMAX2(a, b)  (((a) > (b)) ? (a) : (b))

//#define grMIN3(x,y,z)     (x < y  ? (x < z ? x : z) : (y < z ? y : z))
//#define grMAX3(x,y,z)     ( (x>y) ? ((x>z)?x:z)     : ((y>z)?y:z) )


#endif    



