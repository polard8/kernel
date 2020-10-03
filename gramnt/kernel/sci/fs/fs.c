/*
 * File: fs/fs.c 
 *
 *     Top level file system support.
 *    
 *   
 * History: 
 *    2015 - Created by Fred Nora.
 *    ...
 */


// #todo
// A tabela de montagem guarda relação com os volumes existentes.
// Esses volumes podem ser de vários tipos.
// See: storage/storage.c

 

#include <kernel.h>



//#todo
/*
// Carrega um arquivo dado a estrutura do diretorio ao qual ele pertence
// Retorna a estrutura de acesso ao arquivo, que tem muitas informaçoes
// sobre o arquivo.
struct file_access_d *fs_load_file_and_get_access( 
    struct dir_d *directory,
    char *filename );
struct file_access_d *fs_load_file_and_get_access ( 
    struct dir_d *directory,
    char *filename )
{

    struct file_access_d *file_access;

    file_access = (struct file_access_d *) kmalloc( sizeof(struct file_access_d) );
    if ( (void*) file_access == NULL )
    {
        debug_print ("fs_load_file_and_get_access: [FAIL] Couldn't allocate\n");
        return (struct file_access_d *) 0;
    }else{

        file_access->Directory = (struct dir_d *) directory;
        
        // ...


    };  
    
    // #todo
    // Load the file and fill the file access structure.
    
    // ...

    debug_print ("fs_load_file_and_get_access: [TODO]\n");
    return (struct file_access_d *) 0;
}
*/



// Cria uma nova estrutura de entrada de diretorio para fat16.
struct fat16_directory_entry_d *fs_new_fat16_directory_entry(void)
{
    struct fat16_directory_entry_d *new;

    new = (struct fat16_directory_entry_d *) kmalloc ( sizeof(struct fat16_directory_entry_d) );
    
    if ( (void*) new == NULL ){
        debug_print("fs_new_fat16_directory_entry: [FAIL]\n");
        return (struct fat16_directory_entry_d *) 0;
    }
    return (struct fat16_directory_entry_d *) new;
}


/*
struct fat16_lfn_directory_entry_d *fs_new_fat16_lfn_directory_entry(void);
struct fat16_lfn_directory_entry_d *fs_new_fat16_lfn_directory_entry(void)
{
    struct fat16_lfn_directory_entry_d *new;

    new = (struct fat16_lfn_directory_entry_d *) kmalloc ( sizeof(struct fat16_lfn_directory_entry_d) );
    
    if ( (void*) new == NULL ){
        debug_print("fs_new_fat16_lfn_directory_entry: [FAIL]\n");
        return (struct fat16_lfn_directory_entry_d *) 0;
    }
    return (struct fat16_lfn_directory_entry_d *) new;
}
*/




/*
//#todo
//Credits: Sirius OS.
unsigned char fs_CheckSum83 (unsigned char *pFcbName);
unsigned char fs_CheckSum83 (unsigned char *pFcbName)
{
	short FcbNameLen;
	unsigned char Sum;
	Sum = 0;

	for (FcbNameLen=11; FcbNameLen!=0; FcbNameLen--) {
		// NOTE: The operation is an unsigned char rotate right
		Sum = ((Sum & 1) ? 0x80 : 0) + (Sum >> 1) + *pFcbName++;
	}

	return (Sum);
}
*/


/*
unsigned char lfn_checksum(const unsigned char *pFCBName);
unsigned char lfn_checksum(const unsigned char *pFCBName)
{
   int i;
   unsigned char sum = 0;

   for (i = 11; i; i--)
      sum = ((sum & 1) << 7) + (sum >> 1) + *pFCBName++;

   return sum;
}
*/


//OUT: inode structure.
struct inode_d *file_inode (file *f)
{
    if ( (void *)f==NULL ){
        return (struct inode_d *) 0;
    }

    return (struct inode_d *) f->inode;
}


// Pega um fd na lista de arquivos do processo, dado o PID.
// Objects[i]
int fs_get_free_fd_from_pid (int pid)
{
    struct process_d *p;
    int __slot=0;


    //#todo max
    if ( pid<0 ){
        debug_print ("fs_get_free_fd_from_pid: pid\n");
        //return -1;
    }

    //
    // Process.
    //
  
    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        debug_print ("fs_get_free_fd_from_pid: p\n");
        return -1;
    }

    if ( p->used != 1 || p->magic != 1234 ){
        debug_print ("fs_get_free_fd_from_pid: p validation\n");
        return -1;
    }
        
        
    // Pick a free one.
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){ return (int) __slot; }
    };
 
 
    return -1;
}



/*
int vfs_root_mounted(void);
int vfs_root_mounted(void)
{
    return (root)?1:0;
}
*/



/*
int fs_file_seek (file *f, int pos);
int fs_file_seek (file *f, int pos)
{
    if( (void*) f == NULL )
        return -1;
        
    f->_w = 0;
    f->_r = 0;
    return 0;
}
*/



// #todo
/*
int fs_count_separators( const char *path);
int fs_count_separators( const char *path){

    size_t count = 0;
    int i;

    
    for (i=0; i < strlen(path); i++)
    {
        if (path[i] == '/')
        {
            count++;
        }
    };


    return (size_t) count;
}
*/


// Check the signature in a elf header.
// OUT:
// 0 = OK. #todo: Isso poderia ser '1'.
// < 0 Means error.

int fsCheckELFFile ( unsigned long address ){

    unsigned char *buffer = (unsigned char *) address;


    if ( buffer[0] != 0x7F ||
         buffer[1] != 0x45 ||
         buffer[2] != 0x4C ||
         buffer[3] != 0x46 )
    {
        printf ("fsCheckELFFile: Sig \n");
        return -1;
    }

    // OK.

    return 0;
}



/*
 *********************************
 * fsListFiles:
 *     Lista os arquivos em um diret�rio, dados os �ndices de disco, 
 * volume e diret�rio.
 */

// #bugbug
// Do not list this in ring0.

void 
fsListFiles ( 
    int disk_id, 
    int volume_id, 
    int directory_id )
{

    // #todo: 
    // Checar mais limites.

    if ( disk_id == -1 || volume_id == -1 || directory_id == -1 )
    {
        debug_print ("fsListFiles: [FAIL]\n");
        goto fail;
    }

    printf ("fsListFiles: disk={%d} vol={%d} dir={%d}\n", 
        disk_id, volume_id, directory_id );

	// Show!
	// Se o diret�rio selecionado � o diret�rio raiz do VFS.

    if ( current_disk == 0 && current_volume == 0 && current_directory == 0 )
    {
        vfsListFiles ();
        goto done;
    }

	// @todo: Suportar outros diret�rios.
	// ...

    goto done;


fail:
    printf ("fail\n");

done:
    refresh_screen ();
    return;
}


/*
 **********************
 * fsList
 *     dir command support.
 *     #bugbug: We don't want this in the kernel.
 */

int fsList ( const char *dir_name ){

    debug_print ("fsList:\n");


    // dir name.
    if ( (void *) dir_name == NULL )
    {
        debug_print ("fsList: dir_name fail\n");
        
        // usar o atual.
        dir_name = current_target_dir.name;

        if ( (void *) dir_name == NULL )
        {
            debug_print ("fsList: dir_name fail\n");
            return -1;
        }
    }


    // address.
    if ( current_target_dir.current_dir_address == 0 ){
        debug_print ("fsList: current_target_dir.current_dir_address fail\n");
        debug_print ("fsList: using root dir [FIXME]\n");
        current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS; 
    }


    if ( (void *) dir_name != NULL && 
         current_target_dir.current_dir_address != 0 )
    {
        // IN:
        // name, dir address, number of entries;
        fsFAT16ListFiles ( (const char *) dir_name,         
            (unsigned short *) current_target_dir.current_dir_address, 
            256 );
        
        debug_print ("fsList: done\n");
        return 0;  
    }

    //fail
    debug_print ("fsList: fail\n");
    return -1;
}


