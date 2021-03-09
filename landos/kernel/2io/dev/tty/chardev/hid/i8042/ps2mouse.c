/*
 * File: i8042/ps2mouse.c
 *
 *      + ps2 mouse controler support.
 *      + mouse event support.
 * 
 * Environment:
 *     Ring 0. Kernel base persistent code.
 *
 * History:
 *     2018 - Created by Fred Nora.
 */

// #todo
// talvez fazer estruturas para controlar as configurações de mouse.

// See:
// https://wiki.osdev.org/Mouse_Input
// https://wiki.osdev.org/PS/2_Mouse
// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-13.html
// http://users.utcluj.ro/~baruch/media/sie/labor/PS2/PS-2_Mouse_Interface.htm
// ...


#include <kernel.h>


//++
// ===================
// Defines
// Credits: serenity OS

// ??
// #define IRQ_MOUSE  1


// ?
#define I8042_BUFFER  0x60
#define I8042_STATUS  0x64

#define I8042_ACK              0xFA
#define I8042_BUFFER_FULL      0x01
#define I8042_WHICH_BUFFER     0x20
#define I8042_MOUSE_BUFFER     0x20
#define I8042_KEYBOARD_BUFFER  0x00

#define PS2MOUSE_SET_RESOLUTION            0xE8
#define PS2MOUSE_STATUS_REQUEST            0xE9
#define PS2MOUSE_REQUEST_SINGLE_PACKET     0xEB
#define PS2MOUSE_GET_DEVICE_ID             0xF2
#define PS2MOUSE_SET_SAMPLE_RATE           0xF3
#define PS2MOUSE_ENABLE_PACKET_STREAMING   0xF4
#define PS2MOUSE_DISABLE_PACKET_STREAMING  0xF5
#define PS2MOUSE_SET_DEFAULTS              0xF6
#define PS2MOUSE_RESEND                    0xFE
#define PS2MOUSE_RESET                     0xFF

#define PS2MOUSE_INTELLIMOUSE_ID 0x03
//--

// i8042 mouse status bit.
#define MOUSE_LEFT_BTN    0x01
#define MOUSE_RIGHT_BTN   0x02
#define MOUSE_MIDDLE_BTN  0x04
#define MOUSE_X_SIGN      0x10
#define MOUSE_Y_SIGN      0x20
#define MOUSE_X_OVERFLOW  0x40
#define MOUSE_Y_OVERFLOW  0x80

//  mouseHandler support
#define MOUSE_DATA_BIT  1
#define MOUSE_SIG_BIT   2
#define MOUSE_F_BIT     0x20
#define MOUSE_V_BIT     0x08 




// Screen width and height

extern unsigned long SavedX; 
extern unsigned long SavedY; 


//=============================
//mouse control

// habilitar e desabilitar o mouse.
// usada pelos aplicativos.
int ps2_mouse_status;

int ps2_mouse_has_wheel;

//1= pressionado 0=liberado
int ps2_button_pressed;

int ps2_mouse_moving;
int ps2_mouse_drag_status;
//int ps2_mouse_drop_status;

//====================================================================
// update_mouse support


long mouse_x = 0;
long mouse_y = 0;

char mouse_packet_data = 0;
char mouse_packet_x = 0;
char mouse_packet_y = 0;
char mouse_packet_scroll = 0;
//=====================================================================




//====================================================================

// Contador
static int count_mouse = 0;

// Buffer
static char buffer_mouse[3];


//=====================================================================


//
// Prototype
//

// Protótipos de funções internas.
int MOUSE_BAT_TEST (void);



/*
 ******************************************
 * MOUSE_SEND_MESSAGE:
 *     Send a mouse message. 
 */

// Pegamos os tres char do inout de mouse e 
// transformamos em uma mensagem que será enviada para uma thread.

// #bugbug
// TODO

int MOUSE_SEND_MESSAGE (void *buffer)
{
    if ( (void *) buffer == NULL )
    {
        return (int) -1;
    }

    unsigned char *chars = (unsigned char *) buffer;

    //char char0 = (char) &chars[0];
    //char char1 = (char) &chars[1];
    //char char2 = (char) &chars[2];
    //char char3 = (char) &chars[3];
    //...

    debug_print ("MOUSE_SEND_MESSAGE: fixme\n");

	// #todo
	// Colocar esses dados em uma mesnagem e enviar para thread.

    return (int) -1;
}



/*
 *********************************************
 * xxx_mouse_write:
 *     Envia um byte para a porta 0x60.
 */

//mudar o arg para data;

void xxx_mouse_write (unsigned char data)
{
	// See:
	// kbdc_wait(?)  .. in  ps2kbd.c

    // 0xD4 diz que eh para enviar o comando para o mouse.
    prepare_for_output();
    out8 (I8042_STATUS, 0xD4);

    prepare_for_output();
    out8 (I8042_BUFFER, data);
}




