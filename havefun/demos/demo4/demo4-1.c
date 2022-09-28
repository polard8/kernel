
// demo4.c
// Using fpu and eng4.
// Credits:
// OneLoneCoder.com - 3D Graphics Part #1 - Triangles & Projections
// GNU GPLv3

#include "../../eng4/gws.h"

char *args[] = { "nothing", NULL };


char obj_buffer[1024];


//struct mesh meshCube;
struct gr_mat4x4_d matProj;
float fTheta;


/*
struct vec3d
{
    float x, y, z;
};
*/

/*
struct triangle
{
    struct gr_vecF3D_d p[3];
};
*/

/*
struct mesh
{
    //int dummy;
    //vector<triangle> tris;

    struct gr_triangleF3D_d tris[12];
};
*/


/*
void 
MultiplyMatrixVector(
    struct gr_vecF3D_d *i, 
    struct gr_vecF3D_d *o, 
    struct gr_mat4x4_d *m )
{
    o->x = 
        i->x * m->m[0][0] + 
        i->y * m->m[1][0] + 
        i->z * m->m[2][0] + 
        m->m[3][0];

    o->y = 
        i->x * m->m[0][1] + 
        i->y * m->m[1][1] + 
        i->z * m->m[2][1] + 
        m->m[3][1];
    
    o->z = 
        i->x * m->m[0][2] + 
        i->y * m->m[1][2] + 
        i->z * m->m[2][2] + 
        m->m[3][2];

    float w = 
        i->x * m->m[0][3] + 
        i->y * m->m[1][3] + 
        i->z * m->m[2][3] + 
        m->m[3][3];

    if (w != 0.0f)
    {
        o->x /= w; 
        o->y /= w; 
        o->z /= w;
    }
}
*/

int OnUserCreate(void)
{

/*
    //meshCube.tris = {

		// SOUTH
		meshCube.tris[0].p[0].x = 0.0f;
		meshCube.tris[0].p[0].y = 0.0f;
		meshCube.tris[0].p[0].z = 0.0f,    
		meshCube.tris[0].p[1].x = 0.0f; 
		meshCube.tris[0].p[1].y = 1.0f; 
		meshCube.tris[0].p[1].z = 0.0f;    
		meshCube.tris[0].p[2].x = 1.0f, 
		meshCube.tris[0].p[2].x = 1.0f, 
		meshCube.tris[0].p[2].x = 0.0f },

		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		};
*/

// Projection Matrix
	float fNear = 0.1f;
	float fFar = 1000.0f;
	float fFov = 90.0f;
		
    //float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
	float fAspectRatio = (float) 800 / (float) 600;

	//float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;

    return 0;
}

// fake Wavefront File Format (.obj)
void test_fake_obj(void)
{
    struct gr_vecF3D_d vecs[32];
    int obj_vecs_counter=0;

/*
v -0.5 -0.5 0.5
v 0.5 -0.5 0.5
v -0.5 0.5 0.5
v 0.5 0.5 0.5
v -0.5 0.5 -0.5
v 0.5 0.5 -0.5
v -0.5 -0.5 -0.5
v 0.5 -0.5 -0.5
*/

    vecs[1].x = -0.2;
    vecs[1].y = -0.2;
    vecs[1].z =  0.2;

    vecs[2].x =  0.2;
    vecs[2].y = -0.2;
    vecs[2].z =  0.2;

    vecs[3].x = -0.2;
    vecs[3].y =  0.2;
    vecs[3].z =  0.2;

    vecs[4].x =  0.2;
    vecs[4].y =  0.2;
    vecs[4].z =  0.2;

    vecs[5].x = -0.2;
    vecs[5].y =  0.2;
    vecs[5].z = -0.2;

    vecs[6].x =  0.2;
    vecs[6].y =  0.2;
    vecs[6].z = -0.2;

    vecs[7].x = -0.2;
    vecs[7].y = -0.2;
    vecs[7].z = -0.2;

    vecs[8].x =  0.2;
    vecs[8].y = -0.2;
    vecs[8].z = -0.2;

/*
f 1 2 4
f 1 4 3
f 3 4 6
f 3 6 5
f 5 6 8
f 5 8 7
f 7 8 2
f 7 2 1
f 2 8 6
f 2 6 4
f 7 1 3
f 7 3 5
*/
    int sequence[3*16];
    sequence[0]  = 1; sequence[1]  = 2;  sequence[2] = 3;
    sequence[3]  = 1; sequence[4]  = 4;  sequence[5] = 3;
    sequence[6]  = 3; sequence[7]  = 4;  sequence[8] = 6;
    sequence[9]  = 3; sequence[10] = 6; sequence[11] = 5;
    sequence[12] = 5; sequence[13] = 6; sequence[14] = 8;
    sequence[15] = 5; sequence[16] = 8; sequence[17] = 7;
    sequence[18] = 7; sequence[19] = 8; sequence[20] = 2;
    sequence[21] = 7; sequence[22] = 2; sequence[23] = 1;
    sequence[24] = 2; sequence[25] = 8; sequence[26] = 6;
    sequence[27] = 2; sequence[28] = 6; sequence[29] = 4;
    sequence[30] = 7; sequence[31] = 1; sequence[32] = 3;
    sequence[33] = 7; sequence[34] = 3; sequence[35] = 5;


    struct gr_triangleF3D_d tri;

    int i=0;
    int j=0;
    int off=0;
    int v=0;
    for(i=1; i<=8; i++)
    {
        off = (i-1)*3;
        
        v = sequence[off+0];
        tri.p[0].x = vecs[v].x;
        tri.p[0].y = vecs[v].y;
        tri.p[0].z = vecs[v].z;
        
        v = sequence[off+1];
        tri.p[1].x = vecs[v].x;
        tri.p[1].y = vecs[v].y;
        tri.p[1].z = vecs[v].z;

        v = sequence[off+2];
        tri.p[2].x = vecs[v].x;
        tri.p[2].y = vecs[v].y;
        tri.p[2].z = vecs[v].z;

        plotTriangleF(NULL, &tri);
    };
}


