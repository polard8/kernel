
// kgws.h

#ifndef __KGWS_H
#define __KGWS_H    1




//
// == prototypes =====================================
//

int init_gramado (void);


int windowLoadGramadoIcons (void);
void *ui_get_system_icon ( int n );


// ==

int KGWS_initialize(void);

void kgws_enable(void);
void kgws_disable(void);

int kgwsRegisterWindowServer (int pid);

#endif   



