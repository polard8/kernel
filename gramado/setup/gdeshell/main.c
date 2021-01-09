/*
 * File: main.c
 * 
 *     gdeshell - Gramado Desktop Environment Shell
 * 
 *     This is a simple command interpreter.
 *     It uses a Land OS library called libcore.
 *     It uses the kgws window server, embedded into the base kernel.
 * 
 * History:
 *     2016 - Created by Fred Nora.
 */

#include "gdeshell.h"

// #hackhack
#define gramado_strncmp strncmp 


#define WINDOW_LEFT      0      //10
#define WINDOW_TOP       0      //10


// Input flags.
#define SHELLFLAG_NULL          0
#define SHELLFLAG_COMMANDLINE   1
#define SHELLFLAG_SCRIPT        2
#define SHELLFLAG_HELP          3
#define SHELLFLAG_VERSION       4
#define SHELLFLAG_USAGE         5
#define SHELLFLAG_TOPBAR        6
#define SHELLFLAG_FEEDTERMINAL  7
#define SHELLFLAG_EXIT          8
// ...


//#define MIN(x,y) ((x < y) ? x : y)

// buffer usado para criar um arquivo de configuracao.
char __setup_buffer[512];

// Para que o procedimento possa acessa-lo.
// #bugbug: size
char __net_buffer[4096];


// A janela principal do aplicativo.
struct window_d *hWindow;  
struct window_d *cpu_window;  //cpu usage test;



// Ser� configurado na inicializa��o.
int __stdin_fd;
int __stdout_fd;
int __stderr_fd;


int ShellFlag = 0;

//O shell est� rodadndo.
int _running = 1;

/* Non-zero when we are executing a top-level command. */
//o shell est� executando um comando que 
//est� emprimeiro plando.
int executing = 0;


int login_status = 0;


//Sendo assim, o shell poderia abrir no ambiente de logon.

char username[11];
char password[11];
//char sUsername[11];
//char sPassword[11];
//char *username;
//char *password; 

//#define DEFAULT_WINDOW_TITLE "Shell"
	
/* Non-zero means that this shell has already been run; i.e. you should
   call shell_reinitialize () if you need to start afresh. */
int shell_initialized = 0;

/* The current maintainer of the shell.  You change this in the
   Makefile. */
#ifndef MAINTAINER
#define MAINTAINER "deliberately-anonymous"
#endif
char *the_current_maintainer = MAINTAINER;

#ifndef PPROMPT
#define PPROMPT "bash\\$ "
#endif
char *primary_prompt = PPROMPT;

#ifndef SPROMPT
#define SPROMPT "bash> "
#endif
char *secondary_prompt = SPROMPT;


#define ROOT_STRING "/"
char *root_string = ROOT_STRING;

COMMAND *global_command = (COMMAND *) NULL;


/* Non-zero after SIGINT. */
int interrupt_state = 0;



/* The current user's name. */
char __username[64];
//char __current_host_name[64];
//char __current_user_name[64];
//char *current_host_name = (char *) &__current_host_name[0]; //"username";
//char *current_user_name = (char *) &__current_user_name[0]; //NULL;


/* Non-zero means that this shell is a login shell.
   Specifically:
   0 = not login shell.
   1 = login shell from getty (or equivalent fake out)
  -1 = login shell from "-login" flag.
  -2 = both from getty, and from flag.
 */

//Se o shell vai ser usado para login.
//Obs: Uma vari�vel no kernel guardo o id do processo 
//que fez login. 

int login_shell = 0;


/* Non-zero means this shell is running interactively. */

//Se for diferente de zero ent�o esse shell � interativo.
//Se for zero ele pode apenas estar executando um script.
// #importante: Inicializa interativo.
// Se quem chamou deseja que o shell n�o seja interativo,
// tem que enviar os argumentos necess�rios.

int interactive = 1;


/* Non-zero means to remember lines typed to the shell on the history
   list.  This is different than the user-controlled behaviour; this
   becomes zero when we read lines from a file, for example. */
int remember_on_history = 1;


/* Non-zero means this shell is restricted. */
int restricted = 0;

/* Special debugging helper. */
int debugging_login_shell = 0;


/* The environment that the shell passes to other commands. */
//O ambiente que o shell passa para 
//o comando que ele executou.
char **shell_environment;


/* The number of commands executed so far. */
int current_command_number = 1;


/* The environment at the top-level REP loop.  We use this in the case of
   error return. */
//jmp_buf top_level, catch;


/* Non-zero is the recursion depth for commands. */
int indirection_level = 0;


/* The number of times BASH has been executed.  This is set
   by initialize_variables () in variables.c. */
int shell_level = 0;


char *shell_name    = "GDESHELL.BIN";
char *dist_version  = "0.1";
char *build_version = "1";


/* The name of the .(shell)rc file. */
char *bashrc_file = "~/.bashrc";

/*nome do arquivo de configura��o*/
char *shell_config_file = "./shellcnf.txt";


/* Non-zero means to act more like the Bourne shell on startup. */
int act_like_sh = 0;



/* Values for the long-winded argument names. */
int debugging = 0;		/* Do debugging things. */
int no_rc = 0;			/* Don't execute ~/.bashrc */
int no_profile = 0;		/* Don't execute .profile */
int do_version = 0;		/* Display interesting version info. */
/* Be quiet when starting up. */
//inicializa��o silenciosa. Suprime alguns verboses.
int quiet = 0;	
int make_login_shell = 0;	/* Make this shell be a `-bash' shell. */
int no_line_editing = 0;	/* Don't do fancy line editing. */
int no_brace_expansion = 0;	/* Non-zero means no foo{a,b} -> fooa fooa. */


//
// ## Arguments support ##
//


/* Some long-winded argument names.  These are obviously new. */
#define Int    1
#define Charp  2

struct {

    char *name;
    int *value;
    int type;

} long_args[] = {

    { "debug",             &debugging,           Int   },
    { "norc",              &no_rc,               Int   },
    { "noprofile",         &no_profile,          Int   },
    { "rcfile",            (int *) &bashrc_file, Charp },
    { "version",           &do_version,          Int   },
    { "quiet",             &quiet,               Int   },
    { "login",             &make_login_shell,    Int   },
    { "nolineediting",     &no_line_editing,     Int   },
    { "nobraceexpansion",  &no_brace_expansion,  Int   },
    { (char *) NULL,       (int *) 0x0,          0     }

};


int shellStatus;
int shellError;


//... 

/*
//argument buffer
char **argbuf;
int argbuf_length;
int argbuf_index;
*/

/*
struct {
	
  char *word;
  int token;
  
} token_word_alist[] = {
  {"if", IF},
  {"then", THEN},
  {"else", ELSE},
  {"elif", ELIF},
  {"fi", FI},
  {"case", CASE},
  {"esac", ESAC},
  {"for", FOR},
  {"while", WHILE},
  {"until", UNTIL},
  {"do", DO},
  {"done", DONE},
  {"in", IN},
  {"function", FUNCTION},
  {"{", '{'},
  {"}", '}'},
  { (char *) NULL, 0 }
};
*/



// status de algumas inicializa��es de duporte a janelas.
int sm_initialized = 0;
int wl_initialized = 0;
int ws_initialized = 0;
int wp_initialized = 0;





//
// ===============================================================
//

//
// ## timer ##
//

int objectX;
int objectY;
int deltaX;
int deltaY;
//int deltaValue = 4;
int deltaValue = 1;
int __count=0;
unsigned long CPU_USAGE[32];



//
// == Prototypes =====================================================
//


//Arg: Endere�os dos buffers contendo os chars.
int 
SendARP ( 
    unsigned long source_ip, 
    unsigned long target_ip, 
    unsigned long target_mac );


void testSendARP (void);


int
__SendMessageToProcess ( 
    int pid, 
    struct window_d *window, 
    int message,
    unsigned long long1,
    unsigned long long2 );


int gdeshell_save_config_file (void);


// ==== Prototypes ====

void die (char *str);
void error ( char *msg, char *arg1, char *arg2 );
void fatal ( char *msg, char *arg1, char *arg2 );

//isso foi para stdlib.c
//void *xmalloc( int size);

char *concat ( char *s1, char *s2, char *s3 );
char *save_string ( char *s, int len );

int shell_save_file (void);

void shellInitSystemMetrics (void);
void shellInitWindowLimits (void);
void shellInitWindowPosition (void);
void shellInitWindowSizes (void);

// testes de scroll.
void testScrollChar (int c);

// row support

void textSetTopRow ( int number );
void textSetBottomRow ( int number );
int textGetTopRow (void);
int textGetBottomRow (void);

void clearLine ( int line_number );
void testShowLines (void);

void testChangeVisibleArea (void);
void updateVisibleArea ( int direction );
void shellRefreshVisibleArea (void);


// Procedimento de janela principal do aplicativo.
unsigned long 
shellProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

// di�logo para alimentar o terminal usado pelos aplicativos.
int 
feedterminalDialog ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

// Procedimento de janela da topbar.
unsigned long 
shellTopbarProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
 


//
// == Functions ==============================================
//


void tty_test (void)
{

    debug_print("tty_test:[FIXME]\n");
    return;
    
    /*
    // Virtual Console and tty.
    int __current_virtual_console = -1;
    int ____tty_id = -1;
    int ____this_tty_id = -1;
    char __wbuf2[128]; //line ?  write
    char __rbuf2[128]; //line ? read 
    int __w_size2 = 0;


        //__current_virtual_console = (int) gramado_system_call (277,0,0,0);
        //printf ("Current Virtual Console %d \n");

        //____tty_id = gramado_system_call ( 1008,0,0,0);
        //printf ("Current tty %d\n", ____tty_id);
        
        //____this_tty_id = gramado_system_call ( 266, getpid(), 0, 0 );
        //printf ("The tty for this process is %d\n", ____this_tty_id);


    // link by pid
    // #todo: Create the function link_by_pid()
    // Obs: Os sistemas costumam criar um tty e 'linkar'
    // quando chamam fork, pois fork faz o filho herdar os 
    // arquivos abertos.
    
    gramado_system_call ( 267,
        getpid(),    // master (shell?)
        getppid(),   // slave pai (terminal? init?)
        0 );

    //
    // scr
    //    
        
        // Show tty for this process.            
    ____this_tty_id = gramado_system_call ( 266, getpid(), 0, 0 );
    printf ("The tty for this process is %d\n", ____this_tty_id);
        
        
    //Escrevendo na tty desse processo e na tty slave pra leitura.
    write_ttyList ( ____this_tty_id, 
        __wbuf2, 
        __w_size2 = sprintf (__wbuf2,"THIS IS A MAGIC STRING\n")  );

    //
    // dst
    //
 
    //Obtem o tty id do pai. (init.bin??)
    ____tty_id = gramado_system_call ( 266, getppid(), 0, 0 );
    printf ("The tty for the father is %d\n", ____tty_id);

    //Lendo no tty do pai
    read_ttyList ( ____tty_id, __rbuf2, 32 );     
    printf (__rbuf2);
    */
}


//tty2
//void xxx_tty_test(void);
void xxx_tty_test(void)
{

    debug_print ("xxx_tty_test: [FIXME]\n");
    return;
    
    /*
    int ____this_tty_id = -1;
    char buf[128]; 
    
    gde_clone_and_execute("true.bin");
    
    ____this_tty_id = gramado_system_call ( 266, getpid(), 0, 0 );
    printf ("The tty for this process is %d\n", ____this_tty_id);


    int nreads = -1;

    // Read the message sended by true.bin.
    while(1)
    {
        nreads = read_ttyList ( ____this_tty_id, buf, 32 );     
        
        if ( nreads > 0){
            //printf ("=====Message:====\n");
            printf (buf);
            fflush(stdout);
            //break;
        }
    }
    */
}


// #obs: Essa rotina pode ser usada no comando top.
void ram_test (void){

    unsigned long __memorysizeBaseMemory;
    unsigned long __memorysizeOtherMemory;
    unsigned long __memorysizeExtendedMemory;
    unsigned long __memorysizeTotal;
    unsigned long __memorysizeUsed;
    unsigned long __memorysizeFree;

    __memorysizeBaseMemory     = gde_get_system_metrics (30);
    __memorysizeOtherMemory    = gde_get_system_metrics (31);
    __memorysizeExtendedMemory = gde_get_system_metrics (32);
    __memorysizeTotal          = gde_get_system_metrics (33);
 
    __memorysizeUsed = gde_get_system_metrics (34);
    __memorysizeFree = gde_get_system_metrics (35);
                
    printf (" RAM Memory info:\n");
    printf ("\n");
    printf (" BaseMemory     = (%d KB)\n", __memorysizeBaseMemory );
    printf (" OtherMemory    = (%d KB)\n", __memorysizeOtherMemory );
    printf (" ExtendedMemory = (%d KB)\n", __memorysizeExtendedMemory );
    printf (" TotalMemory    = (%d KB)\n", __memorysizeTotal );
    printf ("\n");
    printf (" TotalUsed      = (%d KB)\n", __memorysizeUsed );
    printf (" TotalFree      = (%d KB)\n", __memorysizeFree );
}


void process_stats(void){

    register int i=0;
    
    unsigned long __process_image_pa;
    unsigned long __process_image_va;
    unsigned long __process_image_size;

    for (i=100; i<109; i++){
        __process_image_pa  = gde_get_process_stats (i,18);
        __process_image_va  = gde_get_process_stats (i,17);  
        
        __process_image_size = gde_get_process_stats (i,51);  
        printf ("> pid %d: image_size=%d ", i, __process_image_size);
        printf ("pa=%x ", __process_image_pa);
        printf ("va=%x \n", __process_image_va);
    };
    
    gde_show_backbuffer();
}


void fake_sleep (unsigned long t)
{
    unsigned long i = (unsigned long) ( t * 512 );
    
    if(i == 0)
        i=512;
    
    while (i > 0){ i--; }
}




//Arg: Endere�os dos buffers contendo os chars.

int 
SendARP ( 
    unsigned long source_ip, 
    unsigned long target_ip, 
    unsigned long target_mac )
{
    gde_debug_print ("gdeshell-SendARP: [TODO]\n");

	//#todo:
	//filtrar argumentos.

    /*
    return (int) system_call ( ? , 
                    (unsigned long) source_ip, 
                    (unsigned long) target_ip, 
                    (unsigned long) target_mac );
   */
    return 0;
}


// testando o envio de um arp request usando os servi�os do kernel.
void testSendARP (void)
{
	uint8_t source_ip_address[4];
	source_ip_address[0] = 192;
	source_ip_address[1] = 168;
	source_ip_address[2] = 1;   
	source_ip_address[3] = 112; 

	uint8_t target_ip_address[4];
	target_ip_address[0] = 192;
	target_ip_address[1] = 168;
	target_ip_address[2] = 1; 
	target_ip_address[3] = 111; 
	
	uint8_t target_mac_address[6];
	target_mac_address[0] = 0xFF;
	target_mac_address[1] = 0xFF;
	target_mac_address[2] = 0xFF;
	target_mac_address[3] = 0xFF;
	target_mac_address[4] = 0xFF;
	target_mac_address[5] = 0xFF;

    int status = -1;

    status = (int) SendARP ( 
                       (unsigned long) &source_ip_address[0], 
                       (unsigned long) &target_ip_address[0], 
                       (unsigned long) &target_mac_address[0] );

    if (status != 0)
    {
        //
    }

    printf ("done\n");
}




int
__SendMessageToProcess ( 
    int pid, 
    struct window_d *window, 
    int message,
    unsigned long long1,
    unsigned long long2 )
{

    unsigned long message_buffer[5];


    if (pid<0){
        // todo: message
        return -1;
    }
	
	message_buffer[0] = (unsigned long) window;
	message_buffer[1] = (unsigned long) message;
	message_buffer[2] = (unsigned long) long1;
	message_buffer[3] = (unsigned long) long2;
	//...

    return (int) system_call ( 112 , 
                     (unsigned long) &message_buffer[0], 
                     (unsigned long) pid, 
                     (unsigned long) pid );
}
//
// ===============================================================
//




// Usado para testar o timer.
void update_cpu_usage (void)
{
    unsigned long __idle_value=0;
    unsigned long __value=0;
    int i=0;


    __count++;
    //printf ("%d ",__count);

    __idle_value = (unsigned long) gramado_system_call( 777, 0, 0, 0);

    //__value = (100 - __idle_value);
    //CPU_USAGE[__count] = __value;
    CPU_USAGE[__count] = __idle_value;
    
    if (__count < 32)
    {
        return;
    
    }else{

        __count = 0;

        // Clean
        gde_redraw_window ( cpu_window, 1 );

        // Draw
        for (i=1; i<32; i++)
        {
            // IN:
            gde_draw_text ( 
                cpu_window, 
                (i*smCharHeight), CPU_USAGE[i], 
                 COLOR_BLACK, "+");
        };

        // Show
        gde_show_window (cpu_window);
    };
}


// Usado para testar o timer.
void updateObject (void)
{
   //RECT rc;
   //GetClientRect(hwnd, &rc);

   objectX += deltaX;
   objectY += deltaY;

   if ( objectX < 2 )
   {
      objectX = 2;
      deltaX = deltaValue;
   }
   else if ( objectX > 78 ){
      objectX = 78; 
      deltaX = -deltaValue;    // Muda a dire��o.
   }
   
   
   if (objectY < 2)
   {
      objectY = 2;
      deltaY = deltaValue;
   }
   else if ( objectY > 24 ){
      objectY = 24; 
      deltaY = -deltaValue;
   }

    
	//
	// == Draw char ==============================
	//

    //update.
    //textCurrentRow = objectX;
    //textCurrentCol = objectY;

    //putchar.
    //shellInsertNextChar ( (char) 'T' );  

    shellSetCursor ( objectX, objectY );
    printf ("%c", (char) 'X');
}



//interna
//cria a janela
struct window_d *xmas_tree_window;
void *xmas_tree_buffer;
void
xmas_tree_create ( char *file_name)
{
    
    xmas_tree_window = (void *) gde_create_window ( 
                                    WT_SIMPLE, 1, 1, 
                                    "XTREE",     
                                    10, 10, 90, 130,    
                                    0, 0, COLOR_GREEN, COLOR_GREEN );

    if ( (void *) xmas_tree_window == NULL )
    { 
        return; 
    }
    
    gde_register_window ( (struct window_d *) xmas_tree_window );

    // testando malloc.
    xmas_tree_buffer = (void *) malloc (1024*50); 

    //existe um buffer
    shellui_fntos ( (char *) file_name );

    // #todo: 
    // Usar alguma rotina da API especifica para carregar arquivo.
    // na verdade tem que fazer essas rotinas na API.

    // load file.

    gramado_system_call ( 
        SYSTEMCALL_READ_FILE, 
        (unsigned long) file_name, 
        (unsigned long) xmas_tree_buffer, 
        (unsigned long) xmas_tree_buffer );
}


// interna
// voce a janela
void xmas_tree (void)
{
   //RECT rc;
   //GetClientRect(hwnd, &rc);

   objectX += deltaX;
   objectY += deltaY;

   if ( objectX < 2 )
   {
      objectX = 2;
      deltaX = deltaValue;
   }
   else if ( objectX > 78 ){
      objectX = 78; 
      deltaX = -deltaValue;    // Muda a dire��o.
   }
   
   
   if (objectY < 2)
   {
      objectY = 2;
      deltaY = deltaValue;
   }
   else if ( objectY > 24 ){
      objectY = 24; 
      deltaY = -deltaValue;
   }

    
	//
	// ## test ##
	//
	
	//update.
	//textCurrentRow = objectX;
    //textCurrentCol = objectY;
   
    //putchar.
	//shellInsertNextChar ( (char) 'T' );  
	
	shellSetCursor ( objectX, objectY );
	
	//printf ("%c", (char) 'X');
	//shellDisplayBMPEx ( (char *) tokenList[i], (int) (200) );
	
    gde_replace_window ( 
        (struct window_d *) xmas_tree_window, 
        objectX, 
        objectY );
    
    //decodificando ??
	gde_display_bmp ( (char *) xmas_tree_buffer, objectX, objectY ); 
    
    //gde_redraw_window( (struct window_d *) xmas_tree_window, 1); 
    //apiShowWindow ((struct window_d *) xmas_tree_window);
    
    gde_show_backbuffer ();
}


//
// ===============================================================
//



//
// ==== Internals ====
//

static inline void pause (void)
{
    asm volatile ("pause" ::: "memory"); 
} 


/* 
 REP NOP (PAUSE) 
 is a good thing to insert into busy-wait loops. 
 */

static inline void rep_nop (void)
{
    asm volatile ("rep;nop": : :"memory");
}

#define cpu_relax()  rep_nop()


// vamos apenas carregar um arquivo qualquer.
// OK: funcionou no qemu.
void __load_path_test(void)
{

    char __path[] = "/ETC/TEST1.CPP";

    void *__address = 0;
    unsigned long ___size_limit=0;

    //___size_limit = (200*1024); // 200KB
    ___size_limit = (1*1024);

    // endereço para carregar o arquivo
    __address = (void *) malloc (___size_limit);
    
    if ( (void*) __address == NULL )
    {
        printf ("__load_path_test: [FAIL] __address\n");
        return;
    }

    char *buffer = (char *) __address;

    // Load
    // Using the libcore.
    
    gde_load_path ( 
        (char *)         __path, 
        (unsigned long)  buffer, 
        (unsigned long)  ___size_limit );

    
    int mark = (___size_limit - 1);
    buffer[mark] = 0;
    
    // show:
    printf ( "File = {%s}\n", buffer );
    
    printf ("__load_path_test: done\n");
}



