
// console.c

#include <kernel.h>


// 
// Imports
//


// from swlib.asm
// Used to handle callbacks used by the window server.
extern unsigned long wmData_RDI;
extern unsigned long wmData_RSI;
extern unsigned long wmData_RDX;
extern unsigned long wmData_RCX;
extern unsigned long wmWindowMananer_SendMessage(void);

// used for handling screen dimensions.
//extern unsigned long gSavedX;
//extern unsigned long gSavedY;

// global
// Foreground console.
int fg_console=0;
// 0=apaga 1=acende 
int consoleTextCursorStatus=0;
// Esse eh o marcador de estagio do escape sequence.
// Usado para manipular csi
static unsigned long __EscapeSequenceStage = 0;

#define NPAR  16
static unsigned long par[NPAR];
static unsigned long npar = 0;
static unsigned long ques = 0;
static unsigned char attr = 0x07;

static int saved_x=0;
static int saved_y=0;


//
// == Private functions: Prototypes ======================
//

static void __ConsoleOutbyte (int c, int console_number);
static void __test_path(void);

//#todo: Use static modifier.
void __local_ri (void);
void csi_J (int par);
void csi_K(int par);
void csi_m(void);
void csi_M ( int nr, int console_number );
void csi_L (int nr, int console_number);

// =======================

static void __test_path(void)
{
    int status = -1;

    //unsigned long tmp_size = (512*4096);    // 512*4096 = 2MB
    void *b; //= (void *) allocPages ( 512 );

// ===================================
// #test: 
// Testando carregar usando path.

// Valid shapes
    //char PathAddress[] = "/GRAMADO/TEST.BMP";
    //char PathAddress[] = "/GRAMADO/TEST.TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/TEST.TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/TEST2.TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/TEST3.TXT";
    char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/12345678.TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/1.TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/$$$$$$$$.TXT";

// Invalid shapes
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/12345678T.XT";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/1234567.8TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/.TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/1234  78.TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/12345678.1";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/12345678.12";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/12345678.123";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/12345678.C";
    //char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/FOLDER3/12345678.CPP";
    
// =========================================

// (32*4096) bytes

    unsigned long BufferSize = (32*4096);

    b = (void *) allocPages(32); 

    if( (void*) b == NULL )
    {
        printf("b fail\n");
        return;
    }

    // IN: path, address, buffer size in bytes.
    status = (int) fs_load_path ( 
                       (const char*) PathAddress, 
                       (unsigned long) b,
                       (unsigned long) BufferSize ); 
    if(status<0){
        printf("__test_path: fs_load_path fail\n");
        return;
    }

    if( (void*)b != NULL )
        printf("OUTPUT:{%s}\n",b);
}

void __local_ri (void)
{
    //#todo
}

// goto xy
void 
__local_gotoxy ( 
    int new_x, 
    int new_y, 
    int console_number )
{

// #todo: max limit.

    if (console_number<0){
        return;
    }

    if ( new_x >= (CONSOLE_TTYS[console_number].cursor_right-1) )
    {
        return;
    }

    if ( new_y >= (CONSOLE_TTYS[console_number].cursor_bottom-1) )
    {
        return;
    }

    CONSOLE_TTYS[console_number].cursor_x = 
        (unsigned long) (new_x & 0xFFFFFFFF);
    CONSOLE_TTYS[console_number].cursor_y = 
        (unsigned long) (new_y & 0xFFFFFFFF);
}

void __local_save_cur (int console_number)
{
    saved_x = (int) CONSOLE_TTYS[console_number].cursor_x;
    saved_y = (int) CONSOLE_TTYS[console_number].cursor_y;
}

void __local_restore_cur (int console_number)
{
//#todo: max limit
    if(console_number<0){
        return;
    }
    CONSOLE_TTYS[console_number].cursor_x = (unsigned long) (saved_x & 0xFFFF);
    CONSOLE_TTYS[console_number].cursor_y = (unsigned long) (saved_y & 0xFFFF);
}


void __local_insert_line (int console_number)
{
    int oldtop    = 0;
    int oldbottom = 0;

    if(console_number<0){
        return;
    }


    oldtop    = CONSOLE_TTYS[console_number].cursor_top;
    oldbottom = CONSOLE_TTYS[console_number].cursor_bottom;

    CONSOLE_TTYS[console_number].cursor_top = CONSOLE_TTYS[console_number].cursor_y;
    
    //#bugbug: apontando par asi mesmo.
    //CONSOLE[console_number].cursor_bottom = CONSOLE[console_number].cursor_bottom;

    //if (console_number<0)
        //return;

    if( CONSOLE_TTYS[console_number].fullscreen_flag == TRUE ){
        console_scroll(console_number);
    }

    CONSOLE_TTYS[console_number].cursor_top    = oldtop;
    CONSOLE_TTYS[console_number].cursor_bottom = oldbottom;
}

void __local_delete_line(int console_number)
{
    int n=0;
    int oldtop    = 0;
    int oldbottom = 0;

// #todo: max limit
    if(console_number<0){
        return;
    }

    n = console_number;

// save old.
    oldtop    = (int) CONSOLE_TTYS[n].cursor_top;
    oldbottom = (int) CONSOLE_TTYS[n].cursor_bottom;

    CONSOLE_TTYS[n].cursor_top = (int) CONSOLE_TTYS[n].cursor_y;

    //#bugbug: apontando para si mesmo.
    //CONSOLE[n].cursor_bottom = CONSOLE[n].cursor_bottom;

//#todo
    //scrup();

    CONSOLE_TTYS[n].cursor_top    = oldtop;
    CONSOLE_TTYS[n].cursor_bottom = oldbottom;
}


void csi_J (int par)
{

	/*
	long count __asm__("cx");
	long start __asm__("di");

	switch (par) {
		case 0:   //erase from cursor to end of display 
			count = (scr_end-pos)>>1;
			start = pos;
			break;
		case 1:	//erase from start to cursor 
			count = (pos-origin)>>1;
			start = origin;
			break;
		case 2: // erase whole display 
			count = columns*lines;
			start = origin;
			break;
		default:
			return;
	}
	__asm__("cld\n\t"
		"rep\n\t"
		"stosw\n\t"
		::"c" (count),
		"D" (start),"a" (0x0720)
		:"cx","di");
		
	*/
}


// move to
void csi_K(int par)
{
   /*
	long count __asm__("cx");
	long start __asm__("di");

	switch (par) {
		case 0:	   //erase from cursor to end of line 
			if (x>=columns)
				return;
			count = columns-x;
			start = pos;
			break;
		case 1:	//erase from start of line to cursor 
			start = pos - (x<<1);
			count = (x<columns)?x:columns;
			break;
		case 2: //erase whole line 
			start = pos - (x<<1);
			count = columns;
			break;
		default:
			return;
	}
	__asm__("cld\n\t"
		"rep\n\t"
		"stosw\n\t"
		::"c" (count),
		"D" (start),"a" (0x0720)
		:"cx","di");
   */
}

// Fim da escape sequence.
// isso eh chamado quando encontramos um 'm'.
// O 'm' eh um marcador de fim de escape sequence.
// Entao vamos checar os parametros no buffer.
// Configuramos a variavel de atributo de acordo
// com o parametro encontrado.
// Ficaremos com o ultimo atributo. #bugbug ????

void csi_m(void)
{
    int i=0;
    int Ch=0;

    // #bugbug
    // Check 'npar'

    if (npar == 0){
        return;
    }

    for (i=0; i <= npar; i++)
    {
        Ch = (int) par[i];

        switch (Ch) {

        case 0:  attr=0x07;  break;
        case 1:  attr=0x0f;  break;
        case 4:  attr=0x0f;  break;
        case 7:  attr=0x70;  break;
        case 27: attr=0x07;  break;
        // default?

        };
    };
}


void csi_M ( int nr, int console_number )
{

    /*
	if ( nr > CONSOLE_TTYS[console_number].cursor_height )
		nr = CONSOLE_TTYS[console_number].cursor_height;
	else if (!nr)
		nr=1;
	while (nr--)
		__local_delete_line(console_number);
    
    */
}

