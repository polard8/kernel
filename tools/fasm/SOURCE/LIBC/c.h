
// c.h 




//fasm support 

void *fasm_malloc ( size_t size );
FILE *fasm_fopen( const char *filename, const char *mode ); 
void fasm_exit(int code);
void testWrite();
size_t fasm_write (int fd, char *buf, size_t cnt);






