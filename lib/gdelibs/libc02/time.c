/*
 * File: time.c 
 *
 * 2018 - Created by Fred Nora.
 */
 

#include <time.h>
#include <types.h> 


//system calls.
#include <stubs/gramado.h> 

						 
// time 
// #obs: O que representa esse retorno ?
// Isso funciona.

time_t time (time_t *timer){
	
	time_t Ret;
	
	//system call. (224) get time
		
	Ret = (time_t) gramado_system_call ( 224, 0, 0, 0 );
	
    *timer = Ret;

    return (time_t) Ret;	
}

