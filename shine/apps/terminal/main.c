/*
 * File: main.c
 *
 *    Client side application for Gramado Network Server.
 *    Using socket to connect with gns.
 *    AF_GRAMADO family.
 * 
 * 
 *       O propósito é testar o servidor gns.
 *
 * 2020 - Created by Fred Nora.
 */
 
// Connecting via AF_INET.

// tutorial example taken from. 
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
 
/*
    To make a process a TCP server, you need to follow the steps given below −

    Create a socket with the socket() system call.

    Bind the socket to an address using the bind() system call. 
    For a server socket on the Internet, an address consists of a 
    port number on the host machine.

    Listen for connections with the listen() system call.

    Accept a connection with the accept() system call. 
    This call typically blocks until a client connects with the server.

    Send and receive data using the read() and write() system calls.
*/ 

// See:
// https://wiki.osdev.org/Message_Passing_Tutorial
// https://wiki.osdev.org/Synchronization_Primitives
// https://devblogs.microsoft.com/commandline/
// /windows-command-line-introducing-the-windows-pseudo-console-conpty/
// ...



#include "noraterm.h"


// #test
// Tentando deixar o buffer aqui e aproveitar em mais funções.
char __buffer[512];

#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)

// tipos de pacotes.
//#define SERVER_PACKET_TYPE_REQUEST    1000 
//#define SERVER_PACKET_TYPE_REPLY      1001 
//#define SERVER_PACKET_TYPE_EVENT      1002
//#define SERVER_PACKET_TYPE_ERROR      1003



void gnst_yield(void);


// Hello!
// Podemos isso na lib.
int terminal_hello_request(int fd);
int terminal_hello_response(int fd);



//message support
int terminal_loop(int fd);
int terminal_getmessage_request(int fd);
int terminal_getmessage_response(int fd);






//
// =======================
//


void terminal_write_char (int c)
{
    //coloca no buffer de linhas e colunas.
    terminalInsertNextChar ( (char) c ); 
    
    // Refresh!
    // Vamos escrever o char na tela usando o window server.
    
}

/*
 ***************************************************
 * terminalInsertNextChar:
 *     Coloca um char na próxima posição do buffer.
 *     Memória de vídeo virtual, semelhante a vga.
 *     #todo: Esse buffer poderia ser um arquivo que o kernel
 * pudesse usar, ou o servidor de recursos gráficos pudesse usar.
 */

	//#importante:
	//o refresh é chamado no default do procedimento de janela

void terminalInsertNextChar (char c){
	
	// #todo
	// para alguns caracteres temos que efetuar o flush.
	// \n \r ... ??
			
	// Coloca no buffer.
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;
}


// # terminal stuff
void terminalInsertNullTerminator (){
	
	terminalInsertNextChar ( (char) '\0' );
}


// # terminal stuff
void terminalInsertLF (){
	
	terminalInsertNextChar ( (char) '\n' );
}

// # terminal stuff
void terminalInsertCR (){
    
	terminalInsertNextChar ( (char) '\r' );
}


// # terminal stuff
//line feed
void lf (void){
	
	//enquanto for menor que o limite de linhas, avança.
	if ( textCurrentRow+1 < __wlMaxRows )
	{
		textCurrentRow++; 
		return;
	}
	
	//#todo: Scroll up;
	//scrup();
}




// # terminal stuff
//carriege return
void cr (void){
	
    textCurrentCol = 0;
}


// # terminal stuff
// ??
//voltando uma linha.
void ri (void){
	
	//if ( screen_buffer_y > top ){
		
		// Volta uma linha.
	//	screen_buffer_y--;
	//	screen_buffer_pos = (screen_buffer_pos - columns); 
	//	return;
	//}
	
	//@todo:
	//scrdown();
}


// # terminal stuff
void del (void){
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) '\0';
	LINES[textCurrentRow].ATTRIBUTES[textCurrentCol] = 7;
}


// # terminal stuff
// Insere um caractere sentro do buffer.

