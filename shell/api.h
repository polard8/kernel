/*
 * API - This is the header for 32bit applications.
 * Copyright (c) 2017 Fred Nora.
 *
 * File: api.h 
 *
 * @todo: Esse arquivo poderia se chamar gramado.h.
 *        Ou gramado.h incluir esse arquivo.
 *   
 * Description:
 *    Header da API do sistema.
 *    API - ( Application Programming Interface ).
 *    The functions here, call the services of the Kernel via interrupts. 
 *    So and application in User Mode can uses the Kernel resources and 
 * the resources of the modules.
 *
 * Sobre as interrupções:
 *     +As primeiras são interrupções de hardware.
 *     +As interrupções de serviços do KERNEL vão de 48 à 199.
 *     +A interrupções principal é a *200.
 *     +As interrupções de chamadas especiais vão de 201 até 215. 
 *     +As interrupções de serviços da GUI vão de 216 à 219.
 *     +As outras estão indefinidas 220 até 255.
 *
 * Patterns:
 *     + My Own.
 *     + Single UNIX Specification (SUS).
 *     + Portable Operating System Interface (POSIX).
 *     + C99. 
 *     + ...  
 *
 * Sequência:
 *     +Os números das interrupções suportadas.
 *     +Os números dos serviços da interrupção 200.
 *
 *     *IMPORTANTE, as definições de chamadas não podem ser minúsculas.
 *
 * Obs: No futuro pode haver alguma reorganização desses números. 
 *      a mesma ordem deverá se obedecida no kernel base. 
 *
 * Histórico: 
 *     2013 - Esse arquivo foi criado por Fred Nora.
 *     2014 - Implimentação de novas chamadas. 
 *     2015 - Implimentação de novas chamadas.
 *     2016 - Implementação de novas chamadas.
 *     2017 - Revisão.
 */

 
//
// @todo: Fazer suporte a objetos. estruturas.
//
 
// 
//Interrupções. 
//


/*
 * KERNEL:
 *     Serviços relativos ao gerenciamento do kernel.
 *     Manipula status e estatísticas do kernel. Também faz configurações 
 * em tempo real, tais como: Selecionar tipo de scheduler, gerenciar 
 * quantidade de recursos etc ...
 *     Isso são interrupções.
 *     De 48 até 199.
 */
//Kernel.
#define	KERNEL      48
#define	KERNEL48    48
#define	KERNEL49    49

#define	KERNEL50    50
#define	KERNEL51    51
#define	KERNEL52    52
#define	KERNEL53    53
#define	KERNEL54    54
#define	KERNEL55    55
#define	KERNEL56    56
#define	KERNEL57    57
#define	KERNEL58    58
#define	KERNEL59    59

#define	KERNEL60    60
#define	KERNEL61    61
#define	KERNEL62    62
#define	KERNEL63    63
#define	KERNEL64    64
#define	KERNEL65    65
#define	KERNEL66    66
#define	KERNEL67    67
#define	KERNEL68    68
#define	KERNEL69    69

#define	KERNEL70    70
#define	KERNEL71    71
#define	KERNEL72    72
#define	KERNEL73    73
#define	KERNEL74    74
#define	KERNEL75    75
#define	KERNEL76    76
#define	KERNEL77    77
#define	KERNEL78    78
#define	KERNEL79    79

#define	KERNEL80    80
#define	KERNEL81    81
#define	KERNEL82    82
#define	KERNEL83    83
#define	KERNEL84    84
#define	KERNEL85    85
#define	KERNEL86    86
#define	KERNEL87    87
#define	KERNEL88    88
#define	KERNEL89    89

#define	KERNEL90    90
#define	KERNEL91    91
#define	KERNEL92    92
#define	KERNEL93    93
#define	KERNEL94    94
#define	KERNEL95    95
#define	KERNEL96    96
#define	KERNEL97    97
#define	KERNEL98    98
#define	KERNEL99    99

#define	KERNEL100   100
#define	KERNEL101   101
#define	KERNEL102   102
#define	KERNEL103   103
#define	KERNEL104   104
#define	KERNEL105   105
#define	KERNEL106   106
#define	KERNEL107   107
#define	KERNEL108   108
#define	KERNEL109   109

#define	KERNEL110    110
#define	KERNEL111    111
#define	KERNEL112    112
#define	KERNEL113    113
#define	KERNEL114    114
#define	KERNEL115    115
#define	KERNEL116    116
#define	KERNEL117    117
#define	KERNEL118    118
#define	KERNEL119    119

#define	KERNEL120    120
#define	KERNEL121    121
#define	KERNEL122    122
#define	KERNEL123    123
#define	KERNEL124    124
#define	KERNEL125    125
#define	KERNEL126    126
#define	KERNEL127    127
#define	KERNEL128    128
#define	KERNEL129    129

#define	KERNEL130    130
#define	KERNEL131    131
#define	KERNEL132    132
#define	KERNEL133    133
#define	KERNEL134    134
#define	KERNEL135    135
#define	KERNEL136    136
#define	KERNEL137    137
#define	KERNEL138    138
#define	KERNEL139    139

#define	KERNEL140    140
#define	KERNEL141    141
#define	KERNEL142    142
#define	KERNEL143    143
#define	KERNEL144    144
#define	KERNEL145    145
#define	KERNEL146    146
#define	KERNEL147    147
#define	KERNEL148    148
#define	KERNEL149    149

#define	KERNEL150    150
#define	KERNEL151    151
#define	KERNEL152    152
#define	KERNEL153    153
#define	KERNEL154    154
#define	KERNEL155    155
#define	KERNEL156    156
#define	KERNEL157    157
#define	KERNEL158    158
#define	KERNEL159    159

#define	KERNEL160    160
#define	KERNEL161    161
#define	KERNEL162    162
#define	KERNEL163    163
#define	KERNEL164    164
#define	KERNEL165    165
#define	KERNEL166    166
#define	KERNEL167    167
#define	KERNEL168    168
#define	KERNEL169    169

#define	KERNEL170    170
#define	KERNEL171    171
#define	KERNEL172    172
#define	KERNEL173    173
#define	KERNEL174    174
#define	KERNEL175    175
#define	KERNEL176    176
#define	KERNEL177    177
#define	KERNEL178    178
#define	KERNEL179    179

#define	KERNEL180    180
#define	KERNEL181    181
#define	KERNEL182    182
#define	KERNEL183    183
#define	KERNEL184    184
#define	KERNEL185    185
#define	KERNEL186    186
#define	KERNEL187    187
#define	KERNEL188    188
#define	KERNEL189    189


#define	KERNEL190    190
#define	KERNEL191    191
#define	KERNEL192    192
#define	KERNEL193    193
#define	KERNEL194    194
#define	KERNEL195    195
#define	KERNEL196    196
#define	KERNEL197    197
#define	KERNEL198    198
#define	KERNEL199    199


/*
 * SYSTEM:
 *     Serviços básicos do sistema.
 *     Com essas chamas uma aplicações poderá utilizar recursos
 * de de sistema oferecidos pelo kernel base. São recurso diversos
 * porém não se espera que essas chamas tenham um bom desmpenho, mas
 * sim que ofereçam um grande número de serviços básicos.
 * Obs: A interrupção 200 é a interrupção principal, ela ofereçe
 * vários recursos básicos e fundamentais, portanto não se espera 
 * desempenho nessa chamada, mas sim uma grande quantidade de serviços
 * básicos. Já as interrupções que vão de 201 até 215 oferecem recursos 
 * específicos com o propósito de ganhar desempenho em serviços considerados 
 * importantes para o desempenho geral do sistema.
 *
 */
//Sistema.
#define	SYSTEM  200    //*Principal.
//Outras.
#define	SYSTEM1    201
#define	SYSTEM2    202
#define	SYSTEM3    203
#define	SYSTEM4    204
#define	SYSTEM5    205
#define	SYSTEM6    206
#define	SYSTEM7    207
#define	SYSTEM8    208
#define	SYSTEM9    209
#define	SYSTEM10   210
#define	SYSTEM11   211
#define	SYSTEM12   212
#define	SYSTEM13   213
#define	SYSTEM14   214
#define	SYSTEM15   215
//..


/*
 * GUI:
 *     Serviços gráficos rápidos.
 *     Com essas chamadas será possível utilizar os recursos
 * gráficos oferecidos pelo kernel base. O kernel base, por sua vez,
 * atende as chamadas com rotinas próprias e com rotinas disponíveis
 * na biblioteca em user mode.
 *     O objetivo maior dessa chamadas é oferecer serviços gráficos
 * que sejam atendidos mais rapidamente que os outros serviços do 
 * do kernel.
 * Obs: Serão apenas as interrupções 216, 217, 218 e 219.
 *
 */
 
#define	FAST_CREATE_WINDOW     216 //Obs: Essa substitui a chamada GUI. 
#define	GUI     216  //Fast Create window.
#define	GUI217  217
#define	GUI218  218
#define	GUI219  219


//
// Obs: As outras estão indefinidas. De 220 até 255.
//


//
// * Agora segue a lista de serviços usados pela interupção principal. 200.
//

/*
 * interrupção 200:
 * ===============
 *     Lista de serviços oferecidos pela interrupção 200.
 *     Essa é a interrupção de sistema, a principal interrupção.
 * Ofereçe diversos recurso básicos.
 *     O propósito é oferecer um grande número de recursos básicos
 * não dando prioridade ao desempenho.
 *
 * Obs: A ordem dos 19 primeiros implica prioridade e velocidade.
 *      Os serviços estão organizados por categoria.
 *
 * Lembrete: 
 * *Importante: Lembre-se que a ordem que está aqui deve necessariamente
 * ser a mesma ordem encontrada no kernel base. Portanto, alterações
 * aqui apresentam um grande custo, pois acarretam mudanças no kernel base.
 * 
 * Histórico da lista:
 *     2015 - Created.
 *     Set 2016 - Revisão.
 *     ...
 */
