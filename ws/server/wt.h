
#ifndef ____WT_H
#define ____WT_H    1


// 
// == Window Types ==
//

#define WT_NULL          0 
#define WT_SIMPLE        1
// igual simples, mais uma bordinha preta.
#define WT_EDITBOX       2
// sobreposta(completa)(barra de titulo + borda +client area)  
#define WT_OVERLAPPED    3  
// um tipo especial de sobreposta,
//usada em dialog ou message box. (com ou sem barra de titulo ou borda)
#define WT_POPUP         4  
#define WT_CHECKBOX      5  // Caixa de seleção. Caixa de verificação. Quadradinho.
#define WT_SCROLLBAR     6  // Cria uma scroll bar. Para ser usada como janela filha.
#define WT_EDITBOX_MULTIPLE_LINES 7
#define WT_BUTTON     8   
#define WT_STATUSBAR  9
#define WT_ICON       10

//#define WT_MAX (WT_ICON+1)

#endif    



