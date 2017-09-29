/*
 * File: keyboard.h 
 *
 * Descrição:
 *     Header do driver de teclado presente dentro do kernel. 
 *     Manter aqui parâmetros gerais, que possam ser úteis pra qualquer 
 * driver de teclado.
 *     Coisas como estrutura para identificação do modele, nome do driver,
 *      pathname do driver.
 *
 * Ambiente:
 *     Kernel mode (Ring 0).
 *
 * Ports:
 * =====
 *  060-06F  = 8042 Keyboard Controller (AT, PS/2).
 *	060      = 8042 Keyboard input/output buffer register.
 *	061      = 8042 system control port (for compatability with 8255).
 *	064      = 8042 Keyboard command/status register.
 *
 *
 * Keyboard Controller Commands:
 * =============================
 * Commands are sent to the keyboard controller by writing to port 0x64.  
 * Command parameters are written to port 0x60 after teh command is sent.  
 * Results are returned on port 0x60.  Always test the 
 * OBF ("Output Buffer Full") 
 * flag before writing commands or parameters to the 8042.
 *
 * 0x20 (Read Command Byte) - Returns command byte.  (See "Write Command Byte" below).
 * 0x60 (Write Command Byte) - Stores parameter as command byte.  
 * Command byte defined as follows:
 *
 * More ...
 *
 * ?0x90-0x9F (Write to output port) - Writes command's lower nibble to 
 * lower nibble of output port (see Output Port definition.)
 * ?0xA1 (Get version number) - Returns firmware version number.
 * ?0xA4 (Get password) - Returns 0xFA if password exists; otherwise, 0xF1.
 * ?0xA5 (Set password) - Set the new password by sending a null-terminated 
 * string of scan codes as this command's parameter.
 * ?0xA6 (Check password) - Compares keyboard input with current password.
 * 0xA7 (Disable mouse interface) - PS/2 mode only.  
 * Similar to "Disable keyboard interface" (0xAD) command.
 * 0xA8 (Enable mouse interface) - PS/2 mode only.  
 * Similar to "Enable keyboard interface" (0xAE) command. 
 * 0xA9 (Mouse interface test) - Returns 0x00 if okay, 0x01 if Clock line 
 * stuck low, 0x02 if clock line stuck high, 0x03 if data line stuck low, 
 * and 0x04 if data line stuck high.
 * 0xAA (Controller self-test) - Returns 0x55 if okay.
 * 0xAB (Keyboard interface test) - Returns 0x00 if okay, 
 * 0x01 if Clock line stuck low, 0x02 if clock line stuck high, 0x03 if data 
 * line stuck low, and 0x04 if data line stuck high.
 * 0xAD (Disable keyboard interface) - Sets bit 4 of command byte and disables all 
 * communication with keyboard.
 * 0xAE (Enable keyboard interface) - Clears bit 4 of command byte and re-enables 
 * communication with keyboard.
 * 0xAF (Get version)
 * 0xC0 (Read input port) - Returns values on input port (see Input Port definition.)
 * 0xC1 (Copy input port LSn) - PS/2 mode only. 
 * Copy input port's low nibble to Status register (see Input Port definition)
 * 0xC2 (Copy input port MSn) - PS/2 mode only. 
 * Copy input port's high nibble to Status register (see Input Port definition.)
 * 0xD0 (Read output port) - Returns values on output port (see Output Port definition.) 
 * 0xD1 (Write output port) - Write parameter to output port (see Output Port definition.)
 * 0xD2 (Write keyboard buffer) - Parameter written to input buffer as if 
 * received from keyboard.
 * 0xD3 (Write mouse buffer) - Parameter written to input buffer as if received from mouse.
 * 0xD4 (Write mouse Device) - Sends parameter to the auxillary PS/2 device.
 * 0xE0 (Read test port) - Returns values on test port (see Test Port definition.)
 * 0xF0-0xFF (Pulse output port) - Pulses command's lower nibble onto lower nibble 
 * of output port (see Output Port definition.)
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */ 
 
//variável de ambiente. 
#define KEYBOARD_DRIVER_PATHNAME "/root/drivers/keyboard.bin" 
//... 
 
// Keyboard LEDs
#define LED_SCROLLLOCK  1
#define LED_NUMLOCK     2
#define LED_CAPSLOCK    4
 
 
//Usado no mapa de caracteres. 
#define	L	   0x01	   // locking function.
#define	SHF	   0x02	   // keyboard shift.
#define	ALT	   0x04	   // alternate shift -- alternate chars.
#define	NUM	   0x08	   // numeric shift  cursors vs. numeric.
#define	CTL	   0x10	   // control shift  -- allows ctl function.
#define	CPS	   0x20	   // caps shift -- swaps case of letter.
#define	ASCII  0x40	   // ascii code for this key.
#define	STP	   0x80    // stop output.


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


