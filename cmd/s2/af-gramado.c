

// tentando se conectar usado AF_GRAMADO E 
// as portas gramado_ports[]
int main()
{
    int client_fd;
    
    // cria o soquete.
    // AF_GRAMADO
    client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 )
    {
       printf ("iliinit: Couldn't create socket\n");
    }
    
    struct sockaddr addr;
    addr.sa_family = 8000; //AF_GRAMADO
    addr.sa_data[0] = 'w';
    addr.sa_data[0] = 's';    
    
 
    if (connect (client_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) 
    { 
        printf("iliinit: Connection Failed \n"); 
        return -1; 
    }    
    
    //send(client_fd , hello , strlen(hello) , 0 ); 
    
    return 0;

}