/*
 **************************************
 * xxx_mouse_read:
 *     Pega um byte na porta 0x60.
 */

unsigned char xxx_mouse_read (void)
{
    prepare_for_input();
    
    return (unsigned char) in8(0x60);
}


/*
 *********************************** 
 * MOUSE_BAT_TEST:
 * 
 */

// Esta rotina faz o Auto-teste. 
// 0xaa êxito, 0xfc erro.
// Created by Fred Nora.

int MOUSE_BAT_TEST (void)
{
    int val = -1;
    int i = 0;

	// #todo:
	// Cuidado.
	// Diminuir isso se for possivel.
	// Nao funciona na maquina reala sem esse delay.

    // #bugbug: Max
    
    for (i=0; i<99000; i++){  wait_ns (400);  };

    // #bugbug: Max

    for ( i=0; i<999; i++ )
    {
        // #todo
        // Mask only the used bits. 0x000000FF
        
        val = xxx_mouse_read();

        if (val == 0xAA){
            printf ("MOUSE_BAT_TEST: [OK]  \n");  return 0;
        }else if (val == 0xFC){
            printf ("MOUSE_BAT_TEST: [FAIL]\n");  return (int) -1; 
        };

        // Reenviar o comando. 
        // OBS: este comando não é colocado em buffer

        xxx_mouse_write (0xFE);       
    };

    // #bugbug:
    // Não podemos exibir essa mensagem repetidas vezes.
    printf ("MOUSE_BAT_TEST %d times\n", i );
}



/*
 ***********************************************
 * ps2_mouse_globals_initialize:
 *     Inicializando o mouse no controlador 8042.
 *     Carregando o bmp para o curso do mouse.
 * 
 * History:
 *     2018 - Created by Fred Nora.  
 */

int ps2_mouse_globals_initialize (void)
{
    unsigned char response = 0;
    unsigned char deviceId = 0;
    int i = 0; 
    int bruto = 1;  //Método.
    int mouse_ret = 0;


	//printf("ps2_mouse_globals_initialize: inicializando estrutura\n");
	//refresh_screen ();

    // See: user.h   ??
    
    ioControl_mouse = (struct ioControl_d *) kmalloc ( sizeof(struct ioControl_d) );

    if ( (void *) ioControl_mouse == NULL ){
        panic("ps2_mouse_globals_initialize: [FAIL] ioControl_mouse\n");
    }else{
        ioControl_mouse->used  = TRUE;
        ioControl_mouse->magic = 1234;
        ioControl_mouse->id = 0;
		//Qual thread está usando o dispositivo.
        ioControl_mouse->tid = 0;  
        //ioControl_mouse->
    };


	//printf("ps2_mouse_globals_initialize: inicializando variaveis\n");
	//refresh_screen ();

    // #importante
    // habilitando o mouse ps2.
    // ?? Is this a global thing ?
    // Where is it defined?

    ps2_mouse_status = 1;


	// Estamos espaço para o buffer de mensagens de mouse.
	// mousemsg = ( unsigned char *) kmalloc(32);


	//Inicializando as variáveis usadas na rotina em Assemly
	//em hardwarelib.inc

    //#todo:
    //Podemos inicialziar com o mouse no centro da tela.

	//Coordenadas do cursor.
    g_mousepointer_x = (unsigned long) 0;
    g_mousepointer_y = (unsigned long) 0;
    mouse_x = 0;
    mouse_y = 0;


	// #bugbug: 
	// Essa inicialização está travando o mouse.
	// Fazer com cuidado.


    // #bugbug. 
    // Cuidado com essa inicializaçao.
    // #todo
    // We need a helper to set this thing up.

    g_mousepointer_width  = 16;
    g_mousepointer_height = 16;


    //Bytes do controlador.
    //mouse_packet_data = 0;
    //mouse_packet_x = 0;
    //mouse_packet_y = 0;
    //mouse_packet_scroll = 0;


	//
	// BMP
	//

    // #todo
    // We need to change the name of this function.
    // It's because we're gonna need to use another
    // format of file.

	// Carregando o bmp do disco para a memória
	// e apresentando pela primeira vez.

    mouse_ret = (int) load_mouse_bmp();

    if (mouse_ret != 0)
    {
        panic ("ps2_mouse_globals_initialize: [FAIL] load_mouse_bmp\n");
    }

    // ??
    //initialized = 1;

    //return (kernelDriverRegister(mouseDriver, &defaultMouseDriver));

    debug_print("done\n");

    return 0;
}



/*
 ******************************************************
 * ps2mouse_initialize_device
 * ...
 */