/*
 * fsFAT16ListFiles:
 *     Mostra os nomes dos arquivos de um diret�rio.
 *     Sistema de arquivos fat16.
 *
 * IN:
 *     dir_address = Ponteiro para um endere�o de mem�ria 
 *                   onde foi carregado o diret�rio. 
 */

void 
fsFAT16ListFiles ( 
    const char *dir_name, 
    unsigned short *dir_address, 
    int number_of_entries )
{

    int i=0;
    unsigned long j=0;  // Deslocamento
    
    int max = number_of_entries;         // N�mero m�ximo de entradas.

    unsigned short *DirBaseAddress = (unsigned short *) dir_address;



    if ( number_of_entries <= 0 )
    {
        debug_print ("fsFAT16ListFiles: [FAIL] number_of_entries\n");
        return;
    }

    if ( number_of_entries >= 512 )
    {
        debug_print ("fsFAT16ListFiles: [FAIL] number_of_entries is too big\n");
        return;
    }


    if ( (void *) dir_name != NULL ){
        printf ("fsFAT16ListFiles: Listing names in [%s]\n\n", 
            dir_name );
    }

	// Mostra o nao vazio.

    i=0; 
    while (i < max)
    {
        if ( DirBaseAddress[j] != 0 )
        {
            //#bugbug
            printf ("%s\n", &DirBaseAddress[j] );
        } 

        // (32/2) proxima entrada! 
        // (16 words) 512 vezes!
        
        j += 16;  
        i++;  
    }; 

    // ...

    refresh_screen();
}



/*
 * get_file:
 *     Get the pointer given the index in file_table[].
 */
// na lista de arquivos do kernel.
void *get_file (int Index){

	//Limits.
	//@todo: max.

    if (Index < 0)
    {
        // ?? todo: message
        return NULL;
    }

    return (void *) file_table[Index];
}


/*
 * set_file:
 *     Put the pointer in the list, given the index.
 */
// na lista de arquivos do kernel.
void set_file ( void *file, int Index ){

    if (Index < 0){
        // ?? todo: message
        return;
    }

	// #todo:
	// Limite m�ximo da lista.

	// Structure.

    if ( (void *) file == NULL )
    {
        // ?? todo: message
        return;
    }

	// Include pointer in the list.


     file_table[Index] = (unsigned long) file;
}


/*
//#todo
file *getfile(void);
file *getfile(void)
{
    file *_f;
    int i=0;
    
    for(i=0;i<NUMBER_OF_FILES;i++)
    {
        _f = (void*) file_table[i];
        if( (void*) _f == NULL )
            return (file *) _f;
    };

    //fail
    return (file *) 0;
}
*/


void *get_global_open_file (int Index){

	//Limits.
	//@todo: max. NUMBER_OF_FILES

    if (Index < 0){
        // ?? todo: message
        return NULL;
    }

    return (void *) file_table[Index];
}


void set_global_open_file ( void *file, int Index ){

    if (Index < 0){
        // ?? todo: message
        return;
    }

	// #todo:
	// Limite m�ximo da lista.

	// Structure.

    if ( (void *) file == NULL )
    {
        // ?? todo: message
        return;
    }

	// Include pointer in the list.


     file_table[Index] = (unsigned long) file;
}


void fs_show_file_info (file *f)
{
    if ((void*)f==NULL)
    {
        //??
        return;
    }{
        if (f->used==1)
        {
            
            if ( (void*) f->_tmpfname != NULL ){
                printf ("Name={%s}\n",f->_tmpfname);
            //refresh_screen();
            }
        }
    }; 
}

void fs_show_file_table(void)
{
    file *f;
    int i=0;


    printf ("\nfile_table:\n");
    
    for (i=0; i<32; i++)
    {
        f=(file*)file_table[i];
        if( (void*)f!=NULL )
            fs_show_file_info(f);
    };
    
    refresh_screen();
}


void fs_show_inode_info (struct inode_d *i)
{
    if ((void*)i==NULL)
    {
        //??
        return;
    }{
        
        if (i->used==1)
        {
    
            if( (void*)i->path != NULL ){
                printf ("Name={%s}\n",i->path);
            //refresh_screen();
            }
        }
    }; 
}

void fs_show_inode_table(void)
{
    int i=0;
    struct inode_d *inode;


    printf ("\ninode_table:\n");
    
    for(i=0; i<32; i++)
    {
        inode=(struct inode_d *)inode_table[i];
        
        if ( (void*)inode!=NULL ){
            fs_show_inode_info(inode);
        }
    };

    refresh_screen();
}




//get free slots in the file_table[]
int get_free_slots_in_the_file_table(void)
{
    file *tmp;
    int i=0;

    
    for (i=0;i<NUMBER_OF_FILES; i++)
    {
        tmp = (void*) file_table[i];
        
        // Nenhum file descritor está usando essa estrutura.
        if (tmp->used == 1 && 
            tmp->magic == 1234 && 
            tmp->fd_counter == 0)
        { 
            return (int) i; 
        }
    };

    return -1;
}


//get free slots in the inode_table[]
int get_free_slots_in_the_inode_table(void)
{
    struct inode_d *tmp;
    int i=0;

    
    for (i=0;i<32; i++)
    {
        tmp = (void*) inode_table[i];
        
        // Nenhum descritor de estrutura de arquivo está usando essa estrutura inode.
        if (tmp->used == 1 && 
            tmp->magic == 1234 && 
            tmp->filestruct_counter == 0)
        { 
            return (int) i; 
        }
    }

    return -1;
}



/*
 ***************************************************
 * fsCheckMbrFile: 
 *     Check mbr file, given a buffer.
 */

void fsCheckMbrFile ( unsigned char *buffer ){

	//#todo
	//mudar os argumentos para chamarmos as portas ide.

    unsigned char *mbr = (unsigned char *) buffer; 
    int i=0;


	//setor 0.
    my_read_hd_sector ( (unsigned long) &mbr[0] , 0, 0 , 0 ); 

	//message:
    //printf ("\n");
    printf ("fsCheckMbrFile: Testing MBR ...\n");

	// @todo:
	// Checar uma estrutura do mbr do disco do sistema,
	// para validar o acesso � ele.	

    // Check signature.
    if ( mbr[0x1FE] != 0x55 || mbr[0x1FF] != 0xAA ){
        printf ("fsCheckMbrFile: Sig FAIL \n" );
        goto fail;
    }

	//jmp
    printf ("JMP: [ %x ", mbr[ BS_JmpBoot + 0 ] );
    printf ("%x ", mbr[ BS_JmpBoot + 1 ] );
    printf ("%x ]\n", mbr[ BS_JmpBoot + 2 ] );


	//name
    printf ("OS name: [ ");
    for ( i=0; i<8; i++ ){
        printf ("%c", mbr[ BS_OEMName + i ] );
    };
    printf (" ]\n");


	//...


    printf ("Signature: [ %x %x ] \n" , mbr[0x1FE], mbr[0x1FF] );

	// Continua ...
    goto done;

fail:
    printf ("Fail\n");

done:
    printf ("Done\n");
    refresh_screen ();
    return;
}


/*
 * fsCheckVbr:
 *     Checa o registro de boot de um volume.
 *     Vai no endere�o onde est� armazenado o VBR do volume atual
 *     e confere as informa��es sobre o volume.
 */