int OnUserUpdate(float fElapsedTime)
{ 
    demoClearSurface(NULL,COLOR_RED);

//------------------------------------------------
// Rotação em x e y com base no elapsed time.
// Set up rotation matrices
    struct gr_mat4x4_d matRotZ; 
    struct gr_mat4x4_d matRotX;
    fTheta += 1.0f * fElapsedTime;
    //fTheta += 0.2f * fElapsedTime;
    
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


    struct gr_triangleF3D_d tri;            // triângulo original.
    struct gr_triangleF3D_d triProjected;   // triangulo final, mostrado na tela.
    struct gr_triangleF3D_d triTranslated;  //
    struct gr_triangleF3D_d triRotatedZ; 
    struct gr_triangleF3D_d triRotatedZX;

// Triângulo original.
    tri.p[0].x = 0.0f;  tri.p[0].y = 0.0f;  tri.p[0].z = 0.0f;
    tri.p[1].x = 0.0f;  tri.p[1].y = 0.8f;  tri.p[1].z = 0.0f;
    tri.p[2].x = 0.8f;  tri.p[2].y = 0.8f;  tri.p[2].z = 0.0f;

/*
//-------------------------------------------------------------
// #test:
// colocando o triangulo original, direto para ser projetado.
    triProjected.p[0].x = tri.p[0].x; 
    triProjected.p[0].y = tri.p[0].y;  
    triProjected.p[0].z = tri.p[0].z;
    triProjected.p[1].x = tri.p[1].x;  
    triProjected.p[1].y = tri.p[1].y;  
    triProjected.p[1].z = tri.p[1].z;
    triProjected.p[2].x = tri.p[2].x;  
    triProjected.p[2].y = tri.p[2].y;  
    triProjected.p[2].z = tri.p[2].z;
//-------------------------------------------------------------
*/

// rotação em z,
// o output esta no triRotatedZ.
// os 3 vetores foram modificados.
//-----------------------------    
// Rotate in Z-Axis
    gr_MultiplyMatrixVector(&tri.p[0], &triRotatedZ.p[0], &matRotZ);
    gr_MultiplyMatrixVector(&tri.p[1], &triRotatedZ.p[1], &matRotZ);
    gr_MultiplyMatrixVector(&tri.p[2], &triRotatedZ.p[2], &matRotZ);
//-----------------------------    

/*
// colocando para mostrar o triangulo depois
// da rotação em z.
    triProjected.p[0].x = triRotatedZ.p[0].x; 
    triProjected.p[0].y = triRotatedZ.p[0].y;  
    triProjected.p[0].z = triRotatedZ.p[0].z;
    triProjected.p[1].x = triRotatedZ.p[1].x;  
    triProjected.p[1].y = triRotatedZ.p[1].y;  
    triProjected.p[1].z = triRotatedZ.p[1].z;
    triProjected.p[2].x = triRotatedZ.p[2].x;  
    triProjected.p[2].y = triRotatedZ.p[2].y;  
    triProjected.p[2].z = triRotatedZ.p[2].z;
*/


// pegando o trangulo depois da rotação em z
// e fazendo uma rotação em x também.
//-----------------------------    
// Rotate in X-Axis
    gr_MultiplyMatrixVector(&triRotatedZ.p[0], &triRotatedZX.p[0], &matRotX);
    gr_MultiplyMatrixVector(&triRotatedZ.p[1], &triRotatedZX.p[1], &matRotX);
    gr_MultiplyMatrixVector(&triRotatedZ.p[2], &triRotatedZX.p[2], &matRotX);
//-----------------------------    

// colocando para mostrar o triangulo depois
// da rotação em x.
    triProjected.p[0].x = triRotatedZX.p[0].x; 
    triProjected.p[0].y = triRotatedZX.p[0].y;  
    triProjected.p[0].z = triRotatedZX.p[0].z;
    triProjected.p[1].x = triRotatedZX.p[1].x;  
    triProjected.p[1].y = triRotatedZX.p[1].y;  
    triProjected.p[1].z = triRotatedZX.p[1].z;
    triProjected.p[2].x = triRotatedZX.p[2].x;  
    triProjected.p[2].y = triRotatedZX.p[2].y;  
    triProjected.p[2].z = triRotatedZX.p[2].z;


/*
//-----------------------------    
// Offset into the screen
    triTranslated = triRotatedZX;
    triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
    triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
    triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;
//-----------------------------    
*/

/*
// No momento esse trabalho é feito por uma rotina
// alternativa, dentro da engine.
//-----------------------------    
// Project triangles from 3D --> 2D
    gr_MultiplyMatrixVector(&triTranslated.p[0], &triProjected.p[0], &matProj);
    gr_MultiplyMatrixVector(&triTranslated.p[1], &triProjected.p[1], &matProj);
    gr_MultiplyMatrixVector(&triTranslated.p[2], &triProjected.p[2], &matProj);
//-----------------------------    
*/


//-----------------------------    
// Scale into view
// Aumenta 20%
    //triProjected.p[0].x += 0.2f; triProjected.p[0].y += 0.2f;
    //triProjected.p[1].x += 0.2f; triProjected.p[1].y += 0.2f;
    //triProjected.p[2].x += 0.2f; triProjected.p[2].y += 0.2f;
//-----------------------------    



    plotTriangleF(NULL, &triProjected );
    
    //test_fake_obj();

    demoFlushSurface(NULL);
    rtl_yield();
        
    return 0;
}
//---------

