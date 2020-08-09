
#ifndef ____PIPE_H
#define ____PIPE_H



int sys_dup ( int oldfd );
int sys_dup2 (int oldfd, int newfd);
int sys_dup3 (int oldfd, int newfd, int flags);


// POSIX.1-2001, POSIX.1-2008.
// See: fs.c
int sys_pipe ( int *pipefd, int flags );


//#todo: 
//o serviço de ler num pipe deve ser o mesmo de ler num stream dado o fd.
int sys_read_pipe ( int fd, char *ubuf, int count );


//#todo: 
//o serviço de escrever num pipe deve ser o mesmo de escrever num stream dado o fd.
int sys_write_pipe ( int fd, char *ubuf, int count );


#endif


//
// End.
//