void ps2mouse_initialize_device (void)
{

    //register device
    file *__file;
    char __tmpname[64];
    char *newname;

    unsigned char status = 0;
    int i=0;
    unsigned char device_id=0;
    

    __breaker_ps2mouse_initialized = FALSE;



    //
    // Globals first.
    //
    
    // Inicializa variáveis de gerenciamento do driver.
    ps2_mouse_globals_initialize();


//__enable_second_port :

    // reset mouse
    //out8(0xD4, 0x64);      // tell the controller to address the mouse
    //out8(0xFF, 0x60);
    xxx_mouse_write(0xFF); 

    //++
    //======================================================
    // #obs:
    // A rotina abaixo habilita o segundo dispositivo. O mouse.
    
    // #bugbug
    // Essa nao eh uma rotina de habilitaçao do dispositivo secundario,
    // estamos apenas lendo a porta 60 e devolvendo o que lemos o que lemos
    // com alguma modificaçao;
    // #todo: me parece que para habilitar o secundario eh
    // preciso apenas mandar 0xA8 para a porta 0x64.

    // Dizemos para o controlador entrar no modo leitura.
    // Esperamos para ler e lemos.
    // 0x20 Read Command Byte
    // I8042_READ = 0x20

    wait_then_write(0x64,I8042_READ);
    status = wait_then_read(0x60) | 2;


    // #bugbug
    // O defeito pode estar aqui
    //ja que nosso maior problema eh ficar se interrupçao.

    // Dizemos para o controlador entrar no modo escrita.
    // Esperamos para escrever e escrevemos.
    // Enable the PS/2 mouse IRQ (12).
    // The keyboard uses IRQ 1 (and is enabled by bit 0 in this register).
    // 0x60 Write Command Byte
    wait_then_write (0x64,I8042_WRITE);   // I8042_WRITE = 0x60
    wait_then_write (0x60,status);   
    
    // 0x64 <<< 0xA8 ?? enable aux
    // 0x64 <<< 0xA9 ?? check for mouse
    // #todo: See i8042.h for the commands used in the initialization.

    // #test
    // Habilitando o dispositivo secundario na forma bruta.
    // Reenable mouse port.
    // #bugbug: a rotina de inicializaçao da controladora ps2,
    // esta fazendo isso ao fim da rotina. nao precisamos fazer isso aqui.
    // Talvez atrapalhe a inicializaçao.
    // 0xA8 Enable Mouse
    // 0xA7 Disable Mouse
    // 0xA9 Check Mouse InterfaceReturns 0, if OK

    wait_then_write(0x64,0xA8);
    for (i=0; i<20000; i++)
    {
    };

    //======================================================
    //-- 


	// 0xFF
	// Espera o dados descer (ACK)
	// Basic Assurance Test (BAT)





    // Set default settings.
    //xxx_mouse_write (PS2MOUSE_SET_DEFAULTS);
    //expect_ack();

    // Enable streaming.
    //xxx_mouse_write (PS2MOUSE_ENABLE_PACKET_STREAMING);
    //expect_ack();
    
   
    
    
//__enable_wheel:    
  
    //++
    //=================================================
  
    // #obs:
    // A rotina abaixo habilita a rodinha, se o dispositivo possui.
    // Credits: Serenity OS.    

    // Pega o device id e faz configurações de wheel.
    xxx_mouse_write (PS2MOUSE_GET_DEVICE_ID);
    expect_ack();
    
    device_id = xxx_mouse_read(); 
    
    if (device_id != PS2MOUSE_INTELLIMOUSE_ID){

        // Send magical wheel initiation sequence.
        xxx_mouse_write (PS2MOUSE_SET_SAMPLE_RATE);
        expect_ack();
        xxx_mouse_write (200);
        expect_ack();
        xxx_mouse_write (PS2MOUSE_SET_SAMPLE_RATE);
        expect_ack();
        xxx_mouse_write (100);
        expect_ack();
        xxx_mouse_write (PS2MOUSE_SET_SAMPLE_RATE);
        expect_ack();
        xxx_mouse_write (80);
        expect_ack();

        xxx_mouse_write (PS2MOUSE_GET_DEVICE_ID);
        expect_ack();
        device_id = xxx_mouse_read();
    }

    if (device_id == PS2MOUSE_INTELLIMOUSE_ID) {

        //m_has_wheel = true;
        ps2_mouse_has_wheel = 1;
        kprintf ("ps2mouse_initialize_device: Mouse wheel enabled!\n");
        
    } else {
        kprintf ("ps2mouse_initialize_device: No mouse wheel detected!\n");
    };


/*
0xFF ResetMouse reset
0xFE ResendFor serial communications errors
0xF6 Set DefaultsSet default values
0xF5 Disable (Data Reporting)In stream mode, 
     should be sentbefore any other command
0xF4 Enable (Data Reporting)In stream mode only
0xF3 Set Sample RateSets state sampling rate
0xF0 Set Remote modeSend data on request only
0xEB Read DataSend data packet request
0xEA Set Stream ModeSend data on events
0xE9 Status RequestGet mouse configuration (3 bytes)
0xE8 Set Resolution
0xE7 Set Scaling 2:1Accelerationmode
0xE6 Set Scaling 1:1Linear mode
*/

    //=================================================
    //--
    
    
    // 0xF6 Set default settings.
    xxx_mouse_write (PS2MOUSE_SET_DEFAULTS);
    expect_ack();

    // 0xE6 Set Scaling. 
    xxx_mouse_write (0xE6);
    expect_ack();

    // 0xF4 Enable streaming.
    // Enable Data Reporting 
    // 0xF5 Disable (Data Reporting)
    xxx_mouse_write (PS2MOUSE_ENABLE_PACKET_STREAMING);  //0xf4
    expect_ack();

    // 0xF3 set sample rate.
    // Set Sample Rate, valid values are 10, 20, 40, 60, 80, 100, and 200. 
    xxx_mouse_write (0xF3);
    expect_ack();
    xxx_mouse_write (0x64);  //rate value
    expect_ack();
    
    
    // 0xEA Set Stream Mode Send data on events
    // 0xE9 Status Request
    // 0xE7 Set Scaling 2:1 Accelerationmode
    // 0xE6 Set Scaling 1:1 Linear mode
    
    // 0xE8 set resolution
    xxx_mouse_write (0xE8);
    expect_ack();
    xxx_mouse_write (0x03);  //resolution
    expect_ack();
    

    // Wait for nothing!
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);
    
    
//
// ==========================================
//

    //
    // name
    //
   
    //#test
    // isso não é o ponto de montagem.
    sprintf( (char *) &__tmpname[0], "/DEV_I8042_MOUSE");
    newname = (char *) kmalloc (64);
    if ( (void*) newname == NULL )
        panic("ps2mouse_initialize_device: newname");
    strcpy (newname,__tmpname);


    // Agora registra o dispositivo pci na lista genérica
    // de dispositivos.
    // #importante: ele precisa de um arquivo 'file'.

    int register_status = -1;
    
    __file = (file *) kmalloc ( sizeof(file) );
    
    if ( (void *) __file == NULL ){
        panic ("ps2mouse_initialize_device: __file fail, can't register device");    
    }else{
        __file->used  = 1;
        __file->magic = 1234;
        __file->isDevice = 1;

        //
        // Register.
        //

        // #importante
        // Essa é a tabela de montagem de dispositivos.
        // O nome do dispositivo deve ser um pathname.
        // Mas podemos ter mais de um nome.
        // vamos criar uma string aqui usando sprint e depois duplicala.
        
        register_status = devmgr_register_device ( 
            (file *) __file,             // file
             newname,                    // device name.                  
             0,                          //class (char, block, network)
             1,                          //type (pci, legacy
             (struct pci_device_d *) 0,  //pci device
             NULL );                     //tty driver
    
        if (register_status<0){
            panic("ps2mouse_initialize_device: devmgr_register_device fail");
        } 
        
        
        
        //object
        PS2MouseDeviceObject = (file *) __file;  //object file
        if ( (void *) PS2MouseDeviceObject == NULL ){
           panic("ps2kbd_initialize_device: PS2MouseDeviceObject fail");   
        }
        
        
        //device
        PS2MouseDevice = (struct device_d *) __file->device;   //device structure.
        if ( (void *) PS2MouseDevice == NULL ){
           panic("ps2kbd_initialize_device: PS2MouseDevice fail");   
        }
        
        //driver
        //PS2MouseDeviceTTYDriver = (struct ttydrv_d *) __file->device->ttydrv; // driver struct.
        //if ( (void *) PS2MouseDeviceTTYDriver == NULL ){
        //   panic("ps2kbd_initialize_device: PS2MouseDeviceTTYDriver fail");   
        //}
        
        
        // #hackhack
        // Actually we need to create a tty for all the devices.
        // And it needs to be done in devmgr_register_device
        // But we do not have all these resources roght now.
        
        //tty
        PS2MouseDeviceTTY = (struct tty_d *) tty_create();
        
        if ( (void *) PS2MouseDeviceTTY == NULL )
        {
           panic("ps2kbd_initialize_device: PS2MouseDeviceTTY fail");   
        }

     
        // ...
    };
    
    // #test
    // Drain the output buffer for the first time. Residual.

    I8042Controller_do_drain();
    
