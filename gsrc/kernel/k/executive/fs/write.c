/*
 * File: fs\write.c 
 *
 * Descrição: 
 *     Rotinas de gravação. em disco
 *
 * Obs:
 *    As rotinas na biblioteca C devem chamar essas funções.
 * Histórico:
 *    Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *    Versão 1.0: 2016 - Revisão.
 *    ...
 */
 
 
#include <kernel.h>


/*
 * fatWriteCluster:
 *     Salva um cluster no disco.
 *
 * Argumentos:
 *   setor ~ Primeiro setor do cluster.
 *   address ~ Endereço do primeiro setor do cluster.
 *   spc  ~ Número de setores por cluster.
 */
void fatWriteCluster(unsigned long sector, unsigned long address, unsigned long spc)
{
	unsigned long i;

	//Começa do primeiro setor do cluster.
	for(i = 0; i < spc; i++){
        write_lba( address, sector + i );
		address = address +512; 
	};
	return;
};


/*
 * write_lba:
 *     Grava um setor no disco dado o lba.
 *     fsWriteLba
 */
void write_lba( unsigned long address, unsigned long lba)
{    
    //@todo: Check limits.
	
    switch(fatbits)
    {
	    case 32:
	        //Nothing.	    
            return;
			break;		
			
	    case 16:
            my_write_hd_sector( address, lba, 0, 0); 
            return;
			break;		
			
	    case 12:
	        //Nothing.	    
            return;
			break;

        default:
		    return;
            break;		
	};	
	
done:
    return;
};


/*
 * fsSaveFile:
 *     Salva um arquivo.
 *     Por enquanto no diretório raiz.
 * @todo: A biblioteca C pode chamar essa funçao.
 */
unsigned long fsSaveFile( unsigned char *file_name, 
                          unsigned long file_size, 
						  unsigned long file_address )  
{
/*
    unsigned short *root = (unsigned short *) FAT16_ROOTDIR_ADDRESS;
    unsigned short *fat  = (unsigned short *) FAT16_FAT_ADDRESS;
	
    unsigned long i; //deslocamento procurando espaço livre
    unsigned long j; //deslocamento salvando cluster number
    unsigned long c; //Deslocamaento na fat ?
    unsigned long endereco;



    
	//@todo: Número máximo de entradas na lista de clusters. Quantas?
    unsigned long max = 128;  	
	//lista de clusters
	unsigned short list[max];
   

    endereco = file_address;
	
	
    //Carrega root e fat.
	fs_load_rootdirEx();
	fs_load_fatEx();
	
    
    j = 0;  //Deslocamento na lista, tem que ser zero.
    c = 0;  //Deslocamaento na fat ?
    i = 0;  //Contagem de entradas na fat. Começa do 32 e vai ate muito ...

   
    while(i < max)
    {
        //procurando cluster livre na fat.
        //@todo:isso poderia ser uma função.		
        if(fat[c] == 0)
        {
            //encontrado todos os espaços livres que o arquivo precisa.
            if(file_size == 0){
                list[j] = (unsigned short) 0xfff8; //marca o fim         
                goto save_file;
            };    
                  
            list[j] = (unsigned short) c; //salva um endereço livre  
             j++;   //incrementa a lisa

            file_size--; //decrementa o tamanho do arquivo!                  
        };
        
        c++; //incrementa o deslocamento na fat. 
        i++; //incrementa a quantidade de busca.
    }; 
  
fail:  
   printf("Max entries !");
   refresh_screen();
   while(1){}
   
  */ 
/*
 * Salva o arquivo.
 *     O arquivo tem na lista todos os clusters que ele precisa.
 */  

/* 
save_file:
             
    
    i = 0;        //incio da lista
    j = 512*4;

    
    unsigned short first;
    unsigned short next;
    unsigned short sector;
    
    first = list[i];
    
    
    //
    // salva no diretorio raiz o nome e o primeiro cluster
    //
    //corrige deslocamento.
   // salva_nome(file_name, first); 
    
    while(j)
    {            
         //pega um conteudo da lista.
        next = list[i];
        
        //salva a trilha indicada pela lista
       // salva_trilha( next, endereco);
        //save_file( 0, endereco, next, 8);
        
        
        //encontrada a assinatura na lista!
        if( next == 0xfff8)
        {
             next = list[i-1];
             fat[next] = 0xfff8;  
             goto done;         
        }
        //não é assinatura ainda
        else
        { 
            //-0x60 = é uma correção por causa valor do tipo (unsigned long)!!
            //grava na fat o endereço do proximo cluster
            fat[next] = list[i+1];
            
            //grava - aqui next esta certo!!!
            write_lba( endereco, next);
            
            endereco += 512; 
        }; 
         
         //proximo valor da lista
         i++; 
                  
         j--;
    };
    
   // MessageBox("nao encontra assinatura na lista!");
    fatseg3: goto fatseg3;

done:        
    //salva 2 setores da fat!       
    write_lba( FAT16_FAT_ADDRESS, FAT16_FAT_LBA);
    write_lba( FAT16_FAT_ADDRESS + 0x200, FAT16_FAT_LBA + 1);
     
	 */
    return 0;
};



/*
 * fs_save_rootdir:
 *     Salva o diretório raiz no disco.
 *     @todo: Identificar parâmetros do sistema de arquivos atual.
 */
void fs_save_rootdir()
{
	return;
};


/*
 * fs_save_dir:
 *     Salva um diretório.
 */
void fs_save_dir(unsigned long id)
{
	return;
};



/*
 * fs_save_entry_on_root:
 *     Salva uma entrada do diretório raiz, dada
 * a id da estrutura do arquivo.
 * @todo: Checa os parametros do sistema de arquivos e 
 * salva a entrada no diretorio raiz.
 */
void fs_save_entry_on_root(unsigned long eid)
{
    return;
};


void fs_save_structure()
{   
	return;
};

//
// End.
//
