/*
 * File: main.c
 *     Simple virtual terminal.
 *     2021 - Created by Fred Nora.
 */

// #test
// For now it has a small embedded command line interpreter.

// The POSIX terminal interface.
// Raw or Canonical?
// See:
// https://www.gnu.org/software/libc/manual/html_node/Canonical-or-Not.html
// https://en.wikipedia.org/wiki/POSIX_terminal_interface
// https://en.wikipedia.org/wiki/Computer_terminal
// ...

// Connecting via AF_INET.

// tutorial example taken from. 
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
 
/*
    To make a process a TCP server, 
    you need to follow the steps given below −
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

//#include <ctype.h>

// #todo:
// We need to change the name of this document??
#include "noraterm.h"

// #test:
// Testing ioctl()
#include <termios.h>

// network ports.
#define PORTS_WS 4040
#define PORTS_NS 4041
#define PORTS_FS 4042
// ...

#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)


FILE *__terminal_input_fp;

// color
static unsigned int bg_color = COLOR_BLACK;
static unsigned int fg_color = COLOR_WHITE;
static unsigned int prompt_color = COLOR_GREEN;

// cursor
static int cursor_x = 0;
static int cursor_y = 0;

// Embedded shell
// We are using the embedded shell.
static int isUsingEmbeddedShell=TRUE;

// Windows:
static int main_window=0;
static int terminal_window=0;


//
// prototypes
//

static void terminalTerminal (void);
static void terminalInitWindowPosition(void);
static void terminalInitWindowSizes(void);
static void terminalInitWindowLimits (void);
static void terminalInitSystemMetrics (void);

static void compareStrings(int fd);
static void doPrompt(int fd);

static void clear_terminal_client_window(int fd);
static void __send_to_child (void);
static void __test_winfo(int fd, int wid);

//====================================================


// Clear
// Redraw the client window.
// Setup the cursor position.
static void clear_terminal_client_window(int fd)
{
    if (fd<0){return;}

     gws_redraw_window(
         fd,
         Terminal.client_window_id,
         TRUE );

    cursor_x = Terminal.left;
    cursor_y = Terminal.top;
}


// local
// maximize application window.
// #bugbug: Covering the taskbar.
void __winmax(int fd)
{
    int test_win = Terminal.main_window_id;

    unsigned long w=rtl_get_system_metrics(1);
    unsigned long h=rtl_get_system_metrics(2);
                  h=h-40;

    if(fd<0)
        return;

    gws_change_window_position(fd,test_win,0,0);

// resize
    gws_resize_window(
        fd, test_win, w, h );

    gws_redraw_window(
         fd, test_win, TRUE );
}

// local
// maximize application window.
// #bugbug: Covering the taskbar.
void __winmin(int fd)
{
    int test_win = Terminal.main_window_id;

    unsigned long w=rtl_get_system_metrics(1);
    unsigned long h=rtl_get_system_metrics(2);
                  h=h-40;

    if(fd<0)
        return;

    gws_change_window_position(fd,test_win,0,0);

// resize

    unsigned long w_width=0;
    unsigned long w_height=0;

    if(w>100){w_width=100;}
    if(h>100){w_height=100;}

    gws_resize_window(
        fd, test_win, w_width, w_height );

// redraw
    gws_redraw_window(
         fd, test_win, TRUE );
}


// local
void __desktop(int fd)
{
    int test_win = Terminal.main_window_id;

//#test 1
    gws_async_command(fd,11,0,0);  //update desktop

/*
//#test 2
    int i=0;
    for (i=0; i<8; i++){
        gws_change_window_position (fd,test_win,i,i);
        gws_redraw_window (fd, test_win, TRUE );
    };
*/
}



// local
// command "window"
void __test_gws(int fd)
{

    // test window
    int test_win = Terminal.main_window_id;
    //int test_win = Terminal.client_window_id;

    if(fd<0)
        return;

    gws_change_window_position(fd,test_win,0,0);
    gws_resize_window(
        fd, test_win, 400, 400);

    //gws_refresh_window(fd,test_win); //#bugbug

    //text
    //gws_draw_text(fd,test_win,0,0,COLOR_RED,"This is a string");

//redraw and refresh.
    gws_redraw_window(
         fd, test_win, TRUE );
//redraw and not refresh.
    //gws_redraw_window(
         //fd, test_win, FALSE );


    //text
    //gws_draw_text(fd,test_win,0,0,COLOR_RED,"This is a string");

// update desktop
    //gws_async_command(fd,11,0,0); //update desktop
}


static void __test_winfo(int fd, int wid)
{

    struct gws_window_info_d *wi;
    //unsigned long _l,_t,_w,_h;

    if(fd<0)
        return;
    if(wid<0)
        return;


    wi = (void*) malloc( sizeof( struct gws_window_info_d ) );

    if( (void*) wi == NULL )
        return;


    //IN: fd, wid, window info structure.
    gws_get_window_info(
        fd, 
        wid,
        (struct gws_window_info_d *) wi );

    if(wi->used != TRUE)
        return;

    if(wi->magic!=1234)
        return;


//
// Debug
//

// window: l,t,w,h
    printf("terminal: (window) l=%d t=%d w=%d h=%d\n",
        wi->left, wi->top, wi->width, wi->height );

// client rectangle: l,t,w,h
    printf("terminal: (client rectangle) l=%d t=%d w=%d h=%d\n",
        wi->cr_left, wi->cr_top, wi->cr_width, wi->cr_height );

    printf("terminal: done\n");
}

/*
static void __test_rand(void);
static void __test_rand(void)
{
   int i, n;
   time_t t;
  
   n = 5;
   
   //printf ("M=%d\n",rtl_get_system_metrics(118) ); //jiffies
    
   //Intializes random number generator
   //srand((unsigned) time(&t));

   //Print 5 random numbers from 0 to 49 
   for( i = 0 ; i < n ; i++ ) {
      printf("%d\n", rand() % 50);
   }
   
   return(0);
}
*/


