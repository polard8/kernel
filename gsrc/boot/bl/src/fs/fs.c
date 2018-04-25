/*
 * File: fs\fs.c
 *
 * Descrição:
 *     Arquivo principal do sistema de arquivos usado no Boot Loader.
 *     
 * Sobre o sistema de arquivos:
 *    + HD IDE.
 *    + Partição 0. 
 *    
 *      Meus Discos:
 *    + FAT16, 8MB, cluster size = 512 bytes. (VHD)
 *    + FAT16, 255 heads, 63 spt, cylinder 243. (Pen Drive, Kingstone DT 2GB).
 *    + FAT16, 255 heads, 63 spt, cylinder 1946. (Pen Drive, SanDisk 16GB).
 *    + ...
 *
 *  Sobre o Boot Loader:   
 *      O propósito do Boot Loader é fazer inicializações, carregar o Kernel, 
 * alguns módulos, aplicativos a GUI. Depois passa o comando para o Kernel.
 *
 * Observação: 
 *     Os valores das estruturas podem ser salvos em um registro. No registro 
 * pode ter um registro das operações efetuadas no sistema de arquivo.
 *
 * Versão 1.0, 2015 - Created.
 * Versão 1.0, 2016 - Revision.
 */


#include <bootloader.h>


/*
 * fs_load_file:
 *     Carrega um arquivo na memória.
 * 
 */
/* 
int fs_load_file( unsigned char *file_name, unsigned long file_address ){    
	return (int) 0;    //Ainda não implementada.
}; 

*/


/*
 * fs_search_file:
 *    Procura por um nome de arquivo no diretório raiz.
 */
/*
int fs_search_file(unsigned char *file_name){
	return (int) 0;
};
*/


/*
/// Checks if the sector loaded in user_data is a Fat16 boot sector
unsigned short is_FAT16()
{
    char* label="FAT16";
    
	unsigned short res;
    res = memcmp( label, user_data+0x36, 5);  // Compares with label in FAT16 Boot
    if(res)
    {	
	    return 0;
    }		
	else
    {	
		return 1;
	}
};
*/


/*
 * fatClustToSect:
 *     Converte. ??
 */
unsigned long fatClustToSect( unsigned short cluster, 
                              unsigned long spc, 
							  unsigned long first_data_sector )
{
    unsigned long C = (unsigned long) cluster;
done:	
	return (unsigned long) ( ( C - 2 ) * spc) + first_data_sector;
};


/*
 * fatLoadCluster:
 *     Load a clusterfull of data
 */
void fatLoadCluster( unsigned long sector, 
                     unsigned long address, 
					 unsigned long spc )
{
	unsigned long i;

	// Começa do primeiro setor do cluster.
	for(i = 0; i < spc; i++){
        read_lba( address, sector + i );
		
		address = (unsigned long) address + SECTOR_SIZE;    //+512;
	};
	return;
};


/*
 * fs_format:
 *     Formata o diretório raiz.
 *
 * @todo: 
 *     Formatar uma partição.
 *     Deve ficar em aplicativo de formatação.
 *     Mudar para fsFormat();.
 */
void fs_format(){
	printf("fs_format:\n");
    return;	
};


/*
 * fs_search_empty_entry: 
 *     Encontrar uma entrada vazia em um dado diretório.
 *    
 */
unsigned long fs_search_empty_entry(unsigned long id){	
    return 0; 	
};


/*
 * fs_find_not_empty_entry:
 *     Procura entrada NÃO vazia na FAT.
 *     A entrada 0, sempre esta ocupada.
 */
unsigned long fs_find_not_empty_entry(){		
   return (unsigned long) 0;
};


/*
 *
 */
void fs_test_fat_vector(){
    return;
};


/*
 *
 */
unsigned long fs_get_fat_entry(unsigned long n){	
	return (unsigned long) 0;
};


/*
 * fs_create_entry:
 *     Cria uma entrada de diretório.
 *
 * Arguments:
 *     +Nome do arquivo.  
 *     +Id do diretório.
 *     +Id da entrada de diretório.
 *     +Número do cluster inicial na FAT.
 *     +Tamanho do arquivo.
 *
 */
void fs_create_entry( char *name,  
                      unsigned long id,
					  unsigned long eid,
					  unsigned long cluster,
					  unsigned long size )
{
    return;    //Nothing for now.
};


