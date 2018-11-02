

//ps2kbd.h 

//Status
//@todo: Status pode ser (int).
//variáveis usadas pelo line discipline para controlar o 
//estado das teclas de controle.

unsigned long key_status;
unsigned long escape_status;
unsigned long tab_status;
unsigned long winkey_status;
unsigned long ctrl_status;
unsigned long alt_status;
unsigned long shift_status;
unsigned long capslock_status;
unsigned long numlock_status;
unsigned long scrolllock_status;
//...

void  ps2_keyboard_initialize();

void ldisc_init_modifier_keys();
void ldisc_init_lock_keys();

