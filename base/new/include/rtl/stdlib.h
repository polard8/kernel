
#ifndef  __STDLIB_H
#define __STDLIB_H    1


// A rotina terminou normalmente. 
#define EXIT_SUCCESS  0

// A rotina terminou de maneira anormal. 
#define EXIT_FAILURE  1

// Números pseudo-aleatórios   
#define RAND_MAX  32767    //0x7FFF



//
// prototypes ===========================
//

int rand(void);
int __ptsname (int fd, char *buf, size_t buflen);

void *kmalloc (size_t size);
void kfree (void *ptr);


int abs(int j);

#endif    


