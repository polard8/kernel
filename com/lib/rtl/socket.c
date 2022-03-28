/*
 * File: socket.c
 *
 */

// See: 
// http://man7.org/linux/man-pages/man2/socket.2.html

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>

#include <stdio.h>
#include <unistd.h>


#include <rtl/gramado.h> 



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

int socket ( int domain, int type, int protocol )
{
    int __fd = -1;

    __fd = (int) gramado_system_call ( 
                     7000, 
                     (unsigned long) domain, 
                     (unsigned long) type, 
                     (unsigned long) protocol );

    if (__fd<0){
        printf ("socket: [FAIL] Couldn't create the socket!\n");
    }

    return (int) __fd;
}


//interna
//int __socket_pipe ( int pipefd[2] );
int __socket_pipe ( int pipefd[2] )
{
    return (int) gramado_system_call ( 
                     247, 
                     (unsigned long) pipefd, 
                     (unsigned long) pipefd, 
                     (unsigned long) pipefd );
}



// socketpair - create a pair of connected sockets
// POSIX.1-2001, POSIX.1-2008, 4.4BSD.  socketpair() first appeared in
// 4.2BSD.  It is generally portable to/from non-BSD systems supporting
// clones of the BSD socket layer (including System V variants).
// #bugbug: Porque o termo pipe é usado ???

int socketpair (int domain, int type, int protocol, int sv[2])
{
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

    if (__status<0){
        printf ("bind: [FAIL] Couldn't bind\n");
    }

    return (int) __status;
}



/*
 * listen:
 */

// On success, zero is returned.  
// On error, -1 is returned, and errno is set appropriately.     

int listen (int sockfd, int backlog)
{

    int __status = -1;

    __status = (int) gramado_system_call ( 7004, 
                     (unsigned long) sockfd, 
                     (unsigned long) backlog, 
                     (unsigned long) 0 );

    if (__status<0){
        printf ("connect: [FAIL] Couldn't listen\n");
    }

    return (int) __status;
}