//
// Virtual Key.
//

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
#define VK_ESCAPE      0x1B  //27 
#define VK_RETURN      0x1C  //28  //13    //Return.
#define VK_CONVERT	   0x1C  //??
#define VK_CONTROL     0x1D  //29
#define VK_CTRL        0x1D  //29   
#define VK_LCONTROL	   0x1D  //0xA2
#define VK_NONCONVERT  0x1D  //??
#define VK_ACCEPT      0x1E
#define VK_MODECHANGE  0x1F
#define VK_ACENTO_TIL  0x28  //40 //0x7e	abnt
#define VK_LSHIFT	   0x2A  //0xA0 
#define VK_PRINT	   0x54 //0x2A  //42 ?? print screen
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
#define VK_PAUSE  0x45 //0x77  //119 //19 
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


/*
Table 1.  Consumer Page audio controls supported in Windows 2000.
Usage	Usage Name	Usage Type
0xE0	Volume*	Linear Control (LC)
0xE2	Mute*	On/Off Control (OOC)
0xE3	Bass	Linear Control (LC)
0xE4	Treble	Linear Control (LC)
0xE5	Bass Boost*	On/Off Control (OOC)
0xE7	Loudness	On/Off Control (OOC)
0xE9	Volume Increment*	Re-trigger Control (RTC)
0xEA	Volume Decrement*	Re-trigger Control (RTC)
0x152	Bass Increment	Re-trigger Control (RTC)
0x153	Bass Decrement	Re-trigger Control (RTC)
0x154	Treble Increment	Re-trigger Control (RTC)
0x155	Treble Decrement	Re-trigger Control (RTC)
*/


// Enumerando os tipos de teclados.
typedef enum {
    KEYBOARD_VIRTUAL,
    KEYBOARD_PS2,
    KEYBOARD_USB,
    //...
}keyboard_type_t;

//
// @todo: estrutura de dispositivo:
//        nela tem informações sobre o driver.
//


//char keyboardString[] = "Generic keyboard";


/*
 * Keyboard global variables.
 */


//
// @todo: Sondando scancode. (provisório.)
//
int scStatus;


//
// Driver handler support.
//

unsigned long keyboard_handler_address;
 
//@todo: Variável que identifique o driver. seu nome e pathname.

//int KeyboardObjectNumber;
//char *keybaord_driver_name;
//char *keybaord_driver_pathname;


/*
* encapsulando em kernel.c
//status
unsigned long key_status;
unsigned long escape_status;
unsigned long tab_status;
unsigned long winkey_status;
unsigned long ctrl_status;
unsigned long alt_status;
unsigned long shift_status;
*/


unsigned long ambiente;
unsigned long destroy_window;
unsigned long quit_message;


/*
 * ABNT2 keyboard layout.
 *
 * KBDUS means US Keyboard Layout. 
 * This is a scancode table used to layout a standard US keyboard. 
 * I have left some comments in to give you an idea of what key is what,
 * even though I set it's array index to 0.
 * You can change that to whatever you want using a macro, if you wish!
 */


#define CHARMAP_SIZE  128


//
// Endereços de charmaps usados.
// Obs: Incluídos na estrutura.
//unsigned long normal_charmap_address;
//unsigned long shift_charmap_address;
//unsigned long control_charmap_address;

/*
 * NORMAL ABNT2.
 */
