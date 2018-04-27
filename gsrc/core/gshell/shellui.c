/*
 * File shellui.c 
 *
 * Shell User Interface.
 *     Suporte às rotinas gráficas do aplicativo shell.
 *
 * @frednora
 */


//
// Includes.
// 


#include "api.h"
#include "types.h"
#include "stddef.h"   
#include "stdio.h"   
#include "stdlib.h"  
#include "string.h"
#include "shell.h"
#include "globals.h"



//isso é um test.
//o tipo dois funciona.
// testando colocar o ponteiro no edit box. setar foco.
//
void shellCreateEditBox()
{
    
	editboxWindow = (void*) APICreateWindow( 2, 1, 1,"{}shell-editbox1",     
                                       80, 80, 200, 22,    
                                       0, 0, COLOR_WINDOW, COLOR_WINDOW );
									   
									   
	if((void*) editboxWindow == NULL){	
		printf("shellCreateEditBox: fail");
		refresh_screen();
		while(1){}
		//exit(0);
	};
	    //Registrar.
    APIRegisterWindow(editboxWindow);


	shellSetCursor( 8, 8 );								   
};


/*
 * shellCreateTopBar:
 *
 *     CRIANDO A TOP BAR.
 *     Obs: Essa é uma janela filha.
 *     @todo: ?? e o procedimento de janela ?? e as mensagens ??
 *     Obs: É uma janela simples e limpa, feita para dispositivos IOT 
 * com resolução 800x600.
 *
 */
void shellCreateTopBar()
{
	//
	// Precisamos registrar no kernel
	// que essa janela corresponde a área de taskbar 
	// e que a área de trabalho agora é menor.
	//
	
	// Topbar window.
	topbarWindow = (void*) APICreateWindow( 1, 1, 1," {} shell-topbar ",     
                                       0, 0, 800, (600/8),    
                                       0, 0, xCOLOR_GRAY1, xCOLOR_GRAY1 );	   
	if((void*) topbarWindow == NULL){	
		printf("shellCreateTopBar: topbar Window fail");
		refresh_screen();
		while(1){}
		//exit(0);
	};
	    //Registrar.
    APIRegisterWindow(topbarWindow);
	
	//
	// icon 1 window
	//
	
	unsigned long iconMaxWidth  = (600/8);
	unsigned long iconMaxHeight = (600/8);

	i1Window = (void*) APICreateWindow( 1, 1, 1," {} shell-topbar-icon ",     
                                       2, 2, (iconMaxWidth-4), (iconMaxHeight-4),    
                                       0, 0, xCOLOR_GRAY2, xCOLOR_GRAY2 );	   
	if((void*) i1Window == NULL){	
		printf("shellCreateTopBar: icon1 Window fail");
		refresh_screen();
		while(1){}
		//exit(0);
	};
    //Registrar.
    APIRegisterWindow(i1Window);
	
	//
	// icon 2 window
	//

	i2Window = (void*) APICreateWindow( 1, 1, 1," {} shell-topbar-icon ",     
                                       (2+(iconMaxWidth-4)+2), 2, (iconMaxWidth-4), (iconMaxHeight-4),    
                                       0, 0, xCOLOR_GRAY2, xCOLOR_GRAY2 );	   
	if((void*) i2Window == NULL){	
		printf("shellCreateTopBar: icon2 Window fail");
		refresh_screen();
		while(1){}
		//exit(0);
	};
	//Registrar.
    APIRegisterWindow(i2Window);
	
	
    //
    // edit box na topbar
    //
	
	//o tipo 2 funciona.
	topbar_editboxWindow = (void*) APICreateWindow( 2, 1, 1,"{}shell-topbar-editbox1",     
                                       (iconMaxWidth*2) +20, 
									   20, 
									   (800/3) , 
									   22,    
                                       0, 0, COLOR_WINDOW, COLOR_WINDOW );
									   
									   
	if((void*) topbar_editboxWindow == NULL){	
		printf("shellCreateTopBar: fail");
		refresh_screen();
		while(1){}
		//exit(0);
	};
	    //Registrar.
    APIRegisterWindow(topbar_editboxWindow);
	
	
	
	
	
    //
    // check box na topbar
    //
	

	topbar_checkboxWindow = (void*) APICreateWindow( 5, 1, 1,"{}shell-topbar-checkbox1",     
                                       80, 
									   80, 
									   20, 
									   20,    
                                       0, 0, COLOR_WINDOW, COLOR_WINDOW );
									   
									   
	if((void*) topbar_checkboxWindow == NULL){	
		printf("shellCreateTopBar: fail");
		refresh_screen();
		while(1){}
		//exit(0);
	};
	    //Registrar.
    APIRegisterWindow(topbar_checkboxWindow);

	
	
	
	
    //
    // scroll bar na topbar
    //
	

	topbar_scrollbarWindow = (void*) APICreateWindow( 6, 1, 1,"{}shell-topbar-scrollbar",     
                                       (800-41), 
									   0, 
									   40, 
									   (600/8),    
                                       0, 0, COLOR_WINDOW, COLOR_WINDOW );
									   
									   
	if((void*) topbar_scrollbarWindow == NULL){	
		printf("shellCreateTopBar: fail");
		refresh_screen();
		while(1){}
		//exit(0);
	};
	    //Registrar.
    APIRegisterWindow(topbar_scrollbarWindow);

	
		
	
	
	//
	// BMP . LABELS
	//
	
    /*
	 ** isso funcionou.
	void *b;
	b = (void*) malloc(1024*30); 	// testando malloc.
    if( (void*) b == NULL ){
		printf("shellTestDisplayBMP: allocation fail\n");
		//while(1){}
	}
	
	//Carregando o arquivo.
loadFile:
    //@todo: Usar alguma rotina da API específica para carregar arquivo.
	// na verdade tem que fazer essas rotinas na API.
	system_call( SYSTEMCALL_READ_FILE, 
	             (unsigned long) bmp1_file_name, 
				 (unsigned long) b, 
				 (unsigned long) b);	
	
	

	//16x16
	bmpDisplayBMP( b, 2, 2, 16, 16 );	
	bmpDisplayBMP( b, 2+16+2, 2, 16, 16 );		
	*/	
};


