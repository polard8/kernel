/*
 * File: pages.c
 *
 *     Pre-mapping the some memory regions.
 *     The is gonna be changed by the base kernel.
 *     We need this to compile the base kernel 
 * against the 0xC0000000 address.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     ...
 */


#include <bootloader.h>


void load_pml4_table(void *phy_addr)
{
    asm volatile (" movl %0, %%cr3 " :: "r" (phy_addr) );
}

// PAE and PGE
void enable_pae()
{
    // PAE and PGE
    asm volatile ( " movl %%cr4, %%eax; "
                   " orl $0x20, %%eax;  "
                   " movl %%eax, %%cr4  " :: );
}

void page_enable()
{
    asm volatile ( " movl %%cr0, %%eax;      "
                   " orl $0x80000000, %%eax; "
                   " movl %%eax, %%cr0       " :: );
}




/*
 ***************************************************
 * SetUpPaging:
 * 
 *     Mapping.
 *
 * In this function:
 *     (Phase 1) Endereços da memória físicas acessíveis em Kernel Mode. 
 *     (Phase 2) Inicializando o diretório.
 *     (Phase 3) Cria tabelas de páginas e coloca o ponteiro de cada uma 
 * delas na sua respectiva entrada de diretório.
 *     (Phase 4) **** CRIANDO OUTROS DIRETÓRIOS ****
 *
 * @diretorio:
 *   boot_pd0 = 0x9C000.
 *    
 *   Page directory do kernel.
 *
 * Obs: Esse diretório criado será usado pelas primeiros processos durante
 * essa fase de construção do sistema. O ideal é um diretório por processo.
 *      Toda vez que o Kernel inicia a execução de um processo, ele deve 
 * carregar o endereço do diretório do processo em CR3. Por enquanto só tem 
 * um diretório criado e todos os processos estão definindo o diretório do
 * Kernel como sendo seu próprio. Ou seja, eles podem usar as mesmas tabelas
 * de páginas que o processo kernel usa. O problema é que com isso os 
 * processos precisam ter endereço virtual diferentes. Quando cada processo
 * tiver seu próprio diretório então eles poderão ter o mesmo endereço virtual.
 *
 * @todo: Esses endereços precisam ser registrados em variáveis globais ou
 * dentro de uma estrutura para serem passados para o Kernel.
 * 
 * Obs: Essa deve ser uma interface que chama as rotinas de configuração de 
 * paginação. (Mapeamento). 
 *
 * Obs: 
 * Essa configuração inicial feita no Boot Loader, não impede o Kernel de 
 * refazer as configurações básicas de paginação. O fato é que o kernel será o 
 * gerenciador de páginas de memória. O que não impede de haver gerenciamento
 * um user mode.
 * 
 * History:
 *     2015 - Created by Fred Nora.
 *     ...
 */

extern void go_to_kernel(void);

