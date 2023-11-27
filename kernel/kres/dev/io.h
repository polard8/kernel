
// io.h

#ifndef __HAL_IO_H
#define __HAL_IO_H    1

int ioInit(void);
int io_ioctl( int fd, unsigned long request, unsigned long arg );

#endif    


