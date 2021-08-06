


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
    // loop
    int i=0;
    struct process_d *p;

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
                p->Heap,  p->HeapSize );
            printf("stack-base =%x stack-size =%d \n", 
                p->Stack, p->StackSize );

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

// usado pelo comando "current-process" no shell
void show_currentprocess_info (void){

    struct process_d  *Current;


    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX )
    {
        //printf("show_process_information: current_process fail\n");
        return;
    }


	//Struct.
    Current = (void *) processList[current_process];

    if ( (void *) Current == NULL ){
        printf ("show_currentprocess_info: [FAIL] Current \n");
        return;
    } else {

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

		//Heap and stack.
        printf("Heap={%x}  HeapSize={%d KB}  \n", Current->Heap, 
            Current->HeapSize );

        printf("Stack={%x} StackSize={%d KB} \n", Current->Stack, 
            Current->StackSize );

		//...
    };

    refresh_screen();
}