/*
 * fsCreateFileName:
 *     Cria um nome de arquivo.    
 */
void fsCreateFileName( char *name, unsigned long id,unsigned long eid){
    return;
};


/*
 * fsSaveFileName: 
 *     Salva um nome no diretório dado o cluster inicial.
 */
void fsSaveFileName( unsigned char *name, 
                 unsigned long id, 
				 unsigned long eid, 
				 unsigned long initial_cluster )
{        
	return;    //Nothing for now.
};


/*
 * fs_save_entry_on_disc:
 *     @todo: O buffer deve ser salvo no disco.
 */
void fs_save_entry_on_disc(unsigned long id, unsigned long eid){
	return;
};


/*
 *
 */
void fs_set_structures(){
   return;
};


/*
 *
 */
void fs_set_entry(unsigned long id, unsigned long eid){
    return;
};


/*
 *
 */
void fs_get_entry(unsigned long id, unsigned long eid){ 	
    return; 
};

  
/*
 *
 */
void fs_show_dir_entry(unsigned long id,unsigned long eid){
	return; 
};


/*
 *
 */
void fs_show_dir(unsigned long id){
    return; 
};


/*
 * fs_check_cluster:
 *     Confere os clusters de um diretório, procurando por falhas.
 *
 *     Objetivo: 
 *          Encontrar falha de diretório na hora 
 *          do carregamento dos arquivos do sistema.
 *
 *     Obs: Pertence ao Boot Loader.
 */
unsigned long fs_check_cluster(unsigned long id){
	return 0;    // Ainda não implementada.
};


/*
 * fsSaveRootDir:
 *     Salva o diretório raiz no disco.

 *     @todo: Desenvolver essa função.
 *
 *     Observações: 
 *
 *          O Boot Loader pode querer salvar o
 *          arquivo de log de inicialização ou
 *          modificar alguma configuração de inicialização
 *          no arquivo de configuração de inicialização,
 *          então salvará os arquivos no diretório e
 *          gravará o diretório no disco. 
 *
 *          Função importante para o processo
 *          de restauração da inicialização, pois
 *          o objetivo do Boot Loader é apenas
 *          carregar arquivos e não salvar arquivos.
 *          
 */
void fsSaveRootDir(){
	return;    //Ainda não implementada.
};


/*
 * fs_load_dir: 
 *     Carrega um diretório na memória.
 * 
 */
void fs_load_dir(unsigned long id){    
	return;    //Ainda não implementada.
};


/*
 * fs_save_dir:
 *     Grava um diretório no disco.
 *
 */
void fs_save_dir(unsigned long id){
	return;    //Ainda não implementada.
};


/*
 *
 */
void fs_save_structure(){   
	return;    //Ainda não implementada.
};


/*
 *  fs_save_entry_on_root:
 *      Salva uma entrada de diretório no diretório raiz,
 *      dado o número da entrada.
 *      @todo: bugug ? tem alguma incoerência aqui.
 */
void fs_save_entry_on_root(unsigned long eid)
{
	return;    //Ainda não implementada.
};


/*
 * fs_show_entry:
 *     Mostra os dados da entrada de diretório.
 */
void fs_show_entry(unsigned long id, unsigned long eid)
{    
	return;    //Ainda não implementada.
};


/*
 * fs_delete_entry:
 *     Deleta uma entrada.
 */
void fs_delete_entry(unsigned long id, unsigned long eid)
{
	return;    //Ainda não implementada.
};


/*
 *
 */
void fs_init_bootfile_struct()
{
	return;    //Ainda não implementada.
};


/*
 *
 */
unsigned long fs_get_entry_status(unsigned long id, unsigned long eid)
{
    return 0;    //Ainda não implementada.
};


/*
 *
 */
void fs_set_entry_status(unsigned long id, unsigned long eid, unsigned long status)
{
    return;    //Ainda não implementada.
};


/*
 * fs_makeboot:
 *     @todo: Reanalizar o propósito dessa rotina.
 */
unsigned long fs_makeboot(){   	
    return 0;    //Suspensa.
};


/*
 *
 */											 
void fs_set_fat_entry(unsigned long n, unsigned long value)
{
    return;
};


