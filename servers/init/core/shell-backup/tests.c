
//tests.c

// Nesse arquivo ficarão alguns testes.
// Esse arquivo poderá ser descartado depois.

#include "shell.h" 


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

void testsTimerUpdateObject (){
   
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
	//shellInsertNextChar ( (char) 'T' );  
	
	shellSetCursor ( objectX, objectY );	
	
	printf("%c",(char) 'X');
};


void testsInitTimer (struct window_d * window){
	
	    printf("%d Hz | sys time %d ms | ticks %d \n", 
		    apiGetSysTimeInfo(1), 
			apiGetSysTimeInfo(2), 
			apiGetSysTimeInfo(3) );		
					
		//janela, 100 ms, tipo 2= intermitente.
		//system_call ( 222, (unsigned long) window, 100, 2);	
			
        apiCreateTimer ( (struct window_d *) window, 
            (unsigned long) 50, (int) 2 );			
		
		//inicializando.
        objectX = 0;
        objectY = 0;
        deltaX = deltaValue;
        deltaY = deltaValue;
}