// Compare the string typed into the terminal.
// Remember, we have an embedded command interpreter.
static void compareStrings(int fd)
{
    if(fd<0){
        return;
    }

    // #libc
    // Testing libc components.
    if( strncmp(prompt,"libc",4) == 0 )
    {
        //close(0); 
        //close(1); 
        //close(2);
        //#remember: stderr was redirected to stdout.
        //fclose(stdin); 
        //fclose(stdout); 
        //fclose(stderr); 
        
        //creat ( "NEWFILE.TXT", 0666 );
        //mkdir ( "NEWDIR", 0666 );
        
        goto exit_cmp; 
    }

    // get window info: main window
    if ( strncmp(prompt,"w-main",6) == 0 )
    {
        // IN: fd, wid
        __test_winfo( 
            fd,
            main_window );  // app window
        goto exit_cmp;
    }

    // get window info: terminal window
    if ( strncmp(prompt,"w-terminal",10) == 0 )
    {
        // IN: fd, wid
        __test_winfo( 
            fd,
            terminal_window );  // Terminal.client_window_id
        goto exit_cmp;
    }





    if ( strncmp(prompt,"tputstring",10) == 0 )
    {
        __test_escapesequence(fd);
        goto exit_cmp;
    }
    
    if ( strncmp(prompt,"tputc",5) == 0 )
    {
        //It works.
        tputc(fd, Terminal.client_window_id, 'x', 1);
        goto exit_cmp;
    }

    // Quit 'ws'.
    if ( strncmp(prompt,"ws-quit",7) == 0 )
    {
        //gws_async_command(fd,88,0,0);  //ok
        goto exit_cmp;
    }

    // Reboot via 'ws'
    if ( strncmp(prompt,"ws-reboot",9) == 0 )
    {
        gws_async_command(fd,89,0,0);
        goto exit_cmp;
    }

    //testing ioctl
    if( strncmp(prompt,"ioctl",5) == 0 )
    {
        printf ("~ioctl: tests ...\n");

        // flush
        //ioctl ( STDIN_FILENO,  TCIFLUSH, 0 ); // input
        //ioctl ( STDOUT_FILENO, TCIFLUSH, 0 ); // console
        //ioctl ( STDERR_FILENO, TCIFLUSH, 0 ); // regular file
        //ioctl ( 4,             TCIFLUSH, 0 ); // invalid?
        
        // invalid limits
        //ioctl ( -1, -1, 0 );
        //ioctl ( 33, -1, 0 );

        // 1 = Virtual Console.
        // Changing the color.
        // ok: it is working
        //ioctl(1, 1000,COLOR_CYAN);
        //ioctl(1, 1001, 10);  //change x
        //ioctl(1, 1002, 10);  //change y
        //ioctl(1, 1003,  2);  //switch to the virtual console 2. 
        
        printf ("done\n");
        goto exit_cmp;
    }

    if ( strncmp(prompt,"winmax",6) == 0 )
    {
        __winmax(fd);
        goto exit_cmp;
    }

    if ( strncmp(prompt,"winmin",6) == 0 )
    {
        __winmin(fd);
        goto exit_cmp;
    }

    //#test: testando serviços diversos.
    if ( strncmp(prompt,"window",6) == 0 )
    {
        __test_gws(fd);
        goto exit_cmp;
    }

    //#test: update all the windows in the desktop.
    if ( strncmp(prompt,"desktop",7) == 0 )
    {
        __desktop(fd);
        //gws_async_command(fd,12,0,0); //switch focus.
        //gws_async_command(fd,11,0,0); //update desktop
        goto exit_cmp;
    }


// =============
// 'help'
    if ( strncmp(prompt,"help",4) == 0 )
    {
        cursor_y++;

        cursor_x=0;   
        gws_draw_char ( 
            fd, 
            Terminal.client_window_id, 
            (cursor_x*8), 
            (cursor_y*8), 
            fg_color, 
            '\\' ); 

        cursor_x=1;
        gws_draw_char ( 
            fd, 
            Terminal.client_window_id, 
            (cursor_x*8), 
            (cursor_y*8), 
            fg_color, 
            'o' ); 

        cursor_x=2;
        gws_draw_char ( 
            fd, 
            Terminal.client_window_id, 
            (cursor_x*8), 
            (cursor_y*8), 
            fg_color, 
            '/' ); 

        goto exit_cmp;
    }

// =============
// 'reboot'
    if ( strncmp(prompt,"reboot",6) == 0 ){
        rtl_reboot();
        goto exit_cmp;
    }

// =============
// 'cls'
    if ( strncmp(prompt,"cls",3) == 0 ){
        clear_terminal_client_window(fd);
        goto exit_cmp;
    }


// =============
// 't1'
    if ( strncmp(prompt,"t1",2) == 0 )
    {
        
        // pixel: ok
        //gws_plot0(fd, 20, 20, 0, COLOR_RED );
        //gws_plot0(fd, 30, 30, 0, COLOR_GREEN );
        //gws_plot0(fd, 40, 40, 0, COLOR_BLUE );

        // char: #testing
        //gws_draw_char ( 
        //    fd, 
        //    Terminal.client_window_id, 
        //    (cursor_x*8), 
        //    (cursor_y*8), 
        //    fg_color, 
        //    '/' ); 
        
        // #bugbug
        // Esta travando.
        // #fixed: Essa chamada esta funcionando agora.
        //gws_async_command(fd,2,0,0);    // PING
        //gws_async_command(fd,5,0,0);  //rectangle ring3
        //gws_async_command(fd,10,0,0); //ramdom tests
        //gws_async_command(fd,6,0,0);  // show fps bar.

        //demos: IN: fd,service,demo_index,0.
        //gws_async_command(fd,4,1,0); // points (works, but sometimes it fails)
        //gws_async_command(fd,4,5,0);  //cube1 (ok)
        //gws_async_command(fd,4,6,0);  //cube2 (ok)
        //gws_async_command(fd,4,7,0);  //curve (ok)
        //gws_async_command(fd,4,9,0);  //cat   (ok)
        //gws_async_command(fd,4,10,0);  // triangle (ok)
        gws_async_command(fd,4,11,0); //mesh1 (ok)
        //gws_async_command(fd,4,14,0);  //polygon (ok)
        //gws_async_command(fd,4,15,0);  //polygon2 (ok)
        
        // #bugbug
        // Não podemos pegar esse falor corretamente.
        //printf ("M=%d\n",rtl_get_system_metrics(118) ); //jiffies
        //printf ("M=%d\n",rtl_get_system_metrics(120) ); // variável de time
        //printf ("M=%d\n",rtl_get_system_metrics(1) );
        //printf ("M=%d\n",rtl_get_system_metrics(2) );
        goto exit_cmp;
    }


//
// Not a reserved word.
//


// Empty buffer
   if( *prompt == 0 ){
       goto exit_cmp;
   }

// Clone.
// #important:
// For now the system will crash if the
// command is not found.
// #bugbug
// We are using the whole 'command line' as an argument.
// We need to work on that routine of passing
// the arguments to the child process.
// See: rtl.c
// Stop using the embedded shell.

// rebubina o arquivo de input.
    //rewind(__terminal_input_fp);
    
// ==================================

//
// Send command line via stdin
//


// Write it into stdin.
// It's working
// See: crt0.c
    rewind(stdin);
    prompt[511]=0;
    write(fileno(stdin), prompt, 512);
    //write(
    //    fileno(stdin), 
    //    "Data", 
    //    4 );

    //fail
    //fprintf(stdin,"One Two Three ...");
    //fflush(stdin);


/*
// it's working
    char *shared_buffer = (char *) 0x30E00000;  //extra heap 3.
    sprintf(shared_buffer,"One Two Three ...");
    shared_buffer[511] = 0;
*/

// ==================================


//
// Get filename
//


// #bugbug
// The command line accepts only one word
// and the command line has too many words.
 
//#todo
//Create a method.
//int rtl_get_first_word_in_a_string(char *buffer_pointer, char *string);
 
    char filename_buffer[12]; //8+3+1
    char *p;
    p=prompt;
    int ii=0;
    while(1)
    {
        if(ii>=12){
            filename_buffer[ii] = 0;  //finalize
            break;
        }
        if( *p == 0 || 
            *p == ' ' ||
            *p == '\t' )
        {
            filename_buffer[ii] = 0;  //finalize
            break;
        }
        
        // printable.
        // Put the char into the buffer.
        if( *p >= 0x20 && *p <= 0x7F )
        {
            filename_buffer[ii] = (char) *p;
        }
        p++;    // next char in the command line.
        ii++;   // next byte into the filename buffer.
    };

    //rtl_clone_and_execute(prompt);
    rtl_clone_and_execute(filename_buffer);

    // #todo #test
    // This is a method for the whole routine above.
    // rtl_execute_cmdline(prompt);

    isUsingEmbeddedShell = FALSE;
    return;

    //printf("Command not found\n");

exit_cmp:
    doPrompt(fd);
}


static void doPrompt(int fd)
{
    int i=0;

    if(fd<0){
        return;
    }

// Clean prompt buffer and setup it again.

    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){ prompt[i] = (char) '\0'; };

    prompt[0] = (char) '\0';
    prompt_pos    = 0;
    prompt_status = 0;
    prompt_max    = PROMPT_MAX_DEFAULT;  

// Escrevia no console.
    // Prompt
    //printf("\n");
    //printf("cmdline: Type something\n");
    //printf("$ ");
    //fflush(stdout);

// Cursor do terminal.
    cursor_x = 0;
    cursor_y++;


// Refresh client window.

    int wid=Terminal.client_window_id;
    if(wid < 0){
        return;
    }