//
// ==========================================
//

    g_driver_ps2mouse_initialized = 1;
    
    __breaker_ps2mouse_initialized = 1;
}



/*
 ***************************************************
 * getMouseData:
 *     Essa função é usada pela rotina kernelPS2MouseDriverReadData.
 * Input a value from the keyboard controller's data port, 
 * after checking to make sure that there's some mouse data 
 * there for us.
 */

static unsigned char getMouseData (void)
{
    unsigned char data = 0;


    while ( (data & 0x21) != 0x21 )
    {
        data = in8(0x64);
    };

    data = in8(0x60);

    return (data);
}


/*
 ******************************************************
 * kernelPS2MouseDriverReadData:  
 *     Pega os bytes e salva em um array.
 *     Exibe um caractere na tela, dado as cordenadas.
 *     This gets called whenever there is a mouse interrupt
 *     @todo: Rever as entradas no array.         
 */

void kernelPS2MouseDriverReadData (void)
{
    //#suspensa !
}


/*
 *******************************************************
 * load_mouse_bmp:  
 * 
 *     ## teste ##
 * 
 *     Carregando o arquivo MOUSE.BMP, que é o ponteiro de mouse.
 *     Usar isso na inicialização do mouse.
 * 
 *     #bugbug isso pode ir para windowLoadGramadoIcons
 * 
 *     2018 - Created by Fred Nora.
 */

