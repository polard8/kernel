
// sys.c

#include <kernel.h> 



// See:
// kunistd.h
// https://man7.org/linux/man-pages/man2/alarm.2.html
// alarm() returns the number of seconds remaining until any
//       previously scheduled alarm was due to be delivered, or zero if
//       there was no previously scheduled alarm.

unsigned long sys_alarm(unsigned long seconds)
{
    struct thread_d *t;
    unsigned long old=0;
    unsigned long seconds_remaining=0;

    unsigned long extra_ms=0;


    if (current_thread<0 || current_thread > THREAD_COUNT_MAX )
        return 0;
 
    t = (struct thread_d *) threadList[current_thread];

    if ( t->used != TRUE || t->magic != 1234 )
        return 0;


// Get the previous alarm.

    old = (unsigned long ) t->alarm;

// alarm() returns zero if
// there was no previously scheduled alarm.

    if (old<=0){
        // Zero seconds remaining.
        return 0;
    }

// Não ha o que fazer.
// O alarme que temos ja expirou.
// É trabalho do scheduler tratar ele.
// Não vamos chamar o scheduler durante uma syscall. 

    if (old < jiffies){
        // Zero seconds remaining.
        return 0;
    }



// O alarme que temos ainda é válido.
// O pit interrompe a 1000 ticks por segundo.
// Ex: 
// ( 8000-4000 )/1000 
// (4000/1000) 
// 4 segundos faltando.

    if (old > jiffies){
        seconds_remaining = (unsigned long) ((old - jiffies) / 1000);
    }


//
// Update.
//

// Update the thread info.

    if ( seconds == 0 ){
        extra_ms = (unsigned long) 0;
    }

    if ( seconds > 0 ){
        extra_ms = (unsigned long) (seconds*1000);
    }

    t->alarm = (unsigned long) ( jiffies + extra_ms ); 


// alarm() returns the number of seconds remaining until any
// previously scheduled alarm was due to be delivered.

    return (unsigned long) seconds_remaining;
}


// 3 | 250
// See: system.c
unsigned long sys_get_system_metrics(int n)
{
    if(n<0){
        return 0;
    }
    return (unsigned long) doGetSystemMetrics ( (int) n );
}


// Only ring3 for now.
// OUT: ?
void *sys_create_process ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long res1,          //nothing
    unsigned long priority, 
    int ppid, 
    char *name,
    unsigned long iopl ) 
{
    struct process_d *new;
    char NewName[32];
    
    struct thread_d *CurrentThread;
    struct process_d *CurrentProcess;
    
    int ProcessPersonality=0;
    int ThreadPersonality=0;

//
// Not tested
//

    debug_print("sys_create_process: [TODO]\n");
    printf     ("sys_create_process: [TODO]\n");
    refresh_screen();
    //return NULL;

    // ==============

    CurrentThread = (struct thread_d *) threadList[current_thread];

    if ((void*)CurrentThread==NULL){
        return NULL;
    }

    if (CurrentThread->magic != 1234)
        return NULL;

    ThreadPersonality = (int) CurrentThread->personality;

    if (ThreadPersonality!=PERSONALITY_GRAMADO &&
        ThreadPersonality!=PERSONALITY_GWS)
    {
        panic("sys_create_process: ThreadPersonality\n");
    }

    // Create a ring0 copy of the name.
    strncpy(NewName,name,16);
    NewName[16]=0;  //finalize


// Old pml4.

    unsigned long old_pml4=0;
    old_pml4 = CurrentThread->pml4_PA;  //save

    // Switch
    x64_load_pml4_table( kernel_mm_data.pml4_pa );

    // VA
    void *pml4_va = (void *) CloneKernelPML4();
    if ( pml4_va == 0 ){
        panic ("sys_create_process: pml4_va\n");
        //goto fail;
    }

    // PA
    unsigned long pml4_pa=0;
    pml4_pa = (unsigned long) virtual_to_physical ( 
                                  pml4_va, gKernelPML4Address );
    if ( pml4_pa == 0 ){
        panic ("sys_create_process: pml4_pa\n");
        //goto fail;
    }

//
// Create process
//

    pid_t current_pid = (pid_t) get_current_process();

    if(current_pid<0 || current_pid >= PROCESS_COUNT_MAX)
    {
        panic("sys_create_process: current_pid\n");
    }

    CurrentProcess = (struct process_d *) processList[current_pid];

    if ( (void*) CurrentProcess == NULL )
        return NULL;
    if (CurrentProcess->magic!=1234)
        return NULL;
    
    ProcessPersonality = (int) CurrentProcess->personality;

    if (ProcessPersonality!=PERSONALITY_GRAMADO &&
        ProcessPersonality!=PERSONALITY_GWS)
    {
        panic("sys_create_process: ProcessPersonality\n");
    }

    if( ProcessPersonality != ThreadPersonality)
    {
        panic("sys_create_process: Personality check\n");
    }

    new = 
        (void *) create_process ( 
                     NULL, NULL, NULL, 
                     (unsigned long) CONTROLTHREAD_BASE, //0x00200000 
                     PRIORITY_HIGH, 
                     (int) current_pid, 
                     (char *) NewName, 
                     RING3, 
                     (unsigned long ) pml4_va,
                     (unsigned long ) kernel_mm_data.pdpt0_va,
                     (unsigned long ) kernel_mm_data.pd0_va,
                     ProcessPersonality );

    if ((void*) new == NULL)
    {
        printf("sys_create_process: new\n");
        refresh_screen();
        goto fail;
    }

    printf("sys_create_process: done :)\n");
    refresh_screen();

    // Switch back
    x64_load_pml4_table( old_pml4 );

// done:

    return (void*) new;

// ==============

fail:
    printf("sys_create_process: fail\n");
    refresh_screen();

    // Switch back
    x64_load_pml4_table( old_pml4 );

    return NULL;
}