/*
 * fs_find_empty_entry:
 *
 */
unsigned short fs_find_empty_entry()
{
    return 0;
};


/*
 * fs_install:
 *     Instalador.
 *     @todo: Essa função deve ser usada em aplicativo.
 */
void fs_install(){
	return;   //@todo: Instala o bootmanager no disco.
};


/*
 * fs_relood_dir: 
 *     Recarrega na memória um diretório dado seu Id.
 */
void fs_relood_dir(unsigned long id){
	return;    //Ainda não implementada.   
};


//
// @todo: 
// ?? Mostrar área de memória.
//
int mostra(){ 
    return (int) 0;    //Suspensa.
};


/*
 *****************************************************************
 * fsLoadFile:
 *     Carrega um arquivo na memória. (#fat16)
 *     O Boot Loader utiliza essa rotina para carregar os arquivos 
 * do sistema.
 *
 * @todo:
 *     +A libC chama essa função atravez de open(...).
 *     +Mudar o tipo de retorno para 'int'.
 *     +...
 */
unsigned long fsLoadFile( unsigned char *name, unsigned long address )
{
	int Status;
	
	//Declara variáveis.
	unsigned long i = 0;
	unsigned long j = 0;
    unsigned short next;

    //Root support.
    unsigned short *root = (unsigned short *) FAT16_ROOTDIR_ADDRESS;
    unsigned long max = 512;    //Número máximo de entradas no root dir.
	unsigned long z = 0;        //Deslocamento no diretório raiz.
    unsigned long n = 0;        //Deslocamento no nome.
	char name_x[13];

	//FAT support.
    unsigned short *fat  = (unsigned short *) FAT16_FAT_ADDRESS;
	unsigned short cluster;   //Cluster inicial.


	//char name_buffer[32];

	//FILE f;
	//f = (void *) malloc( sizeof(FILE) );
	//if( (void*) f == NULL ){
		//fail.
	//};
	
	//#bugbug
	//Essa refresh screen leva muito tempo.

	//Debug
	printf("fsLoadFile: Loading %s\n", (const char*) name );
	refresh_screen();
	
//loadRoot:

    //#test: 
	// Suspendendo o carregamento do root.
	// Ele será previamente carregado em main().
	// Carrega o diretório raiz na memória.
	//fs_load_rootdirEx();
	
	
	if( g_fat16_root_status != 1 )
	{
        printf("fsLoadFile: Root Status \n");     
        return 1;	
	}
	
	
	//#debug 
	//printf("carregar_arquivo: Searching File=[%s]\n",file_name);		

	// Procura o arquivo no diretório raiz.
search_file:
	
	while(max > 0)
    {     
        if(root[z] != 0)
        {   
			//Copia o nome e termina com 0.
			memcpy( name_x, &root[z], 11);
			name_x[11] = 0;
			
            //Compara 11 caracteres.
			Status = (int) strncmp( name, name_x, 11 );
            if(Status == 0){
				cluster = (unsigned short) root[z +13];
                goto arquivo_encontrado;
			}; 
        };   
        z += 16;    // (32/2) próxima entrada!
        max--;      // 512 vezes!
    }; 

   //	
   // Se o arquivo não for encontrado.	
   //
   
arquivo_nao_encontrado:
    printf("fsLoadFile: File not found!\n");     
    return 1;

    //	
    // Se o arquivo for encontrado.    
    //
	
arquivo_encontrado:
    	 
    //Pega cluster inicial (word).
	//Limites: 16 entradas por setor, 32 setores de tamanho.
	//(0x1A/2) = 13.
	cluster = (unsigned short) root[z +13];   
	
	// Limits.
	if( cluster <= 0 || cluster > (0xFFF0) ){
	    printf("fsLoadFile fail: Cluster limits File=[%s] Cluster=[%d]\n",&root[z] ,cluster);
		goto fail;
	};
	
	
	
	//
	// Obs: root[z] é o início da entrada. Podemos pegar várias informações sobre
	// o arquivo. @todo: Precisamos alocar uma estrutura para salvarmos as informções
	// sobre o arquivo.
	//
	
//loadFAT:
	
	//#debug. 
	//printf("carregar_arquivo: Loading FAT ...\n");

	
    //#test: 
	// Suspendendo o carregamento do root.
	// Ele será previamente carregado em main().	
    // Carrega a FAT na memória. 		
	//fs_load_fatEx();
	
	
	if( g_fat16_fat_status != 1 )
	{
        printf("fsLoadFile: FAT Status \n");     
        return 1;	
	}

	
	//#debug. 
    //printf("carregar_arquivo: Loading file ...\n"); 

	//
	// Carregar o arquivo.
	//
	
//Loop.	
proxima_entrada:

/*
 * @todo: 
 * Carrega clusters com mais de um setor por cluster. As rotinas para isso 
 * estão no início desse arquivo.
 *
 
while(1)
    {	
	    //Calcula.
		//Primeiro setor do cluster.
	    unsigned long S;
		S = fatClustToSect(cluster, Spc, FAT16_DATAAREA_LBA); 
		
		//Carrega 'x' setores começando de S.
		fatLoadCluster( S, file_address, Spc);
	
	     // Pegar o próximo cluster na FAT.
	     //O cluster atual contém o número do próximo.
	     
	    cluster = fat[cluster];	

	    //ver se o cluster carregado era o último.
	    if(cluster == 0xffff || cluster == 0xfff8){
            goto done;
	    };
    };
 
 *	
 */
 
	//Ler um setor. 
	//(data_area_base + next_cluster - 2)
	//512 bytes por cluster.
	read_lba( address, FAT16_DATAAREA_LBA + cluster -2 ); 
	
	//Incrementa o buffer. +512;
	address = (unsigned long) address + SECTOR_SIZE;    
	
	//Pega o próximo cluster na FAT.
	next = (unsigned short) fat[cluster];	
	
	//Configura o cluster atual.
	cluster = (unsigned short) next;
	
	//Ver se o cluster carregado era o último cluster do arquivo.
	if(cluster == 0xFFFF || cluster == 0xFFF8)
	{ 
	    goto done; 
	};
	
	//#debug.
	//printf("%d ", cluster);
	
	//
	// Loop: 
	// Vai para próxima entrada na FAT.
	//
	
	goto proxima_entrada;
	
	
//
// Fail: O arquivo não pode ser carregado.
//		
fail:
	printf("fsLoadFile: Fail!\n");	
    return (unsigned long) 1;
	
//
// Done: Arquivo carregado com sucesso.
//
done:
#ifdef BL_VERBOSE
    printf("fsLoadFile: Done!\n");
#endif
    return (unsigned long) 0;
};


