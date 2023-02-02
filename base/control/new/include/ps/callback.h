

// callback.h

#ifndef __CALLBACK_H
#define __CALLBACK_H    1

extern unsigned long asmflagDoCallbackAfterCR3;

//extern unsigned long asmRing3CallbackAddress;
extern unsigned long ring3_callback_address;

struct ws_callback_info_d
{
    int initialized;  // initialized for the first time.
    
    int ready;  // pronto para uso.
    unsigned long callback_address;
    unsigned long callback_address_saved;
};

//extern int _callback_status;
//extern unsigned long _callback_address;
//extern unsigned long _callback_address_saved;

extern struct ws_callback_info_d  ws_callback_info;

// -------------

void initialize_ws_callback_info(void);
void setup_callback(unsigned long r3_address);
void prepare_next_ws_callback(void);

#endif    



