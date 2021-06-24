


#include <kernel.h>



int gwsGetCurrentFontCharWidth (void)
{
    return (int) get_char_width();
}

int gwsGetCurrentFontCharHeight (void)
{
    return (int) get_char_height();
}



