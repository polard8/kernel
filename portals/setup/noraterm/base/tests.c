
//tests.c

// Nesse arquivo ficarão alguns testes.
// Esse arquivo poderá ser descartado depois.

#include "noraterm.h" 


//
// ## timer ##
//

int objectX;
int objectY;
int deltaX;
int deltaY;
//int deltaValue = 4;
int deltaValue = 1;

//usdo para testar o timer.

void testsTimerUpdateObject (void){
   
    //RECT rc;
    //GetClientRect(hwnd, &rc);

   objectX += deltaX;
   objectY += deltaY;

   if ( objectX < 2 )
   {
      objectX = 2;
      deltaX = deltaValue;
   }
   else if ( objectX > 78 ) {
	   
      objectX = 78; 
      deltaX = -deltaValue;  //muda a direção.
   }
   
   
   if (objectY < 2){
      objectY = 2;
      deltaY = deltaValue;
   }
   else if ( objectY > 24 ){
      objectY = 24; 
      deltaY = -deltaValue;
   }
   
	//
	// ## test ##
	//
	
	//update.
	//textCurrentRow = objectX;
    //textCurrentCol = objectY;
   
    //putchar.
	//terminalInsertNextChar ( (char) 'T' );  
	
	terminalSetCursor ( objectX, objectY );	
	
	printf ("%c", (char) 'X');
}


void testsInitTimer (struct window_d * window){
	
	    printf("%d Hz | sys time %d ms | ticks %d \n", 
		    gde_get_systime_info(1), 
			gde_get_systime_info(2), 
			gde_get_systime_info(3) );		
					
		//janela, 100 ms, tipo 2= intermitente.
		//system_call ( 222, (unsigned long) window, 100, 2);	
			
        gde_create_timer ( (struct window_d *) window, 
            (unsigned long) 50, (int) 2 );			
		
		//inicializando.
	
        objectX = 0;
        objectY = 0;
	
        deltaX = deltaValue;
        deltaY = deltaValue;
}

// # terminal stuff
// usado para teste de scroll.
// imprime varias vezes o char indicado.

void testScrollChar ( int c ){
	
    int i=0;
	
    for ( i=0; i < (__wlMaxColumns*26); i++ )
	{
	    //se chegamos no limite do screen_buffer
		//...
		terminalInsertNextChar ((char) c);	
	}		
}



