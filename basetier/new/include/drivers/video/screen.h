
// screen.h

#ifndef ____SCREEN_H
#define ____SCREEN_H    1


#define COLUMNS  80
#define ROWS     25
#define SCREEN_WIDTH   COLUMNS
#define SCREEN_HEIGHT  ROWS
#define SCREEN_DEFAULT_LEFT  0
#define SCREEN_DEFAULT_TOP   0


unsigned long screen_size_in_kb;
// hack: for debuging purpose
int g_use_fake_screen_size;
unsigned long fake_screen_size_in_kb;


// The refresh is enabled we mapped
// memory enough for that.
int refresh_screen_enabled;

// We need to flush the whole screen into the frontbuffer.
int screen_is_dirty;



//
// PAINT
//

// #sobre:
// A estrutura PAINT vai descrever os planos
// que serão usados pelo compositor para desenhar
// a tela.
// Cada plano tem seu backbuffer e seu frontbuffer.
// A placa de vídeo fará todos os frontbuffers serem pintados
// na mesma tela, gerando efeito de sombra e transparência.


struct plane_d
{
    int used;
    
    unsigned char *frontbuffer;
    unsigned char *backbuffer;
    
    unsigned long size_x;
    unsigned long size_y;
    unsigned long size_bpp;
};

struct paint_d
{
    struct plane_d plane[4];
    int number_of_planes;
};

struct paint_d PAINT;


/*
 * struct screen_d:
 *     Estrutura para informações sobre o monitor.
 *     Screen Object.
 */

struct screen_d 
{
    object_type_t  objectType;
    object_class_t objectClass;

    int used;
    int magic;
    
    int id;

    // #todo
    //struct display_d *display;

    unsigned long left;
    unsigned long top;  
    unsigned long width; 
    unsigned long height; 

    unsigned long flag; 
    unsigned long error;  


    //Navigation.
    struct screen_d *next; 
};

struct screen_d  *CurrentScreen;
struct screen_d  *Screen;
struct screen_d  *ScreenInfo;

//...
  
//int screenCount;    //Numero de monitores.
//unsigned long screenList[8];



//
// == prototypes =========================
//

// The whole screen is dirty.
// It can be flushed into the framebuffer.

void invalidate_screen(void);

void screenSetSize( unsigned long width, unsigned long height );

unsigned long screenGetWidth (void);
unsigned long screenGetHeight (void);
unsigned long screenGetBPP (void);

unsigned long screenGetPitch (void);

unsigned long screen_scanline_va( int scanline );

void fb_refresh_screen (unsigned long flags);
void refresh_screen (void);

int screenInit (void);

#endif    