char 
terminalGetCharXY ( unsigned long x, 
                    unsigned long y )
{	
	if ( x >= __wlMaxColumns || y >= __wlMaxRows )
	{	
		return;
	}

	return (char) LINES[y].CHARS[x];
}


// # terminal stuff
// Insere um caractere sentro do buffer.

void 
terminalInsertCharXY ( unsigned long x, 
                       unsigned long y, 
                       char c )
{
	if ( x >= __wlMaxColumns || y >= __wlMaxRows )
	{	
		return;
	}

	LINES[y].CHARS[x] = (char) c;
	LINES[y].ATTRIBUTES[x] = 7;
}






// # terminal stuff
static void save_cur (void){
	
	textSavedCol = textCurrentCol;
	textSavedRow = textCurrentRow;
}


// # terminal stuff
static void restore_cur (void){
	
	textCurrentCol = textSavedCol;
	textCurrentRow = textSavedRow;
}


/*
 ****************************************
 * shellClearBuffer:
 *     Limpa o buffer da tela.
 *     Inicializamos com espaços.
 */

void terminalClearBuffer (){

    int i=0;
    int j=0;

    for ( i=0; i<32; i++ )
    {
		for ( j=0; j<80; j++ )
		{
		    LINES[i].CHARS[j] = (char) ' ';
		    LINES[i].ATTRIBUTES[j] = (char) 7;
	    }
		
		LINES[i].left = 0;
		LINES[i].right = 0;
		LINES[i].pos = 0;
    };
}



//Qual será a linha que estará no topo da janela.
void textSetTopRow ( int number )
{
    textTopRow = (int) number; 	
}


int textGetTopRow ()
{
    return (int) textTopRow; 	
}


//Qual será a linha que estará na parte de baixo da janela.
void textSetBottomRow ( int number )
{
    textBottomRow = (int) number; 	
}


int textGetBottomRow ()
{
    return (int) textBottomRow; 	
}

void textSetCurrentRow ( int number )
{
    textCurrentRow = (int) number; 	
}


int textGetCurrentRow ()
{
    return (int) textCurrentRow; 	
}



void textSetCurrentCol ( int number )
{
    textCurrentCol = (int) number; 	
}


int textGetCurrentCol ()
{
    return (int) textCurrentCol; 	
}



/*
 * move_to:
 *    Move o cursor de posição.
 *    Assim o próximo char será em outro lugar da janela.
 */

void move_to ( unsigned long x, unsigned long y ){
	
	if ( x > __wlMaxColumns || y > __wlMaxRows )
		return;
	
	//screen_buffer_x = x;
	//screen_buffer_y = y;
	
	textCurrentCol = x;
	textCurrentRow = y;
	
	//screen_buffer_pos = ( screen_buffer_y * __wlMaxColumns + screen_buffer_x ) ;
}


/* credits: bsd*/
/* Pad STRING to COUNT characters by inserting blanks. */

int pad_to (int count, char *string){
	
    register int i;

    i = strlen (string);

    if (i >= count)
        string[i++] = ' ';
    else
    {
        while (i < count)
            string[i++] = ' ';
    }
    string[i] = '\0';

    return (i);
}






//
// =======================
//





int terminal_getmessage_request(int fd)
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.



    //char *name = "Window name 1";

   

    //
    // Send request.
    //


    // #debug
    gws_debug_print ("terminal: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 369;    //get message request  //1001;    // msg. Create window.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
 
        //message_buffer[4] = left; //120;   //x
        //message_buffer[5] = top; //120;   //y
        //message_buffer[6] = width; //480;   //w
        //message_buffer[7] = height; //320;   //h
        
        //message_buffer[8] = bg_color; //xCOLOR_GRAY2; 

         
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send (fd, __buffer, sizeof(__buffer), 0);
       
        if(n_writes>0)
           break;
    }


    return 0; 
}

