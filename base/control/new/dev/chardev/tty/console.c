
// console.c

#include <kernel.h>

// Fullscreen kernel console.
// Handmade by the kernel at the initialization.
// see: tty.h
struct tty_d  CONSOLE_TTYS[CONSOLETTYS_COUNT_MAX];

// Main consoles.
struct tty_d  *console0_tty;
struct tty_d  *console1_tty;
struct tty_d  *console2_tty;
struct tty_d  *console3_tty;


// 
// Imports
//

// used for handling screen dimensions.
//extern unsigned long gSavedX;
//extern unsigned long gSavedY;

#define __RESPONSE  "\033[?1;2c"

// Se o console esta atuando como um shell comparando palavras.
int ShellFlag=FALSE;

// global
// Foreground console.
int fg_console=0;
// 0=apaga 1=acende 
int consoleTextCursorStatus=0;
// Cursor
static int saved_x=0;
static int saved_y=0;

// Esse eh o marcador de estagio do escape sequence.
// Usado para manipular csi
static unsigned long __EscapeSequenceStage = 0;

// Array de parâmetros.
#define NPAR  16
static unsigned long par[NPAR];
static unsigned long npar = 0;
static unsigned long ques = 0;
static unsigned char attr = 0x07;


static unsigned long console_interrupt_counter=0;

//
// == Private functions: Prototypes ======================
//

static void __ConsoleOutbyte (int c, int console_number);
static void __test_path(void);
static void __test_tty(void);
// #todo: Use static modifier.
void __local_ri(void);
void csi_J(int par);
void csi_K(int par);
void csi_m(void);
void csi_M(int nr, int console_number);
void csi_L(int nr, int console_number);

static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 );

// =======================

static void __test_path(void)
{
// Test the pathname support.

    int status = -1;
    //unsigned long tmp_size = (512*4096);    // 512*4096 = 2MB
    void *b; //= (void *) allocPages ( 512 );

// ===================================
// #test: 
// Testando carregar usando path.
// #bugbug:
// We have only few pre-allocated buffers,
// so, we only can use four levels for now. (/../../../file.txt)

// Valid shapes
    //char PathAddress[] = "/GRAMADO/TEST.BMP";
    //char PathAddress[] = "/GRAMADO.TXT";
    //char PathAddress[] = "/GRAMADO/FOLDER/TEST.TXT";

// :)
// 4 levels
    char PathAddress[] = "/GRAMADO/FOLDER/FOLDER2/TEST2.TXT";

// Invalid folder name
    //char PathAddress[] = "/GRAMADO///FOLDER/";
    //char PathAddress[] = "/GRAMADO/1234567812345456456/";

// =========================================
// (32*4096) bytes

    //unsigned long BufferSize = (32*4096);
    //b = (void *) allocPages(32); 

// It is a simple text file.
// We don't need too much memory.
// #bugbug: 
// The loader is not getting the file size
// from the fat entry.
    unsigned long BufferSize = (4096);  //One page!

    b = (void *) allocPages(1); 
    if ( (void*) b == NULL ){
        printf("b fail\n");
        return;
    }

// see: fsload.c
// IN: path, address, buffer size in bytes.
    status = 
        (int) fs_load_path ( 
                  (const char*) PathAddress, 
                  (unsigned long) b,
                  (unsigned long) BufferSize ); 
    if (status<0){
        printf("__test_path: fs_load_path fail\n");
        return;
    }
    if ( (void*)b != NULL ){
        printf("OUTPUT: {%s}\n",b);
    }
}

void __local_ri(void)
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
    if (console_number<0 || console_number > 3){
        return;
    }

// Maior que o largura da linha.
    if (new_x > CONSOLE_TTYS[console_number].cursor_right)
    {
        //new_x = CONSOLE_TTYS[console_number].cursor_right;
        return;
    }

// Maior que a altura da coluna.
    if (new_y > CONSOLE_TTYS[console_number].cursor_bottom)
    {
        //new_y = CONSOLE_TTYS[console_number].cursor_bottom;
        return;
    }

// Set x.
    CONSOLE_TTYS[console_number].cursor_x = 
        (unsigned long) (new_x & 0xFFFFFFFF);

// Set y.
    CONSOLE_TTYS[console_number].cursor_y = 
        (unsigned long) (new_y & 0xFFFFFFFF);
}

void __local_save_cur(int console_number)
{
    saved_x = (int) CONSOLE_TTYS[console_number].cursor_x;
    saved_y = (int) CONSOLE_TTYS[console_number].cursor_y;
}

void __local_restore_cur(int console_number)
{
    if (console_number<0 || console_number >3){
        return;
    }

    CONSOLE_TTYS[console_number].cursor_x = 
        (unsigned long) (saved_x & 0xFFFF);

    CONSOLE_TTYS[console_number].cursor_y = 
        (unsigned long) (saved_y & 0xFFFF);
}

void __local_insert_line(int console_number)
{
    int oldtop = 0;
    int oldbottom = 0;

    if (console_number<0 || console_number >3){
        return;
    }

    oldtop    = CONSOLE_TTYS[console_number].cursor_top;
    oldbottom = CONSOLE_TTYS[console_number].cursor_bottom;

    CONSOLE_TTYS[console_number].cursor_top = 
        CONSOLE_TTYS[console_number].cursor_y;

    //#bugbug: apontando par asi mesmo.
    //CONSOLE[console_number].cursor_bottom = CONSOLE[console_number].cursor_bottom;

    //if (console_number<0)
        //return;

    if (CONSOLE_TTYS[console_number].fullscreen_flag == TRUE){
        console_scroll(console_number);
    }

    CONSOLE_TTYS[console_number].cursor_top = oldtop;
    CONSOLE_TTYS[console_number].cursor_bottom = oldbottom;
}

void __local_delete_line(int console_number)
{
    int n=0;
    int oldtop = 0;
    int oldbottom = 0;

// #todo: max limit
    if (console_number<0){
        return;
    }

    n = console_number;

// save old.
    oldtop    = (int) CONSOLE_TTYS[n].cursor_top;
    oldbottom = (int) CONSOLE_TTYS[n].cursor_bottom;

    CONSOLE_TTYS[n].cursor_top = 
        (int) CONSOLE_TTYS[n].cursor_y;

// #bugbug: apontando para si mesmo.
    //CONSOLE[n].cursor_bottom = CONSOLE[n].cursor_bottom;

//#todo
    //scrup();

    CONSOLE_TTYS[n].cursor_top = oldtop;
    CONSOLE_TTYS[n].cursor_bottom = oldbottom;
}

void csi_J(int par)
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


// apagar n bytes na mesma linha
void csi_K(int par)
{
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
// Set some attributes based on the parameters found.
// Sets colors and style of the characters.

    register int i=0;
    int max = (int)(npar & 0xFFFFFFFF);
    int ivalue=0;

// #bugbug
// Check 'npar'

    if (max == 0){
        return;
    }

    for (i=0; i <= max; i++)
    {
        // Get the parameter value.
        ivalue = par[0];
        ivalue = (ivalue & 0xFF);
        ivalue = k_atoi(&ivalue);

        // #todo
        // Call a worker for each of these parameters.
        //console_set_parameter(ivalue);
    };
}

void csi_M (int nr, int console_number)
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
// console_interrupt:
// Called by devices that are not block devices.
// Probably keyboard and serial devices.
// See: keyboard.c and serial.c
// Called by DeviceInterface_PS2Keyboard() in ps2kbd.c
// IN:
// #todo: Explain the parameters.