// draw prompt symbol.
    gws_draw_char ( 
        fd, 
        wid, 
        (cursor_x*8), 
        (cursor_y*8), 
        prompt_color, 
        '>' ); 

// Increment x.
    cursor_x++;

// #bugbug
// Refreshing the whole window is too much.
// Refresh only the rectangle of the size of a char or line.
// #todo: Call gws_refresh_retangle(...) (Not implemented yet)

    // it works.
    gws_refresh_retangle(
        fd,
        (cursor_x*8),(cursor_y*8),8,8);

    // it works
    //gws_refresh_window(fd,wid);
}


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


// f4
// Send the content of prompt[] to stdin.
// The child process will read this.
// This is why the stdin needs to be a tty.
// (Canonical) 
// If the child is a shell it will read a line.
// (Raw) 
// If the child is a text editor it will read a single char.
// Maybe the shell can change stdin for it's child.
// For now, the shell will need a line.

static void __send_to_child (void)
{
    char *shared_flag   = (char *) (0xC0800000 -0x210);   // flag
    char *shared_memory = (char *) (0xC0800000 -0x200);   // input
    //char *shared_memory = (char *) (0xC0800000 -0x100); // output
   
   
    // There is a '\n' terminated line in prompt[].
    // #bugbug: Não podemos mandar uma linha sem '\n'.
    fseek(stdin, 0, SEEK_SET); 
    write ( fileno(stdin), prompt, 80);
    

    //copy to shared memory
    //send a system message.(maybe)
    //flag?


    int i=0;
    // Send the command line to the shared memory.
    for(i=0; i<80; i++){ shared_memory[i] = prompt[i]; }
    // Clear prompt.
    for(i=0; i<80; i++){ prompt[i]=0; }
    prompt_pos = 0; 
    
    // Notify the child that it has a message in the shared memory.
    shared_flag[0] = 1; 
}



