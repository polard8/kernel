
#include "../../eng1/gws.h"


char *args[] = { 
    "nothing", 
    NULL 
};

// Cat
struct model_d
{
    int eyesVisible;
    int whiskersVisible;
    int mouthVisible;

    unsigned int head_color;
    unsigned int eye_color;
    unsigned int whisker_color;
    unsigned int mouth_color;

};
struct model_d  Model;

// include inside the engine.
void gr_setup(void)
{
    //printf("gr_setup:\n");
    //__setupCatModel(TRUE,TRUE,TRUE);

    Model.eyesVisible     = TRUE; //eyes;
    Model.whiskersVisible = TRUE; //whiskers;
    Model.mouthVisible    = TRUE; //mouth;

    Model.head_color    = COLOR_YELLOW;
    Model.eye_color     = COLOR_BLUE;
    Model.whisker_color = COLOR_WHITE;
    Model.mouth_color   = COLOR_RED;
}

// include inside the engine.
void gr_draw(void)
{
    //printf("gr_draw:\n");
    //demoCat();

    int Lcount = 0;

// model
    int model_x = (int) 0; //cat_x;
    int model_y = (int) 0; //cat_y;
    int model_z = (int) 0; //cat_z;
// eyes
    int eye_scale=1;
    int eye1_x = model_x -10;
    int eye1_y = model_y +20;
    int eye2_x = model_x +10;
    int eye2_y = model_y +20;
    int eye_radius = (int) (1*eye_scale);
//---



    while(1)
    {
        validate_background();
        demoClearSurface(NULL,COLOR_BLACK);
        //printf("draw\n");
        
        if(Lcount>8)
           break;
           
        //update model
        // model
        model_x += Lcount;  //cat_x;
        model_y += Lcount;  //cat_y;
        model_z = 0;       //cat_z;
        // eyes
        eye_scale=1;
        eye1_x = model_x -10;
        eye1_y = model_y +20;
        eye2_x = model_x +10;
        eye2_y = model_y +20;
        eye_radius = (int) (1*eye_scale);
        
        //head
        plotCircleZ ( 
            NULL,
            model_x +0,    //x
            model_y +12,   //y
            25,   //r
            Model.head_color,     //color 
            model_z );      // z 


        // eyes
        if ( Model.eyesVisible == TRUE )
        {
            plotCircleZ ( 
                NULL,
                eye1_x, 
                eye1_y, 
                eye_radius, 
                Model.eye_color, 
                model_z );  //z 
            
            plotCircleZ ( 
                NULL,
                eye2_x, 
                eye2_y, 
                eye_radius, 
                Model.eye_color, 
                model_z );  //z 
        }

        // whiskers
        if ( Model.whiskersVisible == TRUE ){
        // =
        plotLine3d ( 
            NULL,
            model_x -40, model_y +8, model_z, 
            model_x -4,  model_y +5, model_z, 
            Model.whisker_color); 
        plotLine3d ( 
            NULL,
            model_x -40, model_y +5, model_z, 
            model_x -4,  model_y +4, model_z, 
            Model.whisker_color); 
        plotLine3d ( 
            NULL,
            model_x -40, model_y +2, model_z, 
            model_x -4,  model_y +3, model_z, 
            Model.whisker_color); 

        // =
        plotLine3d ( 
            NULL,
            model_x + 4,  model_y +5, model_z, 
            model_x + 40, model_y +8, model_z, 
            Model.whisker_color); 
        plotLine3d ( 
            NULL,
            model_x + 4,  model_y +4, model_z, 
            model_x + 40, model_y +5, model_z, 
            Model.whisker_color); 
        plotLine3d ( 
            NULL,
            model_x + 4,  model_y +3, model_z, 
            model_x + 40, model_y +2, model_z, 
            Model.whisker_color); 
        }

        // mouth
        if ( Model.mouthVisible == TRUE )
        {
        plotLine3d ( 
            NULL,
            model_x -10, model_y -2, model_z, 
            model_x +10, model_y -2, model_z, 
            Model.mouth_color); 

        unveil_camera ( model_x, model_y, model_z );
        //unveil_camera ( res_x, res_y, res_z );
        }

        demoFlushSurface(NULL);
        
        Lcount++;
    };
}

int main(int argc, char **argv)
{
    // chama o main() da engine
    //eng1_main();
    
    printf("DEMO1.BIN: Initializing ...\n");
    eng1_main(1,args);
    
    return 0;
}



