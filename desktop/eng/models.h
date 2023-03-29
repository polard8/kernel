
// models.h
// This is a place for structures of default models.


// -----------------------------------------
struct cat_model_d
{
    int eyesVisible;
    int whiskersVisible;
    int mouthVisible;
    // ...
};
extern struct cat_model_d  CatModel;   // Cat model 0.


// -----------------------------------------
//  Flying cube.
struct cube_model_d
{
    float fThetaAngle;
    struct gr_vecF3D_d vecs[32];
    int colors[32];
    float hposition;  //horisontal position
    float vposition;  //vertical position
    float model_initial_distance;
    float model_distance;

// Acceletarion: How fast the velocity changes.
    float a;
// Velocity:
    float v;
// Time:
    float t;
};

extern struct cube_model_d *terrain;

// -----------------------------------------

void __setupCatModel(int eyes, int whiskers, int mouth );
void __draw_cat(int eye_scale, int cat_x, int cat_y, int cat_z);
void __draw_demo_curve1(int position, int model_z);
void drawRectangle0(float modelz);