void fsCheckVbrFile ( unsigned char *buffer ){

    unsigned char *vbr = (unsigned char *) buffer; 

	//#todo: check address validation.

	// #todo:
	// Checar uma estrutura do mbr do disco do sistema, para validar o 
	// acesso � ele.

	// Check signature.

    if ( vbr[0x1FE] != 0x55 || vbr[0x1FF] != 0xAA ){
        printf ("fsCheckVbrFile: Sig Fail\n");
        goto fail;
    }


	//
	// Continua ...
	//

    goto done;

fail:
    printf ("fsCheckVbrFile: fail\n");

done:
    printf ("Done\n");
    refresh_screen();
    return;
}



// set_spc:
// Configura spc, 'Sector Per Cluster' em vari�vel global.
// ?? #bugbug: De qual disco ?? 

void set_spc (int spc)
{
    g_spc = (int) spc;
}


/*
 * get_spc:
 *     Pega spc, Sector Per Cluster.
 *     ?? #bugbug: De qual disco ?? 
 */

int get_spc (void)
{
    return (int) g_spc;
}


/*
 * get_filesystem_type:
 *     Pega o tipo de sistema de arquivos.
 *     ?? #bugbug: De qual volume ??  
 */

int get_filesystem_type (void)
{
    return (int) g_currentvolume_filesystem_type;
}


/*
 * set_filesystem_type:
 *     Configura o tipo de sistema de arquivo.
 *     ?? #bugbug: De qual volume ?? 
 */

void set_filesystem_type (int type)
{
    g_currentvolume_filesystem_type = (int) type;
}



//Credits: Sirius OS.
unsigned long path_count (unsigned char *path)
{
    int i=0;
    unsigned long val=0;
    int max = (80*25);


    for ( i=0; i < max; i++ )
    {
        if (path[i] == '/')
            val++;
        
        if (path[i] == '\0')
            break;
    };


    return (unsigned long) val;
}




/*
 ********************************** 
 * load_path:
 *     Carrega nesse endereço o arquivo que está nesse path.
 */


// IN:
// path de dois níveis, endereço onde carregar.
// Ex: "/BIN/GDESHELL.BIN"

// #ok
// Carregou um arquivo com 3 niveis.


//   0 ---> ok.
// != 0 ---> fail