int load_mouse_bmp (void)
{
    int Status = 1;
    int Index = 0; 
    unsigned long fileret = 0;


#ifdef KERNEL_VERBOSE
    //printf ("load_mouse_bmp:\n");
#endif

    // #bugbug
    // Alocando duas páginas para um BMP pequeno. 8KB.

    unsigned long tmp_size = (2*4096);
    mouseBMPBuffer = (void *) allocPages (2);


    if ( (void *) mouseBMPBuffer == NULL ){
        printf ("load_mouse_bmp: mouseBMPBuffer\n");
        goto fail;
    }


	//
	// ## Loading ...  ##
	//

	//read_fntos( (char *) arg1);


	//===================================
	// MOUSE

    // #todo
    // We need to load from any directory, not only root.
    
    // Loading from root dir. 512 entries.

    fileret = (unsigned long) fsLoadFile ( 
                                  VOLUME1_FAT_ADDRESS,
                                  VOLUME1_ROOTDIR_ADDRESS, 
                                  FAT16_ROOT_ENTRIES, //#bugbug: Number of entries.
                                  "MOUSE   BMP", 
                                  (unsigned long) mouseBMPBuffer,
                                  tmp_size );

    if ( fileret != 0 ){
        printf        ("load_mouse_bmp: [FAIL] MOUSE.BMP\n");
        goto fail;
    }


	// Render BMP file on backbuffer.
	//bmpDisplayBMP( mouseBMPBuffer, 20, 20 );
	//refresh_rectangle( 20, 20, 16, 16 );
	//===================================


//refresh_rectangle:

	//Isso funcionou ...
	//refresh_rectangle( 20, 20, 16, 16 );

    Status = (int) 0;
    goto done;

fail:
    printf ("fail\n");
    Status = (int) 1;

done:

#ifdef KERNEL_VERBOSE
    printf ("done\n");
#endif

	//refresh_screen();
    return (int) Status;
}


// events.h
void set_current_mouse_responder (int i)
{
    current_mouse_responder = i;
}


// events.h
int get_current_mouse_responder (void)
{
    return (int) current_mouse_responder;
}


/*
 * =====================================================
 * update_mouse:
 *     Updates the mouse position.
 */

// #todo
// Describe this funcion.
// Change name to ps2mouse_update_mouse()

void update_mouse (void)
{

//======== X ==========
// Testando o sinal de x.
// Do the x pos first.

//pega o delta x
//testa o sinal para x
do_x:
    if ( mouse_packet_data & MOUSE_X_SIGN ){  goto x_neg;  }

//Caso x seja positivo.
x_pos:
    mouse_x += mouse_packet_x;
    goto do_y;

//Caso x seja negativo.
x_neg:
    mouse_x -= ( ~mouse_packet_x + 1 );

    if (mouse_x > 0){  goto do_y;  }

    mouse_x = 0;

//======== Y ==========
// Testando o sinal de x. 
// Do the same for y position.

//Pega o delta y.
//Testa o sinal para y.
do_y:
    if ( mouse_packet_data & MOUSE_Y_SIGN ){  goto y_neg;  }

//Caso y seja positivo.
y_pos:
    mouse_y -= mouse_packet_y;

    if ( mouse_y > 0 ){  goto quit; }

    mouse_y = 0;
    goto quit;

//Caso y seja negativo. 
y_neg:
    mouse_y += ( ~mouse_packet_y + 1 );

// Quit
quit:
    return;
}