// move to
void csi_L (int nr, int console_number)
{
   /*
	if (nr > CONSOLE[console_number].cursor_height)
		nr = CONSOLE[console_number].cursor_height;
	else if (!nr)
		nr=1;
	while (nr--)
		__local_insert_line(console_number);
    */
}



//============================================
// input:
// called by devices that are not block devices.
// probably keyboard and serial devices.
// See: keyboard.c and serial.c
// Called by DeviceInterface_PS2Keyboard() in ps2kbd.c

void 
console_interrupt(
    int target_thread, 
    int device_type, 
    int data )
{

    //int TargetThread = foreground_thread;
    int TargetThreadTID = (target_thread & 0xFFFF);
    int DeviceType = device_type;
    int Data = data;
    int Status=-1;

// #todo
// E se não tivermos uma foreground thread ?
// foreground representa a thred com 'foco de entrada'
// >> então, se não tivermos uma thread com foco de entrada,
// podemos mandar a mensagem para outra thread ?

// #todo: 
// Check overflow
// #todo
// Maybe we can set the idle thread if it fail.
// #todo: max limit

    if ( TargetThreadTID < 0 ){
        debug_print ("console_interrupt: [FAIL] TargetThreadTID\n");
        return;
    }

    switch (DeviceType){

        // keyboard
        // data =  raw byte.
        // See: kgws.c
        case CONSOLE_DEVICE_KEYBOARD:
            debug_print("console_interrupt: input from keyboard device :)\n");

            Status = (int) wmKeyEvent( (tid_t) TargetThreadTID, Data );
            if(Status<0)
                return;
            
            // Lets end this round putting a given thread at the end
            // of this round.

            // #tested: No difference at all.
            //if ( TargetThreadTID > 0 && TargetThreadTID < THREAD_COUNT_MAX )
                //cut_round( threadList[TargetThreadTID] );

            break;

        // COM port
        case CONSOLE_DEVICE_SERIAL:
            debug_print("console_interrupt: input from serial device\n");
            break;
 
        //network device.
        case CONSOLE_DEVICE_NETWORK:
            debug_print("console_interrupt: input from network device\n");
            break;

        // ...

        default:
            debug_print("console_interrupt: [FAIL] Default input device\n");
            break;
    };
}


// Initializar virtual console.
// Inicializa a estrutura de console virtual
// configura uma entrada no diretorio dev/
void console_init_virtual_console (int n)
{
    int ConsoleIndex = -1;

    debug_print ("console_init_virtual_console:\n");

// Limits

    ConsoleIndex = (int) n;
    if ( ConsoleIndex < 0 || 
         ConsoleIndex >= CONSOLETTYS_COUNT_MAX  )
    {
        debug_print ("console_init_virtual_console: [FAIL] ConsoleIndex\n");
        x_panic     ("console_init_virtual_console: [FAIL] ConsoleIndex\n");
    }

//
// Data
//

    CONSOLE_TTYS[ConsoleIndex].initialized = FALSE;

    // Todo virtual console eh uma tty. Os 4.
    CONSOLE_TTYS[ConsoleIndex].objectType  = ObjectTypeTTY;
    CONSOLE_TTYS[ConsoleIndex].objectClass = ObjectClassKernelObjects;
    CONSOLE_TTYS[ConsoleIndex].used  = TRUE;
    CONSOLE_TTYS[ConsoleIndex].magic = (int) 1234;

    // No thread for now.
    CONSOLE_TTYS[ConsoleIndex].control = NULL;

    // tty is a terminal, so the user logs on a terminal.
    // No user logged yet.
    CONSOLE_TTYS[ConsoleIndex].user_info = NULL;

    // Security stuff.
    // Nao sei se essas estruturas estao prontas para isso nesse momento
    // ou se esses ponteiros sao nulos.
    CONSOLE_TTYS[ConsoleIndex].user_session = NULL;  // CurrentUserSession;
    CONSOLE_TTYS[ConsoleIndex].room         = NULL;  // CurrentRoom;
    CONSOLE_TTYS[ConsoleIndex].desktop      = NULL;  // CurrentDesktop;

    // file pointer
    // this file handles this tty object
    // CONSOLE[ConsoleIndex]._fp
    
    // tty name
    //CONSOLE_TTYS[ConsoleIndex].name[?] 
    CONSOLE_TTYS[ConsoleIndex].Name_len = 0;  //initialized

    //#todo: Indice do dispositivo.
    // CONSOLE_TTYS[ConsoleIndex].device = 0;   // initialized.

    CONSOLE_TTYS[ConsoleIndex].driver = NULL;  //driver struct
    CONSOLE_TTYS[ConsoleIndex].ldisc  = NULL;  //line discipline struct

    //CONSOLE_TTYS[ConsoleIndex].termios??       //termios struct (not a pointer)

    // process group.
    CONSOLE_TTYS[ConsoleIndex].gid = current_group;

    // ??
    // Quantos processos estao usando essa tty.
    CONSOLE_TTYS[ConsoleIndex].pid_count=0;

    CONSOLE_TTYS[ConsoleIndex].type = 0;
    CONSOLE_TTYS[ConsoleIndex].subtype = 0;
        
    CONSOLE_TTYS[ConsoleIndex].flags = 0;

    // not stopped
    CONSOLE_TTYS[ConsoleIndex].stopped = FALSE;

    // process
    //CONSOLE_TTYS[ConsoleIndex].process = KernelProcess;
    
    // thread
    //CONSOLE_TTYS[ConsoleIndex].thread  = ?

    // Qual terminal virtual esta usando essa tty.
    CONSOLE_TTYS[ConsoleIndex].virtual_terminal_pid = 0;

    // Window.
    // When we are using the kgws.
    // CONSOLE_TTYS[ConsoleIndex].window = NULL;


    //
    // == buffers ===========================
    //

    // #bugbug
    // No buffers fo rthe virtual consoles.
    // remember: 
    // The virtual console is used only in the 'stdout' of a process.
    CONSOLE_TTYS[ConsoleIndex].nobuffers = TRUE;   // No buffers.
    
    //#bugbug: buffer não á mais arquivo.
    //CONSOLE_TTYS[ConsoleIndex]._rbuffer = (file *) 0; 
    //CONSOLE_TTYS[ConsoleIndex]._cbuffer = (file *) 0;
    //CONSOLE_TTYS[ConsoleIndex]._obuffer = (file *) 0;


    // cursor dimentions in pixel.
    // #bugbug: determinado
    CONSOLE_TTYS[ConsoleIndex].cursor_width_in_pixels = 8; 
    CONSOLE_TTYS[ConsoleIndex].cursor_height_in_pixels = 8;

    //cursor position in chars.
    CONSOLE_TTYS[ConsoleIndex].cursor_x = 0;
    CONSOLE_TTYS[ConsoleIndex].cursor_y = 0;

    
// cursor limits


// #todo: 8 = char size.
    unsigned long screen_width_in_chars  = (gSavedX/8);
    unsigned long screen_height_in_chars = (gSavedY/8);

// Full screen
    CONSOLE_TTYS[ConsoleIndex].fullscreen_flag = TRUE;
    CONSOLE_TTYS[ConsoleIndex].cursor_left = 0;
    CONSOLE_TTYS[ConsoleIndex].cursor_top  = 0;
    CONSOLE_TTYS[ConsoleIndex].cursor_right  = screen_width_in_chars;
    CONSOLE_TTYS[ConsoleIndex].cursor_bottom = screen_height_in_chars;

// Everyone has the same color.
// White on black.
    CONSOLE_TTYS[ConsoleIndex].bg_color = COLOR_BLUE;
    CONSOLE_TTYS[ConsoleIndex].fg_color = COLOR_WHITE;

// A different color for each console number.
    if (ConsoleIndex == 0){
        CONSOLE_TTYS[ConsoleIndex].fg_color = COLOR_WHITE; 
    }
    if (ConsoleIndex == 1){
        CONSOLE_TTYS[ConsoleIndex].fg_color = COLOR_YELLOW; 
    }
    if (ConsoleIndex == 2){
        CONSOLE_TTYS[ConsoleIndex].fg_color = COLOR_GREEN; 
    }
    if (ConsoleIndex == 3){
        CONSOLE_TTYS[ConsoleIndex].fg_color = COLOR_CYAN; 
    }

    //#todo
    // Buffers !!!
    //CONSOLE_TTYS[ConsoleIndex]._rbuffer ...
    //CONSOLE_TTYS[ConsoleIndex]._cbuffer ...    


    //#todo
    // Local mode flags.
    CONSOLE_TTYS[ConsoleIndex].termios.c_lflag = ECHO;


    //CONSOLE_TTYS[ConsoleIndex].vc_mode = 0;

    // #bugbug
    // A estrutura tem mais elementos que podem ser inicializados.
    // Tivemos problemas ao tentar inicializa-los.

    CONSOLE_TTYS[ConsoleIndex].initialized = TRUE;
    
    //if ( CONSOLE_TTYS[ConsoleIndex].initialized != TRUE )
        //x_panic("FUCK");
    
}