int load_path ( unsigned char *path, unsigned long address ){

    int i=0;         // Deslocamento dentro do buffer.
    int level=0;
    int l=0;
    unsigned long n_levels = 0;
    
    // Fail. 
    // Usado na função que carrega o arquivo.
    int Ret = -1;    
        
    char buffer[12];
    unsigned char *p;


    // Onde carregaremos o diretório.
    void *__src_buffer;
    void *__dst_buffer;
    void *__file_buffer;



    // Address
    if (address == 0){
        panic ("load_path: address\n");
    }

    // File buffer.
    __file_buffer = (void *) address;


    // Counting the levels.
    n_levels = path_count(path);
    
    if (n_levels==0){
        panic ("load_path: n_levels\n");
    }
    
    printf ("path with %d levels\n",n_levels);


    // Start with 0.
    level = 0;

    // Path provisório.
    p = path;


    // #bugbug
    // Overflow quando colocarmos um diretorio maior que
    // o buffer.

    // Primeiro src =  root address;
    __src_buffer = (void *) VOLUME1_ROOTDIR_ADDRESS;
    unsigned long limits = (512*32);

    
    // Not absolute   
    if ( p[0] != '/' )
    {
        panic ("load_path: Not absolute pathname \n");
    }

    
    //
    // loop: Carregar n levels.
    //

    for (l=0; l<n_levels; l++)
    {

        printf ("\n[LEVEL %d]\n\n",l);
        
        // The level needs to start with '/', even the first one.
        if ( p[0] != '/' ){
            panic ("load_path: All levels need to start with '/' \n");
        }
        
        //Skip the '/'.
        p++;  

        // Walk 13 chars in the same level.
        for ( i=0; i<12; i++ )
        {
            // #debug
            printf ("%c", (char) *p);

            // Copia o char para o buffer até que o char seja '/'
            // indicando inicio do próximo nível.
            
            buffer[i] = (char) *p;
            
            
            // O ponto deve aparecer no último nível.
            // caso contrário falhou
            if ( *p == '.' )
            {
                if ( l != (n_levels-1) ){
                    panic ("load_path: Directory name with '.'\n");
                }
                
                // Se o ponto está além do limite permitido.
                //if (i>7){
                if (i>=7){
                    printf ("load_path: '.' fail.\n");
                    panic ("Name size bigger than 8.\n");
                }
                
                // Se o ponto for antes do nono slot. OK.
                if (i<8)
                {
                     // Nome tem no máximo 8 chars.
                     // Completamos com espaço, pois queremos o formato:
                     // "FILE    123"
                     while (i<=7){ buffer[i] = ' '; i++; };

                     
                     // Skip the dot '.'.
                     // Yes it is a dot. See the IF statement above.
                     p++;
                     
                     // Add the extension.
                     while (i<=11)
                     {
                         buffer[i] = (char) *p;
                         i++;
                         p++;
                     } 
                       
                     // Finalize the string.
                     buffer[11] = 0;
                     
                     printf ("\n");
                     printf ("load_path: This is the name {%s}\n",buffer);   
                }


                //
                // Load file.
                //
    
                // Como esse é o último, então vamos usar o endereço desejado pelo usuário.
                __dst_buffer = (void *) __file_buffer;
    
                if ( (void *) __dst_buffer == NULL ){
                    panic ("load_path: __dir\n");
                }

                      // IN: 
                      // fat address, dir address, filename, file address.
                Ret = fsLoadFile ( 
                          (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                          (unsigned long) __src_buffer,         // dir address. onde procurar. 
                          32,                                   //#bugbug: Number of entries. 
                          (unsigned char *) buffer,             // nome 
                          (unsigned long) __dst_buffer,         // addr. Onde carregar.
                          limits );                             // tamanho do buffer onde carregar.             

                // ok.
                if ( Ret == 0 )
                {
                    printf ("Level %d loaded!\n\n",l);
                    
                    // #importante
                    // Esse nível tinha ponto, então deveria ser o último.
                    if ( l != (n_levels-1) )
                    {
                        printf ("load_path: Directory name with '.'\n");
                        panic ("It needs to be the last level.\n");
                    }

                    // SUCCESS ?!!
                    debug_print ("load_path: done\n");
                    return 0;

                }else{
                    panic ("load_path: [FAIL] Loading level 0\n");
                };
            }


            // Se encontramos um indicador de próximo nível,
            // então esse nível não será considerado binário.
            // obs: 
            // Ao iniciar o for ele precisa encontrar esse mesmo char.
            
            if ( *p == '/' )
            {
                // Encontramos o indicador de proximo nivel,
                // o buffer ja tem chars que foram colocados um a um.
                // Nao encontramos ponto nesse nivel.
                // Vamos completar o nome do diretorio com espaços e finalizar.
                
                if (i<11)
                {
                    // Adicionando espaços.
                    // O formato desejado eh: "DIRXDIRX   "
                    // Nome do diretorio sem extensao.
                    while (i<=11)
                    { 
                        //o primeiro espaço deve retirar a barra colocada antes
                        buffer[i] = ' ';  
                        i++; 
                    }
                }
                
                // Finalize the string.
                buffer[11] = 0;
                
                printf ("\n");
                printf ("load_path: This is the name {%s}\n",buffer);

                //
                // Load directory.
                //

                // #bugbug
                // E se o arquivo for maior que a area alocada.
                // Alocando memória para carregar o diretório.
                
                unsigned long BUGBUG_OVERFLOW = (512*32);
                limits = BUGBUG_OVERFLOW;
                
                __dst_buffer = (void *) kmalloc (    BUGBUG_OVERFLOW    ); 
    
                if ( (void *) __dst_buffer == NULL ){
                    panic ("load_path: __dir\n");
                }
                          
                      //IN: fat address, dir address, filename, file address.
                Ret = fsLoadFile ( 
                          (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                          (unsigned long) __src_buffer,         // dir address. onde procurar.
                          32,                                   // #bugbug: Number of entries.  
                          (unsigned char *) buffer,             // nome que pegamos no path 
                          (unsigned long) __dst_buffer,         // onde carregar. 
                          limits );                             // tamanho do buffer onde carregar.
                          
                          
                // ok.
                if ( Ret == 0 )
                {
                    printf ("Level %d loaded!\n\n",l);
                    
                    // O endereço onde carregamos o arquivo desse nível
                    // será o endereço onde vamos procurar o arquivo do próximo nível.
                    __src_buffer = __dst_buffer;
                    
                    break;

                }else{
                    panic ("load_path: [*FAIL] Loading level 0\n");
                };
            }


            // Avançamos o char se não foi '.', nem '/'.
            p++;
        };
    };   


fail:
    debug_print ("load_path: Fail\n");
    printf      ("load_path: Fail\n");
    refresh_screen();
    return (-1);
}


/*
 ****************************************
 * sys_load_path:
 *     Load file given a pathname.
 */

int sys_load_path ( unsigned char *path, unsigned long u_address )
{
    int status = -1;


    debug_print ("sys_load_path:\n");
    
    status = load_path ( (unsigned char *) path, (unsigned long) u_address );
    
    return (int) status;
}


/*
 ***********************************************
 * fs_init_fat:
 *     Inicializa a estrutura usada no sistema de arquivos.
 *     fsInitFat()
 *     ?? #bugbug: De qual volume ?? 
 */

// #todo: Usar tipo 'int'.

void fs_init_fat (void){

    //
    // The root file system structure.
    //
    
    // "/"

    if ( (void *) root == NULL ){
        panic ("fs_init_fat: No root file system!\n");
    }


    //
    // FAT structure.
    //
    
    
    fat = (void *) kmalloc ( sizeof(struct fat_d) );

    if ( (void *) fat == NULL ){
        panic ("fs_init_fat: No fat struture \n");

    }else{

        // Info.
        fat->address = root->fat_address; 
        fat->type    = root->type;


        // Continua ...
    };


	// #bugbug
	// N�o fizemos nada com a estrutura 'fat'
	// tem que passar esse ponteiro para algum lugar.


	// Continua a inicializa��o da fat.
}


/*
 ******************************************************
 * fs_init_structures:
 *     Inicializa a estrutura do sistema de arquivos.
 *     fsInitStructures
 */

// #todo: Usar tipo 'int'.

void fs_init_structures (void){

    int Type=0;

    //
    // The root file system.
    //
    
    // "/"

    root = (void *) kmalloc ( sizeof(struct filesystem_d) );

    if ( (void *) root == NULL ){
        panic ("fs_init_structures: Couldn't create the root structure.\n");

    }else{
        root->objectType  = ObjectTypeFileSystem;
        root->objectClass = ObjectClassKernelObjects;
        root->used  = 1;
        root->magic = 1234;

        root->name = (char *) ____root_name;
        
        // Se o volume do vfs ainda não foi criado 
        // então não podemos prosseguir.
        if ( (void *) volume_vfs == NULL )
        {
            debug_print("fs_init_structures: [FAIL] volume_vfs not initialized");
            panic      ("fs_init_structures: [FAIL] volume_vfs not initialized");
        }
        
        volume_vfs->fs = root;
        
        storage->fs = root;
        //...
    };



    // Type.
    // #bugbug: 
    // Em qual disco e volume pegamos o tipo de sistema de arquivos?


    Type = (int) get_filesystem_type();

    if ( Type <= 0 ){
        panic ("fs_init_structures: [PANIC] Type");

    }else{
        root->type = (int) Type;
    };


    switch (Type)
    {
        case FS_TYPE_FAT16:

            // Disk stuff.
            // spc - Sectors per cluster.
            root->spc = (int) get_spc(); 

            // Rootdir, Fat and data area.
            // #bugbug: Specific for fat16.
            root->rootdir_address = VOLUME1_ROOTDIR_ADDRESS;
            root->rootdir_lba     = VOLUME1_ROOTDIR_LBA;
            root->fat_address     = VOLUME1_FAT_ADDRESS;
            root->fat_lba         = VOLUME1_FAT_LBA;
            root->dataarea_lba    = VOLUME1_DATAAREA_LBA;
            //filesystem->dataarea_address = ??;
 
            // Root dir.
            
            // Number of entries in the root dir.
            // #bugbug: Specific for fat16.
            root->dir_entries = FAT16_ROOT_ENTRIES;
            
            // Size of the entry in bytes.
            // #bugbug: Specific for fat16.
            root->entry_size = FAT16_ENTRY_SIZE;
       
            // ...
            break;

        // Nothing for now.
        case FS_TYPE_EXT2:
            panic ("fs_init_structures: [PANIC] FS_TYPE_EXT2 not supported");
            break;

        //...

        // Nothing for now.
        default:
            panic ("fs_init_structures: [PANIC] default Type");
            break;
    };
    
    // Done.
}



void fs_show_root_fs_info(void)
{

    printf ("\n");
    printf ("fs_show_root_fs_info:\n");

    //
    // root fs structure.
    //

    if ( (void *) root == NULL ){
        printf ("No root structure\n");
        goto fail;
 
    }else{

        if ( root->used != 1 || root->magic != 1234 ){
             printf ("Validation fail\n");
             goto fail;
        }

        printf ("name = %s \n",        root->name );
        printf ("Object type %d \n",   root->objectType );
        printf ("Object class %d \n",  root->objectClass );
        printf ("type = %d \n",        root->type );
        printf ("Dir entries %d \n",   root->dir_entries );
        printf ("Entry size %d \n",    root->entry_size );
        //printf ("",root-> );

        refresh_screen();
        return;
    }; 

fail:
    refresh_screen();
    return;
}


/*
 ********************************************************
 * fsInit:
 *     Initializes the fs support.
 * 
 */


// #todo
// Essa funcao deve ter acesso as informacoes herdadas do boot.
// Talvez uma estrutura de 'BootInfo'.


int fsInit (void)
{
    int slot = -1;



    debug_print ("fsInit:\n");

    // Undefined fs!
    set_filesystem_type(FS_TYPE_NULL);


    //
    // Initialize fat16 support for the system's volume.
    //

    // #todo: 
    // Devemos checar o tipo da partiçao de boot. 
    // Se nao aqui, depois!

    fat16Init();


	//
	// == fileList =========================
	//

	// Agora inicialzamos as stream 4 e 5.
	// As anteriores foram inicializadas em stdio,
	// pois s�o o fluxo padr�o.

    //
    // == volume1_rootdir =========================================== 
    //

    // pega slot em file_table[] para
    slot = get_free_slots_in_the_file_table();
    if(slot<0 || slot >=NUMBER_OF_FILES)
        panic("fsInit: slot");
    volume1_rootdir = file_table[slot];
    volume1_rootdir->filetable_index = slot;

    if ( (void *) volume1_rootdir == NULL ){
        panic ("fsInit: volume1_rootdir \n");

    } else {

        volume1_rootdir->used = 1;
        volume1_rootdir->magic = 1234;
        volume1_rootdir->____object = ObjectTypeVolume;

        volume1_rootdir->_base = (unsigned char *) VOLUME1_ROOTDIR_ADDRESS;
        volume1_rootdir->_p    = (unsigned char *) VOLUME1_ROOTDIR_ADDRESS;
        volume1_rootdir->_cnt = (32 * 512);
        volume1_rootdir->_file = 0;
        volume1_rootdir->_tmpfname = "VOLUME1 VOL";
        volume1_rootdir->fd_counter = 1;

        // #bugbug: 
        // Validade da estrutura.
        
        // ...
        // inode support.
        // pega slot em inode_table[] 
        slot = get_free_slots_in_the_inode_table();
        if(slot<0 || slot >=32)
            panic("fsInit: volume1_rootdir inode slot");
        volume1_rootdir->inode = inode_table[slot];
        volume1_rootdir->inodetable_index = slot;
        if( (void*) volume1_rootdir->inode == NULL ){
            panic("fsInit: volume1_rootdir inode struct");
        }
        volume1_rootdir->inode->filestruct_counter = 1; //inicialize
        memcpy( (void*) volume1_rootdir->inode->path, 
                (const void*) volume1_rootdir->_tmpfname, 
                sizeof( volume1_rootdir->inode->path ) );
        // ... 


        // File that represents the system volume.
        storage->__file = volume1_rootdir; 
    };


    //
    // == volume2_rootdir =========================================== 
    //


    // pega slot em file_table[] para
    slot = get_free_slots_in_the_file_table();
    if(slot<0 || slot >=NUMBER_OF_FILES)
        panic("fsInit: slot");
    volume2_rootdir = file_table[slot];
    volume2_rootdir->filetable_index = slot;

    if ( (void *) volume2_rootdir == NULL ){
        panic ("fsInit: volume2_rootdir\n");


    }else{

        volume2_rootdir->used = 1;
        volume2_rootdir->magic = 1234;
        volume2_rootdir->____object = ObjectTypeVolume;
 
        volume2_rootdir->_base = (unsigned char *) VOLUME2_ROOTDIR_ADDRESS;
        volume2_rootdir->_p    = (unsigned char *) VOLUME2_ROOTDIR_ADDRESS;
        volume2_rootdir->_cnt = (32 * 512) ;
        volume2_rootdir->_file = 0; //?
        volume2_rootdir->_tmpfname = "VOLUME2 VOL";
        volume2_rootdir->fd_counter = 1;

        // ...
        // inode support.
        // pega slot em inode_table[] 
        slot = get_free_slots_in_the_inode_table();
        if(slot<0 || slot >=32)
            panic("fsInit: volume2_rootdir inode slot");
        volume2_rootdir->inode = inode_table[slot];
        volume2_rootdir->inodetable_index = slot;
        if( (void*) volume2_rootdir->inode == NULL ){
            panic("fsInit: volume2_rootdir inode struct");
        }
        volume2_rootdir->inode->filestruct_counter = 1; //inicialize
        memcpy( (void*) volume2_rootdir->inode->path, 
                (const void*) volume2_rootdir->_tmpfname, 
                sizeof( volume2_rootdir->inode->path ) );
        // ... 

    };


    //
    // == pipe_gramadocore_init_execve ================================ 
    //


	//
	// ## Inicializando os pipes usados em execve ## 
	//

	
	//gramado core init execve 
	
	//aloca mem�ria para a estrutura.
    pipe_gramadocore_init_execve = (file *) kmalloc ( sizeof(file) );

    if ( (void *) pipe_gramadocore_init_execve == NULL ){
        panic ("fsInit: pipe_gramadocore_init_execve\n");

    }else{

        // Aloca memória para o buffer.
        unsigned long pipe0base = (unsigned long) kmalloc (512);

        if ( (void *) pipe0base == NULL ){
            panic ("fsInit: pipe0base\n");
        }


        pipe_gramadocore_init_execve->used = 1;
        pipe_gramadocore_init_execve->magic = 1234;

        pipe_gramadocore_init_execve->_base = (unsigned char *) pipe0base;
        pipe_gramadocore_init_execve->_p = (unsigned char *) pipe0base;
        pipe_gramadocore_init_execve->_cnt  = 512;
        pipe_gramadocore_init_execve->_file = 0; //??
        pipe_gramadocore_init_execve->_tmpfname = "pipe0";
        
        
        // #todo
        //fileList[ ? ] = (unsigned long) pipe_gramadocore_init_execve;

        // 0
        Pipes[0] = (unsigned long) pipe_gramadocore_init_execve;
    };


	//
	// PWD
	//

    // Inicializa o pwd support.
    fsInitializeWorkingDiretoryString();

	//
	// target dir struct
	//

    // Inicializa a estrutura de suporte ao target dir.
    fsInitTargetDir();

    
    // Done.
    debug_print ("fsInit: done\n");

    
    return 0;
}



/*
 *****************************************************
 * fat16Init:
 *     Initialize fat16 fs support.
 *     This is used by the system's volume.
 */

int fat16Init (void){

    debug_print ("fat16Init:\n");
    
    fat_cache_loaded = CACHE_NOT_LOADED;
    fat_cache_saved  = CACHE_NOT_SAVED;



	// Type - Configura o tipo de sistema de arquivos usado. 
	// No caso, (fat16).
	//
	// @todo: Deve-se checar o volume ativo e ver qual sistema de arquivos est�
	//        sendo usado, ent�o depois definir configurar o tipo.
	//        O sistema operacional pode salvar o tipo usado. Nesse caso 
	//        apenas checar se ouve altera��es nas configura��es de sistema de arquivos.
	//        O registro de configura��es de disco pode ser armazenado em arquivos de metadados.

    set_filesystem_type (FS_TYPE_FAT16);


	// SPC 
	// Configura o n�mero de setores por cluster.
	// Nesse caso, s�o (512 bytes por setor, um setor por cluster).

    set_spc(1);


	// ## initialize currents ##


	//selecionando disco, volume e diret�rio.
	//estamos resetando tudo e selecionando o diret�rio raiz 
	//do vfs ... mas na verdade o diret�rio selecionado 
	//deveria ser o diret�rio onde ficam a maioria dos aplicativos.
	//para que o usu�rio possa chamar o maior n�mero de apps usando 
	//apenas comandos simples.
	//#bugbug: isso deveria se passado pelo boot ??	


	//#bugbug: 
	//Deixaremos cada m�dulo inicializar sua vari�vel.
	//Mas aqui podemos zerar esses valores.
	
	//current_disk = 0;
	//current_volume = 0;   
	//current_directory = 0;



    // Structures and fat.

    fs_init_structures();
    fs_init_fat();


    // Done.
    debug_print ("fat16Init: done\n");
    
    return 0;
}


/*
 *****************************************
 * fsInitializeWorkingDiretoryString:
 *     Atualiza a string do diret�rio de trabalho.
 * Essa eh a string que ser� mostrada antes do prompt.
 * 'pwd'> 
 */
 
void fsInitializeWorkingDiretoryString (void){

    struct volume_d  *v;

    char volume_string[8];   


    debug_print ("fsInitializeWorkingDiretoryString:\n");


    volume_string[0] = 'v';
    volume_string[1] = 'o';
    volume_string[2] = 'l';
    volume_string[3] = 'u';
    volume_string[4] = 'm';
    volume_string[5] = 'e';
    volume_string[6] = (char)( '1' + (char) current_volume - (char) 1 );
    volume_string[7] = '\0';


	//'root:'
	//  ## volume list ##
	//primeiro colocamos a string que indica a lista de volumes. 

    sprintf ( current_workingdiretory_string, FS_ROOT_STRING ); 

	//'/'
	// ## separador ##
    strcat ( current_workingdiretory_string, FS_PATHNAME_SEPARATOR );


	//
	//  ## volume root dir ##
	//

    v = (struct volume_d *) volumeList[current_volume];

    if ( (void *) v == NULL )
    {
        panic ("fsInitializeWorkingDiretoryString: v\n");

    }else{

        if ( v->used != 1 || v->magic != 1234 ){
            panic ("fsInitializeWorkingDiretoryString: validation\n");
        }

        switch (v->id)
        {
			//case 0:
		        //global usada para string do nome do volume.
			//    current_volume_string = (char *) FS_VOLUME0_STRING;
			//    break;

			//case 1:
		        //global usada para string do nome do volume.
			//   current_volume_string = (char *) FS_VOLUME1_STRING;
			//   break;
			
            default:
		        //fail.
		        //printf("fsInitializeWorkingDiretoryString: default volume #todo\n");
		        //die();
                current_volume_string = (char *) volume_string; 
                break;
        };


		//path string na estrutura do volume.
        sprintf ( v->path_string, current_volume_string );

	    //'volumeX'
        strcat ( current_workingdiretory_string, v->path_string );
	    //strcat ( current_workingdiretory_string, current_volume_string );
    };


	// ## separador ##
    strcat ( current_workingdiretory_string, FS_PATHNAME_SEPARATOR );

	//More ?...
    pwd_initialized = 1;

    debug_print ("fsInitializeWorkingDiretoryString: done\n");
}


/*
 ***************************
 * fsInitTargetDir:
 *     Para inicializarmos o sistema ja' com um alvo, no caso o root dir. 
 */

void fsInitTargetDir (void)
{
    current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
    //current_target_dir.name = ?;
}


/*
 **************************************
 * fs_initialize_process_pwd:
 *     Cada processo deve inicialiar seus dados aqui. 
 */

int fs_initialize_process_pwd ( int pid, char *string ){

    struct process_d *p;
    int i=0;


    if (pid<0){
        debug_print ("fs_initialize_process_pwd: pid\n");
        return 1;
    }


    if ( (void *) string == NULL ){
        debug_print ("fs_initialize_process_pwd: string\n");
        return 1;
    }

    // Current process.

	// #importante
	// Vamos copiar a string para a estrutura do processo atual.

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fs_initialize_process_pwd: p\n");

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fs_initialize_process_pwd: validation\n");
        }

        for ( i=0; i<32; i++ ){
            p->pwd_string[i] = string[i];
        }
    };


    return 0;
}