// o driver de mouse entrega informações sobre o evento atual
// para quem pedir. Como o servidor de janelas atual.
unsigned long ps2_mouse_get_info ( int i )
{

    //if (i<0)
        //return 0;

    switch (i){

        case 1:
            return (unsigned long) saved_mouse_x;
            break;

        case 2:
            return (unsigned long) saved_mouse_y;
            break;
            
        case 3:
            return (unsigned long) mouse_x;
            break;
            
        case 4:
            return (unsigned long) mouse_y;
            break;
            
        case 5:
            return (unsigned long) ps2_mouse_moving;
            break;

        case 6:
            return (unsigned long) ps2_mouse_drag_status;
            break;
            
        case 7:
            return (unsigned long) mouse_button_action;
            break;            

        case 8:
            return (unsigned long) mouse_buttom_1;
            break;
            
        case 9:
            return (unsigned long) mouse_buttom_2;
            break;
            
        case 10:
            return (unsigned long) mouse_buttom_3;
            break;

        case 11:
            return (unsigned long) old_mouse_buttom_1;
            break;
            
        case 12:
            return (unsigned long) old_mouse_buttom_2;
            break;
            
        case 13:
            return (unsigned long) old_mouse_buttom_3;
            break;
            
            
        case 14:
            return (unsigned long) ps2_button_pressed;
            break;

          //...
    };
}



void ps2mouse_change_and_show_pointer_bmp ( int number )
{

    if ( number<0 )
        return;


    switch (number){

        case 1:
           refresh_rectangle ( 
               saved_mouse_x, saved_mouse_y, 20, 20 );
           bmpDisplayMousePointerBMP ( 
               mouseBMPBuffer, mouse_x, mouse_y ); 
           break;

        // app icon
        case 2:
            refresh_rectangle ( 
                saved_mouse_x, saved_mouse_y, 20, 20 );
            bmpDisplayMousePointerBMP ( 
                shared_buffer_app_icon, mouse_x, mouse_y ); 
            break;

        // file icon
        case 3:
            refresh_rectangle ( 
                saved_mouse_x, saved_mouse_y, 20, 20 );
            bmpDisplayMousePointerBMP ( 
                shared_buffer_file_icon, mouse_x, mouse_y );
            break;

        // folder icon
        case 4:
            refresh_rectangle ( 
                saved_mouse_x, saved_mouse_y, 20, 20 );
            bmpDisplayMousePointerBMP ( 
                shared_buffer_folder_icon, mouse_x, mouse_y ); 
            break;

        // terminal icon
        case 5:
           refresh_rectangle ( 
               saved_mouse_x, saved_mouse_y, 20, 20 );
           bmpDisplayMousePointerBMP (
               shared_buffer_terminal_icon, mouse_x, mouse_y ); 
           break;


        case 6:
            refresh_rectangle ( 
                saved_mouse_x, saved_mouse_y, 20, 20 );
            bmpDisplayMousePointerBMP ( 
                shared_buffer_cursor_icon, mouse_x, mouse_y );
            break;
 
        // #test
        // Estamos usando os ícones previamente carregados.  

        //...  
 
        default:
           refresh_rectangle ( 
               saved_mouse_x, saved_mouse_y, 20, 20 );
           bmpDisplayMousePointerBMP ( 
               mouseBMPBuffer, mouse_x, mouse_y ); 
           break;
    };
}


