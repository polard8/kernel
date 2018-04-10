/*
 * File: diskmap.h 
 *
 * Descrição:
 *     Disk map support header.
 *     
 * *IMPORTANTE:
 *      Esse arquivo mapeia os componentes do subsystema System4Nora no disco.
 *      O System4Nora é composto de 4 partes e por enquanto ocupa os 32KB iniciais 
 *      do disco.
 *
 *  Stage1 = setor 1. (MBR).
 *  Stage2 = Setor 2.
 *  //...
 * 
 * 
 * Versão 1.0, 2015.
 */
 
 
//?? @todo: Rever
#define System4NoraSize 32    //32 KB. 
#define Stage1StartSector 1 
#define Stage2StartSector 2
#define Stage2Size 31 
 
 
int zica;


//
//fim.
//

