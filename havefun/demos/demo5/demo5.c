
// demo5.c
// Using the gramado game engine.
// Using fpu and eng5.
// Credits:
// OneLoneCoder.com - 3D Graphics Part #1 - Triangles & Projections
// GNU GPLv3

#include "../../eng5/gramado.h"

char *args[] = { "nothing", NULL };


char obj_buffer[1024];
float fTheta;
float model_distance;


/*
struct mesh
{
    //int dummy;
    //vector<triangle> tris;
    struct gr_triangleF3D_d tris[12];
};
*/


int DrawModel1(float fElapsedTime);
int DrawModel2(float fElapsedTime);
int DrawModel3(float fElapsedTime);

// -----------------------------



int OnUserCreate(void)
{
    fTheta = (float) 0.0f;
    model_distance = (float) 0.0f;
    return 0;
}


// fake Wavefront File Format (.obj)
// rotate in z
int DrawModel1(float fElapsedTime)
{
    struct gr_mat4x4_d matRotZ; 

    fTheta += 1.0f * fElapsedTime;
// Rotation Z
	matRotZ.m[0][0] =  cosf(fTheta);
	matRotZ.m[0][1] =  sinf(fTheta);
	matRotZ.m[1][0] = -sinf(fTheta);
	matRotZ.m[1][1] =  cosf(fTheta);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;
//------------------------------------------------

// triangles
    struct gr_triangleF3D_d tri;            // triângulo original.
    struct gr_triangleF3D_d triRotatedZ; 
    struct gr_triangleF3D_d triProjected;   // triangulo final, mostrado na tela.
// vectors
    struct gr_vecF3D_d vecs[32];


// #bugbug
// Isso foi projetado para estar dentro 
// de um model space. Se usarmos num view space
// que é o que a camera vê, então teríamos valores negativos,
// que não deviram aparecer na imagem final.

    vecs[1].x = (float) -0.2f;  vecs[1].y = (float) -0.2f;  vecs[1].z = (float)  0.2f;
    vecs[2].x = (float)  0.2f;  vecs[2].y = (float) -0.2f;  vecs[2].z = (float)  0.2f;
    vecs[3].x = (float) -0.2f;  vecs[3].y = (float)  0.2f;  vecs[3].z = (float)  0.2f;
    vecs[4].x = (float)  0.2f;  vecs[4].y = (float)  0.2f;  vecs[4].z = (float)  0.2f;
    vecs[5].x = (float) -0.2f;  vecs[5].y = (float)  0.2f;  vecs[5].z = (float) -0.2f;
    vecs[6].x = (float)  0.2f;  vecs[6].y = (float)  0.2f;  vecs[6].z = (float) -0.2f;
    vecs[7].x = (float) -0.2f;  vecs[7].y = (float) -0.2f;  vecs[7].z = (float) -0.2f;
    vecs[8].x = (float)  0.2f;  vecs[8].y = (float) -0.2f;  vecs[8].z = (float) -0.2f;


    int sequence[3*16];
    
    sequence[0]  = 1; sequence[1]  = 2;  sequence[2] = 3; //f 1 2 4
    sequence[3]  = 1; sequence[4]  = 4;  sequence[5] = 3; //f 1 4 3
    sequence[6]  = 3; sequence[7]  = 4;  sequence[8] = 6; //f 3 4 6
    sequence[9]  = 3; sequence[10] = 6; sequence[11] = 5; //f 3 6 5
    sequence[12] = 5; sequence[13] = 6; sequence[14] = 8; //f 5 6 8
    sequence[15] = 5; sequence[16] = 8; sequence[17] = 7; //f 5 8 7
    sequence[18] = 7; sequence[19] = 8; sequence[20] = 2; //f 7 8 2
    sequence[21] = 7; sequence[22] = 2; sequence[23] = 1; //f 7 2 1
    sequence[24] = 2; sequence[25] = 8; sequence[26] = 6; //f 2 8 6
    sequence[27] = 2; sequence[28] = 6; sequence[29] = 4; //f 2 6 4
    sequence[30] = 7; sequence[31] = 1; sequence[32] = 3; //f 7 1 3
    sequence[33] = 7; sequence[34] = 3; sequence[35] = 5; //f 7 3 5
    
    int i=0;
    int j=0;
    int off=0;
    int v=0;

    for(i=1; i<=12; i++)
    {
        off = (i-1)*3;
        
        v = sequence[off+0];
        tri.p[0].x = vecs[v].x;
        tri.p[0].y = vecs[v].y;
        tri.p[0].z = vecs[v].z;
        tri.p[0].color = COLOR_WHITE;  //COLOR_RED; 
        
        v = sequence[off+1];
        tri.p[1].x = vecs[v].x;
        tri.p[1].y = vecs[v].y;
        tri.p[1].z = vecs[v].z;
        tri.p[1].color = COLOR_WHITE;  // COLOR_GREEN;

        v = sequence[off+2];
        tri.p[2].x = vecs[v].x;
        tri.p[2].y = vecs[v].y;
        tri.p[2].z = vecs[v].z;
        tri.p[2].color = COLOR_WHITE;  // COLOR_BLUE;
        
        //-----------------------------    
        // Rotate in Z-Axis
        gr_MultiplyMatrixVector(&tri.p[0], &triRotatedZ.p[0], &matRotZ);
        gr_MultiplyMatrixVector(&tri.p[1], &triRotatedZ.p[1], &matRotZ);
        gr_MultiplyMatrixVector(&tri.p[2], &triRotatedZ.p[2], &matRotZ);
        //-----------------------------    

        triRotatedZ.p[0].color = tri.p[0].color;
        triRotatedZ.p[1].color = tri.p[1].color;
        triRotatedZ.p[2].color = tri.p[2].color;

        // Translate in z
        model_distance = (float) (model_distance + 0.002f);
        if(model_distance>10.0f)
            model_distance = 0.8f;
        triRotatedZ.p[0].z = triRotatedZ.p[0].z + model_distance; 
        triRotatedZ.p[1].z = triRotatedZ.p[1].z + model_distance; 
        triRotatedZ.p[2].z = triRotatedZ.p[2].z + model_distance; 

        //translate in x
        triRotatedZ.p[0].x = triRotatedZ.p[0].x - 0.8f; 
        triRotatedZ.p[1].x = triRotatedZ.p[1].x - 0.8f; 
        triRotatedZ.p[2].x = triRotatedZ.p[2].x - 0.8f; 


        //We need a valid window, to use the rasterization features.
        if( (void*) __root_window != NULL ){
            plotTriangleF(__root_window, &triRotatedZ,FALSE);
        }
    };
    
    return 0;
}