static unsigned char map_abnt2[CHARMAP_SIZE] = {
 0,      //Scancode 0.
 033,    //1  (Esc). (\e)
 '1',    //2
 '2',    //3
 '3',
 '4',
 '5',
 '6',
 '7',
 '8',      //9
 '9',      //10
 '0',      //11
 '-',      //12
 '=',      //13
 VK_BACK,  //14 BackSpace. (0xF7) delete
 VK_TAB,   //15 TAB.        (\t)
 'q',      //16 
 'w',      //17 (alt)
 'e',
 'r',
 't',
 'y',
 'u',
 'i',
 'o',
 'p',
 '´',          //26 (00b4 @) dead_acute dead_grave
 '[',          //27   bracketleft   braceleft
 VK_RETURN,    //28 Enter.
 VK_LCONTROL,  //29 ms right control. ??
 'a',          //30 (O a minúsculo é 30 em abnt 2).
 's',          //31.
 'd',          //32.
 'f',
 'g',
 'h',
 'j',
 'k',
 'l',    //38 
 'ç',    //39 00e7 ccedilla
 '~',    //40 dead_tilde	dead_circumflex
 '\'',    //41 (espaço) (')(") dead_acute dead_diaeresis 
 VK_LSHIFT,    //42 Shift.  
 ']',    //43 bracketright braceright asciitilde Control_bracketright 
 'z',    //44 
 'x',
 'c',
 'v',
 'b',
 'n',
 'm',  //50 
 ',',  //51 comma  less
 '.',  //52 period greater 
 ';',  //53  numlockdesligado=(;) numlockligado=(/).
 VK_RSHIFT,    //54 Right Shift.
 '*',          //55 NUM * (NUM lock??).(printscreen)
 VK_ALTGR,     //56 Alt. VK_ALTGR
 ' ',          //57 Space. VK_SPACE
 VK_CAPITAL,   //58 Caps Lock.
 VK_F1,        //59 F1.(abnt)
 VK_F2,        //60 F2.(abnt)
 VK_F3,        //61 F3.(abnt)
 VK_F4,        //62 F4.(abnt)
 VK_F5,        //63	F5  .(abnt)
 VK_F6,        //64 F6 .(abnt)
 VK_F7,        //65 F7.(abnt)
 VK_F8,        //66 F8.(abnt)
 VK_F9,        //67 F9.(abnt)
 VK_F10,       //68 F10.(abnt)
VK_PAUSE,     //VK_NUMLOCK,      //69 PAUSE. (num lock)
VK_SCROLL,     //70 Scroll Lock(abnt). break.
'7',    //71 (7). home
'8',    //72 (8). up
'9',    //73 (9). pgup
'-',    //74       
'4',    //75 left 
'5',    //76     
'6',    //77 right
'+',    //78
'1',	 //79  end  
'2',    //80 down
'3',    //81 pgdn (q).     
'0',    //82  Ins
VK_DELETE_TECLADONUMERICO,    //83 Num DEL (abnt).(´)(,)
VK_PRINT,    //84 PRINT SCREEN E sys req (abnt).
'.',    //85
'\\',    //86 (\).help backslash  bar
VK_F11,    //87 (F11)abnt.	 
VK_F12,    //88 (F12)abnt.
'/',    //89 slash question /?
VK_F14,    //90
VK_LWIN,    //91 Left Windows(abnt). (right WinKey) ([).
VK_RWIN,    //92 Right Windows(abnt).(left WinKey) (\).
VK_CONTROL_MENU,    //93 CONTROL MENU, Application(abnt). (]).
VK_F18,    //94
VK_F19,    //95
'`',//VK_RETURN,    //96 (0). (`)Acento grave.(enter)
VK_LCONTROL,    //97 (1) (a) Minúscula. control
'/',    //98 (2) (/) KP_Divide
VK_F23,    //99 (3) VoidSymbol  
VK_ALTGR,    //100 (4) AltGr
VK_BREAK,    //101 (5). 0xE9
VK_FIND,    //102 (6) (\).
VK_UP,    //103 (7).
VK_PRIOR,    //104 (8).
VK_LEFT,    //105 (9). 0xED
VK_RIGHT,    //106 *
VK_SELECT,    //107 +
VK_DOWN,  //108 RETURN.
VK_NEXT,     //109 -
VK_INSERT,       // 
VK_REMOVE,       //111 (/). 0xF3
VK_F1,   //112 (F1). MACRO
VK_F2,   //113 (F2) F13
VK_F3,   //114 (F3) F14
'/',   //115 (F4)(/). HELP
VK_F5,   //116 (F5) DO
VK_F6,   //117 (F6) F17
VK_F7,   //118 (F7) (esc) KP_MinPlus
VK_PAUSE,   //119 (F8) Pause 
VK_F9,   //120 (F9)
VK_F10,  //121 (F10)
VK_F11,  //122 (F11)
VK_F12,  //123 (F12)
0,       //124 F13(abnt) 
0,       //125 F14(abnt)
'~',     //126 VK_ACENTO_TIL(abnt). (.) F15 (abnt) 
0,	     //        F16 (abnt) Obs: Continua F... 
};


/*
 * SHIFT ABNT2.
 */
