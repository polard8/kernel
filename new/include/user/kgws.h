
// kgws.h

#ifndef __KGWS_H
#define __KGWS_H    1




//
// == prototypes =====================================
//




int init_gramado (void);


int windowLoadGramadoIcons (void);
void *ui_get_system_icon ( int n );


// ========

// See: kgwm.c
unsigned long 
__kgwm_ps2kbd_procedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

int 
sendto_eventqueue ( 
    int tid,
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte );

// Send message.
// Pega um scancode, transforma em caractere e envia na forma de mensagem
// para a thread de controle associada com a janela que tem o foco de entrada.

int 
UserInput_SendKeyboardMessage (
    int tid, 
    unsigned char raw_byte );


int
kgws_send_to_tid ( 
    int tid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );


int
kgws_send_to_foreground_thread ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

int KGWS_initialize(void);

void kgws_enable(void);
void kgws_disable(void);

int kgwsRegisterWindowServer (int pid);

#endif   



