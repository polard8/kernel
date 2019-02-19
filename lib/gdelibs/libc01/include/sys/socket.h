
#include <stddef.h>

//socket.h 

//shutdown	- shut down part of a full-duplex connection
//POSIX.1-2001, 
//4.4BSD (the shutdown() function call  first  appeared  in 4.2BSD).
int shutdown ( int	sockfd,	int how );


//send
//4.4BSD, SVr4, POSIX.1-2001.  These function calls appeared in 4.2BSD.
//POSIX.1-2001   describes	  only	 the   MSG_OOB	 and   MSG_EOR	flags.
//POSIX.1-2008 adds a specification  of  MSG_NOSIGNAL.   The  MSG_CONFIRM
//flag is a Linux extension.
// comments credits: freebsd.org	 
ssize_t send ( int sockfd, const void *buf, size_t len, int flags );



// listen -	listen for connections on a socket
// 4.4BSD,	POSIX.1-2001.	
// The  listen()  function	call first appeared in 4.2BSD.
int listen(int sockfd, int backlog);



// socket
//socket -	create an endpoint for communication
//4.4BSD, POSIX.1-2001.
//The SOCK_NONBLOCK and SOCK_CLOEXEC flags	are Linux-specific.
//socket()	 appeared in 4.2BSD.  It is generally portable to/from non-BSD
//systems supporting clones of the	BSD socket layer (including  System  V
//variants).
// comments credits: freebsd.org	 
int socket ( int domain, int type, int protocol );


//recv - receive a message from	a socket

ssize_t recv ( int sockfd,	void *buf, size_t len, int flags );






