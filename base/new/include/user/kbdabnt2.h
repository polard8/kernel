/*
 * File: kbdabnt2.h 
 *     Header de suporte ao teclado abnt2.
 */

#ifndef ____KBDABNT2_H
#define ____KBDABNT2_H    1


//Usado no mapa de caracteres. 
#define L      0x01    // locking function.
#define SHF    0x02    // keyboard shift.
#define ALT    0x04    // alternate shift -- alternate chars.
#define NUM    0x08    // numeric shift  cursors vs. numeric.
#define CTL    0x10    // control shift  -- allows ctl function.
#define CPS    0x20    // caps shift -- swaps case of letter.
#define ASCII  0x40    // ascii code for this key.
#define STP    0x80    // stop output.


//ASCII

//A disciplina de linhas precisa disso.
#define KEY_RETURN   28   //13 //sc 28 #bugbug tem que ser 28
#define KEY_TAB      15
#define KEY_SHIFT    42   //16
#define KEY_CONTROL  29   //17
#define KEY_CTRL     29   //17
#define KEY_MENU     56   //18
#define KEY_ALT      56   //18
#define KEY_CAPITAL  20   //58
#define KEY_SPACE    57   //32
#define KEY_WINKEY   91   
#define KEY_DELETE   127  //sc 83



#define KEY_F1   0x80
#define KEY_F2   (KEY_F1  + 1)
#define KEY_F3   (KEY_F2  + 1)
#define KEY_F4   (KEY_F3  + 1)
#define KEY_F5   (KEY_F4  + 1)
#define KEY_F6   (KEY_F5  + 1)
#define KEY_F7   (KEY_F6  + 1)
#define KEY_F8   (KEY_F7  + 1)
#define KEY_F9   (KEY_F8  + 1)
#define KEY_F10  (KEY_F9  + 1)
#define KEY_F11  (KEY_F10 + 1)
#define KEY_F12  (KEY_F11 + 1)


/* Cursor keys. */
/*
#define KINS   0x90
#define KDEL    (KINS + 1)
#define KHOME   (KDEL + 1)
#define KEND   (KHOME + 1)
#define KPGUP   (KEND + 1)
#define KPGDN  (KPGUP + 1)
#define KLEFT  (KPGDN + 1)
#define KUP    (KLEFT + 1)
#define KDOWN    (KUP + 1)
#define KRIGHT (KDOWN + 1)
*/



//Mouse
#define KEY_MOUSEBUTTON1   5000
#define KEY_MOUSEBUTTON2   5000
#define KEY_MOUSEBUTTON3   5000



#endif   