/*
 * fs_print_process_pwd
 *     Cada processo tem seu pr�prio pwd.
 *     Essa rotina mostra o pathname usado pelo processo. 
 */

int fs_print_process_pwd (int pid){

    struct process_d *p;


    debug_print ("fs_print_process_pwd:\n");

    if (pid<0){
        debug_print ("fs_print_process_pwd: pid\n");
        return 1;
    }

    // Process

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fs_print_process_pwd: p\n");

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fs_print_process_pwd: validation\n");
        }

        printf ("PWD:\n");
        
        if ( (void *) p->pwd_string != NULL )
            printf ("> PID=%d %s \n", p->pid, p->pwd_string);
            
        if ( (void *) current_target_dir.name != NULL )
            printf ("> PID=%d %s \n", p->pid, current_target_dir.name);

        refresh_screen ();
        return 0;
    };


    // fail.
    debug_print ("fs_print_process_pwd: fail\n");
    
    return -1;
}


/*
 *****************************************
 * fsUpdateWorkingDiretoryString:
 * 
 *     +Atualiza o pathname na estrutura do processo atual.
 *     +Atualiza o pathname na string global. 
 */ 
 
void fsUpdateWorkingDiretoryString ( char *string ){

    struct process_d  *p;
    char *tmp;
    int i=0; 


    tmp = string;

    debug_print ("fsUpdateWorkingDiretoryString:\n"); 

    // Initialized ?
    if ( pwd_initialized == 0 ){
        debug_print ("fsUpdateWorkingDiretoryString: pwd_initialized\n"); 
        return;
    }

    // string
    if ( (void *) string == NULL ){
        debug_print ("fsUpdateWorkingDiretoryString: string\n"); 
        return;  
    }

    // Current process.

    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        panic ("fsUpdateWorkingDiretoryString: p\n");

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fsUpdateWorkingDiretoryString: validation\n");
        }

        // Atualiza a string do processo atual. Concatenando.
        if ( (void *) string != NULL )
        {
            // Concatena string.
            strcat ( p->pwd_string, string );

            // Concatena separador.
            strcat ( p->pwd_string, FS_PATHNAME_SEPARATOR );

            // Atualiza a string global usando a string do 
            // processo atual.
            for ( i=0; i<32; i++ ){
                current_workingdiretory_string[i] = p->pwd_string[i];
            }

            // #bugbug: rever isso.
            // Nome do diretório alvo atual.
            for ( i=0; i< 11; i++ ){
                current_target_dir.name[i] = *tmp;
                tmp++;
            }
        }
    };

    debug_print ("fsUpdateWorkingDiretoryString: done\n"); 
}