void console_set_current_virtual_console (int n)
{
    if ( n < 0 || n >= 4 ){
        debug_print ("console_set_current_virtual_console: Limits\n");
        return;
    }

    fg_console = n;
}


int console_get_current_virtual_console (void)
{
    return (int) fg_console;
}


// Called by: 
// __local_ps2kbd_procedure in ps2kbd.c
// VirtualConsole_initialize in console.c
// __initialize_virtual_consoles in kstdio.c

void jobcontrol_switch_console(int n)
{
    // #todo:
    // maybe we can do somo other configuration here.
 
    if ( n<0 || n >= CONSOLETTYS_COUNT_MAX )
    {
        debug_print("jobcontrol_switch_console: Limits\n");
        return;
    }
    
// Change the foreground console.
    console_set_current_virtual_console(n);
}


/*
 * set_up_cursor:
 *     Setup cursor for the current virtual console.
 */

// #todo
// Maybe change to console_set_up_cursor();

// We need a routine to change the cursor inside a wigen window.
// The console has a window ? No ? ... but it has a dimension.
// See the tty structure at hal/dev/tty/tty.h

// We need to know that there is a difference between 
// printing at a given console and printing at a given window.
// The tty has a window, but we are not using it, we are using
// the margins for the console.

// #todo
// Quando estivermos colocando o cursor em uma janela e
// a janela não for válida, então colocamos o cursor na posição 0,0.

// #todo
// Podemos criar uma rotina que mude o cursor de um dado console.
//void set_up_cursor2 ( int console, unsigned long x, unsigned long y );
//void set_up_cursor2 ( int console, unsigned long x, unsigned long y ){}

// Change to setup_fgconsole_cursor(..)
void set_up_cursor ( unsigned long x, unsigned long y )
{
    if (fg_console<0){ return; }
    if (fg_console>=CONSOLETTYS_COUNT_MAX){ return; }
    CONSOLE_TTYS[fg_console].cursor_x = (unsigned long) x;
    CONSOLE_TTYS[fg_console].cursor_y = (unsigned long) y;
}


/*
 * get_cursor_x:
 *     Pega o valor de x.
 *     @todo: Isso pode ir para outro lugar.
 */
unsigned long get_cursor_x (void)
{
    //if (fg_console<0){ panic("get_cursor_x"); }
    //if (fg_console>=CONSOLETTYS_COUNT_MAX){ panic("get_cursor_x"); }
    return (unsigned long) CONSOLE_TTYS[fg_console].cursor_x;
}

/*
 * get_cursor_y:
 *     Pega o valor de y.
 *     @todo: Isso pode ir para outro lugar.
 */
unsigned long get_cursor_y (void)
{
    //if (fg_console<0){ panic("get_cursor_x"); }
    //if (fg_console>=CONSOLETTYS_COUNT_MAX){ panic("get_cursor_x"); }
    return (unsigned long) CONSOLE_TTYS[fg_console].cursor_y; 
}


void console_scroll (int console_number)
{
    // Salvar cursor
    unsigned long OldX=0;
    unsigned long OldY=0;

    // Salvar limites
    unsigned long OldLeft=0;
    unsigned long OldTop=0;
    unsigned long OldRight=0;
    unsigned long OldBottom=0;

    register int i=0;


    debug_print ("console_scroll: #todo #fixme\n");

    if ( VideoBlock.useGui != TRUE )
    {
        debug_print ("console_scroll: no GUI\n");
        panic       ("console_scroll: no GUI\n");
    }

    // #todo: check overflow
    if ( console_number < 0 ){
        panic ("console_scroll: [FAIL] console_number\n");
    }

    // Scroll the screen rectangle.
    // See: rect.c

    // #todo
    // Isso deveria ser apenas scroll_rectangle()

    scroll_screen_rect();

// Clear the last line.
  
// Salva cursor
    OldX = CONSOLE_TTYS[console_number].cursor_x;
    OldY = CONSOLE_TTYS[console_number].cursor_y;

// Salva cursor limits
    OldLeft   = CONSOLE_TTYS[console_number].cursor_left;
    OldTop    = CONSOLE_TTYS[console_number].cursor_top;
    OldRight  = CONSOLE_TTYS[console_number].cursor_right;
    OldBottom = CONSOLE_TTYS[console_number].cursor_bottom;
    

// Cursor na ultima linha.
// Para podermos limpa-la.

    CONSOLE_TTYS[console_number].cursor_x =   CONSOLE_TTYS[console_number].cursor_left; 
    CONSOLE_TTYS[console_number].cursor_y = ( CONSOLE_TTYS[console_number].cursor_bottom); 


// Limpa a últime linha.
// #bugbug: 
// Essa rotina pode sujar alguns marcadores importantes.
// Depois disso precisamos restaurar os valores salvos


   if ( CONSOLE_TTYS[console_number].cursor_left < (CONSOLE_TTYS[console_number].cursor_right-1) )
   {
       for ( i = CONSOLE_TTYS[console_number].cursor_left; 
             i < (CONSOLE_TTYS[console_number].cursor_right-1);
             i++ )
       {
           __ConsoleOutbyte(' ',console_number); 
       };
    }


// Restaura limits
    CONSOLE_TTYS[console_number].cursor_left   = (OldLeft   & 0xFFFF);
    CONSOLE_TTYS[console_number].cursor_top    = (OldTop    & 0xFFFF);
    CONSOLE_TTYS[console_number].cursor_right  = (OldRight  & 0xFFFF);
    CONSOLE_TTYS[console_number].cursor_bottom = (OldBottom & 0xFFFF);

    CONSOLE_TTYS[console_number].cursor_x = 0; 
    CONSOLE_TTYS[console_number].cursor_y = ( CONSOLE_TTYS[console_number].cursor_bottom -1); 

    invalidate_screen();
    //refresh_screen();
}


/*
 * console_outbyte:
 *     Trata o caractere a ser imprimido e chama a rotina /_outbyte/
 * para efetivamente colocar o caractere na tela.
 * Essa rotina é chamada pelas funções: /putchar/scroll/.
 * @todo: Colocar no buffer de arquivo.
 */
// This functions calls __ConsoleOutbyte to draw
// the char into the screen.

