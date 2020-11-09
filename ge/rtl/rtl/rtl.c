
/*
 * File: rtl.c 
 * 
 */


#include <stdio.h>
#include <types.h> 
#include <stdarg.h> 
#include <stddef.h>
#include <rtl/gramado.h> 
#include <sysdeps/gramado/syscall.h>



void *gramado_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d )
{
    int __Ret = 0;

    // System interrupt.

    asm volatile ( " int %1 \n"
                 : "=a"(__Ret)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );

    return (void *) __Ret; 
}



//P (Proberen) testar.
void rtl_enter_critical_section (void){

    int S=0;

    // Pega o valor do spinlock rpincipal.
    while (1){
        S = (int) gramado_system_call ( SYSTEMCALL_GET_KERNELSEMAPHORE, 
                      0, 0, 0 );
                      
		// Se deixou de ser 0 então posso entrar.
		// Se ainda for 0, continuo no while.
        if ( S == 1 ){ goto done; }
        
        //#wait
        gramado_system_call (265,0,0,0); //yield thread.
    };

    //Nothing

done:
    //Muda para zero para que ninguém entre.
    gramado_system_call ( SYSTEMCALL_CLOSE_KERNELSEMAPHORE, 0, 0, 0 );
    return;
}


//V (Verhogen)incrementar.
void rtl_exit_critical_section (void)
{
	//Hora de sair. Mudo para 1 para que outro possa entrar.
    gramado_system_call ( SYSTEMCALL_OPEN_KERNELSEMAPHORE, 0, 0, 0 );
}



/*
 **************************
 * gws_create_thread:
 *     Create a thread.
 *     #todo: 
 *     Precisamos uma função que envie mais argumentos.
 *     Essa será uma rotina de baixo nível para pthreads.
 */

void *
rtl_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name )
{
    //#define	SYSTEMCALL_CREATETHREAD     72
    debug_print ("rtl_create_thread:\n");
    return (void *) gramado_system_call ( 72, //SYSTEMCALL_CREATETHREAD, 
                        init_eip, 
                        init_stack, 
                        (unsigned long) name );
}


/*
 ****************************************************************
 * rtl_start_thread:
 *     Coloca no estado standby para executar pela primeira vez
 */

void rtl_start_thread (void *thread)
{
    debug_print ("rtl_create_thread:\n");
    gramado_system_call ( SYSTEMCALL_STARTTHREAD, 
        (unsigned long) thread, 
        (unsigned long) thread, 
        (unsigned long) thread );
}




//vamos escrever em uma janela indefinida. NULL.
//provavelmente a janela principal.
int 
rtl_draw_text ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    char *string )
{

    unsigned long msg[8];

    msg[0] = (unsigned long) 0; //window;
    msg[1] = (unsigned long) x;
    msg[2] = (unsigned long) y;
    msg[3] = (unsigned long) color;
    msg[4] = (unsigned long) string;
    // ...

    return (int) gramado_system_call ( SYSTEMCALL_DRAWTEXT, 
                    (unsigned long) &msg[0], 
                    (unsigned long) &msg[0], 
                    (unsigned long) &msg[0] );
}


/*
 *************************************
 * rtl_show_backbuffer:
 *     Refresh Screen.
 *     Passa o conteúdo do backbuffer para o lfb. 
 */

void rtl_show_backbuffer (void)
{
    // #todo
    // trocar o nome dessa systemcall.
    // refresh screen será associado à refresh all windows.
    
    gramado_system_call ( SYSTEMCALL_REFRESHSCREEN, 0, 0, 0 );
}


/*
 **********************************
 * rtl_get_system_metrics:
 *     Obtem informações sobre dimensões e posicionamentos. 
 *     #importante
 */

unsigned long rtl_get_system_metrics (int index){
    //if (index<0){
        //gde_debug_print ("gde_get_system_metrics: fail\n");
        //return 0;
    //}

    return (unsigned long) gramado_system_call ( SYSTEMCALL_GETSYSTEMMETRICS, 
                               (unsigned long) index, 
                               (unsigned long) index, 
                               (unsigned long) index );
}


// ms
// tempo total em ms.
// usado para calcular o tempo de execuçao de uma funcao.
unsigned long rtl_get_progress_time(void)
{
    return rtl_get_system_metrics (120);
}


/*
void XorSwap( int* x, int* y ); 
void XorSwap( int* x, int* y ) 
{
  if (x != y)
  {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
  }
}
*/


/*
void AddSwap( unsigned int* x, unsigned int* y );
void AddSwap( unsigned int* x, unsigned int* y )
{
  if (x != y)
  {
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
  }
}
*/


/*
 *************************************************** 
 * rtl_copy_text:
 *      Copy a string of bytes given the source, the destination,
 * the width and the height.
 *      It copies in chuncks of 64 bytes.
 *      
 */

// #bugbug
// Not tested yet.
int 
rtl_copy_text ( 
    unsigned long src, 
    unsigned long dest, 
    int width, 
    int height )
{

    char *__src  = (char *) src;
    char *__dest = (char *) dest; 

    // text width and text height.
    int __width  = width;
    int __height = height;

    int x=0;
    int y=0; 


    if ( (void *) src == NULL || (void *) dest == NULL )
    {
        printf("rtl_copy_text: src dest\n");
        return -1;
    }

    if ( width <= 0 || height <= 0 )
    {
        printf("rtl_copy_text: width height\n");
        return -1;
    }
  

    for ( y=0; y< __height; y++ ) 
    { 
        for (x=0 ; x<__width/64 ; x++) 
        { 
            memcpy ( __dest, __src+((y&63)<<6),64 );
            __dest += 64; 
        } 
        if (__width&63) 
        { 
            memcpy (__dest, __src+((y&63)<<6), __width&63 ); 
            __dest += (__width&63); 
        } 
    };
    
    return -0; 
}


/*
char *johncarmack_strstr(const char *haystack, const char *needle);
char *johncarmack_strstr(const char *haystack, const char *needle)
{
	// ...
}
*/



/*
int rtl_file_length (FILE *f);
int rtl_file_length (FILE *f)
{
	int		pos;
	int		end;

	pos = ftell (f);
	fseek (f, 0, SEEK_END);
	end = ftell (f);
	fseek (f, pos, SEEK_SET);

	return end;
}
*/

/*
int rtl_file_exists (const char *filename);
int rtl_file_exists (const char *filename)
{
	FILE *f;

	// [RH] Empty filenames are never there
	if (*filename == 0)
		return FALSE;

	f = fopen (filename, "r");
	if (!f)
		return FALSE;
	fclose (f);
	return TRUE;
}
*/

void rtl_reboot(void)
{
    gramado_system_call(110,0,0,0);
}


/*
void rtl_set_line_buffering(void);
void rtl_set_line_buffering(void)
{
    setvbuf(stdout, NULL, _IOLBF, 0);
}
*/








