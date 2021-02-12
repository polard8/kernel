
#ifndef __DEMOS_H
#define __DEMOS_H  1


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

void setupCatModel(int eyes, int whiskers, int mouth );




//
// == fred demo  ===========================================
//
void demoFred0(void);
void demoFred1(void);
void demoFred2(void);
// ...

//start up animation
void demoSA1(void);
// ...


void demoCube1(void);
void demoCube2(void);

void demoCurve(void);

void demoMatrix1(void);

void demoCat(void);

void demos_startup_animation(int i);


#endif    



