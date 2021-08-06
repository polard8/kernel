
#ifndef ____SCREEN_H
#define ____SCREEN_H    1

#define COLUMNS  80
#define ROWS     25
#define SCREEN_WIDTH   COLUMNS
#define SCREEN_HEIGHT  ROWS
#define SCREEN_DEFAULT_LEFT  0
#define SCREEN_DEFAULT_TOP   0


unsigned long screen_size_in_kb;
int refresh_screen_flag;


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
struct screen_d  *Screen;
struct screen_d  *ScreenInfo;
struct screen_d  *CurrentScreen;
//...
  
//int screenCount;    //Numero de monitores.
//unsigned long screenList[8];



//
// == prototypes =========================
//

unsigned long screenGetWidth (void);
unsigned long screenGetHeight (void);
void screenSetSize( unsigned long width, unsigned long height );


void refresh_screen (void);

int screenInit (void);

#endif    


