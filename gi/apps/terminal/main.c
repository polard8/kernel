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



// Hello!
// Podemos isso na lib.
int terminal_hello_request(int fd);
int terminal_hello_response(int fd);



//message support
int terminal_loop(int fd);
int terminal_getmessage_request(int fd);
int terminal_getmessage_response(int fd);


//constructor.
void terminalTerminal ();
void terminalInitWindowPosition();
void terminalInitWindowSizes();
void terminalInitWindowLimits ();
void terminalInitSystemMetrics ();





// interna
// Isso chama o aplicativo true.bin
// que se conecta a esse via tty e nos envia uma mensagem.
void test_tty_support(int fd)
{
    gws_debug_print("test_tty_support: [FIXME] undefined reference\n");
    return;
    
    /*
    char buffer[32];
    int nread = 0;



    gws_debug_print("test_tty_support:\n");

    int ____this_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );



   // lançando um processo filho.  
   gramado_system_call ( 900, 
       (unsigned long) "true.bin", 0, 0 );


    gws_yield();
    
    
    int i=0;
    while(1){

        nread = read_ttyList ( ____this_tty_id, buffer, 32 ); 
        
        if( nread>0){
            
            for(i=0;i<32;i++){
                if( buffer[i] != 0)
                    terminal_write_char(fd, buffer[i]);
            }
            return;
        }
        gws_yield();
        
        //i++;
        //if(i>20) i=0;
    }
    */
   
    /*
    int nwrite = -1; // bytes escritos.
    size_t __w_size2=0;
    while(1)
    {
        // Escrevendo na tty desse processo e na tty slave pra leitura.
        nwrite = write_ttyList ( ____this_tty_id, 
                     buffer, 
                     __w_size2 = sprintf (buffer,"THIS IS A MAGIC STRING\n")  );
    
        if (nwrite > 0)
           return 0;//goto __ok;
    }
    */
}


void send_again()
{
    fseek(stdin, 0, SEEK_SET); 
    fseek(stdout, 0, SEEK_SET); 
    fseek(stderr, 0, SEEK_SET); 

    //#bugbug
    //Não podemos escrever usando o tamanho do buffer
    //porque o arquivo é menor que isso.
    write(fileno(stdin), prompt, 10);//#bugbug sizeof(prompt));    
    write(fileno(stdout),prompt, 10);//#bugbug sizeof(prompt)); 
    write(fileno(stderr),prompt, 10);//#bugbug sizeof(prompt)); 

    fseek(stdin, 0, SEEK_SET); 
    fseek(stdout, 0, SEEK_SET); 
    fseek(stderr, 0, SEEK_SET); 

}

void test_standard_stream(int fd)
{
    char buffer[4096];
    int nread = 0;
    

    gws_debug_print("test_standard_stream:\n");  


    FILE *f;
    //f = fopen("syscalls.txt", "r+"); 
    f = fopen("gramado.txt", "r+"); 
    //f = fopen("kstderr.txt", "r+");
    //f = fopen("g.txt", "r+");


    // Testar   
    //gramado_system_call ( 900, 
        //(unsigned long) "tprintf.bin", 0, 0 );


   //gramado_system_call ( 900, 
     //  (unsigned long) "tprintf.bin", 0, 0 );

   //gramado_system_call ( 900, 
     //  (unsigned long) "tprintf.bin", 0, 0 );
     
    fseek(f, 0, SEEK_END);   // seek to end of file
    size_t size = ftell(f);  // get current file pointer
    fseek(f, 0, SEEK_SET);   // seek back to beginning of file
    printf (">>>> size %d \n",size);  


      
    fseek(stdin, 0, SEEK_SET); 
    fseek(stdout, 0, SEEK_SET); 
    fseek(stderr, 0, SEEK_SET); 

    //#bugbug
    //Não podemos escrever usando o tamanho do buffer
    //porque o arquivo é menor que isso.
    write(fileno(stdin), prompt, 10);//#bugbug sizeof(prompt));    
    write(fileno(stdout),prompt, 10);//#bugbug sizeof(prompt)); 
    write(fileno(stderr),prompt, 10);//#bugbug sizeof(prompt)); 

    fseek(stdin, 0, SEEK_SET); 
    fseek(stdout, 0, SEEK_SET); 
    fseek(stderr, 0, SEEK_SET); 


    gramado_system_call ( 900, 
      (unsigned long) "tprintf.bin", 0, 0 );

    return;
    while(1);
    


    int i=0;
    while(1){

        //nread = read ( fileno(f), buffer, sizeof(buffer) ); 
        nread = read ( fileno(f), buffer, size ); 
        //nread = read ( fileno(stdin), buffer, size ); 
        //nread = read ( fileno(stdout), buffer, size ); 

        if( nread>0){
            
            for(i=0;i< size ;i++){

                if( buffer[i] == 0){ printf("FIM0\n"); return; }
                
                //eof
                if( buffer[i] == EOF){ printf("FIM1\n"); return; }
                
                if( buffer[i] != 0){
                    //terminal_write_char(fd, buffer[i]);
                    tputc ((int) fd, (int) buffer[i], (int) 1); //com tratamento de escape sequence.
                }
            };
            printf("FIM2\n");
            return;
        }
    };
}