void quit ( int status )
{
    _running = 0;
}
 


/*
void reader_loop ();
void reader_loop ()
{
    extern int indirection_level;
    
	int our_indirection_level;
    
	COMMAND *current_command = (COMMAND *) NULL;

    our_indirection_level = ++indirection_level;

    while (!EOF_Reached)
    {
        sighandler sigint_sighandler ();
        
		int code = setjmp (top_level);

        signal (SIGINT, sigint_sighandler);

        if (code != NOT_JUMPED)
 	    {
	        indirection_level = our_indirection_level;

	        switch (code)
	        {
	            //Some kind of throw to top_level has occured. 
	            case FORCE_EOF:
	            case EXITPROG:
	                current_command = (COMMAND *) NULL;
	                EOF_Reached = EOF;
	                goto exec_done;

	            case DISCARD:
	                //Obstack free command elements, etc. 
	                break;
					
	            default:
	                programming_error ("Bad jump %d", code);
	        }
	   }

      executing = 0;
		
      dispose_used_env_vars ();

      if (read_command () == 0)
	  {
	      if (global_command) 
		  {
	          current_command = global_command;

	          current_command_number++;

	          //POSIX spec: "-n  The shell reads commands but does
	          //not execute them; this can be used to check for shell
	          //script syntax errors.  The shell ignores the -n option
	          //for interactive shells. " 

	          if (interactive || !read_but_dont_execute)
	          {
		          executing = 1;
		          execute_command (current_command);
	          }

	         exec_done:
	         
			  if (current_command)
	             dispose_command (current_command);
	             QUIT;
	      }
		  
	  }else{
		  
	      // Parse error, maybe discard rest of stream if not interactive. 
	      if (!interactive)
	          EOF_Reached = EOF;
	  };
		
      if (just_one_command)
	      EOF_Reached = EOF;
    
	}; //while
	
    indirection_level--;
}
*/



/*
 ***********************************************
 * shellProcedure:
 *     Procedimento de janela.
 *     LOCAL
 */


unsigned long 
shellProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    unsigned long input_ret=0;
    unsigned long compare_return=0;
    int q=0;

    int c=0;


    // #bugbug
    // switch sempre da problemas de compilacao ...
    // corrija os problemas ... use returns.
    
    switch (msg)
    {

        case MSG_KEYDOWN:
            //...
            switch (long1)
            {
                //case EOF:  break;

                // Null key.
                case 0:
                    cpu_relax(); 
                    return (unsigned long) 0;
                    break;

                // [Enter].
                // Finaliza a string e compara.
                // #obs: 
                // #importante 
                // Se essa janela for a janela do gdeshell, então 
                // a rotina de comparação poderá fazer um refresh 
                // dessa janela. 
                // #obs: talvez esse refresh nem seja necessário.
                // cada rotina chamada que fará seu próprio refresh 
                // se conseguir.
                
                case VK_RETURN:
                    input('\0');
                    shellCompare (window);
                    goto done;
                    break; 


                // #test
                case VK_TAB: printf ("\t"); goto done; break;
                
                case 0x07: printf ("TREMA\n"); goto done; break;
                
                //keyboard arrows
                case 0x48: printf ("UP   \n"); goto done; break;
                case 0x4B: printf ("LEFT \n"); goto done; break;
                case 0x4D: printf ("RIGHT\n"); goto done; break;
                case 0x50: printf ("DOWN \n"); goto done; break;


                // home end
                case 0x47: printf ("HOME\n"); goto done; break;
                case 0x4F: printf ("END \n"); goto done; break;

                //pageup pagedown
                case 0x49: printf ("PAGEUP   \n"); goto done; break;
                case 0x51: printf ("PAGEDOWN \n"); goto done; break;

                // insert delete
                case 0x52: printf ("INSERT\n"); goto done; break;
                case 0x53: printf ("DELETE\n"); goto done; break;


                // #todo
                // falta configurar prompt[] usado por input();
                // falta configurar LINES[]...
                case 0x8: // backspace
                //case 0x7f: // del
                case VK_BACK:  //0x0E
                    // Apaga o char na tela, na linha de comandos e no buffer.
                    if ( textCurrentCol > 0 )
                    { 
                        // ok. funcionou. 
                        // a linha de comandos. prompt[]
                        putchar(0x8);  input(0x8);  // volta
                        putchar(0x20); input(0x20); // apaga
                        putchar(0x8);  input(0x8);  // volta
                        fflush(stdout);             // mostra sem mudar de linha.
                        //o buffer.
                        //volta um char no buffer e apaga na nova posiçao.
                        textCurrentCol--; 
                        LINES[textCurrentRow].CHARS[textCurrentCol] = 0;       
                    }
                    goto done;
                    break;


                // Mensagens de digitação.
                // Enfilera os caracteres na string 'prompt[]' 
                // para depois ser comparada com outras strings.
                // Coloca na memória de video virtual,
                // Que é semelhante a vga, contendo char e atributo.
                // Isso mostra o caractere na tela.
                default:
                    input ( (unsigned long) long1 );  
                    shellInsertNextChar ( (char) long1 );  
                    goto done;
                    break; 
            };
            goto done;
            break;


        case MSG_KEYUP: 
            break;
 

        case MSG_SYSKEYDOWN: 
            switch (long1)
            {

                case VK_F1: 
                    debug_print(" [F1] "); 
                    gde_clone_and_execute ("launcher.bin");
                    exit(0);
                    break;
                    
                case VK_F2: 
                    debug_print(" [F2] "); 
                    gde_clone_and_execute ("gramcode.bin");
                    exit(0);
                    break;
                    
                case VK_F3: 
                    debug_print(" [F3] "); 
                    gde_clone_and_execute ("sysmon.bin");
                    exit(0);
                    break;
                    
                case VK_F4: 
                    debug_print(" [F4] "); 
                    gde_clone_and_execute ("gwssrv.bin");
                    exit(0);
                    break;

                case VK_F9: 
                    debug_print(" [F9] "); 
                    gde_clone_and_execute ("reboot.bin");
                    exit(0);
                    break;

                case VK_F10: 
                    debug_print(" [F10] "); 
                    gde_clone_and_execute ("reboot.bin");
                    exit(0);
                    break;

                case VK_F11: 
                    debug_print(" [F11] "); 
                    gde_clone_and_execute ("reboot.bin");
                    exit(0);
                    break;

                case VK_F12: 
                    debug_print(" [F12] "); 
                    gde_clone_and_execute ("reboot.bin");
                    exit(0);
                    break;

            };
            goto done;
            break;

		//Obs:
		//essas teclas são tratadas pelo procedimento do sistema.
		//mas alguma tecla personalizada pode ser  tratada pelo aplicativo,
		//como o context menu [Application Key]
        case MSG_SYSKEYUP:
            switch (long1)
            {
                // Menu.
                case VK_APPS:
                    gde_message_box ( 3, "gdeshell:", "VK_APPS" );
                    break;
            };
            goto done;
            break;


        // Commands.
        case MSG_COMMAND:
            switch (long1)
            {
                case CMD_ABOUT:
                    printf ("MSG_COMMAND-CMD_ABOUT\n");
                    break;

                // Nothing for now!
                default: break;
            };
            goto done;
            break;

       //#todo
        case MSG_CLOSE:   
            printf ("MSG_CLOSE\n");   
            exit(0);
            gdeshell_exit();
            break;
            
        case MSG_DESTROY: printf ("MSG_DESTROY\n"); break;


        // MSG_MOUSEKEYDOWN
        case 30:
            debug_print ("gdeshell: MSG_MOUSEKEYDOWN\n"); goto done;
            break;

        // MSG_MOUSEKEYUP
        case 31:
            debug_print ("gdeshell: MSG_MOUSEKEYUP\n"); goto done;
            break;


        //Quando a aplicativo em user mode chama o kernel para 
        //que o kernel crie uma janela, depois que o kernel criar a janela,
        //ele faz uma chamada ao procedimento de janela do aplicativo com a mensagem 
        //MSG_CREATE, se o aplicativo retornar -1, ent�o a rotina em kernel mode que 
        //esta criando a janela, cancela a janela que est� criando e retorn NULL.		
        case MSG_CREATE: 
            printf ("MSG_CREATE\n"); 
            break;


        // #IMPORTANTE
        // A API CHAMA ISSO DE TEMPOS EM TEMPOS 
        // DE ACORDO COM A CONFIGURACAO FEITA ANTES POR ESSE APP.
        case MSG_TIMER:
            //printf("TIMER\n");
            update_cpu_usage();  // cpu usage viwer.
            //updateObject();    // moving char.
            //xmas_tree();       // moving image.
            break; 


        //case MSG_SETFOCUS:   break;
        //case MSG_KILLFOCUS:  break;


        // Isso pinta os elementos da �rea de cliente.
        // Essa mensagem � enviada para o aplicativo quando 
        // a fun��o 'update window' � chamada.
        // Como estamos em fullscreen, n�o h� o que fazer aqui.
        //case MSG_PAINT: break;

        
        // o driver de rede notifica o aplicativo de que
        // tem conte�do no buffer previamente configurado pelo aplicativo.
        // veja gde_setup_net_buffer;
        //__net_buffer[] 
        // #todo: ler o __net_buffer        
        case 1444:
           printf ("gdeshell: 1444 net driver notification! \n"); 
           printf (" We got data in our buffer :)\n");
           break;


         // Receberemos uma mensagem vida do servidor de rede.
         case MSG_AF_INET:
             printf ("gdeshell: MSG_AF_INET\n");
             break;


         // Receberemos uma mensagem vida do servidor de rede.
         case MSG_NET_DATA_IN:
             printf ("gdeshell: MSG_NET_DATA_IN\n");
             while ( (c = fgetc( (FILE *) long1)) >= 0 )
                 printf ("%c", c); 
             break;


         // esse processo � notificado sobre o recebimento de um pacote ipv4    
         //receberemos uma mensagem vida do servidor de rede.
         case MSG_NETWORK_NOTIFY_PROCESS:
             printf ("gdeshell: MSG_NETWORK_NOTIFY_PROCESS\n");
              while ( (c = fgetc( (FILE *) long1)) >= 0 )
                  printf ("%c", c); 
             break;             

		//Faz algumas inicializa��es de posicionamento e dimens�es.
        //case MSG_INITDIALOG:
        //    break;

        //Torna a janela vis�vel.
        //case MSG_SHOWWINDOW:
        //    break; 

        // Nothing for now!
        default:
            debug_print ("gdeshell: default message\n");
            break;
    };


    // Nothing for now !

    // Calling system procedure.

done:
    return (unsigned long) gde_def_dialog (window,msg,long1,long2);
}


// #todo: Delete
void shellWaitCmd (void)
{
	// Nothing.
}



/*
 ****************
 * shellCompare:
 *     Compara comandos digitados com palavras chave.
 *     Compara a palavra em 'prompt[]' com outras e chama o servi�o.
 * o enter foi o caractere digitado, vamos comparar palavras.
 *
 * Credits:
 * + Stephen Brennan - https://brennan.io/2015/01/16/write-a-shell-in-c/
 * + Frederico Martins Nora (frednora)
 */


#define LSH_TOK_DELIM   " \t\r\n\a" 
#define LSH_TOK_DELIM2  " \t\r\n\a+!:=/.<>;|&" 
#define SPACE " "
#define TOKENLIST_MAX_DEFAULT 80