// fake Wavefront File Format (.obj)
//rotate in x
int DrawModel2(float fElapsedTime)
{
    struct gr_mat4x4_d matRotZ; 
    struct gr_mat4x4_d matRotX;

    fTheta += 1.0f * fElapsedTime;

//------------------------------------------------
// Rotation X
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] =  cosf(fTheta * 0.5f);
	matRotX.m[1][2] =  sinf(fTheta * 0.5f);
	matRotX.m[2][1] = -sinf(fTheta * 0.5f);
	matRotX.m[2][2] =  cosf(fTheta * 0.5f);
	matRotX.m[3][3] = 1;
//------------------------------------------------

// triangles
    struct gr_triangleF3D_d tri;            // triângulo original.
    struct gr_triangleF3D_d triRotatedX;
    struct gr_triangleF3D_d triProjected;   // triangulo final, mostrado na tela.
// vectors
    struct gr_vecF3D_d vecs[32];


// #bugbug
// Isso foi projetado para estar dentro 
// de um model space. Se usarmos num view space
// que é o que a camera vê, então teríamos valores negativos,
// que não deviram aparecer na imagem final.

    vecs[1].x = (float) -0.2f;  vecs[1].y = (float) -0.2f;  vecs[1].z = (float)  0.2f;
    vecs[2].x = (float)  0.2f;  vecs[2].y = (float) -0.2f;  vecs[2].z = (float)  0.2f;
    vecs[3].x = (float) -0.2f;  vecs[3].y = (float)  0.2f;  vecs[3].z = (float)  0.2f;
    vecs[4].x = (float)  0.2f;  vecs[4].y = (float)  0.2f;  vecs[4].z = (float)  0.2f;
    vecs[5].x = (float) -0.2f;  vecs[5].y = (float)  0.2f;  vecs[5].z = (float) -0.2f;
    vecs[6].x = (float)  0.2f;  vecs[6].y = (float)  0.2f;  vecs[6].z = (float) -0.2f;
    vecs[7].x = (float) -0.2f;  vecs[7].y = (float) -0.2f;  vecs[7].z = (float) -0.2f;
    vecs[8].x = (float)  0.2f;  vecs[8].y = (float) -0.2f;  vecs[8].z = (float) -0.2f;


    int sequence[3*16];
    
    sequence[0]  = 1; sequence[1]  = 2;  sequence[2] = 3; //f 1 2 4
    sequence[3]  = 1; sequence[4]  = 4;  sequence[5] = 3; //f 1 4 3
    sequence[6]  = 3; sequence[7]  = 4;  sequence[8] = 6; //f 3 4 6
    sequence[9]  = 3; sequence[10] = 6; sequence[11] = 5; //f 3 6 5
    sequence[12] = 5; sequence[13] = 6; sequence[14] = 8; //f 5 6 8
    sequence[15] = 5; sequence[16] = 8; sequence[17] = 7; //f 5 8 7
    sequence[18] = 7; sequence[19] = 8; sequence[20] = 2; //f 7 8 2
    sequence[21] = 7; sequence[22] = 2; sequence[23] = 1; //f 7 2 1
    sequence[24] = 2; sequence[25] = 8; sequence[26] = 6; //f 2 8 6
    sequence[27] = 2; sequence[28] = 6; sequence[29] = 4; //f 2 6 4
    sequence[30] = 7; sequence[31] = 1; sequence[32] = 3; //f 7 1 3
    sequence[33] = 7; sequence[34] = 3; sequence[35] = 5; //f 7 3 5
    
    int i=0;
    int j=0;
    int off=0;
    int v=0;

    for(i=1; i<=12; i++)
    {
        off = (i-1)*3;
        
        v = sequence[off+0];
        tri.p[0].x = vecs[v].x;
        tri.p[0].y = vecs[v].y;
        tri.p[0].z = vecs[v].z;
        tri.p[0].color = COLOR_WHITE;  //COLOR_RED; 
        
        v = sequence[off+1];
        tri.p[1].x = vecs[v].x;
        tri.p[1].y = vecs[v].y;
        tri.p[1].z = vecs[v].z;
        tri.p[1].color = COLOR_WHITE;  // COLOR_GREEN;

        v = sequence[off+2];
        tri.p[2].x = vecs[v].x;
        tri.p[2].y = vecs[v].y;
        tri.p[2].z = vecs[v].z;
        tri.p[2].color = COLOR_WHITE;  // COLOR_BLUE;
        
        //-----------------------------    
        // Rotate in Z-Axis
        gr_MultiplyMatrixVector(&tri.p[0], &triRotatedX.p[0], &matRotX);
        gr_MultiplyMatrixVector(&tri.p[1], &triRotatedX.p[1], &matRotX);
        gr_MultiplyMatrixVector(&tri.p[2], &triRotatedX.p[2], &matRotX);
        //-----------------------------    

        triRotatedX.p[0].color = tri.p[0].color;
        triRotatedX.p[1].color = tri.p[1].color;
        triRotatedX.p[2].color = tri.p[2].color;


        // Translate in z
        model_distance = (float) (model_distance + 0.002f);
        if(model_distance>10.0f)
            model_distance = 0.8f;
        triRotatedX.p[0].z = triRotatedX.p[0].z + model_distance; 
        triRotatedX.p[1].z = triRotatedX.p[1].z + model_distance; 
        triRotatedX.p[2].z = triRotatedX.p[2].z + model_distance; 

        //translate in x
        triRotatedX.p[0].x = triRotatedX.p[0].x + 0.01f; 
        triRotatedX.p[1].x = triRotatedX.p[1].x + 0.01f; 
        triRotatedX.p[2].x = triRotatedX.p[2].x + 0.01f; 

        //We need a valid window, to use the rasterization features.
        if( (void*) __root_window != NULL ){
            plotTriangleF(__root_window, &triRotatedX,FALSE);
        }
    };

    return 0;
}