//NULL.
#define	SYSTEMCALL_NULL  0

//Disk.
#define	SYSTEMCALL_READ_LBA    1
#define	SYSTEMCALL_WRITE_LBA   2
#define	SYSTEMCALL_READ_FILE   3
#define	SYSTEMCALL_WRITE_FILE  4

//Gráfico.
#define	SYSTEMCALL_VSYNC                5
#define	SYSTEMCALL_BUFFER_PUTPIXEL      6
#define	SYSTEMCALL_BUFFER_DRAWCHAR      7
#define	SYSTEMCALL_BUFFER_DRAWLINE      8
#define	SYSTEMCALL_BUFFER_DRAWRECT      9
#define	SYSTEMCALL_BUFFER_CREATEWINDOW  10
#define	SYSTEMCALL_REFRESHSCREEN        11

//Rede.
#define	SYSTEMCALL_REDE_RES1  12
#define	SYSTEMCALL_REDE_RES2  13
#define	SYSTEMCALL_REDE_RES3  14
#define	SYSTEMCALL_REDE_RES4  15

//i/o.
#define	SYSTEMCALL_IO_RES1  16
#define	SYSTEMCALL_IO_RES2  17
#define	SYSTEMCALL_IO_RES3  18
#define	SYSTEMCALL_IO_RES4  19

//Outros. 

//Buffer.
#define	SYSTEMCALL_REFRESH_BUFFER1  20
#define	SYSTEMCALL_REFRESH_BUFFER2  21
#define	SYSTEMCALL_REFRESH_BUFFER3  22

//Screen.
#define	SYSTEMCALL_REFRESH_SCREEN2  23

//Refresh Bars.
#define	SYSTEMCALL_REFRESH_TITLEBAR   24
#define	SYSTEMCALL_REFRESH_MENUBAR    25
#define	SYSTEMCALL_REFRESH_TOOLBAR    26
#define	SYSTEMCALL_REFRESH_STATUSBAR  27
#define	SYSTEMCALL_REFRESH_TASKBAR    28

//Buffer: Print string.
#define	SYSTEMCALL_BUFFER_PRINTSTRING  29

//Buffer: Put pixel on buffer.
#define	SYSTEMCALL_BUFFER1_PUTPIXEL  30
#define	SYSTEMCALL_BUFFER2_PUTPIXEL  31
#define SYSTEMCALL_BUFFER3_PUTPIXEL  32

//Edit box.
#define	SYSTEMCALL_EDITBOX    33

//Cursor.
#define	SYSTEMCALL_SETCURSOR  34

//Message and procedures.
#define	SYSTEMCALL_SETPROCEDURE          35
#define	SYSTEMCALL_KSENDMESSAGE          36  //O teclado envia essa mensagem para o procedimento ativo.
#define	SYSTEMCALL_CALL_SYSTEMPROCEDURE  37  //chama o procedimento padrao do sistema.

//Read sector.
#define	SYSTEMCALL_READSECTOR  38

//Show buffer.
#define	SYSTEMCALL_SHOWBUFFER  39

//Shut down computer.
#define	SYSTEMCALL_SHUTDOWN  40    //Desliga o computador.
#define	SYSTEMCALL_41        41

//Bitmap img: 
#define	SYSTEMCALL_LOAD_BITMAP_16x16  42  //Load bitmap image, size=16x16.
#define	SYSTEMCALL_43                 43

// ?? Next app.
#define	SYSTEMCALL_G_NEXT_APP         44

//Message box.
#define	SYSTEMCALL_MESSAGE_BOX        45

//Client area.
#define	SYSTEMCALL_SET_CLIENT_AREA    46

//Create Window support.
#define	SYSTEMCALL_CREATEWINDOW0  47 // envia argumentos de controle. 
#define	SYSTEMCALL_CREATEWINDOW1  48 // envia argumentos de posicionamento.
#define	SYSTEMCALL_CREATEWINDOW2  49 // envia argumentos de dimensões.

//
//(50~59) Window suppot, manipulação de janelas.
//

#define	SYSTEMCALL_RESIZEWINDOW    50 //resize. 
#define	SYSTEMCALL_REDRAWWINDOW    51 //redraw.
#define	SYSTEMCALL_REPLACEWINDOW   52 //replace.
#define	SYSTEMCALL_MAXIMIZEWINDOW    53 //MAXIMIZE
#define	SYSTEMCALL_MINIMIZEWINDOW    54 //MINMIZE
#define	SYSTEMCALL_GETFOREGROUNDWINDOW    55   //GET FOREGROUND
#define	SYSTEMCALL_SETFOREGROUNDWINDOW    56   // SET FOREGROUND
//Register window.
#define	SYSTEMCALL_REGISTERWINDOW  57  
//Close window.
#define	SYSTEMCALL_CLOSEWINDOW     58
//Destroy window. (Destrói a estrutura e a classe).
#define	SYSTEMCALL_DESTROYWINDOW   59



//Active window support.
#define	SYSTEMCALL_SETACTIVEWINDOW  60
#define	SYSTEMCALL_GETACTIVEWINDOW  61

//Focus support.
#define	SYSTEMCALL_SETFOCUS   62
#define	SYSTEMCALL_GETFOCUS   63
#define	SYSTEMCALL_KILLFOCUS  64

//Outros. 
//@todo: Reservar próximos para seleção de janela. 
#define	SYSTEMCALL_SYS_PUTCHAR  65
#define	SYSTEMCALL_66  66
#define	SYSTEMCALL_67  67
#define	SYSTEMCALL_68  68
#define	SYSTEMCALL_69  69

//Exit process support.
#define	SYSTEMCALL_EXIT             70

//fork support.
#define	SYSTEMCALL_FORK             71  

//Create thread.
#define	SYSTEMCALL_CREATETHREAD     72

//Create process.
#define	SYSTEMCALL_CREATEPROCESS    73

//Outros. 
//@todo: Reservar próximos para manipulação de threads e processos. 
#define	SYSTEMCALL_CLOSEALLPROCESS  74
#define	SYSTEMCALL_75               75 //poderia ser close current process.??
#define	SYSTEMCALL_GETNEXTPROCESS   76
#define	SYSTEMCALL_SETNEXTPROCESS   77
#define	SYSTEMCALL_GETNEXTTHREAD    78
#define	SYSTEMCALL_SETNEXTTHREAD    79

//@todo: Resevar próximos para manipulação de processos.
#define	SYSTEMCALL_CURRENTPROCESSINFO  80  //Informações sobre o processo atual.
#define	SYSTEMCALL_GETPPID  81
#define	SYSTEMCALL_SETPPID  82
#define	SYSTEMCALL_WAIT4    83 //wait for process termination
#define	SYSTEMCALL_84       84
#define	SYSTEMCALL_GETPID   85
#define	SYSTEMCALL_SETPID   86
#define	SYSTEMCALL_SEMAPHORE_DOWN  87
#define	SYSTEMCALL_88              88  //Em uso. não mudar.
#define	SYSTEMCALL_SEMAPHORE_UP    89

//reserva próximos para manipulação de threads.
//Dead thread collector.
#define	SYSTEMCALL_DEAD_THREAD_COLLECTOR  90
#define	SYSTEMCALL_ALERTTHREAD  91
#define	SYSTEMCALL_92  92
#define	SYSTEMCALL_93  93
#define	SYSTEMCALL_STARTTHREAD  94 //REAL (coloca a thread em standby para executar pela primeira vez.)
#define	SYSTEMCALL_95  95
#define	SYSTEMCALL_96  96
#define	SYSTEMCALL_97  97
#define	SYSTEMCALL_RESUMETHREAD  98

//Procedure arguments. (window,msg,long1,long2)
#define	SYSTEMCALL_GET_HWINDOW           99
#define	SYSTEMCALL_GET_KEYBOARD_MESSAGE  100
#define	SYSTEMCALL_GET_LONG1             101 
#define	SYSTEMCALL_GET_LONG2             102

//(103~109) Rotinas de mensagens. Channels, Sockets.
#define	SYSTEMCALL_RECEIVEMESSAGE     103  //Pega uma mensagem no PCB de um processo.
#define	SYSTEMCALL_SENDMESSAGE        104  //Envia uma mensagem para o PCB de um processo.
#define	SYSTEMCALL_REGISTERPROCEDURE  105
#define	SYSTEMCALL_CREATECHANNEL      106
#define	SYSTEMCALL_DESTROYCHANNEL     107
#define	SYSTEMCALL_OPENCHANNEL        108
#define	SYSTEMCALL_CLOSECHANNEL       109

//Reboot.
#define	SYSTEMCALL_REBOOT  110

//Outros. 
//@todo: Reservar para gerenciamento de energia. 111- 119
#define	SYSTEMCALL_111  111
#define	SYSTEMCALL_112  112
#define	SYSTEMCALL_113  113
#define	SYSTEMCALL_114  114
#define	SYSTEMCALL_115  115
#define	SYSTEMCALL_116  116
#define	SYSTEMCALL_117  117
#define	SYSTEMCALL_118  118
#define	SYSTEMCALL_119  119

//??
//120-125 gerenciamento de barras
#define	SYSTEMCALL_CREATEMENUBAR    120
#define	SYSTEMCALL_CREATETASKBAR    121
#define	SYSTEMCALL_CREATESTATUSBAR  122
#define	SYSTEMCALL_123              123
#define	SYSTEMCALL_124              124
#define	SYSTEMCALL_125              125

//126~129 (RESERVADO PARA COMUNICAÇÃO COM DRIVER.)
#define	SYSTEMCALL_126 126
#define	SYSTEMCALL_127 127
#define	SYSTEMCALL_128 128
//129: Inicializando um driver. Um driver enviou uma systemcall 
//confirmando a inicialização de um driver.
#define	SYSTEMCALL_DRIVERINITIALIZED 129

