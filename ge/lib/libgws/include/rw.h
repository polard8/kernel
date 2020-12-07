

// Read and write from socket.






ssize_t __gws_send ( int sockfd, const void *buf, size_t len, int flags );
ssize_t __gws_recv ( int sockfd, void *buf, size_t len, int flags );


ssize_t gws_write_to_server (int fd, const void *buf, size_t count);
ssize_t gws_read_from_server (int fd, const void *buf, size_t count);



