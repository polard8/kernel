//Standard PS/2 Mouse Commands
//Byte	Data byte	Description
//0xFF	None	Reset
//0xFE	None	Resend
//0xF6	None	Set Defaults
//0xF5	None	Disable Data Reporting
//0xF4	None	Enable Data Reporting
//0xF3	Sample rate, ranges from 10-200.	Set Sample Rate
//0xF2	None	Get Device ID. See Detecting PS/2 Device Types for the response bytes.
//0xF0	None	Set Remote Mode
//0xEE	None	Set Wrap Mode
//0xEC	None	Reset Wrap Mode
//0xEB	None	Read Data
//0xEA	None	Set Stream Mode
//0xE9	None	Status Request


#define MOUSE_RESET  0xFF
#define MOUSE_RESEND 0xFE
#define MOUSE_SET_DEFAULTS 0xF6
//#define MOUSE_
//#define MOUSE_
#define MOUSE_ENABLE_DATA_REPORTING          0xF4


//RESPONSES 

#define MOUSE_COMPLETE  0xAA
#define MOUSE_ID_BYTE   0x00
 
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


unsigned long g_mousepointer_width;
unsigned long g_mousepointer_height;


void mouse_write(unsigned char write);
unsigned char mouse_read();



static unsigned char getMouseData(void);


void kernelPS2MouseDriverReadData(void);


//bmp
//buffer para o bmp
void *mouseBMPBuffer; 
int load_mouse_bmp();



void mouseHandler(); 
void ps2_mouse_initialize();
int ps2_mouse_globals_initialize();


void mouse_install();   


//deletar
void 
DialogBox( struct window_d *parent_window, 
           int type, 
		   char *title, 
		   char *string );
		   
		   
		   
		  
//
//
//


