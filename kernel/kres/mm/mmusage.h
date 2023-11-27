

#ifndef __MM_MMUSAGE_H
#define __MM_MMUSAGE_H    1


//========================================================
// Used memory:
// Estamos medindo o uso de memória física.
// Lembrando que a mesma região de memória física
// pode ser mapeada mais de uma vez.
// #todo #bugbug
// Precisamos checar corretamente qual é o endereço físico
// de cada uma dessas regiões e suas sobreposições.
// see: mminit.c
extern unsigned long mm_used_ring0_area;  // start = 0 size = 4MB
extern unsigned long mm_used_ring3_area;  // start = 0x400000 size = 4MB
extern unsigned long mm_used_kernelimage;
extern unsigned long mm_used_backbuffer;  // start = 0x800000 size = 4MB
extern unsigned long mm_used_pagedpool;   // start = 0xC00000 size = 4MB  
extern unsigned long mm_used_heappool;    // start = 0x01000000 size = 4MB   
extern unsigned long mm_used_extraheap1;  // start = (0x01000000 + 0x400000) size = 4MB
extern unsigned long mm_used_extraheap2;  // start = (0x01000000 + 0x800000) size = 4MB
extern unsigned long mm_used_extraheap3;  // start = (0x01000000 + 0xC00000) size = 4MB
extern unsigned long mm_used_frame_table;
// start = ?? size = 2MB
extern unsigned long mm_used_lfb; 




#endif   