void console_outbyte (int c, int console_number)
{
// Arguments.
    register int Ch = c;
    int n = (int) console_number;

    static char prev=0;

// char support.

    unsigned long __cWidth  = gwsGetCurrentFontCharWidth();
    unsigned long __cHeight = gwsGetCurrentFontCharHeight();

    // #debug
    // debug_print ("console_outbyte:\n");


    // #todo: Check overflow.
    //if (n<0)
    //{
    //    debug_print ("console_outbyte: n\n");
    //    return;
    //}

    if ( n < 0 || n >= CONSOLETTYS_COUNT_MAX  )
    {
        debug_print ("console_outbyte: [FAIL] n\n");
        x_panic     ("console_outbyte: [FAIL] n\n");
    }

    if ( __cWidth == 0 || __cHeight == 0 )
    {
        x_panic ("console_outbyte: [FAIL] char size\n");
    }


// #test
// Tem momento da inicialização em que esse array de estruturas
// não funciona, e perdemos a configuração feita

    if ( CONSOLE_TTYS[n].initialized != TRUE )
    {
        //x_panic ("console_outbyte: CONSOLE_TTYS");
        debug_print ("console_outbyte: [BUGBUG] CONSOLE_TTYS not initialized\n");
        return;
    }

// Obs:
// Podemos setar a posição do curso usando método,
// simulando uma variável protegida.

//checkChar:

    //Opção  
    //switch ?? 


    // form feed - Nova tela.
    if ( Ch == '\f' )
    {
        CONSOLE_TTYS[n].cursor_y = CONSOLE_TTYS[n].cursor_top;
        CONSOLE_TTYS[n].cursor_x = CONSOLE_TTYS[n].cursor_left;
        return;
    }

// #obs: #m$. 
// É normal \n retornar sem imprimir nada.

// Início da próxima linha. 
// not used!!!  "...\r\n";

    if ( Ch == '\n' && prev == '\r' ) 
    {
        // #todo: 
        // Melhorar esse limite.
        if ( CONSOLE_TTYS[n].cursor_y > (CONSOLE_TTYS[n].cursor_bottom) )
        {
            debug_print ("console_outbyte: scroll 1\n"); 
            
            if (CONSOLE_TTYS[n].fullscreen_flag == TRUE ){
                 console_scroll(n);
            }

            CONSOLE_TTYS[n].cursor_y = ( CONSOLE_TTYS[n].cursor_bottom -1 );
            prev = Ch; 
        }else{
            CONSOLE_TTYS[n].cursor_y++;
            CONSOLE_TTYS[n].cursor_x = CONSOLE_TTYS[n].cursor_left;
            prev = Ch;
        };
        return;
    }

// Próxima linha no modo terminal.
// "...\n"

    if ( Ch == '\n' && prev != '\r' ) 
    {
        // se o line feed apareceu quando estamos na ultima linha
        if ( CONSOLE_TTYS[n].cursor_y > (CONSOLE_TTYS[n].cursor_bottom) )
        {
            debug_print ("console_outbyte: scroll 2\n"); 
            if (CONSOLE_TTYS[n].fullscreen_flag == TRUE ){
                console_scroll(n);
            }
            
            CONSOLE_TTYS[n].cursor_y = (CONSOLE_TTYS[n].cursor_bottom -1);
            prev = Ch;
        }else{
            CONSOLE_TTYS[n].cursor_y++;

            // Retornaremos mesmo assim ao início da linha 
            // se estivermos imprimindo no terminal.
            if ( stdio_terminalmode_flag == 1 ){
                CONSOLE_TTYS[n].cursor_x = CONSOLE_TTYS[n].cursor_left;
            } 

            // Verbose mode do kernel.
            // permite que a tela do kernel funcione igual a um 
            // terminal, imprimindo os printfs um abaixo do outro.
            // sempre reiniciando x.
            if ( stdio_verbosemode_flag == 1 ){
                CONSOLE_TTYS[n].cursor_x = CONSOLE_TTYS[n].cursor_left;
            } 

            // Obs: No caso estarmos imprimindo em um editor 
            // então não devemos voltar ao início da linha.

            prev = Ch;
        };

        return;
    }

// TAB
// #todo: Criar a variável 'g_tab_size'.

    if ( Ch == '\t' ) 
    {
        CONSOLE_TTYS[n].cursor_x += (8);
        prev = Ch;
        return; 

        // Não adianta só avançar, tem que apagar o caminho até lá.

		//int tOffset;
		//tOffset = 8 - ( g_cursor_left % 8 );
		//while(tOffset--){
		//	_outbyte(' ');
		//}
		//set_up_cursor( g_cursor_x +tOffset, g_cursor_y );
		//return; 
    }

// Liberando esse limite.
// Permitindo os caracteres menores que 32.

    //if( c <  ' '  && c != '\r' && c != '\n' && c != '\t' && c != '\b' )
    //{
    //    return;
    //};

// Apenas voltar ao início da linha.
    if ( Ch == '\r' )
    {
        CONSOLE_TTYS[n].cursor_x = CONSOLE_TTYS[n].cursor_left;
        prev = Ch;
        return; 
    }

// Space
// #bugbug 
// Com isso o ascii 0x20 foi pintado, 
// mas como todos os bits do char na fonte estão desligados, 
// então não pinta coisa alguma.

    if ( Ch == 0x20 )  
    {
        CONSOLE_TTYS[n].cursor_x++;
        prev = Ch;
        return; 
    }

// Backspace

    //if ( Ch == '\b' )
    if ( Ch == 0x8 )
    {
        CONSOLE_TTYS[n].cursor_x--; 
        prev = Ch;
        return;
    }


//
// == Limits ====
//


//
// Collision.
//

// Sem espaço horizontal.
    if ( CONSOLE_TTYS[n].cursor_left >= CONSOLE_TTYS[n].cursor_right )
    {
        panic ("console_oubyte: l >= r ");
    }

// Sem espaço vertical.
    if ( CONSOLE_TTYS[n].cursor_top >= CONSOLE_TTYS[n].cursor_bottom )
    {
        panic ("console_oubyte: t >= b ");
    }

// Fim da linha.
// Limites para o número de caracteres numa linha.
// Voltamos ao inicio da linha e avançamos uma linha.
// Caso contrario, apenas incrementa a coluna.

    if ( CONSOLE_TTYS[n].cursor_x >= (CONSOLE_TTYS[n].cursor_right -1) ){
        CONSOLE_TTYS[n].cursor_x = CONSOLE_TTYS[n].cursor_left;
        CONSOLE_TTYS[n].cursor_y++;
    }else{ 
        CONSOLE_TTYS[n].cursor_x++;  
    };

// Número máximo de linhas. (n pixels por linha.)
// #bugbug
// Tem um scroll logo acima que considera um valor
// de limite diferente desse.

    if ( CONSOLE_TTYS[n].cursor_y >= (CONSOLE_TTYS[n].cursor_bottom) )  
    { 
        debug_print ("console_outbyte: scroll 3\n"); 

        if (CONSOLE_TTYS[n].fullscreen_flag == TRUE ){
            console_scroll(n);
        }

        CONSOLE_TTYS[n].cursor_x = 0;  //CONSOLE_TTYS[n].cursor_left;
        CONSOLE_TTYS[n].cursor_y = (CONSOLE_TTYS[n].cursor_bottom -1);
    }

// Imprime os caracteres normais.
// Nesse momento imprimiremos os caracteres.
// Imprime os caracteres normais.
// Atualisa o prev.

draw:
    __ConsoleOutbyte(Ch,n);
    prev = Ch;
}


// worker
// __ConsoleOutbyte:
// Outputs a char on the console device;
// Low level function to draw the char into the screen.
// it calls the embedded window server.
// #test
// Tentando pegar as dimensões do char.
// #importante: 
// Não pode ser 0, pois poderíamos ter divisão por zero.
// Called by console_outbyte().

