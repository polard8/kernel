
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


// This functions belongs to the demo module inside another project.
void gr_setup(void);
void gr_draw(void);


void gr_embedded_setup(void);
void gr_embedded_draw(void);


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
void __setupCatModel(int eyes, int whiskers, int mouth );
void demoCat(void);

void demoModel1(void);

#endif    



