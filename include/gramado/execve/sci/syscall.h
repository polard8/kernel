/*
 * File: execve\sci\syscall.h
 *
 * Descrição:
 *     SCI - System Call Interface header.
 *
 *     Header do subsistema do kernel. 
 *     Pertence ao executive.
 *
 *     São as chamadas ao sistema. 
 *     Total de 256 chamadas.
 *
 * *IMPORTANTE Usar maiusculas para que as funções usem minusculas.
 *             Se um serviço implementado se mostrar nocivo ao sistema,  
 *             ele pode ser facilmente desabilitado. 
 *
 * @todo: Essas definições podem ficar no módulo service.
 *       pois é ele que atende as chamadas.
 * oBS:
 * e.g. malloc() is mainly implemented in user space, but uses system calls 
 * to increase the process’ heap size. Ou seja, somente quando acaba a área  
 * que o malloc tem em user mode é que ele chama o kernel e somente para 
 * almentar seu heap.
 *
 * A ordem dos 19 primeiros implica prioridade e velocidade.
 *
 * In this file:
 * =============
 * +Constantes que enumeram as systemcalls.
 * +protótipos para as system calls, separadas por grupos:
 *  executive, microkernel, hal.
 *
 * Versão 1.0, 2015, 2016.
 */
 
// 
// system call service routine numbers. 
//
 
//NULL.
#define	SYS_NULL          0
//Disk.
#define	SYS_READ_LBA      1
#define	SYS_WRITE_LBA     2
#define	SYS_READ_FILE     3
#define	SYS_WRITE_FILE    4
//Gráfico.
#define	SYS_VSYNC              5
#define	SYS_BUFFER_PUTPIXEL    6
#define	SYS_BUFFER_DRAWCHAR    7
#define	SYS_BUFFER_DRAWLINE    8
#define	SYS_BUFFER_DRAWRECT    9
#define	SYS_BUFFER_CREATEWINDOW    10  // ** função principal **
#define	SYS_REFRESHSCREEN          11
//rede
#define	SYS_REDE_R1    12
#define	SYS_REDE_R2    13
#define	SYS_REDE_R3    14
#define SYS_REDE_R4    15
//i/o de disco
#define	SYS_IO_R1    16
#define	SYS_IO_R2    17
#define	SYS_IO_R3    18
#define	SYS_IO_R4    19
//Outros. 
#define	SYS_REFRESH_BUFFER1      20
#define	SYS_REFRESH_BUFFER2      21
#define	SYS_REFRESH_BUFFER3      22
//screen.
#define	SYS_REFRESHSCREEN2       23
//bars.
#define	SYS_REFRESH_TITLEBAR     24
#define	SYS_REFRESH_MENUBAR      25
#define	SYS_REFRESH_TOOLBAR      26
#define	SYS_REFRESH_STATUSBAR    27
#define	SYS_REFRESH_TASKBAR      28
//buffer.
#define	SYS_MY_BUFFER_PRINTSTRING    29
//pixel.
#define	SYS_MY_BUFFER_PUTPIXEL     30
#define	SYS_MY_BUFFER2_PUTPIXEL    31
#define	SYS_MY_BUFFER3_PUTPIXEL    32
//Edit box.
#define	SYS_EDITBOX            33
//Cursor.
#define	SYS_VIDEO_SETCURSOR    34
//Message and procedures.
#define	SYS_SETPROCEDURE       35
#define	SYS_KSENDMESSAGE        36        //O teclado envia essa mensagem para o procedimento ativo.
#define	SYS_CALLSYSTEMPROCEDURE    37    //chama o procedimento padrao do sistema.
//Read sector.
#define	SYS_READSECTOR    38
//Show buffer.
#define	SYS_SHOWBUFFER    39
//Shut down conputer.
#define	SYS_SHUTDOWN        40
#define	SYS_41              41
//Load bitmap image, 
#define	SYS_LOADBMP    42
#define	SYS_43              43
// ?? Next app.
#define	SYS_G_NEXTAPP       44
//Message box.
#define	SYS_MESSAGEBOX      45
//Client area.
#define	SYS_SETCLIENTAREA   46