/*
 * fsSearchFile: 
 *    Procura um arquivo no diretório raiz.
 */
unsigned long fsSearchFile(unsigned char *name)
{        	
    int Status;
    unsigned long z = 0;        //Deslocamento no rootdir. 
    unsigned long n = 0;        //Deslocamento no nome.
    unsigned long max = 512;    //Número máximo de entradas no diretório raiz.
	char name_x[13];
    unsigned short *root = (unsigned short *) FAT16_ROOTDIR_ADDRESS;
	
	// Carrega diretório raiz na memória.
	fs_load_rootdirEx();
    
	
	//
	// Fixa o número máximo de entradas de acordo 
	// com o tipo de sistema de arquivos.
	//
	 
	switch(g_file_system_type)
    {	    
		//fat16
		case 1:
		    max = 512;
		    break; 
	    
		//fat32
		case 2:
		    break;

        //ext2			
	    case 3:
		    break; 
        //...
		
		default:
		    max = 512;
		    break;
	};	
	
	
	//   
	// Procura o arquivo no diretório raiz. 
	// Dado o nome via argumento.
	//
	
	while(max > 0)
    {     
        //Checa a primeira letra do nome.
		if(root[z] != 0)
        {           			
			//Copia o nome e termina incluindo um 0.
			memcpy(name_x, &root[z], 11);
			name_x[11] = 0;
			
            //Compara 11 caracteres.
			Status = strncmp(name, name_x, 11);
            if(Status == 0){
                goto arquivo_encontrado;
			}; 	
		};   
        z += 16;    //(32/2) próxima entrada!
        max--;      //512 vezes!
    }; 
	
	//Nothing.
	
//Se o arquivo não for encontrado.	
arquivo_nao_encontrado:
    printf("fsSearchFile: File not found!\n");     
    return (unsigned long) 1;
	
//Se o arquivo for encontrado.    
arquivo_encontrado:
    return (unsigned long) 0;
};