//130-139 Manipulação de texto.
#define	SYSTEMCALL_DRAWTEXT  130
#define	SYSTEMCALL_131       131
#define	SYSTEMCALL_132       132
#define	SYSTEMCALL_133       133
#define	SYSTEMCALL_134       134
#define	SYSTEMCALL_135       135
#define	SYSTEMCALL_136       136
#define	SYSTEMCALL_137       137
#define	SYSTEMCALL_138       138
#define	SYSTEMCALL_139       139

//Outros. (texto)
#define	SYSTEMCALL_140 140
#define	SYSTEMCALL_141 141
#define	SYSTEMCALL_142 142
#define	SYSTEMCALL_143 143

//144-149 Recursos da area do Cliente.
#define	SYSTEMCALL_GETCLIENTAREARECT 144    // Get client Area rect.
#define	SYSTEMCALL_SETCLIENTAREARECT 145    // Set Client Area rect.
#define	SYSTEMCALL_146 146
#define	SYSTEMCALL_147 147
#define	SYSTEMCALL_148 148
#define	SYSTEMCALL_149 149


//150-159 user and group support.
#define	SYSTEMCALL_CREATEUSER         150
#define	SYSTEMCALL_SETCURRENTUSERID   151
#define	SYSTEMCALL_GETCURRENTUSERID   152
#define	SYSTEMCALL_SETCURRENTGROUPID  153
#define	SYSTEMCALL_GETCURRENTGROUPID  154
#define	SYSTEMCALL_UPDATEUSERINFO     155
#define	SYSTEMCALL_SHOWUSERINFO       156
#define	SYSTEMCALL_157 157
#define	SYSTEMCALL_158 158
#define	SYSTEMCALL_159 159


//160-169 network support
#define	SYSTEMCALL_160 160
#define	SYSTEMCALL_161 161
#define	SYSTEMCALL_162 162
#define	SYSTEMCALL_163 163
#define	SYSTEMCALL_164 164
#define	SYSTEMCALL_165 165
#define	SYSTEMCALL_166 166
#define	SYSTEMCALL_167 167
#define	SYSTEMCALL_168 168
#define	SYSTEMCALL_169 169

//170-179 network support
#define	SYSTEMCALL_170 170
#define	SYSTEMCALL_171 171
#define	SYSTEMCALL_172 172
#define	SYSTEMCALL_173 173
#define	SYSTEMCALL_174 174
#define	SYSTEMCALL_175 175
#define	SYSTEMCALL_176 176
#define	SYSTEMCALL_177 177
#define	SYSTEMCALL_178 178
#define	SYSTEMCALL_179 179

//180-189 Memory support.
#define	SYSTEMCALL_CREATEPAGEDIRECTORY 180
#define	SYSTEMCALL_CREATEPAGETABLE 181
#define	SYSTEMCALL_SHOWMEMORYSTRUCTS 182
#define	SYSTEMCALL_SETCR3 183
#define	SYSTEMCALL_GETPROCESSHEAPPOINTER 184
#define	SYSTEMCALL_SETKERNELHEAP 185
#define	SYSTEMCALL_ALLOCATEKERNELHEAP 186
#define	SYSTEMCALL_FREEKERNELHEAP 187
#define	SYSTEMCALL_GETPROCESSDIRECTORY 188
#define	SYSTEMCALL_SETPROCESSDIRECTORY 189

//190-199 memory support.
#define	SYSTEMCALL_SYS_GETPAGEDIRVALUE 190
#define	SYSTEMCALL_ALLOCATEVIRTUALMEMORY 191
#define	SYSTEMCALL_192 192
#define	SYSTEMCALL_193 193
#define	SYSTEMCALL_194 194
#define	SYSTEMCALL_195 195
#define	SYSTEMCALL_196 196
#define	SYSTEMCALL_197 197
#define	SYSTEMCALL_198 198
#define	SYSTEMCALL_199 199   //@todo: GC

//Outros. (sinais, alertas, mesagens)
#define	SYSTEMCALL_SENDSIGNAL         200  //??reservar.
#define	SYSTEMCALL_WAIT4OBJECT        201
#define	SYSTEMCALL_WAIT4EVENT         202
#define	SYSTEMCALL_WAIT4DEVICE        203
#define	SYSTEMCALL_WAIT4SIGNAL        204
#define	SYSTEMCALL_GENERICWAIT        205
#define	SYSTEMCALL_TIMERGETTICKCOUNT  206
#define	SYSTEMCALL_TIMERGETTIMEOUT    207
#define	SYSTEMCALL_TIMERSETTIMEOUT    208
#define	SYSTEMCALL_CALLIOSERVICES     209

//tty;console;terminal - terminal emulator support.
#define	SYSTEMCALL_CREATETERMINAL          210
#define	SYSTEMCALL_GETCURRENTTERMINAL      211
#define	SYSTEMCALL_SETCURRENTTERMINAL      212
#define	SYSTEMCALL_GETTERMINALINPUTBUFFER  213
#define	SYSTEMCALL_SETTERMINALINPUTBUFFER  214
#define	SYSTEMCALL_GETTERMINALWINDOW       215
#define	SYSTEMCALL_SETTERMINALWINDOW       216
#define	SYSTEMCALL_GETTERMINALRECT         217
#define	SYSTEMCALL_SETTERMINALRECT         218
#define	SYSTEMCALL_DESTROYTERMINAL         219

//Reboot.
#define	SYSTEMCALL_REBOOT2  220

//program support.
#define	SYSTEMCALL_EXECUTEPROGRAM  221  //execute program.
#define	SYSTEMCALL_222             222  
#define	SYSTEMCALL_223  223
#define	SYSTEMCALL_224  224
#define	SYSTEMCALL_225  225

//Critical section. (kernel semaphore)
//Um semáforo do kernel para uso geral.
#define	SYSTEMCALL_GET_KERNELSEMAPHORE    226
#define	SYSTEMCALL_CLOSE_KERNELSEMAPHORE  227
#define	SYSTEMCALL_OPEN_KERNELSEMAPHORE   228

//debug stuff
#define	SYSTEMCALL_KERNELDEBUG  229

//230-239 (Boot support)
//logon logoff support.
#define	SYSTEMCALL_STARTLOGON     230
#define	SYSTEMCALL_STARTLOGOFF    231
#define	SYSTEMCALL_232            232
#define	SYSTEMCALL_233            233
#define	SYSTEMCALL_234            234
#define	SYSTEMCALL_235            235
#define	SYSTEMCALL_236            236
#define	SYSTEMCALL_237            237
#define	SYSTEMCALL_238            238
#define	SYSTEMCALL_SETBOOTOPTIONS 239


//240-249 Reservar próximos para gerenciamento de cursor e ponteiros.
#define	SYSTEMCALL_GETCURSORX  240
#define	SYSTEMCALL_GETCURSORY  241
#define	SYSTEMCALL_242         242
#define	SYSTEMCALL_243         243
#define	SYSTEMCALL_244         244
#define	SYSTEMCALL_245         245
#define	SYSTEMCALL_246         246
#define	SYSTEMCALL_247         247
#define	SYSTEMCALL_248         248
#define	SYSTEMCALL_249         249


//(250 ~ 255) Info support, get info.
//Ou últimos oferecem informações sobre o sistema.
#define	SYSTEMCALL_250                      250 
#define	SYSTEMCALL_251                      251
#define	SYSTEMCALL_252                      252
#define	SYSTEMCALL_253                      253
#define	SYSTEMCALL_SHOW_PCI_INFORMATION     254
#define	SYSTEMCALL_SHOW_KERNEL_INFORMATION  255


//
// Process and threads priorities.
//

/*
 * Constantes para níveis de prioridade.
 * Se um processo quiser alterar a prioridade de outro processo.
 * Qualquer processo pode obter sua prioridade e analizar através 
 * dessas definições.
 */
 
//Definições principais. 
#define PRIORITY_LOW4      1  //4
#define PRIORITY_LOW3      2  //3
#define PRIORITY_LOW2      3  //2
#define PRIORITY_LOW1      4  //1 
#define PRIORITY_NORMAL    5  //*0 (Normal).
#define PRIORITY_HIGH1     6  //1
#define PRIORITY_HIGH2     7  //2
#define PRIORITY_HIGH3     8  //3
#define PRIORITY_HIGH4     9  //4
//Definições secundárias.
#define PRIORITY_LOW        PRIORITY_LOW1
#define PRIORITY_SUPERLOW   PRIORITY_LOW4
#define PRIORITY_MIN        PRIORITY_SUPERLOW
#define PRIORITY_HIGH       PRIORITY_HIGH1 
#define PRIORITY_SUPERHIGH  PRIORITY_HIGH4
#define PRIORITY_MAX        PRIORITY_SUPERHIGH    
//Definição especial.
#define PRIORITY_REALTIME  10    



 
 
//cinza para pintar janela
//a janela tem camadas que vai do mais escuro para o mais claro.
#define xCOLOR_BLACK 0x00000000  //preto
#define xCOLOR_GRAY1 0x20202000  //cinza mais escuro
#define xCOLOR_GRAY2 0x40404000  //cinza
#define xCOLOR_GRAY3 0x60606000  //cinza
#define xCOLOR_GRAY4 0x80808000  //cinza
#define xCOLOR_GRAY5 0xa0a0a000  //cinza
#define xCOLOR_GRAY6 0xc0c0c000  //cinza
#define xCOLOR_GRAY7 0xe0e0e000  //cinza mais clarinho
#define xCOLOR_WHITE 0xffffff00  //branco 


//WIN23
//TRÊS TIPOS DE CINZA.
#define COLOR_LITBUTTON  0xE0E0E000
#define COLOR_LTGRAY     0xC0C0C000
#define COLOR_GRAY       0x80808000

//CORES BÁSICAS.
#define rgbBlack   0x00000000
#define rgbBlue    0x0000FF00
#define rgbCyan    0x00FFFF00
#define rgbGreen   0x00FF0000
#define rgbMagenta 0xFF00FF00
#define rgbRed     0xFF000000
#define rgbYellow  0xFFFF0000
#define rgbWhite   0xFFFFFF00