// #todo
// See: https://linux.die.net/man/2/accept4
int accept4 (int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags)
{
    printf ("accept4: [TODO] Not implemented yet\n");
    return -1;
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

// #test
// Created by Fred Nora.

int accept2 (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int __fd = -1;
    
    __fd = (int) gramado_system_call ( 7010, 
                     (unsigned long) sockfd, 
                     (unsigned long) addr, 
                     (unsigned long) addrlen );

    if(__fd<0){
        //printf ("accept: Couldn't accept the connection\n");
        //debug_print ("accept: Couldn't accept the connection\n");
    }

    return (int) __fd;
}


// accept
// #todo: standard unix-like
// This is the unix standard method.
// Our major goal is to return the fd for the client socket file.
// #bugbug: Work in progress.

int accept (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
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

    if (__status<0){
        printf ("connect: [FAIL] Couldn't connect\n");
    }

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
    //return -1; 

    int __status = -1;


    __status = (int) gramado_system_call ( 7009, 
                         (unsigned long) sockfd, 
                         (unsigned long) how, 
                         (unsigned long) how );

    if (__status<0){
        printf ("shutdown: fail\n");
    }
    
    return (int) __status;
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


/*
 ****************************************
 * send:
 * 
 */

ssize_t 
send ( 
    int sockfd, 
    const void *buf, 
    size_t len, 
    int flags )
{

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

    //if (sockfd<0)
        //return -1;

    return (ssize_t) write ( sockfd, (const void *) buf, len );
}


//#important
//Send a fd to another process. ??? cool
ssize_t sendmsg (int sockfd, const struct msghdr *msg, int flags)
{
    debug_print ("sendmsg: [TODO]\n");
    return -1;
}



/*
 **************************************
 * recv:
 * 
 */

ssize_t 
recv ( 
    int sockfd, 
    void *buf, 
    size_t len, 
    int flags )
{

    //if (sockfd<0)
        //return -1;

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

    //if (sockfd<0)
        //return -1;

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


//POSIX.1-2001, POSIX.1-2008, SVr4, 4.4BSD 
//(getsockname() first appeared in 4.2BSD).

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

    if (__status<0){
        printf ("getsockname: fail\n");
    }

    return (int) __status;
}


//
// ===========
//

int inet_aton (const char *cp, struct in_addr *inp)
{
    debug_print ("inet_aton: [TODO]\n");
    return -1;
}


in_addr_t inet_addr(const char *cp)
{
    printf ("inet_addr: [TODO]\n");
    return (in_addr_t) 0;
}


in_addr_t inet_network(const char *cp)
{
    debug_print ("inet_network: [TODO]\n");
    return (in_addr_t) 0;
}


/*
 * Convert network-format internet address
 * to base 256 d.d.d.d representation.
 */

/*const*/ 

char *inet_ntoa ( struct in_addr in ) 
{
    debug_print ("inet_ntoa: [TODO]\n");
    
    /*
    static char ret[18];

    strlcpy(ret, "[inet_ntoa error]", sizeof(ret));
    (void) inet_ntop(AF_INET, &in, ret, (socklen_t)sizeof ret);

    return ret;
    */

    return (char *) 0;
}


/*
 * Formulate an Internet address from network + host.  Used in
 * building addresses stored in the ifnet structure.
 */
 
struct in_addr inet_makeaddr ( in_addr_t net, in_addr_t host )
{
    
    in_addr_t addr;
    struct in_addr ret;

    printf("inet_makeaddr: [BUGBUG] Not implemented!\n");


	/*
	if (net < 128)
		addr = (net << IN_CLASSA_NSHIFT) | (host & IN_CLASSA_HOST);
	else if (net < 65536)
		addr = (net << IN_CLASSB_NSHIFT) | (host & IN_CLASSB_HOST);
	else if (net < 16777216L)
		addr = (net << IN_CLASSC_NSHIFT) | (host & IN_CLASSC_HOST);
	else
		addr = net | host;
	ret.s_addr = htonl(addr);
	*/

    return ret;
}


/*
 * Return the local network address portion of an
 * internet address; handles class a/b/c network
 * number formats.
 */
in_addr_t
inet_lnaof(struct in_addr in)
{
    printf("inet_lnaof: [BUGBUG] Not implemented!\n");
    return 0;
    
   /*
	in_addr_t i = ntohl(in.s_addr);

	if (IN_CLASSA(i))
		return ((i)&IN_CLASSA_HOST);
	else if (IN_CLASSB(i))
		return ((i)&IN_CLASSB_HOST);
	else
		return ((i)&IN_CLASSC_HOST);

    */
}

/*
 * Return the network number from an internet
 * address; handles class a/b/c network #'s.
 */

in_addr_t inet_netof (struct in_addr in)
{
    printf("inet_netof: [BUGBUG] Not implemented!\n");
    return 0;


   /*
	in_addr_t i = ntohl(in.s_addr);

	if (IN_CLASSA(i))
		return (((i)&IN_CLASSA_NET) >> IN_CLASSA_NSHIFT);
	else if (IN_CLASSB(i))
		return (((i)&IN_CLASSB_NET) >> IN_CLASSB_NSHIFT);
	else
		return (((i)&IN_CLASSC_NET) >> IN_CLASSC_NSHIFT);
   */

}




int getsockopt (int sockfd, int level, int optname, void *optval, socklen_t *optlen)
{ 
    return -1; 
}

int setsockopt (int sockfd, int level, int optname, const void *optval, socklen_t optlen)
{ 
    return -1; 
}

int sendfd(int sockfd, int fd)
{
    if ( sockfd < 0)
        return -1;
 
    return -1; 
}


int recvfd(int sockfd)
{
    if ( sockfd < 0)
        return -1;
        
    return -1; 
}


//
// End.
//





