


#include <kernel.h>



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

unsigned long gwsGetCurrentFontAddress (void)
{
    return (unsigned long) gws_currentfont_address;
}

void gwsSetCurrentFontAddress ( unsigned long address )
{
    gws_currentfont_address = (unsigned long) address;
}


/* 
 * gwsInstallFont:
 *     Carregando e instalando uma fonte dado o nome. 
 */

int gwsInstallFont ( char *file_name ){

    unsigned long fileret=0;

	// #todo #bugbug
	// Rever esse tamanho.

    unsigned long tmp_size = (8*4096);
    void *font_buffer = (void *) allocPages (8);


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

    fileret = (unsigned long) fsLoadFile ( 
                                  (unsigned long) VOLUME1_FAT_ADDRESS, 
                                  (unsigned long) dir_address, 
                                  (int) number_of_entries, 
                                  (const char *) file_name, 
                                  (unsigned long) font_buffer,
                                  (unsigned long) tmp_size );

    if ( fileret != 0 ){
        panic ("gwsInstallFont: fileret\n");
    }

// Configurando o endereço da fonte atual.
    gwsSetCurrentFontAddress ( (unsigned long) (font_buffer + 0x2000) );

    return 0;
}


//
// End.
//













