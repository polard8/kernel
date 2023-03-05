
// ps2.h

#ifndef ____PS2_H
#define ____PS2_H    1


/*
 Wikipedia
 O conector PS/2 é um conector mini-DIN de 6 pinos usado para conectar alguns 
 teclados e mouses a um sistema de computador compatível com PC. 
 Seu nome vem da série de computadores pessoais IBM Personal System/2, 
 com o qual ele foi introduzido em 1987. O conector de mouse PS/2 geralmente 
 substitui antigos conectores de "mouses seriais" DE-9 RS-232, 
 enquanto o conector de teclado PS/2 substituiu o conector DIN mais largo de 5 pinos/180º 
 usado no desenho do IBM PC/AT. Os desenhos PS/2 nas interfaces de teclados e 
 mouses são eletricamente similares e empregam o mesmo protocolo de comunicação. 
 Entretanto, a porta de teclado ou mouse de um determinado sistema pode não ser 
 intercambiável uma vez que os dois dispositivos usam um conjunto de comandos diferentes.
 
A comunicação é serial, síncrona e bidirecional.[1] 
O dispositivo conectado gera o sinal de relógio. O hospedeiro controla a comunicação usando a 
linha de relógio. Quando o hospedeiro puxa o relógio para baixo, a comunicação do dispositivo é inibida.
*/

//
// Definições.
//

#define  PS2_PORT    0x60
#define  PS2_CTRL    0x64
#define  PS2_ACK     0xFA 
//...

// ================================

// The main ps/2 configuration structure.
struct ps2_d
{
    int used;
    int magic;
    
    // #hackhack
    // Use pooling or not.
    // TRUE, FALSE
    // :: 
    // Maybe something is wrong with the 
    // USB/PS2 emulation microcode in my real machine.
    // Maybe the 'interrupts' is not working in the 
    // 32 bit protected mode. 
    // Maybe we can use 'pooling' to aboid this issue. 
    // Just like in Temple OS.
    // ps: Some other OSs are facing the same problem.
    int pooling;

    //flags: TRUE or FALSE,
    int keyboard_initialized;
    int mouse_initialized;
    
    // #todo
    // We can create these two structures.
    // See: ps2kbd.h and ps2mouse.h
    // struct ps2_keyboard_d *ps2_keyboard;
    // struct ps2_mouse_d    *ps2_mouse;
    
    // ...
};

// #important:
// use ps2_ioctl to setup this structure.
// The app needs to open the file /PS2, something like that.

struct ps2_d  PS2;
// ================================


//
// == prototypes ===========================================
//


// ================
// Early initialization
// Only the keyboard.
// It is working
int PS2_early_initialization(void);

// ================
// This is the full initialization.
// #bugbug This is a test yet.
// It fails in the real machine.
int PS2_initialization(void);

void ps2(void);
int PS2_initialize(void);

void ps2kbd_initialize_device (void);
void ps2mouse_initialize_device (void);

int ps2_ioctl ( int fd, unsigned long request, unsigned long arg );

#endif    