/*
 * fsSearchFileName:
 *     Procura um nome de arquivo no diretório.
 *     @todo: Rever o tipo de retorno.
 */
unsigned long fsSearchFileName( unsigned char *name){        
    return fsSearchFile(name);
};


/*
 * fs_load_rootdirEx:    
 *    Carrega o diretório raiz na memória.
 *
 * Obs:
 *    Carregando 32 setores do rootdir.
 *    Size = 32 setores. 
 *    512 entradas de 32 bytes cada.
 *
 */
void fs_load_rootdirEx()
{
	unsigned long i;
	unsigned long n = 0;
	unsigned long root_size = 32;    //@todo: Pegar de estrutura. 
	
	// debug
	// printf("Loading root dir ...\n");
	
	//
	// Carregar 32 setores na memória.
	//
	 
	for( i=0; i < root_size; i++){	
		read_lba( FAT16_ROOTDIR_ADDRESS + n, FAT16_ROOTDIR_LBA + i); 
		n = n+512;    //Incrementa buffer.	
	};
	
	//@todo: test ??

done:	
    return;
};


/*
 * fs_load_rootdirEx:
 *     Carrega a FAT na memória. (size = 64 setores).
 *
 */
void fs_load_fatEx()
{
	unsigned long i;
	unsigned long n = 0;
	
	//@todo: Pegar de estrutura.
	unsigned long fat_size = 64;    //64 setores de tamanho.    
	
	// debug
	// printf("Loading Cluster Table.\n");//fat
	
	//
	// Carregar FAT na memória.
	//
	
	for( i=0; i < fat_size; i++){
	    read_lba( FAT16_FAT_ADDRESS + n, FAT16_FAT_LBA + i);   
		n = n+512;    //Incrementa Buffer
	};
	
	//@todo: test ??

done:
    return;
};


/*
 * fs_put_list_on_fat:
 *     Grava na fat uma lista de clusters.
 *     Uma lista de clusters, forma um arquivo.
 */
void fs_put_list_on_fat()
{
    unsigned short i;
    unsigned short lista_size = 1024;
	
    for( i = 0; i < lista_size; i++)
	{
        //último elemento da lista.
		if( file_cluster_list[i] == 0xFFFF || file_cluster_list[i] == 0xFFF8 )
        {
	        fs_set_fat_entry( file_cluster_list[i], 0xFFFF);
			goto done;
        };
		
		//um elemento qualquer da lista.
   	    if(file_cluster_list[i] > 0 && file_cluster_list[i] < lista_size )
        {	
	        fs_set_fat_entry( file_cluster_list[i], file_cluster_list[i+1]);
        };
    };
	
done:
    return;
};


/*
 * fs_find_n_empty_entries:
 *
 */
unsigned long fs_find_n_empty_entries(unsigned long n)
{
    unsigned long i;
	unsigned long l;
	unsigned short empty;
	unsigned short lista_size = 1024;
	
	//@todo: Pegar de estrutura.
	unsigned short fat_max = (64*512/2);    //Número max de entradas na FAT.
	
	// Limits.
	if(n < 0 || n > lista_size){
	    goto fail;
	};
	
	
	for(i = 0; i < n; i++)
	{
		empty = fs_find_empty_entry();
		
		//cria a lista de entradas vazias.
		if( empty != 0 && empty < fat_max )
		{
		    file_cluster_list[l] = empty;
            l++;
		}
        else
        {
		    goto fail;
		};		
	};
	
    file_cluster_list[l] = 0xFFFF;    
	
//
// Done.
//	
done:
	//retorna o primeiro da lista.
	return file_cluster_list[0];
	
fail:	
    return 0;
};

 
/*
 * fs_load_rootdir: 
 *     Carrega o diretório raiz na memória.
 */ 
void fs_load_rootdir(){
    fs_load_rootdirEx();
	return;
};


/*
 * read_lba: 
 *     Lê uma lba no hd. (um setor)
 *     Operação de hardware.
 */
void read_lba( unsigned long address, unsigned long lba){       
    my_read_hd_sector( address, lba, 0, 0);
    return;
};


/*
 * write_lba: 
 *     Grava uma lba no HD. (um setor).
 */
