/*
 ** Essa é outra forma de implementar o handler de system call 
 ** Podemos usar em outra interrupção usda pela api.
 ** Credits: Nelson Cole.
*/

#define SYSCALL_NUM 5

unsigned int num;


static void *syscall_table[] = {
	 write_clear,		// eax, 0   Limpar tela
	&write_char, 		// eax, 1   imprime um caracter na tela
	&write_string, 		// eax, 2   imprime uma string na tela
	&write_int,  		// eax, 3   imprime valor inteiro decimal na tela
	&write_hexa		// eax, 4   imprime volor inteiro hexadecimal na tela
};


void syscall_handler()
{
	__asm__ __volatile__("              \
	                      push %%eax;   \
	                      add $4, %%esp;\
	                      ":"=r"(num): );
						  
    if(num <= SYSCALL_NUM)
	{
        void *addr = syscall_table[num];

	    __asm__ __volatile__ ("               \
	                           push %%ebx;    \
	                           push %%ecx;    \
	                           push %%edx;    \
	                           call *%0;      \
	                           add $12, %%esp \
	                           "::"r"(addr));
	}else{
	    
		//set_color(4);
	    //printk("Invalid syscall: eax,%d INT 80\n",num);
	    //set_color(0xF);
    };

	return;
};