//
// Create Window support. 
// *Importante:
//  Essas funções serão usadas para suporte à criação de janelas 
//  A função principal será a número 10.
//
#define	SYS_BUFFER_CREATEWINDOWx    47  // envia argumentos de controle de janela.
#define	SYS_BUFFER_CREATEWINDOW1    48  // envia argumentos de posicionamento de janela.
#define	SYS_BUFFER_CREATEWINDOW2    49  // envia argumentos de dimensões de janela.

//(50~59) Window suppot, manipulação de janelas.
#define	SYS_BUFFER_RESIZEWINDOW    50 //resize. 
#define	SYS_BUFFER_REDRAWWINDOW    51 //redraw.
#define	SYS_BUFFER_REPLACEWINDOW   52 //replace.
#define	SYS_BUFFER_MAXIMIZEWINDOW    53 //MAXIMIZE
#define	SYS_BUFFER_MINIMIZEWINDOW    54 //MINMIZE
#define	SYS_BUFFER_GETFOREGROUNDWINDOW    55   //GET FOREGROUND
#define	SYS_BUFFER_SETFOREGROUNDWINDOW    56   // SET FOREGROUND
//Register window.
#define	SYS_REGISTERWINDOW          57
//Close window.
#define	SYS_CLOSEWINDOW             58
//Destroy window. (Destrói a estrutura e a classe).
#define	SYS_DESTROYWINDOW           59

//Active window.
#define	SYS_SETACTIVEWINDOW 60
#define	SYS_GETACTIVEWINDOW 61
//Focus.
#define	SYS_SETFOCUS     62
#define	SYS_GETFOCUS     63
#define	SYS_KILLFOCUS    64

//
// *** input de usuário ***
//

// driver >> executive >> destino certo.

//
// de 65 à 69 é reservado para evento de usuário.

//O driver do dispositivo envirá a mensagem pra cá para ser
//enviada para o destino certo.
#define	SYS_PUTCHAR 65
#define	SYS_66 66  
#define	SYS_67 67
//68-Um evento de mouse ocorreu e o driver de mouse enviou a mensagem pra cá.
//cabe ao executive receber essa mensagem do driver de mouse
//e processa-la da melhor forma..
#define	SYS_68 68
//69-Uma tecla foi digitada e driver de teclado enviou a mensagem pra cá.
//cabe ao executive receber essa mensagem do driver de teclado
//e enviá-la para a janela com o foco de entrada.
#define	SYS_69 69    


//process and thread support.
#define	SYS_EXIT    70    //Uma thread terminou.(terminate a current process)
#define	SYS_FORK    71    //fork.
#define	SYS_CREATETHREAD    72    //Create Thread.
#define	SYS_CREATEPROCESS   73    //Create process. 
#define	SYS_CLOSEALLPROCESS 74    //FECHA TODOS PROCESSO.
#define	SYS_EXECVE  75            //execve 
#define	SYS_GETNEXTPROCESS 76  //get next process
#define	SYS_SETNEXTPROCESS 77
#define	SYS_GETNEXTTHREAD 78   //get next thread.
#define	SYS_SETNEXTTHREAD 79
//process support.
#define	SYS_CURRENTPROCESSINFO 80    //Informações sobre o processo atual.
#define	SYS_GETPPID 81  //get parent process id.
#define	SYS_SETPPID 82  //set parent process id.
#define	SYS_WAIT4 83     //wait for process termination
#define	SYS_84 84
#define	SYS_GETPID 85  //GET CURRENT PROCESS ID.
#define	SYS_SETPID 86  //SET CURRENT PROCESS ID.

//Semaphore support.
#define	SYS_SEMAPHORE_DOWN 87
#define	SYS_88 88  //sendo usada pra outra coisa.
#define SYS_SEMAPHORE_UP 89