/*
 * sys_create_thread:
 *     Create thread system interface.
 */

// 72 - Create thread.
// #todo: 
// Enviar os argumentos via buffer.

void *sys_create_thread ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long init_rip, 
    unsigned long priority, 
    int ppid, 
    char *name )
{
    struct thread_d  *Thread;
    
    //#bugbug: Precisamos trabalhar isso.
    //essa personalidade pode vir via argumento
    //ou depender da personalidade do caller.
    int ThreadPersonality = PERSONALITY_GRAMADO;

    debug_print ("sys_create_thread:\n");

    // #todo:
    // Filtros, para ponteiros NULL.
    
    if ( init_rip == 0 ){
        debug_print ("sys_create_thread: [FAIL] init_rip\n");
        return NULL;
    }

    // Create thread.
    

// #todo
// Temos que checar o iopl do processo que chamou
// e a thread tem que estar no mesmo ring.

    int iopl = RING3;


// #bugbug
// isso significa que a tid0 só pode criar threads
// que vão rodar em ring0 ?

    //if ( ppid = TID0_TID )
        //iopl = RING0;

    // #bugbug #todo
    // Only ring3 for now.
    // We need to receive a parameter for that.
    
    Thread = 
        (struct thread_d *) create_thread ( 
                                room, desktop, window, 
                                init_rip, 
                                priority, 
                                ppid, 
                                name,
                                iopl,
                                ThreadPersonality ); 

    if ( (void *) Thread == NULL )
    {
        debug_print ("sys_create_thread: [FAIL] Thread\n");
        return NULL;
    }

    Thread->saved = FALSE;

// #suspended:
// We have another syscall to put the thread in the standby state.

// Put the state in STANDBY.
    //SelectForExecution ( (struct thread_d *) Thread );

    return (struct thread_d *) Thread;
}


// Exit thread.
// #todo: Use 'int' as a return type.
void sys_exit_thread (int tid)
{
    if ( tid < 0 || tid >= THREAD_COUNT_MAX )
    {
        //#todo: return (int) -EINVAL;
        return;
    }

    exit_thread(tid);
}


// #todo:
// We're working in a helper function for clonning processes.
// See: clone.c
int sys_fork(void)
{
    debug_print ("sys_fork: \n");
    // #todo
    // Call copy_process(...)
    return -1;
}


// 85 
// Get PID of the current process.
//#todo: change to 'pid_t'
int sys_getpid (void)
{
    return (pid_t) get_current_process();
}


// 81
// Get the PID of the father.
int sys_getppid (void)
{
    struct process_d *p;
    pid_t pid = -1;

    pid_t current_process = (pid_t) get_current_process();

    pid = (int) current_process;

    if ( pid >= 0 && pid < PROCESS_COUNT_MAX )
    {
        p = (void *) processList[pid];

        if ( (void *) p == NULL ){ return (int) -1; }

        if ( p->used != 1 || p->magic != 1234 ){ return (int) -1; }

        return (int) p->ppid;
    }

    return (int) (-1);
}


