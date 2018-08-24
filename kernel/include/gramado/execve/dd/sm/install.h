/*
 * Arquivo: install.h 
 *
 * Descrição:
 *     Header para rotinas de instalação de partes do sistema, 
 * BootManager, mbr, metafile ...
 *
 *      @todo: Talvez essas rotinas não devam ficar dentro do Kernel Base.
 *
 * Versão 1.0, 2015.
 */


void install_os();
void install_boot_manager();
void install_bootmanager_stage1();
void install_bootmanager_stage2();
void install_bootmanager_metafile();

//
//fim.
//