//90~98 reservado para thread support
#define	SYS_DEADTHREADCOLLECTOR    90
#define	SYS_ALERTTHREAD 91
#define	SYS_92 92
#define	SYS_93 93
#define	SYS_STARTTHREAD  94 //REAL (coloca a thread em standby para executar pela primeira vez.)
#define	SYS_95 95
#define	SYS_96 96
#define	SYS_97 97
#define	SYS_RESUMETHREAD 98  //retomar thrad.

//Window procedure arguments: window, msg, long1, long2.
#define	SYS_GETHWINDOW             99
#define	SYS_GETKEYBOARDMESSAGE    100
#define	SYS_GETLONG1              101  
#define	SYS_GETLONG2              102

//(103~109) Rotinas de mensagens. Channels, Sockets.

//usado na comunicação entre processos.
#define	SYS_RECEIVEMESSAGE    103  //Pega uma mensagem no PCB de um processo.
#define	SYS_SENDMESSAGE       104  //Envia uma mensagem para o PCB de um processo.

#define	SYS_REGISTERPROCEDURE 105  //REGISTER PROCEDURE.

#define	SYS_CREATECHANNEL  106     //create channel. 
#define	SYS_DESTROYCHANNEL 107     //destroy channel.
#define	SYS_OPENCHANNEL    108     //open channel.
#define	SYS_CLOSECHANNEL   109     //close channel.


//Reboot.
#define	SYS_REBOOT         110

//Outros. @todo: mensagem  
#define	SYS_111 111   //#mensagem.pega 4 elementos.
#define	SYS_112 112

//janela
// 113 Envia uma mensagem PAINT para o aplicativo atualizar a área de trabalho.
#define	SYS_113 113  

//  ## ENVIA UMA MENSAGEM PARA UMA JANELA ##
#define	SYS_SENDWINDOWMESSAGE 114  

//outros.
//#importante 
//115 usado pelos servidores para se comunicarem com o kernel.
#define	SYS_115 115  

//116 testando servidor
////envia uma mensagem de teste para o servidor taskman
#define	SYS_116 116
#define	SYS_117 117

//CreateWindow:
//Passando argumentos via memória. 
#define	SYS_118 118  

//119 - select color scheme
#define	SYS_SELECTCOLORSCHEME 119

//120-125 bars
#define	SYS_CREATEMENUBAR   120    
#define	SYS_CREATETASKBAR   121    
#define	SYS_CREATESTATUSBAR 122
#define	SYS_123 123

//reservado para janela
#define	SYS_124 124  //Show Window Rectangle.(coloca a janela no frontbuffer)
#define	SYS_125 125  //refresh Rectangle.(coloca um retângulo no frontbuffer)

//126~129 (RESERVADO PARA COMUNICAÇÃO COM DRIVER.)
#define	SYS_126 126
#define	SYS_127 127
#define	SYS_128 128
//Inicializando um driver:
//Um driver enviou uma systemcall confirmando a inicialização de um driver.
#define	SYS_DRIVERINITIALIZED 129  
 
//130-139 manipulação de texto.
#define	SYS_DRAWTEXT 130
#define	SYS_BUFFER_DRAWCHAR_WWF 131
#define	SYS_132 132
#define	SYS_133 133

//134 pegar informações sobre a área de cliente de uma janela;
#define	SYS_134 134  

//135 coloca caracteres na estrutura de terminal, para aplciativos pegarem
#define	SYS_FEEDTERMINAL 135
#define	SYS_136 136
#define	SYS_GETCH 137  //SUPORTE a getch()
#define	SYS_138 138    //get key state.
#define	SYS_GETSCANCODE 139  

//keyboard responder
#define	SYS_SET_CURRENT_KEYBOARD_RESPONDER 140
#define	SYS_GET_CURRENT_KEYBOARD_RESPONDER 141