static void __ConsoleOutbyte (int c, int console_number)
{
// Arguments.
    register int Ch = c;
    int n = (int) console_number;

    int cWidth = get_char_width();
    int cHeight = get_char_height();

    // #debug
    // debug_print ("__ConsoleOutbyte:\n");


    // #todo: Check verflow
    //if (n < 0)
    //{
    //    debug_print ("console_outbyte: n\n");
    //    return;
    //}

    if ( n < 0 || n >= CONSOLETTYS_COUNT_MAX  )
    {
        debug_print ("__ConsoleOutbyte: [FAIL] n\n");
        x_panic     ("__ConsoleOutbyte: [FAIL] n\n");
    }

    if ( cWidth == 0 || cHeight == 0 )
    {
        debug_print ("__ConsoleOutbyte: char w h\n");
        x_panic     ("__ConsoleOutbyte: fail w h");
    }

// #bugbug
// Caso estejamos em modo texto.
// Isso ainda não é suportado.

    //if ( VideoBlock.useGui != TRUE )
    if ( VideoBlock.useGui == FALSE )
    {
        debug_print ("__ConsoleOutbyte: kernel in text mode\n");
        x_panic     ("__ConsoleOutbyte: kernel in text mode\n");
    }

// #Importante: 
// Essa rotina não sabe nada sobre janela, ela escreve na tela como 
// um todo. Só está considerando as dimensões do 'char'.
// Caso estivermos em modo gráfico.
// #importante: 
// Essa rotina de pintura deveria ser exclusiva 
// para dentro do terminal.
// Então essa flag não faz sentido.
// See: char.c

    if ( VideoBlock.useGui == TRUE )
    {
        // ## NÃO TRANPARENTE ##
        // Se estamos no modo terminal então usaremos as cores 
        // configuradas na estrutura do terminal atual.
        // Branco no preto é um padrão para terminal.
        if ( stdio_terminalmode_flag == 1 ){
            d_draw_char ( 
                 (cWidth * CONSOLE_TTYS[n].cursor_x), 
                (cHeight * CONSOLE_TTYS[n].cursor_y), 
                Ch, COLOR_WHITE, 0x303030 );

        // ## TRANSPARENTE ##
        // Se não estamos no modo terminal então usaremos
        // char transparente.
        // Não sabemos o fundo. Vamos selecionar o foreground. 
        }else{
            d_drawchar_transparent ( 
                (cWidth  * CONSOLE_TTYS[n].cursor_x), 
                (cHeight * CONSOLE_TTYS[n].cursor_y), 
                CONSOLE_TTYS[n].fg_color, 
                Ch );
        };
        // Nothing.
    }
}


/*
 * console_putchar:
 *     Put a char into the screen of a virtual console.
 *     pinta no backbuffer e faz refresh apenas do retangulo do char.
 */
// #importante
// Colocamos um caractere na tela de um console virtual.
// #bugbug: 
// Como essa rotina escreve na memória de vídeo,
// então precisamos, antes de uma string efetuar a
// sincronização do retraço vertical e não a cada char.

void console_putchar ( int c, int console_number )
{

// Getting char info.
    int cWidth = get_char_width();
    int cHeight = get_char_height();

    if ( cWidth == 0 || cHeight == 0 )
    {
        panic ("console_putchar: char\n");
    }

// flag on.
    stdio_terminalmode_flag = TRUE;

// #todo
// Check these limits.
// Console limits
// CONSOLETTYS_COUNT_MAX
// See: tty.h

    if ( console_number < 0 || console_number > 3 )
    {
        panic ("console_putchar: console_number\n");
    }

// Draw the char into the backbuffer and
// Copy a small rectangle to the framebuffer.

    //if( c != 0)
    console_outbyte ( (int) c, console_number );

    refresh_rectangle ( 
        (CONSOLE_TTYS[console_number].cursor_x * cWidth), 
        (CONSOLE_TTYS[console_number].cursor_y * cHeight), 
        cWidth, 
        cHeight );

// flag off
    stdio_terminalmode_flag = FALSE; 
}


// Coloca no prompt[] para ser comarado.
// Talvez o prompt também seja o buffer de stdin
int consoleInputChar( int c )
{
    unsigned long ascii=0;
    ascii = (unsigned long) (c & 0xFF);

    return (int) kinput(ascii);
}


void __dummy_thread(void)
{
    while(1){}
}

void __test_process(void)
{
    struct process_d *p;

    // Wrapper
    // Only ring3 for now.
    // See: sys.c
    p = (void*) sys_create_process ( 
            NULL, NULL, NULL,       // room, desktop, window
            0,                      // Reserved
            PRIORITY_HIGH,          // priority
            get_current_process(),  // ppid
            "no-name",              // name
            RING3 );                // iopl 

    if( (void*)p==NULL ){
        printf("p fail\n");
        return;
    }

    //show_process_information();
        
// ok, it is working.
// Create and initialize a process structure.

    //__create_and_initialize_process_object();

}


//#test
//Creating a ring0 thread.
//#bugbug: We're having problems with ring0 context swtitching.
void __test_thread(void)
{
    struct thread_d *t;

    t = 
        (struct thread_d *) create_thread ( 
                                NULL, NULL, NULL,   //room desktop window 
                                __dummy_thread, //init_rip, 
                                PRIORITY_HIGH, 
                                get_current_process(), 
                                "no-name",
                                RING0 ); 

    if( (void*)t==NULL ){
        printf("fail\n");
        return;
    }

    //show_slots();
}


// =====================================