int SetUpPaging (){

    unsigned int i=0;


    // 9 9 9 9 12
    // Agora as tabelas possuem 512 entradas,
    // pois é isso o que dá pra ter com apenas 9 bits.


    // Agora o addr de cada tabela é de 52 bits, os outros 12 bits são reservados.
    // Antes cada entrada era de 4 bytes, agora é de 8 bytes.
    // Nesse caso a tabela continua do mesmo tamanho, mas agora com 512 entradas de 8

	//
	// (Phase 1) 
	// Endereços da memória físicas acessíveis em Kernel Mode.
	//

	//
	// Kernel.
	//

    // Address. para os 2 primeiros mega da memória fisica.
    // Base, 0x100000, para o kernel que começa no primeiro mega.
    unsigned long kernel_address = 0;           //Início da memória RAM.                
    unsigned long kernel_base = KERNEL_BASE;    //Início da imagem do kernel.    

    //
    // (Phase 2) 
    // Endereços da memória físicas acessíveis em User Mode.
    //

    // User, 0x00400000.
    unsigned long user_address = USER_BASE;

    // VGA, Físico=0x000B8000.
    unsigned long vga_address = VM_BASE;   

    // VESA LFB, foi passado pelo Boot Manager.
    unsigned long lfb_address  = (unsigned long) g_lbf_pa;

    // backbuffer: endereço físico provisório para o backbuffer
    // BUFFER, provisório. @todo: Mudar. 
    // (para sistemas com pouca memória.)
    // 16mb. (16*1024*1024) = 0x01000000.
    unsigned long buff_address  = (unsigned long) 0x01000000; 


    //
    // DIRECTORY:
    // Diretórios de páginas.
    // Esse valor é salvo em cr3. Cada diretório tem seu endereço.
    // Esse diretório, configurado aqui no Boot Loader é o mesmo usado 
	// pelo Kernel.
	//
	// Obs: 
	// A idéia é que os diretório sejam criados em ordem decrescente.
	// Os espaços entre os diretório serão preenchidos com páginas 
	// avulsas. Depois, no kernel, haverá área de alocação para 
	// diretórios e páginas.
	//
	// Teste:
	// Criando diretórios para os primeiros processos do sistema. 
	// (antes de 32MB).
    //
	// Obs: Essa área onde estão os diretórios é uma área desprotegiada ainda.
	// Obs: O kernel está reconfigurando e usando outro endereço para o 
	// diretório de páginas.
	//
	// @todo: Alertar o kernel sobre esses endereços de diretórios.
	//


// =====================================
// PML4, PDPT, PD, PT
// PML4 - Page Map Level 4
// PDPT - Page Directory Pointer Table
// PD   - Page Directory
// PT   - Page Table

    // level 4
    unsigned long *boot_pml4  = (unsigned long *) (0x01000000 - 0x00700000);
    // level 3
    unsigned long *boot_pdpt  = (unsigned long *) (0x01000000 - 0x00800000);
    // level 2
    unsigned long *boot_pd0   = (unsigned long *) (0x01000000 - 0x00900000);
    // level 1
    // a lot of page tables in the level 1.


	// TABLES: 
	// Tabelas de páginas.
	// Uma tabela para cada área de memória que se deseja usar.
	// Usando endereços decrescentes.

    // ptKM  - First 2MB.
    // ptKM2 - The kernel image.
    // ptUM  - User mode area for application. (Not used yet)
    // ptVGA - Legacy VGA memory.
    // ptLFB - Linear Frame Buffer. (Front buffer)
    // ptBACKBUFFER - The backbuffer.

    unsigned long *ptKM  = (unsigned long *) 0x0008F000;
    unsigned long *ptKM2 = (unsigned long *) 0x0008E000;
    unsigned long *ptUM  = (unsigned long *) 0x0008D000;
    unsigned long *ptVGA = (unsigned long *) 0x0008C000;
    unsigned long *ptLFB = (unsigned long *) 0x0008B000;
    unsigned long *ptBACKBUFFER = (unsigned long *) 0x0008A000;
    // ...


//
// ==================================================
//
    // Clear levels 4, 3 and 2.

    // Clear level 4
    for ( i=0; i < 512; i++ )
    {
        boot_pml4[i*2   ] = (unsigned long) 0 | 2;
        boot_pml4[i*2+1 ] = (unsigned long) 0;
    };

    // Clear level 3
    for ( i=0; i < 512; i++ )
    {
        boot_pdpt[i*2   ] = (unsigned long) 0 | 2;
        boot_pdpt[i*2+1 ] = (unsigned long) 0;
    };

    // Clear level 2
    for ( i=0; i < 512; i++ )
    {
        boot_pd0[i*2   ] = (unsigned long) 0 | 2;
        boot_pd0[i*2+1 ] = (unsigned long) 0;
    };


//
// ============================
//
    // Pointing the 'page directory' address 
    // at the first entry in the 'page directory pointer table'.

    boot_pdpt[0*2]   = (unsigned long) &boot_pd0[0];
    boot_pdpt[0*2]   = (unsigned long) boot_pdpt[0*2] | 3;
    boot_pdpt[0*2+1] = 0; 

    // Pointing the 'page directory pointer table' address 
    // at the first entry in the 'boot_pml4'.

    boot_pml4[0*2]   = (unsigned long) &boot_pdpt[0];
    boot_pml4[0*2]   = (unsigned long) boot_pml4[0*2] | 3; 
    boot_pml4[0*2+1] = 0; 


//
// ============================
//

//
// PAGE TABLES.
//

    // Vamos criar algumas pagetables e apontá-las
    // como entradas no diretório 'boot_pd0'.

// =======================================
// Primeiros 2MB.
// 0virt
Entry_0:
	/*
	 * kernel mode pages 
	 * =================
	 * (kernel mode)(0fis = 0virt).
	 *
	 * Configurando o início da memória RAM
	 * como área em kernel mode.
	 *
	 * + Mapeando os primeiros 2MB da memória.  
	 * + Preenchendo a tabela km_page_table.
	 * + A entrada '0' do diretório aponta para
	 *   uma tabela que mapeia os primeiros 4 mega 
	 *   de endereço virtual.
	 *
	 * 'kernel_address' é o início da memória RAM.
	 *  Cada pagina tem 4KB.
	 */
	 
	 // #importante
	 // Essa primeira entrada esta funcionando.
	 // Conseguimos usar essa identidade 1:1,
	 // tanto aqui no bl, quanto no kernel.

    for ( i=0; i < 512; i++ )
    {
        ptKM[i*2]   = kernel_address | 3; 
        ptKM[i*2+1] = 0;
        kernel_address = kernel_address + 4096;
    };
    // Criando a primeira entrada do diretório.
    // Isso mapeia os primeiros 2MB da memória RAM.
    boot_pd0[0*2] = (unsigned long) &ptKM[0];
    boot_pd0[0*2] = boot_pd0[0*2] | 3;    //Configurando atributos.
    boot_pd0[0*2+1] = 0;


// =======================================
// Uma área em user mode.
// 0x00200000vir - Começa na marca de 32mb.
Entry_1:

	/*
	 * user mode pages 
	 * ===============
	 * (400000fis = 400000virt).
	 *
	 * Configurando uma área de memória em user mode,
	 * usada por processos em user mode.
	 * Mapear 2MB da memória começando em 400000fis. 
	 * (user mode).
	 * user_address = (400000fis = 400000virt).
	 *
	 */

    for (i=0; i < 512; i++)
    {
        ptUM[i*2]   = user_address | 7;    //0111 em binário.
        ptUM[i*2+1] = 0;
        user_address = user_address + 4096;     //4096 = 4KB.
    };
    //Criando a entrada número 1 do diretório.
    boot_pd0[1*2]   = (unsigned long) &ptUM[0];
    boot_pd0[1*2]   = (unsigned long) boot_pd0[1*2] | 7;    //Configurando atributos.
    boot_pd0[1*2+1] = 0; 


// ============================
// vga
Entry_2:
    /*
	 * User Mode VGA pages: 
	 * ===================
	 * (0xB8000fis = 800000virt).
	 * 
	 * Mapeando a área de memória usada pela memória
	 * de vídeo em modo texto, 0xB8000.
	 *
	 * Mapear 2MB da memória começando em B8000fis.
	 *
	 * Obs:
	 *     Aqui, na verdade não precisaria configurar 4 megas, 
	 *     apenas o tamanho da memória de vídeo presente em 0xb8000.
	 * vga_address = 0xB8000.
	 */

    for ( i=0; i < 512; i++ )
    {
        ptVGA[i*2]   = vga_address | 7;    //0111 em binário.
        ptVGA[i*2+1] = 0;
        vga_address  = vga_address + 4096;       //4KB.
    };
    //Criando a entrada número 2 no diretório.
    boot_pd0[2*2] = (unsigned long) &ptVGA[0];
    boot_pd0[2*2] = boot_pd0[2*2] | 7;    //Configurando atributos.
    boot_pd0[2*2+1] = 0; 


// =====================================
// A imagem do kernel.
// 0x30000000virt - Começa na marca de 1MB da memória física.
Entry_384:

    // #bugbug
    // Essa não é possivel pois temos o limite de 512 entradas.

	/*
	 * kernel mode pages 
	 * =================
	 * (0x100000fis = 0xc0000000virt).
	 *  
	 *      possivelmente 0x30000000
	 *      mas precisamos checar, pois isso não esta funcionando.
	 *      precisamos encontrar esse endereço virtual.
	 * 
	 * Configurando a área de memória onde ficará a imagem do kernel.
	 * Isso mapeia 2MB começando do primeiro mega. 
	 * (kernel mode).
	 *
	 * Preenchendo a tabela km_page_table.
	 * 'kernel_base' é o endereço físico da imagem do kernel.
	 */

    for ( i=0; i < 512; i++ )
    {
        ptKM2[i*2]   = kernel_base | 3;    //0011 binário.
        ptKM2[i*2+1] = 0;
        kernel_base  = kernel_base + 4096;       //4KB.
    };
    //Criando a entrada de número 768 do diretório.
    boot_pd0[384*2] = (unsigned long) &ptKM2[0];
    boot_pd0[384*2] = (unsigned long) boot_pd0[384*2] | 3;    //Configurando atributos.
    boot_pd0[384*2+1] = 0;

    //   1 1000 0 000
    // | 0 0000 0 000 | 0 0000   0000  | 0000 0000 0000
    //   00|000 0|000   0 0000 | 0000    0000 0000 0000
    //   30000000
    // então a entrada 384 aponta para 0x30000000      


//===========================================
// frontbuffer - LFB
// 0x30200000virt
Entry_385:

    /*
     * user mode LFB pages 
     * ===================
	 * (0X??fis = 0xC0400000virt).
	 * 
	 * O endereço linear do lfb é  agora. ?? 0x30200000
	 *
	 * Mapear 2MB à partir do endereço configurado
	 * como início do LFB.
	 * 
	 * O Boot Manager configurou VESA e obteve o endereço do LFB.
	 * O Boot Manager passou para o Boot Loader esse endereço.
	 * Mapeando 2MB da memória fisica começando no 
	 * endereço passado pelo Boot Manager.
	 * O endereço de memória virtual utilizada é 0xC0400000.
	 * lfb_address = Endereço do LFB, passado pelo Boot Manager.
	 *
	 */

    for ( i=0; i < 512; i++ )
    {
        ptLFB[i*2]   = lfb_address | 7;    //0111 em binário.
        ptLFB[i*2+1] = 0;
        lfb_address  = lfb_address + 4096;       //4KB.
    };
    //Criando a entrada número 769 do diretório.
    boot_pd0[385*2] = (unsigned long) &ptLFB[0];
    boot_pd0[385*2] = boot_pd0[385*2] | 7;    //Configurando atributos.	
    boot_pd0[385*2+1] = 0; 


// ===================================================
// backbuffer
// 0x30400000virt
Entry_386:
    /*
	 * user mode BUFFER1 pages 
	 * =======================
	 * (0X??fis = 0xC0800000virt) (BackBuffer). 0x30800000
	 * 
	 * Esse é o backbuffer para a memória de vídeo.
	 * O conteúdo desse buffer é transferido para o LFB. 
	 * O endereço de memória virtual utilizada é 0xC0800000.
	 * buff_address = 0x01000000. (16MB), provisório.
	 * //16mb. (16*1024*1024) = 0x01000000.
	 */

    for ( i=0; i < 512; i++ )
    {
        ptBACKBUFFER[i*2] = buff_address | 7;    //0111 em binário.
        ptBACKBUFFER[i*2+1] = 0;
        buff_address    = buff_address + 4096;       //4KB.
    };
    //Criando a entrada número 770 do diretório.
    boot_pd0[386*2] = (unsigned long) &ptBACKBUFFER[0];
    boot_pd0[386*2] = (unsigned long) boot_pd0[386*2] | 7;    //Configurando atributos.
    boot_pd0[386*2+1] = 0;


    //breakpoint
    printf ("SetUpPaging: tables done\n");
    //refresh_screen();
    //while(1){}


    // ==============================================

    // __asm__ __volatile__("cli");


//
// PAE
//

// pae
    printf ("SetUpPaging: enable_pae\n");
    //refresh_screen();

    enable_pae();

    //refresh_screen();
    //while(1){}


//
// CR3
//

    // Point cr3 to boot_pml4.
    
    printf ("SetUpPaging: load_pml4_table\n");
    refresh_screen();
    
    load_pml4_table( &boot_pml4[0] );


//
// MSR
//

    // ==============================================
    printf ("SetUpPaging: cpuSetMSR\n");
    refresh_screen();

    // #todo
    // long mode exige uma configuração usando msr.
    //int msrStatus = FALSE;
    //msrStatus = cpuHasMSR();
    //in: MSR, LO, HI
    cpuSetMSR( 0xC0000080, 0x100, 0 );

    // Nesse caso habilitamos SYSCALL/SYSRET
    // #ok: Testado no qemu
    //cpuSetMSR( 0xC0000080, 0x101, 0 );


    //refresh_screen();
    //while(1){}


// Enable paging.
    //printf ("SetUpPaging: page_enable\n");
    //refresh_screen();
    
    
    // #important:
    // Adiamos isso, o assembly vai fazer isso.
    // Pois no momento em que configurarmos isso, o long mode
    // estará habilitado.
    // page_enable();

    // #bugbug
    // Não podemos chamar rotina alguma antes de configurarmos
    // os registradores.
    
    // vamos tentar fazer isso quando saltarmos para o kernel
    //unsigned long *fb = (unsigned long *) 0xC0400000; 
    //fb[0] = 0xFF00FF;

    // nao podemos chamar rotina alguma aqui,
    // somente retornar.
    // os registradores estao bagunçados.

    //printf ("SetUpPaging: [breakpoint] DONE \n");
    printf ("SetUpPaging: DONE, returning to assembly in head.s \n");

    refresh_screen();


//
// Go to kernel
//

    // See: head.s

    go_to_kernel();


    // Not reached
    while(1){}

    return 0;

    // == cut here ==================
}



//
// End.
//