unsigned long shellCompare (struct window_d *window)
{
    // Token support.

    char *tokenList[TOKENLIST_MAX_DEFAULT];
    char *token;
    int ____token_count=0;
    int ____last=0;
    int i = 0;
    int j = 0;


    int __background = 0;   //&
    unsigned long ret_value=0;
    int q=0;    //dialog
    char *c;
    int absolute=0;     // #bugbug: Absolute pathname?


	// #importante:
	// Transferir toda alinha de comando para a mem�ria compartilhada.
	// Obs: 
	// Possivelmente isso n�o continua� assim, mas por enquanto t� bom.

    unsigned char *shared_memory = (unsigned char *) (0xC0800000 -0x100);

    // Linha de 80 chars no max.
    for ( i=0; i<80; i++ )
    {  
        shared_memory[i] = prompt[i];  
    };


    // Temos uma linha de comando em prompt[]
    // Digitada pelo usu�rio de gdeshel.
    // Quem pegou o input de teclado ??
    // N�o foi o terminal virtual. Como deveria ser.
 
NewCmdLine:

    // #debug
    // printf("prompt:{%s}\n",prompt);

    // Lidando com chars da linha de comando.

    c = prompt;

	// $(NULL)
	// [ENTER] finalizou a atring antes de ter digitado alguma coisa.
	// Se alguem pressiona [ENTER] com prompt vazio d� page fault ?
	// Isso cancela caso o buffer esteja vazio.

    if ( *c == '\0' )
    {
        shellInsertLF();
        goto exit_cmp;
    }


    //
    // Fixing command line.
    //

	// $ ' ' ou \t 
	// Se a linha d comando come�a com espa�o.
	// S� faz o tratamento com while se for igual a ' '.

fixing_command_line:

    if ( *c == ' ' || *c == '\t' )
    {
        // #importante:
        // Aqui estamos tratando uma linha de comando inteira.
        // Enquanto c for diverente de ' ' c avan�a.
        // isso elimina os espa�os para c[]

        j=0;
        while ( *c == ' ' || *c == '\t' )
        { 
            // #debug
            // Window limits.
            // Isso significa que uma string construida em prompt[] 
            // n�o foi corretamente finalizada, ou algum problema 
            // no while anterior.
            // printf("#debug \n");

            j++;
            if ( j > wlMaxColumns ){
               printf ("shellCompare: The command line is too long or there is no terminator! \n");
               exit(1);
            }

            c++; 
        };


		// Se depois de eliminarmos os espa�os encontrarmos um '\0' 
		// de fim de string, significa que o usu�rio digitou um monte 
		// de espa�os depois apertou enter. N�o h� mais o que fazer.

        if ( *c == '\0' )
        {
            shellInsertLF();
            goto exit_cmp;
        }


		// ??
		// Desrepeitamos o limite imposto pelo fim da string.
		// por isso temos que fazer a marca��o exata do in�cio 
		// da linha de comando e do fim da linha de comando.
		// |            |.......|        |
		// start       left   right     end

		// Quando da linha de comando develos mover para o in�cio
		// do buffer?
		// Tamanho da janela menos a quantidade de espa�os encontrados.
 
        int ____coolbytes = (wlMaxColumns-j);

		// Copia todo o resto da linha para o inpicio da linha.
		// Se enquanto estamos copiando, ja copiamos o finalizador 
		// de string, ent�o n�o precisamos copiar mais coisa alguma.
		// Agora a linha de comando est� ajustada.

        for ( j=0; j<____coolbytes; j++ )
        {
            prompt[j] = c[j];

            if ( *c == '\0' ){  goto commandlineOk;  }
        };


		//#bugbug
        //se estamos aqui � porque copiamos quase 80 chars.		
    };

    // Command line ok.

commandlineOk:

    // #debug
    // printf("prompt:{%s}\n",prompt);	

    //>/
    //>.
    //>./
    //>..
    //>../
	
	// #importante:
	// Vamos checar se o pathname � absoluto ou relativo.
	// +Se tiver barra, significa que o pathname � absoluto e 
	// come�a no diret�rio raiz do volume do sistema. root:/volume1/
	// +Se come�ar por root:/ tamb�m � absoluto.
	// +Pathname relativo � somente aquele que � apenas um nome 
	// de arquivo dentro do diret�rio atual. Como: 'name' ou name1/name2,
	// sem barra ou ponto.
	// $/ � o diret�rio raiz do volume do sistema.
	// $v/ � o diret�rio raiz do vfs.	
 

    absolute = absolute_pathname ( (char *) prompt );

    switch (absolute){
        case 0:  goto this_directory;  break;
        case 1:  goto check_directory; break;
        case 2:
        default:
            goto this_directory;
            break;
    };


//precisamos checar em que diret�rio 
//o programa est�.
//o comando tem um pathname absoluto ...
//Precisamos invocar esse programa 
//que est� em um diret�rio apontado no pathname.
//ex: ../cmd 	

check_directory:
	
	
//O primeiro elemento da linha de comandos 
// � um comando simples	
// cd ..
this_directory:	
	
	//if( *prompt == (char) '\0' ){
	//    goto exit_cmp;	
	//}
	
	// O input pode ser copiado aqui, ent�o manipularemos essa vari�vel.
	//char *FileName;
	
	//
	// ?? E se tivermos v�rias palavras na linha de comando ??
	//
		
    // Returns first token 
    //char *token = strtok(prompt, " -");
	
	//#debug
    //printf("shellCompare: Testing ...\n");
    //refresh_screen();

    //
    // The token list.
    //

    // ==========================================
    // ++
    // Get the first call returns pointer to first part of user_input 
    // separated by delim.
    // Isso pega a primeira palavra digitada.
    // Isso inicializa a fun��o strtok. que continua� pegando
    // desse mesmo prompt.
    // Salva a primeira palavra digitada, que pegamos imediatamente
    // antes.
    // #todo: 
    // Isso precisa ser limpado sempre.

    tokenList[0] = strtok ( prompt, LSH_TOK_DELIM );

    token = (char *) tokenList[0];

    i=0;  
    while ( token != NULL )
    {
        // Coloca na lista.
        tokenList[i] = token;

        // Pega mais um da linha de comandos.
        token = strtok ( NULL, LSH_TOK_DELIM );

        i++;
        ____token_count = i;
    }; 

    //Finalizando a lista.
    tokenList[i] = NULL;
    //--
    // ==========================================


    // Last command.
    // When you run a command in the background, you do not have 
    // to wait for the command to finish before running another command.

    //===============================
    //++
    if (____token_count >= 1 )
    {
         ____last = ____token_count -1;
    }
    
    // It's is not a background command.
    __background = 0;

    // Check if it is a background command.
    if ( strncmp( (char*) tokenList[ ____last ], "&", 1 ) == 0 )
    {
        __background = 1;
    }
    //--
    //===============================



	//
	//#importante:
	//nesse momento todos os argumentos est�o certinhos no vetor.
	//j� conferimos.
	//

	//#debug
    //printf("shellCompare: %s \n", tokenList[i] );
    //refresh_screen();	

	//#debug
    //printf("shellCompare: Test done!\n");
    //refresh_screen();	


	// Zerando o �ndice do tokenList
    i=0;	
   
    //printf("shellCompare: Testing ...\n");
    //refresh_screen();
   
    // Keep printing tokens while one of the
    // delimiters present in str[].
    //while(token != NULL)
    //{
    //    printf("%s\n", token);
	//	refresh_screen();
	//	token = strtok(NULL, " -");
    //}
	
	
		
	//do_command(argc, argv);
	
    //goto do_command;
//do_command:

    // nothing.

    //
    // == Compare ===================================================
    //

    // #test
    // A partir daqui teremos comandos que sao aplicativos,
    // ou comandos que falharam, ou comandos embutidos.
    // Ordem:
    // + Primeiro alguns comandos extra.
    // + Depois comandos em ordem alfab�tica.

do_compare:

    // Vamos mostrar o output na proxima linha.
    shellInsertLF();


    //
	// ## identificadores de inicia��o de linha ##
	//
	
	//Esses identificadores determinam o que 
	//se vai encontrar na linha. E n�o existe volta, 
	//o que o identificador determinou ser� obedecido.
	
	//
	// ## Lista de identificadores ligado a execuss�o ##
	//
	// (do)
	//
	// dobin - Execute programa .bin
	// dotry - Tenta executar qualquer extens�o
	// Obs: Esses comandos efetuam goto 
	// dentro desse c�digo, saltando diretamente 
	// para as rotinas executadoras de programas ou scripts.
	// Obs: O nome do progama est� em tokenList[1] e os 
    // argumentos nos pr�ximos tokenList.	


    // #bugbug
    // Podemos cancelar esse comandos extra no começo.
    // Pois estao sem uso.

    if ( strncmp ( (char *) tokenList[0], "dobin", 5 ) == 0 ){
        goto dobin;
    }

    if ( strncmp ( (char *) tokenList[0], "dotry", 5 ) == 0 ){
        goto dotry;
    } 

    //um comando no shell pede para executar um script
    if ( strncmp ( (char *) tokenList[0], "dosh", 4 ) == 0 ){
        goto dosh;
    }


    // =============================================================
    //++
    // Testando tokenList?
    // Esse comando eh usado para testes de comando.

    int __z=0;

    if ( strncmp ( prompt, "token", 5 ) == 0 )
    {
        printf ("Testing tokenList ...\n");
        printf ("Total={%d}\n\n", ____token_count );
        //printf ("Comand = %s \n", tokenList[__z] );

        for (__z=0; __z<____token_count; __z++)
        {
            token = (char *) tokenList[__z];

            if ( token == NULL ){
                goto exit_cmp;
            }else{
                printf ("%d = {%s}\n", __z, tokenList[__z] );
            };
        };

        if (____token_count >= 1 )
             ____last = ____token_count -1;


        // Check least command
        // se o �ltimo comando for um & ent�o ...
        // Acionamos a flag.
            
        // & = Commencial 'and'.
        // When you run a command in the background, you do not have to wait for the 
        // command to finish before running another command.
        if ( strncmp ( (char*) tokenList[ ____last ], "&", 1 ) == 0 )
        {
            printf ("The last comand is %s\n", tokenList[ ____last ] );
            //__background = 1;
        }

        printf ("\n");
        goto exit_cmp;
    };
    //--
    // =============================================================


// =================================================================
// == The commands start here ======================================
// =================================================================

    // #obs:
    // Em ordem alfabética.


    // about 
    if ( strncmp ( prompt, "about", 5 ) == 0 ){
        shellSendMessage ( NULL, MSG_COMMAND, CMD_ABOUT, 0);
        goto exit_cmp;
    }


    // apic
    // #todo: Call kernel to initialize api support.
    if ( strncmp ( prompt, "apic", 4 ) == 0 ){
        gde_debug_print("gdeshell: Testing apic\n");
        printf("apic: TODO: Call kernel to initialize apic\n");
        //gramado_system_call(???,0,0,0);
        goto exit_cmp;
    }

    // arp-test
    if ( strncmp ( prompt, "arp-test", 8 ) == 0 ){
        //testSendARP ();
        __shellTestARP ();
        goto exit_cmp;
    }


    // boot
    // #bugbug
    // Cuidado.
    unsigned long __bi_disk_number;
    if ( strncmp ( prompt, "boot", 4 ) == 0 ){
        __bi_disk_number = (unsigned long) gramado_system_call ( 
                                               293, 3, 0, 0 );
        printf ("disk_number %x \n", __bi_disk_number );
        goto exit_cmp;
    }


    // cd - Change dir.
    if ( strncmp ( prompt, "cd", 2 ) == 0 )
    {
        i++;   // Next token.
        
        token = (char *) tokenList[i];   // Get next token.

        if ( token == NULL ){
            printf ("cd: No arg\n");
        }else{

			//#bugbug: n�o � possivel fazer isso por enquanto,
			//pois n�o estamos fazendo parse de char por char.
			//if( gramado_strncmp( (char*) tokenList[i], ".", 2 ) == 0 )
			//{}

            //Apaga o nome do �ltimo diret�rio.
            if ( strncmp( (char*) tokenList[i], "..", 2 ) == 0 ){
                shell_pathname_backup ( current_workingdiretory_string, 1 ); 
                goto exit_cmp;
            }

            // Updating the current working directory string.
            // Updating the file system support in the kernel.
            shellUpdateWorkingDiretoryString ( (char *) tokenList[i] );
        };

		// o que segue o comando cd � um pathname.
		//@todo: podemos checar se o pathname � absoluto,
		//e onde se encontra o arquivo que queremos.
		//cd_buitins();
        goto exit_cmp;
    }


    // close
    if ( strncmp( prompt, "close", 5 ) == 0 )
    {
        printf ("gdeshell: Testing close and fclose\n");
        
        // ok
        //shellSendMessage ( NULL, MSG_CLOSE, 0, 0 );
        
        // ok
        //close(0); close(1); close(2);
        //close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);
        //close(fileno(stdin)); close(fileno(stdout)); close(fileno(stderr));
        
        // #bugbug: 
        // It fails. 
        // Something is wrong when we create these structures in ring3
        // see: stdio initialization on rtl.
        fclose(stdin);  fclose(stdout);  fclose(stderr);
        
        goto exit_cmp;
    }
    
    if ( strncmp( prompt, "flush", 5 ) == 0 )
    {
        printf ("gdeshell: Testing fflush\n");
        fflush(stdin);  fflush(stdout);  fflush(stderr);
        goto exit_cmp;
    }


    // Clear the screen.
    if ( strncmp( prompt, "CLEAR", 5 ) == 0 ||
         strncmp( prompt, "clear", 5 ) == 0 ||
         strncmp( prompt, "CLS", 3 ) == 0 || 
         strncmp( prompt, "cls", 3 ) == 0 )
    {
        cls_builtins ();
        goto exit_cmp;
    }

    // ??
    // copy - Esse comando pode ser usado pra testar o fs.
    if ( strncmp( prompt, "copy", 4 ) == 0 )
    {
        copy_builtins ();
        goto exit_cmp;
    }

    // cpu-info 
    if ( strncmp( prompt, "cpu-info", 8 ) == 0 ){
        gramado_system_call ( 47, 0, 0, 0 );
        goto exit_cmp;
    }

    // del - Delete a file or directory. ??
    if ( gramado_strncmp( prompt, "del", 3 ) == 0 ){
        del_builtins();
        goto exit_cmp;
    }

    // devices - Mostra a lista de dispositivos deviceList[]
    if ( gramado_strncmp( prompt, "devices", 7 ) == 0 ){
        gramado_system_call ( 770, 0, 0, 0 );
        goto exit_cmp;
    }


    // dir and ls.
    // List files and folders.
    // #todo: Maybe use the sc82.
    if ( gramado_strncmp ( prompt, "dir", 3 ) == 0 || 
         gramado_strncmp ( prompt, "ls",  2 ) == 0 )
    {
        // Argument 1.
        i=1;
        token = (char *) tokenList[i];

        // Listar sem indicar o nome o diretório.
        if ( token == NULL ){

            gde_enter_critical_section ();
            system_call ( 177,
                (unsigned long) root_string,  // "/" 
                (unsigned long) 0, 
                (unsigned long) 0 ); 
            gde_exit_critical_section ();

        // Listar indicando o nome do diretório.
        }else{

            // Listar os arquivos em um diretório dado seu nome.
            gde_enter_critical_section ();
            system_call ( 177,
                (unsigned long) tokenList[i],  //typed pathname.
                (unsigned long) tokenList[i], 
                (unsigned long) tokenList[i] ); 
            gde_exit_critical_section ();

            // ...
        };

		// o que segue o comando dir � um pathname.
		//@todo: podemos checar se o pathname � absoluto,
		//e onde se encontra o arquivo que queremos.
        //se o pathname for null ent�o o comando atua sobre o pwd
        
        //dir_builtins();
        goto exit_cmp;
    };


    // disk-info
    if ( gramado_strncmp( prompt, "disk-info", 9 ) == 0 ){
        shellShowDiskInfo ();
        goto exit_cmp;
    }

    // #todo:
    // float support.
    if ( gramado_strncmp( prompt, "double", 6 ) == 0 )
    {
        printf ("double is a double precision float number\n" );
        goto exit_cmp;
    }

    // exec - Executa um programa fechando o shell.
    // o que segue o comando exec � um pathname.
    //@todo: podemos checar se o pathname � absoluto,
    //e onde se encontra o arquivo que queremos.
    if ( gramado_strncmp ( prompt, "exec", 4 ) == 0 ){
        exec_builtins();
        ShellFlag = SHELLFLAG_EXIT;
        goto exit_cmp;
    }


    // exit - Exit the application.
    if ( gramado_strncmp( prompt, "exit", 4 ) == 0 )
    {
        //exit_builtins();
        //ShellFlag = SHELLFLAG_EXIT;
        gdeshell_exit();
        goto exit_cmp;
    }
    
    // escape.
    // Teste some escape sequences.
    // O tratador eh o console virtual dentro do kernel.
    // #define __ESC "\x1b"
    // #define __CSI "\x1b["
    //See:
    //http://ascii-table.com/ansi-escape-sequences-vt-100.php
    //https://notes.burke.libbey.me/ansi-escape-codes/
    if ( gramado_strncmp( prompt, "escape", 6 ) == 0 )
    {
        printf("~escape: Testing some escape sequences.\n");
        //printf("tes\x1b[7mte\n");
        //printf("tes\x1B[?25hte\n"); 
        //printf("\n");
        //printf("\n");
        //printf("\n");
        //printf("\n");
        goto exit_cmp;
    }

    //fprintf
    if ( gramado_strncmp( prompt, "fprintf", 7 ) == 0 )
    {
        fprintf(stdin,  "STDIN  \n");
        fprintf(stdout, "STDOUT \n");
        fprintf(stderr, "STDERR \n");
        goto exit_cmp;
    }

    //fputs
    if ( gramado_strncmp( prompt, "fputs", 5 ) == 0 )
    {
        fputs("STDIN  \n",stdin );
        fputs("STDOUT \n",stdout);
        fputs("STDERR \n",stderr);
        goto exit_cmp;
    }


    // gethostname 
    char *my_hostname;
    char hostbuffer[256]; 
    if ( gramado_strncmp ( prompt, "gethostname", 11 ) == 0 )
    {
        gethostname (hostbuffer, sizeof(hostbuffer));
        printf(">>> ");  printf (hostbuffer);  printf("\n");
		//#obs: Isso funciona.
		//vai colocar num buffer ba libc
		//my_hostname = ( char *) __gethostname();
		//printf(">> ");
		//printf (my_hostname);
		//printf("\n");
        goto exit_cmp;
    }

    /*
    // getusername 
    char *my_username;
	if ( gramado_strncmp ( prompt, "getusername", 11 ) == 0 )
	{
		//vai colocar num buffer ba libc
		my_username = (char *) getlogin();
		printf (my_username);
	    //getusername ( current_user_name, (size_t) 64);
	    //printf (current_user_name);
        goto exit_cmp;
    };
     */    


    // ws
    // Get the WS environment variable.
    char *env_string;
    if ( gramado_strncmp( prompt, "ws", 2 ) == 0 )
    {
        env_string = (char *) getenv ("WS");
        if ( (void*) env_string != NULL ){
            printf (" The window server is %s .\n", env_string);
        }
        goto exit_cmp;
    }


    // get-ptsname
    // See: stdlib.c  
    // Vai colocar num buffer ba libc
    // IN: fd do master.
    char *my_ptsname;  //ponteiro para um buffer na libcore.
    if ( gramado_strncmp ( prompt, "get-ptsname", 11 ) == 0 )
    {
        my_ptsname = (char *) ptsname (1);
        printf (my_ptsname);
        goto exit_cmp;
    }


    // get-ptsname2
    // See stdlib.c
    // IN: fd do master, buf, buflen
    char ptsname_buffer[64]; 
    if ( gramado_strncmp ( prompt, "get-ptsname2", 12 ) == 0 )
    {
        ptsname_r ( 1,ptsname_buffer, sizeof(ptsname_buffer));
        printf (ptsname_buffer);
        goto exit_cmp;
    } 


    // getpids
    if ( gramado_strncmp ( prompt, "getpids", 7 ) == 0 )
    {
        printf ( "Window Server PID %d\n",  gde_get_pid(GETPID_WS) );
        printf ( "Window Manager PID %d\n", gde_get_pid(GETPID_WM) );
        goto exit_cmp;
    }


    // getpid
    if ( gramado_strncmp( prompt, "getpid", 6 ) == 0 ){
        getpid_builtins ();
        goto exit_cmp;
    }

    // getppid
    if ( gramado_strncmp( prompt, "getppid", 7 ) == 0 ){
        getppid_builtins();
        goto exit_cmp;
    }

    // getuid - get user id
    if ( gramado_strncmp( prompt, "getuid", 6 ) == 0 ){
        getuid_builtins();
        goto exit_cmp;
    }

    // getgid - get group id
    if ( gramado_strncmp( prompt, "getgid", 6 ) == 0 ){
        getgid_builtins();
        goto exit_cmp;
    }

    //get-usersession (security)
    if ( gramado_strncmp( prompt, "get-usersession", 15 ) == 0 ){
        shellShowUserSessionID();
        goto exit_cmp;
    }

    //get-room (security)
    if ( gramado_strncmp( prompt, "get-room", 8 ) == 0 ){
        shellShowWindowStationID(); //mudar o nome;
        goto exit_cmp;
    }

    //get-desktop (security)
    if ( gramado_strncmp( prompt, "get-desktop", 11 ) == 0 ){
        shellShowDesktopID();
        goto exit_cmp;
    }

    // gramado
    // Initialize the window server and the window server
    // will call the first client.
    if ( gramado_strncmp( prompt, "gramado", 7 ) == 0 )
    {
        printf ("type: $ gwssrv &\n");
        goto exit_cmp;
    }
    
    // heap
    void *hBuffer;
    if ( gramado_strncmp( prompt, "heap", 4 ) == 0 )
    {
        printf ("Testing heap\n");
        hBuffer = (void *) malloc ( 1024*100 );       // 100 kb
        //hBuffer = (void *) malloc ( 1024*1024*3 );  // 3 mb
        //...
        if ( (void *) hBuffer == NULL ){
            printf("malloc fail 100kb\n");
        }else{
            printf("malloc ok 100kb\n");
        };
        printf("done\n");
        goto exit_cmp;
    }


    // help
    int help_id=0;
    if ( gramado_strncmp( prompt, "HELP", 4 ) == 0 || 
         gramado_strncmp( prompt, "help", 4 ) == 0 || 
         gramado_strncmp( prompt, "?", 1 ) == 0 )
    {
        //#bugbug: NULL pointer?
        //help_id = (int) atoi( tokenList[1] );
        //printf("help %d: \n",help_id);
        
        help_builtins();
        goto exit_cmp;
    }


    // ioctl
    // Testing libc funciton.
    // See: http://man7.org/linux/man-pages/man2/ioctl.2.html
    if ( gramado_strncmp( prompt, "ioctl", 5 ) == 0 )
    {
        printf ("~ioctl: tests ...\n");

        // fd request
        debug_print("stdin ============\n");
        ioctl ( STDIN_FILENO,  TCIFLUSH, 0 ); // 
        debug_print("stdout ============\n");
        ioctl ( STDOUT_FILENO, TCIFLUSH, 0 ); // console
        debug_print("stderr ============\n");
        ioctl ( STDERR_FILENO, TCIFLUSH, 0 ); // normal
        debug_print("fd 4 ============\n");
        ioctl ( 4,             TCIFLUSH, 0 ); // invalid.
        
        // Not valid.
        debug_print("fd -1 ============\n");
        ioctl ( -1,  -1, 0 );
        
        debug_print("fd 33 ============\n");
        ioctl ( 33, -1, 0 ); // the limit is 31 for now.
        
        // the stdout is a vitual console.
        // Changing the color.
        // ok: it is working
        debug_print("fd 1 ============\n");
        //ioctl(1,1000,COLOR_YELLOW);
        //ioctl(1,1001,10); //change x
        //ioctl(1,1002,10); //change y
        //ioctl(1,1003,2);  //switch to the virtual console 2. 
        
        printf ("done\n");
        goto exit_cmp;
    }


    //++
    // ints
    // Profiler.
    // Mostra os contadores de interrupçao por tipo.
    if ( gramado_strncmp( prompt, "ints", 4 ) == 0 )
    {
        ints_builtins();
        goto exit_cmp;
    }
    //--


    // kernel-info
    if ( gramado_strncmp( prompt, "kernel-info", 11 ) == 0 )
    {
        shellShowKernelInfo ();
        goto exit_cmp;
    }


    // message-box
    if ( gramado_strncmp( prompt, "message-box", 11 ) == 0 )
    {
        gde_message_box ( 3, "MessageBox", "Testing message box." );
        goto exit_cmp;
    }


    // newdir - api
    // Create a new directory, given it's name.
    if ( gramado_strncmp( prompt, "newdir", 6 ) == 0 ){
        gde_create_empty_directory ( (char *) tokenList[1] );
        goto exit_cmp;
    }

    // newfile - api
    // Create a new file, given it's name.
    if ( gramado_strncmp( prompt, "newfile", 7 ) == 0 ){
        gde_create_empty_file ( (char *) tokenList[1] );
        goto exit_cmp;
    }

    // creat (libc)
    // Create a file using the libc.
    if ( gramado_strncmp( prompt, "creat", 5 ) == 0 )
    {
        creat ( (const char *) tokenList[1], 0666 );
        goto exit_cmp;
    }


    // mkdir (libc)
    // Create a directory using the libc.
    if ( gramado_strncmp( prompt, "mkdir", 5 ) == 0 )
    {
        mkdir ( (const char *) tokenList[1], 0666 );
        goto exit_cmp;
    }


    // mm-info
    if ( gramado_strncmp( prompt, "mm-info", 7 ) == 0 ){
        shellShowMemoryInfo ();
        goto exit_cmp;
    }


    // mm-size (MB)
    unsigned long __mm_size_mb = 0;    
    if ( gramado_strncmp( prompt, "mm-size", 7 ) == 0 )
    {
        __mm_size_mb = (unsigned long) gramado_system_call (292,0,0,0);
        printf ("Memory size = %d MB \n",__mm_size_mb);
        goto exit_cmp;
    }


    // mm-kernelheap
    if ( gramado_strncmp( prompt, "mm-kernelheap", 13 ) == 0 ){
        shellShowKernelHeapPointer ();
        goto exit_cmp;
    }


    // mm-processheap
    if ( gramado_strncmp( prompt, "mm-processheap", 14 ) == 0 ){
        shellShowProcessHeapPointer ();
        goto exit_cmp;
    }


    // msg-test
    // Enviando varias mensagens.
    // Send message to this process.
    int mi=0;
    if ( gramado_strncmp( prompt, "msg-test", 8 ) == 0 )
    {
        for (mi=0; mi<20;mi++){
            __SendMessageToProcess ( getpid() , 
               NULL, MSG_COMMAND, CMD_ABOUT, CMD_ABOUT );
        }
        goto exit_cmp;
    }


    // metrics
    // Mostra algumas informaçoes de metrica do sistema.
    if ( gramado_strncmp( prompt, "metrics", 7 ) == 0 )
    {
        shellShowMetrics();
        goto exit_cmp;
    }


    // mounted
    if ( gramado_strncmp( prompt, "mounted", 7 ) == 0 )
    {
        gramado_system_call (8500,0,0,0);
        goto exit_cmp;
    }


    // network
    // Initialize ring0 network support.
    // Reading the buffers sended by the kernel.
    // See: net.c
    if ( gramado_strncmp( prompt, "network", 7 ) == 0 )
    {
        network();
        goto exit_cmp;
    }

    // mbr
    // Check mbr sector.
    if ( gramado_strncmp( prompt, "mbr", 3 ) == 0 )
    {
        shellTestMBR ();
        printf ("done\n");
        goto exit_cmp;
    }


    // pci-info
    if ( gramado_strncmp( prompt, "pci-info", 8 ) == 0 )
    {
        shellShowPCIInfo ();
        goto exit_cmp;
    }


    // process-stats
    // Testando informa��es estat�sticas sobre os processos.
    // #bugbug: N�o mostra as informa��es dos processos clones.
    if ( gramado_strncmp( prompt, "process-stats", 13 ) == 0 )
    {
        process_stats();
        goto exit_cmp;
    }


    // current-process
    if ( gramado_strncmp ( prompt, "current-process", 15 ) == 0 )
    {
        printf("\n");
        system_call ( SYSTEMCALL_CURRENTPROCESSINFO, 0, 0, 0 );
        goto exit_cmp; 
    }


    // process-info
    if ( gramado_strncmp ( prompt, "process-info", 12 ) == 0 )
    {
        printf("\n");
        gramado_system_call ( 82, 0, 0, 0 );
        goto exit_cmp; 
    }


    // This sistem call is able to initialize a lot
    // of system's components.
    // IN: 1 = full initialization os ps2.
    if ( gramado_strncmp ( prompt, "ps2-init", 8 ) == 0 )
    {
        printf("\n");
        gramado_system_call ( 350, 1, 0, 0 );
        goto exit_cmp; 
    }

    // pwd - Print Working Directory.
    if ( gramado_strncmp( prompt, "pwd", 3 ) == 0 )
    {
        pwd_builtins ();
        goto exit_cmp;
    }

    // ram - Show RAM memory info.
    if (gramado_strncmp ( prompt, "ram", 3 ) == 0)
    {
        ram_test();
        goto exit_cmp;
    }
 

    // root - Show root file system info.
    if ( gramado_strncmp( prompt, "root", 4 ) == 0 )
    {
        gramado_system_call (4444, 0, 0, 0);
        goto exit_cmp;
    }


    // sethostname
    // Pega a segunda palavra digitada.
    if ( gramado_strncmp( prompt, "sethostname", 11 ) == 0 )
    {
        i++; //#bugbug: Indefined value.
        token = (char *) tokenList[i];
        sethostname( (const char*) tokenList[i], (size_t) 64-1 );
        goto exit_cmp;
    }


    // setusername
    // Pega a segunda palavra digitada.
    if ( gramado_strncmp( prompt, "setusername", 11 ) == 0 )
    {
        i++; //#bugbug: Indefined value.
        token = (char *) tokenList[i];
        setlogin( (const char*) tokenList[i] );

        //Testing setusername()
        //sprintf ( current_user_name, (const char*) tokenList[i] ); 
        //setusername ( current_user_name, (size_t) 64);

        //Testing setusername()
        //sprintf ( __username, (const char*) tokenList[i] ); 
        //setusername ( __username, (size_t) 64);

        goto exit_cmp;
    }
    

    // shell
    // Registrando esse shell como uma das portas
    // no domínio AF_GRAMADO.
    if ( gramado_strncmp( prompt, "shell", 5 ) == 0 )
    {
        printf ("~shell: Register shell on a gramado port.\n");
        
        // Registrando uma gramado port.
        // IN: shell port, pid
        gramado_system_call (7006, 8, getpid(), 0 );
        goto exit_cmp;
    }


    // setup
    // #test: Saving the config file.
    if ( gramado_strncmp( prompt, "setup", 5 ) == 0 )
    {
        sprintf (__setup_buffer,"This is the setup file");
        gdeshell_save_config_file();
        goto exit_cmp;
    }


	// socket
	// Testando socket() da libc.
	// >>> Isso est� criando o socket e se comunicando com o driver de rede.
	//nesse teste aproveitamos o soquete criado para se
	//comunicar com o driver de rede. que enviar� uma mensagem para
	//esse processo.

    // #todo
    // Criar um funçao para isso em net.c
    // ex: test_xxxx()

    if ( gramado_strncmp( prompt, "socket1", 7 ) == 0 )
    {
        net_socket_test1();
        goto exit_cmp;
    }


    // test-net
    // Testando a funçao socket() da libc
    // Pedimos para o servidor de rede enviar dados para o
    // processo atraves da stream configurada anteriormente.
    // if ( gramado_strncmp( prompt, "socket2", 7 ) == 0 )
    // {
    //     goto exit_cmp;
    // }
  

    // t500 - Setup a ring3 net buffer for the current process.
    // process->net_buffer = arg.
    // Testando o servico 550.
    // See: sci.c
    int __net_ret;
    if ( gramado_strncmp( prompt, "t550", 4 ) == 0 )
    {
         // service 550.
         __net_ret = (int) gde_setup_net_buffer ( 
                               getpid(),                // PID 
                               __net_buffer,            // buffer
                               sizeof(__net_buffer) );  // buffer size

         if (__net_ret == 0){
             printf ("Ok buffer configurado\n");
         }else{
             printf ("fail. buffer nao configurado\n");
         };
         goto exit_cmp;
    }

    // streams
    if ( gramado_strncmp( prompt, "streams", 7 ) == 0 )
    {
        printf ("Streams: \n");
        printf ("fd of stdin  = %d \n", fileno(stdin) );
        printf ("fd of stdout = %d \n", fileno(stdout) );
        printf ("fd of stderr = %d \n", fileno(stderr) );
        //...
        goto exit_cmp;
    }

    // sync - salva os buffers em ring0 no disco fisico.
    // Isso pode ser um programa.
    // See: unistd.c
    if ( gramado_strncmp( prompt, "sync", 4 ) == 0 )
    {
        printf ("sync: \n");
        sync();
        goto exit_cmp;
    }


    // system-info
    if ( gramado_strncmp( prompt, "system-info", 11 ) == 0 )
    {
        shellShowSystemInfo ();
        goto exit_cmp;
    }

    //
    // == Tests =============================================
    //
    
    // t1 ~ txx

    // t1 - 
    // Test file
    // Carrega um arquivo no buffer de words 
    // depois exibe todo o buffer mantendo o posicionamento 
    // no cursor. Isso força um scroll.
    if ( gramado_strncmp( prompt, "t1", 2 ) == 0 )
    {
        printf ("t1: Loading a file\n");
        shellTestLoadFile ();
        goto exit_cmp;
    }


    // t2 - Test fork()
    if ( gramado_strncmp( prompt, "t2", 2 ) == 0 || 
         gramado_strncmp( prompt, "test-fork", 9 ) == 0 )
    {
        printf ("t2: Testing fork\n");
        shellTestFork();
        goto exit_cmp;
    }


    // t3 - Test thread
    if ( gramado_strncmp( prompt, "t3", 2 ) == 0 ||
         gramado_strncmp( prompt, "test-thread", 11 ) == 0 )
    {
        printf ("t3: Testing thread\n");
        shellTestThreads();
        goto exit_cmp;
    }


    // t4 - Testing fopen function.
    // ok funcionou com fgetc e getc.
    FILE *f1;
    int ch_test;
    char t4buf[64];  //line
    int t4_line_offset=0;
    int t4nbytes=0;
    if ( gramado_strncmp( prompt, "t4", 2 ) == 0 )
    {
        
        //stdout
        printf ("t4: Open and reading a file\n");
        printf ("t4: Change the input mode.\n");
        //gramado_system_call(912,2000,2000,2000);  // INPUT_MODE_TTY
        rtl_set_input_mode(2000);
        
        //f1 = fopen ("gramado.txt","rb");
        f1 = stdin;
        if ( f1 == NULL ){
            printf ("fopen fail\n");  //stdout
            goto exit_cmp;
        }
        printf ("Testing getc ... \n\n");
        t4_line_offset=0;  
        while (1){
            //ch_test = (int) fgetc (f1);    //funcionou.
            //ch_test = (int) getc(f1);  //funcionou. 
            t4nbytes = read(0, &t4buf[t4_line_offset], 1);
            if ( t4nbytes > 0 )
            {
                ch_test = t4buf[t4_line_offset]; //ultimo que pegamos.
                if ( ch_test == 'q' ){ printf( "String={%s}\n",t4buf); break; }
                
                t4_line_offset++; 
                if(t4_line_offset>=64){ printf("overflow: {%s}\n",t4buf); break; }
                
                //if ( ch_test == 'q' ){
                //    printf("  EOF reached :)\n\n"); 
                //    goto exit_cmp;
                //}else{
                //     printf("[%c]", ch_test);  fflush(stdout);  
                //};
            }
        };
        t4_line_offset = 0;
        t4nbytes=0;
        printf ("t4: Change the input mode.\n");
        //gramado_system_call(912,1000,1000,1000);  // INPUT_MODE_SETUP
        rtl_set_input_mode(1000);
        goto exit_cmp;
    }


    int crI;
    char crName[11];
    if ( gramado_strncmp( prompt, "tcreat", 6 ) == 0 )
    {
        for (crI=0; crI<8; crI++)
        {
            itoa(crI,crName); 
            crName[crI+1] = 'x';
            creat (crName, 0);
        }
            
        goto exit_cmp;
    }
    
    // t5
    // Saving a file.
    // It's running on qemu.
    // It's not running on real machine.
    // if ( gramado_strncmp ( prompt, "t5", 2 ) == 0 )
    if ( gramado_strncmp ( prompt, "redpill", 7 ) == 0 )
    {
        printf ("redpill: Saving a file\n");
        shell_save_file ();  //local
        //gde_test_save_file("FILE1UM TXT");  // See: libcore.
        printf ("redpill: Done :)\n");
        goto exit_cmp;
    }


    // t6 - Save file using close().
    // The kernel has files tor standard stream.
    // and we are writing on stderr. KSTDERR.TXT i guess.
    // It is working. \o/
    char _buftest[] = "DIRTYDIRTYDIRTYDIRTYDIRTY";
    if ( gramado_strncmp ( prompt, "t6", 2 ) == 0 )
    {
        printf ("t6: Testing close()\n");
        write (0,_buftest,sizeof(_buftest));
        //close(0); //regular file
        //close(1); //virtual console
        //close(2); //regular file
        goto exit_cmp;
    }


    // t7 - Testando estado das teclas.
    if ( gramado_strncmp( prompt, "KEYS", 4 ) == 0 ||
         gramado_strncmp( prompt, "keys", 4 ) == 0 || 
         gramado_strncmp( prompt, "T7", 2 ) == 0 || 
         gramado_strncmp( prompt, "t7", 2 ) == 0 )
    {
        printf ("t7: Testing keyboard key state\n");
        
        printf ("VK_CAPITAL %d \n", 
            system_call ( 138, VK_CAPITAL, VK_CAPITAL, VK_CAPITAL ) );

        printf ("VK_LSHIFT %d \n", 
            system_call ( 138, VK_LSHIFT, VK_LSHIFT, VK_LSHIFT ) );

        printf ("VK_RSHIFT %d \n", 
            system_call ( 138, VK_RSHIFT, VK_RSHIFT, VK_RSHIFT ) );

        printf ("VK_CONTROL %d \n", 
            system_call ( 138, VK_CONTROL, VK_CONTROL, VK_CONTROL ) );

        printf ("VK_WINKEY %d \n", 
            system_call ( 138, VK_WINKEY, VK_WINKEY, VK_WINKEY ) );

        printf ("VK_LMENU %d \n", 
            system_call ( 138, VK_LMENU, VK_LMENU, VK_LMENU ) );
        //...
        goto exit_cmp;
    }


    // t8
    // Testando a criaçao de botao e a interaçao com ele 
    // atraves do mouse.
    if ( gramado_strncmp( prompt, "t8", 2 ) == 0 )
    {
        printf ("t8: Creating buttons \n");
        shellTestButtons ();
        gde_show_backbuffer ();
        goto exit_cmp;
    }

    // t9: Test pipe.
    // See: rtl.c
    if ( gramado_strncmp( prompt, "t9", 2 ) == 0 )
    {
        printf ("t9: Test pipe \n");
        rtl_test_pipe();
        goto exit_cmp;
    }

    int magic_value=0;
    if ( gramado_strncmp( prompt, "t10", 3 ) == 0 )
    {
        printf ("t10:  \n");
        //sc80 (0,0,0,0);
        //sc81 (0,0,0,0);
        sc82 (1,5678,0,0);               //set magic of fg_console
        magic_value = sc82 (2,0,0,0); //get magic of fg_console
        printf("MAGIC={%d}\n",magic_value);
        
        goto exit_cmp;
    }


    // t11 
    // Testando o envio de mensagens para o 
    // procedimento de janelas desse processo. Usando o kernel.
    // Chama message box com mensagem about.
    
    if ( gramado_strncmp( prompt, "t11", 3 ) == 0 )
    { 
        printf ("t11: Sending message to this process \n");
        gde_send_message ( 
             (struct window_d *) 0, 
             (int)               MSG_COMMAND, 
             (unsigned long)     CMD_ABOUT, 
             (unsigned long)     0 );
        goto exit_cmp;
    }


	// t16 - cancelado.


    // t17 - create process
    // #bugbug: It is not working.
    // It's a work in progress!
    // #todo:
    // No kernel, precisamos criar mais rotinas de suporte
    // a criacao de processos.
    // Temos poucas opçoes e tudo esta meio fora de ordem ainda.
    
    void *P;
    if ( gramado_strncmp( prompt, "t17", 3 ) == 0 )
    {
        printf ("t17: [FIXME] Creating process\n");
        
        // ?? critical session ??
        //#bugbug: O primeiro argumento está errado.
        P = (void *) gde_create_process ( "SYSMON  BIN", PRIORITY_HIGH ); 

        if ( (void *) P == NULL ){ printf ("t17: Fail creating process\n"); }
        
        printf ("t17: Done\n");
        goto exit_cmp;
    }



	// t18 - OpenTTY.
	// DEPRECATED !!!
	//FILE *opentty_fp;
	//FILE *terminal_opentty_fp;
	int x_ch;
	int terminal_PID;
	#define MSG_TERMINALCOMMAND 100 //provis�rio

    // DEPRECATED!!!
    // if ( gramado_strncmp ( prompt, "t18", 3 ) == 0 )
    // { goto exit_cmp; }



    // t19
    int xxx__PID;
    // deprecated.
    //if ( gramado_strncmp ( prompt, "t19", 3 ) == 0 )
    //{  goto exit_cmp; }


    // t20 - Isso executa o terminal e manda uma mensagem pra ele.
    int terminal___PID;
    FILE *_fp;
    // deprecated.
    //if ( gramado_strncmp ( prompt, "t20", 3 ) == 0 )
    //{  goto exit_cmp; }


    // t900 - Clona e executa o filho dado o nome do filho.
    // Isso funciona muito bem.
    if ( gramado_strncmp ( prompt, "t900", 4 ) == 0 )
    {
        printf ("t900: Testing the systemcall 900.\n");
        printf ("Clone and execute a new process. (sysmon.bin)\n");
        system_call ( 900, (unsigned long) "sysmon.bin", 0, 0 );
        goto exit_cmp;
    }


    // tty
    if ( gramado_strncmp ( prompt, "tty", 3 ) == 0 )
    {
        tty_test();
        goto exit_cmp;
    }

    // tty2
    if ( gramado_strncmp ( prompt, "tty2", 4 ) == 0 )
    {
        xxx_tty_test();
        goto exit_cmp;
    }


    // tty3
    if ( gramado_strncmp ( prompt, "tty3", 4 ) == 0 )
    {
        if ( isatty(fileno(stdin)) == 0 ){
            printf ("stdin is not a tty\n");
        }
        if ( isatty(fileno(stdout)) == 0 ){
            printf ("stdout is not a tty\n");
        }
        if ( isatty(fileno(stderr)) == 0 ){
            printf ("stderr is not a tty\n");
        }
        goto exit_cmp;
    }


	// tasklist - Lista informaçoes sobre os processos.
	// isso sera um programa tasklist.bin
    if ( gramado_strncmp( prompt, "tasklist", 8 ) == 0 )
    {
        shellTaskList();
        goto exit_cmp;
    }


    // test-path
    if ( gramado_strncmp( prompt, "test-path", 9 ) == 0 )
    {
        __load_path_test();
        goto exit_cmp;
    }


	// timer-test
	// Essa rotina cria um objeto timer que gera um interrupçao
	// de tempos em tempos e � tratado pelo procedimento de janelas.
    if ( gramado_strncmp( prompt, "timer-test", 10 ) == 0 )
    {
        __count = 0;  //tem que Inicializar;

        printf("timer-test: Creating timer\n");
        printf("%d Hz | sys time %d ms | ticks %d \n", 
            gde_get_systime_info(1), 
            gde_get_systime_info(2), 
            gde_get_systime_info(3) );

        gde_enter_critical_section ();
        cpu_window = (void *) gde_create_window ( 1, 
                                 1, 1, "shell-main",     
                                 400, 40, 32*8, 100,    
                     0, 0, COLOR_WHITE, COLOR_WHITE );
        gde_register_window (cpu_window);
        gde_show_window (cpu_window);
        gde_exit_critical_section ();

		//janela, 100 ms, tipo 2= intermitente.
		//system_call ( 222, (unsigned long) window, 100, 2);

        gde_create_timer ( 
            getpid(), 
            (unsigned long) 30, // interval. count down.
            (int) 2 );

		//inicializando.
        objectX = 0;
        objectY = 0;
        deltaX = deltaValue;
        deltaY = deltaValue;
          
        printf ("timer-test: done\n");
        goto exit_cmp;
    }



    // user info
    // Mas mostraremos as informa��es so usu�rio atual.
    // IN: service, user id.
    if ( gramado_strncmp( prompt, "user-info", 9 ) == 0 )
    {
        gramado_system_call (156, 0,0,0);
        goto exit_cmp;
    }


    // volume-info
    if ( gramado_strncmp( prompt, "volume-info", 11 ) == 0 )
    {
        shellShowVolumeInfo();
        goto exit_cmp;
    }


	// window
	// Testing kgws.
    if ( gramado_strncmp( prompt, "window", 6 ) == 0 )
    {
        shellShowWindowInfo();
        goto exit_cmp;
    }

    // wscreen - test screen window (root window)
    // #obs: 
    // Se minimizada, por isso n�o pode ser pintada ou repintada.
    struct window_d *__screen_window;
    if ( gramado_strncmp( prompt, "wscreen", 7 ) == 0 )
    {
        __screen_window = (struct window_d *) gde_get_screen_window();
        gde_redraw_window (__screen_window,1);
        goto exit_cmp;
    }


    // write on virtual console.
    char __wbuf[128]; //line ? 
    int __w_size = 0;
    if ( gramado_strncmp( prompt, "write", 5 ) == 0 )
    {
		//isso retorna o tamanho da string ??.
		//sprintf (__wbuf,"Testing tty_write ...\n");

		
		//IN: device, buf, count
        //write ( 0, __wbuf, sizeof(__wbuf) );
        //write_VC ( 0, __wbuf, __w_size = sprintf (__wbuf,"Testing tty_write ...\n") );
        goto exit_cmp;
    }


    // wait-test
    // Vamos esperar por qualquer um dos filhos.
    int ___wait_status;
    if ( gramado_strncmp( prompt, "wait-test", 9 ) == 0 )
    {
        //wait (&___wait_status);
        waitpid (-1,&___wait_status,0);
        goto exit_cmp;
    }


    // Wait for a reason.
    if ( gramado_strncmp ( prompt, "wait-reason", 11 ) == 0)
    {
        printf ("gdeshell: child ...\n");
        system_call ( 900, (unsigned long) "false.bin", 0, 0 );
    
        printf ("gdeshell: still alive 1 ...\n");
        
        // Wait for a reason. (current thread.)
        gramado_system_call ( 970, 
            WAIT_REASON_TEST, 
            WAIT_REASON_TEST, 
            WAIT_REASON_TEST );

        printf ("gdeshell: still alive 2 ...\n");
        goto exit_cmp;
    }


//
// == End of the commands ===========================================
//


    // Se apertamos o [ENTER] e não encontramos um comando válido.
    // Então damos um aviso de comando inválido e 
    // reiniciamos o prompt na próxima linha.

    //fail.
    int Execve_Ret = 1;

    // #todo: 
    // Colocar isso no início dessa função.
    unsigned long buffer[5];
    int z=0;


//doexec_first_command:

    //
    // ## TEST ##
    //

	// #importante:
	// Se estamos aqui � porque o comando n�o corresponde a nenhuma das 
	// palavras reservadas acima, ent�o executaremos, presumindo ser um nome 
	// de aplicativo no formato 'test.bin'. 
	
	// #importante:
	// Vamos checar se o pathname � absoluto ou relativo.
	// +Se tiver barra, significa que o pathname � absoluto e 
	// come�a no diret�rio raiz do volume do sistema.
	// root:/volume1/
	// +Se come�ar por root:/ tamb�m � absoluto.
	// +Pathname relativo � somente aquele que � apenas um nome 
	// de arquivo dentro do diret�rio atual. Como: 'name' ou name1/name2,
	// sem barra ou ponto.

    // #bugbug
    // It is wrong!

    /*
    absolute = absolute_pathname ( (char *) tokenList[0] );

    switch (absolute)
    {
		//N�o � absoluto ou falhar
        case 0:
		    //printf("doexec_first_command: not absolute pathname\n");
		    break;
			
		//� absoluto	
        case 1:
		    printf("doexec_first_command: absolute pathname\n");
			
			break;
			
		//falha	
        case 2:
		default:
		    printf("doexec_first_command: pathname fail\n");
			break;
    }; 
    */


    // Trata no caso de ser absoluto.
    // + Eliminar ./ pois se trata de arquivo no diret�rio atual.
    /*
    if (absolute == 1)
    {
        // #bugbug: 
        // Essa definição não deve ficar aqui.
        char *t = (char *) tokenList[0];

        if ( *t == '.' )
        {
            t++;
            if ( *t == '/' ){
                t++;
                tokenList[0] = (char *) t;
            }
        }
    }
    */



	//
	// ## Executando um programa no formato ">test.bin"
	//
	
	//char *tmp[] = { tokenList[1], tokenList[2], tokenList[3], NULL };
	//char *tmp2[] = { tokenList[1], tokenList[2], tokenList[3], NULL };
	
    //Presumindo ser um nome de aplicativo no formato 'test.bin'.
    //o token 0 � o nome do programa e o os pr�ximos s�o argumenteos ..
	//dessa forma podemos enviar um comando e dois argumentos ...
	//?? Talvez devessemos enviar um ponteiro para um array de strings 
	// no �ltimo argumento. (argv) ou ainda um env
						 

    //Execve_Ret = (int) shell_gramado_core_init_execve( 
	//                       (const char*) tokenList[0], //nome
	//                       (const char*) tokenList[1], 
	//             (const char*) tokenList[2] ); //env ...deve ser null
	
	//#bugbug: e sem argumento.
	/*
	char *p = ( char * ) &prompt[0];
	
	while( *p && *p != ' ' && *p != '\0' )
	{
		p++;
	}
	
	while( *p && *p == ' ' && *p != '\0' )
	{
		p++;
	}
	*/



    // Copiando todos os ponteiros para um array.
    for ( z=0; z<____token_count; z++ ){
        buffer[z] = (unsigned long) tokenList[z];
    };



    //
    // == Clone ===============================================
    //

    // Clonning the process!
    // Clone e executa o processo filho.
    // O shell não sai ... o filho fica em background.
    // (&) podemos usar o 'e' comercial no fim da linha de comandos.  

    int fake_pid=-1;
    
    //fake_pid = (int) system_call ( 900, 
    //                     (unsigned long) tokenList[0], 0, 0 ); 

    fake_pid = (int) gde_clone_and_execute( (char *) tokenList[0] );
    
    if (fake_pid < 0){
        debug_print ("gdeshell: gde_clone_and_execute fail!\n");
        goto fail;
    }


    //
    // == Wait support =============================================   
    //

    int Wait_status=0;
    
//___wait:

    // Se devemos rodar o comando em background.
    // Isso significa que não precisamos esperar.

    // Continuamos pegando comandos. 
    if ( __background == 1 )
    {
        printf ("The child will run in background.\n");
        goto exit_cmp;

    // Se o filho não vai rodar em bg, então devemos esperar.
    }else{

        debug_print ("The child will run in foreground.\n");

        //exit(0);
                
        //gramado_system_call (265,0,0,0); //yield thread.
        //gramado_system_call (265,0,0,0); //yield thread.
        //gramado_system_call (265,0,0,0); //yield thread.
        //gramado_system_call (265,0,0,0); //yield thread.
        sc82 (265,0,0,0);
        
        fake_sleep (8000);
        fake_sleep (8000);
        waitpid (-1,&Wait_status,0);
        debug_print("gdeshell: waitpid() ends\n");
        fake_sleep (8000);
        fake_sleep (8000);
        
        goto exit_cmp;
    };


    //
    // Crazy!
    //
    
    debug_print ("gdeshell: Crazy fail\n");
    goto fail;

    
// ======
dosh:
    debug_print ("gdeshell: [FAIL] dosh\n");
    goto fail;
dotry:
    debug_print ("gdeshell: [FAIL] dotry\n");
    goto fail;
dobin:
    debug_print ("gdeshell: [FAIL] dobin\n");
    goto fail;    
    


   // ==================
   //       fail 
   // ==================

fail:
    printf(" Unknown command!\n");
    ret_value=1;
    goto done;
    


//
// == exit_cmp =======================================================
//

exit_cmp:

    ret_value = 0;

done:

    // Clean the token list.
    // Show the prompt.

    for ( i=0; i<TOKENLIST_MAX_DEFAULT; i++ ){ tokenList[i] = NULL; };

    shellPrompt();

    return (unsigned long) ret_value;
}