// Compare the strings that were
// typed into the kernel virtual console.
int consoleCompareStrings(void)
{
    int status=0;
    int fpu_status = -1;

    debug_print("consoleCompareStrings: \n");
    printf("\n");


// ========
// exit
// Exit the kernel console.
    if ( strncmp(prompt,"exit",4) == 0 )
    {
        exit_kernel_console(); 
        goto exit_cmp;
    }

// #note
// The is already doing that in the initialization.
    if ( strncmp(prompt,"fpu",3) == 0 )
    {
        printf("Initialize fpu support\n");
        fpu_status = x64_init_fpu_support();
        if(fpu_status<0){
            printf("Initialization fail\n");
        }
        printf("done\n");
        goto exit_cmp;
    }

    // See: x64.c
    if ( strncmp( prompt, "smp", 3 ) == 0 )
    {
        // #suspended
        // We're making this test during the kernel initialization.
        // See: init_hal() in hal.c
        //smp_probe();
        printf("#suspended: See init_hal() in hal.c\n");
        goto exit_cmp;
    }

    // disk
    // See: ata.c
    if ( strncmp( prompt, "disk", 4 ) == 0 ){
        printf("disk: Show ide info:\n");
        //show_ide_info();
        ata_show_device_list_info();
        goto exit_cmp;
    }


// device list
    if( strncmp(prompt,"device",6) == 0 )
    {
        printf("tty devices:\n");
        devmgr_show_device_list(ObjectTypeTTY);
        printf("pci devices:\n");
        devmgr_show_device_list(ObjectTypePciDevice);
        printf("devices with regular files:\n");
        devmgr_show_device_list(ObjectTypeFile);
        //...
        goto exit_cmp;
    }


// ========
// 'about'
    if ( strncmp( prompt, "about", 5 ) == 0 ){
        printf("About: The kernel console\n");
        goto exit_cmp;
    }

// ========
// 'cls'
    if ( strncmp( prompt, "cls", 3 ) == 0 )
    {
        //backgroundDraw(COLOR_BLACK);
        backgroundDraw(COLOR_EMBEDDED_SHELL_BG);
        set_up_cursor(1,1);
        goto exit_cmp;
    }

// ========
// 'cpu'
    if ( strncmp( prompt, "cpu", 3 ) == 0 ){
        x64_info();
        goto exit_cmp;
    }

// ========
// 'help'
    if ( strncmp( prompt, "help", 4 ) == 0 ){
        printf("Commands: about, help, reboot, ...\n");
        goto exit_cmp;
    }

// ========
// 'memory'
    if ( strncmp( prompt, "memory", 6 ) == 0 ){
        memoryShowMemoryInfo();
        goto exit_cmp;
    }

// ========
// 'path'
    if ( strncmp(prompt,"path",4) == 0 )
    {
        __test_path();
        goto exit_cmp;
    }

// ========
// 'process'
    if ( strncmp( prompt, "process", 7 ) == 0 )
    {
        __test_process();
        goto exit_cmp;
    }


// ========
// 'ps2'
// Testing the full initialization of ps2 interface.
// This is a work in progress.
// See: dev/i8042.c
    if ( strncmp( prompt, "ps2", 3 ) == 0 )
    {
        printf("[Test]: Full ps2 full initialization!\n");
        PS2_initialization();
        goto exit_cmp;
    }

// ========
// 'reboot'
    if ( strncmp( prompt, "reboot", 6 ) == 0 ){
        hal_reboot();
        goto exit_cmp;
    }


// ========
// 'thread'
    if ( strncmp( prompt, "thread", 6 ) == 0 )
    {
        __test_thread();
        goto exit_cmp;
    }

// ========
// 'time'
    if ( strncmp( prompt, "time", 4 ) == 0 )
    {
        printf ("Init stime %d\n",InitThread->stime);
        printf ("Init utime %d\n",InitThread->utime);
        goto exit_cmp;
    }

// ========
// 'tty'
    char data0[8];
    data0[0]='a';
    data0[1]='b';
    data0[2]='c';
    data0[3]=0;

    char data1[8];
    data1[0]='x';
    data1[1]='y';
    data1[2]='z';
    data1[3]=0;

    if ( strncmp( prompt, "tty", 3 ) == 0 )
    {
        __tty_write(KernelProcess->tty,data0,3); //write
        __tty_read (KernelProcess->tty,data1,3); //read
        printf("%c\n",data1[0]);
        printf("%c\n",data1[1]);
        printf("%c\n",data1[2]);
        goto exit_cmp;
    }


// ========
// 'wm'
// Send input to the window manager
// inside the window server (gwssrv.bin).
// See: kgwm.c

    if ( strncmp( prompt, "wm", 2 ) == 0 )
    {
        if ( gUseWMCallbacks != TRUE )
            goto exit_cmp;

        // See: swlib.asm
        // Setup parameters
        //wmData_RDI = 0;
        //wmData_RSI = MSG_SYSKEYDOWN;  //MSG_KEYDOWN;
        //wmData_RDX = VK_F1;           //3;
        //wmData_RCX = 4;
        // Trampoline
        //wmWindowMananer_SendMessage();
 
        //#test
        //wmSendInputToWindowManager(0,9092,0,0);  // update desktop
        //wmSendInputToWindowManager(0,9093,0,0);    // ramdom tests
        //wmSendInputToWindowManager(0,0,0,0);
        //wmSendInputToWindowManager(0,0,0,0);

        goto exit_cmp;
    }

// ========
// 'close'
// msg:
    if ( strncmp(prompt,"close",5) == 0 )
    {
        if( (void*) InitThread == NULL ){goto exit_cmp;}
        post_message_to_tid(
            InitThread->tid,
            NULL,  //window
            MSG_CLOSE,  //msg code
            0,
            0 );
        goto exit_cmp;
    }

// ========
// 'app1'
// msg:
    if ( strncmp(prompt,"app1",4) == 0 )
    {
        if( (void*) InitThread == NULL ){goto exit_cmp;}
        post_message_to_tid(
            (int) InitThread->tid,
            NULL,  //window
            (int)MSG_COMMAND,  //msg code
            4001,
            0 );
        printf("app1: done\n");
        //refresh_screen();
        goto exit_cmp;
    }

// ========
// 'app2'
// msg:
    if ( strncmp(prompt,"app2",4) == 0 )
    {
        if( (void*) InitThread == NULL ){goto exit_cmp;}
        post_message_to_tid(
            (int) InitThread->tid,
            NULL,  //window
            (int)MSG_COMMAND,  //msg code
            4002,
            0 );
        printf("app2: done\n");
        //refresh_screen();
        goto exit_cmp;
    }

// ========
// 'app3'
// msg:
    if ( strncmp(prompt,"app3",4) == 0 )
    {
        if( (void*) InitThread == NULL ){goto exit_cmp;}
        post_message_to_tid(
            (int) InitThread->tid,
            NULL,  //window
            (int)MSG_COMMAND,  //msg code
            4003,
            0 );
        printf("app3: done\n");
        //refresh_screen();
        goto exit_cmp;
    }

//
// Invalid
//

    printf("\n");
    printf ("Error: Command not found!\n");
    printf("\n");

exit_cmp:
   //nothing
done:
    consolePrompt();
    return 0;
}


/*
 * consolePrompt:
 *     Inicializa o prompt.
 */
// Clean prompt buffer.
// Print the prompt string.
 
void consolePrompt (void)
{
    register int i=0;
    
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){ 
        prompt[i] = (char) '\0'; 
    };

    prompt[0] = (char) '\0';
    prompt_pos    = 0;
    prompt_status = 0;
    prompt_max    = PROMPT_MAX_DEFAULT;  

    printf("\n");
    printf("$ ");

    refresh_screen();
    //invalidate_screen();
}


// No escape sequence support.
ssize_t 
__console_write ( 
    int console_number, 
    const void *buf, 
    size_t count )
{

// #todo
// #bugbug
// Precisamos checar os limites para o buffer.
// Não podemos aceitar escrever um numero muito grande
// de bytes num buffer qualquer, correndo o risco
// sujarmos alguma área importante.

// Arguments.
    int n = (int) console_number;
    char *data = (char *) buf;
    size_t MaxSize = (size_t) count;

    register size_t i=0;
    char ch=0; 

// Console number
    if ( n < 0 || n > 3 )
    {
       printf ("__console_write: n\n");
       goto fail;
    }
// Buffer pointer
    if ( (void *) buf == NULL )
    {
        printf ("__console_write: buf\n");
        goto fail;
    }
// Max size.
    //if (count==0 || count > ?)
    if(!count)
    {
        printf ("__console_write: count\n");
        goto fail;
    }

// ====================
// Write string

    for (i=0; i<MaxSize; i++){
        console_putchar ( (int) data[i], (int) n );
    };

// Return the counter.
    return (ssize_t) MaxSize;

fail:
    refresh_screen();
    return (ssize_t) (-1);
}


// #todo
// Isso é importante.
// Pegar input na estrutura de console do kernel.

ssize_t 
console_read ( 
    int console_number, 
    const void *buf, 
    size_t count )
{
    debug_print ("console_read: [TODO]\n");
    return -1;  //todo
}


/*
 * console_write:
 * 
 */
// Called by sys_write() in sys.c.
// Tem escape sequence
// console number, buffer, size.