//windows2k system colors
#define COLOR_TEST_0  0x8080FF00  // COLOR_BACKGROUND(verde claro) ??
#define COLOR_TEST_1  0x80FFFF00  // COLOR_APPWORKSPACE, MDIWINDOW 
#define COLOR_TEST_2  0x80FF8000  // COLOR_WINDOW, CLIENT
#define COLOR_TEST_3  0x80FF0000  // COLOR_WINDOWTEXT, CLIENTTEXT 
#define COLOR_TEST_4  0xFFFF8000  // COLOR_MENU, MENUBAR
#define COLOR_TEST_5  0xFF800000  // COLOR_MENUTEXT (laranjado+-)
#define COLOR_TEST_6  0xC080FF00  // COLOR_ACTIVECAPTION, MYCAPTION
#define COLOR_TEST_7  0xFF80FF00  // COLOR_INACTIVECAPTION, CAPTION2
#define COLOR_TEST_8  0x0000FF00  // COLOR_CAPTIONTEXT, CAPTIONTEXT(azul)highlight
#define COLOR_TEST_9  0x00FFFF00  // COLOR_ACTIVEBORDER, BORDER
#define COLOR_TEST_10 0x00FF8000  // COLOR_INACTIVEBORDER, BORDER2
#define COLOR_TEST_11 0x40FF0000  // COLOR_WINDOWFRAME
#define COLOR_TEST_12 0xFFFF0000  // COLOR_SCROLLBAR (amarelo)
#define COLOR_TEST_13 0xC0800000  // COLOR_BTNFACE
#define COLOR_TEST_14 0xC0808000  // COLOR_BTNSHADOW (vinho)
#define COLOR_TEST_15 0xFF00FF00  // COLOR_BTNTEXT (rosa)
#define COLOR_TEST_16 0x40408000  // COLOR_HIGHLIGHT ~ COLOR_GRAYTEXT (azul escuro)
#define COLOR_TEST_17 0x4080FF00  // COLOR_HIGHLIGHT
#define COLOR_TEST_18 0x00FF0000  // COLOR_HIGHLIGHTTEXT (verde)
#define COLOR_TEST_19 0x80800000  // COLOR_INACTIVECAPTIONTEXT
#define COLOR_TEST_20 0x80400000  // COLOR_BTNHIGHLIGHT
#define COLOR_TEST_21 0xFF808000 
#define COLOR_TEST_22 0x40008000 
#define COLOR_TEST_23 0x8000FF00
#define COLOR_TEST_24 0x00008000  //COLOR_HIGHLIGHT ~ hot track (azul)
#define COLOR_TEST_25 0x0080FF00 
#define COLOR_TEST_26 0x00800000 
#define COLOR_TEST_27 0x40800000 
#define COLOR_TEST_28 0xFF000000  //red
#define COLOR_TEST_29 0xA0000000 
#define COLOR_TEST_30 0x80008000 
#define COLOR_TEST_31 0xFF008000
#define COLOR_TEST_32 0x00004000
#define COLOR_TEST_33 0x00408000 
#define COLOR_TEST_34 0x00400000 
#define COLOR_TEST_35 0x40400000 
#define COLOR_TEST_36 0x80000000 
#define COLOR_TEST_37 0x40000000 
#define COLOR_TEST_38 0x40004000
#define COLOR_TEST_39 0x80004000
#define COLOR_TEST_40 0x00000000 //COLOR_BTNSHADOW ~ preto text
#define COLOR_TEST_41 0x00808000  //vrde escuro
#define COLOR_TEST_42 0x40808000  //vrde escuro
#define COLOR_TEST_43 0x80808000  //COLOR_APPWORKSPACE (cinza)
#define COLOR_TEST_44 0x80804000 
#define COLOR_TEST_45 0xC0C0C000  //silver
#define COLOR_TEST_46 0x40004000
 
 
//outros teste
#define COLOR_TEST_47 0x3366FF00  //azul claro
    

/*
 * Cores usadas nessa sistema.
 */

#define COLOR_BLACK               0x00000000
#define COLOR_WHITE               0xFFFFFF00 
#define COLOR_RED                 0xFF000000 
#define COLOR_GREEN               0x00FF0000
#define COLOR_BLUE                0x0000FF00
#define COLOR_DARKRED             0x8B000000
#define COLOR_DARKGREEN           0x00640000
#define COLOR_DARKBLUE            0x00008B00
//#define COLOR_GRAY                0x80808000
#define COLOR_GREY                0xAFAFAF00
#define COLOR_LIGHTGRAY           0xD3D3D300
#define COLOR_LIGHTGREEN          0x90EE9000
#define COLOR_LIGHTBLUE           0xADD8E600
#define COLOR_SILVER              0xC0C0C000

//window colors
#define COLOR_ACTIVEBORDER        0xB4B4B400
#define COLOR_ACTIVECAPTION       0x99B4D100
#define COLOR_ACTIVECAPTIONTEXT   0x00000000
#define COLOR_APPWORKSPACE        COLOR_SILVER 
// A cor padrão para o Bg é azul quase escuro,
// o azul escuro é usado em seleção de item.
#define COLOR_BACKGROUND          0x00808000  
#define COLOR_BORDER              COLOR_SILVER 
#define COLOR_BUTTONFACE          0xF0F0F000
#define COLOR_BUTTONHIGHLIGHT     0xFFFFFF00
#define COLOR_BUTTONSHADOW        0xA0A0A000  //COLOR_BLACK
#define COLOR_BUTTONTEXT          COLOR_WINDOWTEXT
#define COLOR_CONTROL             0xF0F0F000
#define COLOR_CONTROLDARK         0xA0A0A000
#define COLOR_CONTROLDARKDARK     0x69696900
#define COLOR_CONTROLLIGHT        0xE3E3E300
#define COLOR_CONTROLLIGHTLIGHT   0xFFFFFF00
#define COLOR_CONTROLTEXT         0x00000000
#define COLOR_DESKTOP             0x00000000
#define COLOR_FOCUS_TOPBAR        0x7FFF0000
#define COLOR_GRAYTEXT            0x80808000
#define COLOR_HIGHLIGHT           0x3399FF00
#define COLOR_HIGHLIGHTTEXT       0xFFFFFF00
#define COLOR_INACTIVEBORDER      0xF4F7FC00
#define COLOR_INACTIVECAPTION     0xBFCDDB00
#define COLOR_INACTIVECAPTIONTEXT 0x434E5400
#define COLOR_INFO                0xFFFFE100
#define COLOR_INFOTEXT            0x00000000

#define COLOR_MENU                  COLOR_GRAY
#define COLOR_MENUTEXT              COLOR_BLACK
#define COLOR_MENUITEM              COLOR_WHITE
#define COLOR_MENUITEMTEXT          COLOR_BLACK
#define COLOR_MENUITEM_SELECTED     COLOR_BLUE
#define COLOR_MENUITEMTEXT_SELECTED COLOR_WHITE
#define COLOR_MENUBAR               COLOR_GRAY
#define COLOR_MENUHIGHLIGHT         0x3399FF00

#define COLOR_NAVIGATIONBAR       COLOR_BLACK
#define COLOR_NAVIGATIONBAR_TEXT  COLOR_WHITE
#define COLOR_STATUSBAR           COLOR_WINDOW
#define COLOR_TASKBAR             COLOR_WINDOW
#define COLOR_TASKBAR_TEXT        COLOR_TEXT
#define COLOR_TEXT                0x00000000
#define COLOR_TITLEBAR            COLOR_BLUE
#define COLOR_TITLEBAR_TEXT       COLOR_WHITE
#define COLOR_TOPBAR              0x83F52C00
#define COLOR_TOPBAR_TEXT         0x397D0200
#define COLOR_WINDOW              0xFFFFFF00
#define COLOR_WINDOWFRAME         COLOR_GRAY
//(debug: Pink para contraste com quaquer cor de janela)
#define COLOR_WINDOWTEXT          COLOR_PINK //COLOR_BLACK 
#define COLOR_WORKSPACE           0x0000FF00 //area de trabalho

//Tipos de azul
#define COLOR_BLUE1 0x067AB500
#define COLOR_BLUE2CYAN   0x1BA1E200
#define COLOR_BLUE3COBALT 0x0050EF00
#define COLOR_BLUE4INDIGO 0x6A00FF00

/*
 *  Lista de cores de 32 bit usando Alpha.
 */