// fake Wavefront File Format (.obj)
int DrawModel3(float fElapsedTime)
{
    struct gr_mat4x4_d matRotZ; 
    struct gr_mat4x4_d matRotX;

    fTheta += 1.0f * fElapsedTime;
// Rotation Z
	matRotZ.m[0][0] =  cosf(fTheta);
	matRotZ.m[0][1] =  sinf(fTheta);
	matRotZ.m[1][0] = -sinf(fTheta);
	matRotZ.m[1][1] =  cosf(fTheta);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;
// Rotation X
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] =  cosf(fTheta * 0.5f);
	matRotX.m[1][2] =  sinf(fTheta * 0.5f);
	matRotX.m[2][1] = -sinf(fTheta * 0.5f);
	matRotX.m[2][2] =  cosf(fTheta * 0.5f);
	matRotX.m[3][3] = 1;
//------------------------------------------------

// triangles
    struct gr_triangleF3D_d tri;            // triângulo original.
    struct gr_triangleF3D_d triRotatedZ; 
    struct gr_triangleF3D_d triRotatedZX;
    struct gr_triangleF3D_d triProjected;   // triangulo final, mostrado na tela.
// vectors
    struct gr_vecF3D_d vecs[32];


// #bugbug
// Isso foi projetado para estar dentro 
// de um model space. Se usarmos num view space
// que é o que a camera vê, então teríamos valores negativos,
// que não deviram aparecer na imagem final.

    vecs[1].x = (float) -0.2f;  vecs[1].y = (float) -0.2f;  vecs[1].z = (float)  0.2f;
    vecs[2].x = (float)  0.2f;  vecs[2].y = (float) -0.2f;  vecs[2].z = (float)  0.2f;
    vecs[3].x = (float) -0.2f;  vecs[3].y = (float)  0.2f;  vecs[3].z = (float)  0.2f;
    vecs[4].x = (float)  0.2f;  vecs[4].y = (float)  0.2f;  vecs[4].z = (float)  0.2f;
    vecs[5].x = (float) -0.2f;  vecs[5].y = (float)  0.2f;  vecs[5].z = (float) -0.2f;
    vecs[6].x = (float)  0.2f;  vecs[6].y = (float)  0.2f;  vecs[6].z = (float) -0.2f;
    vecs[7].x = (float) -0.2f;  vecs[7].y = (float) -0.2f;  vecs[7].z = (float) -0.2f;
    vecs[8].x = (float)  0.2f;  vecs[8].y = (float) -0.2f;  vecs[8].z = (float) -0.2f;


    int sequence[3*16];
    
    sequence[0]  = 1; sequence[1]  = 2;  sequence[2] = 3; //f 1 2 4
    sequence[3]  = 1; sequence[4]  = 4;  sequence[5] = 3; //f 1 4 3
    sequence[6]  = 3; sequence[7]  = 4;  sequence[8] = 6; //f 3 4 6
    sequence[9]  = 3; sequence[10] = 6; sequence[11] = 5; //f 3 6 5
    sequence[12] = 5; sequence[13] = 6; sequence[14] = 8; //f 5 6 8
    sequence[15] = 5; sequence[16] = 8; sequence[17] = 7; //f 5 8 7
    sequence[18] = 7; sequence[19] = 8; sequence[20] = 2; //f 7 8 2
    sequence[21] = 7; sequence[22] = 2; sequence[23] = 1; //f 7 2 1
    sequence[24] = 2; sequence[25] = 8; sequence[26] = 6; //f 2 8 6
    sequence[27] = 2; sequence[28] = 6; sequence[29] = 4; //f 2 6 4
    sequence[30] = 7; sequence[31] = 1; sequence[32] = 3; //f 7 1 3
    sequence[33] = 7; sequence[34] = 3; sequence[35] = 5; //f 7 3 5
    
    int i=0;
    int j=0;
    int off=0;
    int v=0;

    for(i=1; i<=12; i++)
    {
        off = (i-1)*3;
        
        v = sequence[off+0];
        tri.p[0].x = vecs[v].x;
        tri.p[0].y = vecs[v].y;
        tri.p[0].z = vecs[v].z;
        tri.p[0].color = COLOR_WHITE;  //COLOR_RED; 
        
        v = sequence[off+1];
        tri.p[1].x = vecs[v].x;
        tri.p[1].y = vecs[v].y;
        tri.p[1].z = vecs[v].z;
        tri.p[1].color = COLOR_WHITE;  // COLOR_GREEN;

        v = sequence[off+2];
        tri.p[2].x = vecs[v].x;
        tri.p[2].y = vecs[v].y;
        tri.p[2].z = vecs[v].z;
        tri.p[2].color = COLOR_WHITE;  // COLOR_BLUE;
        
        //-----------------------------    
        // Rotate in Z-Axis
        gr_MultiplyMatrixVector(&tri.p[0], &triRotatedZ.p[0], &matRotZ);
        gr_MultiplyMatrixVector(&tri.p[1], &triRotatedZ.p[1], &matRotZ);
        gr_MultiplyMatrixVector(&tri.p[2], &triRotatedZ.p[2], &matRotZ);
        //-----------------------------    
        // Rotate in X-Axis
        gr_MultiplyMatrixVector(&triRotatedZ.p[0], &triRotatedZX.p[0], &matRotX);
        gr_MultiplyMatrixVector(&triRotatedZ.p[1], &triRotatedZX.p[1], &matRotX);
        gr_MultiplyMatrixVector(&triRotatedZ.p[2], &triRotatedZX.p[2], &matRotX);

        triRotatedZX.p[0].color = tri.p[0].color;
        triRotatedZX.p[1].color = tri.p[1].color;
        triRotatedZX.p[2].color = tri.p[2].color;


        // Translate in z
        model_distance = (float) (model_distance + 0.002f);
        if(model_distance>10.0f)
            model_distance = 0.8f;
        triRotatedZX.p[0].z = triRotatedZX.p[0].z + model_distance; 
        triRotatedZX.p[1].z = triRotatedZX.p[1].z + model_distance; 
        triRotatedZX.p[2].z = triRotatedZX.p[2].z + model_distance; 

        //translate in x
        triRotatedZX.p[0].x = triRotatedZX.p[0].x + 0.8f; 
        triRotatedZX.p[1].x = triRotatedZX.p[1].x + 0.8f; 
        triRotatedZX.p[2].x = triRotatedZX.p[2].x + 0.8f; 

        //We need a valid window, to use the rasterization features.
        if( (void*) __root_window != NULL ){
            plotTriangleF(__root_window, &triRotatedZX,FALSE);
        }
    };
    
    return 0;
}


// Include inside the engine.
// see: gramado.h
void gramado_setup(void)
{
// Here we can call some methods inside the engine.

    // #test
    //printf("gr_setup:\n");
    //__setupCatModel(TRUE,TRUE,TRUE);
    
    OnUserCreate();
}


// Include inside the engine.
// see: gramado.h
void gramado_update(void)
{
// Clear the surface.
    gramado_clear_surface(NULL,COLOR_BLACK);

// Draw model 1. rotate in z
    DrawModel1(0.02f);

// Draw model 2. rotate in x
    DrawModel2(0.02f);

// Draw model 3. rotate in z and x
    DrawModel3(0.02f);

// #todo
// This functions needs to be called the engine
// or the compisitor callback inside the engine.
    gramado_flush_surface(NULL);
}


int main(int argc, char **argv)
{
    // chama o main() da engine
    
    printf("DEMO4.BIN: Initializing ...\n");

/*
    FILE *fp;
    fp = (FILE *) fopen("test1.obj", "a+");
    int nreads=-1;
    nreads = read( fp->_file, obj_buffer, 511 );
    printf("%s\n",obj_buffer);
    while(1){}
*/

// Initialize the library.
// see: eng5/main.c
    gramado_initialize(1,args);

    return 0;
}