// Write something in the standard stream and call shell.bin.
void test_standard_stream(int fd)
{
    char buffer[4096];  //#bugbug: 4KB
    int nread = 0;

    gws_debug_print("test_standard_stream:\n");  

    //FILE *f;
    //f = fopen("syscalls.txt", "r+"); 
    //f = fopen("gramado.txt", "r+"); 
    //f = fopen("kstderr.txt", "r+");
    //f = fopen("g.txt", "r+");

    // Testar   
    //gramado_system_call ( 900, 
        //(unsigned long) "tprintf.bin", 0, 0 );

   //gramado_system_call ( 900, 
     //  (unsigned long) "tprintf.bin", 0, 0 );

   //gramado_system_call ( 900, 
     //  (unsigned long) "tprintf.bin", 0, 0 );
     
    //fseek(f, 0, SEEK_END);   // seek to end of file
    //size_t size = ftell(f);  // get current file pointer
    //fseek(f, 0, SEEK_SET);   // seek back to beginning of file
    //printf (">>>> size %d \n",size);  

    fseek(stdin, 0, SEEK_SET); 
    fseek(stdout, 0, SEEK_SET); 
    fseek(stderr, 0, SEEK_SET); 

    input('\n');
    input('\0');
    //input(-1);

    //#bugbug
    //Não podemos escrever usando o tamanho do buffer
    //porque o arquivo é menor que isso.
    write(fileno(stdin), prompt, 20);//#bugbug sizeof(prompt));    
    write(fileno(stdout),prompt, 20);//#bugbug sizeof(prompt)); 
    write(fileno(stderr),prompt, 20);//#bugbug sizeof(prompt)); 

    //fseek(stdin, 0, SEEK_SET); 
    //fseek(stdout, 0, SEEK_SET); 
    //fseek(stderr, 0, SEEK_SET); 

    int ii=0;
    prompt_pos = 0;
    for(ii=0;ii<32;ii++) {prompt[ii]=0;}

    //gramado_system_call ( 900, 
      //(unsigned long) "tprintf.bin", 0, 0 );

    gramado_system_call ( 900, 
      (unsigned long) "shell.bin", 0, 0 );

    return;
    //while(1);
    

    /*

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
                    tputc ((int) fd, window, (int) buffer[i], (int) 1); //com tratamento de escape sequence.
                }
            };
            printf("FIM2\n");
            return;
        }
    };
    */
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

void 
terminal_write_char (
    int fd, 
    int window, 
    int c )
{
    static char prev=0;
    unsigned long x = (cursor_x*8);
    unsigned long y = (cursor_y*8);

    if (fd<0)    {return;}
    if (window<0){return;}
    if (c<0)     {return;}

// #todo
// Ver no kernel esse tipo de rotina
// tab;

    if ( c == '\r' )
    {
        cursor_x=0;
        prev = c;
        return;
    }

    //if ( c == '\n' && prev == '\r' ) 
    if ( c == '\n')
    {
         //printf("NEWLINE\n");
         cursor_x=0; // começo da linha ...(desnecessário)
         cursor_y++;  //linha de baixo
         //começo da linha
         prev = c; 
         return;
    }

// Draw!
// Draw the char into the given window.
// Vamos pintar o char na janela usando o window server.
// White on black
// IN: fd, wid, l, t, color, ch.

    gws_draw_char (
        (int) fd,
        (int) window,
        (unsigned long) (x & 0xFFFF),
        (unsigned long) (y & 0xFFFF),
        (unsigned long) fg_color,
        (unsigned long) c );

// Coloca no buffer de linhas e colunas.
    terminalInsertNextChar ( (char) c ); 

// Circula
// próxima linha.
// começo da linha
    cursor_x++;
    
    //if (cursor_x > __wlMaxColumns)
    if(cursor_x >= Terminal.width_in_chars)
    {
        cursor_y++;
        cursor_x=0;
    }
}


/*
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

    LINES[cursor_y].CHARS[cursor_x] = (char) c;
}


// # terminal stuff
void terminalInsertNullTerminator (void)
{
    terminalInsertNextChar ( (char) '\0' );
}


// # terminal stuff
void terminalInsertLF (void)
{
    terminalInsertNextChar ( (char) '\n' );
}

// # terminal stuff
void terminalInsertCR (void)
{
    terminalInsertNextChar ( (char) '\r' );
}


// # terminal stuff
//line feed
void lf (void)
{
    // Enquanto for menor que o limite de linhas, avança.

    if ( cursor_y+1 < __wlMaxRows )
    {
        cursor_y++; 
        return;
    }

	//#todo: Scroll up;
	//scrup();
}




// # terminal stuff
//carriege return
void cr (void)
{
    cursor_x = 0;
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
    //if(cursor_x<0){cursor_x=0;}
    //if(cursor_y<0){cursor_y=0;}
    
    LINES[cursor_y].CHARS[cursor_x] = (char) '\0';
    LINES[cursor_y].ATTRIBUTES[cursor_x] = 7;
}


void __test_escapesequence(int fd)
{
    tputstring(fd, "Testing scape sequence:\n");
    //tputstring(fd, "One: \033[m");          //uma sequencia.
    //tputstring(fd, "Two: \033[m \033[m");   //duas sequencias.
    tputstring(fd, "~Before \033[m ~Inside \033[m ~ After"); 
    //tputstring(fd, "\033[1Am"); //ok
    //tputstring(fd, "\033[2Am X");  // cursor move up.
    tputstring(fd, "\033[4Bm cursor down!\n");  // cursor move down.
    
    //tputstring(fd, "\033[sm");     // save cursor position
    //tputstring(fd, "\033[um");     // restore cursor position
    
    // apagar N bytes na mesma linha.
    //tputstring(fd, "Before --|\033[0Km|-- After \n");  
    tputstring(fd, "Before --|\033[1Km|-- After \n");  
    tputstring(fd, "Before --|\033[2Km|-- After \n");  
    tputstring(fd, "Before --|\033[3Km|-- After \n");  
    tputstring(fd, "Before --|\033[4Km|-- After \n");  
    //tputstring(fd, "Before --|\033[5Km|-- After \n");  
    //tputstring(fd, "Before --|\033[6Km|-- After \n");  
    //tputstring(fd, "Before --|\033[7Km|-- After \n");  
    //tputstring(fd, "Before --|\033[8Km|-- After \n");  

    //move cursor right
    tputstring(fd, "\033[8Cm Fred\n");
    //move cursor left
    tputstring(fd, "\033[8Dm Fred\n");

    tputstring(fd, "done :)\n");
}


void tputstring( int fd, char *s )
{
    size_t StringSize=0;
    register int i=0;
    char *b = (char *) s;

    if( (void*) s == NULL )
        return;
    if( *s == 0 )
        return;

    StringSize = (size_t) strlen(s);
    if(StringSize<=0)
        return;
    // Limits: #test
    if(StringSize>=32)
        return;


// Initialize escape sequence steps.
    __sequence_status=0;

    for(i=0; i<StringSize; i++){
        tputc(fd, Terminal.client_window_id, b[i], 1);
    }
}


/*
 * tputc:
 *     Draw a char into the client window.
 */

// #todo
// See-github: tlvince/st.c

// #Atenção: 
// A libc do app foi configurada dinamicamente
// para que printf coloque chars no arquivo. Mas 
// a libc desse terminal ainda não foi. Então a printf
// desse terminal escreve no backbuffer e exibe na tela.
// #bugbug: 
// O problema é que dessa forma nada foi colocado no buffer de arquivo.
// #todo
// fazer essa função colocar os chars no buffer de arquivo. 
// Usaremos no scroll.

/*
Black       0;30     Dark Gray     1;30  
Blue        0;34     Light Blue    1;34  
Green       0;32     Light Green   1;32  
Cyan        0;36     Light Cyan    1;36  
Red         0;31     Light Red     1;31  
Purple      0;35     Light Purple  1;35  
Brown       0;33     Yellow        1;33  
Light Gray  0;37     White         1;37   
*/

/*
Position the Cursor:
puts the cursor at line L and column C.
\033[<L>;<C>H 
Or
\033[<L>;<C>f
Move the cursor up N lines:          \033[<N>A
Move the cursor down N lines:        \033[<N>B
Move the cursor forward N columns:   \033[<N>C
Move the cursor backward N columns:  \033[<N>D
Clear the screen, move to (0,0):     \033[2J
Erase to end of line:     \033[K
Save cursor position:     \033[s
Restore cursor position:  \033[u
*/

/*
ESC [ 4 A             move cursor 4 lines up (4 can be any number)
ESC [ 5 B             move cursor 5 lines down
ESC [ 2 K             erase current line 
ESC [ 30;46 m         set black text (30) on cyan background (46)
ESC [ 0 m             reset color and attributes
*/

/*
DEC	HEX	CHARACTER
0	0	NULL
1	1	START OF HEADING (SOH)
2	2	START OF TEXT (STX)
3	3	END OF TEXT (ETX)
4	4	END OF TRANSMISSION (EOT)
5	5	END OF QUERY (ENQ)
6	6	ACKNOWLEDGE (ACK)
7	7	BEEP (BEL)
8	8	BACKSPACE (BS)
9	9	HORIZONTAL TAB (HT)
10	A	LINE FEED (LF)
11	B	VERTICAL TAB (VT)
12	C	FF (FORM FEED)
13	D	CR (CARRIAGE RETURN)
14	E	SO (SHIFT OUT)
15	F	SI (SHIFT IN)
16	10	DATA LINK ESCAPE (DLE)
17	11	DEVICE CONTROL 1 (DC1)
18	12	DEVICE CONTROL 2 (DC2)
19	13	DEVICE CONTROL 3 (DC3)
20	14	DEVICE CONTROL 4 (DC4)
21	15	NEGATIVE ACKNOWLEDGEMENT (NAK)
22	16	SYNCHRONIZE (SYN)
23	17	END OF TRANSMISSION BLOCK (ETB)
24	18	CANCEL (CAN)
25	19	END OF MEDIUM (EM)
26	1A	SUBSTITUTE (SUB)
27	1B	ESCAPE (ESC)
28	1C	FILE SEPARATOR (FS) RIGHT ARROW
29	1D	GROUP SEPARATOR (GS) LEFT ARROW
30	1E	RECORD SEPARATOR (RS) UP ARROW
31	1F	UNIT SEPARATOR (US) DOWN ARROW
*/


// See: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

// void tputc (int fd, char *c, int len){
void 
tputc ( 
    int fd, 
    int window,
    int c, 
    int len )
{
    int ivalue=0;
    unsigned char ascii = (unsigned char) c;
    //unsigned char ascii = *c;

// Control codes?
    //int control = (ascii < '\x20' || ascii == 0177);
    int is_control=FALSE;
    if ( ascii < '\x20' || ascii == 0177 )
    {
        is_control = TRUE;
    }


// Invalid socket
    if(fd<0)
        return;

// Invalid target window.
    if(window<0)
        return;

// Invalid char len.
// #bugbug: Isso nem precisa.
     //if(len!=1)
         //len=1;

    //??
    //if(iofd != -1) {}

 
    //
    // #importante
    // Se não é controle é string ou escape sequence.
    //

/*
    //string normal
    //if(term.esc & ESC_STR) 
    if (__sequence_status == 0)
    {
        switch (ascii){
        
        // [Esc]
        // Deixou de ser string normal e entramos em uma sequência.
        // Logo abaixo esse char será tratado novamente.
        case '\033':
            printf("FOUND {033}. Start of sequence\n");
            term.esc = ESC_START;
            __sequence_status = 1;
            break;

        // #importante
        // Imprimindo caracteres normais.
        // #todo: talvez possamos usar a API para isso.
        // como acontece nos caracteres digitados no shell interno.
        // #importante
        // Isso vai exibir o caractere mas também
        // na colocar ele no buffer da posição atual.
        default:
            //printf ("%c",ascii);  //debug
                 
            // It's not a control code.
            if(is_control==FALSE){
                terminal_write_char ( fd, window, (int) ascii ); 
            }
            return;
        };
    }
*/


//==============================
// Se uma sequencia foi finalizada, ou nunca foi inicializada.

    if (__sequence_status == 0)
    {
        // Vamos imprimir quando
        // uma sequencia nao esta inicializada e
        // temos um char que nao eh controle.
        if(is_control==FALSE){
            terminal_write_char ( fd, window, (int) ascii ); 
            return;
        }
    }




// ===========================
// Se o char eh um control code.
// Control codes. 
// (dentro de um range)

    if (is_control==TRUE){

        switch (ascii)
        {
            //case '\v':    /* VT */
            //case '\a':    /* BEL */    
            case '\t':      /* HT */
            case '\b':      /* BS */
            case '\r':      /* CR */
            case '\f':      /* LF */
            case '\n':      /* LF */
                terminal_write_char (fd, window, (int) ascii);
                //printf ("%c",ascii); //debug
                return;
                break;

            //^[   (Esc)
            //case '\e':
            //case '\033':
            case '\x1b':
                //printf("FOUND {033}. Start of sequence\n");
                __sequence_status = 1;
                term.esc = ESC_START;
                //terminal_write_char ( fd, window, (int) '$');  //debug
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
                //terminal_write_char ( fd, window, (int) '$'); //debug
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

// ===========================
// Se encontramos um char logo apos encontrarmos um \033.
// Um 1b já foi encontrado.
// Um \033 foi encontrado.

    } else if (term.esc & ESC_START){

        // Um [ já foi encontrado.
        // Vamos analisar a sequencia depois de '['
        // A sequencia vai terminar com um 'm'
        // #todo parse csi
        if(term.esc & ESC_CSI){

            switch (ascii)
            {
                // Quando acaba a sequência.
                //'\033[0m'       #Reset text
                case 'm':
                    //printf("FOUND {m}. End of sequence\n");
                    __sequence_status = 0;   // essa sequencia terminou.
                    // agora o buffer esta vazio.
                    // #todo: usarloop para de fato esvaziar o buffer.
                    __csi_buffer_tail = 0;
                    term.esc = 0;  //??
                    //terminal_write_char (fd, window, (int) '$'); //debug
                    //printf (" {m} "); //debug
                    return;
                    break;

                 //save cursor position
                 case 's':
                     //printf("FOUND {Save cursor position}\n");
                     save_cur();
                     return;
                     break;

                 //restore cursor position
                 case 'u':
                     //printf("FOUND {Restore cursor position}\n");
                     restore_cur();
                     return;
                     break;

                 //move cursor N lines up (N can be any number)
                 //N is inside the buffer
                 case 'A':
                     //printf("FOUND {A}\n");
                     ivalue = (int) CSI_BUFFER[0];
                     ivalue = (int) (ivalue & 0xFF); //only the first byte.
                     ivalue = atoi(&ivalue); 
                     //printf("ivalue {%d}\n",ivalue);
                     cursor_y = (cursor_y - ivalue);
                     if(cursor_y<0){ cursor_y=0; }
                     return;
                     break;
                 
                 //move cursor N lines down
                 //N is inside the buffer
                 case 'B':
                     //printf("FOUND {B}\n");
                     ivalue = (int) CSI_BUFFER[0];
                     ivalue = (int) (ivalue & 0xFF); //only the first byte.
                     ivalue = atoi(&ivalue); 
                     //printf("ivalue {%d}\n",ivalue);
                     cursor_y = (cursor_y + ivalue);
                     if(cursor_y>24){ cursor_y=24; }
                     return;
                     break;

                 // cursor right
                 case 'C':
                     //printf("FOUND {C}\n");
                     ivalue = (int) CSI_BUFFER[0];
                     ivalue = (int) (ivalue & 0xFF); //only the first byte.
                     ivalue = atoi(&ivalue); 
                     //printf("ivalue {%d}\n",ivalue);
                     cursor_x = (cursor_x + ivalue);
                     if(cursor_x>=80){ cursor_x=79; }
                     return;
                     break;

                 //cursor left
                 case 'D':
                     //printf("FOUND {D}\n");
                     ivalue = (int) CSI_BUFFER[0];
                     ivalue = (int) (ivalue & 0xFF); //only the first byte.
                     ivalue = atoi(&ivalue); 
                     //printf("ivalue {%d}\n",ivalue);
                     cursor_x = (cursor_x - ivalue);
                     if(cursor_x<0){ cursor_x=0; }
                     return;
                     break;


                 // 2K   erase 2 bytes in the current line 
                 case 'K':
                     //printf("FOUND {K}\n");
                     ivalue = (int) CSI_BUFFER[0];
                     ivalue = (int) (ivalue & 0xFF); //only the first byte.
                     ivalue = atoi(&ivalue); 
                     //printf("ivalue {%d}\n",ivalue);
                     if( (cursor_x+ivalue)<80)
                     {
                         while(ivalue>0){
                             terminal_write_char (fd, window, (int) ' ');
                             ivalue--;
                         }
                     }
                     return;

                     break;

                 // Estilo de texto.
                 // Quando aparece o ';' temos que mudar o estilo.
                 // No buffer tem o valor do novo estilo.
                 case ';':
                     //printf("FOUND {;}\n");
                     ivalue = (int) CSI_BUFFER[0];
                     ivalue = (int) (ivalue & 0xFF); //only the first byte.
                     ivalue = atoi(&ivalue); 
                     if(ivalue==0){}; //reset all modes (styles and colors)
                     if(ivalue==1){}; //set bold mode.
                     if(ivalue==2){}; //set dim/faint mode.
                     if(ivalue==3){}; //set italic mode.
                     if(ivalue==4){}; //set underline mode.
                     if(ivalue==5){}; //set blinking mode
                     if(ivalue==6){}; //
                     if(ivalue==7){}; //
                     if(ivalue==8){}; //set hidden/invisible mode
                     if(ivalue==9){}; //set strikethrough mode.
                     return;
                     break;

                // Vamos apenas colocar no buffer
                // para analizarmos depois.
                // Colocamos no tail e retiramos no head.
                default:
                    //printf ("FOUND {value}\n"); //debug
                    
                    //#test: using only the first offset for now.
                    CSI_BUFFER[0] = (char) ascii;
                    
                    //#bugbug: 'PF'
                    //CSI_BUFFER[__csi_buffer_tail] = (char) ascii;
                    //__csi_buffer_tail++;
                    //if ( __csi_buffer_tail >= CSI_BUFFER_SIZE )
                    //{
                    //    __csi_buffer_tail = 0;
                    //}
                    //printf("value done\n");
                    return;
                    break;
            };


        } else if (term.esc & ESC_STR_END){ 
 
            // ...

        } else if (term.esc & ESC_ALTCHARSET){

            switch (ascii)
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

            // Encontramos o '[' depois de \033.
            // Entao vamos entrar em ESC_CSI?
            case '[':
                //printf ("FOUND {[}\n"); //debug
                term.esc |= ESC_CSI;
                //terminal_write_char ( fd, window, (int) '['); //debug
                return;
                break; 
   
            case '#':
                 //printf ("FOUND {#}\n"); //debug
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
                terminal_write_char ( fd, window, (int) '$');  //debug
                //printf (" {IND} ");  //debug
                break;

            /* NEL -- Next line */ 
            case 'E': 
                term.esc = 0;
                terminal_write_char ( fd, window, (int) '$'); //debug
                //printf (" {NEL} "); //debug
                break;

            /* HTS -- Horizontal tab stop */
            case 'H':   
                term.esc = 0;
                terminal_write_char ( fd, window, (int) '$'); //debug
                 //printf (" {HTS} "); //debug
                break;

            /* RI -- Reverse index */
            case 'M':     
                term.esc = 0;
                terminal_write_char ( fd, window, (int) '$'); //debug
                //printf (" {RI} "); //debug
                break;

            /* DECID -- Identify Terminal */
            case 'Z':  
                 term.esc = 0;
                 terminal_write_char (fd, window, (int) '$'); //debug
                 //printf (" {DECID} "); //debug
                 break;


            /* RIS -- Reset to inital state */
            case 'c': 
                 term.esc = 0;
                 terminal_write_char ( fd, window, (int) '$'); //debug
                 //printf (" {reset?} "); //debug
                 break; 

            /* DECPAM -- Application keypad */
            case '=': 
                 term.esc = 0;
                 terminal_write_char ( fd, window, (int) '$'); //debug
                 //printf (" {=} "); //debug
                 break;

            /* DECPNM -- Normal keypad */
            case '>': 
                term.esc = 0;
                terminal_write_char (fd, window, (int) '$'); //debug
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
// Insere um caractere dentro do buffer.

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

    LINES[y].CHARS[x]      = (char) c;
    LINES[y].ATTRIBUTES[x] = 7;
}


// # terminal stuff
static void save_cur (void)
{
    textSavedCol = cursor_x;
    textSavedRow = cursor_y;
}


// # terminal stuff
static void restore_cur (void)
{
    cursor_x = textSavedCol;
    cursor_y = textSavedRow;
}



// terminalClearBuffer:
// Limpa o buffer da tela.
// Inicializamos com espaços.

void terminalClearBuffer (void)
{
    register int i=0;
    int j=0;
    for ( i=0; i<32; i++ )
    {
        for ( j=0; j<80; j++ ){
            LINES[i].CHARS[j]      = (char) ' ';
            LINES[i].ATTRIBUTES[j] = (char) 7;
        };
        LINES[i].left = 0;
        LINES[i].right = 0;
        LINES[i].pos = 0;
    };
}


/*
//#test
void
__testPrintBuffer(void)
{
    register int i=0;
    int j=0;
    for ( i=0; i<32; i++ )
    {
        for ( j=0; j<80; j++ )
        {
            if ( LINES[i].CHARS[j] != 0 )
            {
            }
            
            //LINES[i].CHARS[j]      = (char) ' ';
            //LINES[i].ATTRIBUTES[j] = (char) 7;
        };
        //LINES[i].left = 0;
        //LINES[i].right = 0;
        //LINES[i].pos = 0;
    };
}
*/


//Qual será a linha que estará no topo da janela.
void textSetTopRow ( int number )
{
    textTopRow = (int) number; 
}


int textGetTopRow (void)
{
    return (int) textTopRow;
}


//Qual será a linha que estará na parte de baixo da janela.
void textSetBottomRow ( int number )
{
    textBottomRow = (int) number; 
}


int textGetBottomRow (void)
{
    return (int) textBottomRow; 
}

void textSetCurrentRow ( int number )
{
    cursor_y = (int) number; 
}


int textGetCurrentRow (void)
{
    return (int) cursor_y;
}



void textSetCurrentCol ( int number )
{
    cursor_x = (int) number; 
}


int textGetCurrentCol (void)
{
    return (int) cursor_x; 
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
    cursor_x = x;
    cursor_y = y;

	//screen_buffer_pos = ( screen_buffer_y * __wlMaxColumns + screen_buffer_x ) ;
}


/* credits: bsd */
/* Pad STRING to COUNT characters by inserting blanks. */

int pad_to (int count, char *string)
{
    register int i=0;

//#todo
//Check string validation?

    i = strlen(string);
    if (i >= count){
        string[i++] = ' ';
    }else{
        while (i < count)
            string[i++] = ' ';
    };
    string[i] = '\0';

    return (int) (i);
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



//interna
int __terminal_clone_and_execute ( char *name )
{
    //if( (void*) name == NULL )
    //    return -1;
    //if(*name == 0)
    //    return -1;
    return (int) gramado_system_call ( 900, (unsigned long) name, 0, 0 );
}

void _draw(int fd, int c)
{

   //unsigned long x;
   //x=0x65666768; //last
   

    //printf ("%c",c);
    //fflush(stdout);
    //return;
   
   
                  /*
                    terminal_drawchar_request (
                        (int) fd,//fd,
                        (int) 0, //__response_wid, //window_id,
                        (unsigned long) __tmp_x,//left,
                        (unsigned long) __tmp_y,//top,
                        (unsigned long) COLOR_RED,
                        (unsigned long) x ); 
                        */
                    
                  gws_draw_char (
                      (int) fd,             // fd,
                      (int) 0,              // window id,
                      (unsigned long) __tmp_x,    // left,
                      (unsigned long) __tmp_y,    // top,
                      (unsigned long) fg_color,
                      (unsigned long) c );
      
                    
                        
                 __tmp_x = __tmp_x + 8;
                 
                 //if ( __tmp_x > (8*80) )
                 //{
                 //    __tmp_y = __tmp_y + 8;
                 //    __tmp_x = 0;
                 //}
                 
                //terminal_drawchar_response((int) fd);
}


// worker
void __on_return_key_pressed(int fd)
{
    unsigned long jiffie_start=0;
    unsigned long jiffie_end=0;
    unsigned long jiffie_delta=0;

// Finalize the command line.

    input('\0');

    //jiffie_start = (unsigned long) rtl_get_system_metrics(118);

    if(fd<0)
        return;

    compareStrings(fd);

    //jiffie_end = (unsigned long) rtl_get_system_metrics(118);
    //jiffie_delta = (jiffie_end-jiffie_start);

// #bugbug: 
// We do not have a function to print strings
// into the terminal's client window.

    //printf("speed: %d ms\n",jiffie_delta);
}


// local
int 
terminalProcedure ( 
    int fd,
    int window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )

{
    if (fd<0)    {return -1;}
    if (window<0){return -1;}
    if (msg<0)   {return -1;}

// ==================

    switch(msg){

    //case MSG_QUIT:
    //case 4080:
        //exit(0);
        //break;

    case MSG_KEYDOWN:
        switch(long1)
        {
            case VK_RETURN:
                
                // When using the embedded shell.
                // Compare strings.
                if( isUsingEmbeddedShell == TRUE ){
                    __on_return_key_pressed(fd);
                }

                // When not using the embedded shell.
                // Goto next line.
                if( isUsingEmbeddedShell == FALSE ){
                    cursor_x++;
                    if( cursor_x >= Terminal.width_in_chars)
                    {
                        cursor_x = Terminal.left;
                        cursor_y++;
                    }
                }

                return 0;
                break;

            // Draw the char using the window server.
            // tputc() uses escape sequence.
            default:
                if( isUsingEmbeddedShell == TRUE ){  input(long1);  }
                tputc(
                    (int) fd, 
                    (int) Terminal.client_window_id, 
                    (int) long1, 
                    (int) 1 );

                return 0;
                break;
        };
        break;


    // #bugbug: Not working
    // It's because the terminal is getting input
    // from file, not from the control thread.
    //case MSG_SYSKEYDOWN:
    //    switch(long1){
    //    case VK_F1: gws_clone_and_execute("browser.bin");  break;
    //    case VK_F2: gws_clone_and_execute("editor.bin");   break;
    //    case VK_F3: gws_clone_and_execute("fileman.bin");  break;
    //    case VK_F4: gws_clone_and_execute("shutdown.bin"); break;
    //    };
    //    return 0;
    //    break;

    default:
        return 0;
        break;
    };

// done
    return 0;
}


// local
// Pegando o input de GRAMADO.TXT.
int __input_GRAMADOTXT(int fd)
{
// #importante:
// Esse event loop pega dados de um arquivo.

    int C=0;
    int client_fd = fd;
    int window_id = Terminal.client_window_id;

    FILE *new_stdin;

    new_stdin = (FILE *) fopen("gramado.txt","a+");
    if( (void*) new_stdin == NULL )
    {
        printf ("__input_GRAMADOTXT: new_stdin\n");
        return -1;
    }

// O kernel seleciona qual será 
// o arquivo para teclado ps2.
    gramado_system_call(
        8002,
        fileno(new_stdin),
        0,
        0 );

// Poisiona no início do arquivo.
    rewind(new_stdin);

// relax
    rtl_yield();
    
    while (1){
        C = fgetc(new_stdin);
        if (C > 0)
        {
            terminalProcedure( 
                client_fd,    // socket
                window_id,    // window ID
                MSG_KEYDOWN,  // message code
                C,            // long1 (ascii)
                C );          // long2 (ascii)
        }
        rtl_yield(); // relax
    };
    
    return 0;
}


// local
// Pegando o input de 'stdout'.
// #bugbug
// Isso esta falhando porque stdout não é um 'regular file'
// ele é um console e só esta aceitando saída por enquanto.
int __input_STDOUT(int fd)
{
// #importante:
// Esse event loop pega dados de um arquivo.

    int C=0;
    int client_fd = fd;
    int window_id = Terminal.client_window_id;

    FILE *new_stdin;
    //new_stdin = (FILE *) fopen("gramado.txt","a+");
    new_stdin = stdout;

    if( (void*) new_stdin == NULL ){
        printf ("__input_STDOUT: new_stdin\n");
        return -1;
    }

// O kernel seleciona qual será 
// o arquivo para teclado ps2.

    gramado_system_call(
        8002,
        fileno(new_stdin),
        0,
        0 );

// Poisiona no início do arquivo.
    rewind(new_stdin);

// relax
    rtl_yield();
    
    while (1){

        C = fgetc(new_stdin);

        if( C == EOF || C == VK_RETURN ){
            rewind(new_stdin);
        }
        
        if (C > 0)
        {
            terminalProcedure( 
                client_fd,    // socket
                window_id,    // window ID
                MSG_KEYDOWN,  // message code
                C,            // long1 (ascii)
                C );          // long2 (ascii)
        }
        rtl_yield(); // relax
    };
    
    return 0;
}


// local
// Pegando o input de 'stderr'.
// It's working
int __input_STDERR(int fd)
{
// #importante:
// Esse event loop pega dados de um arquivo.

    int C=0;
    int client_fd = fd;
    int window_id = Terminal.client_window_id;

    FILE *new_stdin;
    //new_stdin = (FILE *) fopen("gramado.txt","a+");
    new_stdin = stderr;
    __terminal_input_fp = stderr;   //save global.

    if( (void*) new_stdin == NULL ){
        printf ("__input_STDERR: new_stdin\n");
        return -1;
    }

// relax
    rtl_yield();
    rtl_yield();
    rtl_yield();
    rtl_yield();
    
    while (1){
        C = fgetc(new_stdin);
        if (C > 0)
        {

            if(C == '9'){
                //printf("TERMINAL: 9\n");  //console
            }
            
            terminalProcedure( 
                client_fd,    // socket
                window_id,    // window ID
                MSG_KEYDOWN,  // message code
                C,            // long1 (ascii)
                C );          // long2 (ascii)
        }
        rtl_yield(); // relax
    };
    
    return 0;
}

// local
// Pegando o input de 'stdin'.
int __input_STDIN(int fd)
{
// #importante:
// Esse event loop pega dados de um arquivo.

    int C=0;
    int client_fd = fd;
    int window_id = Terminal.client_window_id;

    FILE *new_stdin;
    //new_stdin = (FILE *) fopen("gramado.txt","a+");
    new_stdin = stdin;

    if( (void*) new_stdin == NULL ){
        printf ("__input_STDIN: new_stdin\n");
        return -1;
    }

// O kernel seleciona qual será 
// o arquivo para teclado ps2.

    gramado_system_call(
        8002,
        fileno(new_stdin),
        0,
        0 );

// Poisiona no início do arquivo.
    rewind(new_stdin);

// relax
    rtl_yield();
    
    while (1){
        
        if( isUsingEmbeddedShell == FALSE )
            return 0;  //ok
        
        C = fgetc(new_stdin);
        if (C > 0)
        {
            terminalProcedure( 
                client_fd,    // socket
                window_id,    // window ID
                MSG_KEYDOWN,  // message code
                C,            // long1 (ascii)
                C );          // long2 (ascii)
        }
        //rtl_yield(); // relax
    };

    return 0;
}



//
// Main
//

int main ( int argc, char *argv[] )
{

// ====
    //porta para o Window Server 'ws' em gramado_ports[]
    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    
    // Connecting to the window server in this machine.
    addr_in.sin_port = PORTS_WS;
    addr_in.sin_addr.s_addr = IP(127,0,0,1); 
// ====

    int client_fd = -1;


    debug_print ("terminal: Initializing\n");

// Device info
// #todo: Check for 'zero'.

    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);

    Terminal.initialized = FALSE;

// Cursor
    cursor_x = 0;
    cursor_y = 0;

// Process info
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
    //printf ("terminal: Creating socket\n");

    //client_fd = socket ( AF_GRAMADO, SOCK_STREAM, 0 );
    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );
    if ( client_fd < 0 )
    {
       debug_print ("terminal: Couldn't create socket\n");
       printf      ("terminal: Couldn't create socket\n");
       exit(1);
    }



// Saving the fd in the main struct.
    Terminal.client_fd = client_fd;
    //...

    // pid=2 fd=4
    printf ("TERMINAL.BIN: pid{%d} fd{%d}\n",
        Terminal.pid,
        Terminal.client_fd );

    //while(1){}

//
// connect
// 

// Nessa hora colocamos no accept um fd.
// então o servidor escreverá em nosso arquivo.

    //printf ("terminal: Connecting to ws via inet ...\n");

    int con_status = -1;

    while (1){

        con_status = (int) connect(client_fd, (void *) &addr_in, sizeof(addr_in));

        if ( con_status < 0 ){ 
            
            // Nesse caso a conexao pode ter sido recusada 
            // porque o servidor tem clentes demais.
            // Vamos esperar para sempre?
            if( con_status == ECONNREFUSED )
                rtl_yield();

            debug_print ("terminal: Connection Failed \n");
            printf      ("terminal: Connection Failed \n");

        }else{ 
            break; 
        };
    };

// Windows: it's global now.
    //int main_window = 0;
    //int terminal_window = 0;

//
// main window
//

    unsigned long mwWidth  = (w >> 1);
    unsigned long mwHeight = (h >> 1); 
    unsigned long mwLeft   = ( ( w - mwWidth ) >> 1 );
    unsigned long mwTop    = ( ( h - mwHeight) >> 1 );
    unsigned int mwColor   = COLOR_WINDOW;


//
// Client area window
//

// Set default
    unsigned long wLeft   = 2;   // por causa da borda.
    unsigned long wTop    = 34;  // por causa da title bar
    unsigned long wWidth  =  mwWidth  -2 -2;
    unsigned long wHeight =  mwHeight -2 -34;

    unsigned int wColor = (unsigned int) bg_color;

// The surface of this thread.
    setup_surface_retangle ( 
        (unsigned long) mwLeft, 
        (unsigned long) mwTop, 
        (unsigned long) mwWidth, 
        (unsigned long) mwHeight );

// ===================================================

//
// main window
//

// style: 
// 0x0001=maximized | 0x0002=minimized | 0x0004=fullscreen

    main_window = gws_create_window (
                      client_fd,
                      WT_OVERLAPPED, 1, 1, "Terminal",
                      mwLeft, mwTop, mwWidth, mwHeight,
                      0,
                      0x0000,
                      mwColor, 
                      mwColor );

    Terminal.main_window_id = main_window;

    if(main_window<0){
        printf("terminal: fail on main_window\n");
        while(1){}
    }


// ===================================================

//
// Client area window
//

// Let's get some values.
// Remember: Maybe the window server changed
// the window size and position.
// We need to get these new values.

    struct gws_window_info_d *wi;

    wi = (void*) malloc( sizeof( struct gws_window_info_d ) );

    if( (void*) wi == NULL )
    {
        printf("terminal: wi\n");
        while(1){}
    }

    //IN: fd, wid, window info structure.
    gws_get_window_info(
        client_fd, 
        main_window,   // The app window.
        (struct gws_window_info_d *) wi );

    if(wi->used != TRUE)
    {
        printf("terminal: wi->used\n");
        while(1){}
    }

    if(wi->magic!=1234)
    {
        printf("terminal: wi->magic\n");
        while(1){}
    }



// Setting new values for the client window.


    // nao pode ser maior que o dispositivo
    if( wi->cr_left >= w)
    {
        printf("terminal: wi->cr_left\n");
        while(1){}
    }

    // nao pode ser maior que o dispositivo
    if(wi->cr_top >= h)
    {
        printf("terminal: wi->cr_top\n");
        while(1){}
    }

    // nao pode ser maior que o dispositivo
    if(wi->cr_width == 0 || wi->cr_width > w)
    {
        printf("terminal: wi->cr_width\n");
        while(1){}
    }

    // nao pode ser maior que o dispositivo
    if(wi->cr_height == 0 || wi->cr_height > h)
    {
        printf("terminal: wi->height\n");
        while(1){}
    }

// #danger
// Let's get the values for the client area.

    wLeft   = wi->cr_left;
    wTop    = wi->cr_top;
    wWidth  = wi->cr_width;
    wHeight = wi->cr_height;

    terminal_window = gws_create_window (
                          client_fd,
                          WT_SIMPLE, 1, 1, "ter-client",
                          wLeft, wTop, wWidth, wHeight,
                          main_window,0,wColor,wColor);

    if(terminal_window<0){
        printf("terminal: fail on terminal_window\n");
        while(1){}
    }


// Saving the window id.
    Terminal.client_window_id = terminal_window;

// #bugbug
// Something is wrong here.
// is it in pixel or in chars?
    Terminal.left = 0;
    Terminal.top  = 0;
    //Terminal.left = wLeft;  //0;
    //Terminal.top  = wTop;   //0;

// Width and height

    // In pixels.
    Terminal.width = wWidth;
    Terminal.height = wHeight;

// In chars.
    Terminal.width_in_chars  = (unsigned long)((wWidth/8)  & 0xFFFF);
    Terminal.height_in_chars = (unsigned long)((wHeight/8) & 0xFFFF);

    Terminal.initialized = TRUE;

// Set window with focus
    //gws_async_command(client_fd,9,0,terminal_window);

// Invalidate surface.
    invalidate_surface_retangle();

    //while(1){}

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


// Initialize globals.
// #importante: 
// Isso será definido somente uma vez.

    __wlMaxColumns = DEFAULT_MAX_COLUMNS;
    __wlMaxRows    = DEFAULT_MAX_ROWS;


// Initializations
// #important:
// We will call this function
// only after having the Terminal structure initialized.

    terminalTerminal();

// Inicializando prompt[].
    input('\n');
    input('\0');

//
// Client
//

// #todo
// Vamos fazer isso outra hora.
// por hora vamos apenas usar o terminal,
// com o input no terminal
// Write something in the standard stream and call shell.bin.

    // test_standard_stream(client_fd);


// ============================================
// focus
// #bugbug
// It needs to be an 'editbox' for typing messages.

/*
    gws_async_command(
         client_fd,
         9,             // set focus
         terminal_window,
         terminal_window );
*/

    //rtl_focus_on_this_thread();



/*
//================
//cls
     gws_redraw_window(client_fd,Terminal.client_window_id,TRUE);
     //#define SYSTEMCALL_SETCURSOR  34
     gramado_system_call ( 34, 2, 2, 0 );
//=================
*/

    clear_terminal_client_window(client_fd);
    doPrompt(client_fd);

// Input loop!
// local routine.

    int InputStatus=-1;


//from GRAMADO.TXT
//ok, it is working.
    //InputStatus = __input_GRAMADOTXT(client_fd);

//from stdout
// #bugbug
// Isso esta falhando porque stdout não é um 'regular file'
// ele é um console e só esta aceitando saída por enquanto.
    //InputStatus = __input_STDOUT(client_fd);


// from stdin
// stdin é um 'regular file'
    InputStatus = __input_STDIN(client_fd);

     // estavamos lendo em stdin, e vamos começar a ler em stderr
     // sem mandarmos o kernel enviar o input para stderr

    if( InputStatus == 0 )
    {

        //printf("TERMINAL: newloop\n");

// from srderr
// stderr é um 'regular file'
// It's working.

       // rebubina o arquivo de input.
        //rewind(stdin);

        // agora vamos ler stderr
        InputStatus = __input_STDERR(client_fd);
    }

//exit:
    debug_print ("terminal: bye\n"); 
    printf      ("terminal: bye\n");
    
    while(1){}

    return 0;
}


/*
 * terminalTerminal:
 *     Constructor.
 *     Não emite mensagens.
 */

// #bugbug
// essas configurações são configurações de janela,
// então estão mais para terminal do que para shell.


static void terminalTerminal (void)
{
    int i=0;
    int j=0;

// Internas.
    //shellStatus = 0;
    //shellError = 0;

// Initialize colors.
    bg_color = COLOR_BLACK;
    fg_color = COLOR_WHITE;

    cursor_x=0;
    cursor_y=0;

    prompt_color = COLOR_GREEN;


// Inicializando as estruturas de linha.
// Inicializamos com espaços.
// Limpa o buffer de linhas onde os caracteres são colocados.
    
    terminalClearBuffer();

// Deve ser pequena, clara e centralizada.
// Para ficar mais rápido.
// #importante:
// O aplicativo tem que confiar nas informações 
// retornadas pelo sistema.
// Usar o get system metrics para pegar o 
// tamanho da tela.

//inicializa as metricas do sistema.
    terminalInitSystemMetrics();

//inicializa os limites da janela.
    terminalInitWindowLimits();

//inicia o tamanho da janela.
    terminalInitWindowSizes();

//inicializar a posição da janela.
    terminalInitWindowPosition();
 
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

	//shellBufferMaxColumns = DEFAULT_BUFFER_MAX_COLUMNS;
	//shellBufferMaxRows    = DEFAULT_BUFFER_MAX_ROWS;
	
	//buffersize = (shellBufferMaxColumns * shellBufferMaxRows);
	

//
// #todo: 
// E o fluxo padrão. Quem configurou os arquivos ???
// o kernel configuroru???
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


static void terminalInitSystemMetrics(void)
{

// Screen width and height.
    smScreenWidth = gws_get_system_metrics(1);
    smScreenHeight = gws_get_system_metrics(2); 

// Cursor width and height.
    smCursorWidth = gws_get_system_metrics(3);
    smCursorHeight = gws_get_system_metrics(4);

// Mouse pointer width and height.
    smMousePointerWidth = gws_get_system_metrics(5);
    smMousePointerHeight = gws_get_system_metrics(6);

// Char width and height.
    smCharWidth = gws_get_system_metrics(7);
    smCharHeight = gws_get_system_metrics(8);


//#todo:
//vertical scroll size
//horizontal scroll size.

//#importante
//#todo: pegar mais.

    //...

// #todo: 
// Temos que criar essa variável.

    //InitSystemMetricsStatus = TRUE;
} 


static void terminalInitWindowLimits (void)
{

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


// Fullscreen support.
    wlFullScreenLeft = 0;
    wlFullScreenTop  = 0;
    wlFullScreenWidth  = smScreenWidth;
    wlFullScreenHeight = smScreenHeight;

//Limite de tamanho da janela.
    wlMinWindowWidth  = (smCharWidth * 80);
    wlMinWindowHeight = (smCharWidth * 25);
    wlMaxWindowWidth  = wlFullScreenWidth;
    wlMaxWindowHeight = wlFullScreenHeight;

// Quantidade de linhas e colunas na área de cliente.
    wlMinColumns = 80;
    wlMinRows = 1;

// Dado em quantidade de linhas.
    textMinWheelDelta = 1;  //mínimo que se pode rolar o texto
    textMaxWheelDelta = 4;  //máximo que se pode rolar o texto	
    textWheelDelta = textMinWheelDelta;
    //...
}


static void terminalInitWindowSizes(void)
{

    if (Terminal.initialized != TRUE ){
        printf("terminalInitWindowSizes: Terminal.initialized\n");
        exit(1);
    }

//
//  ## Window size ##
//

    //wsWindowWidth = wlMinWindowWidth;
    //wsWindowHeight = wlMinWindowHeight;	

// Tamanho da janela do shell com base nos limites 
// que ja foram configurados.

    wsWindowWidth  = Terminal.width;
    wsWindowHeight = Terminal.height;

    if ( wsWindowWidth < wlMinWindowWidth ){
        wsWindowWidth = wlMinWindowWidth;
    }

    if ( wsWindowHeight < wlMinWindowHeight ){
        wsWindowHeight = wlMinWindowHeight;
    }
}


static void terminalInitWindowPosition(void)
{
    if (Terminal.initialized != TRUE ){
        printf("terminalInitWindowPosition: Terminal.initialized\n");
        exit(1);
    }

// Window position
    wpWindowLeft = Terminal.left;
    wpWindowTop  = Terminal.top;
    //wpWindowLeft = (unsigned long) ( (smScreenWidth - wsWindowWidth)/2 );
    //wpWindowTop = (unsigned long) ( (smScreenHeight - wsWindowHeight)/2 );  	
}


//
// End.
//