void 
console_interrupt(
    int target_thread, 
    int device_type, 
    int data )
{
// Devece drivers will call this routine to process the data.
// The data is a 'char'.

    // # Not in use.
    tid_t target_tid = (tid_t) target_thread;

    int DeviceType = device_type;
    int Data = data;
    int Status=-1;

    console_interrupt_counter++;

    // # Not in use.
    if (target_tid < 0 || target_tid >= THREAD_COUNT_MAX){
        debug_print ("console_interrupt: target_tid\n");
        goto fail;
    }


    switch (DeviceType){

        // keyboard
        // data =  raw byte.
        // See: kgws.c
        case CONSOLE_DEVICE_KEYBOARD:
            debug_print("console_interrupt: Input from keyboard device\n");
            // In this case the target tid is the window server.
            // IN: scancode, prefix.
            // #bugbug: No prefix always. We need a prefix.
            Status =  (int) wmKeyEvent( Data, (int) 0 );
            if (Status<0){
                goto fail;
            }
            break;

        // COM port
        case CONSOLE_DEVICE_SERIAL:
            debug_print("console_interrupt: Input from serial device\n");
            break;
 
        //network device.
        case CONSOLE_DEVICE_NETWORK:
            debug_print("console_interrupt: Input from network device\n");
            break;

        // ...

        default:
            debug_print("console_interrupt: Undefined input device\n");
            goto fail;
            break;
    };

// done
    return;

fail:
    debug_print ("console_interrupt: Fail\n");
    return;
}

