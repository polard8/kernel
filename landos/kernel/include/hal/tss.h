
// tss.h

#ifndef __TSS_H
#define __TSS_H    1


// See:
// https://wiki.osdev.org/Task_State_Segment

typedef struct tss_d {

    unsigned int reserved;
    
    unsigned long rsp0; 
    unsigned long rsp1; 
    unsigned long rsp2;

    unsigned int reserved2[2];

    unsigned long ist1; 
    unsigned long ist2; 
    unsigned long ist3; 
    unsigned long ist4; 
    unsigned long ist5; 
    unsigned long ist6; 
    unsigned long ist7;

    unsigned int reserved3[2];

    unsigned short reserved4;
    unsigned short IOPB_offset;

}__attribute__((packed)) tagTSS;



//
// == prototypes ===========================
//

#endif    