//mouse responder
#define	SYS_SET_CURRENT_MOUSE_RESPONDER 142
#define	SYS_GET_CURRENT_MOUSE_RESPONDER 143

//144-149 Recursos da area do Cliente.
#define	SYS_GETCLIENTAREARECT 144
#define	SYS_SETCLIENTAREARECT 145

//janelas principais.
//usadas pelo gws
#define	SYS_146 146  //retorna o ponteiro para gui->screen 
#define	SYS_147 147  //retorna o ponteiro para gui->main

//grid
#define	SYS_148 148 //create grid
#define	SYS_149 149 //initialize grid.
//150-159 user and group support.
#define	SYS_CREATEUSER         150
#define	SYS_SETCURRENTUSERID   151
#define	SYS_GETCURRENTUSERID   152
#define	SYS_SETCURRENTGROUPID  153
#define	SYS_GETCURRENTGROUPID  154
#define	SYS_UPDATEUSERINFO     155
#define	SYS_SHOWUSERINFO       156
#define	SYS_GETCURRENTUSERSESSION   157 //user session
#define	SYS_GETCURRENTWINDOWSTATION 158 //window station
#define	SYS_GETCURRENTDESKTOP       159 //desktop


//network support
#define	SYS_160 160   //create socket (retorna o ponteiro para a estrutura)
#define	SYS_161 161    //get socket IP	
#define	SYS_162 162  //get socket port	
#define	SYS_163 163  //update socket  
#define	SYS_164 164
#define	SYS_165 165
#define	SYS_166 166

/*gramado core specials execve*/
#define	SYS_GRAMADOCORE_INIT_EXECVE    167
#define	SYS_GRAMADOCORE_SHELL_EXECVE   168
#define	SYS_GRAMADOCORE_TASKMAN_EXECVE 169
//#importante
//fs - gerenciamento de arquivos e fs.
//@todo: get set disk id e directory id.
#define	SYS_PWD 170                 // Print Working Directory.
#define	SYS_GETCURRENTVOLUMEID 171  // Get current volume id.
#define	SYS_SETCURRENTVOLUMEID 172  // configura o id do volume atual.

// Listar os arquivos do diretório. 
// Dados ids de disco, volume e diretório.
#define	SYS_LISTFILES          173  
#define	SYS_SEARCHFILE         174  // Procurar arquivo. 

//175 atualizar string no pathname do pwd. 
#define	SYS_175 175  //#usado para atualiza pwd
#define	SYS_176 176  //#usado para atualiza pwd

//listando arquivos em um diretório dado o nome.
#define	SYS_177 177  

#define	SYS_178 178

// # test #
//#bugbug: suspenso	
// passando vetor de ponteiros,
// executando um novo programa no processo init.
#define	SYS_179 179