/* 
 ************************************************
 * fs_pathname_backup:
 *     Remove n nomes de diret�rio do pathname do processo indicado no 
 * argumento.
 *     Copia o nome para a string global.
 *     Remove the last N directories from PATH.  
 *     Do not leave a blank path.
 *     PATH must contain enough space for MAXPATHLEN characters. 
 *     #obs: O PID costuma ser do processo atual mesmo. 
 *     Credits: bash 1.05 
 */
 
void fs_pathname_backup ( int pid, int n ){

    struct process_d *p;
    int i=0;


    if ( pwd_initialized == 0 ){
        printf ("fs_pathname_backup: pwd not initialized\n"); 
        return;
    } 


    if ( pid<0 ){
        printf ("fs_pathname_backup: PID\n"); 
        return;
    }


    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fsUpdateWorkingDiretoryString: p\n");

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fsUpdateWorkingDiretoryString: validation\n");
        }


        char *path = (char *) p->pwd_string;

        register char *s = path + strlen( path );
 
        if (*path)
            s--;

        while (n--)
        {
            while (*s == '/')
                s--;

            while (*s != '/')
                s--;

            *++s = '\0';
        };

        // Atualizando a string global.
        for ( i=0; i<32; i++ ){
            current_workingdiretory_string[i] = p->pwd_string[i];
        }


        // Name.
        for ( i=0; i< 11; i++ ){
            current_target_dir.name[i] = '\0';
        }
    };
}


/*
//#todo
// temos que procurar um path na lista de inodes.
// retorna o index se encontrarmos e -1 se falhar.
int fs_search_inode_table( char *path )
int fs_search_inode_table( char *path )
{
    //fail
    return -1;
}
*/

/*
 ************************************* 
 * sys_read_file: 
 * 
 *     This is called by sys_open()
 */

// usada por open()
// tem que retornar o fd e colocar o ponteiro na lista de arquivos
// abertos.
// Carrega um arquivo do disco para a mem�ria.
// funcionou.

// #bugbug
// Na minha m�quina real, �s vezes d� problemas no tamanho do arquivo.


// #bugbug
// Estamos alocando mem�ria em ring para carregar o arquivo
// e depois estamos usando o buffer em ring3 passado pelo usu�rio.
// >>> vamos confiar no usu�rio e usarmos


    // #bugbug
    // precisamos colocar os arquivos também na lista
    // global de arquivos abertos. file_table[]
    // E na lista de inodes. inode_table[]
    // See: fs.c