#define COLOR_ALICEBLUE           0xF0F8FFFF
#define COLOR_ANTIQUEWHITE        0xFAEBD7FF
#define COLOR_AQUA                0x00FFFFFF
#define COLOR_AQUAMARINE          0x7FFFD4FF
#define COLOR_AZURE               0xF0FFFFFF
#define COLOR_BEIGE               0xF5F5DCFF
#define COLOR_BISQUE              0xFFE4C4FF
#define COLOR_BLANCHEDALMOND      0xFFEBCDFF
#define COLOR_BLUEVIOLET          0x8A2BE2FF
#define COLOR_BROWN               0xA52A2AFF
#define COLOR_BURLYWOOD           0xDEB887FF
#define COLOR_CADETBLUE           0x5F9EA0FF
#define COLOR_CHARTREUSE          0x7FFF00FF
#define COLOR_CHOCOLATE           0xD2691EFF
#define COLOR_CORAL               0xFF7F50FF
#define COLOR_CORNFLOWERBLUE      0x6495EDFF
#define COLOR_CORNSILK            0xFFF8DCFF
#define COLOR_CRIMSON             0xDC143CFF
#define COLOR_CYAN                0x00FFFFFF
#define COLOR_DARKCYAN            0x008B8BFF
#define COLOR_DARKGOLDENROD       0xB8860BFF
#define COLOR_DARKGRAY            0xA9A9A9FF
#define COLOR_DARKKHAKI           0xBDB76BFF
#define COLOR_DARKMAGENTA         0x8B008BFF
#define COLOR_DARKOLIVEGREEN      0x556B2FFF
#define COLOR_DARKORANGE          0xFF8C00FF
#define COLOR_DARKORCHID          0x9932CCFF
#define COLOR_DARKSALMON          0xE9967AFF
#define COLOR_DARKSEAGREEN        0x8FBC8BFF
#define COLOR_DARKSLATEBLUE       0x483D8BFF
#define COLOR_DARKSLATEGRAY       0x2F4F4FFF
#define COLOR_DARKTURQUOISE       0x00CED1FF
#define COLOR_DARKVIOLET          0x9400D3FF
#define COLOR_DEEPPINK            0xFF1493FF
#define COLOR_DEEPSKYBLUE         0x00BFFFFF
#define COLOR_DIMGRAY             0x696969FF
#define COLOR_DODGERBLUE          0x1E90FFFF
#define COLOR_FIREBRICK           0xB22222FF
#define COLOR_FLORALWHITE         0xFFFAF0FF
#define COLOR_FORESTGREEN         0x228B22FF
#define COLOR_FUCHSIA             0xFF00FFFF
#define COLOR_GAINSBORO           0xDCDCDCFF
#define COLOR_GHOSTWHITE          0xF8F8FFFF
#define COLOR_GOLD                0xFFD700FF
#define COLOR_GOLDENROD           0xDAA520FF
#define COLOR_GRADIENTACTIVECAPTION   0xB9D1EAFF
#define COLOR_GRADIENTINACTIVECAPTION 0xD7E4F2FF
#define COLOR_GREENYELLOW         0xADFF2FFF
#define COLOR_HONEYDEW            0xF0FFF0FF
#define COLOR_HOTPINK             0xFF69B4FF
#define COLOR_HOTTRACK            0x0066CCFF
#define COLOR_INDIANRED           0xCD5C5CFF
#define COLOR_INDIGO              0x4B0082FF
#define COLOR_IVORY               0xFFFFF0FF
#define COLOR_KHAKI               0xF0E68CFF
#define COLOR_LAVENDER            0xE6E6FAFF
#define COLOR_LAVENDERBLUSH       0xFFF0F5FF
#define COLOR_LAWNGREEN           0x7CFC00FF
#define COLOR_LEMONCHIFFON        0xFFFACDFF
#define COLOR_LIGHTCORAL          0xF08080FF
#define COLOR_LIGHTCYAN           0xE0FFFFFF
#define COLOR_LIGHTGOLDENRODYELLOW 0xFAFAD2FF
#define COLOR_LIGHTPINK           0xFFB6C1FF
#define COLOR_LIGHTSALMON         0xFFA07AFF
#define COLOR_LIGHTSEAGREEN       0x20B2AAFF
#define COLOR_LIGHTSKYBLUE        0x87CEFAFF
#define COLOR_LIGHTSLATEGRAY      0x778899FF
#define COLOR_LIGHTSTEELBLUE      0xB0C4DEFF
#define COLOR_LIGHTYELLOW         0xFFFFE0FF
#define COLOR_LIME                0x00FF00FF
#define COLOR_LIMEGREEN           0x32CD32FF
#define COLOR_LINEN               0xFAF0E6FF
#define COLOR_MAGENTA             0xFF00FFFF
#define COLOR_MAROON              0x800000FF
#define COLOR_MEDIUMAQUAMARINE    0x66CDAAFF
#define COLOR_MEDIUMBLUE          0x0000CDFF
#define COLOR_MEDIUMORCHID        0xBA55D3FF
#define COLOR_MEDIUMPURPLE        0x9370DBFF
#define COLOR_MEDIUMSEAGREEN      0x3CB371FF
#define COLOR_MEDIUMSLATEBLUE     0x7B68EEFF
#define COLOR_MEDIUMSPRINGGREEN   0x00FA9AFF
#define COLOR_MEDIUMTURQUOISE     0x48D1CCFF
#define COLOR_MEDIUMVIOLETRED     0xC71585FF
#define COLOR_MIDNIGHTBLUE        0x191970FF
#define COLOR_MINTCREAM           0xF5FFFAFF
#define COLOR_MISTYROSE           0xFFE4E1FF
#define COLOR_MOCCASIN            0xFFE4B5FF
#define COLOR_NAVAJOWHITE         0xFFDEADFF
#define COLOR_NAVY                0x000080FF
#define COLOR_OLDLACE             0xFDF5E6FF
#define COLOR_OLIVE               0x808000FF
#define COLOR_OLIVEDRAB           0x6B8E23FF
#define COLOR_ORANGE              0xFFA500FF
#define COLOR_ORANGERED           0xFF4500FF
#define COLOR_ORCHID              0xDA70D6FF
#define COLOR_PALEGOLDENROD       0xEEE8AAFF
#define COLOR_PALEGREEN           0x98FB98FF
#define COLOR_PALETURQUOISE       0xAFEEEEFF
#define COLOR_PALEVIOLETRED       0xDB7093FF
#define COLOR_PAPAYAWHIP          0xFFEFD5FF
#define COLOR_PEACHPUFF           0xFFDAB9FF
#define COLOR_PERU                0xCD853FFF
#define COLOR_PINK                0xFFC0CBFF
#define COLOR_PLUM                0xDDA0DDFF
#define COLOR_POWDERBLUE          0xB0E0E6FF
#define COLOR_PURPLE              0x800080FF
#define COLOR_ROSYBROWN           0xBC8F8FFF
#define COLOR_ROYALBLUE           0x4169E1FF
#define COLOR_SADDLEBROWN         0x8B4513FF
#define COLOR_SALMON              0xFA8072FF
#define COLOR_SANDYBROWN          0xF4A460FF
#define COLOR_SCROLLBAR           0xC8C8C8FF
#define COLOR_SEAGREEN            0x2E8B57FF
#define COLOR_SEASHELL            0xFFF5EEFF
#define COLOR_SIENNA              0xA0522DFF
#define COLOR_SKYBLUE             0x87CEEBFF
#define COLOR_SLATEBLUE           0x6A5ACDFF
#define COLOR_SLATEGRAY           0x708090FF
#define COLOR_SNOW                0xFFFAFAFF
#define COLOR_SPRINGGREEN         0x00FF7FFF
#define COLOR_STEELBLUE           0x4682B4FF
#define COLOR_TAN                 0xD2B48CFF
#define COLOR_TEAL                0x008080FF
#define COLOR_THISTLE             0xD8BFD8FF
#define COLOR_TOMATO              0xFF6347FF
#define COLOR_TRANSPARENT         0xFFFFFF00
#define COLOR_TURQUOISE           0x40E0D0FF
#define COLOR_VIOLET              0xEE82EEFF
#define COLOR_WHEAT               0xF5DEB3FF
#define COLOR_WHITESMOKE          0xF5F5F5FF
#define COLOR_YELLOW              0xFFFF00FF
#define COLOR_YELLOWGREEN         0x9ACD32FF
#define STEALTH_ORANGE            0xFF880000
#define STEALTH_OLIVE             0x66660000
#define STEALTH_GREEN             0x33DD1100
#define STEALTH_PINK              0xFF22EE00
#define STEALTH_BLUE              0x0077BB00
 
 
/*
 * (w) Colors, futuristic GUI. (Dark blu and Black)
 */ 
//#define COLOR_DARKBLUE   0x00008B00 
//#define COLOR_BLACK      0x00000000 
 
 
 
#define COLOR_KERNEL_BACKGROUND COLOR_BLUE     



//
// Linha e coluna.
//

//Suporte para linha e coluna.
#define COL_MAX      800  //1024,640, provisório.
#define LINHA_MAX    600  //768,480, provisório. 
//...


//
// Client Area support.
//

//Suporte para a área de cliente.
#define CLIENT_X_START   0
#define CLIENT_X_END     800    //640.
#define CLIENT_Y_START   40
#define CLIENT_Y_END     508    //420.
//...


//
// Message Box support.
//

//bg
#define MB_X              100
#define MB_Y              100
#define MB_LARGURA        200
#define MB_ALTURA         90
//title
#define MB_TITULO_X       (MB_X + 2 )
#define MB_TITULO_Y       (MB_Y + 2 )
#define MB_TITULO_LARGURA  (200 - 4)
#define MB_TITULO_ALTURA   30
//client
#define MB_CLIENT_X       (MB_X + 2)              
#define MB_CLIENT_Y       (MB_Y + MB_TITULO_ALTURA + 2)
#define MB_CLIENT_LARGURA ( MB_LARGURA - 4 )
#define MB_CLIENT_ALTURA  ( MB_ALTURA - MB_TITULO_ALTURA - 2)
//string       
#define MB_STRING_X       110  
#define MB_STRING_Y       110


//
// Title Bar support.
//

#define TB_X           0
#define TB_Y           0
#define TB_LARGURA     800    //1024,640.
#define TB_ALTURA      40
#define TB_STRING_X    10  
#define TB_STRING_Y    5


//
// Char support.
//

//Suporte para caracteres.
#define CHAR_WIDTH   8
#define CHAR_HEIGHT  8
//...

//
// Bars support.
//

#define	BAR_STEPS   46


//
// Video memory support.
//

//Suporte para memória de vídeo.
#define MEM_BASE 0x000A0000  //VGA.
//...

//
// Linhas e colunas.
//

//Suporte ao gerenciamento de linhas e colunas.
#define LINE    1024    //640.
//...


//
// Window Style support.
//

//Suporte ao estilo de janela.
#define WS_SIMPLES       1
#define WS_POPUP         2
#define WS_BUTTON_DOWN   3
#define WS_BUTTON_UP     4
//Continua...


//
// Task Bar support.
//

