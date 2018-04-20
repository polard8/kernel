

//vfs.c

// Virtual File System


// sistema de arquivos virtual gerenciado pelo kernel base.


#include <kernel.h>

//int dummy_vfs;


void vfsInit()
{
	//
	// Inicializando a estrutura do VFS.
	//
	
	//Nosso objetivo é que tenha apenas uma estrutura 
	//para o VFS.
	
	//@todo: object stuff
	
	VFS_INFO.used = 1;
	VFS_INFO.magic = 1234;
	
	VFS_INFO.status = VFSStatusInitialized;
	
	VFS_INFO.name = "VFS NAME";
	VFS_INFO.description = "VIRTUAL FILE SYSTEM";
	VFS_INFO.help_string = "Virtual File System help string @todo.";
	VFS_INFO.vfs = NULL;  //Nenhum diretório aqui.

	
	printf("Initilizing VFS ... \n");
};


