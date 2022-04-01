
// ps2mouse.h

#ifndef ____PS2MOUSE_H
#define ____PS2MOUSE_H    1


#define PS2MOUSE_RESULUTION    3

// Sampling Rate: 
// Packets the mouse can send per second.
//#define PS2MOUSE_DEFAULT_SAMPLERATE  100
#define PS2MOUSE_DEFAULT_SAMPLERATE  200


// #bugbug
// We have these same definitions on ps2mouse.c ??

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

// 8042 mouse commands.
#define MOUSE_SET_RESOLUTION           0xE8
#define MOUSE_READ_STATUS              0xE9
#define MOUSE_GET_DEVICE_ID            0xF2
#define MOUSE_SET_SAMPLING_RATE        0xF3
#define MOUSE_ENABLE_DATA_REPORTING    0xF4  // Enable mouse transmition.
#define MOUSE_SET_DEFAULTS             0xF6
#define MOUSE_RESEND                   0xFE
#define MOUSE_RESET                    0xFF



#define PS2MOUSE_GET_DEVICE_ID      0xF2
#define PS2MOUSE_SET_SAMPLE_RATE    0xF3

//intelligente mouse
#define PS2MOUSE_INTELLIMOUSE_ID 0x03
#define PS2MOUSE_INTELLIMOUSE_EXPLORER_ID 0x04


// 8042 mouse responses.
#define MOUSE_ID_BYTE       0x00
#define WHEELMOUSE_ID_BYTE  0x03 
#define MOUSE_COMPLETE      0xAA 
//...

// Generic PS/2 Mouse Packet Bits

#define  MOUSE_LEFT_BUTTON    0x01
#define  MOUSE_RIGHT_BUTTON   0x02
#define  MOUSE_MIDDLE_BUTTON  0x04
//#define BUTTON_4           0x10
//#define BUTTON_5           0x20

#define  MOUSE_X_DATA_SIGN    0x10
#define  MOUSE_Y_DATA_SIGN    0x20
#define  MOUSE_X_OVERFLOW     0x40
#define  MOUSE_Y_OVERFLOW     0x80

//
// =====================================================
//


// mouse info.
// This is gonna be used by PS2 structure in ps2.h
struct ps2_mouse_d
{
    object_type_t  objectType;
    object_class_t objectClass;

    int device_id;

    int initialized;

    unsigned int resolution;
    unsigned int sample_rate;

    // #todo
    // int control_fd;
    // int input_fd;
    // pid_t pid;

// Device id
// If the mouse has been initalized so 
// that its mouseID is 3 or 4, it will send a 4th byte in each packet.

    int has_wheel;
    int has_five_buttons;
};

//#todo
// If we have only one mouse device.
struct ps2_mouse_d  PS2Mouse;


//
// Stop
//

// The interrupt handler will not work.

//int ps2mouseStopped;


//usado pra exibir provisoriamente alguma imagem em cima da janela 
//que o mouse passa por cima.
unsigned long savedmouseoverwindowX;
unsigned long savedmouseoverwindowY;


//#deletar
//Coisas que antes eram importadas de hwlib.inc e qua não são mais.
//Coordenadas do cursor.
//extern int mouse_x;
//extern int mouse_y;
//Bytes do controlador.
//extern char mouse_packet_data;
//extern char mouse_packet_x;
//extern char mouse_packet_y;
//extern char mouse_packet_scroll;
//extern void update_mouse();


//Estado dos botões do mouse
int mouse_button_1; 
int mouse_button_2;
int mouse_button_3;

//Estado anterior dos botões do mouse.
int old_mouse_button_1; 
int old_mouse_button_2;
int old_mouse_button_3;

//se ouve alguma modificação no estado 
//dos botões.
int mouse_button_action;

//--
//=========================================================

unsigned long g_mousepointer_width;
unsigned long g_mousepointer_height;


//
// == prototypes =====================
//

void DeviceInterface_PS2Mouse(void);

void zzz_mouse_write(unsigned char data);
unsigned char zzz_mouse_read (void);
void mouse_expect_ack (void);


#endif    















