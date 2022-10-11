
// demos.h

#ifndef __DEMOS_H
#define __DEMOS_H  1


extern int gUseDemos;


//
// models
//

struct cat_model_d
{
    int eyesVisible;
    int whiskersVisible;
    int mouthVisible;
    // ...
};
struct cat_model_d CatModel;


//
// == Prototypes ===============
//


void demoClearWA(unsigned int color);
void 
demoClearSurface(
    struct gws_window_d *clipping_window, 
    unsigned int color );
void demoFlushSurface(struct gws_window_d *clipping_window);


void demoLines(void);

void demoTriangle(void);

void demoPolygon(void);
void demoPolygon2(void);

// curve+string
void demoCurve(void);

// cat
void __setupCatModel(int eyes, int whiskers, int mouth );
void demoCat(void);

void demoModel1(void);

// flying cube
void FlyingCubeMove(int left_right, float value);
void demoFlyingCubeSetup(void);
void demoFlyingCube(void);

#endif    



