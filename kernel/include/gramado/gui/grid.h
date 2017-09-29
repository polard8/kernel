/*
 * Arquivo: grid.h
 *
 * Descrição:
 *     Header para grid da área de trabalho.
 *     Os grids de aplicativos serão resolvidos fora do kernel.
 *
 *     @todo: Esses grids devem ser mínimos em kernel mode.
 *
 * Versão 1.0, 2015.
 */
 
 
// 
// Armazena ponteiros de estrutura.
//

unsigned long screenGrid[128];   //@todo: Esses grids devem ser mínimos em kernel mode.


int initScreenGrid();
int drawScreenGrid();


//
//fim.
//