int terminal_getmessage_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_reads = 0;    // For receiving responses.

    //
    // Waiting for response. ==================
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    // gws_debug_print ("terminal: Waiting ...\n");      

    
    // #bugbug
    // Talvez não precisamos disso, vamos testar sem isso.
    // Tem um yield logo abaixo no write().
    
    //int y;
    //for(y=0; y<15; y++)
    //    gws_yield();   // See: libgws/


    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.


    //
    // read
    //

    // #debug
    gws_debug_print ("terminal: reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, __buffer, sizeof(__buffer), 0 );
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
        gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("terminal: recv fail.\n");
        printf ("terminal: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }

    //
    // The msg index.
    //
    
    // Get the message sended by the server.

    int window          = (int) message_buffer[0];
    int msg             = (int) message_buffer[1];
    unsigned long long1 = (unsigned long) message_buffer[2];
    unsigned long long2 = (unsigned long) message_buffer[3];
    
    //#debug
    //if(msg!=0)
        //printf ("%c",long1); //printf ("{%d%c} ",msg,long1);
        
        
        
    switch (msg){

        //OK isso funcionou.
        case MSG_KEYDOWN:
          //case 20:
            //gws_debug_print ("MSG_KEYDOWN\n");
            
            // #importante:
            // Temos um input
            // Vamos colocar ele nos buffers de linha
            // e imprimirmos na tela usando o window server.
            
            switch (long1)
            {
                //case 0:
                    //relax cpu
                    //break; 
                    
                //case VK_RETURN:
                    //goto process_event;
                    //break;
                  
                //case VK_TAB:
                //case VK_BACK:
                
                //...
                
                
                // We are in the terminal ...
                // We will not process the chars ...
                // We need to send it to the client via file.
                default:
                    //terminal_write_char(long1) #todo
                    
                    //isso funciona
                    //printf ("%c",long1);
                    //fflush(stdout);
                    
                    // Colocando no buffer de linha
                    terminal_write_char((int)long1);
    
                    // Imprimindo o char na tela usando o window server.
                    // Testing draw a char in a window.
                    // Isso funciona. Precisamos das rotinas do noraterm
                    // pra lidar com caracteres ... o x e o y.
                    terminal_drawchar_request (
                        (int) fd,//fd,
                        (int) 0, //__response_wid, //window_id,
                        (unsigned long) __tmp_x,//left,
                        (unsigned long) __tmp_y,//top,
                        (unsigned long) COLOR_RED,
                        (unsigned long) long1 );

                    terminal_drawchar_response((int) fd);                    
                    
                    //#test
                    __tmp_x = __tmp_x + 8;
                    
                    goto process_event;
                    break;
            };
            break;


        //case MSG_KEYUP:
          case 21:  
            //gws_debug_print ("MSG_KEYUP\n");
            goto process_event;
            break;
            
            
        case MSG_SYSKEYDOWN:
            switch (long1)
            {
                //case VK_F1:
                default:
                    goto process_event;
                    break;
            };
            break;
            

        case MSG_SYSKEYUP:
            switch (long1)
            {
                //case VK_F1:
                default:
                    goto process_event;
                    break;
            };
            break;

        // Commands.
        case MSG_COMMAND:
            switch (long1)
            {
                //case CMD_ABOUT:
                    //printf ("terminal: CMD_ABOUT\n");
                    //goto process_event;
                    //break;
                    
                default:
                    goto process_event;
                    break;
            };

        
		//case MSG_TERMINALCOMMAND:
			//switch (long1)
			//{
			// CMD_XXX ??
		    //};


        case SERVER_PACKET_TYPE_REQUEST:
            gws_yield ();
            goto response_loop;
            break;
            
        // Reply!
        case SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            goto process_event;
            //goto response_loop;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            gws_debug_print ("terminal: SERVER_PACKET_TYPE_ERROR\n");
            goto response_loop;
            //exit (-1);
            break;
        
        default:
            gws_debug_print ("@");
            goto process_event;
            //goto response_loop;
            break; 
    };





//
// Process reply.
//

// A resposta tras o window id no início do buffer.
    
process_reply:

    // #test
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    return 0;

//
// Process an event.
//

process_event:
    gws_debug_print ("terminal: We got an event\n"); 
    return 0;
}


//loop
int terminal_loop(int fd)
{
	//while(___running){
    while(1){
        terminal_getmessage_request(fd);
        terminal_getmessage_response(fd);
    }
    return 0; 
}


int 
terminal_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color );
    
