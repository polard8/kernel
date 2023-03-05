
// font.c
// ring0

#include <kernel.h>

// #todo
// Move more variables from ws.h to font.c.
unsigned long gws_currentfont_address=0;
unsigned long g8x8fontAddress=0;     // 8×8, 80×25,CGA, EGA
unsigned long g8x14fontAddress=0;    // 8x14,80×25,EGA
unsigned long g8x16fontAddress=0;    // ??
unsigned long g9x14fontAddress=0;    // 9x14,80×25,MDA, Hercules
unsigned long g9x16fontAddress=0;    // 9x16,80×25,VGA
//...

int gfontSize=8;

// #todo: 
// We need a global structure for font support.

int gwsInitializeDefaultKernelFont(void)
{
// BIOS 8x8 font.

    fontSetCurrentAddress(BIOSFONT8X8);
    gwsSetCurrentFontCharWidth(8);
    gwsSetCurrentFontCharHeight(8);
    gfontSize = FONT8X8;
    return 0;
}


int gwsGetCurrentFontCharWidth (void)
{
    return (int) get_char_width();
}

void gwsSetCurrentFontCharWidth (int width)
{
    set_char_width (width);
}

int gwsGetCurrentFontCharHeight (void)
{
    return (int) get_char_height();
}

void gwsSetCurrentFontCharHeight (int height)
{
    set_char_height (height);
}

unsigned long fontGetCurrentAddress(void)
{
    return (unsigned long) gws_currentfont_address;
}

// Set the base address for the current font.
void fontSetCurrentAddress(unsigned long address)
{
    gws_currentfont_address = (unsigned long) address;
}

// gwsInstallFont:
// Carregando e instalando uma fonte dado o nome.
int gwsInstallFont (char *file_name)
{
// Load a font from the disk.
// # Not in use.

    unsigned long fileret=0;

// #todo #bugbug
// Rever esse tamanho.

    unsigned long tmp_size = (8*4096);
    void *font_buffer = (void *) allocPages(8);

    if ( (void *) file_name == NULL ){
        panic ("gwsInstallFont: file_name\n");
    }
    if ( *file_name == 0 ){
        panic ("gwsInstallFont: *file_name\n");
    }
    if ( (void *) font_buffer == NULL ){
        panic ("gwsInstallFont: font_buffer\n");
    }

// Load file from root dir.
// #bugbug: 
// (FAT16_ROOT_ENTRIES) Number of entries.

    unsigned long dir_address = VOLUME1_ROOTDIR_ADDRESS;
    int number_of_entries = FAT16_ROOT_ENTRIES;

    fileret = 
        (unsigned long) fsLoadFile ( 
                            (unsigned long) VOLUME1_FAT_ADDRESS, 
                            (unsigned long) dir_address, 
                            (int) number_of_entries, 
                            (const char *) file_name, 
                            (unsigned long) font_buffer,
                            (unsigned long) tmp_size );

    if (fileret != 0){
        panic ("gwsInstallFont: fileret\n");
    }

// Set the address for the current font.
    unsigned long base_address = (unsigned long) (font_buffer + 0x2000);
    fontSetCurrentAddress(base_address);

    return 0;
}

//
// End
//