int OnUserUpdate2(float fElapsedTime)
{
    demoClearSurface(NULL,COLOR_GREEN);

    struct gr_mat4x4_d matRotZ; 
    fTheta += 1.0f * fElapsedTime;
// Rotation Z
	matRotZ.m[0][0] =  cosf(fTheta);
	matRotZ.m[0][1] =  sinf(fTheta);
	matRotZ.m[1][0] = -sinf(fTheta);
	matRotZ.m[1][1] =  cosf(fTheta);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

    struct gr_triangleF3D_d tri;            // triângulo original.
    struct gr_triangleF3D_d triRotatedZ; 
    struct gr_triangleF3D_d triProjected;   // triangulo final, mostrado na tela.

// Triângulo original.
    tri.p[0].x = 0.0f;  tri.p[0].y = 0.0f;  tri.p[0].z = 0.0f;
    tri.p[1].x = 0.0f;  tri.p[1].y = 0.8f;  tri.p[1].z = 0.0f;
    tri.p[2].x = 0.8f;  tri.p[2].y = 0.8f;  tri.p[2].z = 0.0f;

// rotação em z,
// o output esta no triRotatedZ.
// os 3 vetores foram modificados.
//-----------------------------    
// Rotate in Z-Axis
    gr_MultiplyMatrixVector(&tri.p[0], &triRotatedZ.p[0], &matRotZ);
    gr_MultiplyMatrixVector(&tri.p[1], &triRotatedZ.p[1], &matRotZ);
    gr_MultiplyMatrixVector(&tri.p[2], &triRotatedZ.p[2], &matRotZ);
//-----------------------------    

    triProjected.p[0].x = triRotatedZ.p[0].x; 
    triProjected.p[0].y = triRotatedZ.p[0].y;  
    triProjected.p[0].z = triRotatedZ.p[0].z;
    triProjected.p[1].x = triRotatedZ.p[1].x;  
    triProjected.p[1].y = triRotatedZ.p[1].y;  
    triProjected.p[1].z = triRotatedZ.p[1].z;
    triProjected.p[2].x = triRotatedZ.p[2].x;  
    triProjected.p[2].y = triRotatedZ.p[2].y;  
    triProjected.p[2].z = triRotatedZ.p[2].z;

    plotTriangleF(NULL, &triProjected );

    demoFlushSurface(NULL);
    rtl_yield();

    return 0;
}


// include inside the engine.
void gr_setup(void)
{
    //printf("gr_setup:\n");
    //__setupCatModel(TRUE,TRUE,TRUE);
    
    OnUserCreate();
}


// include inside the engine.
void gr_draw(void)
{
    //printf("gr_draw:\n");
    //demoCat();
    //OnUserUpdate(1);
    OnUserUpdate2(1);
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

    eng4_main(1,args);
    
    return 0;
}



