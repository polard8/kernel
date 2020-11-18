

// programa usado para testes da libc e do console.



// rtl
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>





int  i, j, life, maxrand;
int c;


// String do número digitado.
char number[16]; 






//
// ===============================================================
//
int
__SendMessageToProcess ( int pid, 
                          unsigned long window, 
                          int message,
                          unsigned long long1,
                          unsigned long long2 );
//
// ===============================================================
//



/*
int getWindowSize(int *rows, int *cols) {
  struct winsize ws;
  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
    return 0;
  }
}
*/


/*

 3 enum ClearCodes {
 4 	CLEAR_FROM_CURSOR_TO_END,
 5 	CLEAR_FROM_CURSOR_TO_BEGIN,
 6 	CLEAR_ALL
 7 };
 8 
 9 void clearScreen(void) {
10 	printf("\x1b[%dJ", CLEAR_ALL);
11 }
12 
13 void clearScreenToBottom(void) {
14 	printf("\x1b[%dJ", CLEAR_FROM_CURSOR_TO_END);
15 }
16 
17 void clearScreenToTop(void) {
18 	printf("\x1b[%dJ", CLEAR_FROM_CURSOR_TO_BEGIN);
19 }
20 
21 void clearLine(void) {
22 	printf("\x1b[%dK", CLEAR_ALL);
23 }
24 
25 void clearLineToRight(void) {
26 	printf("\x1b[%dK", CLEAR_FROM_CURSOR_TO_END);
27 }
28 
29 void clearLineToLeft(void) {
30 	printf("\x1b[%dK", CLEAR_FROM_CURSOR_TO_BEGIN);
31 }


 3 void moveUp(int positions) {
 4 	printf("\x1b[%dA", positions);
 5 }
 6 
 7 void moveDown(int positions) {
 8 	printf("\x1b[%dB", positions);
 9 }
10 
11 void moveRight(int positions) {
12 	printf("\x1b[%dC", positions);
13 }
14 
15 void moveLeft(int positions) {
16 	printf("\x1b[%dD", positions);
17 }
18 
19 void moveTo(int row, int col) {
20 	printf("\x1b[%d;%df", row, col);
21 }
* 
*/








int
__SendMessageToProcess ( int pid, 
                          unsigned long window, 
                          int message,
                          unsigned long long1,
                          unsigned long long2 )
{
	unsigned long message_buffer[5];

	
    if (pid<0)
		return -1;
	
	message_buffer[0] = (unsigned long) window;
	message_buffer[1] = (unsigned long) message;
	message_buffer[2] = (unsigned long) long1;
	message_buffer[3] = (unsigned long) long2;
	//...

	return (int) gramado_system_call ( 112, 
	                 (unsigned long) &message_buffer[0], 
	                 (unsigned long) pid, 
	                 (unsigned long) pid );
}

//interna
void __debug_print (char *string)
{
    gramado_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}



FILE *__stream;

//interna
void __serenity_put_string( char *string )
{
    int Index=0;
    for ( Index=0; string[Index] != 0; Index++ )
        putc ( string[Index], __stream );
}



/*
 * main:
 * 
 * 
 */

char _buf[1024];

int main ( int argc, char *argv[] )
{
    //Torvalds_printf ("Torvalds_printf: Hello from hello.bin !!\n");
    
    
    
    __debug_print( "hello.bin: initializing ...\n");
    
    
    // Funcionou.
    /*
    __stream = (FILE *) malloc (sizeof(FILE));
    
    //buffer
    __stream->_base = (unsigned char *) malloc (BUFSIZ);
    __stream->_w = 0; //indice de escrita.
    __stream->_lbfsize = (BUFSIZ-1);
    __stream->_flags |= _IOLBF;
     __serenity_putc ( 'X' ,__stream);
    __serenity_putc ( 'Y' ,__stream);
    __serenity_putc ( 'Z' ,__stream);
    __serenity_putc ( '\n' ,__stream);
    __serenity_put_string ("Hello from hello.bin !!!\n");
    write_VC ( 0, "write_VC: ok  \n", 16 );
    */
            
    // escreverá em stdout;
    // mas write enciará para o console virtual 0.       
    printf ("hello.bin: Writing into the virtual console 0!\n");   
    
    //printf ("\x1b[8A test\n");   // Cursor Up
    //printf ("\x1b[8B test\n");   // Cursor Down
    printf ("hello.bin: My super \x1b[8C string!\n");   // Cursor Forward
    //printf ("\x1b[8D test\n");   // Cursor Backward
    //printf ("\x1b[8E test\n");   // Cursor Next Line
    //printf ("\x1b[8F test\n");   // Cursor Previous Line
    
    char *env_string;
       
    env_string = (char *) getenv ("PS1");
    printf(">>> %s .\n", env_string);
    
    
    env_string = (char *) getenv ("EDITOR");
    printf(">>> %s .\n", env_string);


    env_string = (char *) getenv ("TERM");
    printf(">>> %s .\n", env_string);


    env_string = (char *) getenv ("LANG");
    printf(">>> %s .\n", env_string);

    
    //Torvalds_printf("hello.bin: \x1b[H Writing into the virtual console 0!\n");
    
    //isso vai escrever na stream 1 do processo
    // em p->Streams[1];
    
    //#bugbug: isso não funcionou na máquina real.
    //provavelmente tem um ponteiro nulo em sys_write no kernel.
    
    //sprintf(_buf,"Testing write() \n");
    //write ( 1, _buf, sizeof(_buf) );     
            
     
    // funcionou no qemu.       
    //putc('X',stdout);        
    //putc('Y',stdout);        
    //putc('Z',stdout);        
    //putc('\n',stdout);        
    
    
    // Testado no qemu. 
    // Não travou.
    /*
    int i;
    int c;
    while(1)
    {
        c = getc(stdin);
        if(c==EOF)break;
        
        putc(c,stdout);
    }
    */
    
    
    //printf ("A");
    //printf("\x1b[2J");    // Clear the entire screen  fail
    //printf ("B \n");
    
    //fflush(stdout);
    
    //printf("\x1b[1J");    // Clear the screen from cursor to the beginning
   //printf("\x1b[0J");    // Clear the screen from cursor to the end    
    
   //printf("\x1b2dK");    // Clear the current line
   //printf("\x1b1dK");    // Clear the current line from cursor to left (beginning of the line)
   //printf("\x1b0dK");    // Clear the current line from cursor to right (end of the line)

   //printf("\x1b%d", 7);    // Save cursor
   //printf("\x1b%d", 8);    // Restore saved cursor

    

    //write(STDOUT_FILENO, "\x1b[2J", 4);
    //write(STDOUT_FILENO, "\x1b[H", 3);  

    /*
    int i=0;
    while(1){
        i++;
        //printf ("\e[%d;%dH    %c\n",i,i,c++);
        if (i>20)i=0;
    }
    */
    
    
    //printf ("\e[1;1H\e[0J *\n");
    //printf ("\e[1;1H\e[1J *\n");
    //printf ("\e[1;1H\e[2J *\n");
    //printf ("\e[1;1H\e[J  *\n");

     //\x1b[H is the code for returning the cursor to the home position.

    //printf ("\e[40;40H Fred Nora\n");
    
    
    


    //int __ret = -1;
    
    //__ret = fork();

    //printf (">>>>Oi, eu sou PID %d \n", getpid() );
    
    //gramado_system_call ( 82, 0, 0, 0 );
    //while(1){}
    
    return 0;
}


