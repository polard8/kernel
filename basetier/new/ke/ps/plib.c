
// plib.c
// Process library.

#include <kernel.h>



/*
 * show_process_information:
 *     Mostra informa��es sobre os processos. 
 *     #todo: na verdade um aplicativo em user mode deve fazer esse trabalho
 * solicitando informa��es sobre cada processo atrav�s de chamadas.
 */

// Mostrar informa��es sobre os processos da lista.
// obs: as imagens s�o carregadas em endere�os virtuais diferentes
// e o endere�o mostrado � em rela��o ao diret�rio de p�ginas do kernel
// pois o kernel � que controla o posicionamento das imagens.

void show_process_information (void)
{
    struct process_d *p;
    int i=0;

    printf ("show_process_information: \n");

    for ( i=0; i<PROCESS_COUNT_MAX; i++ )
    {
        p = (void *) processList[i];

        if ( (void *) p != NULL && 
             p->used  == TRUE && 
             p->magic == 1234 )
        {
            //printf("\n");
            printf("\n=====================================\n");
            printf(">>[%s]\n", p->__processname);
            printf("PID=%d PPID=%d \n", p->pid,  p->ppid );
            
            printf("image-base =%x image-size =%d \n", 
                p->Image, p->ImageSize );
            printf("heap-base  =%x heap-size  =%d \n", 
                p->HeapStart,  p->HeapSize );
            
            
            // #bugbug: It's very wrong!
            // See: create_process() in process.c
            //
            //printf("stack-base =%x stack-size =%d \n", 
            //    p->StackStart, p->StackSize );

            //printf("dir-pa=%x dir-va=%x \n", 
            //    p->DirectoryPA, p->DirectoryVA );

            printf("iopl=%d prio=%d state=%d \n", 
                p->iopl, p->priority, p->state );

            printf("syscalls = { %d }\n", p->syscalls_counter );
        }
    // Nothing.
    };

    refresh_screen();
}


// Usado pelo comando "current-process" no shell
void show_currentprocess_info (void)
{
    struct process_d  *Current;

    pid_t current_process = (pid_t) get_current_process();

    if ( current_process < 0 || 
         current_process >= PROCESS_COUNT_MAX )
    {
        //printf("show_process_information: current_process fail\n");
        return;
    }

// Struct.

    Current = (void *) processList[current_process];

    if ( (void *) Current == NULL ){
        printf ("show_currentprocess_info: [FAIL] Current \n");
        return;
    }

    if(Current->magic != 1234)
        return;

    //Index.
    printf ("PID={%d} PPID={%d} UID={%d} GID={%d} \n",
        Current->pid, Current->ppid, Current->uid, Current->gid );

    //Name
    //printf ("Name={%s} \n", Current->name_address );
    printf ("Name={%s} \n", Current->name );
 
    //Image Address.
    printf ("ImageAddress={%x} \n", Current->Image );

    //Directory Address. *IMPORTANTE.
    //printf (">>DirectoryPA={%x} \n", Current->DirectoryPA );
    //printf (">>DirectoryVA={%x} \n", Current->DirectoryVA );

// Heap and stack.

    printf("HeapStart={%x}  HeapSize={%d KB}  \n", 
        Current->HeapStart, Current->HeapSize );
    printf("StackStart={%x} StackSize={%d KB} \n", 
        Current->StackStart, Current->StackSize );

    //...

    refresh_screen();
}