// IN: 
ssize_t 
console_write ( 
    int console_number, 
    const void *buf, 
    size_t count )
{
    // loop
    int i=0;
    
    char ch=0; 
    char *data = (char *) buf;
    size_t StringSize=0;


    //debug_print ("console_write: [test]\n");

    // Console number
    if ( console_number < 0 || console_number > 3 )
    {
        printf ("console_write: [FAIL] console_number\n");
        goto fail;
    }

    // Buffer
    if ( (void *) buf == NULL ){
        printf ("console_write: buf\n");
        goto fail;
    }

    // Count
    if (!count){
        printf ("console_write: count\n");
        goto fail;
    }

//
// Write string
//   

// Isso eh o contador de estagios do escape sequence.
// Vamos percorret todos os bytes da sequencia quando
// encontrarmos o marcador.
// #todo
// Esse marcador de estagio deve ser especifico para
// cada console. CONSOLE[i].esc_stage

    __EscapeSequenceStage = 0; 

     StringSize = count;

    for (i=0; i<StringSize; i++)
    {
        // Get next char from the string.
        ch = data[i];

        // Select the stage in the escape sequence.
 
        switch (__EscapeSequenceStage){

            //================================================
            // Stage 0
            // Nao entramos em uma escape sequence.
            case 0:
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '0',console_number);
                //console_putchar ( '\n',console_number);

               // Is printable?
               if (ch >31 && ch <127){
                    console_putchar ( ch, console_number );
               
               // >>>> [ Escape ]
               // Entramos em uma escape sequence,
               // entao o proximo case inicia o tratamento da escape sequence.
               } else if (ch==27){
                   __EscapeSequenceStage=1;  // <<<<<<<--

               // ?? \n
               }else if (ch==10 || ch==11 || ch==12){
                   console_putchar ( ch, console_number );

               // Enter ? cr \n
               }else if (ch==13){ 
                   console_putchar ( ch, console_number ); 

               // Backspace
               }else if (ch==8) {
                   console_putchar ( ch, console_number );

               // Tab.S. horizontal tab
               } else if (ch==9) {
                   console_putchar ( ch, console_number ); 
               };
               break;
            
            //================================================
            // Stage 1
            // Acabamos de entrar na escape sequence.
            // Vamos checar o primeiro char.
            case 1:
            
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '1',console_number);
                //console_putchar ( '\n',console_number);
            
                // Zerando o marcador de estagio.
                // Isso porque o estagio mudara dependendo do char encontrado agora.
                __EscapeSequenceStage=0; 
                
                // '['
                // CSI.    '0x1b['
                if (ch=='['){
                    __EscapeSequenceStage = 2;
                
                // >>> nao eh csi ... o 'E' esta no lugar do '['
                
                }else if (ch=='E'){ 
                    __local_gotoxy ( 0, (CONSOLE_TTYS[console_number].cursor_y + 1), console_number );
                }else if (ch=='M'){
                    __local_ri ();   //scroll. deixa pra depois. kkk
                }else if (ch=='D'){
                    console_putchar ( ch, console_number );  //lf();
                }else if (ch=='Z'){
                    __respond (console_number);    //test
                
                //??
                // tivemos um 0x1b e o cursor esta em determinado lugar.
                }else if ( CONSOLE_TTYS[console_number].cursor_x == '7'){   //?? What L.T.
                    __local_save_cur (console_number);
                
                //??
                // tivemos um 0x1b e o cursor esta em determinado lugar.
                }else if ( CONSOLE_TTYS[console_number].cursor_x == '8' ){  //?? What L.T.
                    __local_restore_cur (console_number);
                };
                break;

            //================================================
            // Stage 2
            // Chegamos aqui depois de encontrarmos um CSI. '0x1b['
            // O que vem apos o '[' sao parametros separados por delimitadores
            // e terminados com um 'm'. 
            case 2:
            
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '2',console_number);
                //console_putchar ( '\n',console_number);
 
                // Limpando o array de parametros.
                for ( npar=0; npar<NPAR; npar++ ){ par[npar]=0; };
                npar=0;
                //Mudando de estago para checar os parametros.
                __EscapeSequenceStage=3;  // Next state.
                
                //Se o primeiro char apos o '[' for um '?'
                // entao vamos para o proximo estagio, mas quebraremos 
                // par ao for pegar o proximo char.
                // Caso contrario vamos para o proximo estago sem pegarmos o proximo char?
                if ( ques = ( ch == '?' ) ) 
                    break;

            //================================================
            // Stage 3
            case 3:
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '3',console_number);
                //console_putchar ( '\n',console_number);
            
                // Se encontramos um delimitador
                // e ainda nao acabou o array usado para parametros.
                // entao avançamos para o proximo char nos parametros.
                if ( ch == ';' && 
                     npar < NPAR-1) 
                {
                    // Avançamos, mas quebramos para que o for pegue
                    // o proximo char da string.
                    //#bugbug: Não moda de state??
                    npar++;  break;  

                // Isso nao eh um delimitador.
                // Checamos se eh um numero.
                } else if ( ch >= '0' && ch <='9'){

                    // Sim eh um numero.
                    // #bugbug?
                    // Multiplicamos o que estava no buffer por 10.
                    // Mas nem sei o que ja estava no buffer??
                    // porque fizemos isso ?
                    // o buffer provavelmente esta vazio no primeiro numero.
                    // Sendo assim qeubramos para tentarmos pegar mais numeros no for.
                    par[npar] = 10 * par[npar] + ch - '0';
                    break;

                 // Nao eh um delimitador nem um numero.
                 // entao vamos para o proximo estagio
                 // porque provavelmente eh uma letra.
                 // Nao precisamos quebrar, pois ja temos um char.
                 } else { 
                     __EscapeSequenceStage = 4;
                 }

            // Stage 4
            case 4:
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '4',console_number);
                //console_putchar ( '\n',console_number);

                // Zerando o marcador de estagio.
                // Significa que se quebrarmos, vamos voltar para o estagio zero.
                // No estagio zero estamos fora da escape sequence.
 
                __EscapeSequenceStage=0;
                
                switch (ch){

                    // mudamos o cursor e saimos da escape sequence
                    case 'G': case '`':
                        if (par[0]){  par[0]--;  }
                        __local_gotoxy ( 
                            par[0], 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        break;

                    // Mudamos o cursor e saimos da escape sequence
                    case 'A':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x,  
                            CONSOLE_TTYS[console_number].cursor_y - par[0], 
                            console_number );
                        break;

                    case 'B': case 'e':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x, 
                            CONSOLE_TTYS[console_number].cursor_y + par[0], 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence 
                    case 'C': case 'a':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x + par[0], 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'D':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x - par[0], 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'E':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            0, 
                            CONSOLE_TTYS[console_number].cursor_y + par[0], 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'F':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            0, 
                            CONSOLE_TTYS[console_number].cursor_y - par[0], 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'd':
                        if (par[0]){  par[0]--;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x, 
                            par[0], 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'H': case 'f':
                        if (par[0]){  par[0]--;  }
                        if (par[1]){  par[1]--;  }
                        __local_gotoxy ( 
                            par[1],
                            par[0], 
                            console_number );
                        break;

                    // Outros tratadores.
                    case 'J': csi_J  (par[0]);                 break;
                    case 'K': csi_K  (par[0]);                 break;
                    case 'L': csi_L  (par[0], console_number); break;
                    case 'M': csi_M  (par[0], console_number); break;
                    case 'P': csi_P  (par[0], console_number); break;
                    case '@': csi_at (par[0], console_number); break;


                    // FIM.
                    // Isso marca o fim da escape sequence,
                    // vamos quebrar e voltar para a string normal.
                    // Essa rotina cheaca os parametros e configura o atributo
                    // de acordo com o ultimo parametro.
                    case 'm': 
                        csi_m(); 
                        break;


                    // ??  #bugbug
                    // 0x1b[r
                    // Isso ajusta o top e o bottom.
                    case 'r':
                        if (par[0])  { par[0]--; }
                        if (!par[1]) { par[1] = CONSOLE_TTYS[console_number].cursor_bottom; }  
                        if (par[0] < par[1] &&
                            par[1] <= CONSOLE_TTYS[console_number].cursor_bottom ) 
                        {
                            // Ajuste feito por 'r'.
                            CONSOLE_TTYS[console_number].cursor_top    = par[0];
                            CONSOLE_TTYS[console_number].cursor_bottom = par[1];
                        }
                        break;

                    // Save cursor
                    case 's': 
                        __local_save_cur( console_number );
                        break;

                    // Restore cursor
                    case 'u': 
                        __local_restore_cur(console_number);
                        break;
                };
                break;

            // Stage fail
            default:
                printf ("console_write: default\n");
                goto fail;
                break;
        };
    };  // FOR 

// done:
    return (ssize_t) StringSize;
fail:
    refresh_screen();
    return -1;
}


// #bugbug
// Isso tá errado.

#define __RESPONSE  "\033[?1;2c"

void __respond (int console_number)
{
    char *p = __RESPONSE;

// #todo: max limit
    if(console_number<0){
        return;
    }

    while (*p) {
        
        //PUTCH(*p,tty->read_q);
        console_putchar ( (int) *p, console_number );
        p++;
    };

    //copy_to_cooked(tty);
}


// See:
// https://en.wikipedia.org/wiki/Control_character
// https://en.wikipedia.org/wiki/C0_and_C1_control_codes#Device_control

