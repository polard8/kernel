/*
 * File: socket.c
 *
 */

// See: http://man7.org/linux/man-pages/man2/socket.2.html
// 

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



//gnu
/*
int accept4(int sockfd, struct sockaddr *addr,
           socklen_t *addrlen, int flags);
int accept4(int sockfd, struct sockaddr *addr,
           socklen_t *addrlen, int flags)
{ return -1; }
*/ 



// POSIX.1-2001, POSIX.1-2008, SVr4, 4.4BSD, 
//(connect() first appeared in 4.2BSD).
/*
int connect(int sockfd, const struct sockaddr *addr,
           socklen_t addrlen);
int connect(int sockfd, const struct sockaddr *addr,
           socklen_t addrlen)
{ return -1; }
*/           
           
           
           
/*
The accept() system call is used with connection-based socket types
       (SOCK_STREAM, SOCK_SEQPACKET).  It extracts the first connection
       request on the queue of pending connections for the listening socket,
       sockfd, creates a new connected socket, and returns a new file
       descriptor referring to that socket.  The newly created socket is not
       in the listening state.  The original socket sockfd is unaffected by
       this call.
*/
/*
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{ return -1; }
*/


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
            
            
            
/*
int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);
int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen)
{ return -1; }
*/

/*
 * listen:
 */

int listen (int sockfd, int backlog){

	return -1; //#todo
}


/*
 * recv:
 */

ssize_t recv ( int sockfd,	void *buf, size_t len, int flags )
{
   //falta flags.
   return (ssize_t) read ( sockfd, (const void *) buf, len );
}



/*
 * send:
 */

ssize_t send ( int sockfd, const void *buf, size_t len, int flags )
{
    //falta flags.
    
    return (ssize_t) write ( sockfd, (const void *) buf, len );
}


/*
 * shutdown:
 *     shut down part of a full-duplex connection    
 */

int shutdown ( int	sockfd,	int how ){
	
	return -1; //#todo
}


/*
 *****************************************************
 * socket:
 *     Create an endpoint for communication
 */

// Linux style.
// See: http://man7.org/linux/man-pages/man2/socket.2.html

/*
socket() creates an endpoint for communication and returns a file
       descriptor that refers to that endpoint.  The file descriptor
       returned by a successful call will be the lowest-numbered file
       descriptor not currently open for the process. 
 */

//int socket ( int family, int type, int protocol ){
int socket ( int domain, int type, int protocol )
{
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
//int socket_pipe ( int pipefd[2] );
int socket_pipe ( int pipefd[2] ){

    return (int) gramado_system_call ( 247, (unsigned long) pipefd, 
                     (unsigned long) pipefd, (unsigned long) pipefd );
}



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
        fd = (int) socket_pipe (pipefd);

        if ( fd  == -1 ) 
        {    
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


// POSIX.1-2001, POSIX.1-2008, SVr4, 4.4BSD, 
//(connect() first appeared in 4.2BSD).
// initiate a connection on a socket
           
int 
connect ( int sockfd, 
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
     
     
    //If the connection or binding succeeds, zero is returned.  On error,
    //   -1 is returned, and errno is set appropriately.
          
    return (int) __status;
}


//  bind a name to a socket.
// “assigning a name to a socket”.
//  POSIX.1-2001, POSIX.1-2008, SVr4, 
//  4.4BSD (bind() first appeared in 4.2BSD).
int 
bind ( int sockfd, 
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
     
     
    //On success, zero is returned.  On error, -1 is returned, and errno is
    //   set appropriately.

          
    return (int) __status;
}




//
// End.
//





