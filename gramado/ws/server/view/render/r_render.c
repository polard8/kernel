

#include <gws.h>



/*
 //#test.
void
r_render_copy_buffer (
    char *target_ptr,
    char *source_ptr,
    unsigned long length );
void
r_render_copy_buffer (
    char *target_ptr,
    char *source_ptr,
    unsigned long length )
{
    while (length--){
        *target_ptr++ = *source_ptr++;
    };
}
*/


/*
void r_render_copy_to_lfb (unsigned long ofs, int count);
void r_render_copy_to_lfb (unsigned long ofs, int count)
{
    memcpy (
        screens[0]+ofs, 
        screens[1]+ofs, 
        count );
}
*/


void r_refresh_screen(void)
{
    //todo
}