int terminal_createwindow_response(int fd);



int 
terminal_drawchar_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    unsigned long c );
    
int terminal_drawchar_response(int fd);

//...



//
// =====================================================
//

int 
terminal_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.



    char *name = "Window name 1";

   

    //
    // Send request.
    //


    // #debug
    gws_debug_print ("terminal: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1001;    // msg. Create window.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = left; //120;   //x
        message_buffer[5] = top; //120;   //y
        message_buffer[6] = width; //480;   //w
        message_buffer[7] = height; //320;   //h
        
        message_buffer[8] = bg_color; //xCOLOR_GRAY2; 

         
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send (fd, __buffer, sizeof(__buffer), 0);
       
        if(n_writes>0)
           break;
    }


    return 0; 
}

//response
//#todo: the response needs to be unsigned long or void *.
int terminal_createwindow_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_reads = 0;    // For receiving responses.

    //
    // Waiting for response. ==================
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    gws_debug_print ("terminal: Waiting ...\n");      

    int y;
    for(y=0; y<15; y++)
        gws_yield();   // See: libgws/


    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.


    //
    // read
    //

    // #debug
    gws_debug_print ("terminal: reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, __buffer, sizeof(__buffer), 0 );
    
    //if (n_reads<=0){
    //     gws_yield(); 
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
         gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("terminal: recv fail.\n");
        printf ("terminal: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }


    //
    // The msg index.
    //
    
    // Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        case SERVER_PACKET_TYPE_REQUEST:
            gws_yield ();
            goto response_loop;
            break;
            
        // Reply!
        case SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            goto process_event;
            //goto response_loop;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            gws_debug_print ("terminal: SERVER_PACKET_TYPE_ERROR\n");
            goto response_loop;
            //exit (-1);
            break;
        
        default:
            goto response_loop;
            break; 
    };





//
// Process reply.
//

// A resposta tras o window id no início do buffer.
    
process_reply:

    // #test
    gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    return (int) message_buffer[0];
    //return 0;

//
// Process an event.
//

process_event:
    gws_debug_print ("terminal: We got an event\n"); 
    return 0;

}



int 
terminal_drawchar_request (
    int fd,
    int window_id,
    unsigned long left,
    unsigned long top,
    unsigned long color,
    unsigned long c )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.



    //char *name = "Window name 1";

   

    //
    // Send request.
    //


    // #debug
    gws_debug_print ("terminal: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1004;    // Draw char.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = window_id;
        message_buffer[5] = left; 
        message_buffer[6] = top; 
        message_buffer[7] = color; 
        
        message_buffer[8] = c;   // The 'char'.

         
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send (fd, __buffer, sizeof(__buffer), 0);
       
        if(n_writes>0)
           break;
    }


    return 0; 
}



//response
int terminal_drawchar_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_reads = 0;    // For receiving responses.

    //
    // Waiting for response. ==================
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    gws_debug_print ("terminal: Waiting ...\n");      

    int y;
    for(y=0; y<15; y++)
        gws_yield();   // See: libgws/


    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.


    //
    // read
    //

    // #debug
    gws_debug_print ("terminal: reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, __buffer, sizeof(__buffer), 0 );
    
    //if (n_reads<=0){
    //     gws_yield(); 
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
         gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("terminal: recv fail.\n");
        printf ("terminal: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }


    //
    // The msg index.
    //
    
    // Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        case SERVER_PACKET_TYPE_REQUEST:
            gws_yield ();
            goto response_loop;
            break;
            
        // Reply!
        case SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            goto process_event;
            //goto response_loop;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            gws_debug_print ("terminal: SERVER_PACKET_TYPE_ERROR\n");
            goto response_loop;
            //exit (-1);
            break;
        
        default:
            goto response_loop;
            break; 
    };





//
// Process reply.
//

// A resposta tras o window id no início do buffer.
    
process_reply:

    // #test
    //gws_debug_print ("terminal: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("terminal: bye\n"); 
    //printf ("terminal: Window ID %d \n", message_buffer[0] );
    //printf ("terminal: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    //return 0;
    return (int) message_buffer[0];

//
// Process an event.
//

process_event:
    gws_debug_print ("terminal: We got an event\n"); 
    return 0;
}



