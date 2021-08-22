
// sprite

#include <gws.h>



/*
// #todo
// create a sprite of given types and
// return the structure.
// The caller will put that pointer in a list
// to call the loop function PlotSprite3D().
struct gws_sprite_d *create_sprite_point()
struct gws_sprite_d *create_sprite_line()
struct gws_sprite_d *create_sprite_circle()
*/


/*
//#todo
struct gws_sprite_d *create_sprite_point (int z, int x, int y, unsigned long color);
struct gws_sprite_d *create_sprite_point (int z, int x, int y, unsigned long color)
{
    struct gws_sprite_d *sprite;

    sprite = (struct gws_sprite_d *) malloc( sizeof(struct gws_sprite_d) );
    
    // todo check.
    
    sprite->x1 = x;
    sprite->y1 = y;
    sprite->z1 = z;
    sprite->color1 = color;

    return (struct gws_sprite_d *) sprite;
}
*/



/*
 * PlotSprite3D:
 * 
 *     display     - display structure.
 *     x,y,z       - position.
 *     sprite_list - linked list of sprite structures.
 *     list_size   - how many elements in the list.
 */

int 
PlotSprite3D ( 
    struct gws_display_d *display,
    int x, int y, int z,
    unsigned long sprite_list_address,
    int sprite_list_size,
    int just_one )
{

    unsigned long *list = (unsigned long *) sprite_list_address;

    struct gws_sprite_d *sprite;
    int Type = SPRITE_NULL;

    int i=0;
    int number_of_elements = sprite_list_size;
    int Max = SPRITE_MAX_NUMBER;


    gwssrv_debug_print("PlotSprite3D: [TODO] \n");
 
    // invalid address
    if ( sprite_list_address == 0 )
    {
        gwssrv_debug_print("PlotSprite3D: [FAIL] sprite_list_address\n");
        return -1;
    }

    // no elements
    if ( number_of_elements <= 0 )
    {
        gwssrv_debug_print("PlotSprite3D: [FAIL] no elements\n");
        return -1;
    }

    // too much elements
    if ( number_of_elements >= SPRITE_MAX_NUMBER )
    {
        gwssrv_debug_print("PlotSprite3D: [FAIL] number_of_elements\n");
        return -1;
    }


    // Loop: 
    // todos os elementos da lista.
    
    for(i=0; i<number_of_elements; i++){


    // Get sprite structure.

    sprite = (struct gws_sprite_d *) list[i];

    // last one.
    if ( (void*) sprite == NULL ){
        gwssrv_debug_print("PlotSprite3D: [ERROR] sprite \n");
        break;
    }

    if ( sprite->used != 1 || sprite->magic != 1234 ){
        gwssrv_debug_print("PlotSprite3D: [ERROR] sprite validation\n");
        break;
    }

    // type
    Type = sprite->type;
    switch (Type){

        // #todo
        // Insert here the primitives.
        
        case SPRITE_NULL:
            gwssrv_debug_print("PlotSprite3D: [SPRITE_NULL] \n");
            break;
        
        case SPRITE_POINT:
            gwssrv_debug_print("PlotSprite3D: [SPRITE_POINT] \n");
            grPlot0 (
                NULL, 
                (int) (z + sprite->z1), 
                (int) (x + sprite->x1), 
                (int) (y + sprite->y1), 
                (unsigned long) sprite->color1 );
            break;

        case SPRITE_LINE:
            gwssrv_debug_print("PlotSprite3D: [SPRITE_LINE] \n");
            plotLine3d ( 
               (int) (x + sprite->x1), 
               (int) (y + sprite->y1), 
               (int) (z + sprite->z1), 
               (int) (x + sprite->x2), 
               (int) (y + sprite->y2), 
               (int) (z + sprite->z2), 
               (unsigned long) sprite->color1 );
            break;

        case SPRITE_CIRCLE:
            gwssrv_debug_print("PlotSprite3D: [SPRITE_CIRCLE] \n");
            plotCircleZ ( 
                (int) (x + sprite->x1),           // xm 
                (int) (y + sprite->y1),           // ym 
                (int) sprite->r,                  // r 
                (unsigned long) sprite->color1,   // color 
                (int) (z + sprite->z1) );         // z 
            break;
            
        // ...
        
        default:
            gwssrv_debug_print("PlotSprite3D: [default] \n");
            break;

    };
    
        if ( just_one == TRUE ){  break;  }
    };


    // #todo
    // Restaura para o padrao os elemento da estrutura display.
    // device context
    
    gwssrv_debug_print("PlotSprite3D: done \n");
    
    return 0;
}

