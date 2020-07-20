/*
 * File: socket.c
 *
 */

// See: 
// http://man7.org/linux/man-pages/man2/socket.2.html



#include <sys/types.h>  
#include <sys/select.h>
#include <sys/socket.h>
//#include <unistd.h>




//sortix style;
/*
#define FLAGS_MASK (SOCK_NONBLOCK | SOCK_CLOEXEC | SOCK_CLOFORK)
#define TYPE_MASK (~FLAGS_MASK)
#define FLAGS(x) ((x) & FLAGS_MASK)
#define TYPE(x) ((x) & TYPE_MASK)

*/


/*
 *****************************************************
 * socket:
 *     Create an endpoint for communication.
 */

/*
  socket() creates an endpoint for communication and 
  returns a file descriptor that refers to that endpoint.  
  The file descriptor returned by a successful call will be the 
  lowest-numbered file descriptor not currently open for the process. 
 */

// Linux style.
// See: http://man7.org/linux/man-pages/man2/socket.2.html

//int socket ( int family, int type, int protocol ){

int socket ( int domain, int type, int protocol ){

    int __fd = -1;


    __fd = (int) gramado_system_call ( 7000, 
                     (unsigned long) domain, 
                     (unsigned long) type, 
                     (unsigned long) protocol );

    if(__fd<0)
        printf ("socket: Couldn't create the socket!\n");
        
    return (int) __fd;
}



//interna
//int __socket_pipe ( int pipefd[2] );
int __socket_pipe ( int pipefd[2] ){

    return (int) gramado_system_call ( 247, 
                     (unsigned long) pipefd, 
                     (unsigned long) pipefd, 
                     (unsigned long) pipefd );
}



// socketpair - create a pair of connected sockets
// POSIX.1-2001, POSIX.1-2008, 4.4BSD.  socketpair() first appeared in
// 4.2BSD.  It is generally portable to/from non-BSD systems supporting
// clones of the BSD socket layer (including System V variants).
// #bugbug: Porque o termo pipe é usado ???

int socketpair (int domain, int type, int protocol, int sv[2]){

    int fd = -1; 
    int pipefd[2];


    if ( domain == AF_UNSPEC || domain == AF_UNIX )
    {
        if ( protocol != 0 )
            return (int) (-1);

        //if ( type != SOCK_STREAM )
            //return (int) (-1);

        // Podemos colocar sv diretamente.
        fd = (int) __socket_pipe (pipefd);

        if ( fd  == -1 ) { 
            printf ("socketpair: fail\n");
            return (int) (-1);

        }else{
            sv[0] = pipefd[1];
            sv[1] = pipefd[1];
            return 0;
        };
    }


    return (int) (-1);
}


// #todo
// not tested.
/*
int gramado_socketpair (int fd[2]);
int gramado_socketpair (int fd[2])
{
    return (int) socketpair ( AF_UNIX, SOCK_STREAM, 0, fd );
}
*/


// POSIX.1-2001, POSIX.1-2008, SVr4, 4.4BSD, 
//(connect() first appeared in 4.2BSD).
// initiate a connection on a socket

// If the connection or binding succeeds, zero is returned.  
// On error, -1 is returned, and errno is set appropriately.


int 
connect ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen )
{
    int __status = -1;


    __status = (int) gramado_system_call ( 7001, 
                     (unsigned long) sockfd, 
                     (unsigned long) addr, 
                     (unsigned long) addrlen );

    if(__status<0)
        printf ("connect: Couldn't connect\n");
     

    return (int) __status;
}
           
           
           
           
/*
  The accept() system call is used with connection-based socket 
  types (SOCK_STREAM, SOCK_SEQPACKET).  
  It extracts the first connection request on the queue of 
  pending connections for the listening socket, sockfd, 
  creates a new connected socket, and returns a new file descriptor 
  referring to that socket.  
  The newly created socket is not in the listening state.  
  The original socket sockfd is unaffected by this call.
*/


//  On success, these system calls return a nonnegative integer 
//  that is a file descriptor for the accepted socket.  
// On error, -1 is returned, errno is set appropriately, 
// and addrlen is left unchanged.


int accept (int sockfd, struct sockaddr *addr, socklen_t *addrlen){

    int __fd = -1;
    
    __fd = (int) gramado_system_call ( 7002, 
                     (unsigned long) sockfd, 
                     (unsigned long) addr, 
                     (unsigned long) addrlen );

    if(__fd<0){
        //printf ("accept: Couldn't accept the connection\n");
        //debug_print ("accept: Couldn't accept the connection\n");
    }

    return (int) __fd;
}


/*
void FD_CLR(int fd, fd_set *set);
void FD_CLR(int fd, fd_set *set)
{}
*/

/*
int  FD_ISSET(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set)
{ return -1; }
*/

