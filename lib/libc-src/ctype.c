/*
 * File: ctype.c
 *
 * usado na lib c em user mode
 *
 * Descrição:
 *    Rotinas variadas em kernel mode.
 *
 * Versão 0.1 2018
 */


#include <types.h> 
#include <ctype.h>


//#if defined(LIBC_SCCS) && !defined(lint)
//static char sccsid[] = "@(#)ctype_.c	5.4 (Berkeley) 3/9/86";
//#endif LIBC_SCCS and not lint


char _ctype_[1 + 256] = {
    0,  //
	_C,	//0
	_C,	//1
	_C,	//2
	_C,	//3
	_C,	//4
	_C,	//5
	_C,	//6
	_C, //7
	_C,	//8
	_C | _S, // 9	\t
	_C | _S, //10	lf
	_C | _S, //11	
	_C | _S, //12	
	_C | _S, //13	cr
	_C, //14	
	_C, //15
	_C,	//16
	_C,	//17
	_C,	//18
	_C,	//19
	_C,	//20
	_C,	//21
	_C,	//22
	_C, //23
	_C,	//24
	_C,	//25
	_C,	//26
	_C,	//27
	_C,	//28
	_C,	//29
	_C,	//30
	_C, //31
	_S | _B, //32	(space)
	_P, //33 !	
	_P,	//34 "
	_P,	//35 #
	_P,	//36 $
	_P,	//37  
	_P,	//38 &
	_P, //39 '
	_P,	//40 (
	_P,	//41 )
	_P,	//42 *
	_P,	//43 +
	_P,	//44 ,
	_P,	//45 -
	_P,	//46 .
	_P, //47 /
	_D,	//48  0 (dígito) Número
	_D,	//49
	_D,	//50
	_D,	//51
	_D,	//52
	_D,	//53
	_D,	//54
	_D, //55 
	_D,	//56
	_D,	//57
	_P,	//58 :
	_P,	//59 ;
	_P,	//60 <
	_P,	//61 =
	_P,	//62 >
	_P, //63 ?
	_P,	//64 @
	_U | _X, //65 A  (maiúscula) (hexa)	
	_U | _X, //66   (maiúscula) (hexa)		
	_U | _X, //67   (maiúscula) (hexa)		
	_U | _X, //68   (maiúscula) (hexa)		
	_U | _X, //69   (maiúscula) (hexa)		
	_U | _X, //70   (maiúscula) (hexa)
	_U, // 71 maiúscula.
	_U,	// 72
	_U,	// 73
	_U,	// 74
	_U,	// 75
	_U,	// 76
	_U,	// 77
	_U,	// 78
	_U, // 79
	_U,	// 80
	_U,	// 81
	_U,	// 82
	_U,	// 83
	_U,	// 84
	_U,	// 85
	_U,	// 86
	_U, // 87
	_U,	// 88
	_U,	// 89
	_U,	// 90
	_P,	// 91 [
	_P,	// 92 \
	_P,	// 93 ]
	_P,	// 94 ^
	_P, // 95 _
	_P,	// 96 `
	_L | _X,  // 'a' minúscula heaxa	
	_L | _X,  //minúscula heaxa	
	_L | _X,  //minúscula heaxa	
	_L | _X,  //minúscula heaxa	
	_L | _X,  //minúscula heaxa	
	_L | _X,  //minúscula heaxa	
	_L, // 103 'g'
	_L,	// 104 
	_L,	// 105 
	_L,	// 106 
	_L,	// 107 
	_L,	// 108 
	_L,	// 109 
	_L,	// 110
	_L, // 111
	_L,	// 112
	_L,	// 113
	_L,	// 114
	_L,	// 115
	_L,	// 116
	_L,	// 117
	_L,	// 118
	_L, // 119
	_L,	// 120 
	_L,	// 121
	_L,	// 122 'z'
	_P,	// 123 '{'
	_P,	// 124 '|'
	_P,	// 125 '}'
	_P,	// 126 '~'
	_C, // DEL
    0, //128
    0, //129  
0, //130
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //140
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //150
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //160
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //170
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //180
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //190
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //200
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //210
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //220
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //230
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //240
0,
0,
0,
0,
0,
0,
0,
0,
0,
0, //250
0, //251
0, //252
0, //253
0, //254
0 //255
};


/*
unsigned char __tolower(unsigned char c) {
  if (isupper(c)) {
    c -= 'A' - 'a';
  }

  return c;
}

unsigned char __toupper(unsigned char c) {
  if (islower(c)) {
    c -= 'a' - 'A';
  }

  return c;
}
*/

/*
#bugbug: isso não funciona.
int isalnum(int c)
{
	return (int) __isalnum (c);
}
*/

int isalpha(int c)
{
	return (int) __isalpha(c);	
}

int iscntrl(int c)
{
	return (int) __iscntrl(c);		
}


int isdigit(int c)
{
	return (int) __isdigit(c);			
}


int isgraph(int c)
{
	return (int) __isgraph(c);	
}


int islower(int c)
{
	return (int) __islower(c);		
}


int isprint(int c)
{
	return (int) __isprint(c);			
}


int ispunct(int c)
{
	return (int) __ispunct(c);	
}


int isspace(int c)
{
	return (int) __isspace(c);		
}



int isupper(int c)
{
	return (int) __isupper(c);		
}



int isxdigit(int c)
{
	return (int) __isxdigit(c);		
}




//
// End.
//
