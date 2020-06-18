// libconn
// Biblioteca usada para conecção.
// 2020 - Created by Fred Nora.


#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)


int libconn_connect(int domain);
int libconn_connect_af_gramado(void);
int libconn_connect_af_inet(void);


int libconn_connect_af_gramado(void){

    int client_fd = -1;

    //debug_print ("libconn_connect_af_gramado:\n"); 

    client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       gws_debug_print ("libconn_connect_af_gramado: Couldn't create socket\n");
       printf ("libconn_connect_af_gramado: Couldn't create socket\n");
       exit(1);  //#bugbug Cuidado.
    }

    // Vamos nos concetar com o processo identificado 
    // com o nome 'ws'

    // The port name is 'port:/ws'

    struct sockaddr addr;
    addr.sa_family = 8000; //AF_GRAMADO
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';  
    

    //
    // connect
    // 

    //nessa hora colocamos no accept um fd.
    //então o servidor escreverá em nosso arquivo.
    
    // #debug
    printf ("libconn_connect_af_gramado: Connecting to the address 'ws' ...\n");      

    // Tentando nos conectar ao endereço indicado na estrutura
    // Como o domínio é AF_GRAMADO, então o endereço é "w","s".
    if ( connect (client_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0 )
    { 
        gws_debug_print ("libconn_connect_af_gramado: Connection Failed\n");
        printf ("libconn_connect_af_gramado: Connection Failed \n"); 
        return -1; 
    } 


    return (int) client_fd;
}





int libconn_connect_af_inet(void){

    int client_fd = -1;
 
    //debug_print ("libconn_connect_af_inet:\n"); 
 
 
     client_fd = socket ( AF_INET, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       printf ("libconn_connect_af_inet: Couldn't create socket\n");
       exit(1);
    }


    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port   = 7548;   //porta para o Network Server 'ns' em gramado_ports[]
    addr_in.sin_addr.s_addr = IP(192, 168, 1, 79); 

    printf ("libconn_connect_af_inet: Connecting to the address via inet  ...\n");      
    if (connect (client_fd, (void *) &addr_in, sizeof(addr_in)) < 0){ 
        printf("libconn_connect_af_inet: Connection Failed \n"); 
        return -1; 
    } 

    return (int) client_fd;     
}



int libconn_connect (int domain){

    int fd = -1;

    switch (domain){
    case AF_GRAMADO:
        return (int) libconn_connect_af_gramado();
        break;
    case AF_INET:
        return (int) libconn_connect_af_inet();
        break;
    default:
        return -1;
        break;
    };


    return -1;
}


//
// End.
//