/*
 ********************************* 
 * shellInitSystemMetrics: 
 * 
 */
 
	// step1
	//inicializa as metricas do sistema.
void shellInitSystemMetrics (void){

	//pegaremos todas as metricas de uma vez s�,
	//se uma falhar, ent�o pegaremos tudo novamente.

    // Window server info.
    sm_ws_type            = gde_get_system_metrics(200);
    sm_ws_pid             = gde_get_system_metrics(201);
    sm_ws_virtual_console = gde_get_system_metrics(202);
    sm_ws_initialized     = gde_get_system_metrics(203);


    // Tamanho da tela.
    smScreenWidth  = gde_get_system_metrics(1);
    smScreenHeight = gde_get_system_metrics(2);
    
    // cursor. 
    smCursorWidth  = gde_get_system_metrics(3);
    smCursorHeight = gde_get_system_metrics(4);
    
    smMousePointerWidth  = gde_get_system_metrics(5);
    smMousePointerHeight = gde_get_system_metrics(6);
    
    smCharWidth  = gde_get_system_metrics(7);
    smCharHeight = gde_get_system_metrics(8);
    // ...

    //#debug  ok t� certo.
    //printf("w={%d} h={%d}\n", smScreenWidth, smScreenHeight); 
    //while (1){ asm ("pause"); }	

    sm_initialized = 1;
} 



	// step2
    //inicializa os limites da janela.
