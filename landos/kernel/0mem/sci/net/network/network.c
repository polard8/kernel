
// network.c

#include <kernel.h>


// Status do driver de network
// 0 - uninitialized
// 1 - initialized

int network_status;   

// Status para notificações.
// Podemos ou não notificar os processo sobre os eventos de rede.
// O shell vai habilitar essa notificação no momento em que
// envia um stream para mensagens de texto.

int notification_status; 

// Usado por esse módulo.
file *____network_file;




// Colocar um buffer numa lista de buffers.
// Vamos copiar o pacote para alguma fila de buffers.
// A rotina de decodificar o pacote pegará o
// pacote em alguma fila de buffers.
// len: 
//     Tamanho do pacote. Temos que considerar limites.
// buffer:
//     Endereço do pacote.
// Copiamos se o comprimento está no limite.

int network_buffer_in( void *buffer, int len )
{
    void *dst_buffer;
    int tail=0;


    // check args

    if ( (void*) buffer == NULL ){
        panic ("network_buffer_in: buffer\n");
    }

    // #todo
    // Veja na configuração do dispositivo, que o buffer 
    // configurado para o hardware é de 0x3000 bytes.
    if(len>1500){
        debug_print("network_buffer_in: [FIXME] len\n");
        len = 1500;
        //return -1;
    }

    if (NETWORK_BUFFER.initialized != TRUE){
        panic ("network_buffer_in: Shared buffers not initialized\n");
    }

    tail = (int) NETWORK_BUFFER.receive_tail;

    //circula.
    NETWORK_BUFFER.receive_tail++;
    if (NETWORK_BUFFER.receive_tail >= 32){
        NETWORK_BUFFER.receive_tail=0;
    }

	// #todo
	// MTU: maximim transmition unit.
	// For ethernet is 1500 bytes.
	
    //printf ("network_buffer_in: buffer_len %d\n",len);
    //refresh_screen();


    if (tail<0){
        return -1;
    }


    // Pega o destination buffer.
    if (tail<32)
    {
        // Se o buffer está cheio é porque ele não foi consumido.
        // Vamos sobrepor ?
        if ( NETWORK_BUFFER.receive_status[tail] == TRUE )
        {
            // #bugbug
            // #todo: Podemos criar um contador de vezes que isso acontece.
            
            //
            // Isso acontece frequentemente.
            //
            
            // panic ("network_buffer_in: [TEST] Not responding ...\n");
            //printf ("network_buffer_in: [FIXME] Can't write. This buffer is full.\n");
            //refresh_screen();
        }

        dst_buffer = (void*) NETWORK_BUFFER.receive_buffer[tail];
       
        if ((void*)dst_buffer != NULL){
            memcpy( dst_buffer, buffer, len);
        }        
    
        // Avisamos que esse buffer está cheio.
        NETWORK_BUFFER.receive_status[tail] = TRUE;
        
        //printf("network_buffer_in: ok\n");
        //refresh_screen();
        return 0;//ok
    }

    return -1;
}

// #importante
// O kernel vai chamar essa rotina para que ela coloque o conteudo do
// buffer no endereço de buffer indicado no argumento
// o endereço do argumento será o endereço usado pelo controlador na hora do send.
// Retirar um buffer de uma lista de buffers.
// O gns chamará essa rotina e copiará um buffer para ring3, 
// onde chamará as rotinas de protocolo.

int network_buffer_out ( void *buffer, int len )
{
    void *src_buffer;
    int head=0;


    debug_print("network_buffer_out:\n");

    // check args

    if ( (void*) buffer == NULL ){
        panic ("network_buffer_out: [FAIL] buffer\n");
    }

    // #bugbug:
    // Isso pode ser maior se considerarmos todos os headers.
    // #todo
    // Veja na configuração do dispositivo, que o buffer 
    // configurado para o hardware é de 0x3000 bytes.
    if (len>1500){
        debug_print("network_buffer_out: [FIXME] len\n");
        len=1500;
        //return -1;
    }

    if (NETWORK_BUFFER.initialized != TRUE){
        panic ("network_buffer_out: Shared buffers not initialized\n");
    }
    
    // Vamos pegar um numero de buffer para enviarmos o pacote.
    // o kernel vai retirar do head ... 
    // o que foi colocado pelo aplicativo em tail.

    head = (int) NETWORK_BUFFER.send_head;

    // circula.
    NETWORK_BUFFER.send_head++;
    if (NETWORK_BUFFER.send_head >= 8)
        NETWORK_BUFFER.send_head=0;


	// #todo
	// MTU: maximim transmition unit.
	// For ethernet is 1500 bytes.
	
    //printf ("network_buffer_in: buffer_len %d\n",len);
    //refresh_screen();

        
    if(head<0){
        return -1;
    }

    // Pega o destination buffer.
    if (head<8)
    {
        src_buffer = (void*) NETWORK_BUFFER.send_buffer[head];
       
        // Aqui pode estar errado.
        if ((void*)src_buffer != NULL){
            memcpy( buffer, src_buffer, len );
        } 

        //printf("network_buffer_in: ok\n");
        //refresh_screen();
        return 0;//ok
    }

   return -1;
}


