/*
 * File: main.c 
 *     tmetrics.bin.
 *
 */
 

#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "api.h" 

//
int app_test()
{
    unsigned char count;
	unsigned char standard_ascii_max = 128;
	
	struct window_d *hWindow;
	
    //stdlib
	//inicializando o suporte a alocação dinâmica de memória.
	libcInitRT();

	//stdio
	//inicializando o suporte ao fluxo padrão.
    stdioInitialize();	
	
	//printf("TMETRICS.BIN:\n");
	//printf("Show ascii table ...\n\n");
	
	
	//Criando uma janela para meu editor de textos.
	apiBeginPaint(); 
	hWindow = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1,"{} TMETRICS.BIN",
	                    20, 20, 
						800-40, 600-40,    
                        0, 0, COLOR_WINDOW , 0x303030 );	  

	if((void*) hWindow == NULL)
	{	
		printf("TMETRICS.BIN: hWindow fail");
		apiEndPaint();
		goto fail;
	}
    apiEndPaint();
	
	
    APIRegisterWindow(hWindow);
    APISetActiveWindow(hWindow);	
    APISetFocus(hWindow);	
	
	apiSetCursor( 2, 6);
	 
	int i;
	for( i=0; i<12; i++ )
	{
		printf("Metrics: id={%d} value={%d}\n", 
		    i, apiGetSystemMetrics(i) );
	}
	
	
	refresh_screen();
	
	
	
	

	
	/*
	
	
    for( count=0; count<standard_ascii_max; count++ )
    {
		printf(" %d - %c",count,count);
        if( count % 4 == 0 ){
            printf("\n");
		}
    };	
	*/

    goto done;
fail:
	printf("fail\n");	
done:	
	printf("done.\n");
	

	while(1){
		asm("pause");
	}
    
    //return 0;
};

