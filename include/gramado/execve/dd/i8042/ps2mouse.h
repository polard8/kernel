

 
//=======================================================
//++ Usadas pelo mouse.
// hardwarelib.inc
//
#define MOUSE_X_SIGN	0x10
#define MOUSE_Y_SIGN	0x20


int saved_mouse_x;
int saved_mouse_y;

//Coordenadas do cursor.
extern int mouse_x;
extern int mouse_y;

//Bytes do controlador.
extern char mouse_packet_data;
extern char mouse_packet_x;
extern char mouse_packet_y;
//extern char mouse_packet_scroll;
 
extern void update_mouse();


//Estado dos botões do mouse
int mouse_buttom_1; 
int mouse_buttom_2;
int mouse_buttom_3;

//Estado anterior dos botões do mouse.
int old_mouse_buttom_1; 
int old_mouse_buttom_2;
int old_mouse_buttom_3;

//se ouve alguma modificação no estado 
//dos botões.
int mouse_button_action;

//--
//=========================================================



//?? usado pelo mouse
#define outanyb(p) __asm__ __volatile__( "outb %%al,%0" : : "dN"((p)) : "eax" )









//
// Mouse support
//

//bytes do controlador.
char mouse_status;
char delta_x;
char delta_y;

//coordenadas.
int mouse_pos_x;
int mouse_pos_y;









void mouse_write(unsigned char write);
unsigned char mouse_read();







void 
DialogBox( struct window_d *parent_window, 
           int type, 
		   char *title, 
		   char *string );
		   
		   
		   
		   

		   

		   
		   
		   
//
//
//