//Suporte a barra de tarefas.
#define BARRA_DE_TAREFAS_X        0
#define BARRA_DE_TAREFAS_Y        560    //748,460.
#define BARRA_DE_TAREFAS_LARGURA  800    //1024,640.
#define BARRA_DE_TAREFAS_ALTURA   20
#define AREA_DE_TAREFAS_X  MENU_INICIAR_LARGURA
#define AREA_DE_TAREFAS_Y  548    
#define AREA_DE_TAREFAS_LARGURA  (BARRA_DE_TAREFAS_LARGURA - MENU_INICIAR_LARGURA)
#define AREA_DE_TAREFAS_ALTURA   20



//
// Desktops support.
//

//
// Suporte à desktop:
// Obs: Uma user session contém uma window station, uma window station
// contém um desktop e um desktop contém janelas.
// 
//Dimensões da tela.
#define DESKTOP_X        0
#define DESKTOP_Y        0
#define DESKTOP_LARGURA    800    //1024,640.
#define DESKTOP_ALTURA     600    //768,480.


//
// Menu support.
//

//Suporte geral à menus.
#define MENU_X  0
#define MENU_Y  600    //768          //460 
#define MENU_LARGURA  200
#define MENU_ALTURA   200
#define MENU_INICIAR_X  0
#define MENU_INICIAR_Y  600    //748    //460
#define MENU_INICIAR_LARGURA  60
#define MENU_INICIAR_ALTURA   20
#define menu_size  (MENU_ALTURA * 8)


//
// task Bar support.
//

//Suporte à barra de tarefas.
#define TASKBUTTONS_BASE 40      //Botão.
#define CLOCK_BASE  (800-40)    //Relógio.   
//...


//
// Disk sectors support.
//

//Suporte à diso.
#define INIT_SECTOR 20    //??
//...

//
// Floppy Disk Controller support.
//
//Floppy disk support. (@todo:).
#define DOR1  0x3F2    /* Digital Output Register */
#define DOR2  0x372  
#define MSR1  0x3F4    /* Main Status Register */
#define MSR2  0x374  
#define DR1   0x3F5    /* Data Register */
#define DR2   0x375
#define DIR1  0x3F7    /* Digital Input Register */
#define DIR2  0x377
#define CCR1  0x3F7    /* Configuration Contorol Register */
#define CCR2  0x377
#define DOR   DOR1
#define DSR   MSR1


//
// Keyboard LEDs support.
//

#define LED_SCROLLLOCK  1
#define LED_NUMLOCK     2
#define LED_CAPSLOCK    4  


//
// Virtual Keys support.
//


//ASCII
#define KEY_RETURN   13     //sc 28
#define KEY_TAB	     15
#define KEY_SHIFT	 42     //16
#define KEY_CONTROL	 29     //17
#define KEY_CTRL	 29     //17
#define KEY_MENU	 56     //18
#define KEY_ALT  	 56     //18
#define KEY_CAPITAL	 20     //58
#define KEY_SPACE	 57     //32
#define KEY_WINKEY	 91   
#define KEY_DELETE   127    //sc 83
#define KEY_F1  0x80
#define KEY_F2  (KEY_F1 + 1)
#define KEY_F3  (KEY_F2 + 1)
#define KEY_F4  (KEY_F3 + 1)
#define KEY_F5  (KEY_F4 + 1)
#define KEY_F6  (KEY_F5 + 1)
#define KEY_F7  (KEY_F6 + 1)
#define KEY_F8  (KEY_F7 + 1)
#define KEY_F9  (KEY_F8 + 1)
#define KEY_F10 (KEY_F9 + 1)
#define KEY_F11 (KEY_F10 + 1)
#define KEY_F12 (KEY_F11 + 1)
//Mouse
#define KEY_MOUSEBUTTON1   5000
#define KEY_MOUSEBUTTON2   5000
#define KEY_MOUSEBUTTON3   5000


//****

//
// Teclas virtuais.
#define VK_LBUTTON	0x01
#define VK_RBUTTON	0x02
#define VK_CANCEL	0x03
#define VK_POWER    0x03  //??
#define VK_MBUTTON	0x04
#define VK_XBUTTON1	0x05
#define VK_XBUTTON2	0x06
#define VK_CLEAR	0x0C  //12
#define VK_BACK	    0x0E  //14  //8
#define VK_TAB      0x0F  //15  //9
#define VK_KANA	    0x15
#define VK_HANGEUL  0x15
#define VK_HANGUL	0x15
#define VK_JUNJA	0x17
#define VK_FINAL	0x18
#define VK_HANJA	0x19
#define VK_KANJI	0x19
#define VK_ACENTO_AGUDO 0x1A  //26 //0xb4 abnt	
#define VK_ACENTO_GRAVE 0x1A  //26  //0x60	abnt
#define VK_ESCAPE   0x1B  //27 
#define VK_RETURN   0x1C  //28  //13    //Return.
#define VK_CONVERT	0x1C  //??
#define VK_CONTROL     0x1D  //29
#define VK_CTRL        0x1D  //29   
#define VK_LCONTROL	   0x1D  //0xA2
#define VK_NONCONVERT  0x1D  //??
#define VK_ACCEPT      0x1E
#define VK_MODECHANGE  0x1F
#define VK_ACENTO_TIL  0x28  //40 //0x7e	abnt
#define VK_LSHIFT	   0x2A  //0xA0 
#define VK_PRINT	   0x2A  //42 ??
#define VK_EXECUTE	   0x2B  //43
#define VK_SNAPSHOT    0x2C  //44
#define VK_VIRGULA     0x33       //51 abnt
#define VK_PONTO       0x34       //52 abnt
#define VK_PONTOVIRGULA  0x35  //53 abnt
#define VK_RSHIFT	   0x36  //54  //0xA1
#define VK_ALT         0x38  //56   
#define VK_LMENU	   0x38  //56   //Não mudar.
#define VK_MENU        0x38  //56 
#define VK_RMENU	   0x38  //56   //@todo:Mudar esse
#define VK_ALTGR       0x38  //56 abnt //100 //56
#define VK_SPACE       0x39  //57  //Space.
#define VK_CAPITAL	   0x3A  //58  //20  
#define VK_F1	0x3B  //59    // No DOS é 0x170.  
#define VK_F2	0x3C  //60 
#define VK_F3	0x3D  //61 
#define VK_F4	0x3E  //62 
#define VK_F5	0x3F  //63 
#define VK_F6	0x40  //64 
#define VK_F7	0x41  //65 
#define VK_F8	0x42  //66 
#define VK_F9	0x43  //67 
#define VK_F10	0x44  //68
#define VK_NUMLOCK  0x45  //69 //0x90
#define VK_SCROLL	0x46  //70 //0x91
#define VK_HOME	  0x47  //71          
#define VK_END	  0x4F  //79
#define VK_DELETE_TECLADONUMERICO 0x53  //83  
#define VK_F11	  0x57  //87 
#define VK_F12	  0x58  //88    
#define VK_LWIN	  0x5B
#define VK_WINKEY 0x5B  //91    
#define VK_RWIN	  0x5C
#define VK_APPS	  0x5D
#define VK_CONTROL_MENU 0x5D  //93
#define VK_ACENTO_CIRCUNFLEXO 0x5E  //abnt	
#define VK_SLEEP     0x5F
#define VK_NUMPAD0	 0x60
#define VK_NUMPAD1	 0x61
#define VK_NUMPAD2	 0x62
#define VK_NUMPAD3	 0x63
#define VK_NUMPAD4	 0x64
#define VK_BREAK     0x65  //101
#define VK_NUMPAD5	 0x65
#define VK_FIND      0x66  //102
#define VK_NUMPAD6	 0x66
#define VK_UP	     0x67  //103 //72 
#define VK_NUMPAD7	 0x67  //??
#define VK_PRIOR     0x68  //104 //33 (prior).
#define VK_NUMPAD8	 0x68  //??
#define VK_LEFT	     0x69  //105 //75 
#define VK_NUMPAD9   0x69  //??
#define VK_RIGHT     0x6A  //106 //77	
#define VK_MULTIPLY  0x6A  //??
#define VK_SELECT	 0x6B  //107 //41
#define VK_ADD       0x6B  //??
#define VK_DOWN	     0x6C  //108 //80
#define VK_SEPARATOR 0x6C  //??
#define VK_NEXT	     0x6D  //109 //34
#define VK_SUBTRACT  0x6D  //??
#define VK_INSERT	 0x6E  //110 //45
#define VK_DECIMAL	 0x6E  //??
#define VK_REMOVE    0x6F  //111
#define VK_DIVIDE	 0x6F  //??
#define VK_HELP	     0x73  //115 //47
#define VK_PAUSE  0x77  //119 //19 
#define VK_F13	0x7C
#define VK_F14	0x7D
#define VK_F15	0x7E
#define VK_F16	0x7F
#define VK_DELETE  0x7F  //127 (delete)
#define VK_F17	0x80
#define VK_F18	0x81
#define VK_F19	0x82
#define VK_F20	0x83
#define VK_F21	0x84
#define VK_F22	0x85
#define VK_F23	0x86
#define VK_F24  0x87
#define VK_RCONTROL         0xA3  //0x1D  //0xA3
#define VK_BROWSER_BACK     0xA6
#define VK_BROWSER_FORWARD  0xA7
#define VK_ACENTO_TREMA     0xA8  //abnt
#define VK_BROWSER_REFRESH  0xA8  //??
#define VK_BROWSER_STOP	    0xA9
#define VK_BROWSER_SEARCH   0xAA
#define VK_BROWSER_FAVORITES  0xAB
#define VK_BROWSER_HOME	0xAC
#define VK_VOLUME_MUTE	0xAD
#define VK_VOLUME_DOWN	0xAE
#define VK_VOLUME_UP	0xAF
#define VK_MEDIA_NEXT_TRACK	 0xB0
#define VK_MEDIA_PREV_TRACK  0xB1
#define VK_MEDIA_STOP  0xB2
#define VK_MEDIA_PLAY_PAUSE	0xB3
#define VK_LAUNCH_MAIL  0xB4
#define VK_LAUNCH_MEDIA_SELECT  0xB5
#define VK_LAUNCH_APP1	0xB6
#define VK_LAUNCH_APP2  0xB7
#define VK_OEM_1	  0xBA
#define VK_OEM_PLUS	  0xBB
#define VK_OEM_COMMA  0xBC
#define VK_OEM_MINUS  0xBD
#define VK_OEM_PERIOD 0xBE
#define VK_OEM_2	  0xBF
#define VK_OEM_3	  0xC0
#define VK_OEM_4	  0xDB
#define VK_OEM_5	  0xDC
#define VK_OEM_6	  0xDD
#define VK_OEM_7	  0xDE
#define VK_OEM_8	  0xDF
#define VK_OEM_102	  0xE2
#define VK_PROCESSKEY 0xE5
#define VK_PACKET	  0xE7
#define VK_ATTN	      0xF6
#define VK_CRSEL	  0xF7
#define VK_EXSEL	  0xF8
#define VK_EREOF	  0xF9
#define VK_PLAY	      0xFA
#define VK_ZOOM	      0xFB
#define VK_NONAME	  0xFC
#define VK_PA1	      0xFD
#define VK_OEM_CLEAR  0xFE
//#define VK_
//#define VK_
//#define VK_
//#define VK_