/*
 * shellTestDisplayBMP:
 *     Carrega um arquivo .bmp na memória e decodifica, mostrando na tela.
 *
 */
void shellTestDisplayBMP()
{	
	//
	// #bugbug @todo: Aumenta o tamanho do heap do processo.
	// Esse heap é gerenciando nas bibliotecas ou na API.
	//Obs: 32Kb é alem do limite.
	//
	
	void *b = (void*) malloc(1024*30); 	// testando malloc.
    if( (void*) b == NULL ){
		printf("shellTestDisplayBMP: allocation fail\n");
		//while(1){}
	}
	
	//Carregando o arquivo.
loadFile:
    //@todo: Usar alguma rotina da API específica para carregar arquivo.
	// na verdade tem que fazer essas rotinas na API.
	system_call( SYSTEMCALL_READ_FILE, 
	             (unsigned long) bmp1_file_name, 
				 (unsigned long) b, 
				 (unsigned long) b);	
	
	

	//16x16
	bmpDisplayBMP( b, 10, 450, 16, 16 );
	 
	 
    //
	//Mostrando informações sobre o arquivo.
	//
	
	//base do bmp carregado na memória
	//unsigned char *bmp = (unsigned char *) b;
	
	
	//@todo: encontrando o magic
	
	//if( bmp[0] != 0x42 )
	//{
	//	printf("~Sig fail\n");
	//    printf("magic0 %c\n", bmp[0]);	
	//    printf("magic1 %c\n", bmp[1]);			
	//	printf("buffer %x\n",bmp); //Ok
    //    printf("buffer %x\n",b);   //Ok
		//printf("width %d \n", bmp[0x12]);
		//printf("height %d \n", bmp[0x16]);
	//}
	
	//
	//Mostrando características do bmp.
	
	//printf("magic0 %c\n", bmp[0]);	
	//printf("magic1 %c\n", bmp[1]);
	//printf("data area begin %c %c %c \n",bmp[base] ,bmp[base+1] ,bmp[base+2]);	
	//printf("buffer %x \n",bmp);
	//printf("data area address %x \n",&bmp[base]);
		
};


/*
 * bmpDisplayBMP:
 *     Mostra na tela uma imagem .bmp carregada na memória.
 */
void bmpDisplayBMP( void *address, 
                    unsigned long x, 
					unsigned long y, 
					int width, 
					int height )
{
	
	int i, j, base, offset;	
	unsigned long left, top, bottom;
	unsigned long color;
	
	base = 0x36;  //início da área de dados do bmp
	
	//limits
	
	//@todo: Refazer isso
	if( x > 800 ){ return; }
	if( y > 600 ){ return; }
	if( width > 800 ){ return; }
	if( height > 600 ){ return; }
	
	if(address == 0){return;}
	
	left = x;    //
	top  = y; 
	bottom = top + height;
	
	//base do bmp carregado na memória
	unsigned char *bmp = (unsigned char *) address;
	unsigned char *c   = (unsigned char *) &color;
	
	
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{	
			//construindo o char.
			
			offset = base;
			c[1] = bmp[offset];
			
			offset = base+1;
			c[2] = bmp[offset];
			
			offset = base+2;
			c[3] = bmp[offset];
			
			c[0] = 0;
			
			base = base + 3;
			
			//put pixel.
			//number,cor,x,y
			system_call( SYSTEMCALL_BUFFER_PUTPIXEL, 
			             (unsigned long) color, 
						 (unsigned long) left, 
						 (unsigned long) bottom );
						 
			//my_buffer_put_pixel( (unsigned long) color, (unsigned long) left, (unsigned long) bottom, 0);
			
			left++; //próximo pixel.
		}
		
		//vamos para a linha anterior.
		bottom = bottom-1;
		left = x;    //reiniciamos o x.
	};	
	
	return;
};