// #todo: 
// Isso aqui deveria colocar um pacote na fila
// para o window server pegar depois.
void ps2mouse_parse_data_packet (void)
{

	// A partir de agora já temos os três chars.
	// Colocando os três chars em variáveis globais.
	// Isso ficará assim caso não haja overflow.

    mouse_packet_data = buffer_mouse[0];    // Primeiro char
    mouse_packet_x    = buffer_mouse[1];    // Segundo char.
    mouse_packet_y    = buffer_mouse[2];    // Terceiro char.
            
    //
    // ==== Posicionamento ====
    //            
  

	// Salvando o antigo antes de atualizar.
	// Para poder apagar daqui a pouco.
	// Atualizando.
    saved_mouse_x = mouse_x;
    saved_mouse_y = mouse_y;
    update_mouse (); 
 
    // Agora vamos manipular os valores obtidos através da 
    // função de atualização dos valores.
    // A função de atualização atualizou os valores de
    // mouse_x e mouse_y.
    mouse_x = (mouse_x & 0x000003FF );
    mouse_y = (mouse_y & 0x000003FF );

	// #importante:
	// Checando limites.
	// Isso é provisório.

    if ( mouse_x < 1 ){ mouse_x = 1; }
    if ( mouse_y < 1 ){ mouse_y = 1; }
    if ( mouse_x > (SavedX-16) ){ mouse_x = (SavedX-16); }
    if ( mouse_y > (SavedY-16) ){ mouse_y = (SavedY-16); }

    // Comparando o novo com o antigo, pra saber se o mouse se moveu.
    // #obs: Pra quem mandaremos a mensagem de moving ??
    if ( saved_mouse_x != mouse_x || saved_mouse_y != mouse_y )
    {
		// flag: o mouse está se movendo.
		// usaremos isso no keydown.
		// >> na hora de enviarmos uma mensagem de mouse se movendo
		// se o botão estiver pressionado então temos um drag (carregar.)
		// um release cancela o carregar.
		
        ps2_mouse_moving = 1;

       // draw

       // Apaga o antigo.
       // + Copia no LFB um retângulo do backbuffer 
       // para apagar o ponteiro antigo.
       refresh_rectangle ( saved_mouse_x, saved_mouse_y, 20, 20 );
                
       // Acende o novo.
       //+ Decodifica o mouse diretamente no LFB.
       // Copiar para o LFB o antigo retângulo  
       // para apagar o ponteiro que está no LFB.
       bmpDisplayMousePointerBMP ( mouseBMPBuffer, mouse_x, mouse_y );   
                         
    }else{
		
		// Não redesenhamos quando o evento for um click, sem movimento.
        ps2_mouse_moving = 0;
    }; 

    // Botão
    // Apenas obtendo o estado dos botões.
    mouse_buttom_1 = 0;
    mouse_buttom_2 = 0;
    mouse_buttom_3 = 0;



	// ## LEFT ##
    if ( ( mouse_packet_data & MOUSE_LEFT_BUTTON ) == 0 )
    {
		//liberada.
        mouse_buttom_1 = 0;
        ps2_button_pressed = 0;
        
        //mudamos sempre que pressionar.
        //todo: mudaremos sempre que pressionar numa title bar.
        //refresh_rectangle ( saved_mouse_x, saved_mouse_y, 20, 20 );
        //bmpDisplayMousePointerBMP ( mouseBMPBuffer, mouse_x, mouse_y ); 

    }else if( ( mouse_packet_data & MOUSE_LEFT_BUTTON ) != 0 )
     {
		    //pressionada.
		    //Não tem como pressionar mais de um botão por vez.
            mouse_buttom_1 = 1;
            mouse_buttom_2 = 0;
            mouse_buttom_3 = 0;
            ps2_button_pressed = 1;
            
            //mudamos sempre que pressionar.
            //todo: mudaremos sempre que pressionar numa title bar.
            //refresh_rectangle ( saved_mouse_x, saved_mouse_y, 20, 20 );
            //bmpDisplayMousePointerBMP ( appIconBuffer, mouse_x, mouse_y ); 
     };



	// ## RIGHT ##
    if ( ( mouse_packet_data & MOUSE_RIGHT_BUTTON ) == 0 )
    {
	    //liberada.
        mouse_buttom_2 = 0;
        ps2_button_pressed = 0;

    }else if( ( mouse_packet_data & MOUSE_RIGHT_BUTTON ) != 0 )
        {
		    //pressionada.
		    //Não tem como pressionar mais de um botão por vez.
            mouse_buttom_1 = 0;
            mouse_buttom_2 = 1;
            mouse_buttom_3 = 0;
            ps2_button_pressed = 1;
        };



	// ## MIDDLE ##
    if ( ( mouse_packet_data & MOUSE_MIDDLE_BUTTON ) == 0 )
    {
	    //liberada.
        mouse_buttom_3 = 0;
        ps2_button_pressed = 0;

    }else if( ( mouse_packet_data & MOUSE_MIDDLE_BUTTON ) != 0 )
        {
	        //pressionada.
	        //Não tem como pressionar mais de um botão por vez.
	        mouse_buttom_1 = 0;
	        mouse_buttom_2 = 0;
	        mouse_buttom_3 = 1;
	        ps2_button_pressed = 1;
        };


	// ===
	// Confrontando o estado atual com o estado anterior para saber se ouve 
	// alguma alteração ou não.
	// 1 = ouve alteração.

    if ( mouse_buttom_1 != old_mouse_buttom_1 ||
         mouse_buttom_2 != old_mouse_buttom_2 ||
         mouse_buttom_3 != old_mouse_buttom_3 )
    {
        mouse_button_action = TRUE;
    }else{
        mouse_button_action = FALSE;
    };
}


/*
 ********************************************************
 * mouseHandler:
 *     Handler de mouse. 
 *
 * *Importante: 
 *     Se estamos aqui é porque os dados disponíveis no controlador 8042 
 * pertencem ao mouse.
 *
 * Obs: 
 * Temos externs no início desse arquivo.
 */

