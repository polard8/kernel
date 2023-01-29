
ssize_t 
gramsock_send ( 
    int sockfd, 
    const void *buf, 
    size_t len, 
    int flags,
    int mode );
    
    
ssize_t 
gramsock_sendto ( 
    int sockfd, 
    const void *buf, 
    size_t len, 
    int flags,
    const struct sockaddr *dest_addr, 
    socklen_t addrlen, 
    int mode );
    
   
ssize_t 
gramsock_recv ( 
    int sockfd, 
    void *buf, 
    size_t len, 
    int flags,
    int mode );
    
    
ssize_t 
gramsock_recvfrom ( 
    int sockfd, 
    void *buf, 
    size_t len, 
    int flags,
    struct sockaddr *src_addr, 
    socklen_t *addrlen,
    int mode );
    
    
    
    
int gramsock_socket ( int domain, int type, int protocol, int mode );

int 
gramsock_bind ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen,
    int mode );

int gramsock_listen (int sockfd, int backlog, int mode);


int 
gramsock_connect ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen,
    int mode );


int 
gramsock_accept ( 
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen, 
    int mode );
    
 
 
   
    
    
    
    
    
    
    
    
    
    
    
    
    
