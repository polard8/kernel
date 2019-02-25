
// socket.h
// suporte a socket da klibc.


int socket ( int family, int type, int protocol );

// Essa rotina sera' chamada se os serviços forem superios a 7000 ou inferiores a 8000
unsigned long socket_services ( unsigned long number, unsigned long arg2, unsigned long arg3, unsigned long arg4 );







