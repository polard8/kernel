
// system.c

#include <kernel.h>    

// global
unsigned long sys_time_hz=0;
static char *default_user_name = DEFAULT_USERNAME;

static void __a_soft_place_to_fall(void);

// ====================================

/*
 * doGetSystemMetrics:
 *     Retorna informações sobre o sistema.
 *     #todo: 
 *     Criam um enum para essa função, aqui mesmo nesse arquivo.
 */

unsigned long doGetSystemMetrics(int index)
{

    // We are trying to have more system calls. sc80 sc81 sc82.
    // These system calls uses different set of selectors.

    //print ("#debug: doGetSystemMetrics: i={%d} \n",index)

    if (index <= 0){
        return (unsigned long) 0;
    }

    switch (index){

        //screen width.
        case 1:
            return (unsigned long) screenGetWidth();
            break;

        //screen height.
        case 2:
            return (unsigned long) screenGetHeight();
            break;

        //cursor width in pixels.
        case 3:
            return (unsigned long) CONSOLE_TTYS[fg_console].cursor_width_in_pixels;
            break;

        //cursor height in pixels.
        case 4:
            return (unsigned long) CONSOLE_TTYS[fg_console].cursor_height_in_pixels;
            break;

        // mouse pointer width.
        case 5:
            return (unsigned long) g_mousepointer_width;
            break;

        // mouse pointer height. 
        case 6:
            return (unsigned long) g_mousepointer_height;
            break;

        // char width.
        case 7:
            return (unsigned long) get_char_width();
            break;

        // char height.
        case 8:
            return (unsigned long) get_char_height();
            break;

        case 9:
            return (unsigned long) gSavedBPP;
            break;

        // screen buffers

        // lfb pa
        case 10:
            return (unsigned long) g_frontbuffer_pa;
            break;

        // lfb va
        case 11:
            return (unsigned long) g_frontbuffer_va;
            break;

        // main backbuffer va
        case 12:
            return (unsigned long) g_backbuffer_va;
            break;

        //20
        // mouse x    
        case SM_GETMOUSEX:
            //#bugbug: Pegando informações com o driver de mouse.
            //return (unsigned long) ps2_mouse_get_info (3); 
            panic ("doGetSystemMetrics: SM_GETMOUSEX #todo \n");
            break;

        //21
        //mouse y
        case SM_GETMOUSEY:
           //#bugbug: Pegando informações com o driver de mouse.
            //return (unsigned long) ps2_mouse_get_info (4); 
            panic ("doGetSystemMetrics: SM_GETMOUSEY #todo\n");
            break;

        // Ram support

        // base memory
        case 30:
            return (unsigned long) memorysizeBaseMemory;
            break;
            
        // extended - base
        case 31:
            return (unsigned long) memorysizeOtherMemory;
            break;

        // extended memory
        case 32:
            return (unsigned long) memorysizeExtendedMemory;
            break;

        // total = base + other + extended 
        case 33:
            return (unsigned long) memorysizeTotal;
            break;

        // used
        case 34:
            return (unsigned long) memorysizeUsed;
            break;

        // free   
        case 35:
            return (unsigned long) memorysizeFree;
            break;  

         // Kernel Heap support.

        case 40:
            return (unsigned long) kernel_heap_start;
            break;

        case 41:
            return (unsigned long) kernel_heap_end;
            break;

        case 42:
            return (unsigned long) g_available_heap;
            break;

         // Kernel Stack support.

        case 50:
            return (unsigned long) kernel_stack_start;
            break;

        case 51:
            return (unsigned long) kernel_stack_end;
            break;

        case 52:
            return (unsigned long) kernel_stack_start_pa;
            break; 

        // Used memory support

        case 60:
            return (unsigned long) mm_used_ring0_area;
            break;

        case 61:
            return (unsigned long) mm_used_ring3_area;
            break;

        case 62:
            return (unsigned long) mm_used_backbuffer;
            break;

        case 63:
            return (unsigned long) mm_used_pagedpool;
            break;

        case 64:
            return (unsigned long) mm_used_heappool;
            break;

        case 65:
            return (unsigned long) mm_used_extraheap1;
            break;

        case 66:
            return (unsigned long) mm_used_extraheap2 ;
            break;

        case 67:
            return (unsigned long) mm_used_extraheap3;
            break;

        // Dispatch critéria.

        case 70:
            return (unsigned long) DispatchCountBlock->SelectIdleCount;
            break;

        case 71:
            return (unsigned long) DispatchCountBlock->SelectInitializedCount;
            break;

        case 72:
            return (unsigned long) DispatchCountBlock->SelectNextCount;
            break;

        case 73:
            return (unsigned long) DispatchCountBlock->SelectCurrentCount;
            break;

        case 74:
            return (unsigned long) DispatchCountBlock->SelectAnyCount;
            break;

        case 75:
            return (unsigned long) DispatchCountBlock->SelectIdealCount;
            break;

        case 76:
            return (unsigned long) DispatchCountBlock->SelectDispatcherQueueCount;
            break;

        // System type by memory size;
        case 90:
            return (unsigned long) g_mm_system_type;
            break;

        // Profiler ... (reservar vários números.)

        case 100:
            return (unsigned long) g_profiler_ints_irq0;
            break;

        case 101:
            return (unsigned long) g_profiler_ints_irq1;
            break;

        case 102:
            return (unsigned long) g_profiler_ints_irq2;
            break; 

        case 103:
            return (unsigned long) g_profiler_ints_irq3;
            break;

        case 104:
            return (unsigned long) g_profiler_ints_irq4;
            break;

        case 105:
            return (unsigned long) g_profiler_ints_irq5;
            break;

        case 106:
            return (unsigned long) g_profiler_ints_irq6;
            break;              

        case 107:
            return (unsigned long) g_profiler_ints_irq7;
            break;

        case 108:
            return (unsigned long) g_profiler_ints_irq8;
            break;

        case 109:
            return (unsigned long) g_profiler_ints_irq9;
            break;

        case 110:
            return (unsigned long) g_profiler_ints_irq10;
            break;

        case 111:
            return (unsigned long) g_profiler_ints_irq11;
            break;

        case 112:
            return (unsigned long) g_profiler_ints_irq12;
            break;

        case 113:
            return (unsigned long) g_profiler_ints_irq13;
            break;

        case 114:
            return (unsigned long) g_profiler_ints_irq14;
            break;

        case 115:
            return (unsigned long) g_profiler_ints_irq15;
            break;

        // Interrupção de serviços do sistema.
        case 117:
            return (unsigned long) g_profiler_ints_gde_services;
            break; 

       // PIT
       // See: hal/pit.h

       // jiffies.
       // total ticks
       case 118:  return (unsigned long) jiffies;  break;

       // seconds
       // por quantos segundos o sistema esta rodando
       // jiffies/sys_time_hz
       case 119:  return (unsigned long) seconds;      break;
       
       // Por quantos ms o sistema esta rodando.
       case 120:  return (unsigned long) sys_time_ms;  break;

       // pit frequency
       case 121:  return (unsigned long) sys_time_hz;  break;

        // ...

       // gramado mode, gamemode.
       // jail, p1, home ...
       case 130:  return (unsigned long) current_mode;  break;

       // When a thread is running to call this service,
       // so, this thread is the current thread.
       // But, current for what processor?
       case 140:  
           //return (unsigned long) current_process;
           return (unsigned long) get_current_process(); //#bugbug mask?  
           break;
       
       case 141:  
           return (unsigned long) current_thread;   
           break;

       // return the number of processors.
       case 150:  
           return (unsigned long) (g_processor_count & 0xFFFFFFFF);
           break;
       //case 151:  break;

        // 200 ~ 2xx window server info.
        // See: ws.h

        // #bugbug
        // Quando estamos dentro do kernel por entrarmos via interrupçao de teclado,
        // esses valores estao certos,
        // mas quando estamos dentro do kernel, por entrarmos via interrupçao de sistema,
        // esses valores estao errados.
        // #porque
        // ?? seria algum problema de selecao de diretorio de paginas,
        // ou de configuraçao de registrador de segmento.
        // podemos checar se a configuraçao dos segmentos de dados esta
        // certa na hora da entrada da interrupçao de sistema.
        // o problema eh que mudarmos o registrador de segmento, entao
        // o kernel nao podera mais pegar as informaçoes que estao em ring3. certo??
        // See:
        // sw.asm
        
        case 200:
           //printf ("#type: %d\n",WindowServer_type);
           //refresh_screen();
           return (unsigned long) WindowServer_type;
           break;

        case 201:
           //printf ("#pid: %d\n",WindowServer_pid);
           //refresh_screen();
           return (unsigned long) WindowServer_pid; 
           break;

        case 202:
           //printf ("#virtual_console: %d\n",WindowServer_virtual_console);
           //refresh_screen();
           return (unsigned long) WindowServer_virtual_console; 
           break;

        case 203:
           //printf ("#initialized: %d\n",WindowServer_initialized);
           //refresh_screen();
           return (unsigned long) WindowServer_initialized; 
           break;

// is quemu
        case 300:
            return (unsigned long) isQEMU();
            break;

        // ...

        default:
            goto done;
            break;
    };

done:
    return (unsigned long) 0;
}


