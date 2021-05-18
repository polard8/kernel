/*
 * File: keyboard.h
 *     Header para driver de teclado.
 */
 
 
 
#ifndef ____KEYBOARD_H
#define ____KEYBOARD_H


#define KEYBOARD_DRIVER_VERSION "0.1"



//
// ## keybuffer ##
//

// #bugbug
// Esses offsets precisar estar dentro da estrutura de tty
// pois lidam com um buffer dentro dela.
 
int keybuffer_index; 
int keybuffer_head;
int keybuffer_tail;
int keyboard_message_head;
int keyboard_message_tail;

struct tty_d PS2keyboardTTY;



// Estrutura para enviar mensagens de teclado do kernel para 
// um aplicativo em user mode. 

struct keyboard_message_d
{
    int used;
    int magic;

    // Identificadores.
    struct process_d  *receiver_process;
    struct process_d  *receiver_thread;

    struct window_d *receiver_window;

    // Dados.
    struct window_d  *window;
    int  msg;
    unsigned long  long1;
    unsigned long  long2;
}; 

struct keyboard_message_d keyboard_queue[8]; 



//
// == prototypes =======================================
//


void DeviceInterface_PS2Keyboard(void);

int ps2tty_get_byte_from_input_buffer (void);
void ps2tty_put_byte_into_input_buffer( char c );


#endif   


//
// End.
//