void __local_insert_char ( int console_number )
{

    if(console_number<0){
        return;
    }

	//int i=x;
	//unsigned short tmp,old=0x0720;
	//unsigned short * p = (unsigned short *) pos;

/*
	while (i++ < columns) {

		// Salvo o char da posição atual.
		tmp = *p;

        // coloco o char de controle na posição atual
        // ou o caractere salvo anteriomente.
		*p=old;

        // coloco o caractere salvo para uso futuro.
		old=tmp;

        //avança até o fim da linha.
		p++;
	}
*/

    //int i = CONSOLE[console_number].cursor_x;
    //int tmp;
    //int old = 0x20;
    
    // #bugbug
    // Não é possível fazer essa rotina pois não temos um buffer e chars.

    //while (i++ < CONSOLE[console_number].cursor_height ) {};
    
    console_putchar (0x20, console_number);
}



void __local_delete_char(int console_number)
{

// #todo: max limit

    if(console_number<0){
        return;
    }

    console_putchar ( ' ', console_number);

/*
	int i;
	unsigned short * p = (unsigned short *) pos;

	if (x >= columns)
		return;

	i = x;
	while (++i < columns) 
	{
		*p = *(p+1);
		p++;
	}
	*p=0x0720;
*/

}


void csi_P (int nr, int console_number)
{

    if (console_number<0){
        return;
    }

    if (nr > CONSOLE_TTYS[console_number].cursor_right -1 )
    {
        nr = CONSOLE_TTYS[console_number].cursor_right -1 ;
    } else {
        
        if (!nr)
        {
            nr = 1;
        }
    };

    if (nr<0)
        return;

    while (nr--){
        __local_delete_char(console_number);
    };
}


void csi_at (int nr, int console_number)
{

    if( console_number<0){
        return;
    }

    if (nr > CONSOLE_TTYS[console_number].cursor_right -1 )
    {
        nr = CONSOLE_TTYS[console_number].cursor_right -1 ;
    }else {
        
        if (!nr){
            nr=1;
        }
    };

    if (nr<0)
        return;

    while (nr--){
        __local_insert_char(console_number);
    };
}



// main routine.
// called by main.c

int VirtualConsole_initialize(void)
{
    register int i=0;

// No shell for now.
// No input in prompt[].

    ShellFlag = FALSE;

// Virtual Console:
// The kernel only have four virtual consoles.

    //struct tty_d *tmp_tty;

    for (i=0; i<CONSOLETTYS_COUNT_MAX; i++)
    {
        console_init_virtual_console(i);
    
        //tmp_tty = (struct tty_d *) &CONSOLE_TTYS[i];
        
        // Register tty device.
        //devmgr_register_device ( 
        //    (file *) __file, 
        //    newname,            // pathname 
        //    0,                  // class (char, block, network)
        //    1,                  // type (pci, legacy
        //    NULL,  // Not a pci device.
        //    tmp_tty );  // tty device

    };

// Setup foreground console.
    jobcontrol_switch_console(0);




// Obs: 
// O video já foi inicializado em main.c.
// Isso atualiza a estrutura de console do console atual.

// BANNER !
// Welcome message. (Poderia ser um banner.) ??

// Cursor:
// See: system.c

    set_up_cursor(0,0);

// #hackhack
// Esse trabalho não nos pertence, pertence ao stdio,
// mas funciona.

    stdio_terminalmode_flag = TRUE;
    stdio_verbosemode_flag = TRUE;

    return 0;
}


// This will be the firt message
// at the top/left corner of the screen.
void console_banner(unsigned long banner_flags)
{

// Serial
    if ( Initialization.serial_log == TRUE ){
        debug_print ("Welcome to Gramado OS!\n");
    }

// Virtual console
// #todo
// Print some more basic info
// just like the processor brand and the size of the ram.
    if( Initialization.console_log == TRUE )
    {
        set_up_cursor (0,0);
        printf ("Welcome to Gramado OS!\n");
    }
    
    refresh_screen();
}


/*
 * console_ioctl:
 * 
 */
// Podemos mudar as características de um console.

int 
console_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{
    debug_print ("console_ioctl: TODO\n");

    if ( fd < 0 || fd >= OPEN_MAX )
    {
        return (int) (-EBADF);
    }

    // #todo: Check overflow
    if (fg_console<0){
        debug_print ("console_ioctl: [ERROR] fg_console\n");
        return -1;
    }


    switch (request){

    // set fg color.
    case 400:
        CONSOLE_TTYS[fg_console].fg_color = (unsigned int) arg;
        return 0;
        break;
    // get fg color.
    case 401:
        return (int) CONSOLE_TTYS[fg_console].fg_color;
        break;
    // set bg color.
    case 402:
        CONSOLE_TTYS[fg_console].bg_color = (unsigned int) arg;
        return 0;
        break;
    // get bg color.
    case 403:
        return (int) CONSOLE_TTYS[fg_console].bg_color;
        break;
    
    // clear console.
    case 440:
        // IN: color, console number.
        clear_console( (unsigned int) arg, fg_console );
        return 0;
        break;

    //#deprecated.
    case 1000:
        return 0;
        break;

    // cursor x position
    // #bugbug #todo  limits
    case 1001:
        CONSOLE_TTYS[fg_console].cursor_x = 0;
        return 0;
        break;

    // cursor y position
    // #bugbug #todo  limits
    case 1002:
        CONSOLE_TTYS[fg_console].cursor_y = 0;
        return 0;
        break;

    // switching the current virtual console.
    // We have onlu 4 virtual consoles.
    case 1003:
        if ( arg >= 0 && 
             arg < CONSOLETTYS_COUNT_MAX )
        { 
            fg_console = arg;
            return 0; 
        }
        return (int) (-EINVAL);
        break;

    // #todo:
    // There is no fflush here in ring0.
    // The ring3 libc is doing this job using write.
    case TCIFLUSH:
        debug_print ("console_ioctl: [TEST] flush\n");
        break;
        
    // #todo: Yes, we can return data from the console tty termios. 
    // case TCGETS:
    // ...
    
    default:
        debug_print ("console_ioctl: [TODO] request\n");
        return (int) (-EINVAL);
        break;
    };

    return -1;
}


/*
 * REFRESH_STREAM:
 * 
 *     #IMPORTANTE
 *     REFRESH SOME GIVEN STREAM INTO TERMINAL CLIENT WINDOW !!
 */

// #todo
// Change this name. 
// Do not use stream in the base kernel.

void REFRESH_STREAM ( file *f )
{
    int i=0;
    int j=0;
    char *ptr;

    debug_print("console.c-REFRESH_STREAM: [FIXME] It is wrong!\n");

// char width and height.
    int cWidth  = get_char_width();
    int cHeight = get_char_height();
    
    if ( cWidth == 0 || cHeight == 0 ){
        panic ("REFRESH_STREAM: [FAIL] char w h\n");
    }

    j = (80*25);

// File
// #bugbug
// Tem que checar a validade da estrutura e do ponteiro base.

    if ( (void *) f == NULL ){ 
        panic ("REFRESH_STREAM: [FAIL] f\n");
    }

// Pointer

    ptr = f->_base;

// #bugbug
// Tem que checar a validade da estrutura e do ponteiro base.

    //if ( (void *) c == NULL ){ ? }

// Seleciona o modo terminal.


//++
    stdio_terminalmode_flag = TRUE; 
    for ( i=0; i<j; i++ )
    {
        printf ("%c", *ptr );

        // #bugbug
        // It is very wrong!
        
        refresh_rectangle ( 
            (CONSOLE_TTYS[fg_console].cursor_x * cWidth), 
            (CONSOLE_TTYS[fg_console].cursor_y * cHeight),  
            cWidth, 
            cHeight );

        ptr++;
    };
    stdio_terminalmode_flag = FALSE; 
//--
}


// kclear:
//     Clear console.
// #todo: change the name of the function.

int clear_console (unsigned int color, int console_number)
{

// #todo: max limit.
    if (console_number<0){
        return -1;
    }
    if ( VideoBlock.useGui != TRUE ){
        return -1;
    }
    backgroundDraw (color);
    CONSOLE_TTYS[console_number].cursor_x = 0;
    CONSOLE_TTYS[console_number].cursor_y = 0;
    return 0;
}