//****


/*
 * Messages.
 *     Lista de mensagens suportadas pelo sistema.
 *     ...
 */
 
//window (0-19) 
#define MSG_NULL          0  //@todo: Criar pequeno comentário descritivo.  
#define MSG_CREATE        1  //...
#define MSG_DESTROY       2
#define MSG_MOVE          3 
#define MSG_SIZE          4
#define MSG_RESIZE        5
//#define MSG_OPEN        6
#define MSG_CLOSE         7
#define MSG_PAINT         8
#define MSG_SETFOCUS      9
#define MSG_KILLFOCUS     10
#define MSG_ACTIVATE      11
#define MSG_SHOWWINDOW    12 
#define MSG_SETCURSOR     13
//keyboard (20-29)
#define MSG_KEYDOWN       20
#define MSG_KEYUP         21
#define MSG_SYSKEYDOWN    22
#define MSG_SYSKEYUP      23
//mouse (30 - 39)
#define MSG_MOUSEKEYDOWN  30
#define MSG_MOUSEKEYUP    31
//outros (40 - ...)
#define MSG_COMMAND       40

#define MSG_CUT           41
#define MSG_COPY          42
#define MSG_PASTE         43
#define MSG_CLEAR         44 
#define MSG_UNDO          45
#define MSG_INSERT        46
#define MSG_RUN_PROCESS   47
#define MSG_RUN_THREAD    48
// Continua ...
// Muitas outras mensagens podem ser criadas,
// A variável é do tipo int.
//...

 
/*
 * Window Type - Tipos de janela.
 */
#define WT_NULL          0 
#define WT_SIMPLE        1
#define WT_EDITBOX       2 // igual simples, mais uma bordinha preta.
#define WT_OVERLAPPED    3 //sobreposta(completa)(barra de titulo + borda +client area)
#define WT_POPUP         4 //um tipo especial de sobreposta,  //usada em dialog ou message box. (com ou sem barra de titulo ou borda)					   
#define WT_BUTTON_DOWN   5 //rever
#define WT_BUTTON_UP     6 //rever
//...

//apresentação.
#define VIEW_NULL      0
#define VIEW_FULL      1000
#define VIEW_MAXIMIZED 1001
#define VIEW_MINIMIZED 1002
//...

//botões
#define BN_CLICKED  200
#define BN_DOWN     1
#define BN_UP       2
#define BN_SELECTED 3
//...


//
// Application support.
//


/*
 * ApplicationInfo_d:
 *     Informações básicas sobre uma applicação.
 *     Talvez o nome poderia ser ApplicationHook. 
 */
typedef struct ApplicationInfo_d ApplicationInfo_t;
struct ApplicationInfo_d
{
    int pid;	   //Process Id.
    char *name;    //Name.
    //...
};
ApplicationInfo_t *ApplicationInfo;
// 


/*
 * buffer_info_d:
 *     Informações básicas sobre um buffer.
 */
typedef struct buffer_info_d buffer_info_t;
struct buffer_info_d
{    
    unsigned long address;
	//...
};
buffer_info_t *BufferInfo;
//

  
//
// Estruturas para recursos gráficos:
//     Aqui deve ficar apenas as estruturas básicas que o cliente    
// pode acessar através da API. Haverá uma biblioteca exclusivamente 
// para recursos gráficos. Obs: Não pode haver conflito quando o
// cliente incluir a API e a biblioteca de recursos grpaficos.
//
  
  
//Client area info.  
typedef struct client_area_info_d client_area_info_t;  
struct client_area_info_d 
{    
	struct window_d *window;
    struct rect_d *rect;
    int dummy;
};
client_area_info_t *ClientAreaInfo;
//


//Cursor info.
typedef struct cursor_info_d cursor_info_t; 
struct cursor_info_d 
{    
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
    unsigned long image_address;  //x.cur
	//...
};
cursor_info_t *CursorInfo; 
//


//
// rectangle support.
//
 
typedef struct rect_d rect_t;
struct rect_d 
{
    unsigned long x;
    unsigned long y;
    unsigned long cx;
    unsigned long cy;	
};
rect_t *rect;
//


//
// Window support.
//


/*
 * window_d:
 *     Window Structure.
 *     @todo: *Deve ficar igual a do kernel.
 *     Obs: Não sei se essa estrutura pode ser pública.
 *
 * Histórico:
 *     2015 - Created.
 *     Oct 2016 - Revision.
 *     ...
 */
typedef struct window_d window_t;
struct window_d
{	
    //
    // Identificadores.
    //
    
	//@todo: Crir isso no começo de todas as estruturas.
	//object_type_t object_type = ObjectTypeWindow;
	
    unsigned long id;              //Window Id. 
	char *name;                    //Window name.
	
	//Segurança.
	//int used;
	//int magic;
	
	
	//
	// Window Class support.
	//
	
	//@todo: Criar essa estrutura.
	//struct window_class_d *windowClass;
	
	unsigned long type;                    //tipo ... (editbox, normal, ...)  style???
    unsigned long procedure;               //procedimento da janela
    struct window_procedure_d *wProcedure; //procedure struct
	//unsigned long Icon;
	//unsigned long Cursor;    //@todo: Criar cursorx e cursory.
	//unsigned long CursorX;
	//unsigned long CursorY;
	//unsigned long Background;
	//int instance; //???	
	
	
    //
	// Características dessa janela..
	//

	int active;    //Se é a janela ativa ou não.
	int focus;     //Se tem o foco de entrada ou não.
    int view;      //Estado: (Full,Maximized,Minimized...)	
	unsigned long status;  //?? @todo: Deletar..

    unsigned long x;           //deslocamento x
    unsigned long y;           //deslocamento y 
    unsigned long left;        //margem esquerda 
    unsigned long top;         //margem superior
    unsigned long right;       //margem direita  
    unsigned long bottom;      //margem inferior       
    unsigned long width;       //largura
    unsigned long height;      //altura
    unsigned long color_bg;    //cor    

	//?? Se mudar para Rect pode deletar alguns elementos acima
	//como x, y, width ...
	struct rect_d *rcWindow;

	// Bars support.
	// Cada tipo de janela tem seus itens específicos.
	// Esses são os status dos ítens. Se eles estão presentes ou não.
	
	int titlebarUsed;
    int menubarUsed; 
	int toolbarUsed;
	int statusbarUsed;
	int scrollbarUsed;
	//Continua.
	
	
	//
	// Buffers support.
	//

	// Buffer.
	// DedicatedBuffer
	// DedicatedBuffer --> LFB.
	// Endereço de memória onde a janela foi pintada.
	// Obs: Toda janela deve ter seu próprio buffer de pintura para poder 
	// passar a janela direto de seu próprio buffer para o LFB, sem passar 
	// pelo Backbuffer.
	void *buffer;        //Qual buffer dedicado a janela usa.
	void *BackBuffer;    //Qual backbuffer a janela usa.
	void *FrontBuffer;   //Qual frontbuffer a janela usa. (LFB).
    //... 	

	
	//
	// Parent support
	//
    unsigned long parentid;           //(Número da janela mãe).
	struct window_d *parent;	  //Parent window.	
	
	//
	// Child support.
	//
	
	//Lista encadeada de janelas filhas.
	struct window_d *childListHead;
    int childCount;    //Tamanho da lista.
	
	//
	// Client window support.
	//
    
	//Client window.( A área de cliente pode ter uma moldura na forma de janela.)
	struct window_d *client_window;   	
	//O retângulo de input e output para cliente.
	struct rect_d *rcClient;     // Client, usar '.'
		
	
	
	//
	// Desktop support.
	//
	
	int desktop_id;    //desnecessário.	
	struct desktop_d *desktop;
   
	
	//
	// Menus support.
	//
	
	//?? Qual janela.
	struct window_d *menu_window;   //Menu Window.
	
	struct menu_d *sysMenu;         //menu de sistema.(control menu)
	struct menu_d *barMenu;         //menu da barra de menu.
	struct menu_d *defaultMenu;     //menu da janela (*importante)
	//...

	//
	// @todo: Deletar isso. ??	
    // Texto para o caso da janela ser um item de menu.	
    //
	int selected;     //seleção  de item de menu.
    const char *text; //@todo usar unsigned char.
	

    //
    // Ações.
    //
   
    int redraw; 
    int draw;     //Repintar a janela.
    //...
 	
	
	//
	// Aqui em baixo deve ficar os elementos referenciados com pouca 
	// frequência.
	//
	
	//
	// Trava.
	//
	
