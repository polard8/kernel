
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

    unsigned int head_color;
    unsigned int eye_color;
    unsigned int whisker_color;
    unsigned int mouth_color;

    // ...
};
struct cat_model_d CatModel;


//
// == Prototypes ===============
//

void demoClearSurface(struct gws_window_d *clipping_window, unsigned int color);
void demoFlushSurface(struct gws_window_d *clipping_window);

void demos_startup_animation(int i);

void demoLines(void);
void demoLine1(void);

void demo34567(void);

void demoFred0(void);
void demoFred1(void);
void demoFred2(void);

void demoSA1(void);
void demoTriangle(void);

void demoPolygon(void);
void demoPolygon2(void);

// curve+string
void demoCurve(void);

// cat
void demoCat(void);

void demoModel1(void);

#endif    