static unsigned char shift_abnt2[CHARMAP_SIZE] = {	
0, 
033, 
 '!',   //2 
 '@',   //3
 '#',   //4
 '$',   //5
 '%',   //6
 0xA8,   //7 (00a8 @) (trema)
 '&',   //8
 '*',   //9
 '(',   //10
 ')',   //11
 '_',   //12
 '+',   //13 
0177,
'\t',    //15 TAB
 'Q',    //16
 'W',    //17
 'E',    //18
 'R',    //19
 'T',    //20
 'Y',    //21
 'U',    //22
 'I',
 'O',    //24
 'P',    //25
 '`',    //26
 '{',    //27
KEY_RETURN,
CTL,
'A',    //30
'S',
'D',
'F',
'G',
'H',
'J',
'K',
'L',  //38
'Ç',  //39 (00c7)
'^',  //40
'"',  //41(")
SHF,
 '}',    //43 
'Z',     //44 
'X',
'C',
'V',
'B',
'N',
'M',  //50 
'<',  //51 
'>',  //52
':',  //53
SHF,  //54 
CTL,  //55
ALT,  //56
' ',  //57
CPS|L,    //58
0,      //59
0,      //60
' ',    //61
0,   //62
0,   //63
0,   //64
0,   //65
0,   //66
0,   //67
0,   //68
NUM|L,    //69
STP|L,    //70
'7',      //71
'8',    //72
'9',    //73
'-',    //74
'4',    //75
'5',    //76
'6',    //77
'+',    //78
'1',    //79
'2',    //80
'3',    //81
'0',    //82
',',    //83 (,)
0,      //84
0,      //85
'|',    //86 (|)
0,  //87
0,  //88
0,  //89
0,  //90
0,  //91
0,  //92
0,  //93
0,  //94
0,  //95
0,  //96
0,  //97
0,  //98
0,  //99
0,  //100
0,  //101
0,  //102
0,  //103
0,  //104
0,  //105
0,  //106
0,  //107
0,  //108
0,  //109
0,  //110
0,  //111
0,  //112
0,  //113
0,  //114
'?',  //115 (?)
0,  //116
0,  //117
0,  //118
0,  //119
0,    //120
0,    //121
0,    //122
0,    //123
0,    //124
0,    //125
'.',  //126 (.).
0,
};


/*
 * CONTROL ABNT2.
 */
static unsigned char ctl_abnt2[CHARMAP_SIZE] = {
0,     //0
033,   //1
'!',   //2
000,   //3
'#',   //4
'$',   //5
'%',   //6
036,   //7
'&',   //8
'*',   //9
'(',   //10
')',   //11
037,
'+',
034,
'\177',
021,
027,
005,
022,
024,
031,
025,
011,
017,
020,
033,
035,
'\r',
CTL,
001,
013,
004,
006,
007,
010,
012,
013,
014,
';',
'\'',
'`',
SHF,
034,
032,
030,
003,
026,
002,
016,
015,
'<',
'>',
'?',
SHF,
'*',
ALT,
' ',
CPS|L,
0,
0,
' ',
0,
0,
CPS|L,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
033,
'7',
'4',
'1',
0, 
NUM|L,
'8',
'5',
'2',
0,
STP|L,
'9',
'6',
'3',
'.',
0,
'*',
'-',
'+',
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
};



//
// structure for hardware keyboard info.
//

typedef struct keyboard_d keyboard_t;
struct keyboard_d
{
	object_type_t objectType;
	object_class_t objectClass;

	keyboard_type_t type;
	//...
	int dummy;
	//int VendorId;
	//...

    //unsigned long normal_charmap_address;
    //unsigned long shift_charmap_address;
    //unsigned long control_charmap_address;

	//unsigned long keyboard_handler_address;

};
//keyboard_t *Keyboard;


//
// Prototypes.
//

//Pega o status das teclas de modificação.
unsigned long keyboardGetKeyState( unsigned char key );

//@todo: função para mudar o handler.
//o kernel deve oferecer o serviço de trocar o handler
//de todo driver.


//Enable and disable keyboard.
void keyboardEnable();
void keyboardDisable();

/*
 * Prototypes for keyboard support.
 */

//Set flags.
void keyboard_set_leds(char flag); 
 
int get_alt_status();
int get_ctrl_status();

void abnt2_keyboard_handler();
void KeKeyboard();    //User Mode driver.
void KiKeyboard();    //Kernel Base driver.
void init_keyboard();

/*
 * Get window procedure parameters.
 */
void *KdGetWindowPointer(int tid); 
int KbGetMessage(int tid);
unsigned long KbGetLongParam1(int tid);
unsigned long KbGetLongParam2(int tid);


//input pega caracteres digitados.
unsigned long input(unsigned long ch);

/*
 * Reboot via Keyboard port.
 */
void reboot();

//
// End.
//