void write_lba( unsigned long address, unsigned long lba){     
    my_write_hd_sector( address, lba, 0, 0);     
    return;
};


/*
 * fsSaveFile:
 * Salvando um arquivo.
 * @todo: Manter a estrutura dessa função mas mudar as rotinas chamadas.
 *           A lib C chama essa função.
 */
unsigned long fsSaveFile( unsigned char *file_name, 
                          unsigned long file_size, 
						  unsigned long file_address )  
{
    unsigned long i;  //Deslocamento. Procurando espaço livre.
    unsigned long j;  //Deslocamento. Salvando cluster number.
    unsigned long c;
    //@todo: Pegar esse valor de uma estrutura de FAT.
    unsigned long max = 128;  //Número máximo de entradas na FAT.
    unsigned long first;
    unsigned long next;
    unsigned long sector;
    unsigned long endereco;  //File address.    	
	unsigned long *fat_base = (unsigned long *) FAT16_FAT_ADDRESS; 
	//Obs: Endereço imposto.
    //@todo: Alocar dinâmicamente.
    unsigned long *list = (unsigned long *) 0x04600000;  //@todo: Rever esse endereço.    
	
	//@todo: Check file address limits.
    //if(file_address == 0){}
	
    //File address.
    endereco = (unsigned long) file_address;
    
    //Carrega 2 setores da FAT.
	//@todo: Isso precisa ser ampliado.
    read_lba(FAT16_FAT_ADDRESS, FAT16_FAT_LBA);
    read_lba(FAT16_FAT_ADDRESS + 0x200, FAT16_FAT_LBA + 1);
	
    j = 0;     //Deslocamento na lista, tem que ser zero.
    c = 32;    //Deslocamaento na FAT.
    i = 32;    //Contagem de entradas  na FAT, começa do 32 e vai até muito.
    
    //Loop. 
    
	while(i != max)
    {
        //procurando espaço livre   
        if(fat_base[c] == 0)
        {
            //fim do arquivo ?
            if(file_size == 0)
            {
                //marca o fim          
                list[j] = 0x0000FFFF;  //eof           
                //encontrado todos os espaços livres que o arquivo precisa.
                goto fat_save;
            };    

            //salva um endereço livre           
            list[j] = c;

            //incrementa a lisa
            j++; 

            //decrementa o tamanho do arquivo!
            file_size--;                  
         };
         
        //incrementa a fat
        c++; 
        
        //incrementa a quantidade de busca.
        i++;
   }; 
   
  // MessageBox("Max entries !");
   fatseg2: goto fatseg2;
    return 1;           

fat_save:
       
    //Início da lista.
    j = (512*4);
    i = 0;
    
    first = list[i];
    
    //
    // Salva no diretório raiz o nome e o primeiro cluster ?? @todo: Check.
    // Corrige deslocamento ?? @todo: Check.
    
	// ??
	// salva_nome(file_name, first); 
    
    while(j)
    {            
        //Pega um conteúdo da lista.
        next = list[i];
        
        //Salva a trilha indicada pela lista.
        // salva_trilha( next, endereco);
        
		//??
		//save_file( 0, endereco, next, 8);
        
		
        //Encontrada a assinatura na lista.
        if(next == 0x0000FFFF)    //@todo: Usar constante. 
        {
            next = list[i-1];
            fat_base[next] = 0x0000FFFF;    //@todo: Usar constante.  
            goto done;         
        }
        else    //Não é assinatura ainda.
        { 
            //-0x60 = é uma correção por causa valor do tipo (unsigned long)!!
            //grava na fat o endereço do proximo cluster
            fat_base[next] = list[i+1];
            
            //grava - aqui next esta certo!!!
            write_lba( endereco, next);
            
            endereco += 512; 
        }; 
         
        i++;    //Próximo valor da lista.           
        j--;
    };
    
    //MessageBox("nao encontra assinatura na lista!");
    
	//
	// @todo: Precisa de uma mensagem de erro aqui.
	//
	
	fatseg3: goto fatseg3;

done:        
    //Salva dois setores da FAT!
    //@todo: Isso precisa ser ampliado.	
    write_lba(FAT16_FAT_ADDRESS        , FAT16_FAT_LBA);
    write_lba(FAT16_FAT_ADDRESS + 0x200, FAT16_FAT_LBA + 1);
    
	return (unsigned long) 0;
};