// Initializar virtual console.
// Inicializa a estrutura de console virtual
// configura uma entrada no diretorio dev/
void 
console_init_virtual_console(
    int n, 
    unsigned int bg_color, 
    unsigned int fg_color )
{
// Initialize a given console.
// #todo: We can pass more parameters.

    register int ConsoleIndex = -1;
    register int i=0;

    debug_print ("console_init_virtual_console:\n");

/*
// Char width and height
    int cWidth  = get_char_width();
    int cHeight = get_char_height();
    if ( cWidth == 0 || cHeight == 0 ){
        x_panic ("console_init_virtual_console: cWidth cHeight");
    }
*/

// #todo #bugbug
// determinado: 8 = char size.
// #todo: Use cWidth and cHeight.
    unsigned long screen_width_in_chars = (unsigned long) (gSavedX/8);
    unsigned long screen_height_in_chars = (unsigned long) (gSavedY/8);

// Limits
    ConsoleIndex = (int) n;
    if (ConsoleIndex < 0 || ConsoleIndex >= CONSOLETTYS_COUNT_MAX){
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

// Cursor dimentions in pixel.
// #bugbug: determinado
    CONSOLE_TTYS[ConsoleIndex].cursor_width_in_pixels = 8; 
    CONSOLE_TTYS[ConsoleIndex].cursor_height_in_pixels = 8;

// Cursor position in chars.
    CONSOLE_TTYS[ConsoleIndex].cursor_x = 0;
    CONSOLE_TTYS[ConsoleIndex].cursor_y = 0;

// Cursor limits

// Full screen
    CONSOLE_TTYS[ConsoleIndex].fullscreen_flag = TRUE;
    CONSOLE_TTYS[ConsoleIndex].cursor_left = 0;
    CONSOLE_TTYS[ConsoleIndex].cursor_top  = 0;
    CONSOLE_TTYS[ConsoleIndex].cursor_right = screen_width_in_chars;
    CONSOLE_TTYS[ConsoleIndex].cursor_bottom = screen_height_in_chars;

// Everyone has the same color.
// White on black.
    CONSOLE_TTYS[ConsoleIndex].bg_color = bg_color;
    CONSOLE_TTYS[ConsoleIndex].fg_color = fg_color;

/*
// Default colors.
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
*/

    //#todo
    // Buffers !!!
    //CONSOLE_TTYS[ConsoleIndex]._rbuffer ...
    //CONSOLE_TTYS[ConsoleIndex]._cbuffer ...    

    CONSOLE_TTYS[ConsoleIndex].termios.c_lflag = ECHO;

    //CONSOLE_TTYS[ConsoleIndex].vc_mode = 0;

//
// Charset support.
//

// see:
// https://man7.org/linux/man-pages/man7/charsets.7.html

    CONSOLE_TTYS[ConsoleIndex].charset_lowercase = (void*) map_abnt2;
    CONSOLE_TTYS[ConsoleIndex].charset_uppercase = (void*) shift_abnt2;
    CONSOLE_TTYS[ConsoleIndex].charset_controlcase = (void*) ctl_abnt2;

    CONSOLE_TTYS[ConsoleIndex].charset_size = 
        (size_t) ABNT2_CHARMAP_SIZE;

// charset name

    size_t name_size = (size_t) strlen(ABNT2_CHARMAP_NAME);

    memset(
        CONSOLE_TTYS[ConsoleIndex].charset_name,
        0,
        64);
    strncpy( 
        CONSOLE_TTYS[ConsoleIndex].charset_name,
        ABNT2_CHARMAP_NAME,
        name_size );
    
    CONSOLE_TTYS[ConsoleIndex].charset_name_size = 
        (size_t) name_size;

// ascii, unicode ...
    CONSOLE_TTYS[ConsoleIndex].charset_id = 0;

// language id.
    CONSOLE_TTYS[ConsoleIndex].charset_lang_id = 0;

//
// Font support.
//

    CONSOLE_TTYS[ConsoleIndex].font_address = 
        (void*) gwsGetCurrentFontAddress();

// #bugbug
// A estrutura tem mais elementos que podem ser inicializados.
// Tivemos problemas ao tentar inicializa-los.
// ...

    switch (ConsoleIndex){
    case 0:
        console0_tty = (struct tty_d *) &CONSOLE_TTYS[0];
        break;
    case 1:
        console1_tty = (struct tty_d *) &CONSOLE_TTYS[1];
        break;
    case 2:
        console2_tty = (struct tty_d *) &CONSOLE_TTYS[2];
        break;
    case 3:
        console3_tty = (struct tty_d *) &CONSOLE_TTYS[3];
        break;
    };

    CONSOLE_TTYS[ConsoleIndex].initialized = TRUE; 
}

void console_set_current_virtual_console(int n)
{
    if (n == fg_console){
        return;
    }
    if ( n < 0 || n >= 4 ){
        debug_print ("console_set_current_virtual_console: Limits\n");
        return;
    }
    fg_console = (int) n;
}

int console_get_current_virtual_console(void)
{
    return (int) fg_console;
}


// Called by: 
// __local_ps2kbd_procedure in ps2kbd.c
// VirtualConsole_initialize in console.c
// __initialize_virtual_consoles in kstdio.c
// #todo:
// maybe we can do somo other configuration here.
// Change the foreground console.

void jobcontrol_switch_console(int n)
{
    unsigned int bg_color=COLOR_BLACK;
    unsigned int fg_color=COLOR_WHITE;

    if (n<0 || n >= CONSOLETTYS_COUNT_MAX){
        debug_print("jobcontrol_switch_console: Limits\n");
        return;
    }

// Set the current virtual console.
    console_set_current_virtual_console(n);

// Clear the screen, set bg and fg colors and set the cursor position.
// IN: bg color, fg color, console number.
    bg_color = (unsigned int) CONSOLE_TTYS[n].bg_color;
    fg_color = (unsigned int) CONSOLE_TTYS[n].fg_color;
    clear_console( bg_color, fg_color, n );

// banner
    printf ("Console number {%d}\n", n);
    refresh_screen();
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
void set_up_cursor2 ( int console_number, unsigned long x, unsigned long y );
void set_up_cursor2 ( int console_number, unsigned long x, unsigned long y )
{
    if (console_number<0){ return; }
    if (console_number>=CONSOLETTYS_COUNT_MAX){ return; }
    CONSOLE_TTYS[console_number].cursor_x = (unsigned long) x;
    CONSOLE_TTYS[console_number].cursor_y = (unsigned long) y;
}
*/

unsigned long get_cursor_x(void)
{
// In the case of called before console initialization.
    if (fg_console<0 || fg_console>=CONSOLETTYS_COUNT_MAX){
        return 0;
    }
    return (unsigned long) CONSOLE_TTYS[fg_console].cursor_x;
}

unsigned long get_cursor_y(void)
{
// In the case of called before console initialization.
    if (fg_console<0 || fg_console>=CONSOLETTYS_COUNT_MAX){
        return 0;
    }
    return (unsigned long) CONSOLE_TTYS[fg_console].cursor_y; 
}

unsigned long get_bg_color(void)
{
// In the case of called before console initialization.
    if (fg_console<0 || fg_console>=CONSOLETTYS_COUNT_MAX){
        return 0;
    }
    return (unsigned long) CONSOLE_TTYS[fg_console].bg_color;
}

unsigned long get_fg_color(void)
{
// In the case of called before console initialization.
    if (fg_console<0 || fg_console>=CONSOLETTYS_COUNT_MAX){
        return 0;
    }
    return (unsigned long) CONSOLE_TTYS[fg_console].fg_color;
}

void console_scroll(int console_number)
{
    register int i=0;
// Salvar cursor
    unsigned long OldX=0;
    unsigned long OldY=0;
// Salvar limites
    unsigned long OldLeft=0;
    unsigned long OldTop=0;
    unsigned long OldRight=0;
    unsigned long OldBottom=0;

    if (VideoBlock.useGui != TRUE){
        debug_print("console_scroll: no GUI\n");
        panic      ("console_scroll: no GUI\n");
    }

    if ( console_number < 0 || console_number >= CONSOLETTYS_COUNT_MAX ){
        panic ("console_scroll: console_number\n");
    }

// Scroll the screen rectangle.
// See: rect.c
// #todo
// Isso deveria ser apenas scroll_rectangle()
// #bugbug
// Valid only for full screen

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


// #bugbug
// cursor_bottom Isso não é a última, é o limite.
// A última é cursor_bottom-1.

// Cursor na ultima linha.
// Para podermos limpa-la.
    CONSOLE_TTYS[console_number].cursor_x = 
        CONSOLE_TTYS[console_number].cursor_left; 
    CONSOLE_TTYS[console_number].cursor_y = 
        CONSOLE_TTYS[console_number].cursor_bottom; 

// Limpa a última linha.
// #bugbug: 
// Essa rotina pode sujar alguns marcadores importantes.
// Depois disso precisamos restaurar os valores salvos

/*
   if ( CONSOLE_TTYS[console_number].cursor_left < (CONSOLE_TTYS[console_number].cursor_right-1) )
   {
       for ( i = CONSOLE_TTYS[console_number].cursor_left; 
             i < (CONSOLE_TTYS[console_number].cursor_right-1);
             i++ )
       {
           __ConsoleOutbyte(' ',console_number);
           //__ConsoleOutbyte('.',console_number); 
       };
    }
*/

// Restaura limits
    CONSOLE_TTYS[console_number].cursor_left   = (OldLeft   & 0xFFFF);
    CONSOLE_TTYS[console_number].cursor_top    = (OldTop    & 0xFFFF);
    CONSOLE_TTYS[console_number].cursor_right  = (OldRight  & 0xFFFF);
    CONSOLE_TTYS[console_number].cursor_bottom = (OldBottom & 0xFFFF);

// Reposiciona:
// Primeira coluna, última linha.
    CONSOLE_TTYS[console_number].cursor_x = 0; 
    CONSOLE_TTYS[console_number].cursor_y = 
        (CONSOLE_TTYS[console_number].cursor_bottom -1); 

// #todo:
// Essa flag permite que o taskswitch faça o refresh
// da tela.
// see: schedulerUpdateScreen() in kgwm.c
// O certo seria dispatchUpdateScreen()

    //invalidate_screen();  //#bugbug not working
    refresh_screen();
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
// + Draw char.
// + Do not refresh char.

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

    if (n < 0 || n >= CONSOLETTYS_COUNT_MAX){
        debug_print ("console_outbyte: [FAIL] n\n");
        x_panic     ("console_outbyte: [FAIL] n\n");
    }

    if (__cWidth == 0 || __cHeight == 0){
        x_panic ("console_outbyte: [FAIL] char size\n");
    }

// #test
// Tem momento da inicialização em que esse array de estruturas
// não funciona, e perdemos a configuração feita

    if (CONSOLE_TTYS[n].initialized != TRUE){
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

    // type: 'int'.
    if (Ch<0)
        return;

    // form feed - Nova tela.
    if (Ch == '\f')
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
        if (CONSOLE_TTYS[n].cursor_y >= CONSOLE_TTYS[n].cursor_bottom){
            if (CONSOLE_TTYS[n].fullscreen_flag == TRUE ){
                 console_scroll(n);
            }
            // Última linha.
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
        // Se o line feed apareceu quando estamos na ultima linha
        if ( CONSOLE_TTYS[n].cursor_y >= CONSOLE_TTYS[n].cursor_bottom){
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
            if (stdio_verbosemode_flag == 1){
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
    if (Ch == '\r')
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

    if (Ch == 0x20)
    {
        CONSOLE_TTYS[n].cursor_x++;
        prev = Ch;
        return; 
    }

// Backspace

    //if ( Ch == '\b' )
    if (Ch == 0x8)
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

// Out of screen
// Sem espaço horizontal.
    if ( CONSOLE_TTYS[n].cursor_left >= CONSOLE_TTYS[n].cursor_right )
    {
        panic ("console_oubyte: l >= r ");
    }

// Out of screen
// Sem espaço vertical.
    if ( CONSOLE_TTYS[n].cursor_top >= CONSOLE_TTYS[n].cursor_bottom )
    {
        panic ("console_oubyte: t >= b ");
    }


    //__ConsoleOutbyte(Ch,n);
    //prev = Ch;

// Fim da linha.
// Limites para o número de caracteres numa linha.
// Voltamos ao inicio da linha e avançamos uma linha.
// Caso contrario, apenas incrementa a coluna.

    if ( CONSOLE_TTYS[n].cursor_x >= (CONSOLE_TTYS[n].cursor_right -1) ){
        CONSOLE_TTYS[n].cursor_y++;
        CONSOLE_TTYS[n].cursor_x = CONSOLE_TTYS[n].cursor_left;
    }else{
        CONSOLE_TTYS[n].cursor_x++;
    };

// Número máximo de linhas. (n pixels por linha.)
// #bugbug
// Tem um scroll logo acima que considera um valor
// de limite diferente desse.

    if ( CONSOLE_TTYS[n].cursor_y >= CONSOLE_TTYS[n].cursor_bottom)  
    {
        if (CONSOLE_TTYS[n].fullscreen_flag == TRUE ){
            console_scroll(n);
        }
        CONSOLE_TTYS[n].cursor_x = 0;  //CONSOLE_TTYS[n].cursor_left;
        CONSOLE_TTYS[n].cursor_y = 
            (CONSOLE_TTYS[n].cursor_bottom -1);
    }



//draw:
// Draw in x*8 | y*8.
// Only if the echo mode is enabled.
// Nesse momento imprimiremos os caracteres.
// Imprime os caracteres normais.
// Atualisa o prev.

// local modes
    tcflag_t c_lflag = 
        (tcflag_t) CONSOLE_TTYS[n].termios.c_lflag;

    if (c_lflag & ECHO){
        __ConsoleOutbyte(Ch,n);
    }

    prev = Ch;
}


void console_outbyte2 (int c, int console_number)
{
// + Draw char.
// + Refresh char.

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

    if (n < 0 || n >= CONSOLETTYS_COUNT_MAX){
        debug_print ("console_outbyte: [FAIL] n\n");
        x_panic     ("console_outbyte: [FAIL] n\n");
    }

    if (__cWidth == 0 || __cHeight == 0){
        x_panic ("console_outbyte: [FAIL] char size\n");
    }

// #test
// Tem momento da inicialização em que esse array de estruturas
// não funciona, e perdemos a configuração feita

    if (CONSOLE_TTYS[n].initialized != TRUE){
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

    // type: 'int'.
    if (Ch<0)
        return;

    // form feed - Nova tela.
    if (Ch == '\f')
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
        
        if (CONSOLE_TTYS[n].cursor_y >= CONSOLE_TTYS[n].cursor_bottom){
            if (CONSOLE_TTYS[n].fullscreen_flag == TRUE ){
                 console_scroll(n);
            }
            // Vai para última linha
            CONSOLE_TTYS[n].cursor_y = ( CONSOLE_TTYS[n].cursor_bottom -1 );
            prev = Ch; 
        // Avança uma linha e volta para o começo da linha.
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
        // Se o line feed apareceu quando estamos na ultima linha
        if ( CONSOLE_TTYS[n].cursor_y >= CONSOLE_TTYS[n].cursor_bottom){
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
            if (stdio_verbosemode_flag == 1){
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
    if (Ch == '\r')
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

    if (Ch == 0x20)
    {
        CONSOLE_TTYS[n].cursor_x++;
        prev = Ch;
        return; 
    }

// Backspace

    //if ( Ch == '\b' )
    if (Ch == 0x8)
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

// Out of screen
// Sem espaço horizontal.
    if ( CONSOLE_TTYS[n].cursor_left >= CONSOLE_TTYS[n].cursor_right )
    {
        panic ("console_oubyte: l >= r ");
    }

// Out of screen
// Sem espaço vertical.
    if ( CONSOLE_TTYS[n].cursor_top >= CONSOLE_TTYS[n].cursor_bottom )
    {
        panic ("console_oubyte: t >= b ");
    }


    int Increment = FALSE;

// Fim da linha.
// Limites para o número de caracteres numa linha.
// Voltamos ao inicio da linha e avançamos uma linha.
// Caso contrario, apenas incrementa a coluna.

    if ( CONSOLE_TTYS[n].cursor_x >= (CONSOLE_TTYS[n].cursor_right -1) ){
        CONSOLE_TTYS[n].cursor_y++;
        CONSOLE_TTYS[n].cursor_x = CONSOLE_TTYS[n].cursor_left;
    }else{
        //CONSOLE_TTYS[n].cursor_x++;
        Increment = TRUE;
    };

// Número máximo de linhas. (n pixels por linha.)
// #bugbug
// Tem um scroll logo acima que considera um valor
// de limite diferente desse.

    if ( CONSOLE_TTYS[n].cursor_y >= CONSOLE_TTYS[n].cursor_bottom)  
    {
        if (CONSOLE_TTYS[n].fullscreen_flag == TRUE ){
            console_scroll(n);
        }
        CONSOLE_TTYS[n].cursor_x = 0;  //CONSOLE_TTYS[n].cursor_left;
        CONSOLE_TTYS[n].cursor_y = 
            (CONSOLE_TTYS[n].cursor_bottom -1);
    }


// draw:
// Draw in x*8 | y*8.
// Don't change the position.
// Only if the echo mode is enabled.
// Nesse momento imprimiremos os caracteres.
// Imprime os caracteres normais.

// local modes
    tcflag_t c_lflag = 
        (tcflag_t) CONSOLE_TTYS[n].termios.c_lflag;
    
    if (c_lflag & ECHO){
        __ConsoleOutbyte(Ch,n);
    }

// Atualisa o prev.
    prev = Ch;


// Refresh.
    unsigned long x=0;
    unsigned long y=0;
    x = (unsigned long) (CONSOLE_TTYS[n].cursor_x * __cWidth);
    y = (unsigned long) (CONSOLE_TTYS[n].cursor_y * __cHeight);
    refresh_rectangle ( x, y, __cWidth, __cHeight );

    if(Increment)
        CONSOLE_TTYS[n].cursor_x++;
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
    register int Ch = c;

// Target console
    int n = (int) console_number;

    int cWidth = get_char_width();
    int cHeight = get_char_height();

    unsigned long screenx=0;
    unsigned long screeny=0;
    unsigned int bg_color=0;
    unsigned int fg_color=0;

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

    if (VideoBlock.useGui != TRUE){
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

    if (VideoBlock.useGui != TRUE)
        return;

// Screen position.
    screenx = (unsigned long) (cWidth  * CONSOLE_TTYS[n].cursor_x);
    screeny = (unsigned long) (cHeight * CONSOLE_TTYS[n].cursor_y);

// Get the colors for this console.
    bg_color = (unsigned int) CONSOLE_TTYS[n].bg_color; 
    fg_color = (unsigned int) CONSOLE_TTYS[n].fg_color;

// Sempre pinte o bg e o fg.
    d_draw_char ( screenx, screeny, Ch, fg_color, bg_color );

/*
// ## NÃO TRANPARENTE ##
// Se estamos no modo terminal então usaremos as cores 
// configuradas na estrutura do terminal atual.
// Branco no preto é um padrão para terminal.

    if (stdio_terminalmode_flag == 1){
        // Pinta bg e fg.
        d_draw_char ( screenx, screeny, Ch, fg_color, bg_color );
        return;
    }

// ## TRANSPARENTE ##
// Se não estamos no modo terminal então usaremos
// char transparente.
// Não sabemos o fundo. Vamos selecionar o foreground.     

    // Pinta apenas o fg.
    d_drawchar_transparent ( screenx, screeny, fg_color, Ch );
*/

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

void console_putchar (int c, int console_number)
{
// + Draw char.
// + Refresh char.

// Char info and
// parameter for refresh worker.
    unsigned long x=0;
    unsigned long y=0;
    unsigned long cWidth  = get_char_width();
    unsigned long cHeight = get_char_height();

    cWidth  = (unsigned long) (cWidth  & 0xFFFF);
    cHeight = (unsigned long) (cHeight & 0xFFFF);

    if (cWidth == 0 || cHeight == 0){
        panic ("console_putchar: char\n");
    }

// flag on.
    stdio_terminalmode_flag = TRUE;

// #todo
// Check these limits.
// Console limits
// CONSOLETTYS_COUNT_MAX
// See: tty.h

    if (console_number < 0 || console_number > 3){
        panic ("console_putchar: console_number\n");
    }

// Draw the char into the backbuffer and
// Copy a small rectangle to the framebuffer.

    //if( c != 0)
    console_outbyte ( (int) c, console_number );

// #danger
// We will no be able to refresh if the routine above
// change the cursor position, incrementing or
// comming back to the start of the line.

    x = (unsigned long) (CONSOLE_TTYS[console_number].cursor_x * cWidth);
    y = (unsigned long) (CONSOLE_TTYS[console_number].cursor_y * cHeight);
    refresh_rectangle ( x, y, cWidth, cHeight );

// flag off
    stdio_terminalmode_flag = FALSE; 
}

void console_putchar_in_fgconsole(unsigned long _char)
{
    int c = (int) (_char & 0xFF);
    console_putchar( c, fg_console );
}

// Print consecutive spaces.
void console_print_indent(int indent, int console_number)
{
    register int i=0;
    const int Ch = ' ';

    if (indent<0)
        indent=0;
    if (console_number<0)
        return;
    for (i=0; i<indent; i++){
        console_putchar(Ch,console_number);
    };
}


// Coloca no prompt[] para ser comarado.
// Talvez o prompt também seja o buffer de stdin
int consoleInputChar(int c)
{
    unsigned long ascii=0;
    ascii = (unsigned long) (c & 0xFF);

    return (int) kinput(ascii);
}


void __dummy_thread(void)
{
    while (1){
    };
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

    if ( (void*)p==NULL ){
        printf("p fail\n");
        return;
    }

    //show_process_information();
        
// ok, it is working.
// Create and initialize a process structure.

    //__create_and_initialize_process_object();

}


// #test
// Creating a ring0 thread.
// #bugbug: 
// We're having problems with ring0 context switching.

void __test_thread(void)
{

// #bugbug: ring0 threads are a huge problem.
// Avoid that for now.

    struct thread_d *t;

    t = 
        (struct thread_d *) create_thread ( 
                                NULL, NULL, NULL,  // room desktop window 
                                __dummy_thread,    // init_rip, 
                                PRIORITY_HIGH, 
                                get_current_process(), 
                                "no-name",
                                RING0,
                                PERSONALITY_GRAMADO ); 

    if ( (void*)t==NULL ){
        printf("fail\n");
        return;
    }

    //show_slots();
}


static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 )
{
// #todo
// + Maybe return 'unsigned long'.
// + Maybe share data via shared memory
//   using a big buffer for that.
// + Maybe share the pointer of the buffer of a file.
// ...

// 32bit
    unsigned int x = (unsigned int) (data0 & 0xFFFFFFFF);
    unsigned int y = (unsigned int) (data0 & 0xFFFFFFFF);

// #todo: Simplify

    asm ("movl %1, %%eax;"
         "movl %%eax, %0;"
         "movl %%eax, %%edi;"
         :"=r"(y)        /* output */
         :"r"(x)         /* input */
         :"%eax"         /* clobbered register */
    );   

    //asm (" movq $65, %rdi ");
    
    asm ("call *%0" : : "r"(function_address));
}


void DANGER_VGA_clear_screen(void);
void DANGER_VGA_clear_screen(void)
{
/*
    unsigned int x=0;
    unsigned int y=0;

    unsigned char *VGA_address = (unsigned char *) 0xA0000;
    //unsigned char *VGA_address = (unsigned char *) FRONTBUFFER_VA;
    unsigned int VGA_width = 320;
    unsigned int VGA_height = 200;

    //printf ("VGA_clear_screen:\n");
    
    for(y=0; y<VGA_height; y++)
    {
        for (x=0; x<VGA_width; x++)
        {
            VGA_address[ VGA_width*y+x ] = 0x0f;
            //VGA_address[ y+x ] = 0xFF;
        };
    };

    while(1){}
*/

    printf("done\n");
    refresh_screen();
}

// Read and write from a tty device.
static void __test_tty(void)
{
    char data0[8];
    data0[0]='a';  data0[1]='b';  data0[2]='c';  data0[3]=0;

    char data1[8];
    data1[0]='x';  data1[1]='y';  data1[2]='z';  data1[3]=0; //dirty

    if ( (void*) KernelProcess == NULL ){
        return;
    }
    if (KernelProcess->magic != 1234){
        return;
    }

    __tty_write(KernelProcess->tty,data0,3); //write
    __tty_read (KernelProcess->tty,data1,3); //read

    printf("%c\n",data1[0]);
    printf("%c\n",data1[1]);
    printf("%c\n",data1[2]);
}


// Compare the strings that were
// typed into the kernel virtual console.
int consoleCompareStrings(void)
{
    int status=0;
    int fpu_status = -1;

    //debug_print("consoleCompareStrings: \n");
    printf("\n");

// test nic
    if ( strncmp(prompt,"test-nic",8) == 0 ){
        testNIC();
        goto exit_cmp;
    }
    if ( strncmp(prompt,"test-arp",8) == 0 ){
        network_send_arp_request();
        goto exit_cmp;
    }
    if ( strncmp(prompt,"test-arp2",9) == 0 ){
        network_send_arp_request2();
        goto exit_cmp;
    }
    if ( strncmp(prompt,"test-udp",8) == 0 ){
        network_test_udp();
        goto exit_cmp;
    }
    if ( strncmp(prompt,"test-udp2",9) == 0 ){
        network_test_udp2();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"test-dhcp",9) == 0 ){
        network_initialize_dhcp();
        goto exit_cmp;
    }

    if ( strncmp(prompt,"str",3) == 0 )
    {
        console_print_indent(4,fg_console);
        console_write_string(fg_console,"This is a string\n");
        console_print_indent(8,fg_console);
        console_write_string(fg_console,"This is another string\n");
        //__respond(fg_console);
        goto exit_cmp;
    }

// mod0: Call the entrypoint of the module.
// mod0.bin entry point.
// When this moudule was loaded?
// see: I_x64CreateKernelProcess in x64init.c
    if ( strncmp(prompt,"mod0",4) == 0 )
    {
        if ( (void*) kernel_mod0 != NULL )
        {
            if (kernel_mod0->magic == 1234)
            {
                if (kernel_mod0->initialized == TRUE)
                {
                    //while(1){
                    // No return value.
                    // 1 parameter.
                    // reason=1000. (Initialize)
                    caller1((unsigned long) 0x30A01000,1000);
                    // reason=1001. (test)
                    caller1((unsigned long) 0x30A01000,1001);
                    // Invalid reason
                    caller1((unsigned long) 0x30A01000, 999 );
                    //};
                }
            }
        }
        goto exit_cmp;
    }



// dir:
// List the files in a given directory.
// root dir. Same as '/'.
    if ( strncmp(prompt,"dir",3) == 0 ){
        fsList("[");
        goto exit_cmp;
    }

// Testing vga stuff.
    if ( strncmp(prompt,"vga-cls",7) == 0 ){
        //DANGER_VGA_clear_screen();
        goto exit_cmp;
    }

// mm1: Show paged memory list.
// IN: max index.
    if ( strncmp(prompt,"mm1",3) == 0 ){
        showPagedMemoryList(512); 
        goto exit_cmp;
    }

// mm2: show the blocks allocated by the kernel allocator.
// inside the kernel heap.
// IN: max index.
    if ( strncmp(prompt,"mm2",3) == 0 ){
        showMemoryBlocksForTheKernelAllocator(); 
        goto exit_cmp;
    }

// exit: Exit the embedded kernel console.
    if ( strncmp(prompt,"exit",4) == 0 ){
        exit_kernel_console(); 
        goto exit_cmp;
    }

/*
// #note
// We already did that in the kernel initialization.
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
*/

/*
// smp:
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
*/

// disk: Show some disk information.
// See: ata.c
    if ( strncmp( prompt, "disk", 4 ) == 0 ){
        printf("disk: Show ide info:\n");
        ata_show_device_list_info();
        //show_ide_info();
        //disk_show_info();
        goto exit_cmp;
    }

// volume: Show some volume information.
    if ( strncmp(prompt,"volume",6) == 0 ){
        volume_show_info();
        goto exit_cmp;
    }

// device: Device list.
// Show tty devices, pci devices and devices with regular file.
// See: devmgr.c
    if ( strncmp(prompt,"device",6) == 0 )
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

// pci:
    if ( strncmp( prompt, "pci", 3 ) == 0 ){
        printf("~pci:\n");
        pciInfo();
        goto exit_cmp;
    }

// about:
    if ( strncmp( prompt, "about", 5 ) == 0 ){
        printf("About: The kernel console\n");
        goto exit_cmp;
    }

// cls:
    if ( strncmp( prompt, "cls", 3 ) == 0 )
    {
        //backgroundDraw(COLOR_EMBEDDED_SHELL_BG);
        //set_up_cursor(1,1);

        //IN: bg color, fg color, console number.
        clear_console(
            (unsigned int) CONSOLE_TTYS[fg_console].bg_color,
            (unsigned int) CONSOLE_TTYS[fg_console].fg_color,
            fg_console );

        goto exit_cmp;
    }

// cpu: Display cpu info.
    if ( strncmp( prompt, "cpu", 3 ) == 0 ){
        x64_info();
        goto exit_cmp;
    }

// pit: Display PIT info.
    if ( strncmp( prompt, "pit", 3 ) == 0 ){
        printf("Dev freq: %d | Clocks per sec: %d HZ | Period: %d\n",
            PITInfo.dev_freq,
            PITInfo.clocks_per_sec,
            PITInfo.period );
        goto exit_cmp;
    }

// help:
    if ( strncmp( prompt, "help", 4 ) == 0 ){
        printf("Commands: about, help, reboot, cpu, memory, ...\n");
        goto exit_cmp;
    }

// memory:
    if ( strncmp( prompt, "memory", 6 ) == 0 ){
        memoryShowMemoryInfo();
        goto exit_cmp;
    }

// path:
// Test the use of 'pathnames' with multiple levels.
// #test: This test will allocate some pages
// for the buffer where we are gonna load the file.
    if ( strncmp(prompt,"path",4) == 0 ){
        __test_path();
        goto exit_cmp;
    }

// process:
    if ( strncmp( prompt, "process", 7 ) == 0 ){
        __test_process();
        goto exit_cmp;
    }

// ps2-qemu:
// Testing the full initialization of ps2 interface.
// This is a work in progress.
// See: dev/i8042.c
    if ( strncmp( prompt, "ps2-qemu", 8 ) == 0 )
    {
        if (HVInfo.initialized == TRUE){
            if (HVInfo.type == HV_TYPE_QEMU){
                printf("#test: PS2 full initialization on qemu\n");
                PS2_initialization();
            }
        }
        goto exit_cmp;
    }

// ps2-kvm: Initializze the ps2 support when running on kvm.
// #bugbug
// The initialization is not working on kvm.
    if ( strncmp( prompt, "ps2-kvm", 7 ) == 0 )
    {
        printf ("#todo: Initialization not working on kvm\n");
        if (HVInfo.initialized == TRUE){
            if (HVInfo.type == HV_TYPE_KVM){
                //printf("#test: PS2 full initialization on kvm\n");
                //PS2_initialization();
            }
        }
        goto exit_cmp;
    }

// reboot:
    if ( strncmp( prompt, "reboot", 6 ) == 0 ){
        hal_reboot();
        goto exit_cmp;
    }

// beep:
    if ( strncmp( prompt, "beep", 4 ) == 0 ){
        hal_test_speaker();
        goto exit_cmp;
    }

/*
// thread:
// #bugbug: ring0 threads are a huge problem.
// Avoid that for now.
    if ( strncmp( prompt, "thread", 6 ) == 0 ){
        //__test_thread();
        goto exit_cmp;
    }
*/

// time:
    if ( strncmp( prompt, "time", 4 ) == 0 )
    {
        printf ("Init stime %d\n",InitThread->stime);
        printf ("Init utime %d\n",InitThread->utime);
        goto exit_cmp;
    }

// tty: Read and write from tty device.
    if ( strncmp( prompt, "tty", 3 ) == 0 ){
        __test_tty();
        goto exit_cmp;
    }

// serial: Display serial support info.
// #todo: Only com1 for now.
// But we can get information for all the 4 ports.
    if ( strncmp( prompt, "serial", 6 ) == 0 )
    {
        //#todo: Only com1 for now.
        printf("com1.divisor:       %d\n",
            SerialPortInfo.com1.divisor);
        printf("com1.divisorLoByte: %d\n",
            SerialPortInfo.com1.divisorLoByte);
        printf("com1.divisorHiByte: %d\n",
            SerialPortInfo.com1.divisorHiByte);
        printf("com1.baudrate:      %d\n",
            SerialPortInfo.com1.baudrate);
        goto exit_cmp;
    }

// ========
// close: Sending a MSG_CLOSE messsage to the init thread.
    if ( strncmp(prompt,"close",5) == 0 )
    {
        if( (void*) InitThread == NULL ){goto exit_cmp;}
        post_message_to_tid(
            (tid_t) 0,                //sender tid. #todo
            (tid_t) InitThread->tid,  //receiver tid.
            NULL,                     //window
            (int) MSG_CLOSE,          //msg code
            0,
            0 );
        goto exit_cmp;
    }

// ========
// app1: Sending a MSG_COMMAND/4001 messsage to the init thread.
    if ( strncmp(prompt,"app1",4) == 0 )
    {
        if ( (void*) InitThread == NULL ){ goto exit_cmp; }
        post_message_to_tid(
            (tid_t) 0,                // sender tid #todo
            (tid_t) InitThread->tid,  // receiver tid
            NULL,                     // window
            (int) MSG_COMMAND,        // msg code
            (unsigned long) 4001,     // data1
            0 );
        printf("app1: done\n");
        //refresh_screen();
        goto exit_cmp;
    }

// ========
// app2: Sending a MSG_COMMAND/4002 messsage to the init thread.
    if ( strncmp(prompt,"app2",4) == 0 )
    {
        if ( (void*) InitThread == NULL ){ goto exit_cmp; }
        post_message_to_tid(
            (tid_t) 0,                 //sender tid #todo
            (tid_t) InitThread->tid,   //receiver tid
            NULL,                      //window
            (int) MSG_COMMAND,         //msg code
            (unsigned long) 4002,      //data1
            0 );
        printf("app2: done\n");
        //refresh_screen();
        goto exit_cmp;
    }

// ========
// app3: Sending a MSG_COMMAND/4003 messsage to the init thread.
    if ( strncmp(prompt,"app3",4) == 0 )
    {
        if ( (void*) InitThread == NULL ){ goto exit_cmp; }
        //#todo: We do not have a sender tid yet.
        post_message_to_tid(
            (tid_t) 0,                // sender tid. (#todo)
            (tid_t) InitThread->tid,  // receiver tid
            NULL,                     // window
            (int) MSG_COMMAND,        // msg code
            (unsigned long) 4003,     // data
            (unsigned long) 0 );      // data
        printf("app3: done\n");
        //refresh_screen();
        goto exit_cmp;
    }

// Invalid command

    //printf("\n");
    printf ("Error: Command not found!\n");
    //printf("\n");

exit_cmp:
   //nothing
done:
    consolePrompt();
    return 0;
}

// consolePrompt:
// Inicializa o prompt.
// Clean prompt buffer.
// Print the prompt string.
void consolePrompt(void)
{
    register int i=0;

//
// Prompt
//

    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){ 
        prompt[i] = (char) '\0'; 
    };
    prompt[0] = (char) '\0';
    prompt_pos = 0;
    prompt_status = 0;
    prompt_max = PROMPT_MAX_DEFAULT;  
    printf("\n");
    printf("$ ");
    refresh_screen();
    //invalidate_screen();

//
// Initialize escape sequence.
//
    //for (i=0; i<NPAR; i++){
    //    par[i]=0;
    //};
    //__EscapeSequenceStage=0;
}

// __console_write:
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
    if (!count){
        printf ("__console_write: count\n");
        goto fail;
    }

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

// console_read:
// #todo
// Isso é importante.
// Pegar input na estrutura de console do kernel.

ssize_t 
console_read ( 
    int console_number, 
    const void *buf, 
    size_t count )
{
// #todo
// Not fully implemented!

// Console number
    if (console_number < 0 || console_number > 3){
        printf ("console_read: [FAIL] console_number\n");
        goto fail;
    }
// Buffer
    if ( (void *) buf == NULL ){
        printf ("console_read: buf\n");
        goto fail;
    }
// Count
    if (!count){
        printf ("console_read: count\n");
        goto fail;
    }

    //debug_print ("console_read: [TODO]\n");

/*
// #test
    __tty_read( 
        (struct tty_d *) &CONSOLE_TTYS[console_number],
        buf,
        count );
*/

fail:
    return -1;  //todo
}

// ------------------------------
// console_write:
// Called by sys_write() in fs.c quando o arquivo é do tipo console.
// Also called by sci.c.
// Tem escape sequence.
// IN:
// console number, buffer, size. 

ssize_t 
console_write ( 
    int console_number, 
    const void *buf, 
    size_t count )
{
// Write n bytes of a string into a given console.
// Called by sys_write.
// Called by sys_write on fflush().

// loop
    register int i=0;
    char ch=0; 
    char *data = (char *) buf;
    size_t StringSize=0;
    int ivalue=0;
    int ivalue2=0;
    int ivalue3=0;

    //debug_print ("console_write: [test]\n");

// Console number
    if (console_number < 0 || console_number > 3){
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

/*
// #test
    __tty_write( 
        (struct tty_d *) &CONSOLE_TTYS[console_number],
        buf,
        count );
*/


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
               // ascii, not abnt2
               if (ch >= 32 && ch <= 127){
                    
                    // Draw and refresh.
                    console_outbyte2 ( ch, console_number );
               
               // >>>> [ Escape ]
               // Entramos em uma escape sequence,
               // entao o proximo case inicia o tratamento da escape sequence.
               } else if (ch==27){
                   __EscapeSequenceStage=1;
               
               // ?? \n
               //}else if (ch==10 || ch==11 || ch==12){
               }else if (ch == '\n'){
               
                   console_putchar(ch,console_number);
               // Enter ? cr \n
               }else if (ch == '\r'){ 
                   console_putchar(ch,console_number); 
               // Backspace
               }else if (ch=='\b') {
                   console_putchar(ch,console_number);
               // Tab.
               } else if (ch=='\t') {
                   console_putchar(ch,console_number); 
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
                

                // ESC [ -  CSI Control sequence introducer
                // https://man7.org/linux/man-pages/man4/console_codes.4.html
                if (ch=='['){
                    __EscapeSequenceStage = 2;

                // ESC E - NEL  Newline.
                }else if (ch=='E'){ 
                    __local_gotoxy ( 0, (CONSOLE_TTYS[console_number].cursor_y + 1), console_number );
                    //__EscapeSequenceStage = 0;
                
                // ESC M - RI Reverse linefeed.
                }else if (ch=='M'){
                    __local_ri ();   //scroll. deixa pra depois. kkk
                    //__EscapeSequenceStage = 0;
                
                // ESC D - IND Linefeed.
                }else if (ch=='D'){
                    console_putchar ( ch, console_number );  //lf();
                    //__EscapeSequenceStage = 0;
                
                // ESC Z - DECID  DEC private identification.
                // The kernel returns the string  ESC[?6c, 
                // claiming that it is a VT102.
                }else if (ch=='Z'){
                    __respond (console_number);    //test
                    //__EscapeSequenceStage = 0;
                
                //??
                // tivemos um 0x1b e o cursor esta em determinado lugar.
                }else{
                }
                
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
                for ( npar=0; npar<NPAR; npar++ ){ 
                    par[npar]=0;
                };
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
                if ( ch == ';' && npar < NPAR-1 ) {
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
                    // O valor no buffer provavelmente é 0,
                    // no primeiro numero.
                    // Sendo assim quebramos para 
                    // tentarmos pegar mais numeros no for.
                    //par[npar] = (10 * par[npar]) +ch -'0';
                    par[npar] = ch;
                    break;

                 // Nao eh um delimitador nem um numero.
                 // entao vamos para o proximo estagio
                 // porque provavelmente eh uma letra.
                 // Nao precisamos quebrar, pois ja temos um char.
                 } else { 
                     __EscapeSequenceStage = 4;
                 };

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
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        __local_gotoxy ( 
                            ivalue, 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // Mudamos o cursor e saimos da escape sequence
                    // n lines up
                    case 'A':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x,  
                            CONSOLE_TTYS[console_number].cursor_y - ivalue, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    case 'B': case 'e':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x, 
                            CONSOLE_TTYS[console_number].cursor_y + ivalue, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // Cursor right.
                    // mudamos o cursor e saimos da escape sequence 
                    case 'C': case 'a':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x + ivalue, 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // Cursor left.
                    // mudamos o cursor e saimos da escape sequence
                    case 'D':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x - ivalue, 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'E':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        __local_gotoxy ( 
                            0, 
                            CONSOLE_TTYS[console_number].cursor_y + ivalue, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'F':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        __local_gotoxy ( 
                            0, 
                            CONSOLE_TTYS[console_number].cursor_y - ivalue, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'd':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);

                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x, 
                            ivalue, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'H': case 'f':

                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);

                        ivalue2 = par[1];
                        ivalue2 = (ivalue2 & 0xFF);
                        ivalue2 = k_atoi(&ivalue2);

                        __local_gotoxy ( 
                            ivalue,
                            ivalue2, 
                            console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // Outros tratadores.
                    case 'J': 
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        csi_J(ivalue);
                        __EscapeSequenceStage = 4;
                        break;
                    case 'K':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        csi_K(ivalue);
                        __EscapeSequenceStage = 4;
                        break;
                    case 'L':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        csi_L( ivalue, console_number );
                        __EscapeSequenceStage = 4;
                        break;
                    case 'M':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        csi_M( ivalue, console_number );
                        __EscapeSequenceStage = 4;
                        break;
                    case 'P':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        csi_P( ivalue, console_number );
                        __EscapeSequenceStage = 4;
                        break;
                    case '@':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);
                        csi_at( ivalue, console_number );
                        __EscapeSequenceStage = 4;
                        break;

                    // FIM.
                    // Isso marca o fim da escape sequence,
                    // vamos quebrar e voltar para a string normal.
                    // Essa rotina cheaca os parametros e configura o atributo
                    // de acordo com o ultimo parametro.
                    case 'm': 
                        //printf ("m found\n");
                        //csi_m(); // Set some attributes based on the parameters found.
                        // Limpando o array de parametros.
                        for ( npar=0; npar<NPAR; npar++ ){ 
                            par[npar]=0;
                        };
                        npar=0;
                        __EscapeSequenceStage = 0;
                        break;

                    // ??  #bugbug
                    // 0x1b[r
                    // Isso ajusta o top e o bottom.
                    case 'r':
                        ivalue = par[0];
                        ivalue = (ivalue & 0xFF);
                        ivalue = k_atoi(&ivalue);

                        ivalue2 = par[1];
                        ivalue2 = (ivalue2 & 0xFF);
                        ivalue2 = k_atoi(&ivalue2);

                        //if (par[0])  { par[0]--; }
                        //if (!par[1]) { par[1] = CONSOLE_TTYS[console_number].cursor_bottom; }  
                        //if (par[0] < par[1] &&
                        //    par[1] <= CONSOLE_TTYS[console_number].cursor_bottom ) 
                        //{
                            // Ajuste feito por 'r'.
                        //    CONSOLE_TTYS[console_number].cursor_top    = par[0];
                         //   CONSOLE_TTYS[console_number].cursor_bottom = par[1];
                        //}
                        
                        __EscapeSequenceStage = 4;
                        break;

                    // Save cursor
                    case 's': 
                        __local_save_cur(console_number);
                        __EscapeSequenceStage = 4;
                        break;

                    // Restore cursor
                    case 'u': 
                        __local_restore_cur(console_number);
                        __EscapeSequenceStage = 4;
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


void console_write_string(int console_number, char *string)
{
// Write a string into a console.
    char *p;
    p = string;
    size_t i=0;
    size_t size = strlen(string);
    if(size<=0)
        return;
    for (i=0; i<size; i++)
    {
        console_write(
            console_number, 
            p,
            1 );
        p++;
    };
}


void __respond (int console_number)
{
    char *p = __RESPONSE;
    console_write_string(console_number,p);
}

// See:
// https://en.wikipedia.org/wiki/Control_character
// https://en.wikipedia.org/wiki/C0_and_C1_control_codes#Device_control

void __local_insert_char(int console_number)
{
// #todo: max limit
    if (console_number<0){
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
    if (console_number<0){
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
// #todo: max limit
    if (console_number<0){
        return;
    }

    if (nr > CONSOLE_TTYS[console_number].cursor_right -1 ){
        nr = CONSOLE_TTYS[console_number].cursor_right -1 ;
    } else {
        if (!nr){
            nr = 1;
        }
    };

    if (nr<0){
        return;
    }

    while (nr--){
        __local_delete_char(console_number);
    };
}

void csi_at (int nr, int console_number)
{
// #todo: max limit
    if ( console_number<0){
        return;
    }

    if (nr > CONSOLE_TTYS[console_number].cursor_right -1 ){
        nr = CONSOLE_TTYS[console_number].cursor_right -1 ;
    }else{
        if (!nr){
            nr=1;
        }
    };

    if (nr<0){
        return;
    }

    while (nr--){
        __local_insert_char(console_number);
    };
}

// Intialize the support for virtual consoles.
// Called by preinit_OutputSupport in main.c
// #todo: Explain it better.
// We have 4 preallocated tty structures for virtual consoles.
int VirtualConsole_initialize(void)
{
// Early initialization of the consoles.
// It's gonna be reinitializad by __initialize_virtual_consoles()
// in kstdio.c

    register int i=0;

// No embedded shell for now.
// No input in prompt[].
    ShellFlag = FALSE;

    __EscapeSequenceStage=0;

// Limpa o array de parâmetros usado durante o 
// tratamento de escape sequencies.
    for (i=0; i<NPAR; i++){
        par[i]=0;
    };

    unsigned int bg_colors[CONSOLETTYS_COUNT_MAX];
    unsigned int fg_colors[CONSOLETTYS_COUNT_MAX];

// Default kernel console.
    bg_colors[0] = (unsigned int) COLOR_BLUE;
    fg_colors[0] = (unsigned int) COLOR_WHITE;
// 
    bg_colors[1] = (unsigned int) COLOR_BLUE;
    fg_colors[1] = (unsigned int) COLOR_YELLOW;
// Warning console.
    bg_colors[2] = (unsigned int) COLOR_ORANGE;
    fg_colors[2] = (unsigned int) COLOR_WHITE;
// Danger console.
    bg_colors[3] = (unsigned int) COLOR_RED;
    fg_colors[3] = (unsigned int) COLOR_YELLOW;


// Virtual Console:
// The kernel only have four virtual consoles.
    for (i=0; i<CONSOLETTYS_COUNT_MAX; i++)
    {
        // IN: console index, bg color, fg color
        console_init_virtual_console(
            i,
            bg_colors[i],
            fg_colors[i] );

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

// Cursor for the current console.
// See: system.c
    set_up_cursor(0,0);

// #hackhack
// Esse trabalho não nos pertence, pertence ao stdio,
// mas funciona.
    stdio_terminalmode_flag = TRUE;
    stdio_verbosemode_flag = TRUE;

    return 0;
}

// Console banner:
// This will be the first message in the screen.
// It is goona be seen at top/left corner of the screen.

void console_banner(unsigned long banner_flags)
{
// Serial debug
    if (Initialization.serial_log == TRUE){
        debug_print ("Gramado OS\n");
    }
// Virtual console
    if (Initialization.console_log == TRUE){
        set_up_cursor(0,0);
        printf ("Gramado OS\n");
    }
    refresh_screen();
}

// console_ioctl:
// Podemos mudar as características de um console.
// #bugbug: fd and fg_console needs to be the same?
int 
console_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{

    debug_print ("console_ioctl: TODO\n");
    //printf ("console_ioctl: TODO\n");

    if ( fd < 0 || fd >= OPEN_MAX ){
        return (int) (-EBADF);
    }

// Standard stream.
// Only the fd 1 is a console.
// This is the fg_console, always.
    if ( fd != 1 )
    {
        //#debug
        panic ("console_ioctl: fd != 1\n");
    }

    //#debug
    //printf ("console_ioctl:  fd=1\n");

//----------------------------------------------------------------------
// Setup the foreground console.
// We operate only on the fg_console!

    if (fg_console<0 || fg_console > 3){
        panic ("console_ioctl: fg_console\n");
    }

    switch (request){

// #todo:
// There is no fflush here in ring0.
// The ring3 libc is doing this job using write.
// ??
// The ring3 flush implementation flushes the content 
// that is in a ring 3 buffer.
// The flush in ring 0 maybe can flush the backbuffer
// into the lfb.
// 1
// Flush accumulated input data.
// Flushes data received, but not read.
    case TCIFLUSH:
        debug_print ("console_ioctl: TCIFLUSH\n");
        printf ("console_ioctl: TCIFLUSH\n");
        refresh_screen();  //#test
        break;

// 2
// Flush accumulated output data.
// Flushes data written but not transmitted.
    case TCOFLUSH:
        printf ("console_ioctl: TCOFLUSH\n");
        refresh_screen();  //#test
        break;

// 3
// Flush accumulated input and output data.
// Flushes both data received but not read, and 
// data written but not transmitted.
    case TCIOFLUSH:
        printf ("console_ioctl: TCIOFLUSH\n");
        refresh_screen();  //#test
        break;

// #todo: 
// Yes, we can return data from the console tty termios. 
    // case TCGETS:
    // ...

    // ...

//
// fg color
//

    // set fg color.
    case 400:
        //#deprecated
        return 0;
        break;
    // get fg color.
    case 401:
        return (int) get_fg_color();
        break;

//
// bg color
//

    // set bg color.
    case 402:
        //#deprecated
        return 0;
        break;
    // get bg color.
    case 403:
        return (int) get_bg_color();
        break;

// Clear console.
// IN: bg color, fg color, console number.
    case 440:
        clear_console( 
            (unsigned int) CONSOLE_TTYS[fg_console].bg_color,
            (unsigned int) CONSOLE_TTYS[fg_console].fg_color, 
            fg_console );
        return 0;
        break;

// Is it initialized or not?
    case 500:
        return (int) CONSOLE_TTYS[fg_console].initialized;
        break;

// Is it stopped?
    case 501:
        return (int) CONSOLE_TTYS[fg_console].stopped;
        break;

// What process group it belongs to?
    case 502:
        return (int) CONSOLE_TTYS[fg_console].gid;
        break;

// ??
// Qual eh o modo de operacao do console virtual.
// graphics, text ...
    case 503:
        return (int) CONSOLE_TTYS[fg_console].vc_mode;
        break;

// tty type
    case 504:
        return (int) CONSOLE_TTYS[fg_console].type;
        break;

// tty subtype
    case 505:
        return (int) CONSOLE_TTYS[fg_console].subtype;
        break;

// ??
// Qual terminal virtual esta usando essa tty.
    case 506:
        return (int) CONSOLE_TTYS[fg_console].virtual_terminal_pid;
        break;

// fullscreen or not?
    case 507:
        return (int) CONSOLE_TTYS[fg_console].fullscreen_flag;
        break;

// charset id
    case 508:
        return (int) CONSOLE_TTYS[fg_console].charset_id;
        break;

// charset lang id
    case 509:
        return (int) CONSOLE_TTYS[fg_console].charset_lang_id;
        break;

//
// Margins in bytes
//

    case 510:
        return (int) CONSOLE_TTYS[fg_console].cursor_left;
        break;
    case 511:
        return (int) CONSOLE_TTYS[fg_console].cursor_top;
        break;
    case 512:
        return (int) CONSOLE_TTYS[fg_console].cursor_right;
        break;
    case 513:
        return (int) CONSOLE_TTYS[fg_console].cursor_bottom;
        break;

// In pixels

    case 514:
        return (int) CONSOLE_TTYS[fg_console].cursor_width_in_pixels;
        break;
    case 515:
        return (int) CONSOLE_TTYS[fg_console].cursor_height_in_pixels;
        break;

// ...

    case 999:
        console_scroll(fg_console);
        return 0;
        break;

    //#deprecated.
    case 1000:
        return 0;
        break;

    // Cursor: x position
    case 1001:
        __local_gotoxy(
            arg,
            CONSOLE_TTYS[fg_console].cursor_y, 
            fg_console );
        return 0;
        break;

    // Cursor: y position
    case 1002:
        __local_gotoxy(
            CONSOLE_TTYS[fg_console].cursor_x,
            arg, 
            fg_console );
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

// ...

// Goto first line at given col.
    case 1008:
        // IN: x, y, console number
        __local_gotoxy(
            arg,
            0, 
            fg_console );
        break;

// Goto last line at given col.
    case 1009:
        // IN: x, y, console number
        __local_gotoxy(
            arg,
            (CONSOLE_TTYS[fg_console].cursor_bottom -1), 
            fg_console );
        break;

    case 1010:
        // max limit
        if (arg < 70){
            console_print_indent(arg,fg_console);
        }
        break;

// Get cursor x
    case 1011:
        return (int) get_cursor_x();
        break;
// Get cursor y
    case 1012:
        return (int) get_cursor_y();
        break;

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
 *     #IMPORTANTE
 *     REFRESH SOME GIVEN STREAM INTO TERMINAL CLIENT WINDOW !!
 */
// #todo
// Change this name. 
// Do not use stream in the base kernel.

void REFRESH_STREAM(file *f)
{
    register int i=0;
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

int 
clear_console (
    unsigned int bg_color, 
    unsigned int fg_color, 
    int console_number )
{
// Clear a console with the given colors.

    if ( VideoBlock.useGui != TRUE ){
        return -1;
    }
    if (console_number<0 || console_number > 3){
        return -1;
    }

// Clear background.
    backgroundDraw(bg_color);
    CONSOLE_TTYS[console_number].bg_color = (unsigned int) bg_color;
    CONSOLE_TTYS[console_number].fg_color = (unsigned int) fg_color;

// Cursor
    __local_gotoxy(0,0,console_number);

    refresh_screen();

    return 0;
}