//Memory support.
#define	SYS_CREATEPAGEDIRECTORY 180    //cria um pagedir.
#define	SYS_CREATEPAGETABLE     181    //cria uma pagetable.
#define	SYS_SHOWMEMORYSTRUCTS   182    //mostra estruturas de gerencia de memória.
#define	SYS_SETCR3              183    //configura o cr3 do processo atual.
#define	SYS_GETPROCESSHEAPPOINTER 184  //pega o heap pointer de um processo.
#define	SYS_SETKERNELHEAP 185          //configura o heap do kernel.
#define	SYS_ALLOCATEKERNELHEAP 186     //aloca heap do kernel.
#define	SYS_FREEKERNELHEAP 187         //Libera heap do kernel.
#define	SYS_GETPROCESSDIRECTORY 188    //get process directory.
#define	SYS_SETPROCESSDIRECTORY 189    //set process directory.
//memory support.
#define	SYS_GETPAGEDIRVALUE 190  //get page dir value.
//Aloca memória virtual para um processo.
//Deve-se alocar memória dentro do heap do processo.
#define	SYS_ALLOCATEVIRTUALMEMORY 191  //ALOCA MEMÓRIA VIRTUAL PARA UM PROCESSO.
#define	SYS_192 192
#define	SYS_193 193
#define	SYS_194 194
#define	SYS_195 195
#define	SYS_196 196
#define	SYS_197 197
#define	SYS_198 198
#define	SYS_GC 199
//variados
#define	SYS_SENDSIGNAL 200  //Envia um sinal para um processo.
#define	SYS_WAIT4OBJECT 201  //espera por um objeto
#define	SYS_WAIT4EVENT  202   //ESPERA POR UM EVENTO.
#define	SYS_WAIT4DEVICE 203  //ESPERA POR UM DISPOSITIVO.
#define	SYS_WAIT4SIGNAL 204  //
#define	SYS_GENERICWAIT 205
#define	SYS_TIMERGETTICKCOUNT 206
#define	SYS_TIMERGETTIMEOUT 207
#define	SYS_TIMERSETTIMEOUT 208
#define	SYS_CALLIOSERVICES 209  //call i/o services. (io.c)
//terminal emulator support.
#define	SYS_CREATETERMINAL 210
#define	SYS_GETCURRENTTERMINAL 211
#define	SYS_SETCURRENTTERMINAL 212
#define	SYS_GETTERMINALINPUTBUFFER 213
#define	SYS_SETTERMINALINPUTBUFFER 214
#define	SYS_GETTERMINALWINDOW 215
#define	SYS_SETTERMINALWINDOW 216
#define	SYS_GETTERMINALRECT 217
#define	SYS_SETTERMINALRECT 218
#define	SYS_DESTROYTERMINAL 219

#define	SYS_REBOOT2   220
#define	SYS_EXECUTEPROGRAM 221
#define	SYS_222 222
#define	SYS_223 223

//time date
#define	SYS_GETTIME 224
#define	SYS_GETDATE 225

//Critical section support.
#define	SYS_GET_KERNELSEMAPHORE    226  //Get.     
#define	SYS_CLOSE_KERNELSEMAPHORE  227  //Close (0).
#define	SYS_OPEN_KERNELSEMAPHORE   228  //Open  (1).


#define	SYS_KERNELDEBUG 229    //some kernel checks.
//logon logoff support.
#define	SYS_STARTLOGON  230
#define	SYS_STARTLOGOFF 231
#define	SYS_232 232
#define	SYS_233 233
#define	SYS_234 234
#define	SYS_235 235
#define	SYS_236 236 //reservado para boot support.
#define	SYS_237 237 //reservado para boot support.
#define	SYS_238 238 //reservado para boot support.
#define	SYS_SETBOOTOPTIONS 239 //boot support.

//240-249 Reservar próximos para gerenciamento de cursor e ponteiros.
#define	SYS_GETCURSORX 240
#define	SYS_GETCURSORY 241
#define	SYS_242 242
#define	SYS_243 243
#define	SYS_244 244   //enable text cursor.
#define	SYS_245 245   //disable text cursor.

#define	SYS_246 246

#define	SYS_247 247
#define	SYS_248 248
#define	SYS_249 249
//Info support.
#define	SYS_GETSYSTEMMETRICS  250 
#define	SYS_SHOWDISKINFO      251 //Informações sobre o disco atual.            
#define	SYS_SHOWVOLUMEINFO    252 //Informações sobre o volume atual.
#define	SYS_MEMORYINFO        253
#define	SYS_SHOWPCIINFO       254
#define	SYS_SHOWKERNELINFO    255


// 
// system call service routine prototypes. 
//

/*
typedef struct systemcall_d systemcall_t;
struct systemcall_d
{
    object_type_t objectType;
	object_class_t objectClass;
	
	int number;
	struct process_d *process; //caller
}
systemcall_t *CurrentSystemCall;
*/


//#importante:
//@todo system call table.
//unsigned long sys_call_table[] = {
//    ...
	//endereços dos serviços.
//	...
//};	

//
// End.
//