/*
void FD_SET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set)
{}
*/

/*
void FD_ZERO(fd_set *set);
void FD_ZERO(fd_set *set)
{}
*/  



/*
select() and pselect() allow a program to monitor multiple file
       descriptors, waiting until one or more of the file descriptors become
       "ready" for some class of I/O operation (e.g., input possible).
*/
//see: sys/select.h
/*
int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);
int select(int nfds, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout)
{ return -1; }
*/  
  
/*       
int pselect(int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, const struct timespec *timeout,
            const sigset_t *sigmask);                       
int pselect(int nfds, fd_set *readfds, fd_set *writefds,
            fd_set *exceptfds, const struct timespec *timeout,
            const sigset_t *sigmask)
{ return -1; }
*/            
            
            
            

//  bind a name to a socket.
// “assigning a name to a socket”.
//  POSIX.1-2001, POSIX.1-2008, SVr4, 
//  4.4BSD (bind() first appeared in 4.2BSD).

// On success, zero is returned.  
// On error, -1 is returned, and errno is set appropriately.

int 
bind ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen )
{
    int __status = -1;

    __status = (int) gramado_system_call ( 7003, 
                     (unsigned long) sockfd, 
                     (unsigned long) addr, 
                     (unsigned long) addrlen );

    if(__status<0)
        printf ("bind: Couldn't bind\n");
     
     
    return (int) __status;
}




/*
 * listen:
 */

// On success, zero is returned.  
// On error, -1 is returned, and errno is set appropriately.     

int listen (int sockfd, int backlog){

    int __status = -1;

    __status = (int) gramado_system_call ( 7004, 
                     (unsigned long) sockfd, 
                     (unsigned long) backlog, 
                     (unsigned long) 0 );

    if(__status<0)
        printf ("connect: Couldn't listen\n");
     

    return (int) __status;
}



/*
 * send:
 */

ssize_t send ( int sockfd, const void *buf, size_t len, int flags ){

    //#todo: Usar esse.
    //return (ssize_t) sendto ( (int) sockfd, 
        //(const void *) buf, (size_t) len, (int) flags,
        //(const struct sockaddr *) dest_addr, (socklen_t) addrlen );


    return (ssize_t) write ( sockfd, (const void *) buf, len );
}


//4.4BSD, SVr4, POSIX.1-2001.  
//These interfaces first appeared in 4.2BSD.
       
ssize_t 
sendto ( 
    int sockfd, 
    const void *buf, 
    size_t len, 
    int flags,
    const struct sockaddr *dest_addr, 
    socklen_t addrlen )
{

    return (ssize_t) write ( sockfd, (const void *) buf, len );
}



ssize_t sendmsg (int sockfd, const struct msghdr *msg, int flags)
{
    debug_print ("sendmsg: [TODO]\n");
    return -1;
}



/*
 * recv:
 */

ssize_t recv ( int sockfd, void *buf, size_t len, int flags ){

    // #todo: Usar esse.
    //return (ssize_t) recvfrom ( (int) sockfd, 
        //(void *) buf, (size_t) len, (int) flags,
        //(struct sockaddr *) src_addr, (socklen_t *) addrlen );

 
   return (ssize_t) read ( sockfd, (const void *) buf, len );
}



ssize_t 
recvfrom ( 
    int sockfd, 
    void *buf, 
    size_t len, 
    int flags,
    struct sockaddr *src_addr, 
    socklen_t *addrlen )
{

     return (ssize_t) read ( sockfd, (const void *) buf, len );
}


ssize_t recvmsg (int sockfd, struct msghdr *msg, int flags)
{
    debug_print ("recvmsg: [TODO]\n");
    return -1;
}



int 
getpeername ( 
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen )
{
    debug_print ("getpeername: [TODO]\n");
    return -1;
}



//POSIX.1-2001, POSIX.1-2008, SVr4, 4.4BSD (getsockname() first
//appeared in 4.2BSD).

int 
getsockname ( 
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen )
{
    int __status = -1;


    __status = (int) gramado_system_call ( 7007, 
                         (unsigned long) sockfd, 
                         (unsigned long) addr, 
                         (unsigned long) addrlen );

    if(__status<0)
        printf ("getsockname: fail\n");
     
     
    return (int) __status;
}


/*
 * shutdown:
 *     shut down part of a full-duplex connection    
 */

// See:
// https://linux.die.net/man/3/shutdown

// how: 
// Muda as flags do arquivo. 
// Alterando permissões de leitura ou escrita.

int shutdown ( int sockfd, int how )
{
    // #todo
    // Deve existir uma rotina na libc que mude
    // as permissões de um arquivo. Então é ela que devemos
    // chamar agora e não uma system call.

    debug_print ("shutdown: [TODO]\n");
    return -1; 
}




//
// End.
//





