
// detect.h

#ifndef __DETECT_H
#define __DETECT_H    1

int hal_probe_cpu(void);
int hal_probe_processor_type(void);

int detect_hv(void);

int isQEMU(void);

#endif    

