


#ifndef  __STORAGE_H
#define  __STORAGE_H    1


struct storage_d
{

    // Disk.
    // System disk
    // The disk where the system is installed.

    struct disk_d *system_disk;


    // Volume.
    // vfs volume.
    // Boot volume.
    // System volume.

    struct volume_d     *vfs_volume;
    struct volume_d    *boot_volume;
    struct volume_d  *system_volume;


    // vfs
    // virtual file system
    
    //struct vfs_d *vfs;


    //
    //  fs ???
    //
    
    // #bugbug
    // Talvez podemos encontrar issa informação
    // na estrutura de volume.

    //file system
    //Ponteiro para o sistema de arquivos atual.
    //Se isso for NULL, então não temos sistema de arquivos.
    struct filesystem_d *fs;



    //
    // file ??
    //

	//Stream 
	//ponteiro para o arquivo atual,
	//que pode ser um arquivo, um diretório, um dispositivo ...
	//tudo seguindo definições unix-like para esse tipo de estrutura.
	//Na inicialização uma das estruturas deve ser apontada aqui.
	
	//#importante 
	//devemos permitir que os programas em user mode tenham acesso 
	//as streams gerenciadas pelo kernel.
	
	//na estrutura de processo devemos indicar 
	//quais são as streams gerenciadas pelo kernel que 
	//o processo tem acesso, também devemos indicar quais são 
	//as streams abertas pelo processo.

    file *__file;
};


// Essa será a esttrutura usada para saber informações sobre o 
// sistema de arquivos atual e gerenciar o sistema de arquivos atual.

struct storage_d *storage;
//struct storage_d *CurrentStorage;
// ...


#endif    