static void __a_soft_place_to_fall(void)
{
    while (TRUE)
    { 
        asm ("cli");
        //asm ("mwait");   
        asm ("hlt");
    };
}

// The kernel hangs.
void die(void)
{
    if (Initialization.serial_log == TRUE){
        PROGRESS("die:\n");
    }
    if (Initialization.console_log == TRUE){
        printf("die: System Halted\n");
        refresh_screen();
    }
    __a_soft_place_to_fall();
    die();
}


/*
 * doSetupVersion:
 *     Setup version info.     
 */
// See:
// config/version.h
// config/u.h
// system.h

void doSetupVersion(void)
{

// Global structure
// #todo:
// Isso deve ser considerado um erro fatal,
// pois existem aplicações que dependem da versão do sistema 
// para funcionarem corretamente.. 

    Version = (void *) kmalloc( sizeof(struct version_d) );

    if ( (void *) Version == NULL ){
        panic("doSetupVersion: Version");
    }

    Version->Major = VERSION_MAJOR;
    Version->Minor = VERSION_MINOR;
    Version->Build = VERSION_BUILD;

// Global structure
// #todo:
// Isso deve ser considerado um erro fatal,
// pois existem aplicações que dependem da versão do sistema 
// para funcionarem corretamente.. 

    VersionInfo = (void *) kmalloc ( sizeof(struct version_info_d) );

    if ( (void *) VersionInfo == NULL ){
        panic ("doSetupVersion: VersionInfo\n");
    }

// Global structure
// Colocando na estrutura System se ela for válida.

    if ( (void *) System == NULL ){
        panic ("doSetupVersion: System\n");
    }

    if ( (void *) System != NULL )
    {
        if ( System->used == TRUE && System->magic == 1234 )
        {
            System->version      = (void *) Version;
            System->version_info = (void *) VersionInfo;
        }
        //Nothing
    }
}


/*
 * init_executive:
 *     Initialize the kernel executive.
 *     Architecture (independent) inicialization. 
 */
// called by I_Init().
// Probe PCI devices.
// see: /dev/pci/
// Initialize rtc support.
// see: /hal/x86_64/rtc.c 
// Initialize ATA support.
// #importante: 
// Só depois de inicializarmos o ata é que 
// podemos carregar algum arquivo.
// #importante
// Nessa hora ja temos as estruturas de disk e volume inicializadas.
// entao as estruturas usadas pelo driver ata, pode
// se registrar em disk ou volume.
// see: /dev/ata/atainit.c
// OUT: return TRUE if its ok.

int init_executive(void)
{
// Initialize pci, rtc and ata.

    int Status = FALSE;

    debug_print ("init_executive:\n");
    Initialization.executive_checkpoint = FALSE;
    init_pci();
    init_rtc();
    ataDialog ( 1, FORCEPIO, FORCEPIO );
    Initialization.executive_checkpoint = TRUE;

    return TRUE;
}

