

#ifndef  __MK_H
#define __MK_H    1


/*
 * Segments @todo: Include this constants.
 * it's Intel's specific stuff.
 *
#define GDT_KCODE   0x08
#define GDT_KDATA   0x10
#define GDT_UCODE   (0x18 | 3)
#define GDT_UDATA   (0x20 | 3)
*/


//
//  ## JOB CONTROL SUPPORT ##
//

#define PROCESS    10
#define THREAD     20
#define BACKGROUND 100 
#define FOREGROUND 200

//
// == prototypes =========================
//

int init_microkernel (void);

int jobcheck ( int type, int id );
int jobcontrol ( int type, int id, int plane );

#endif   