void mouseHandler (void)
{

	// #importante:
	// Essa será a thread que receberá a mensagem.
	//struct thread_d *t;


	// #importante:
	// Essa será a janela afetada por qualquer evento de mouse.
	// ID de janela.

    //struct window_d *Window;
    //int wID; 
    
    //#test
    //int last_wID;

	// Coordenadas do mouse.
	// Obs: Isso pode ser global.
	// ?? O tratador em assembly tem as variáveis globais do posicionamento.

    int posX = 0;
    int posY = 0;


	// Lendo um char no controlador.
    char *_byte;
    
    
    int msg_status=-1; //FAIL


    // Disable keyboard.
    wait_then_write (0x64,0xAD); 


    //#todo: Isso é um teste.
    // O mouse ps2 está desabilitado porém recebendo as interupções
    // Os aplicativos podem reabilitá-lo a qualquer momento.
    // Atribuindo foco por exemplo.
    
    //#bugbug
    //Isso realmente paraliza o mouse. Mas reabilitar não está funcionando.
    //if ( ps2_mouse_status == 0 )
    //{
    //      return;
    // }


	//Char para o cursor provisório.
	//#todo: Isso foi subtituido por uma bmp. Podemos deletar.
    //static char mouse_char[] = "T";


	//
	// Read !
	//

	// #obs:
	// Lendo um char no controlador.
	// #importante:
	// Contagem de interruções:
	// #obs: 
	// Precisamos esperar 3 interrupções.
	// #obs: 
	// count_mouse é global. Provavelmente nesse arquivo mesmo.

    *_byte = (char) xxx_mouse_read();

    switch (count_mouse){

        // > Essa foi a primeira interrupção.
        case 0:
            //Pegamos o primeiro char.
            buffer_mouse[0] = (char) *_byte;
            if (*_byte & MOUSE_V_BIT){ count_mouse++; }
            break;

        // >> Essa foi a segunda interrupção.
        case 1:
            //Pegamos o segundo char.
            buffer_mouse[1] = (char) *_byte;
            count_mouse++;
            break;

        // >>> Essa foi a terceira interrupção. É a última.
        case 2:
            //Pegamos o terceiro char.
            buffer_mouse[2] = (char) *_byte;
            count_mouse = 0;
            
            //
            // == Message ==========================================
            //
            
            
            if (current_input_mode == INPUT_MODE_SETUP )
            {
                    // #todo
                    // Nao precisamos fazer esse parse aqui ...
                    // apenas mandar o pacote para o window server em ring3
                    // na forma de mensagens.
                    // Tambem nao precisamos escanear janelas ... o ws fara isso.
                ps2mouse_parse_data_packet();

                // #bugbug
                // Escaneando janelas.
                // O window server deveria fazer isso.

                // Estamos mandando o evento para a thread associada `a
                // janela 'a qual o mouse esta passando por cima.
                 // Isso nao muda a thread que esta em foreground.

                // vt/draw/model/kgws.c

                kgws_mouse_scan_windows();
            }

            
            // O driver precisa do old pra configurar a variável de ação.
            // #todo Talvez precise de outras
            
            old_mouse_buttom_1 = mouse_buttom_1;
            old_mouse_buttom_2 = mouse_buttom_2;
            old_mouse_buttom_3 = mouse_buttom_3;
            break;



        // Problemas na contagem de interrupções.
        default:
            count_mouse = 0;
            break;
    };

    // Reanable keyboard.
    wait_then_write (0x64,0xAE); 
}



// =====================================================
// #bugbug
// Danger Danger !!
// =====================================================

void expect_ack (void)
{
    // #bugbug
    // ? loop infinito  
    
    while ( xxx_mouse_read() != 0xFA);
}


void set_ps2_mouse_status(int status)
{
    ps2_mouse_status = status;
}


int get_ps2_mouse_status(void)
{
    return (int) ps2_mouse_status;
}


/*
 * ps2_mouse_dialog:
 *  
 */

unsigned long 
ps2_mouse_dialog ( 
    int msg,
    unsigned long long1,
    unsigned long long2 )
{

    //if ( msg<0 )
        //return 0;

    switch (msg){

        //habilitar
        case 4000:
            printf ("ps2_mouse_dialog: 4000\n");
            refresh_screen();
            ps2_mouse_status = 1;
            break;

        //desabilitar.
        case 4001:
            printf ("ps2_mouse_dialog: 4001\n");
            refresh_screen();
            ps2_mouse_status = 0;
            break;

        //#test
        // reinicializar ??
        //case 4002:
            //break;
            
        default:
            break;
    };

    return 0;
}


//
// End.
//