	//Enables or disables mouse and keyboard input to the specified window 
	//or control.
    //Se travada, não pode mudar nada.	
	int locked;    

	
	//linked list. ( a linked list da janela)
	struct linkedlist_d *linkedlist;

	
	// Navegation.
	struct window_d *prev;     
	struct window_d *next;     //Next window.	
};
window_t *CurrentWindow;
//window_t *Window;
// As principais janelas usadas pelos utilitários
// dos subsistemas em user mode podem ser definidas aqui.
//...


/*
 * semaphore_d:
 *     Estrutura para criação de um semáforo.        
 *
 *     Pode-se criar vários semáforos. Cada semáforo é usado para
 * controlar o fluxo em um determinado recurso.
 *  Obs: Aqui em user mode talvez não precise criar a estrtutura inteira somente o handle.
 */ 
typedef struct semaphore_d semaphore_descriptor_t;
struct semaphore_d 
{
	//object_type_t objectType;   //@todo: criar esses enum
	//object_class_t objectClass; //@todo: criar esses enum
    
    //call back. @todo: Create.
	//unsigned long callback; //d
	
	//Identificadores do semáforo.   	
	int id;         //c
	int used;       //b
	int magic;      //a
	int taskId;    	//g, A tarefa que esta usando o dispositivo. 
	
	//Estado do semáforo. (verde, vermelho)
	int color;          //G
	int status;         //F Flag.
	unsigned int count; //>=0   //E
   
    //...
	
    struct d_wait_queue *sema_wait;   //ext1    	
	//...	
};
semaphore_descriptor_t *current_semaphore; 
//...


//
// Principais chamadas ao sistema.
//

 
/*
 * apiSystem: 
 *     Interpreta um comando e envia uma systemcall para o Kernel.
 *
 * Obs: Há comandos predefinidos, porém um comando pode ser o nome
 * abreviado de um programa ou uma variável de ambiante representando
 * um diretório.
 *
 * Argumento:
 *     String de comando.
 *
 * Retorno:
 *     ?? 
 */
int apiSystem(const char *command);


/*
 * system_call: 
 *     Interrupção de sistema, número 200, pode chamar vários serviços do 
 * Kernel com a mesma interrupção. O número do serviço é passado via 
 * argumento.
 *     Essa é a chamada mais simples.
 *
 * Argumentos:
 *    eax = arg1, o Número do serviço.
 *    ebx = arg2. 
 *    ecx = arg3.
 *    edx = arg4.
 */
void *system_call( unsigned long ax, 
                   unsigned long bx, 
				   unsigned long cx, 
				   unsigned long dx );
				   
//
// As chamadas system1 à system15 poderão ser revistas
// atribuindo a elas uma destinação mais importante.
//

//Print pixel.
int system1( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
			 
//Print horizontal line.
int system2( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
			 
//Ret�ngulo.
int system3( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
//Putch.
int system4( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
			 
//Print string.
int system5( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
			 
//Message box - Buffer. 
int system6( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
//
int system7( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
//
int system8( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
			 
//  Chama o procedimento da vez. - executa outro procedimento
int system9( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx );
			 
//
int system10( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx );
			  
//
int system11( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx );
//
int system12( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx );
//
int system13( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx );
//
int system14( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx );
//
int system15( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx );


			  
			  
/*
 * Outras chamadas.
 */

 
//int 200 - serviço 14.
int edit_box( unsigned long x,  
              unsigned long y, 
			  unsigned long height, 
			  unsigned long width ); 
 
//
// Messages support, (IPC).
// 

//int 200 - serviço 17.
int SetNextWindowProcedure(unsigned long next_procedure);
int chama_procedimento(unsigned long proximo_procedure);  //@todo: traduzir para inglês.
 
 
//Carrega bitmap 16x16.
void carrega_bitmap_16x16( unsigned long img_address, 
                           unsigned long x, 
						   unsigned long y );

//int 200 - serviço 241.
void apiInitBackground();

//Message Box.
void MessageBox(int type, char *string1, char *string2);


/*
 * call_kernel:
 *      Chama os serviços do Kernel.
 */
int call_kernel( unsigned long int_number, 
                 unsigned long service_number, 
                 unsigned long arg1, 
                 unsigned long arg2, 
                 unsigned long arg3, 
                 unsigned long arg4,
                 unsigned long arg5, 
                 unsigned long arg6, 
                 unsigned long arg7, 
                 unsigned long arg8,
                 unsigned long arg9, 
                 unsigned long arg10, 
                 unsigned long arg11, 
                 unsigned long arg12 );

				 
/*
 * call_gui:
 *     Chama os serviços de GUI.
 *     Chama os serviços da GUI que estão em Kernel Mode.
 */
int call_gui( unsigned long int_number, 
              unsigned long service_number, 
              unsigned long arg1, 
              unsigned long arg2, 
              unsigned long arg3, 
              unsigned long arg4,
              unsigned long arg5, 
              unsigned long arg6, 
              unsigned long arg7, 
              unsigned long arg8,
              unsigned long arg9, 
              unsigned long arg10, 
              unsigned long arg11, 
              unsigned long arg12 );
			  
	


//
// Window support.
//

					   
/*
 * APICreateWindow: 
 *     Cria uma janela com base em uma struct.
 *     Retorna o endereço da estrutura da janela criada. 
 *     Para que possa ser registrada na lista windowList[].
 *
 * Cria a janela dependendo do tipo:                              
 * =================================
 * 1 - POP-UP.
 * 2 - EDIT-BOX.
 * 3 - NORMAL ( bg + client area ).
 * 4 - NORMAL_EDIT ( bg + editbox).
 * 5 - MENUBAR.
 * 6 - TOOLBAR.
 * 7 - STATUSBAR.
 * 8 - TASKBAR.
 * 9 - ? 
 * CONTINUA ...
 */
void *APICreateWindow( unsigned long type,        //1-Tipo de janela, (popup,normal,...).
                       unsigned long status,      //2-Estado da janela, (ativa ou não).
                       unsigned long view,        //3-(min, max ...).
                       char *windowname,          //4-Título.                          
                       unsigned long x,           //5-Deslocamento em relação às margens do Desktop.                           
                       unsigned long y,           //6-Deslocamento em relação às margens do Desktop.
                       unsigned long width,       //7-Largura da janela.
                       unsigned long height,      //8-Altura da janela.
                       struct window_d *pWindow,  //9-Endereço da estrutura da janela mãe.
                       unsigned long onde,        //10-Ambiente.( Estão no desktop, barra, cliente ...)
                       unsigned long clientcolor, //11- Cor da área de cliente.
                       unsigned long color );     //12-Color (bg) (para janela simples).

					   
//Register Window.		
int APIRegisterWindow(struct window_d *window);

//Close Window.
int APICloseWindow(struct window_d *window);

//Set Focus.
int APISetFocus(struct window_d *window);
	
//Get Focus.
int APIGetFocus();

//Kill Focus.
int APIKillFocus(struct window_d *window);

//Set Active Window.
int APISetActiveWindow(struct window_d *window);

//Get Active Window.
int APIGetActiveWindow();

//Client area.
void *apiGetClientAreaRect();
void apiSetClientAreaRect(struct rect_d *r);


/*window support.*/
void APIresize_window(struct window_d *window, unsigned long x, unsigned long y);
void APIredraw_window(struct window_d *window);
void APIreplace_window(struct window_d *window, unsigned long x, unsigned long y);
void APImaximize_window(struct window_d *window);
void APIminimize_window(struct window_d *window);
void *APIget_foregroung_window();
void APIset_foregroung_window(struct window_d *window);
	
//
// Char support.
//	
	
//put char.
//@todo: Mudar argumento para *ch.
void put_char( unsigned long x,  
               unsigned long y,  
			   unsigned long color, 
			   unsigned char *ch );
	

//
// String support.
//

int api_strncmp(char *s1, char *s2, int len);

//int 200 - serviço 10.
void print_string( unsigned long x,  
                   unsigned long y,  
				   unsigned long color, 
				   unsigned char *string );
			  


//
// Buffer support.
//

//int 200 - serviços - 1,2,3,4,5,6,7,8,9.
void refresh_buffer(unsigned long n);



//
// Screen support.
//

//Refresh screen.
void api_refresh_screen();
void refresh_screen();

//int 200 - serviço 15. 
int vsync();


//
// Shutdown support.
//

//int 200 - serviço 220 - (shut down).
//@todo: Usar esse serviço pra desligar a máquina e não pra reboot.
void apiShutDown();

//
// Reboot support.
//

void apiReboot();

//
// Cursor support.
//

unsigned long apiGetCursorX();
unsigned long apiGetCursorY();
void apiSetCursor( unsigned long x, unsigned long y);


//
// Process support.
//

//Create process.
void *apiCreateProcess(unsigned long process_eip, unsigned long process_priority, char *name);

//Mostra informações sobre o processo atual.	
void APIShowCurrentProcessInfo();

//Torna zombie a thread atual.
//Obs: Um processo fecha quando fecha a thread principal.
//@todo: Isso não deveria fechar um processo.
void exit(int exit_code);	

//Destrói a thread atual.
void kill(int exit_code);	
	

//
// Thread support.
//

//Create thread.
void *apiCreateThread(unsigned long thread_eip, unsigned long thread_priority, char *name);
void apiStartThread(void *Thread); //coloca no estado standby para executar pela primeira vez

//
// File support.
//

//Open file.
void *apiFOpen(const char *filename, const char *mode);

//Operação down em um semáforo indicado no argumento.
void apiDown(struct semaphore_d *s);

//Operação up em um semáforo indicado no argumento.
void apiUp(struct semaphore_d *s);



//Critical section support.
void enterCriticalSection();         //P (Proberen) testar.
void exitCriticalSection();          //V (Verhogen)incrementar.
void initializeCriticalSection();    //Inicializa em 1

//Paint support.
void apiBeginPaint();
void apiEndPaint();

void apiPutChar( int c );

/*
int getpid();
*/



//
//...
//

//
// End.
//