/*
// gerar número aleatório dentro de uma faixa.
int gerar_numero(int lim_inf, int lim_sup)
{
    return (lim_inf + (rand() % lim_sup));
}
*/




void gnst_yield(void){
	
    gramado_system_call (265,0,0,0); //yield thread.
}




//char *hello = "Hello there!\n";
/*
#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/




int terminal_hello_response(int fd){

    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_reads = 0;    // For receiving responses.


    //
    // waiting
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    debug_print ("terminal: Waiting ...\n");      


    int y;
    for(y=0; y<15; y++)
        gnst_yield();



    //
    // read
    //

    // #debug
    debug_print ("terminal: Reading ...\n");      


       //#caution
       //we can stay here for ever.
       //it's a test yet.
__again:
    n_reads = read ( fd, __buffer, sizeof(__buffer) );
    
    // Não vamos insistir num arquivo vazio.
    //if (n_reads<=0){
    //     gnst_yield();        
    //    goto __again;
    //}

    if (n_reads == 0){
         gnst_yield();        
        goto __again;
    }
    
    if (n_reads < 0){
        printf ("terminal: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }
    

    
    // Get the message sended by the server.
    int msg = (int) message_buffer[1];
    
    switch (msg)
    {
        case SERVER_PACKET_TYPE_REQUEST:
            gnst_yield ();
            goto __again;
            break;
            
        case SERVER_PACKET_TYPE_REPLY:
            debug_print ("terminal: SERVER_PACKET_TYPE_REPLY received\n"); 
            goto process_reply;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            //todo: call procedure.
            goto __again;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            debug_print ("terminal: SERVER_PACKET_TYPE_ERROR\n");
            goto __again;
            //exit (-1);
            break;
        
        default:
            goto __again;
            break; 
    };


process_reply:

    //
    // done:
    //

    //printf("%d bytes readed\n",n_reads);
    printf("RESPONSE: {%s} \n",__buffer+16);

    return 0;
}


int terminal_hello_request(int fd){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.

     //
     // Loop for new message.
     //

    unsigned long ____color = 0x00FF00;

// loop:
new_message:

    
    //
    // Write
    //

    // #debug
    debug_print ("terminal: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??


    // Write!
    // Se foi possível enviar, então saimos do loop.        
    // obs: podemos usar send();

    while (1){

        // solicita um hello!      
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1000;    // msg=hello.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        // ...

        n_writes = write (fd, __buffer, sizeof(__buffer));
        if(n_writes>0)
           break;
    }

    return 0;
}


//interna
int __terminal_clone_and_execute ( char *name )
{
    return (int) gramado_system_call ( 900, (unsigned long) name, 0, 0 );
}



void _draw(int fd, int c)
{

   unsigned long x;
   //x=0x65666768; //last
   

    //printf ("%c",c);
    //fflush(stdout);
    //return;
   

                    terminal_drawchar_request (
                        (int) fd,//fd,
                        (int) 0, //__response_wid, //window_id,
                        (unsigned long) __tmp_x,//left,
                        (unsigned long) __tmp_y,//top,
                        (unsigned long) COLOR_RED,
                        (unsigned long) x );  
                        
                 __tmp_x = __tmp_x + 8;
                 
                 //if ( __tmp_x > (8*80) )
                 //{
                 //    __tmp_y = __tmp_y + 8;
                 //    __tmp_x = 0;
                 //}
                 
                terminal_drawchar_response((int) fd);
}



//
// Main
//

int main ( int argc, char *argv[] ){

    int client_fd = -1;


    debug_print ("---------------------------\n");    
    debug_print ("terminal: Initializing ...\n");


    //#test
    Terminal.pid = getpid();
    Terminal.uid = getuid();
    Terminal.gid = getgid();

    //setreuid(-1, -1);
    //setpgrp(0, getpid());


    //
    // socket
    // 

    // #debug
    printf ("terminal: Creating socket\n");

    // cria o soquete.
    // AF_GRAMADO
    //client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       debug_print ("terminal: Couldn't create socket\n");
       printf ("terminal: Couldn't create socket\n");
       exit(1);
    }
    
    // Saving the fd in the main struct.
    Terminal.client_fd = client_fd;
    //...

    //porta para o Window Server 'ws' em gramado_ports[]
    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port   = 7547;   
    addr_in.sin_addr.s_addr = IP(192, 168, 1, 112); 


    //
    // connect
    // 


    //nessa hora colocamos no accept um fd.
    //então o servidor escreverá em nosso arquivo.
    
    // #debug
    //printf ("gnst: Connecting to the address 'ws' ...\n");      
    
    printf ("terminal: Connecting to the address via inet  ...\n");      
    if (connect (client_fd, (void *) &addr_in, sizeof(addr_in)) < 0){ 
        debug_print ("terminal: connect() Fail \n"); 
        printf("terminal: Connection Failed \n"); 
        return -1; 
    } 
 
 
    //
    // messages
    //
   
    // #test
    // Testing loop; ok.
    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.


    //
    // Test 1
    //
   
    // Testing hello message
    terminal_hello_request(client_fd);
    terminal_hello_response(client_fd);


    //
    // Test 2
    //


    //Creating the main window
    int __response_wid = 0;
    __response_wid = terminal_createwindow_request(client_fd, 100, 100, 480, 320, COLOR_BLACK);
    terminal_createwindow_response(client_fd); 

    // Saving the window id.
    Terminal.window_id = __response_wid;
    // ...
    

    //
    // Test 3
    //
 

    __tmp_x = 40;
    __tmp_y = 40;


    //testing draw a char in a window.
    terminal_drawchar_request (
        (int) client_fd,//fd,
        (int) __response_wid, //window_id,
        (unsigned long) __tmp_x,//left,
        (unsigned long) __tmp_y,//top,
        (unsigned long) COLOR_RED,
        (unsigned long) 'X' );

    terminal_drawchar_response((int) client_fd);
    
    //#debug
    //hanging
    //while(1){}


    //
    // Loop!
    //


    // loop
    // This the loop that gets messages from the window server;
    terminal_loop(client_fd);
    
    debug_print ("terminal: bye\n"); 
    printf ("terminal: bye\n");
    return 0;






    //
    // ============== test start =======================
    //
   
     
    // #tet
    // Let's try another loop;
    // Let's call the shell and get input from the stdout.
    
    //
    // Calling child
    //
    
    //Precisamos de um loop aqui pra chamar o shell sempre que ele fechar.
    __terminal_clone_and_execute ("true.bin"); 
    
    // talvez precisamos esperar ...


     // #bugbug
     // Nesse teste o arquivo é aberto duas vezes ...
     //não é o mesmo arquivo, é uma instância.

    
     
     FILE *fp; 
     fp = fopen ("gramado.txt", "w+" );
     if(!fp){
         printf("cant open\n");
         return 1;
     }
     

    int c=0;
    while(1)
    {
        //testing stdin
        fseek(fp, 0, SEEK_SET);   // seek back to beginning of file
        //fprintf(fp,"terminal: Testing string ...\n");

        // arquivo que o filho vai herdar.
        c = fgetc(fp); 
         
        //if( c == EOF) break;
        
        if( c != EOF)
        {
            //_draw(client_fd,c); //#bugbug
 
           printf ("%c",c);
           fflush(stdout);
        }
        //printf ("[EOF]\n");
    }
    //
    // ============== test end =======================
    //



    //done

    debug_print ("terminal: bye\n"); 
    printf ("terminal: bye\n");


    return 0;
}

//
// End.
//








