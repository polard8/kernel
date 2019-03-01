/*
 * File: gramado\logoff\logoff.c
 *
 *  Kernel Mode Logoff Support Routines.
 *
 * isso prepara um ambiente para rodar o processo logoff
 *
 * Descrição:
 *     Módulo do kernel responsável por rotinas de logoff.
 *     Esse módulo faz parte do kernel base.
 *     Encerra uma seção de usuário.
 *     Um usuário sai.
 *     Fecha todos os programas e enserra a sessão do usuário.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 */


#include <kernel.h>			



//Variáveis internas
//int logoffStatus;
//...


/*
 * StartLogoff:
 *        
 */
int StartLogoff(int argc, char *argv[]) 
{
   printf("Starting logoff ...\n");
   
   //...
   
done:
	return (int) 0;
};



int init_logoff(int argc, char *argv[]) 
{
	int Status;
	char *s;    //String
	int LogoffFlag;
	
	if (argc < 1) {
        //Usage();
		goto done;
    };
	
   while(--argc) 
   {
        s = *++argv;
        if (*s == '-' || *s == '/') 
		{
            while(*++s) 
			{
                switch(*s) 
				{
                    case 'l':
                        LogoffFlag = 1;
                        break;

                    case 's':
                        LogoffFlag = 2;
                        break;

                    case 'r':
					    LogoffFlag = 3;
                        break;

                    case 'f':
					    LogoffFlag = 4;
                        break;

                    default:    
					    LogoffFlag = 0;
						//Usage();
						break;
                };
            };
        }
        else 
		{
            //Usage();
        }
    };   
   
   
   //
   //@todo: Criar rotina chamando funções de fechamento.
   //

    if(LogoffFlag == 2)
	{
		//kbackground(COLOR_BLACK);	
		//StatusBar( gui->screen, "StatusBar: ", "Logoff...");	
		//refresh_screen();
		
		//sleep(4000);
        //set_up_cursor(0,0);	
        //set_up_text_color(0x0f, 0x09);	
	    //printf("\n\n Logoff... \n\n");
		
	    // Scheduler stuffs.
	    //sleep(4000);
	    //printf("Locking Scheduler and task switch.\n");
	    //scheduler_lock();		
		//taskswitch_lock();
		//refresh_screen();
		
		//Fechar todos os processos.
		//CloseAllProcesses();
		
		
			// Interruoções.
	    //sleep(4000);
	    //asm("cli");	
		
		//Finalizar sessão.
		//close_user_session();
    };	
	
done:	
    logoffStatus = 1;
	
	
	//Status = (int) StartLogoff(int argc, char *argv[]);
	
    printf("Fail!\n");
	return (int) 1;	
};


/*
int logoffInit()
{}
*/

//
//fim.
//