void networkSetstatus (int status)
{
    if ( status < 0 || status > 1 )
    {
        return;
    }

    network_status = (int) status;
}


int networkGetStatus (void)
{
    return (int) network_status;
}


/*
 **********************************************************
 * networkInit:
 * 
 * It only initializes some network structures. 
 * Not the adapters.
 * Initialize the buffers used by the NIC adapter.
 * Initialize HostInfo structure.
 * Create a default socket structure for localhost. 
 * CurrentSocket = LocalHostHTTPSocket
 */ 

// Called by init() in init.c.

// #fixme
// Provavelmente esse alocador ainda nao funciona.

int networkInit (void)
{
    debug_print ("networkInit: [TODO] [FIXME]\n");
    
    // #debug
    return 0;

    // =====================================================

    // #importante
    // Essa é a flag que indica que a última inicialização foi feita.
    // Aquela chamada por processos inicializadores em ring3.
    // Com essa flag acionada o handler do nic poderá
    // decodificar o buffer, caso contrário deve ignorar.

    ____network_late_flag=0;



    //
    // buffers:
    // We will create 32 buffers to receive data and
    // 8 buffers to send data.
    //
    
    // 

    void *nbuffer;
    int i=0;

    debug_print ("networkInit: [FIXME] Initializing buffers for the NIC controller.\n");

    // #fixme
    // Provavelmente esse alocador ainda nao funciona.

    NETWORK_BUFFER.initialized = FALSE;

    // =====================================
    // receive buffers

    for (i=0; i<32; i++)
    {
        nbuffer = (void*) newPage();
        
        if ((void *)nbuffer == NULL){
            panic("networkInit: [FAIL] receive nbuffer\n");
        }
        NETWORK_BUFFER.receive_buffer[i] = (unsigned long) nbuffer;
        NETWORK_BUFFER.receive_status[i] = FALSE;  //EMPTY
    };
    NETWORK_BUFFER.receive_tail =0;
    NETWORK_BUFFER.receive_head =0;

    // ========================================
    // send buffers

    for (i=0; i<8; i++)
    {
        nbuffer = (void*) newPage();
        
        if((void *)nbuffer == NULL){
            panic("networkInit: [FAIL] send nbuffer\n");
        }
        NETWORK_BUFFER.send_buffer[i] = (unsigned long) nbuffer;
        NETWORK_BUFFER.send_status[i] = FALSE;  //EMPTY 
    };
    NETWORK_BUFFER.send_tail =0;
    NETWORK_BUFFER.send_head =0;

    // flag.
    NETWORK_BUFFER.initialized = TRUE;

    // =====================================

    // Status.
    networkSetstatus(0);

    // =====================================
    
    // Host info struct. 
    // See: include/rtl/net/host.h
    debug_print ("networkInit: HostInfo \n");

    HostInfo = (struct host_info_d *) kmalloc( sizeof( struct host_info_d ) ); 

    if ( (void *) HostInfo == NULL ){
        panic("networkInit: HostInfo\n");
    }else{

        // #todo object header

        HostInfo->used  = TRUE;
        HostInfo->magic = 1234;

        //
        // hostname
        //

        //HostInfo->__hostname[0] = 'h';
        //HostInfo->hostName_len = (size_t) HOST_NAME_MAX;

        sprintf(HostInfo->__hostname,"gramado");
        HostInfo->hostName_len = (size_t) strlen("gramado");
        if ( HostInfo->hostName_len >= HOST_NAME_MAX )
        {
            panic("networkInit: hostname\n");
        }


        HostInfo->hostVersion = NULL;

        // #todo
        // Call some helpers to get these values.
        // Maybe the init process needs to setup these values.
        // It's because these values are found in files.

        HostInfo->hostVersionMajor    = 0;
        HostInfo->hostVersionMinor    = 0; 
        HostInfo->hostVersionRevision = 0;

        // #todo
        // Where is this information?

        HostInfo->hostArchitecture    = 0; 

        // ...
    };


    //
    // == Socket =============================================
    //

	// Criando socket para local host porta 80;
	// Localhost (127.0.0.1):80 
	// Configurando soquete atual.
	
	debug_print ("networkInit: LocalHostHTTPSocket \n");

    LocalHostHTTPSocket = (struct socket_d *) create_socket_object();  

    if ( (void *) LocalHostHTTPSocket == NULL ){
        panic ("networkInit: Couldn't create LocalHostHTTPSocket\n");
    }else{

        LocalHostHTTPSocket->ip   = 0;
        LocalHostHTTPSocket->port = 0;
        // ...
        
        CurrentSocket = (struct socket_d *) LocalHostHTTPSocket;
    };

	// ...

    // ??
    // What is this?
    
    socket_init();

	// Status
    networkSetstatus(1);

    debug_print ("networkInit: done\n");
    
    return 0;
}



















