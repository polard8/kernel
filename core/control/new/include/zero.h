
// zero.h


#ifndef __ZERO_H
#define __ZERO_H    1

void zero_initialize_virtual_consoles(void);
void zero_initialize_video(void);
void zero_initialize_runtime(int arch_id);
void zero_initialize_background(void);
int zero_initialize_x64(void);
void zero_initialize_default_kernel_font(void);
void zero_show_banner(void);
int zero_initialize_arch(int arch_type);

#endif   