void
test_child_message(void)
{
   // lançando um processo filho.  
   gramado_system_call ( 900, 
       (unsigned long) "sh1.bin", 0, 0 );

}

//
// =======================
//

//int prev;

void terminal_write_char (int fd, int c)
{

    static char prev = 0;

    unsigned long x = (textCurrentCol*8);
    unsigned long y = (textCurrentRow*8);


    // #todo
    // Ver no kernel esse tipo de rotina
    // tab;
    

    if ( c == '\r' ){
        textCurrentCol=0; //TTY[console_number].cursor_x = TTY[console_number].cursor_left;  
        prev = c;
        return;    
    }
    
    //if ( c == '\n' && prev == '\r' ) 
    if ( c == '\n')
    {
         //printf("NEWLINE\n");
         textCurrentCol=0; // começo da linha ...(desnecessário)
         textCurrentRow++;  //linha de baixo
         //começo da linha
         prev = c; 
         return;
    }


    // Refresh!
    // Vamos escrever o char na tela usando o window server.

    // Imprimindo o char na tela usando o window server.
    // Testing draw a char in a window.
    // Isso funciona. Precisamos das rotinas do noraterm
    // pra lidar com caracteres ... o x e o y.
    terminal_drawchar_request (
        (int) fd,             // fd,
        (int) 0,              // window id,
        (unsigned long) x,    // left,
        (unsigned long) y,    // top,
        (unsigned long) COLOR_RED,
        (unsigned long) c );

    terminal_drawchar_response((int) fd);  


    // Coloca no buffer de linhas e colunas.
    terminalInsertNextChar ( (char) c ); 
    
    
    //circula
    textCurrentCol++;
    if (textCurrentCol>__wlMaxColumns)
    {
        textCurrentRow++;    //próxima linha.
        textCurrentCol=0;    //começo da linha
    }
    
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

void terminalInsertNextChar (char c)
{

	// #todo
	// para alguns caracteres temos que efetuar o flush.
	// \n \r ... ??
			
	// Coloca no buffer.

    LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;
}


// # terminal stuff
void terminalInsertNullTerminator ()
{
    terminalInsertNextChar ( (char) '\0' );
}


// # terminal stuff
void terminalInsertLF ()
{
    terminalInsertNextChar ( (char) '\n' );
}

// # terminal stuff
void terminalInsertCR ()
{
    terminalInsertNextChar ( (char) '\r' );
}


// # terminal stuff
//line feed
void lf (void)
{
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
void cr (void)
{
    textCurrentCol = 0;
}


// # terminal stuff
// ??
//voltando uma linha.
void ri (void)
{
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
void del (void)
{
    LINES[textCurrentRow].CHARS[textCurrentCol] = (char) '\0';
    LINES[textCurrentRow].ATTRIBUTES[textCurrentCol] = 7;
}



/*
 ***************** 
 * tputc:
 * 
 */

// #todo
// See: https://github.com/gramado/st/blob/tlvince/st.c

		// #Atenção: A libc do app foi configurada dinamicamente
		// para que printf coloque chars no arquivo. Mas 
		// a libc desse terminal ainda não foi. Então a printf
		// desse terminal escreve no backbuffer e exibe na tela.
        // #bugbug: O problema é que dessa forma nada foi colocado no buffer de arquivo.
        
//#todo
// fazer essa função colocar os chars no buffer de arquivo. Usaremos no scroll.
//void tputc (int fd, char *c, int len){

void 
tputc ( 
    int fd, 
    int c, 
    int len )
{

    unsigned char ascii = (unsigned char) c;
    //unsigned char ascii = *c;


    // Control codes
    int control = ascii < '\x20' || ascii == 0177;
    //bool control = ascii < '\x20' || ascii == 0177;

 
    /*
    if(fd<0){
        printf("tputc: fd\n"); //debug
        return;
    }
    */
     
    //??
    //if(iofd != -1) {}

 
    //
    // #importante
    // Se não é controle é string ou escape sequence.
    //
 
    //string normal
    //if(term.esc & ESC_STR) 
    if (__sequence_status == 0)
    {
        switch (ascii)
        {
            // [Esc]
            // Deixou de ser string normal e entramos em uma sequência.
            // Logo abaixo esse char será tratado novamente.
            case '\033':
                term.esc = ESC_START;
                __sequence_status = 1;
                break;

             // #importante
             // Imprimindo caracteres normais.
             // #todo: talvez possamos usar a API para isso.
             // como acontece nos caracteres digitados no shell interno.
             // #importante
             // Isso vai exibir o caractere mas também
             // na colocar ele no buffer ba posição atual.
             default:
                 terminal_write_char ( fd, (int) ascii); 
                 //printf ("%c",ascii);  //debug
                 return;
         };
    }


    // Control codes. 
    // (dentro de um range)

    if (control){
 
        switch(ascii)
        {
            //case '\v':    /* VT */
            //case '\a':    /* BEL */    
            case '\t':      /* HT */
            case '\b':      /* BS */
            case '\r':      /* CR */
            case '\f':      /* LF */
            case '\n':      /* LF */
                terminal_write_char (fd, (int) ascii);
                //printf ("%c",ascii); //debug
                return;
                break;

            //^[   (Esc)
            //case '\e':
            //case '\033':
            case '\x1b':
                term.esc = ESC_START;
                __sequence_status = 1;
                terminal_write_char ( fd, (int) '$');  //debug
                //printf (" {ESCAPE} ");  //debug
                return;
                break;


            case '\016':    /* SO */
            case '\017':    /* SI */
                return;
                break;


            case '\032':    /* SUB */
            case '\030':    /* CAN */
                //csireset ();
                terminal_write_char ( fd, (int) '$'); //debug
                //printf (" {reset?} "); //debug
                return;
                break;


            case '\005':    /* ENQ (IGNORED) */
            case '\000':    /* NUL (IGNORED) */
            case '\021':    /* XON (IGNORED) */
            case '\023':    /* XOFF (IGNORED) */
            //case 0177:    /* DEL (IGNORED) */
                //Nothing;
                return;

            // ...
        };

        // ... 

    // Um 1b já foi encontrado.
    } else if (term.esc & ESC_START) {

        // Um [ já foi encontrado.
        // #todo parse csi
        if(term.esc & ESC_CSI){

            switch(ascii)
            {
                // Quando acaba a sequência.
                case 'm':
                    term.esc = 0;
                    __sequence_status = 0;
                    terminal_write_char (fd, (int) '$'); //debug
                    //printf (" {m} "); //debug
                    return;
                    break;  

                 // ??
                 //case ';':
                     //return;
                     //break;


                // Vamos apenas colocar no buffer
                // para analizarmos depois.
                // Colocamos no tail e retiramos no head.
                default:
                    terminal_write_char ( fd, (int) '$'); //debug
                    //printf (" {.} "); //debug
                    CSI_BUFFER[__csi_buffer_tail] = ascii;
                    __csi_buffer_tail++;
                    if ( __csi_buffer_tail >= CSI_BUFFER_SIZE )
                    {
                        __csi_buffer_tail = 0;
                    }
                    return;
                    break;
            };


        } else if (term.esc & ESC_STR_END){ 
 
            // ...

        } else if (term.esc & ESC_ALTCHARSET){

            switch(ascii)
            {
                case 'A':  /* UK (IGNORED) */
                case '<':  /* multinational charset (IGNORED) */
                case '5':  /* Finnish (IGNORED) */
                case 'C':  /* Finnish (IGNORED) */
                case 'K':  /* German (IGNORED) */
                    break;
            };


        } else if (term.esc & ESC_TEST) {

            // ...
 
        }else{

            switch (ascii){

            case '[':
                term.esc |= ESC_CSI;
                terminal_write_char ( fd, (int) '$'); //debug
                //printf (" {CSI} "); //debug
                return;
                break; 
   
            case '#':
                 term.esc |= ESC_TEST;
                 break;

            case 'P':  /* DCS -- Device Control String */
            case '_':  /* APC -- Application Program Command */
            case '^':  /* PM -- Privacy Message */
            case ']':  /* OSC -- Operating System Command */
            case 'k':  /* old title set compatibility */
                term.esc |= ESC_STR;
                break; 

            /* Set primary charset G0 */ 
            case '(': 
                term.esc |= ESC_ALTCHARSET;
                break;    

            case ')':  /* set secondary charset G1 (IGNORED) */
            case '*':  /* set tertiary charset G2 (IGNORED) */
            case '+':  /* set quaternary charset G3 (IGNORED) */
                term.esc = 0;
                __sequence_status = 0;
                break;  


            /* IND -- Linefeed */
            case 'D': 
                term.esc = 0;
                terminal_write_char ( fd,(int) '$');  //debug
                //printf (" {IND} ");  //debug
                break;

            /* NEL -- Next line */ 
            case 'E': 
                term.esc = 0;
                terminal_write_char ( fd,(int) '$'); //debug
                //printf (" {NEL} "); //debug
                break;


            /* HTS -- Horizontal tab stop */
            case 'H':   
                term.esc = 0;
                terminal_write_char ( fd,(int) '$'); //debug
                 //printf (" {HTS} "); //debug
                break;


            /* RI -- Reverse index */
            case 'M':     
                term.esc = 0;
                terminal_write_char ( fd,(int) '$'); //debug
                //printf (" {RI} "); //debug
                break;

            /* DECID -- Identify Terminal */
            case 'Z':  
                 term.esc = 0;
                 terminal_write_char (fd, (int) '$'); //debug
                 //printf (" {DECID} "); //debug
                 break;


            /* RIS -- Reset to inital state */
            case 'c': 
                 term.esc = 0;
                 terminal_write_char ( fd,(int) '$'); //debug
                 //printf (" {reset?} "); //debug
                 break; 

            /* DECPAM -- Application keypad */
            case '=': 
                 term.esc = 0;
                 terminal_write_char ( fd,(int) '$'); //debug
                 //printf (" {=} "); //debug
                 break;

            /* DECPNM -- Normal keypad */
            case '>': 
                term.esc = 0;
                terminal_write_char (fd, (int) '$'); //debug
                //printf (" {>} "); //debug
                break;


            /* DECSC -- Save Cursor */ 
            //case '7':     
               //  term.esc = 0;
               //  break;

            /* DECRC -- Restore Cursor */ 
            //case '8': 
               //  term.esc = 0;
               //  break;

            /* ST -- Stop */
            //0x9C ST String Terminator ???
            //case '\\':   
                 //term.esc = 0;
                 //break;
  
            //erro    
            //default:
                //break; 
            };
        };
        
        // ...

        return;
    };
 
    // ...
}





// # terminal stuff
// Insere um caractere sentro do buffer.

char 
terminalGetCharXY ( 
    unsigned long x, 
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
terminalInsertCharXY ( 
    unsigned long x, 
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
static void save_cur (void)
{
    textSavedCol = textCurrentCol;
    textSavedRow = textCurrentRow;
}


// # terminal stuff
static void restore_cur (void)
{
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
        };
		
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

void move_to ( unsigned long x, unsigned long y )
{

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

    register int i=0;

    i = strlen (string);

    if (i >= count){
        string[i++] = ' ';
    }else{

        while (i < count)
            string[i++] = ' ';
    };
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

    //char *c;

    switch (msg){

        // message from child
        //case 7000:
            //gws_debug_print("7000\n"); exit(0);
            //tputc ((int) fd, (int) 'C', (int) 1);
            //gws_reboot();
            //break;

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
                    
                case VK_RETURN:
                    //goto process_event;
                    tputc ((int) fd, (int) '\r', (int) 1);
                    tputc ((int) fd, (int) '\n', (int) 1);
                    input('\n');
                    input('\0');
                    prompt_pos = 0;
                    break;
                  
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
                    //terminal_write_char( (int)fd, (int) long1 );
                    
                    //*c = (char *) long1;
                    
                    input( (unsigned long) long1 );
                    //#test
                    // fd, buf, bufsize
                    tputc ((int) fd, (int) long1, (int) 1);
                     
                     //gws_debug_print("$");
                     
                    /* Tentando mover essa rotina para dentro da função terminal_write_char
                    // Imprimindo o char na tela usando o window server.
                    // Testing draw a char in a window.
                    // Isso funciona. Precisamos das rotinas do noraterm
                    // pra lidar com caracteres ... o x e o y.
                    terminal_drawchar_request (
                        (int) fd,                   // fd,
                        (int) 0,                    // window id,
                        (unsigned long) __tmp_x,    // left,
                        (unsigned long) __tmp_y,    // top,
                        (unsigned long) COLOR_RED,
                        (unsigned long) long1 );

                    terminal_drawchar_response((int) fd);  
                    
                    //#test
                    __tmp_x = __tmp_x + 8;
                    */
                    
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
                case VK_F1:
                    test_tty_support(fd);
                    break;

                // Test standard srteam                
                case VK_F2:
                    test_standard_stream(fd);
                    break;

                case VK_F3:
                    test_child_message();
                    break;


                case VK_F4:
                    send_again();
                    break;
                   
                   
                 //...
                    
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


    char *name = "Terminal";


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

        message_buffer[4] = left; 
        message_buffer[5] = top; 
        message_buffer[6] = width; 
        message_buffer[7] = height; 

        message_buffer[8] = bg_color; //xCOLOR_GRAY2; 

        //type
        message_buffer[9] = WT_SIMPLE;   //ok
        //message_buffer[9] = WT_EDITBOX;  //ok
        //message_buffer[9] = WT_POPUP;
        //message_buffer[9] = WT_CHECKBOX;
        //message_buffer[9] = WT_SCROLLBAR; //fail
        //message_buffer[9] = WT_EDITBOX_MULTIPLE_LINES; //fail
        //message_buffer[9] = WT_BUTTON; //ok
        //message_buffer[9] = WT_STATUSBAR;
        //message_buffer[9] = WT_ICON;
        //message_buffer[9] = WT_SIMPLE;
        
        
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
        gws_yield();



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
    //     gws_yield();        
    //    goto __again;
    //}

    if (n_reads == 0){
         gws_yield();        
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
            gws_yield ();
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

    //porta para o Window Server 'ws' em gramado_ports[]
    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port   = 7547;   
    addr_in.sin_addr.s_addr = IP(192, 168, 1, 112); 


    debug_print ("---------------------------\n");    
    debug_print ("terminal: Initializing ...\n");


    //#test
    Terminal.pid = getpid();
    Terminal.uid = getuid();
    Terminal.gid = getgid();

    //setreuid(-1, -1);
    //setpgrp(0, getpid());


    __sequence_status = 0;

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


    while (1){

        //
        // connect
        // 

        //nessa hora colocamos no accept um fd.
        //então o servidor escreverá em nosso arquivo.
    
        // #debug
        //printf ("gnst: Connecting to the address 'ws' ...\n");  
        printf ("terminal: Connecting to ws via inet  ...\n");  
        
        if (connect (client_fd, (void *) &addr_in, sizeof(addr_in)) < 0){ 
            debug_print ("terminal: connect() Fail \n"); 
            printf("terminal: Connection Failed \n"); 
            //close(client_fd);
            //exit(1);
            //return -1; 
         
             //try again.
         }else{
             break;
         };
    };

 
 
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
    
    //__response_wid = terminal_createwindow_request(client_fd, 100, 100, 480, 320, COLOR_BLACK);
    //terminal_createwindow_response(client_fd); 

     

     //#test
     //Creating a window using the libgws library.
     //Ok. it works.
     __response_wid = gws_create_window_using_socket (client_fd,
                          WT_SIMPLE, 1, 1, "Terminal",
                          100, 100, 480,320,
                          0,0,COLOR_GRAY,COLOR_BLACK);

    // Saving the window id.
    Terminal.window_id = __response_wid;
 

    //
    // Test 3
    //
 
    /*
    __tmp_x = 40;
    __tmp_y = 40;

    // Testing draw a char in a window.
    terminal_drawchar_request (
        (int) client_fd,          //fd,
        (int) __response_wid,     //window_id,
        (unsigned long) __tmp_x,  //left,
        (unsigned long) __tmp_y,  //top,
        (unsigned long) COLOR_RED,
        (unsigned long) 'X' );

    terminal_drawchar_response((int) client_fd);
    */
    
   
    //#debug
    //hanging
    //while(1){}


    //initialize globals.
	//#importante: Isso será definido somente uma vez.
	__wlMaxColumns = DEFAULT_MAX_COLUMNS;
	__wlMaxRows    = DEFAULT_MAX_ROWS;


    //inicializações;
    terminalTerminal();

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
    //gws_clone_and_execute("true.bin");
    
    
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




/*
 ******************************************
 * terminalTerminal:
 *     Constructor.
 *     Não emite mensagens.
 */

// #bugbug
// essas configurações são configurações de janela,
// então estão mais para terminal do que para shell.


void terminalTerminal (){
	
	int i=0;
	int j=0;
	
	// Internas.
	
    //shellStatus = 0;
    //shellError = 0;
	
	//
	// ## Inicializando as estruturas de linha ##
	//
	
	//inicializamos com espaços.
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
	
	
	
	// Deve ser pequena, clara e centralizada.
	// Para ficar mais rápido.
	
	// #importante:
	// O aplicativo tem que confiar nas informações 
	// retornadas pelo sistema.
		
	// Usar o get system metrics para pegar o 
	// tamanho da tela.
	
	//inicializa as metricas do sistema.
	terminalInitSystemMetrics ();
	
    //inicializa os limites da janela.
	terminalInitWindowLimits ();
	
	//inicia o tamanho da janela.
	terminalInitWindowSizes ();
	
	//inicializar a posição da janela.
	terminalInitWindowPosition ();
 
 
    //
	// initialize visible area.
	// #todo: criar função para isso
	// É melhor que seja pequena por enquanto pra não ativar
	// o scroll do kernel e só usar o scroll desse terminal.
	
	//textTopRow = 0;
	//textBottomRow = 24;
    //terminalNewVisibleArea ( 0, 19);


	//...	

	
	// Obs:
	// prompt[] - Aqui ficam as digitações. 

	//terminalClearBuffer ();

	
	//shellBufferMaxColumns = DEFAULT_BUFFER_MAX_COLUMNS;
	//shellBufferMaxRows    = DEFAULT_BUFFER_MAX_ROWS;
	
	//buffersize = (shellBufferMaxColumns * shellBufferMaxRows);
	

	
	//
	// @todo: E o fluxo padrão. Quem configurou os arquivos ???
	//        o kernel configuroru???
	//
	
    //...
	
	
	//for ( i=0; i<WORKINGDIRECTORY_STRING_MAX; i++ ){
	//	current_workingdiretory_string[i] = (char) '\0';
	//};
	
    //sprintf ( current_workingdiretory_string, 
	//    SHELL_UNKNOWNWORKINGDIRECTORY_STRING );    
	
	//...
	
//done:

    //ShellFlag = SHELLFLAG_COMMANDLINE;
	
    //#bugbug
	//Nossa referência é a moldura e não a área de cliente.
	//@todo:usar a área de cliente como referência
	//terminalSetCursor(0,0);
    //terminalSetCursor(0,4);
    
	//@todo
	//tentando posicionar o cursor dentro da janela
	//terminalSetCursor( (shell_info.main_window->left/8) , (shell_info.main_window->top/8));	
	
	//shellPrompt();
}


void terminalInitSystemMetrics (){
	
	
	//Tamanho da tela. (full screen)
	smScreenWidth = gws_get_system_metrics (1);
	smScreenHeight = gws_get_system_metrics (2); 
	
	//cursor
	smCursorWidth = gws_get_system_metrics(3);
	smCursorHeight = gws_get_system_metrics(4);
	
	//mouse
	smMousePointerWidth = gws_get_system_metrics(5);
	smMousePointerHeight = gws_get_system_metrics(6);
	
	//char
	smCharWidth = gws_get_system_metrics(7);
	smCharHeight = gws_get_system_metrics(8);
	
	
	//#todo:
	//vertical scroll size
	//horizontal scroll size.
	
	//#importante
	//#todo: pegar mais.
	
	//...
	
	//#todo: Temos que criar essa variável.
	//InitSystemMetricsStatus = 1;
} 


void terminalInitWindowLimits (){
	
	// #todo
	// Tem variáveis aqui que não podem ser '0'.
	
	//#todo: temos que criar essa variável.
	/*
	if (InitSystemMetricsStatus == 0)
	{
	    terminalInitSystemMetrics ();
	}
	*/
	
    //
    // ## Window limits ##
    //
	
	// problemas; 
	//if ( smScreenWidth == 0 || smScreenHeight )
	//{
	//	 printf ...
	//}

    //full screen support
    wlFullScreenLeft = 0;
    wlFullScreenTop = 0;
    wlFullScreenWidth = smScreenWidth;
    wlFullScreenHeight = smScreenHeight;
	
    //limite de tamanho da janela.
    wlMinWindowWidth = smCharWidth * 80;
    wlMinWindowHeight = smCharWidth * 25;
    wlMaxWindowWidth = wlFullScreenWidth;
    wlMaxWindowHeight = wlFullScreenHeight;	
	
    //quantidade de linhas e colunas na área de cliente.
    wlMinColumns = 80;
    wlMinRows = 1;


	
	//dado em quantidade de linhas.
    textMinWheelDelta = 1;  //mínimo que se pode rolar o texto
    textMaxWheelDelta = 4;  //máximo que se pode rolar o texto	
	textWheelDelta = textMinWheelDelta;
	//...
}


void terminalInitWindowSizes()
{
	
//
//  ## Window size ##
//

    //wsWindowWidth = wlMinWindowWidth;
    //wsWindowHeight = wlMinWindowHeight;	
	
	//Tamanho da janela do shell com base nos limites 
    //que ja foram configurados.	
	
	wsWindowWidth =  WINDOW_WIDTH;
	wsWindowHeight = WINDOW_HEIGHT;
	
	
	if ( wsWindowWidth < wlMinWindowWidth )
	{
		wsWindowWidth = wlMinWindowWidth;
	}
	
	if ( wsWindowHeight < wlMinWindowHeight )
	{
	    wsWindowHeight = wlMinWindowHeight;	
	}
}


void terminalInitWindowPosition()
{
	
	//window position
	wpWindowLeft = WINDOW_LEFT;
	wpWindowTop = WINDOW_TOP;
	
	//wpWindowLeft = (unsigned long) ( (smScreenWidth - wsWindowWidth)/2 );
	//wpWindowTop = (unsigned long) ( (smScreenHeight - wsWindowHeight)/2 );  	
}


//
// End.
//