void shellInitWindowLimits(void){
	
    //
    // ## Window limits ##
    //

    if ( sm_initialized != 1 )
    {
		printf ("shellInitWindowLimits:");
		while(1){}
	} 


    //full screen support
    wlFullScreenLeft = 0;
    wlFullScreenTop = 0;
    wlFullScreenWidth = smScreenWidth;
    wlFullScreenHeight = smScreenHeight;
	
    //limite de tamanho da janela.
    wlMinWindowWidth = smCharWidth * 80;
    wlMinWindowHeight = smCharWidth * 25;
    wlMaxWindowWidth = smScreenWidth;
    wlMaxWindowHeight = smScreenHeight;	
	
    //quantidade de linhas e colunas na �rea de cliente.
    wlMinColumns = 80;
    wlMinRows = 1;
    
    //#bugbug: temos que dividir pelo tamanho do char.
    //mas se for zero d� problema.
    wlMaxColumns = (smScreenWidth / smCharWidth);
    wlMaxRows = (smScreenHeight / smCharHeight);
	
	//dado em quantidade de linhas.
    textMinWheelDelta = 1;  //m�nimo que se pode rolar o texto
    textMaxWheelDelta = 4;  //m�ximo que se pode rolar o texto	
	textWheelDelta = textMinWheelDelta;
	//...
	
	wl_initialized = 1;
}


	// step3
	//inicia o tamanho da janela.
void shellInitWindowSizes (void){
	
    if ( wl_initialized != 1 )
    {
		printf ("shellInitWindowSizes:");
		while(1){}
	} 	
	
	wsWindowWidth = smScreenWidth;
	wsWindowHeight = smScreenHeight;	
	
	ws_initialized = 1;
}


	// step4
	//inicializar a posi��o da janela.
void shellInitWindowPosition (void){
	
	//window position
	wpWindowLeft = WINDOW_LEFT;
	wpWindowTop = WINDOW_TOP;
	
	//wpWindowLeft = (unsigned long) ( (smScreenWidth - wsWindowWidth)/2 );
	//wpWindowTop = (unsigned long) ( (smScreenHeight - wsWindowHeight)/2 );
	
	wp_initialized = 1;
}



/*
 ******************************************
 * shellShell:
 *     Constructor.
 *     N�o emite mensagens.
 */
 
// #aten��o
// Isso deve ser chamado antes de criarmos a janela principal. 
 
void shellShell (void){

    int i=0;
    int j=0;


	// Internas.

    shellStatus = 0;
    shellError = 0;



	//
	// ## Inicializando as estruturas de linha ##
	//
	
	//inicializamos com espa�os.
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
	// Para ficar mais r�pido.
	
	// #importante:
	// O aplicativo tem que confiar nas informa��es 
	// retornadas pelo sistema.
		
	// Usar o get system metrics para pegar o 
	// tamanho da tela.
	
	// step1
	//inicializa as metricas do sistema.
	shellInitSystemMetrics ();
	
	// step2
    //inicializa os limites da janela.
	shellInitWindowLimits ();
	
	// step3
	//inicia o tamanho da janela.
	shellInitWindowSizes ();
	
	// step4
	//inicializar a posi��o da janela.
	shellInitWindowPosition ();
 
 
    //
	// initi visible area.
	// #todo: criar fun��o para isso
	
	textTopRow = 0;
	textBottomRow = 24;
	
	//limits.
	//quantidade de linhas de colunas da janela.
	//na verdade deve ser da �rea de cliente.
	
    wlMaxColumns = (wsWindowWidth/smCharWidth);    
    wlMaxRows = (wsWindowHeight/smCharHeight);         
 
    if ( wlMaxColumns < wlMinColumns )
	{
	    wlMaxColumns = wlMinColumns;
	}
		
	if ( wlMaxRows < wlMinRows )
	{
		wlMaxRows = wlMinRows;
	}
	
	//...	

	//
	// Setup buffers.
	//
	

	// #inportante:
	// #bugbug: N�o podemos deixar o stdout como screenbuffer 
	// pois no screen buffer os caracteres tem atributos ...
	// e no stdout podemos ter um arquivo normal ...
	//ou sa�da normal que servir� de entrada para  
	//outro processo.
    // reiniciando as vari�veis na estrutura do output
	
	//obs: Ao cancelarmos isso o std volta a ser 
	//o antigo e j� configurado stdout.
	//stdout->_base = &screen_buffer[0];
	//stdout->_ptr = stdout->_base;
	//stdout->_cnt = PROMPT_MAX_DEFAULT;
	//stdout->_file = 1;
	//stdout->_tmpfname = "shell_stdout";
	
	//...	
	
	// Obs:
	// prompt[] - Aqui ficam as digita��es. 

	shellClearBuffer();

	
	//shellBufferMaxColumns = DEFAULT_BUFFER_MAX_COLUMNS;
	//shellBufferMaxRows    = DEFAULT_BUFFER_MAX_ROWS;
	
	//buffersize = (shellBufferMaxColumns * shellBufferMaxRows);
	

	
	//
	// @todo: E o fluxo padr�o. Quem configurou os arquivos ???
	//        o kernel configuroru???
	//
	
	// N�mero m�ximo de colunas e linhas.
	g_columns = wlMaxColumns;  // 80;
	g_rows = wlMaxRows;        // 25;
    //...
	

    for ( i=0; i<WORKINGDIRECTORY_STRING_MAX; i++ )
    {
        current_workingdiretory_string[i] = (char) '\0';
    };

    //sprintf ( current_workingdiretory_string, 
        //SHELL_UNKNOWNWORKINGDIRECTORY_STRING );    

	//...
	
//done:

    ShellFlag = SHELLFLAG_COMMANDLINE;
	
    //#bugbug
	//Nossa refer�ncia � a moldura e n�o a �rea de cliente.
	//@todo:usar a �rea de cliente como refer�ncia
	//shellSetCursor(0,0);
    //shellSetCursor(0,4);
    
	//@todo
	//tentando posicionar o cursor dentro da janela
	//shellSetCursor( (shell_info.main_window->left/8) , (shell_info.main_window->top/8));
	
	//shellPrompt();
}


/*
 ****************************
 * shellInit:
 *     Inicializa o Shell.  
 *
 * @todo: Inicializar globais e estruturas.
 */
 
int shellInit ( struct window_d *window ){

	//#bugbug 
	//o ponteiro do argumento pode ser inv�lido, pois 
	//� uma vari�vel local.

    char buffer[512];
    int PID=0;
    int PPID=0;
    int ActiveWindowId = 0;
    int WindowWithFocusId = 0;
    void *P;


	//??
	//stream status
	shell_info.stream_status = 0;
	


	//
	// ## buffer support ##
	//
	
	
    /* 
	Line buffer output for stderr. 
    If your machine doesn't have either of setlinebuf or setvbuf,
    you can just comment out the buffering commands, and the shell
    will still work.  It will take more cycles, though. 
	*/
	
/*++ HAVE_SETLINEBUF */	
/*
#if defined (HAVE_SETLINEBUF)
    setlinebuf(stderr);
    setlinebuf(stdout);
#else
# if defined (_IOLBF)
    setvbuf( stderr, (char *) NULL, _IOLBF, BUFSIZ );
    setvbuf( stdout, (char *) NULL, _IOLBF, BUFSIZ );
# endif
#endif
*/ 
/*-- HAVE_SETLINEBUF */
	
	
	// Antes dessa fun��o ser chamada, o foco foi setado 
	// na janela do aplicativo.
	// Test: N�o mechemos no cursor nesse momento, deicharemos 
	// a fun��o SetFocus configurar o curso.
	// N�o mostraremos o prompt, somente depois dos testes de inicializa��o.
	
    //bugbug	
	//cursor
	//shellSetCursor(0,4);
	
	//pointer
	//shellPrompt();
    
	// message.
    //printf("shellInit: Running tests ...\n");	


	//
	// Window support.
	//

	// Testando a validade do ponteiro da janela.
	// Recebido via argumento.
	// #importante: 
	// A estrutura est� em kernel mode e n�o podemos acessa-la.

    if ( (void *) window == NULL ){
        printf ("shellInit: window fail.\n"); 

    } else {
        gde_set_focus(window);

		// Welcome messages.

#ifdef SHELL_VERBOSE
        printf ("Starting gdeshell ...\n");
#endif

    };
    
    
    // #tests
    // Getting the IDs for active window and window woth focus.


	//
	// Active window.
	//


	//Active window
	ActiveWindowId = (int) gde_get_active_window();

	//valor de erro
    if ( ActiveWindowId == (-1) ){
        printf ("shellInit: ERROR getting Active window ID\n");	
    }

#ifdef SHELL_VERBOSE
    printf ("ActiveWindowId={%d}\n", ActiveWindowId );
#endif

    //
    // Window with focus
    //

	// Obtendo informa��es sobre a janela com o foco de entrada.

	// Focus.
    WindowWithFocusId = (int) gde_get_focus ();

	//valor de erro
    if ( WindowWithFocusId == (-1) ){
        printf ("shellInit: ERROR getting Window With Focus ID\n");
    }

#ifdef SHELL_VERBOSE
    printf ("WindowWithFocusId={%d}\n", WindowWithFocusId );
#endif


	//
	// Obtendo informa��es sobre linhas e colunas do shell.
	//

#ifdef SHELL_VERBOSE
	//columns and rows
    printf ("wlMaxColumns={%d} \n", wlMaxColumns );
    printf ("wlMaxRows={%d} \n", wlMaxRows );
#endif


	//
	// Process support.
	//
	
	// @todo: 
	// Essa mensagem est� aparecendo fora da �rea de trabalho do shell
	// pois ainda n�o temos um ponteiro para a mem�ria que representa essa �rea.
	// Talvez as mensagens devessem ir para um buffer de linha antes de irem 
	// para a mem�ria de v�deo.
	// #Impotante:
	// Devemos utilizar as configura��es de terminal virtual, respeitar a estrutura 
	// de terminal, que indicar� qual � a janela de terminal onde os caracteres 
	// devem ser escritos. Na verdade � um ponteiro para um ret�ngulo e n�o para 
	// uma janela. Obs: Esse ret�ngulo do terminal deve esr configur�vel e uma rotina 
	// deve dar suporte a essa configura��o.
	

	// @todo: 
	// O que tevemos fazer aqui � pegar informa��es sobre o processo Shell
	// e coloca-las na tela.
	

	// #todo: 
	// Criar na API uma rotina de inteface que use essa chamada.
	// ex: APIGetPID().


	//PID = (int) APIGetPID();

    //PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0 );
    PID = (int) getpid();
    if ( PID == (-1) ){
        printf ("ERROR getting PID\n");
    }

    //PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0 );
    PPID = (int) getppid();
    if ( PPID == (-1) ){
        printf ("ERROR getting PPID\n");
    }


	//
	// == PWD ==========================
	//

    // #test
    // Prompt string support
    shellInitializeWorkingDiretoryString();


// Done.

done:

    // #bugbug
    // Inicializar o nome do host.
    // #bugbug: 
    // Suspensa. Problemas nessa rotina dentro do kernel,

    // getusername ( current_user_name, (size_t) 64);
    // gethostname ( current_host_name, (size_t) 64);

    
    if ( interactive == 1 )
    {
        // Welcome message!
        
        //shellSetCursor ( 0, 0 );
        
        // Top of the screen ?
        printf("\f");
        printf("GRAMADO OS 1.0");
        printf("\n");
        
        printf("______________");
        printf("\n");
        
        printf("\n");
        fflush(stdout);

        // First prompt.
        shellPrompt();
    }

    //printf ("gdeshell-shellInit: breakpoint    \n");
    //while(1){}

    return 0;
}


int shellCheckPassword (void)
{

    FILE *user_stream;
    char buffer[512];
    int i=0;

	// Se o shell nao for interativo nao tem login.

	if (interactive == 1)
	{
		//hostname
        //current_host_name = "??host??";		
		
		
		//file 
		
		user_stream = (FILE *) fopen ("user.txt","w+");
		
		//#todo check.
		
		// Testing welcome message.
	    //printf("\n");
	    printf("\n Welcome to Norax Kernel! \n");
	    //printf("\n");
	
        		
		//
		//  ## username  ##
		//
		
	    printf("\n username: ");
	    gets(username);
		//current_user_name = username;
		
		//
		//  ## password ##
	    //
		
		printf("\n password: ");
	    gets(password);
		
		printf("\n");
	
#ifdef SHELL_VERBOSE	
        //@todo colocar o ponteiro na vari�vel no in�cio do arquivo.	
	    printf("username={%s} password={%s} \n", username, password );
		//printf("\n");
#endif
		
		char *c = (char *) &user_stream->_base[0];		
		
		//procura user name.
		while ( *c && *c != 'U' )
		{
			c++;
		};
		
		if ( c[0] == 'U' &&
             c[1] == 'S' &&
             c[2] == 'E' &&
             c[3] == 'R' &&
             c[4] == 'N' &&
             c[5] == 'A' &&
             c[6] == 'M' && 			
		     c[7] == 'E' )
		{
		    //USERNAME={fred}
            c = c+10; 
			
		    
			//Move apenas 'fred'
		    for ( i=0; i<4; i++ ){
			    buffer[i] = c[i];
		    }			
			
			//printf("\n");
			//printf("%c", c[0]);
			//printf("%c", c[1]);
			//printf("%c", c[2]);
			//printf("%c", c[3]);
			//printf("\n");
			
			//printf("\n");
			//printf("%c", buffer[0]);
			//printf("%c", buffer[1]);
			//printf("%c", buffer[2]);
			//printf("%c", buffer[3]);
			//printf("\n");
			
#ifdef SHELL_VERBOSE			
			printf(">>%s\n", username);
			printf(">>%s\n", buffer);
#endif
			
            if( gramado_strncmp( username, buffer, 4 ) == 0 )
            {
#ifdef SHELL_VERBOSE				
				printf("# USERNAME OK #\n");
#endif				
				login_status = 1;
			}else{
				printf("# USERNAME FAIL #\n");
				login_status = 0;
			};				

        }else{
			
			printf("# USERNAME FAIL #\n");
			login_status = 0;
		};


		while ( *c && *c != 'P' ){			
			c++;
		};
		
		if ( c[0] == 'P' &&
             c[1] == 'A' &&
             c[2] == 'S' &&
             c[3] == 'S' &&
             c[4] == 'W' &&
             c[5] == 'O' &&
             c[6] == 'R' && 			
		     c[7] == 'D' )
		{
		    //PASSWORD={1234}
            c = c+10; 
			
		    //Move apenas '1234'
		    for ( i=0; i<4; i++ ){
			    buffer[i] = c[i];
		    };

#ifdef SHELL_VERBOSE				
			printf(">>%s\n", password);
			printf(">>%s\n", buffer);
#endif			
			
            if ( gramado_strncmp( password, buffer, 4 ) == 0 )
            {
#ifdef SHELL_VERBOSE								
				printf("# PASSWORD OK #\n");
#endif
				login_status = 1;
			}else{
				printf("# PASSWORD FAIL #\n");
				login_status = 0;
			};					
			
		}else{
			
		    printf("# PASSWORD FAIL #\n");
            login_status = 0; 			
		};
		    
	}else{
		
		printf("shell not interactive\n");
		login_status = 0;
	};
	
#ifdef SHELL_VERBOSE
		printf("Login done!\n");
#endif


    return (int) login_status;
}


/*
 * shellSetCursor:
 *     Configurando o cursor. (stdio.h).
 *
 * @todo: Aqui quando definimos os valores o cursor no shell 
 * devemos considerar que a janela com o foco de entrada tambem tem um cursor...
 * Temos que atualizar o cursor da janela com foco de entrada se quizermos 
 * escrever corretamente dentro dela.
 * e isso se faz atrav�s de uma chamada ao kernel.
 */


// printf escrevera no console virtual
// atraves do arquivo '1'.
// Isso implica que esara o cursor do console virtual.

void 
shellSetCursor ( 
    unsigned long x, 
    unsigned long y )
{

    // Setando o cursor usado pelo kernel base.
    gde_set_cursor (x,y);


    // Atualizando as variaveis globais 
    // usadas somente aqui no shell.

    g_cursor_x = (unsigned long) x;
    g_cursor_y = (unsigned long) y;

    // buffer.
    // Coisas do screen buffer.

    move_to(x,y);
}



/*
 *******************************************
 * shellThread:
 *     Um thread dentro para testes.
 */

void shellThread (void){


	printf("\n");
	printf("$\n");
	printf("$$\n");
	//printf("$$$\n");
    printf("#### This is a thread ####\n");
	//printf("$$$\n");
	printf("$$\n");
	printf("$\n");
    printf("\n");
	
    gde_show_backbuffer ();
	
	while(1){}
    while(1)
	{	
	    //printf("$");
		asm ( "pause" );
		asm ( "pause" );
		asm ( "pause" );
		asm ( "pause" );
    }	
}


//help message
void shellHelp (void)
{
    printf (help_banner);	
}


//drawing a tree
void shellTree (void){

    printf (tree_banner);
}


/*
 **************************************************
 * shellPrompt:
 *     Inicializa o prompt.
 *     Na inicializa��o de stdio, 
 *    prompt foi definido como stdin->_base.
 */

void shellPrompt (void){

    int i=0;

    // Clean prompt buffer.
    
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){ prompt[i] = (char) '\0'; };
    
    prompt[0] = (char) '\0';
    prompt_pos = 0;
    prompt_status = 0;
    prompt_max = PROMPT_MAX_DEFAULT;  

    // Prompt.
    printf("\n");
    putc('$',stdout);
    putc(' ',stdout);
    fflush(stdout);
}


/*
 * shellClearBuffer:
 *     Limpa o buffer da tela.
 */

