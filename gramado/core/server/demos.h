
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


//
// == Prototypes ===============
//

void demoClearSurface(unsigned int color);
void demoFlushSurface(void);
void demos_startup_animation(int i);

void demoLines(void);
void demoLine1(void);
void demoFred0(void);
void demoFred1(void);
void demoFred2(void);
void demoSA1(void);
void demoTriangle(void);


//mesh1
struct gr_mesh_triangle_d *__demoMesh1_worker(int number_of_elements);
void __demoMesh1_transformation(struct gr_mesh_triangle_d *mesh);
void __draw_mesh1(struct gr_mesh_triangle_d *mesh, int number_of_elements);
void demoMesh1(void);

void demoPolygon(void);
void demoPolygon2(void);
void demoCube1(void);
void demoCube2(void);

// curve+string
void __draw_demo_curve1(int position);
void demoCurve(void);

void demoMatrix1(void);

// cat

void setupCatModel(int eyes, int whiskers, int mouth );
void __draw_cat(int eye_scale);
void demoCat(void);


#endif    