int 
sys_read_file ( 
    char *file_name, 
    int flags, 
    mode_t mode )
{

    file *__file;
    size_t FileSize=-1;
    
    struct process_d *p;

    int __slot = -1;
    int Status = -1;
    int __ret = -1;

    void *buff;



    debug_print ("sys_read_file:\n");

    // Convertendo o formato do nome do arquivo.    
    // >>> "12345678XYZ"
    
    read_fntos ( (char *) file_name );


    // #bugbug
    // We need to search in the inode list. inode_table[]
    // If the file is found in the inode list, so we don't
    // need to load it again, just increment the counter.

    // #todo
    // fs_search_inode_table(file_name);

    // Searching for the file only on the root dir.

    Status = (int) KiSearchFile ( file_name, VOLUME1_ROOTDIR_ADDRESS );

    if (Status != 1)
    {
         //#debug
         printf ("sys_read_file: [FIXME] File not found!\n");
         refresh_screen();
         
         // Create a new one.
         if (flags & O_CREAT)
         {
             debug_print ("sys_read_file: [O_CREAT] Creating a new file\n"); 

             buff = (void*) kmalloc(1024);
             if ((void*)buff==NULL){
                 debug_print("sys_read_file: buff fail\n");
                 return -1; 
             }

             //++
             // See: sci/fs/write.c
             taskswitch_lock ();
             scheduler_lock ();

             __ret = (int) fsSaveFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, FAT16_ROOT_ENTRIES, 
                              (char *) file_name, 
                              (unsigned long) 2,      // size in sectors 
                              (unsigned long) 1024,   // size in bytes  
                              (char *) buff,          // buffer ?
                              (char) 0x20 );          // flag 

              scheduler_unlock ();
              taskswitch_unlock ();
              //--
              
              // Ok
              if (__ret == 0)
                  goto __go;
         }
         
         return (int) (-1);
    }

__go:

    //
    // Process.
    //
  
    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print ("sys_read_file: p\n");
        return -1;
    }

    if ( p->used != 1 || p->magic != 1234 ){
        debug_print ("sys_read_file: validation\n");
        return -1;
    }
    
    
    // Procurando um slot livre.
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){ goto __OK; }
    };
    
    panic ("sys_read_file: No slots!\n");

// Slot found.
__OK:

    if ( __slot < 0 || __slot >= 32 )
    {
        printf ("sys_read_file: Slot fail\n");
        refresh_screen();
        return (int) (-1);
    }
 
    // Struct
    
    __file = (file *) kmalloc( sizeof(file) );
    
    if ( (void *) __file == NULL ){
        printf ("sys_read_file: __file\n");
        refresh_screen();
        return -1;

    }else{
        __file->used = 1;
        __file->magic = 1234;
        __file->pid = (pid_t) current_process;
        __file->uid = (uid_t) current_user;
        __file->gid = (gid_t) current_group;
        
        // #bugbug [FIXME]
        // We need a type in read().

        __file->____object = ObjectTypeFile;
  
  
        // #todo:
        // We need to get the name in the inode.
        //__file->_tmpfname = NULL;
 

        __file->_lbfsize = BUFSIZ;
        __file->_r = 0;
        __file->_w = 0;
        __file->_file = __slot;
        __file->fd_counter = 1; //inicializando. 


        // #todo
        // Se ele não foi encontrado na lista de inodes
        // e tivemos que carrega-lo do disco, então
        // precisamos colocar ele na lista de inodes.. inode_table[]
        // Atenção: O arquivo será carregado logo abaixo.
        
        // #todo
        // atualizar a tabela  global de arquivos. file_table[]
    };
    

    //
    // buffer
    //

    // buffer padrão
    // #bugbug: open chama isso. E se o arquivo for maior que o buffer ?
    // open() precisa alocar outro buffer.
        
    __file->_base = (char *) kmalloc(BUFSIZ);
    
    if ( (void *) __file->_base == NULL ){
        printf ("sys_read_file: buffer fail\n");
        refresh_screen();
        return -1;
    }


    // File size.
    // #bugbug: OUT: 'unsigned long'
    FileSize = (size_t) fsRootDirGetFileSize( (unsigned char *) file_name );
    
    if (FileSize <= 0){
        printf ("sys_read_file: File size fail\n");
        refresh_screen();
        return (-1);
    }

    // Limits.
    if ( FileSize < __file->_lbfsize ){ FileSize = __file->_lbfsize; }

    // Limits.
    // Se o arquivo for maior que buffer dispon�vel.
    // Podemos almentar o buffer.
    if (FileSize > __file->_lbfsize)
    {
        // #bugbug: Provisório.
        // Limite - 1MB.
        if (FileSize > 1024*1024){
            printf ("sys_read_file: File size out of limits\n");
            printf ("%d bytes \n",FileSize);
            refresh_screen();
            return (-1);
        }
        
        // Allocate new buffer.
        __file->_base = (char *) kmalloc(FileSize);
        
        if ( (void *) __file->_base == NULL ){
            printf ("sys_read_file: Couldn't create a new buffer\n");
            refresh_screen();
            return -1;             
        }
 
        // Temos um novo buffer size.
        __file->_lbfsize = (int) FileSize;
    }

    // #paranoia.
    // Checando os limites novamente.
    // #bugbug: Provisório.
    // Limits - 1MB
    if (FileSize > 1024*1024){
        printf ("sys_read_file: File size out of limits\n");
        refresh_screen();
        return -1;
    }

    // #paranoia.
    // Checando base novamente.
    if ( (void *) __file->_base == NULL ){
        printf ("sys_read_file: buffer fail\n");
        refresh_screen();
        return -1;
    }

   // Pointer.
    __file->_p = __file->_base;
    
    //
    // Load.
    //
    
    // Carrega o arquivo na memória.
 
    Status = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                       VOLUME1_ROOTDIR_ADDRESS, 
                       32, //#bugbug: Number of entries.
                       file_name, 
                       (unsigned long) __file->_base,
                       __file->_lbfsize );

    if ( Status != 0 ){
        printf ("sys_read_file: fsLoadFile fail\n");
        refresh_screen();
        return -1;
    }

    
    // #bugbug
    // Agora é a hora de atualizarmos as tabelas ....
    // Depois de carregarmos o arquivo.
    
     
    //
    // Pointer. (mode)
    //
    
    // Ajusta o ponteiro para depois do tamanho do arquivo.
    // Dependendo do modo.
    
    // See:
    // https://linux.die.net/man/2/open

           /*
           O_RDONLY        open for reading only
           O_WRONLY        open for writing only
           O_RDWR          open for reading and writing
           O_NONBLOCK      do not block on open or for data to become available
           O_APPEND        append on each write
           O_CREAT         create file if it does not exist
           O_TRUNC         truncate size to 0
           O_EXCL          error if O_CREAT and the file exists
           O_SHLOCK        atomically obtain a shared lock
           O_EXLOCK        atomically obtain an exclusive lock
           O_NOFOLLOW      do not follow symlinks
           O_SYMLINK       allow open of symlinks
           O_FSYNC         write will save into the disk. :)
           */
      
      // Saving into de disk ?
      // You can use the O_FSYNC open mode to make write always 
      // store the data to disk before returning;    
          
          
     // Default ???
       
       
    //if (mode == 0)
    //{
          debug_print ("sys_read_file: default mode\n");
          __file->_p = __file->_base;
    //}


    // The file is opened in append mode. 
    // O offset fica no fim do arquivo.
    if ( mode & O_APPEND)        
    { 
        debug_print ("sys_read_file: O_APPEND\n");
        //__file->_p = __file->_base + s;
    }

    if ( mode & O_ASYNC )        
    { 
         debug_print ("sys_read_file: O_ASYNC\n");
    }

    /* 
    // Enable the close-on-exec flag for the new file descriptor.
    if ( mode & O_CLOEXEC )        
    { 
         debug_print ("sys_read_file: O_CLOEXEC\n");
    }
    */


    if ( mode & O_CREAT )        
    { 
         debug_print ("sys_read_file: O_CREAT\n");
    }
        
             
    
    // #importante
    // Se não liberarmos para leitura então read()
    // não poderá ler.
    
    __file->_flags = (__file->_flags | __SRD);
        

    // Salva o ponteiro.  
    // Ja checamos fd.
    p->Objects[__slot] = (unsigned long) __file;



    //printf ("done\n");
    //refresh_screen();
          
    //
    // Done.
    // Vamos retornar o fd.
    // Pois essa rotina � usada por open();
    //      

    debug_print ("sys_read_file: done\n");
                  
    return (int) __file->_file;
}