void shellClearBuffer (void)
{
    int i=0;
    int j=0;

	//inicializamos com espa�os.
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



/*
 * shellShowScreenBuffer:
 *     Quando for efeturar o refresh da tela
 * � o conte�do desse buffer que deve ser pintado 
 * no ret�ngulo que � a �rea de cliente do shell.  
 */
//mostra o buffer screen buffer, onde ficam 
//armazenados os caracteres e atributos datela
//do terminal virtual.

//#importante: vamos mostrar todo o buffer de words, a partir 
//da posi��o atual do cursor, for�ando um scroll

//Isso � s� um teste.

void shellShowScreenBuffer (void)
{
    shellRefreshVisibleArea ();
}


/*
 * shellTestLoadFile:
 *     Carrega um arquivo de texto no buffer e mostra na tela.
 */

void shellTestLoadFile (void){

    FILE *f;

	int i=0;
	int Ret=0;
	int ch_test=0;
	int pos=0;


	//#importante:
	//precisa ser arquivo pequeno.
	
	
	f = fopen ("gramado.txt","rb");  	
	
	//pequeno
	//f = fopen ("init.txt","rb");  
	
	//grande
	//f = fopen ("init.txt","rb");  	
	
    if( f == NULL ){
        printf("shellTestLoadFile: f fail\n");
        return;

    }else{
		//printf("fopen ok\n");
    };

	
	//#test 
	//testando com um arquivo com texto pequeno.
	//enviando para o buffer de words, 
	//obs: agora tem rotinas de refresh.


    while (1){
        ch_test = (int) getc(f); 

        if ( ch_test == EOF ){
			//printf("\n");
			//printf("EOF reached :)\n");
			goto done;

        }else{ 
            shellInsertNextChar ( (char) ch_test );
        };
    };

    // fail
    
fail:
    // Nothing.
done:
    return;
}


void shellTestFork(void)
{
    int pid = -1;


    debug_print("shellTestFork:\n");
    
    printf ("father pid = %d\n",getpid());

    pid = fork();

    printf ("return pid = %d\n",pid);
    while(1){}
}


/*
 *************************************************************
 * shellTestThreads:
 *     Cria um thread e executa.
 *     #bugbug ...j� funcionou uma vez, mas agora est� com problemas.
 *     @todo: na hora de criar a thread precisamos passar o PID desse processo.
 */

    // #obs: 
    // As threads criadas aqui sao atribuidas ao processo PID=0.
    // #todo: 
    // No kernel, quando criar uma thread ela deve ser atribuida
    // ao processo que chamou a rotina de criacao.


// 'shellThread' is the function that is gonna run.

// Status:
// It is working.
// We can create and run a thread in this test.

void shellTestThreads (void)
{

    void *T;
    
    void *Thread;
    unsigned long *StackAddress;


    printf ("shellTestThreads: \n");



    //===================================================
    //++
    gde_enter_critical_section();

    // Stack
    StackAddress = (unsigned long *) malloc (2*1024);
    
    if ( (void *) StackAddress == NULL ){
        printf ("shellTestThreads: [FAIL] StackAddress\n");
        goto fail;
    }


    printf ("shellTestThreads: Creating the thread.\n");

    Thread  = (void *) gde_create_thread ( (unsigned long) &shellThread, 
                                (unsigned long) (&StackAddress[0] + (2*1024) - 4), 
                                "ThreadTest1" );

    if ( (void *) Thread == NULL ){
        printf ("shellTestThreads: [FAIL] Thread\n");
        goto fail;
    }

	// #importante:
	// La no kernel, isso deve selecionar a thread para execussao, 
	// colocando no estado standby.
	// Logo em seguida a rotina de taskswitch efetua o spawn.
    
    printf ("shellTestThreads: Starting the thread.\n");
    
    gde_start_thread (Thread);
    
    gde_exit_critical_section();
    //--
    //===================================================

    printf ("gdeshell: done \n");
    
    // Permitir que o shell continue.
    return;

fail:
    gde_exit_critical_section();

    printf ("gdeshell: Fail\n");
    // Permitir que o shell continue.
    return;
}


/*
 *************************************
 * shellClearScreen:
 *     Limpar a tela do shell.
 *     usada pelo comando 'cls'.
 */

// called by cls_builtins().

void shellClearScreen (void){


    struct window_d  *w;
    unsigned long left, top, right, bottom;


    //desabilita o cursor
    system_call ( 245, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0 );


    shellClearBuffer();


    w = (void *) shell_info.terminal_window;

    if ( (void *) w != NULL )
    {
        gde_redraw_window ( w, 1 );
    }


    // #bugbug
    // This routine is not working ...
    // so we're gonna try the printf escape sequence.
    
    left = (terminal_rect.left/smCharWidth);
    top  = (terminal_rect.top/smCharHeight);
    shellSetCursor ( left, top );
    
    printf("\f");
    fflush(stdout);
    
    
	// Copiamos o conte�do do screenbuffer para 
	// a �rea de cliente do shell.
	// obs: A outra op��o seria repintarmos a janela.

    //shellRefreshScreen ();	
	
	//shellRefreshVisibleArea();
	
	//reabilita o cursor
    system_call ( 244, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
}


/*
 *******************************************
 * shellRefreshScreen:
 * 
 *     #importante 
 *      
       #OBS
       NA VERDADE SE REFERE AO REFRESH DA �REA DE CLIENTE DO SHELL.
 *
 *     Copia o conte�do do (screen_buffer) buffer de output 
 * para a tela. (dentro da janela). 
 * ## Acho que se trata de stdout.
 * � uma mem�ria VGA virtual com caractere e atributo.
 * na hora de efetuar refresh precisamos considerar o atributo 
 * para sabermos a cor do caractere e de seu background.
 */

void shellRefreshScreen (void){

	int i=0;
	int j=0;

	//desabilita o cursor
	system_call ( 245, 
	    (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	
	for ( i=textTopRow; i<textBottomRow; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    //LINES[i].CHARS[j] = (char) 'x';
		    //LINES[i].ATTRIBUTES[j] = (char) 7;
	        
			printf ("%c", LINES[i].CHARS[j] );
		}
		printf ("\n");
	};

	//reabilita o cursor
	system_call ( 244, 
	    (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
}


// a inten��o aqui � fazer o refresh de apenas uma linha do arquivo.
//#todo podemos fazer o mesmo para um char apenas.

void shellRefreshLine ( int line_number ){

	int col = 0;  


	if ( line_number > wlMaxRows )
		return;	
	
	int lin = (int) line_number; 

	
#ifdef SHELL_VERBOSE		
	//#debug
	printf("shellRefreshScreen:\n");
#endif 

	//cursor apontando par ao in�cio da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//in�cio da �rea de cliente.
	//left ser� a coluna.
	
	shellSetCursor ( col, lin );
		
	//colunas.
	for ( col=0; col < wlMaxColumns; col++ )
	{
	    //Mostra um char do screen buffer.
		printf( "%c", LINES[lin].CHARS[col] );
	};	
}


// a inten��o aqui � fazer o refresh de apenas uma linha do arquivo.
//#todo podemos fazer o mesmo para um char apenas.
// #importante
// Rever essa rotina, pois vamos usar
// a nova vers�o da libc que envia os caracteres para o arquivo
// ficando por conta do terminal imprimi-los em sua �rea de cliente.
// #bugbug: Aqui, por enquanto, esse printf envia ele mesmo
// os chars para a tela.

void 
shellRefreshChar ( 
    int line_number, 
    int col_number )
{

    if ( col_number > wlMaxColumns || 
         line_number > wlMaxRows )
    { 
        return; 
    }

    shellSetCursor(col_number,line_number);

	//Mostra um char do screen buffer.
    printf ("%c", LINES[line_number].CHARS[col_number] );
}




//refresh do char que est� na posi��o usada pelo input.
// #importante
// Rever essa rotina, pois vamos usar
// a nova vers�o da libc que envia os caracteres para o arquivo
// ficando por conta do terminal imprimi-los em sua �rea de cliente.
// #bugbug: Aqui, por enquanto, esse printf envia ele mesmo
// os chars para a tela.

void shellRefreshCurrentChar (void)
{
    printf ("%c", LINES[textCurrentRow].CHARS[textCurrentCol] );
}



/*
 ********************************************
 * shellScroll:
 *     @todo: Efetuar um scroll somente dentro 
 * da VGA virtual.
 * #importante: isso n�o deveria estar aqui,
 * deve ser uma rotina de automa��o, presente 
 * em alguma biblioteca, servidor ou kernel.
 */

void shellScroll (void){
	
	//reajustando a �rea vis�vel do buffer 
 

	//desliga o cursor
	//system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	

    testChangeVisibleArea();	//desloca a �rea vis�vel usando delta.
	shellRefreshVisibleArea();
	
	//#todo:posicionar cursor
	
	//reabilita o cursor
	//system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
}


static void save_cur (void)
{
	textSavedCol = textCurrentCol;
	textSavedRow = textCurrentRow;
}


static void restore_cur (void)
{
	textCurrentCol = textSavedCol;
	textCurrentRow = textSavedRow;
}


//line feed
static void lf (void){
	
	//enquanto for menor que o limite de linhas, avan�a.
	if ( textCurrentRow+1 < wlMaxRows )
	{
		textCurrentRow++; 
		return;
	}
	
	//#todo: Scroll up;
	//scrup();
}


// ??
//voltando uma linha.
static void ri (void)
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


//carriege return
static void cr (void)
{
    textCurrentCol = 0;
}


static void del (void)
{
    LINES[textCurrentRow].CHARS[textCurrentCol] = (char) '\0';
    LINES[textCurrentRow].ATTRIBUTES[textCurrentCol] = 7;
}


// Insere um caractere sentro do buffer.
void 
shellInsertCharXY ( 
    unsigned long x, 
    unsigned long y, 
    char c )
{

    if ( x >= wlMaxColumns || y >= wlMaxRows )
    {
        return;
    }

	LINES[y].CHARS[x] = (char) c;
	LINES[y].ATTRIBUTES[x] = 7;
}


// Insere um caractere sentro do buffer.
char 
shellGetCharXY ( 
    unsigned long x, 
    unsigned long y )
{

    if ( x >= wlMaxColumns || y >= wlMaxRows ){ return; }

    return (char) LINES[y].CHARS[x];
}


/*
//inserindo uma string em uma posi��o do buffer de sa�da.
void shellInsertStringPos( unsigned long offset, char *string );
void shellInsertStringPos( unsigned long offset, char *string )
{
    //@todo
};
*/


/*
 preenche todo o buffer de sa�da com char ou atributo
void shellFillOutputBuffer( char element, int element_type )
{
	
}
*/


//usado para teste de scroll.
//imprime varias vezes o char indicado.

void testScrollChar ( int c ){

    int i=0;

    for ( i=0; i < (wlMaxColumns*26); i++ )
    {
	    //se chegamos no limite do screen_buffer
		//...
		shellInsertNextChar ((char) c);
    };
}


/*
 ***************************************************
 * shellInsertNextChar:
 *     Coloca um char na pr�xima posi��o do buffer.
 *     Mem�ria de v�deo virtual, semelhante a vga.
 */

void shellInsertNextChar (char c){


	// Coloca o char no buffer.
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;


	// refresh
    //shellRefreshCurrentChar ();
    
    
    // #bugbug
    // A rotina de libc s� vai imprimir quando enche o buffer.
    printf ("%c", LINES[textCurrentRow].CHARS[textCurrentCol] );
    fflush (stdout);

	// update
	textCurrentCol++;


	if (textCurrentCol >= 80 )
	{
		textCurrentCol = 0;
		
		textCurrentRow++;
		
		if ( textCurrentRow >= 25 )
		{
			shellScroll ();
			while(1){}
		}
	}

    // atualiza posicionamento da string dentro da linha.
	LINES[textCurrentRow].pos = textCurrentCol;
	LINES[textCurrentRow].right = textCurrentCol;
}


void shellInsertCR (void){
    
	shellInsertNextChar ( (char) '\r' );		
}


void shellInsertLF (void){
	
	shellInsertNextChar ( (char) '\n' );
}


void shellInsertNullTerminator (void){
	
	shellInsertNextChar ( (char) '\0' );	
}


/*
 ***************************************************
 * shellTestMBR:
 *     Testar a leitura de um setor do disco.
 *     Testaremos o setor do mbr.
 */

void shellTestMBR (void){
	
    unsigned char buffer[512];

    printf ("gdeshell.bin: shellTestMBR()\n");
    printf ("Reading the sector to a ring3 buffer\n\n");

    //++
    gde_enter_critical_section (); 
    //read sector
    // IN: service number, buffer, lba, nothing.
    system_call ( 
        SYSTEMCALL_READ_LBA, 
        (unsigned long) &buffer[0],  
        (unsigned long) 0, 
        (unsigned long) 0);
    gde_exit_critical_section ();   
    //--

    //
    // Print.
    //

    // jump
    printf("JMP: [ %x %x ] \n" , buffer[0], buffer[1] );

    // os name
    char OS_Name[8+1];  //MSDOSxx
    OS_Name[0] = buffer[2];
    OS_Name[1] = buffer[3];
    OS_Name[2] = buffer[4];
    OS_Name[3] = buffer[5];
    OS_Name[4] = buffer[6];
    OS_Name[5] = buffer[7];
    OS_Name[6] = buffer[8];
    OS_Name[7] = buffer[9];
    OS_Name[9] = 0;  // finaliza
    printf("OS Name: %s\n",OS_Name);
 

    // volume label   //GRAMADO      11 bytes
    char VolumeLabel[11+1];
    VolumeLabel[0] = buffer[42];
    VolumeLabel[1] = buffer[43];
    VolumeLabel[2] = buffer[44];
    VolumeLabel[3] = buffer[45];
    VolumeLabel[4] = buffer[46];
    VolumeLabel[5] = buffer[47];
    VolumeLabel[6] = buffer[48];
    VolumeLabel[7] = buffer[49];
    VolumeLabel[8] = buffer[50];
    VolumeLabel[9] = buffer[51];
    VolumeLabel[10] = buffer[52];
    
    VolumeLabel[11] = 0;  // finaliza
    printf("Volume Label: %s\n",VolumeLabel);


    // fs type string.  'FAT16   '.
    // #bugbug: what is the right offset??
    char fsTypeString[8+1];
    fsTypeString[0] = buffer[53];
    fsTypeString[1] = buffer[54];
    fsTypeString[2] = buffer[55];
    fsTypeString[3] = buffer[56];
    fsTypeString[4] = buffer[57];
    fsTypeString[5] = buffer[58];
    fsTypeString[6] = buffer[59];
    fsTypeString[7] = buffer[60];
    fsTypeString[9] = 0;  // finaliza
    printf("fs type string: %s\n",fsTypeString);

 
    // signature
    printf("Signature: [ %x %x ] \n" , buffer[0x1FE], buffer[0x1FF] );
    
    printf("shellTestMBR: done\n");
}


/*
 * move_to:
 *    Move o cursor de posi��o.
 *    Assim o pr�ximo char ser� em outro lugar da janela.
 */

void move_to ( unsigned long x, unsigned long y )
{	
	if ( x > wlMaxColumns || y > wlMaxRows )
		return;
	
	//screen_buffer_x = x;
	//screen_buffer_y = y;
	
	textCurrentCol = x;
	textCurrentRow = y;
	
	//screen_buffer_pos = ( screen_buffer_y * wlMaxColumns + screen_buffer_x ) ;
}


//show shell info
void shellShowInfo (void){
	
	int PID, PPID;
	
    printf (" # shellShowInfo: #\n");
	
	/*
    PID = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
	if ( PID == (-1))
	{
	    printf("ERROR getting PID\n");	
	}
  
    PPID = (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0);
	if ( PPID == (-1))
	{
	    printf("ERROR getting PPID\n");	
	}
	*/
  
	PID = getpid();
	PPID = getppid();
		
	printf ("Process info: PID={%d} PPID={%d} \n", PID, PPID );
	
	printf ("wlMaxColumns={%d} \n", wlMaxColumns );
	printf ("wlMaxRows={%d} \n", wlMaxRows );	
	//...
}


// metrics
void shellShowMetrics (void){

    //reinicializa as metricas do sistema.
    //isso pega os valores e coloca nas vari�veis globais.

    shellInitSystemMetrics();

    printf ("\n");  
    printf (" # shellShowMetrics: # \n");

    printf ("window server type: %d\n"            ,sm_ws_type);
    printf ("window server pid: %d \n"            ,sm_ws_pid);
    printf ("window server virtual console: %d \n",sm_ws_virtual_console);
    printf ("window server initialized: %d \n"    ,sm_ws_initialized);



	printf ("screenWidth={%d} screenHeight={%d}\n", 
	    smScreenWidth, smScreenHeight );
	
	printf ("cursorWidth={%d} cursorHeight={%d}\n", 
	    smCursorWidth, smCursorHeight );
	
	printf ("mousepointerWidth={%d} mousepointerHeight={%d}\n", 
	    smMousePointerWidth, smMousePointerHeight );
	
	printf ("charWidth={%d} charHeight={%d}\n", 
	    smCharWidth, smCharHeight );	
	
	//...
	
    printf ("Done\n");	
}


//show system info
void shellShowSystemInfo (void){
	
	int ActiveWindowId=0;
	int WindowWithFocusId=0;
	

	printf ("shellShowSystemInfo:\n");




	//Active
	ActiveWindowId = (int) gde_get_active_window ();

	//valor de erro
	if ( ActiveWindowId == (-1))
	{
	    printf("ERROR getting Active window ID\n");	
	}	
	printf ("ActiveWindowId={%d}\n", ActiveWindowId );


	// Focus.
	WindowWithFocusId = (int) gde_get_focus ();
	
	//valor de erro
	if ( WindowWithFocusId == (-1))
	{
	    printf("ERROR getting Window With Focus ID\n");	
	}	
	printf ("WindowWithFocusId={%d}\n", WindowWithFocusId );	
}


//mostrar informa��es sobre janelas.
void shellShowWindowInfo (void){
	
    int wID=0;	
	
	// #bugbug.
	// Testando a estrutura de janela.
	// A janela foi criada pelo kernel e copiamos o ponteiro 
	// da estrutura para um ponteiro em user mode.
	// Podemos ter erros de mem�ria com essas opera��es.
		
	printf ("\n");	
	printf (" # shellShowWindowInfo #\n");
	
	printf ("mainWindow={%x}\n", shell_info.main_window );
		
	//#bugbug 
	//temos um problema aqui.
	// provavelmente o erro � por acessar um endere�o que est� 
	// em kernel mode.
	//if( shell_info.main_window->left > 0 && shell_info.main_window->top > 0  )
	//{
	//    shellSetCursor( (shell_info.main_window->left/8), (shell_info.main_window->top/8) );
	//}
		
		
	//obs: Isso � uma estrutura interna, n�o reflete 
    //a informa��o usada pelo kernel.	
	
	printf ("\n");		
	printf ("Window info: \n");	
    printf ("l={%d} t={%d} w={%d} h={%d}\n", 
	    wpWindowLeft, wpWindowTop, wsWindowWidth, wsWindowHeight );


	//Obs: isso funcionou. setando o cursor.
	//if( terminal_rect.left > 0 && terminal_rect.top > 0 )
	//{	
    //    shellSetCursor( (terminal_rect.left/8), (terminal_rect.top/8) );  
	//};
		
	// #importante:
	// Getting terminal window.
		
	wID = (int) system_call ( SYSTEMCALL_GETTERMINALWINDOW, 0, 0, 0 ); 
	
	// Check?
	
	printf ("current terminal: ");
	printf ("Windows ID for current terminal = {%d} \n", wID);
	
	//...
}



//??
//void shellSetScreenColors( ... ){}

//??
//void *shellGetTerminalWindow(){}

//void shellSetTerminalRectangle(....){}

//void *shellOpenTerminal(.){}



  
unsigned long 
shellSendMessage ( struct window_d *window, 
                   int msg, 
                   unsigned long long1, 
                   unsigned long long2 )
{
	return (unsigned long) shellProcedure ( window, msg, long1, long2 );
}


//copia bytes	
void shell_memcpy_bytes( unsigned char *Dest, 
                         unsigned char *Source,
                         unsigned long Length )
{
    while (Length--)
        *Dest++ = *Source++;
}


/*
 * shell_write_to_screen:
 *     refresh de um ret�ngulo ??    
 */
/* 
void shell_write_to_screen( struct shell_screen_d *screen, 
                            struct shell_rect_d *region )
{
    //@todo	
}
*/

 
//todo: 
//Criar rotina de sa�da do shell.

void shellExit (int code)
{
	//#todo ...
    exit (code);
}
 

/*
 *****************************************
 * shellUpdateWorkingDiretoryString:
 * 
 *     Atualiza a string do diret�rio de trabalho.
 * Essa � a string que ser� mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 */

// Used by the 'cd' command.

void shellUpdateWorkingDiretoryString ( char *string )
{
    
    // Is it initialized in the gdeshell?
    if ( pwd_initialized == 0 )
    {
        gde_debug_print ("shellUpdateWorkingDiretoryString: [FAIL] pwd_initialized\n");
        return;

    // YES, it is.
    }else{

        if ( (void *) string == NULL )
        {
            gde_debug_print ("shellUpdateWorkingDiretoryString: [FAIL] invalid string\n");
            return;

        // OK, let's go!
        }else{

            //++
            // Atualizando dentro do gdeshell.
            // concatenate string and separator.
            strcat ( current_workingdiretory_string, string );
            strcat ( current_workingdiretory_string, 
                SHELL_PATHNAME_SEPARATOR );

            //++
            // Atualizar no gerenciamento feito pelo kernel.
            system_call ( 175, 
                (unsigned long) string,
                (unsigned long) string, 
                (unsigned long) string );
        };
    };
}


/*
 *****************************************
 * shellInitializeWorkingDiretoryString:
 *     Atualiza a string do diret�rio de trabalho.
 * Essa � a string que ser� mostrada antes do prompt.
 * 'pwd'> 
 * ?? isso deve sser todo o pathname do pwd ?? 
 * ex: root:/volume0>
 */

void shellInitializeWorkingDiretoryString (void){


    gde_debug_print ("shellInitializeWorkingDiretoryString: \n");
 
	//get info
	
	//test: get current volume id.
	current_volume_id = (int) system_call ( 171, 0, 0, 0 );
	
	//global usada para string do nome do volume.
	current_volume_string = (char *) SHELL_VOLUME1_STRING;
	
	
    //  ## volume list ##
	
	//root:
    //primeiro colocamos a string que indica 
	//a lista de volumes.
    sprintf ( current_workingdiretory_string, SHELL_VOLUMELIST_STRING ); 
	
	
	// ## separador ##

	//root:/
	strcat ( current_workingdiretory_string, SHELL_PATHNAME_SEPARATOR );
	
	
	//  ## volume root dir ##
	
	//root:/volumex
	strcat ( current_workingdiretory_string, current_volume_string );

	
	// ## separador ##

	//root:/volumex/
	strcat ( current_workingdiretory_string, SHELL_PATHNAME_SEPARATOR );

	// #ps:
	// In this moment cwd string is initialized.
	// Let's setup environment variables for that.

	// #todo: Isso � um teste ainda.
	// #todo: Implementar isso na libc.
	//int setenv(const char *name, const char *value, int overwrite);
	//setenv ("PWD", (const char *) current_workingdiretory_string, 1);
	
    // Flag.
    pwd_initialized = 1;
}



// Atualiza a vari�vel global para id de diret�rio atual de trabalho.

void shellUpdateCurrentDirectoryID ( int id )
{
    g_current_workingdirectory_id = (id);
}


//lista informa��es sobre os processos.
// op��es:
// +podemos pedir para o kernel listar as informa��es.
// +podemos solicitar as informa��es uma a uma.
// Obs: A segunda op��o � a mais trabalhosa, mas 
// da oportunidade para testarmos as chamadas ao kernel e 
// explorarmos as possibilidades que cada informa��o traz 
// individualmente.

// #todo
// Devemos considerar aqui o que � trabalho do shell e o que �
// trabalho do terminal virtual.

void shellTaskList (void){
		
	// testando posicionamento de strings
	
	unsigned long X, Y;
	int PID=0;

	//Pega o PID do processo atual.
    PID = (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0 );
	
    //X = apiGetCursorX();
	Y = gde_get_cursor_y();
	
	Y++;
	X=0;
	shellSetCursor(X,Y);
    printf("PID ");
	X=8;
	shellSetCursor(X,Y);
	printf("XXXXXXXX");
	
	Y++;
	X=0;
	shellSetCursor(X,Y);
    printf("====");
	X=8;
	shellSetCursor(X,Y);
	printf("========");

	Y++;
	X=0;
	shellSetCursor(X,Y);
    printf("%d",PID);
	X=8;
	shellSetCursor(X,Y);
	printf("...\n");
	
    //...
}


void shellShowPID (void)
{
    printf (" ~ Current PID %d\n", (int) getpid () );
}

void shellShowPPID (void)
{
    printf (" ~ Current PPID %d\n", (int) getppid () );
}

void shellShowUID (void)
{
    printf (" ~ Current UID %d\n", (int) getuid () );
}

void shellShowGID (void)
{
    printf (" ~ Current GID %d\n", (int) getgid () );
}


void shellShowUserSessionID (void)
{
    printf ("Current user session %d\n", 
        (int) system_call( SYSTEMCALL_GETCURRENTUSERSESSION, 0, 0, 0) );
}


void shellShowWindowStationID (void)
{
    printf ("Current room %d\n", 
        (int) system_call( SYSTEMCALL_GETCURRENTWINDOWSTATION, 0, 0, 0) );
}


void shellShowDesktopID (void)
{
    printf ("Current desktop %d\n", 
        (int) system_call( SYSTEMCALL_GETCURRENTDESKTOP, 0, 0, 0) );
}


void shellShowProcessHeapPointer (void){

    unsigned long heap_pointer=0;
    
	//int id = (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0); 
    int id = (int) getpid(); 

    heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, 
                                       id, 0, 0 );

    printf ("Current Process heap pointer address %x\n", 
        (unsigned long) heap_pointer );
}


void shellShowKernelHeapPointer (void){

    unsigned long heap_pointer=0;

	//??
	//Id do processo kernel.
    int id = 0;   

    heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, 
                                       id, 0, 0 );

    printf ("Current Process heap pointer address %x\n", 
        (unsigned long) heap_pointer );
}


//mostra informa��es sobre o disco atual.
void shellShowDiskInfo (void)
{
	//@todo: atualizar api.h
    system_call ( 251, 0, 0, 0 );
}


//mostra informa��es sobre o volume atual.
void shellShowVolumeInfo (void)
{
	
	//@todo: atualizar api.h
	system_call ( 252, 0, 0, 0 );
}


//mostrar informa��es gerais sobre a mem�ria.
void shellShowMemoryInfo (void)
{
    system_call ( SYSTEMCALL_MEMORYINFO, 0, 0, 0 );
}


//mostrar informa��es gerais sobre a mem�ria.
void shellShowPCIInfo (void)
{
    system_call ( SYSTEMCALL_SHOWPCIINFO, 0, 0, 0 );
}


//mostrar informa��es gerais sobre a mem�ria.
void shellShowKernelInfo (void)
{
    system_call ( SYSTEMCALL_SHOWKERNELINFO, 0, 0, 0 );
}



/*
 **********************************************
 * shell_fntos:
 *     Rotina interna de support.
 *     Isso deve ir para bibliotecas depois.
 *     N�o tem prot�tipo ainda.
 *
 * Credits: Luiz Felipe
 */

void shell_fntos (char *name){

    int  i, ns = 0;
    char ext[4];
    //const char ext[4];


    //transforma em mai�scula
   while ( *name && *name != '.' )
    {
        if(*name >= 'a' && *name <= 'z')
            *name -= 0x20;

        name++;
        ns++;
    };


    // aqui name[0] � o ponto.
    // ent�o constroi a extens�o.
    for ( i=0; i < 3 && name[i+1]; i++ )
    {
        if(name[i+1] >= 'a' && name[i+1] <= 'z')
            name[i+1] -= 0x20;

        ext[i] = name[i+1];
    };


    while (ns < 8)
    {
        *name++ = ' ';
        ns++;
    };


    for ( i=0; i < 3; i++ )
        *name++ = ext[i];


    *name = '\0';
}


/*
 *******************************************************
 * shell_gramado_core_init_execve:
 *
 *     Essa � uma rotina alternativa que roda um processo 
 * usando os recursos do processo init.
 */

// #bugbug
// N�o usar mais esse m�todo no garden. usar apenas no gramado core.

int 
shell_gramado_core_init_execve ( 
    const char *arg1,     // nome
    const char *arg2,     // arg (endere�o da linha de comando)
    const char *arg3 )    // env
{

	//erro.
    int Status = 1;

	//unsigned long arg_address = (unsigned long) &argv[0];

	// suprimindo dot-slash
	// The dot is the current directory and the 
	// slash is a path delimiter.
	//if( filename[0] == '.' && filename[1] == '/' )
	//{ 
	//    filename++;
	//    filename++; 
	//    goto translate;	
	//};


	//suprimindo a barra.
	//if( *arg1 == '/' || 
	//    *arg1 == '\\' )
	//{ 
	//    arg1++; 
	//};


translate:

	//
	// ## BUG BUG
	//
	// Talvez nesse momento, ao transformar a string ele 
	// corrompa o espa�o reservado para o argumento seguinte.
	// vamos fazer um teste no quan a rotina n�o precise 
	// acrescentar zeros.
	//
	
	//
	// correto � isso mesmo,
	// para n�o corromper o espa�o dos argumentos no vetor,
	// teremos que transformar somente l� no kernel, pouco antes 
	// de carregarmos o arquivo.
	//
	
	//Isso faz uma convers�o de 'test.bin' em 'TEST    BIN'.
	//Ok funcionou.
	//shell_fntos( (char *) arg1);
	
	//const char* isso n�o foi testado.
	//shell_fntos(filename);


	// #importante:
	// Isso deve chamar gramado_core_init_execve() na api.
								
	
	// #obs:
	// isso chamar� uma rotina especial de execve, somente  
	// usada no ambiente gramado core. 
	// Essa � uma rotina alternativa que roda um processo usando os recursos 
	// do processo init.
	
execve:

	// Obs: 
	// Se retornar o n�mero do processo ent�o podemos esperar por ele 
	// chamando wait (ret);


    Status = (int) system_call ( 167, 
                       (unsigned long) arg1,    // Nome
                       (unsigned long) arg2,    // arg (endere�o da linha de comando)
                       (unsigned long) arg3 );  // env

    if ( Status == 0 )
    {
		//N�o houve erro. O aplicativo ir� executar.

		// Nesse momento devemos usar um novo procedimento de janela.
		// Que vai enviar as mensagens de caractere para um terminal 
		// espec�fico, para que aplicativos que user aquele terminal 
		// possam pegar essas mensgens de caractere.


#ifdef SHELL_VERBOSE
        printf ("gdeshell: aplicativo inicializado.\n");
#endif

		//
		// ## teste ##
		//
		// saindo do shell.
		//
		
		// getpid...
		// waitforpid(?);
		
		//die("Exiting shell.bin\n");
		
		//Saindo sem erro.
		//exit(0);
		
		//Sa�da elegante, retornando para o crt0.
		ShellFlag = SHELLFLAG_EXIT;
		
		//ShellFlag = SHELLFLAG_FEEDTERMINAL;
		goto done;
	}else{
		
		// Se estamos aqui � porque ouve erro 
		// ainda n�o sabemos o tipo de erro. 
		// Status indica o tipo de erro.
		// Se falhou significa que o aplicativo n�o vai executar,
		// ent�o n�o mais o que fazer.
		
		//#importante: Error message.
		printf("shell: aplicativo nao foi inicializado.\n");
		
		ShellFlag = SHELLFLAG_COMMANDLINE;
		goto fail;
	};


	//fail.
	
	// Retornaremos. 
	// Quem chamou essa rotina que tome a decis�o 
	// se entra em wait ou n�o.


fail:

    //#importante: Error message.
    //status = 1.
	
    printf ("shell_gramado_core_init_execve: \n fail retornando ao interpretador\n");
	
done:

    return (int) Status;
}


/*
 * feedterminalDialog:
 *     Para alimentar um terminal com caracteres.
 */
 
int 
feedterminalDialog ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
	//int q;

	switch (msg)
	{
	
	    //para alimentar o terminal
		case MSG_KEYDOWN:
			//para todas as teclas.
			//feed terminal system call.
			system_call( 135,  // n�mero do servi�o 
			             0,    // n�mero do terminal
						 long1,    // o caractere
						 long1 );  // o caractere

			break;
			
		//para sair do di�logo.	
		case MSG_SYSKEYDOWN:
		    switch(long1)
			{

                //
                // ?? #importante:
				// ?? Quando parar de alimentar o terminal ??
                // ## [CONTROL + C]  ou [ESC]  ## 
				// >>> F12 POR ENQUANTO PARA TESTES.
				//
				//help
				case VK_F1:
				    //APISetFocus(i1Window);
					//APIredraw_window(i1Window);
					gde_message_box ( 3, 
					    "feedterminalDialog",
					    "F1: HELP");
					break;
				
                //full screen
                //colocar em full screen somente a �rea de cliente. 
		        case VK_F2:
				    //APISetFocus(i2Window);
					//APIredraw_window(i2Window);
				    gde_message_box ( 3, 
				        "feedterminalDialog", 
				        "F2: ");
					//ShellFlag = SHELLFLAG_COMMANDLINE;
					break;
					
				case VK_F3:
				    printf("F3: Saindo do aplicativo e voltando ao shell...\n");
				    ShellFlag = SHELLFLAG_COMMANDLINE;
				    break;
					
					
			};
		    break;
			
		default:  
		    break;
	
    };


    return 0;
}




/*
 **************
 * die:
 */
 
void die (char *str){

    printf ("die: %s",str);
    fprintf ( stderr, "%s\n", str );
    exit (1);
}


/*
// Isso foi para stdlib.c
// #todo: Conferir e deletar essa aqui.
void *xmalloc( int size){
	
    register int value = (int) malloc(size);
    if(value == 0)
        die ("xmalloc fail.\n");
//done:  
    return (void *) value;
}
*/



/*
 ***********************************
 * concat:
 *     Concatena strings.
 *     #todo: Isso pode ir para a libc.
 */

char *concat ( char *s1, char *s2, char *s3 ){
	
    int len1 = (int) strlen (s1);
    int len2 = (int) strlen (s2);
    int len3 = (int) strlen (s3);
  
    char *result = (char *) xmalloc ( len1 +len2 +len3 +1 );

    strcpy ( result, s1);
    strcpy ( result +len1, s2 );
    strcpy ( result +len1 +len2, s3 );
  
    *( result +len1 +len2 +len3 ) = 0;

    return (void *) result;
}


/* error */

void error ( char *msg, char *arg1, char *arg2 ){
	
    fprintf ( stderr, "shell: ");
    fprintf ( stderr, "%s %s %s", msg, arg1, arg2 );
    fprintf ( stderr, "\n");
}


/* fatal error */

void 
fatal ( 
    char *msg, 
    char *arg1, 
    char *arg2 )
{
    error ( msg, arg1, arg2 );
    //delete_temp_files ();
    exit (1);
}


char *save_string ( char *s, int len )
{
   register char *result = (char *) xmalloc (len + 1);

    bcopy (s, result, len);
    
    result[len] = 0;
  
    return result;
}
 

/*
 *****************************************************
 * shellExecuteThisScript:
 *     Aqui temos que carregar o arquivo de script indicado 
 * nos argumentos.
 * #importante:
 * Apenas colocaremos o arquivo em stdin, que � o pormpt[]
 * e retornaremos ao incio da fun��o que compara, para 
 * comparar agora o que estava escrito no arquivo de script.
 * 
 * 	#todo:
 *	Essa fun��o deve chamar o interpretador de script
 *
 * IN: Nome do arquivo.
 */
 
int shellExecuteThisScript ( char *script_name ){

	//#todo:
	//Essa fun��o deve chamar o interpretador de script	
	
    FILE *script_file;
    int i;
	
	// Aqui temos que carregar o arquivo de script indicado 
	// nos argumentos.
	
    printf ("shellExecuteThisScript:\n");
    printf ("Initializing script ...\n");
    printf ("CurrentFile={%s}\n",script_name);

	
	// #ok 
    // Carregaremos o arquivo com o nome passado por argumento.	
	
    script_file = fopen (script_name,"rw");

    if ( (void *) script_file == NULL )
    {
        printf ("shellExecuteThisScript: Can't open script file!\n");
        die ("*");
    }


	//#Ok
	//atualizando a linha de comandos no prompt[], stdin.
	
	//#obs 
	//Talvez n�o precise copiar o conte�do, e sim apenas 
    //mudar os ponteiros.
    
    //#todo 	
	//Fazer isso ao inv�s de copiar.
	//stdin = script_file;

	// #bugbug
	// N�o podemos acessar elementos da estrutura de arquivo.


    for ( i=0; i< 128; i++ )
    {
        stdin->_base[i] = script_file->_base[i];
    };


	//
	// ## parser ##
	//
	
	//#todo
	//Chamaremos o parser, que num loop chamar� o lexer yylex()
	
	//parser();
	

	//EOF_Reached = EOF;

    return 0;
}


/*
char **array_of_strings (){

	char **a;
	
	a[0] = "test0";
	a[1] = "test1";
	a[2] = NULL;
	
	return (a);
}
*/


/*
//retorna o pool de strings contendo os nomes dos arquivos
//em um diret�rio que est� no buffer.
char **get_dir_files ( char *buffer ){

    char **poll;	
	
	// ...
	
    return (poll);
}
*/



/*
//coloca no pool de strings passado por argumento 
//as strings que correspondem  aos nomes 
// dos arquivos encontrados no diret�rio 
//indicado pelo buffer.
int set_dir_files ( char **poll, char *buffer ){
	
	//...

    return (0);
}
*/


/*
 **************************************
 * absolute_pathname:
 * Retorna 1 nos seguintes casos:
 *
 * >/
 * >.
 * >./
 * >..
 * >../
 *
 * Credits: bash 1.05
 */
	
	// #importante:
	// Vamos checar se o pathname � absoluto ou relativo.
	// +Se tiver barra, significa que o pathname � absoluto e 
	// come�a no diret�rio raiz do volume do sistema. root:/volume1/
	// +Se come�ar por root:/ tamb�m � absoluto.
	// +Pathname relativo � somente aquele que � apenas um nome 
	// de arquivo dentro do diret�rio atual. Como: 'name' ou name1/name2,
	// sem barra ou ponto.
	// $/ � o diret�rio raiz do volume do sistema.
	// $v/ � o diret�rio raiz do vfs.

// #bugbug
// #todo
// rever isso.
// absoluto � o que come�a no diret�rio raiz '/' ou 'root:/'

int absolute_pathname ( char *string ){

	// Checar nulidade.
    if( !string || !strlen(string) )
        return (0);

	//Come�a por barra.
	//Ent�o essa barra significa o diret�rio raiz do 
	//volume do sistema. Ex: root:/volume1/
    if( *string == '/' )
        return (1);


	// .
	// � absoluto, pois estamos determinando o diret�rio.
	// Se for ponto, avan�a em seguida.
    if ( *string++ == '.' )
    {
        // ./
		// Significa que se trata do diret�rio atual
        if ( (!*string) || *string == '/' )
            return (1);

		// ..
		// ../
		// Significa que se trata do diret�rio pai.
		// Se for ponto, avan�a em seguida.
		// se for barra ou nada � absoluto.
		//obs: o nada nesse caso significa que foi digitado apenas '..'
        if ( *string++ == '.' )
            if( !*string || *string == '/' )  
                return (1);

		// ?? Continua ...
		// Se estamos aqui, significa que � um ponto que n�o � seguido 
		// de outro ponto ou barra.
		//?? dever�amos falhar com a op��o 2. 
        return (2);
    }


	// root:/
    if ( *string == 'r' )
    {
        if ( string[0] == 'r' &&
             string[1] == 'o' &&
             string[2] == 'o' &&
             string[3] == 't' &&
             string[4] == ':' &&
             string[5] == '/' )
        {
            return (1);
        }

        return (2);
    }


	// #teste:
	// invendando esquema.
	// Volume do sistema.
	// O n�mero do volume do sistema � um padr�o.
    if ( *string == '$' )
    {

        // root:/volume1/ = $/ (volume do sistema)
        if ( string[0] == '$' &&  string[1] == '/' )
        {
            return (1); 
        }

		// root:/volume1/ = $v/ (vfs)
        if ( string[0] == '$' &&
             string[1] == 'v' && 
             string[2] == '/' )
        {
            return (1);
        }

        return (2);
    }


//fail:
//N�o � absoluto.

    return 0;
}


//inicializaremos o supporte a pathname
int shellInitPathname (void){

    int i=0;

    if (pathname_initilized == 1)
    {
        return 0;
    }


    for ( i=0; i<PATHNAME_LENGHT; i++ )
    {
		pathname_buffer[i] = (char) '\0';
    };


    pathname_lenght = 0;

	//...

    pathname_initilized = 1;

    return 0;
}

 
//inicializaremos o supporte a filename
int shellInitFilename (void){

    int i=0;

    if (filename_initilized == 1)
    {
        return 0;
    }


	for ( i=0; i<FILENAME_LENGHT; i++ )
	{
		filename_buffer[i] = (char) '\0';
	};


    filename_lenght = 0;

	//...


    filename_initilized = 1;

    return 0;
}


/* 
 Remove the last N directories from PATH.  
 Do not leave a blank path.
 PATH must contain enough space for MAXPATHLEN characters. 
 Credits: bash 1.05
 */

//#obs: This is a cool thing!

void shell_pathname_backup ( char *path, int n ){

    register char *p = path + strlen(path);

    unsigned long saveN = (unsigned long) n;

    //#debug 
	//printf("%s", path);
	
    if (*path)
        p--;

    while (n--)
    {
        while(*p == '/')
            p--;

        while(*p != '/')
            p--;

        *++p = '\0';
    };


	// #todo: 
	// Criar em kernelmode uma roptina que fa�a o mesmo que 
	// a shell_pathname_backup 	
	// Atualizar no gerenciamento feito pelo kernel.


    system_call ( 176, 
        (unsigned long) saveN, (unsigned long) saveN, (unsigned long) saveN );
}



// Imprime todas as strings de um vetor de ponteiros.
// Isso vai ser usado pelo echo.

void shell_print_tokenList ( char *token_list[], char *separator ){

    int i;
    char *token;

    token = (char *) token_list[0];

    if ( token == NULL )
        return;


	//token = (char *) tokenList[i];
	//	if( token == NULL ){

    //#todo: Limits.

    for ( i=0; i,128; i++ )
    {
		token = (char *) token_list[i];

        if ( token == NULL )
            return;
		
		if ( gramado_strncmp ( (char *) token_list[i], "echo", 4 ) == 0 )
		    continue;	
		
		printf ("%s", token_list[i] );
		printf ("%s", separator );
    };
}


/* 
This way I don't have to know whether fclose is a function or a macro. 
Credits: bash 1.05.
 */
/*
int
stream_close( FILE *file );
int
stream_close( FILE *file )
{
     return ( fclose(file) );
};
*/

/* 
 Return the octal number parsed from STRING, or -1 to indicate
 that the string contained a bad number. 
 Credits: bash 1.05.
 */
/* 
int
read_octal( char *string );
int
read_octal( char *string )
{
    int result = 0;
    int digits = 0;
    
	while( *string && 
	       *string >= '0' && 
		   *string < '8' )
    {
        digits++;
        result = (result * 8) + *string++ - '0';
    };

    if(!digits || result > 0777 || *string)
        result = -1;

    
done:	
	return (result);
};
*/

/*  Credits: bash 1.05. */
/*
void 
decrement_variable( int *var );
void 
decrement_variable( int *var )
{
    *var = *var - 1;
};
*/




/* Check if it's a .bin file */
int is_bin ( char *cmd ){

    char *p;

    p = cmd;

    int len = strlen (p);

    if ( len <= 4 ) 
        return 0;


    p += len - 4;
    
    if ( *p++ != '.' ) 
        return 0;


    if ( gramado_strncmp ( (char *) p, "bin", 3 ) == 0 )
    {
        return 1;
    }

    return 0;
}


/* Check if it's a .sh1 file */
int is_sh1 ( char *cmd ){

    char *p;

    p = cmd;


    int len = strlen (p);


    if ( len <= 4 ) 
        return 0;


    p += len - 4;


    if ( *p++ != '.' ) 
        return 0;


    if ( gramado_strncmp ( (char *) p, "sh1", 3 ) == 0 )
    {
        return 1;
    }


    return 0;
}


/* 
 * Give version information about this shell. 
 */

void show_shell_version (void)
{
    if ( (void *) shell_name != NULL &&
         (void *) dist_version != NULL &&
         (void *) build_version != NULL )
    {
        printf ("%s version %s.%s \n", 
            shell_name, 
            dist_version, 
            build_version );
   }
}




//testando a rotina de salvar um arquivo.
//estamos usando a API.
	//
	// #importante:
	// N�o podemos chamar a API sem que todos os argumentos estejam corretos.
	//
	
	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???

int shell_save_file (void)
{
	int Ret=0;
	
	char file_1[] = "REDPILL    ";        // REDPILL
	char file_1_name[] = "REDPILL INI";   // redpill.ini

	unsigned long number_of_sectors = 0;
    size_t len = 0;
	
	
	printf ("shell_save_file: Salvando um arquivo ...\n");
	
	//
	// Lenght in bytes.
	//
	
    len = (size_t) strlen (file_1);

    if (len <= 0){
        printf ("shell_save_file:  Fail. Empty file.\n");
        return (int) 1;
    }

    if (len > 2048){
        printf ("shell_save_file:  Limit Fail. The  file is too long.\n");
        return (int) 1;
    }

    //
    // Number os sectors.
    //
	
	number_of_sectors = (unsigned long) ( len / 512 );
	
    if ( len > 0 && len < 512 )
    {
        number_of_sectors = 1; 
    }

    if ( number_of_sectors == 0 )
    {
        printf ("shell_save_file:  Limit Fail. (0) sectors so save.\n");
        return (int) 1;
    }

	//limite de teste.
	//Se tivermos que salvar mais que 4 setores.
    if ( number_of_sectors > 4 )
    {
	    printf ("shell_save_file:  Limit Fail. (%d) sectors so save.\n",
		    number_of_sectors );
        return (int) 1;
    }
	
	
    Ret = (int) gde_save_file ( 
                    file_1_name,            // name 
                    number_of_sectors,      // number of sectors.
                    len,                    // size in bytes
                    file_1,                 // address
                    0x20 );                 // flag

	//if (Ret == 0)

    printf ("shell_save_file: done\n");

    return (int) Ret;
}


/*
 Credits: gcc 0.9 
 Read chars from INFILE until a non-whitespace char
 and return that.  
 
 Comments, both Lisp style and C style, are treated 
 as whitespace.
 
 Tools such as genflags use this function.  
 */
/* 
int
read_skip_spaces (infile)
    FILE *infile;
{
    register int c;
    while (c = getc (infile))
    {
        if (c == ' ' || c == '\n' || c == '\t' || c == '\f')
	    ;
            else if (c == ';')
	             {
	                 while ((c = getc (infile)) && c != '\n') ;
	             }
                 else if (c == '/')
	                  {
	                      register int prevc;
	                      c = getc (infile);
	                      //if (c != '*')
	                          //dump_and_abort ('*', c, infile);
	  
	                      prevc = 0;
	                      while (c = getc (infile))
	                      {
	                          if (prevc == '*' && c == '/')
		                      break;
	                          prevc = c;
	                      }
	                  }
                      else break;
    }
    return c;
}
*/



/* 
 Credits: gcc 0.9
 Read an rtx code name into the buffer STR[].
 It is terminated by any of the punctuation chars 
 of rtx printed syntax.  
 */
/*
static void
read_name (str, infile)
     char *str;
     FILE *infile;
{
  register char *p;
  register int c;

  c = read_skip_spaces(infile);

  p = str;
  while (1)
    {
      if (c == ' ' || c == '\n' || c == '\t' || c == '\f')
	break;
      if (c == ':' || c == ')' || c == ']' || c == '"' || c == '/'
	  || c == '(' || c == '[')
	{
	  ungetc (c, infile);
	  break;
	}
      *p++ = c;
      c = getc (infile);
    }
  *p = NULL;
}
*/


//Qual ser� a linha que estar� no topo da janela.
void textSetTopRow ( int number )
{
    textTopRow = (int) number; 
}


int textGetTopRow (void)
{
    return (int) textTopRow; 
}


//Qual ser� a linha que estar� na parte de baixo da janela.
void textSetBottomRow ( int number )
{
    textBottomRow = (int) number; 
}


int textGetBottomRow (void)
{
    return (int) textBottomRow; 
}


void clearLine ( int line_number )
{
    int lin = (int) line_number; 
    int col=0;  

    int Offset = 0; //Deslocamento dentro do screen buffer.

	//cursor apontando par ao in�cio da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//in�cio da �rea de cliente.
	//left ser� a coluna.
	
	shellSetCursor ( col, lin );
		
	//colunas.
	for ( col=0; col < wlMaxColumns; col++ )
	{
	    //Mostra um char do screen buffer.
		printf( "%c", screen_buffer[Offset] );
		    
		Offset++; //ignora o atributo.
	    Offset++;
	};
	
    //shell_buffer_pos = 0;  //?? posi��o dentro do buffer do shell.	
}


//um teste mostrando todas as linhas do boffer de linhas.
void testShowLines (void){
	
	//desabilita o cursor
    system_call ( 245, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);

    int i=0;
    int j=0;


    for ( i=0; i<32; i++ )
    {
		for ( j=0; j<80; j++ )
		{
		    //LINES[i].CHARS[j] = (char) 'x';
		    //LINES[i].ATTRIBUTES[j] = (char) 7;
	        
			printf ("%c", LINES[i].CHARS[j] );
		}
		printf ("\n");
    };

	//reabilita o cursor
    system_call ( 244, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
}


//mostra a �rea vis�vel dentro do buffer de linhas.
void shellRefreshVisibleArea (void){
	
	//desabilita o cursor
    system_call ( 245, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	
	//
	//seta o cursor no in�cio da janela.
	//
	
	unsigned long left, top, right, bottom;
 
    left = (terminal_rect.left/smCharWidth);
    top = (terminal_rect.top/smCharHeight);
	
    shellSetCursor ( left, top );
	

	//
	// efetua o refresh do char atual, que agora � o primeiro 
	// depois os outros consecutivos.
	//
	
	int i=0;
	int j=0;
	
	//textTopRow = 3;
	//textBottomRow = 3 + 25;
	
	if ( textTopRow > textBottomRow )
	{
		printf("shellRefreshVisibleArea: textTopRow fail\n");
	}
	
	//toda a �rea vis�vel.
	//for ( i=0; i<25; i++ )	
	for ( i=textTopRow; i<textBottomRow; i++ )
	{
		for ( j=0; j<80; j++ )
		{	
	        //refresh
            printf ("%c", LINES[i].CHARS[j] );
		}
	};

	//reabilita o cursor
    system_call ( 244, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
}


void testChangeVisibleArea (void)
{
    textTopRow += textWheelDelta;
    textBottomRow += textWheelDelta;
}


void updateVisibleArea( int direction )
{
    switch (direction)
    {
	    case 0:
	        textTopRow += textWheelDelta;
	        textBottomRow += textWheelDelta;
            break; 

	    case 1:
	        textTopRow -= textWheelDelta;
	        textBottomRow -= textWheelDelta;
            break; 
    };
}





/*
 *====================================
 * gdeshell_save_config_file:
 *     Vamos salvar o arquivo de configuracao criado com as
 * configuracoes selecionadas pelo usuario com o prompt de comandos.
 *  
 * Testando a rotina de salvar um arquivo.
 * Estamos usando a API.
 */

int gdeshell_save_config_file (void){

    char file_1_name[] = "SETUP   TXT";
    int Ret=0;
    unsigned long number_of_sectors = 0;
    size_t len = 0;


    // #importante:
    // Não podemos chamar a API sem que todos os argumentos 
    // estejam corretos.

	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???
	
	
	//preparando o arquivo para salvar.
	//precisamos colocar no buffer
	
	//isso é um teste.
	
	
	//strcat( __setup_buffer, "initializing file ...");
	
	/*
	int l; //linha
	int c; //coluna
	int p = 0; //posição dentro do buffer.
	
	for ( l=0; l<16; l++ )
	{
		for ( c=0; c<80; c++ )
		{
			//pega um char.
			__setup_buffer[p] = (char) LINES[l].CHARS[c];
			p++;
		}
	};
	*/




    //Initializing ...
    printf ("\n");
    printf ("\n");
    printf ("gdeshell_save_config_file: Saving ...\n");


	// Lenght in bytes.

	//len = (size_t) strlen (file_1);
    len = (size_t) strlen ( __setup_buffer );


    if (len <= 0)
    {
        printf ("gdeshell_save_config_file: [FAIL] Empty file.\n");
        return (int) 1;
    }

    if (len > 2048)
    {
        printf ("gdeshell_save_config_file: [FAIL] Limits. The  file is too long.\n");
        return (int) 1;
    }


    //
    // Number os sectors.
    //


    number_of_sectors = (unsigned long) ( len / 512 );


    if ( len > 0 && len < 512 )
    {
        number_of_sectors = 1; 
    }

    if ( number_of_sectors == 0 ){
        printf ("gdeshell_save_config_file:  Limit Fail. (0) sectors to save.\n");
        return (int) 1;
    }

    // limite de teste.
    // Se tivermos que salvar mais que 4 setores.

    if ( number_of_sectors > 4 )
    {
        printf ("gdeshell_save_config_file:  Limit Fail. (%d) sectors to save.\n",
            number_of_sectors );
        return (int) 1;
    }

	//
	// Save
	//

    // name, number of sectors, size in bytes, address, flag.

    Ret = (int) gde_save_file ( file_1_name, 
                    number_of_sectors, len,            
                    &__setup_buffer[0], 
                    0x20 );    

    printf ("done\n");

    return (int) Ret;
}



// Deprecated
int desktopInitialize (void)
{
    printf ("desktopInitialize: Deprecated!\n");
    return 0;
}


// Exit the application.
void gdeshell_exit(void)
{
    printf ("gdeshell_exit: Exiting ...\n");
    
    //fprintf(stderr,"GDESHELL: Exiting with no error...\n");
    //fflush(stderr);
     
    _running = 0;
    
    // ...
    
    exit(0);
}

/*
 *********************************************************
 * main: 
 *     Fun��o principal.
 *     The Application Entry Point.
 *
 * @todo:
 *    +Checar argumentos.
 *    +Criar a janela do TERMINAL. (Ok).
 *    +Enviar mensagem de texto para ele. (Ok).
 *    +Configurar procedimento de janela.
 *    +Definir a janela que � �rea do cliente.
 *    +Carregar um arquivo na �rea de cliente.
 *    +Testar outros recursos do Kernel.
 *    +Testar as chamadas para pegar inform��es sobre o processo.
 *    +...
 *
 * Obs: Esses argumentos podem ser um padr�o.
 */

// #obs:
// O shell � um alicativo e deve rodar no terminal virtual.
// Receberemos os argumentos do crt0.
// #bugbug: No momento estamos usando uma vers�o persnalizada do crt0,
// onde os argumentos s�o criados � m�o. Mas precisamos usar o crt0 padr�o
// que pega os argumentos enviados pelo processo pai.

  

int main ( int argc, char *argv[] )
{
    FILE *default_input = stdin;
    
    int i=0;
    int arg_index = 1;

    char *local_pending_command = (char *) NULL;

    int locally_skip_execution = 0, top_level_arg_index;


    // Setup libc output mode.
    libc_set_output_mode (LIBC_DRAW_MODE);

    // Serial debug.
    gde_debug_print ("--------------------------\n");
    gde_debug_print ("gdeshell: Initializing ...\n");

    //#debug
    //printf ("gdeshell: *breakpoint");
    //gde_debug_print ("gdeshell: *breakpoint \n");
    //while (1){}


    // #bugbug
    // This pointer has an invalid address ?
    // Is this in a shared mamory area ??
    
    // shell_name = (char *) argv[0];
    // printf("%s\n",shell_name);
    // while(1){}


    //shell_environment = env;

#ifdef JOB_CONTROL
    if (act_like_sh)
        job_control = 0;
#endif


    //??
    /* If user supplied the "-login" flag, then set and invert LOGIN_SHELL. */
    if (make_login_shell)
        login_shell = -++login_shell;


after_flags:

    printf ("gdeshell: after_flags ...\n");

    //#testando printf .. ok
    //gde_debug_print ("gdeshell: *breakpoint \n");
    //while (1){}


    top_level_arg_index = arg_index;

    arg_index = top_level_arg_index;

    char *filename;


	// Obs: 
	// Esse n�o � um programa que roda em modo terminal,
	// ele na verdade cria um terminal dentro de uma janela filha.
	// isso pode servir para esse programa interpretar linguagem 
	// basic por exemplo.
	// os programas em modo terminal n�o criar�o janelas e rodar�o nas 
	// janelas de terminal cridas para eles pelo kernel.
	//#debug
	//deixe o kernel usar essa janela para teste.
	//Obs: N�o criaremos a janela principal desse programa 
	//para evitarmos erros com printf.
 

    int Status=0;

    //
    // == Args ================================
    //

	//Ok isso funcionou.
	//Argumentos passados com sucesso do crt0 para o main.

    printf("argc={%d}\n",argc);

	//if ( argc >=2 )
	//{
	//    printf("arg[0]={%s}\n",argv[0]);
	//    printf("arg[1]={%s}\n",argv[1]);	
	//}

	// ok
    //printf ("gdeshell: *breakpoint");
    //while (1){}

	
	
	//
	// Filtra a quantidade de argumentos.
	//
	
	//goto noArgs; 
	
	//N�o usar verbose nessa fase de tratar os argumentos
	//pois a janela ainda n�o foi inicializada.
	
	// Se n�o h� argumentos.
	if (argc < 1)
	{
		//printf("No args !\n");
		//#Test.
        //fprintf( stderr,"Starting Shell with no arguments...\n");	 	
		//die ("gdeshell: No args");
		
		interactive = 1;
		login_shell = 1;
		goto noArgs; 

	}else{
		
         if (argc < 2){
		     printf ("main: argc=%d We need 2 args or more\n", argc );
		    interactive = 1;
		    login_shell = 1;
		    goto noArgs;
		 }

		//printf("Testing args ...\n");
		
		//#todo: (possibilidades)
		//As flags poderia come�ar com f. Ex: fInteractive, fLoginShell,
		
	    if ( gramado_strncmp ( (char *) argv[0], "-interactive", 12 ) == 0 ){
			interactive = 1;
            //printf("Initializing an interactive shell ...\n");
            //printf("arg[0]={%s}\n",argv[0]);			
        };

        //Se o shell foi iniciado com um arquivo de script para ser 
        //executado.
        //a Flag -f indica que o que segue � um arquivo de script.
        //if( gramado_strncmp( (char *) argv[0], "-f", 2 ) == 0 )
        //{
		//	goto dosh2;
		//}			
		
	    if ( gramado_strncmp ( (char *) argv[1], "-login", 6 ) == 0 ){
			
			login_shell = 1;
			
			//printf("Initializing login ...\n");
            //printf("arg[1]={%s}\n",argv[1]);    
        };	
		
		//Nome passado viar argumento.
		//shell_name = (char*) argv[2];

        // ...
    };

	//Nothing.

noArgs:
    printf ("gdeshell: noArgs \n");

	//ok
    //printf ("gdeshell: *breakpoint");
    //while (1){}

	//...
	
	//@todo:
	//Podemos come�ar pegando o id do processo atual e 
	//melhorando a prioridade.
	
	
	// get current dir
	//pegamos o diret�rio atual.
	
	//get user dir
	//pegamos o diret�rio do usu�rio /root/user/(name)
	
	//set current dir
	//setamos para que o diret�rio do usu�rio seja o diret�rio atual.
	
	
	// Isso configura alguns padr�es do aplicativo.
	// Os argumentos tratados abaixo podem modificar esses padr�es
	// Ex: Um argumento de entrada pode solicitar a troca de cor de fonte.
	
	
	// #todo
	// #importante
	// Temos que usar as configura��es do terminal que o gdeshell est� rodando.
	// Ent�o n�o podemos simplesmente criar uma janela do tamanho que quisermos.
	
    //gde_debug_print ("gdeshell: *breakpoint \n");
    //while (1){}

    shellShell();

    //gde_debug_print ("gdeshell: *breakpoint \n");
    //while (1){}

	// Apenas inicialize. 
	// Continuaremos com o procedimento do shell e n�o o da barra,	
	
	
	// #Aten��o
	// Criaremos a janela tranquilamente usando os valores obtidos
	// na inicializa��o.
	
	
	//++
    gde_enter_critical_section ();    
    hWindow = shellCreateMainWindow (1);
    if ( (void *) hWindow == NULL )
    {
        printf ("shellCreateMainWindow FAIL!\n");
        gde_exit_critical_section ();
        exit(1);
        //while (1){}
    }
    gde_register_window (hWindow);
    gde_show_window (hWindow);
    gde_exit_critical_section ();
    //--


    //#debug
    //printf ("*breakpoint");
    //gde_debug_print ("gdeshell: *breakpoint \n");
    //while (1){}
 
	//
	// ++ terminal ++
	//

	// #importante
	// Definindo a janela como sendo uma janela de terminal.
	// Isso faz com que as digita��es tenham acesso ao procedimento de janela de terminal 
	// para essa janela e n�o apenas ao procedimento de janela do sistema.
	// # provavelmente isso marca os limites para a impress�o de caractere em modo terminal 
	
	// #importante
	// Nesse momento estamos configurando os 
	// limites do terminal gerenciado pelo kernel.

    gramado_system_call ( 
        SYSTEMCALL_SETTERMINALWINDOW, 
        (unsigned long) hWindow, 
        (unsigned long) hWindow, 
        (unsigned long) hWindow );

 
    //Salva ponteiro da janela principal e da janela do terminal. 
    shell_info.main_window     = (struct window_d *) hWindow;
    shell_info.terminal_window = (struct window_d *) hWindow;

    terminal_rect.left   = wpWindowLeft;
    terminal_rect.top    = wpWindowTop;
    
    terminal_rect.width  = wsWindowWidth;
    terminal_rect.height = wsWindowHeight;

	// Se der problema no tamanho da area de cliente 

    if ( terminal_rect.left < wpWindowLeft ||
         terminal_rect.top  < wpWindowTop ||
         terminal_rect.width  > wsWindowWidth ||
         terminal_rect.height > wsWindowHeight )
    {
        //#debug
        printf ("gdeshell: [FAIL]\n");
        printf ("terminal_rect: 2\n");
        printf ("l={%d} t={%d} w={%d} h={%d}\n", 
            terminal_rect.left, terminal_rect.top,
            terminal_rect.width, terminal_rect.height );
        
        exit(1);
        //while (1){ asm ("pause"); }
    }

    //printf("#debug breakpoint");
    //while(1){} 
	//===============================




    //==========================
    // Habilitando o cursor piscante de textos.
    shellSetCursor ( 
        (terminal_rect.left / smCharWidth), 
        (terminal_rect.top/smCharHeight) );
    system_call ( 244, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0 ); 
    //===========================


    //ok funcinou
    //gde_debug_print ("gdeshell: *breakpoint \n");
    //while (1){}



	// Init Shell:
	//     Inicializa vari�veis, buffers e estruturas. 
	//     Atualiza a tela.
	// #BUGBUG
	// Estamos passando um ponteiro que � uma vari�vel local.

    // #bugbug
    // alguma coisa esta falhando na maquina real nesse ponto ...
    // vamos usar break point e verbose.


    //++
    gde_enter_critical_section ();
    Status = (int) shellInit(hWindow); 
    if ( Status != 0 ){
        die ("gdeshell-main: shellInit fail\n");
    }
    gde_exit_critical_section (); 
    //--

    //printf ("gdeshell: breakpoint \n");
    //while(1){}


	// #importante:
	// Agora � a hora de pegar mensagens de input de teclado.
	// Mas se o shell n�o for interativo, ent�o n�o pegaremos 
	// mensagens de input de teclado.

    if ( interactive != 1 ){
        printf ("gdeshell is not interactive\n");
        goto skip_input;
    }



    //
    // == Get system message ==============================
    //

    // Buffer.
    //unsigned long message_buffer[5];

    // Stack.
    //struct window_d *msg_Window;
    //int msg_Message;
    //void *msg_Long1;
    //void *msg_Long2;


read_and_execute:
    // Nothing.
    shell_initialized = 1;

    //
    // == Main loop =================================================
    //
    
    int EventStatus=FALSE;  // No event.

Mainloop:

    while (_running){

        // See: ge/libcore/api.c
        EventStatus = (int) libcore_get_event();
        
        // We've got en event. 
        // Call the window procedure. 
        // Call event handler!
        
        if ( EventStatus == TRUE )
        {
            shellProcedure ( 
                (struct window_d *) LibCoreEventBuffer[0], 
                (int)               LibCoreEventBuffer[1], 
                (unsigned long)     LibCoreEventBuffer[2], 
                (unsigned long)     LibCoreEventBuffer[3] );
        }
        
        //pool or sleep.
        //if ( mode == ??
    };


    // Entramos aqui se running for igual a 0.
    // Sai do shell.

    switch (ShellFlag){
        case SHELLFLAG_EXIT: 
        default:
            goto end;
            break;
    };


	// Pulamos a parte que pega mensgens de input de teclado 
	// porque esse shell n�o est� configurado como interativo.

//
// == Run script ====================================
//

skip_input:

    shellExecuteThisScript(argv[3]);

//
// == Exit ===========================================================
//
    // Desabilitando o cursor de texto.
    // Quando outro aplicativo precisar ele clica em uma janela, 
    // ela ganha o foco e habilita o cursor piscante.
    
    // Retornar para o crt0.
    
end:
    system_call ( 245, 
        (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);

#ifdef SHELL_VERBOSE
    printf ("gdeshell: Exiting. Code '0' ...\n");
#endif 

    return 0;
}


//
// End.
//