// service 350. sci0
// Helper function to initialize system's component
// after kernel initialization.
// This is called by ring3 apps.

int sys_initialize_component (int n)
{
    if(n<0)
        return -1;

    switch (n)
    {
        // ps2 full initialization.
        case 1:
            //Not working when called from ring3.
            //PS2_initialize();
            return 0;
            break;

        //case 2:
            //break;

        //case 3:
            //break;

        //case 4:
            //break;

        // ...

        default:
            return -1;
            break;
    };
    
    return (int) 0;
}



/*
 * sys_reboot:
 *     Reboot, Serviço do sistema.
 *     Chamando uma rotina interna de reboot do sistema.
 */
// The service 110.
// It's called by sci.c.
// The higher level routine for reboot.
// It's a wrapper, an interface.
// #todo: maybe we can use arguments.
// # We need to return when a non-superuser process call this
// service. We don't wanna hang the system in this case.
        
int sys_reboot (void)
{
    int value = FALSE;

// #todo
// Is it the superuser?
// We only trust in superusser for this call.

    debug_print("sys_reboot:\n");

/*
    value = (int) is_superuser();
    if(value != TRUE){
        return (-EPERM);
    }
*/

// #todo
// Use MAGIC arguments.

// FAT cache.
// This is the FAT cache for the system disk.
// The boot partition.
    int Status = -1;
    Status = (int) fs_save_fat16_cache();
    if ( Status < 0 || fat_cache_saved != FAT_CACHE_SAVED ){
        debug_print("sys_reboot: Can't reboot without saving the fat cache\n");
        goto fail;
    }

// Reboot
    debug_print("sys_reboot: Rebooting\n");
    hal_reboot();
    panic("sys_reboot: Unexpected error\n");
fail:
    return -1;
}


// 289
// See: sm/debug/debug.c
int sys_serial_debug_printk(char *s)
{
    if ( (void *) s == NULL )
    {
        return (int) (-EINVAL);
    }

    debug_print ( (char *) s );
    return 0;
}


/*
 * sys_shutdown:
 *     Chama uma rotina interna para desligar a máquina.
 */

void sys_shutdown (void)
{
    debug_print("sys_shutdown: [TODO]\n");
    gramado_shutdown(0);
}


// Usada por vários serviços de debug.
// Usada para debug.

void sys_show_system_info(int n)
{
    if (n<0){
        debug_print("sys_show_system_info: [FAIL] n\n");
        return;
    }

    switch (n){
    case 1:  
        disk_show_info();        
        break;
    case 2:  
        volume_show_info();      
        break;
    case 3:  
        //memoryShowMemoryInfo();  
        break;
    case 4:
        //systemShowDevicesInfo();
        //pciInfo();
        break;
    case 5:  
        //KiInformation(); 
        break;
    // See: detect.c
    case 6:
        //show_cpu_info();
        break;
    // ...
    };

    refresh_screen();
}


// service 377.
// IN: Imported pointe to utsname structure.
int sys_uname (struct utsname *ubuf)
{
    debug_print("sys_uname:\n");

    if ( (void *) ubuf == NULL )
    {
        debug_print("sys_uname: ubuf\n");
        return -EINVAL;
    }

// Copy
// #todo
// We gotta get these information from pointer,
// not from 'defines'

// ##
// For now we're using default definitions.
// See:
// gramado/utsname.h
// gramado/0config/u.h
// gramado/0config/version.h

    memcpy ( 
        (void *)  ubuf->sysname, 
        (const void *) OS_NAME, 
        sizeof(OS_NAME) );

    memcpy ( 
        (void *)  ubuf->version, 
        (const void *) VERSION_NAME, 
        sizeof(VERSION_NAME) ); 

    memcpy ( 
        (void *)  ubuf->release, 
        (const void *) RELEASE_NAME, 
        sizeof(RELEASE_NAME) );    

    memcpy ( 
        (void *)  ubuf->machine, 
        (const void *) MACHINE_NAME, 
        sizeof(MACHINE_NAME) );    

    memcpy ( 
        (void *)  ubuf->nodename, 
        (const void *) NODE_NAME, 
        sizeof(NODE_NAME) );

// #todo: domain name.

//done:
    debug_print("sys_uname: done\n");
    return 0;
}


// sys_vsync:
//     Sincroniza o retraço vertical do monitor.
// #bugbug: Slow
void sys_vsync(void)
{
    hal_vsync();
}