/*
 ********************************
 * fsLoadFileFromCurrentTargetDir:
 * 
 *     Carrega o diretório que está configurado como 'target dir' 
 * em algum lugar qualquer da memória. 
 *     Usa-se a estrutura current_target_dir pra gerenciar isso.
 */

int fsLoadFileFromCurrentTargetDir (void){

    int Ret = -1;
    int i=0;
    unsigned long new_address = 0;

    debug_print ("fsLoadFileFromCurrentTargetDir: Loading dir \n");

	//#bugbug
	//Isso 'e um limite para o tamanho do arquivo (apenas dir).
	//precisamos expandir isso.
	//aqui no m'aquimo o arquivo pode ter 4kb.
	//acho ques estamos falando somente de diret'orio aqui.

    new_address = (unsigned long) kmalloc (4096);

    if ( new_address == 0 ){
        debug_print ("fsLoadFileFromCurrentTargetDir: new_address\n");
        return -1;
    }


    // ??
    // Se o endereço atual falhar, resetamos ele.
    if ( current_target_dir.current_dir_address == 0 )
    {
        debug_print ("fsLoadFileFromCurrentTargetDir: current_target_dir.current_dir_address\n");

        // reset.
        current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;

        for ( i=0; i< 11; i++ ){
            current_target_dir.name[i] = '\0';
        };

        return -1;
    }

	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) old_dir_addr=(%x) #debug \n",
	//    current_target_dir.name, current_target_dir.current_dir_address );


    //++
    taskswitch_lock ();
    scheduler_lock ();

    Ret = (int) fsLoadFile ( VOLUME1_FAT_ADDRESS,  
                    current_target_dir.current_dir_address,    //src dir address 
                    32, //#bugbug: Number of entries.
                    (unsigned char *) current_target_dir.name, 
                    (unsigned long) new_address,
                    4096 );             //dst dir address

    scheduler_unlock ();
    taskswitch_unlock ();
    //--

    current_target_dir.current_dir_address = new_address;

	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) new_dir_addr=(%x) #debug \n",
	//   current_target_dir.name, current_target_dir.current_dir_address );


    debug_print ("fsLoadFileFromCurrentTargetDir: done\n");
    
    return (int) Ret;
}



/*
 *****************************
 * sys_write_file:
 *     Interface para salvar arquivo ou diretório.
 *     Isso pode ser usado para criar um diretório ou 
 * copiar um diretório. 
 */

// #todo:
// vamos fazer igual ao sys_read_file 
// e criarmos opções ... se possível.


// IN: 
// name, size in sectors, size in bytes, adress, flag.

int
sys_write_file ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag )  
{
    int __ret = -1;

    debug_print ("sys_write_file:\n");

    //++
    // See: sci/fs/write.c
    taskswitch_lock ();
    scheduler_lock ();

    __ret = (int) fsSaveFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, FAT16_ROOT_ENTRIES,
                      (char *) file_name,    
                      (unsigned long) file_size,       
                      (unsigned long) size_in_bytes,  
                      (char *) file_address,          
                      (char) flag );                  

    scheduler_unlock ();
    taskswitch_unlock ();
    //--

    debug_print ("sys_save_file: done\n");
    
    return __ret;
}


//
// Create
//

int fs_create_empty_file ( char *file_name, int type ){

    file *f;
    
    char buffer[512];
    int number_of_sectors = 1;
    int size_in_bytes = 512;  
    int __ret;
    
    f = (file *) kmalloc( sizeof(size_in_bytes) );
    
    if ( (void *) f == NULL ){
        //todo: message
        return -1;
    }
        
        
    //f->type = type;
    // #todo: fd ...
    
    __ret = (int) fsSaveFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, FAT16_ROOT_ENTRIES,
                    (char *) file_name,    
                    (unsigned long) number_of_sectors,       
                    (unsigned long) size_in_bytes,  
                    (char *) &buffer[0],          
                    (char) 0x20 );  //0x20 = file.                  



    return __ret;
}

// Service 43
int sys_create_empty_file ( char *file_name )
{
    int __ret=0;
    char buffer[512];
    int number_of_sectors = 1;
    int size_in_bytes = 512;  
    
    debug_print ("sys_create_empty_file:\n");
    
    //#test
    read_fntos ( (char *) file_name );
    
    // See: write.c
    __ret = (int) fsSaveFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, FAT16_ROOT_ENTRIES,
                    (char *) file_name,    
                    (unsigned long) number_of_sectors,       
                    (unsigned long) size_in_bytes,  
                    (char *) &buffer[0],          
                    (char) 0x20 );  //0x20 = file.                  


    return __ret;
}



int fs_create_empty_directory ( char *dir_name, int type )
{
    int __ret=0;

    file *f;

    char buffer[512];
    int number_of_sectors = 1;
    int size_in_bytes = 512;  

    f = (file *) kmalloc( sizeof(size_in_bytes) );
    
    if ( (void *) f == NULL ){
        //todo: message
        return -1;
    }
   
   
    //f->type = type;
    // #todo: fd ...
    
    __ret = (int) fsSaveFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, FAT16_ROOT_ENTRIES,
                    (char *) dir_name,    
                    (unsigned long) number_of_sectors,       
                    (unsigned long) size_in_bytes,  
                    (char *) &buffer[0],          
                    (char) 0x10 );  //0x10 = directory.                  



    return (int) __ret;
}


// Service 44
int sys_create_empty_directory ( char *dir_name )
{
    int __ret=0;
    char buffer[512];
    int number_of_sectors = 1;
    int size_in_bytes = 512;  
    
    debug_print ("sys_create_empty_directory:\n");
    
    //#test
    read_fntos ( (char *) dir_name );

     // See: write.c
    __ret = (int) fsSaveFile ( VOLUME1_FAT_ADDRESS, VOLUME1_ROOTDIR_ADDRESS, FAT16_ROOT_ENTRIES,
                    (char *) dir_name,    
                    (unsigned long) number_of_sectors,       
                    (unsigned long) size_in_bytes,  
                    (char *) &buffer[0],          
                    (char) 0x10 );  //0x10 = directory.                  



    return (int) __ret;
}





//#todo
//credits: Chicago OS.
/*
int fs_count_separations (char *path)
int fs_count_separations (char *path){

    int count = 0;

    int i;
    int __len = 0;


    __len = (int) strlen ( (const char *) path );
    
    for ( i=0; i < __len; i++ )
    {
		if (path[i] == '/')
		{
			count++;
		}
    };


    return (int) count;
}
*/


/*
int fat16_create_new_directory ( ... )
int fat16_create_new_directory ( ... )
{}
*/

/*
int fat16_create_new_file ( ... );
int fat16_create_new_file ( ... )
{}
*/



//
// End.
//