/*
 * fsCreateDir:
 *     Cria um diretório.
 */	
unsigned long fsCreateDir( char *name , unsigned long id)
{
	return fsCreateFile(name,id);  //Provisório. 
};


/*
 * fsCreateFile:
 *     Cria um arquivo.
 */
unsigned long fsCreateFile( char *name, unsigned long id)
{
    unsigned long fat_entry;
    unsigned long dir_entry;
	unsigned long size = 1;
	
	//encontra uma entrada vazia na fat.
	fat_entry = fs_find_empty_entry();
	
	//testar antes a validade da entrada.
	
	if( fat_entry == 0 ){
	    printf("fs_create_file: error, o cluster vazio eh 0 \n" );
		goto fail;
	};
			
	//erro 2 - nao ha mais entradas vazias
	if( fat_entry == FAT_ERRO_1 ){
		printf("FAT_ERRO_1 nao ha mais entradas vazias!\n" );
		goto fail;
	};
		
	//
	if( fat_entry < 0 || fat_entry > 1024 ){
	    printf("FAT entry fora dos limites!\n");
		goto fail;
	};
			
	//marca na entrada da fat como fim de arquivo.(size 1)
	//fs_set_fat_entry( fat_entry, 0x0000fff8 );
	fs_set_fat_entry( fat_entry, 0x0000FFFF );  //EOF 0x0000fff8
		
	//procura uma entrada vazia no diretorio.
	dir_entry = fs_search_empty_entry(id);
	
    if( dir_entry == 0 ){
        printf("fs_create_file: nao ha entradas vazias no diretorio escolhido\n");
        goto fail;		
	};	
  		 
	if(dir_entry < 0 || dir_entry > 64){
        printf("fs_create_file: entrada fora dos limites\n");
        goto fail;		
	};	
	
	//cria a entrada no diretorio
	fs_create_entry( name, id, dir_entry, fat_entry, size ); 
	
	//fs_save_entry_on_root(i);

done:
#ifdef BL_VERBOSE
    printf("fs_create_file: done ! cluster = %d \n",fat_entry);
#endif    
	return 0;	
fail:   
    printf("fail cluster = %d \n",fat_entry);
	return 1;
};


/*
 * fsClearFat:
 *     Apaga a fat, colocando zero em tudo.
 */
void fsClearFat()
{
    fsInitFat();  //Provisório.	 
    return;
};


/*
 * fsCheckFat: 
 *     Confere os parâmetros da FAT.
 *     @todo: Usar estrutura.
 */
int fsCheckFat()
{
	unsigned long i;
	unsigned long fat_entry;
	
	printf("\n");
	
    for(i = 0; i < 256; i++)
	{
        //Pega a FAT entry.
		fat_entry = fs_get_fat_entry(i);
		
		//Se a entrada da FAT estiver vazia.
		if(fat_entry == 0){
			printf("%c ",'#');
		}else{
			printf("%d ",fat_entry);		
		};
		//Nothing.
	};	

	//Nothing.
	
exit:
#ifdef BL_VERBOSE
    printf("Done.!\n");
#endif
	return 0;
fail:
    printf("Fail!\n");
    return 1;
};


/*
 * fsInitFat:
 *    Inicializa as estruturas da FAT.
 */
void fsInitFat(){
	return;  //Ainda não implementada.
};


/*
 * fsInitStructures: 
 *     +Limpa as estruturas para primeiro uso.
 *     +@todo: Configura as estruturas com os falores encontrados
 *             no mbr, no rootdir.
 *
 * OBS: Quem vai usar essas estuturas é o bootloader.
 */
void fsInitStructures(){
	return;  //Ainda não implementada.
};


/*
 * fsInit:
 *     Inicializa o sistema de arquivos da partição do sistema.
 *     Obs: Isso deve ficar no fim do arquivo.
 */
int fsInit()
{

#ifdef BL_VERBOSE
    printf("fsInit: Initializing structs..\n");
#endif
	fsInitStructures();

#ifdef BL_VERBOSE
	printf("fsInit: Inicializing file system..\n");
#endif
	fsInitFat();

	//More?!

done:
    return (int) 0;
};


//
// End.
//


