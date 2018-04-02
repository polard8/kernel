/*
 * File: fs\format.c
 *
 * Descrição:
 *     Seviços de formatação de disco e volumes.
 *     Formata a tabela de partições no mbr.
 *     Altera valores no mbr e metafile. 
 *
 * @todo:
 *     Serviços de formatação podem ir para um aplicativo.
 * Histórico:
 *    Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *    Versão 1.0: 2016 - Revisão.
 *    ...
 */
 

#include <kernel.h>


//@todo: mudar o nome da função para fs_clear_fat.
void fs_apaga_fat()
{
    fs_init_fat();
    return;
};


void fs_delete_entry(unsigned long id, unsigned long eid){
    return;
};


/*
 * limpa_root: 
 *
 * Atribuições:
 *     +Salvar o o conteúdo da memória no hd.
 *     +Zerar o buffer na memória ram.
 *     Continua...
 *
 * @todo: 
 *     Mudar o nome da função para fsClearRoot.
 */
void limpa_root()
{
    int i;	
	unsigned char *root = (unsigned char *) FAT16_ROOTDIR_ADDRESS;

    
	/*
     * @todo: 
	 *     O endereço do rootdir deveria estar definido em uma
	 * variável global. Por enquanto esse endereço é constante.
	 */	
    
	/*
     * Tamanho do rootdir.
     *
     * @todo: 
	 *     O tamanho do rootdir deveria estar definido em uma
	 * variável global. Por enquanto o tamanho é constante.
	 */
	i = 0;
     
	 
	
	/*
	 * Limpando o rootdir. (32 setores.) 512 entradas de 32bytes. 
     */
	while(i < (32*512)){
        root[i] = (unsigned char) 0;    
        ++i;
    };
     
    /*
	 * Salva o root dir. (size?)    
     */
	//write_lba(FAT16_ROOTDIR_ADDRESS, FAT16_ROOTDIR_LBA);
     
    return;
};


/*
 * fsClearFat:
 *      Zera o buffer e grava zeros no hd.
 */
void fsClearFat()
{
	int i;
    unsigned char *fat_base = (unsigned char *) FAT16_FAT_ADDRESS;
	
	/*
     * @todo: 
	 *     O endereço da fat deveria estar definido em uma
	 * variável global. Por enquanto esse endereço é improviso.
	 */    
    
	/*
     * Tamanho da fat.
     *
     * @todo: 
	 *     O tamanho da fat deveria estar definido em uma
	 * variável global. 
	 */	
    i = (int) (512*4);
	
	while(i > 0){
        fat_base[i] = 0;    
        i--;
    }; 

    //Salva  FAT ! 
	write_lba(FAT16_FAT_ADDRESS, FAT16_FAT_LBA);

	
    //@todo: Usar while.      
   
done:   
	return;
};

//
// End.
//

