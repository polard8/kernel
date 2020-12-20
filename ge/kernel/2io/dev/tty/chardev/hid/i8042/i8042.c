/*
 * File: i8042/i8042.c
 *     i8042 controller initialization.
 *     initialize ps2 controller.
 * env:
 *     Ring 0. Kernel base persistent code.
 * 2018 - Created by Fred Nora.
 */


 
// When the keyboard and mouse are USB devices, the BIOS uses SMM code 
// to emulate PS/2 devices. 
// I see mentioned that the USB devices should halt ps/2 emulation 
// once they've been initialized (or at least their host hub?)


#include <kernel.h>



void I8042Controller_do_drain(void)
{
    //#define I8042_BUFFER 0x60
    //#define I8042_STATUS 0x64
    //#define I8042_BUFFER_FULL 0x01
    
    unsigned char status=0;
    
    for (;;) {
        status = in8(0x64);
        if (!(status & 0x01)){ return;}  //empty
        in8(0x60);
    }
}


/*
 *********************
 * kbdc_wait:
 *     Espera por flag de autorização para ler ou escrever.
 */

#define __local_out_any_b(p)  asm volatile ( "outb %%al,%0" : : "dN"((p)) : "eax" )

// Espera para ler ou para escrever!

#define __I8042_BUFFER_FULL 0x01

void kbdc_wait (unsigned char type)
{
    unsigned char Status=0;

    // 0 = READ
    if (type==0)
    {
        for (;;) 
        {
            Status = in8(0x64);
           
           // Sinalizado que o buffer ta cheio.
           // # Somente para mouse.
           // See: serenity os.
           if ( (Status & __I8042_BUFFER_FULL) != 0 )  
               return;

            // #todo: delay
            // __local_out_any_b (0x80);
            // wait_ns (400);

        };
    }


    // 1 = WRITE
    if (type==1)
    {
        for (;;)
        {
            if ( !(in8(0x64) & 2) )
                return;
            
            // #todo: delay
            // __local_out_any_b (0x80);
            // wait_ns (400);
        };
    };
}



// =======================
// prepare ..

void prepare_for_input(void)
{
    // 0 = READ
    kbdc_wait(0);
}

void prepare_for_output(void)
{
    // 1 = WRITE
    kbdc_wait(1);
}

//====================================================================


/*
void I8042Controller_prepare_for_input(unsigned char device);
void I8042Controller_prepare_for_input(unsigned char device)
{
    // #define I8042_KEYBOARD_BUFFER 0x00
    // #define I8042_MOUSE_BUFFER 0x20
    // #define I8042_WHICH_BUFFER 0x20
    
    // 1 = KEYBOARD
    // 2 = MOUSE

    unsigned char status=0;
    unsigned char buffer_type = 0; 

    //ASSERT(m_lock.is_locked());
    
        
    switch (device)
    {
        // keyboard.
        case 1:
            buffer_type = I8042_KEYBOARD_BUFFER;
            break;

        // mouse.
        case 2:
            buffer_type = I8042_MOUSE_BUFFER;
            break;

        // invilid device.
        default:
            return;
            break; 
    };


    for (;;) {
        
        status = in8(I8042_STATUS);
        
        if (   (status & I8042_BUFFER_FULL) && 
             ( (status & I8042_WHICH_BUFFER) == buffer_type ) )
        {
            return;
        }
    };
}
*/


/*
void I8042Controller_prepare_for_output(void);
void I8042Controller_prepare_for_output(void)
{
    //ASSERT(m_lock.is_locked());
    
    for (;;) {
        if (!(in8(I8042_STATUS) & 2))
            return;
    };
}
*/



//====================================================================

/*
u8 I8042Controller::do_write_to_device(Device device, u8 data)
{
    ASSERT(device != Device::None);
    ASSERT(m_lock.is_locked());

    ASSERT(!Processor::current().in_irq());

    int attempts = 0;
    u8 response;
    do {
        if (device != Device::Keyboard) {
            prepare_for_output();
            IO::out8(I8042_STATUS, 0xd4);
        }
        prepare_for_output();
        IO::out8(I8042_BUFFER, data);

        response = do_wait_then_read(I8042_BUFFER);
    } while (response == I8042_RESEND && ++attempts < 3);
    if (attempts >= 3)
        dbg() << "Failed to write byte to device, gave up";
    return response;
}
*/

/*
u8 I8042Controller::do_read_from_device(Device device)
{
    ASSERT(device != Device::None);

    prepare_for_input(device);
    return IO::in8(I8042_BUFFER);
}
*/

//====================================================================


// =======================
// wait then ...

unsigned char wait_then_read (int port)
{
    prepare_for_input();
    return (unsigned char) in8 (port);
}

void wait_then_write ( int port, int data )
{
    prepare_for_output();
    out8 ( port, data );
}



/*
 ***************
 * ps2:
 *     Inicializa o controlador ps2.
 * 
 *     Essa rotina de inicialização do controlador 
 * poderá ter seu próprio módulo.
 * 
 *     Inicializa a porta do teclado no controlador.
 *     Inicializa a porta do mouse no controlador.
 *     Obs: *importante: A ordem precisa ser respeitada.
 *     As vezes os dois não funcionam ao mesmo tempo se a 
 *     inicialização não for feita desse jeito. 
 */


// Essa eh uma inicializaçao completa.

void ps2 (void)
{

    unsigned char configuration=0;
    int keyboard_available = 0;
    int mouse_available = 0;
 
 
	// #debug
    printf ("ps2: Initializing..\n");
    refresh_screen();

    // The main structure fisrt of all.
    // #todo: create ps_initialize_main_structure();
    PS2.used = 1;
    PS2.magic = 1234;
    PS2.pooling = FALSE;
    PS2.keyboard_initialized = FALSE;
    PS2.mouse_initialized = FALSE;

    // Zerando estruturas que precisam serem reinicializadas.
    
    //keyboard
    PS2KeyboardDeviceObject = NULL;
    PS2KeyboardDevice = NULL;
    PS2KeyboardDeviceTTYDriver = NULL;
    PS2KeyboardDeviceTTY = NULL;
    
    //mouse
    PS2MouseDeviceObject = NULL;
    PS2MouseDevice = NULL;
    PS2MouseDeviceTTYDriver = NULL;
    PS2MouseDeviceTTY = NULL;



    // ======================================
    // Deactivate ports!
    // Disable devices
    wait_then_write (0x64,0xAD);  // Disable keyboard port.
    wait_then_write (0x64,0xA7);  // Disable mouse port. ignored if it doesn't exist

    // Drain buffers
    I8042Controller_do_drain();

    // # todo
    // # Essa rotina desabilita as irqs
    // precisamos reabilita-las ao fim da inicializaçao
    wait_then_write (0x64,I8042_READ);    // I8042_READ = 0x20    
    configuration = wait_then_read(0x60);
    //wait_then_write (0x64,I8042_WRITE);   // I8042_WRITE = 0x60
    //configuration &= ~3; // Disable IRQs for all
    //wait_then_write (0x60,configuration);   

    //checa um bit.
    int is_dual_channel=0;
    is_dual_channel = (configuration & (1 << 5)) != 0;
    if(is_dual_channel == 1)
        printk("Dual\n");
    if(is_dual_channel == 0)
        printk("Single\n");


    // Perform controller self-test
    wait_then_write(I8042_STATUS, 0xaa);
    if (wait_then_read(I8042_BUFFER) == 0x55) {
        // Restore configuration in case the controller reset
        wait_then_write(I8042_STATUS, 0x60);
        wait_then_write(I8042_BUFFER, configuration);
     } else {
         printk( "I8042: Controller self test failed\n");
     };


    // ==============================
    // Test ports and enable them if available

    // testar se o keyboard esta disponivel.
    wait_then_write(I8042_STATUS, 0xab); // test
    keyboard_available = (wait_then_read(I8042_BUFFER) == 0);

    // testar se o mouse esta disponivel.
    // pra isso precisamos ser dual channel.
    if (is_dual_channel == 1) {
        wait_then_write(I8042_STATUS, 0xa9); // test
        mouse_available = (wait_then_read(I8042_BUFFER) == 0);
    }

    // imprimir o resultado da disponibilidade.
    
    if (keyboard_available ==1){
        printk("~ Keyboard available\n");
        ps2kbd_initialize_device ();
        PS2.keyboard_initialized = TRUE;
        wait_then_write(I8042_STATUS, 0xae); //enable
        configuration |= 1;
        configuration &= ~(1 << 4);
    }

    if (mouse_available ==1){
        printk("~ Mouse available\n");
        ps2mouse_initialize_device ();
        PS2.mouse_initialized = TRUE;
        wait_then_write(I8042_STATUS, 0xa8); // enable
        configuration |= 2;
        configuration &= ~(1 << 5);
    }
    // ==============================
  


   //#todo
   // Enable IRQs for the ports that are usable
   if (keyboard_available || mouse_available) {
       configuration &= ~0x30; // renable clocks
       wait_then_write(I8042_STATUS, 0x60);
       wait_then_write(I8042_BUFFER, configuration);
    }  


    //==========================

    // Wait for nothing!
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);

    // Done.

    //#debug
    printf ("ps2: done\n");
    refresh_screen();
}



/*
 ************************************************************
 * early_ps2_init:
 * 
 * 
 */

// Inicialização preliminar. Sem mouse.
// Ela existe porque a emulação de ps2 na máquina real 
// apresenta falhas.
// No gdeshell.bin incluiremos os comando "ps2-init"
// para obtermos a inicialização completa.

// #importante
// Nao chamamos a rotina de inicializaçao do mouse.
// mas poderiamos. O importante eh deixar a porta desabilitada
// ao final da rotina.
// Ao fim dessa rotina, reabilitamos apenas a porta de teclado.
// A porta de mouse permaneçe fechada.

void early_ps2_init (void)
{
    // mas simples...
    // apenas teclado.

	// #debug
	printf ("early_ps2_init: Initializing..\n");
	refresh_screen();

    // The main structure fisrt of all.
    // #todo: create ps_initialize_main_structure();
    PS2.used = 1;
    PS2.magic = 1234;
    PS2.pooling = FALSE;
    PS2.keyboard_initialized = FALSE;
    PS2.mouse_initialized = FALSE;


    // Zerando estruturas que precisam serem reinicializadas.
    
    //keyboard
    PS2KeyboardDeviceObject = NULL;
    PS2KeyboardDevice = NULL;
    PS2KeyboardDeviceTTYDriver = NULL;
    PS2KeyboardDeviceTTY = NULL;
    
    //mouse
    PS2MouseDeviceObject = NULL;
    PS2MouseDevice = NULL;
    PS2MouseDeviceTTYDriver = NULL;
    PS2MouseDeviceTTY = NULL;


    // ======================================
    // Deactivate ports!
    wait_then_write (0x64,0xAD);  //Disable keyboard port.
    wait_then_write (0x64,0xA7);  //Disable mouse port.


    // Keyboard.
    printf ("early_ps2_init: Initializing keyboard ..\n");
    refresh_screen();
    ps2kbd_initialize_device ();
    PS2.keyboard_initialized = TRUE;

    // Mouse.
    //printf ("ps2: Initializing mouse ..\n");
    //refresh_screen();
    //ps2mouse_initialize_device ();
    PS2.mouse_initialized = FALSE;


    // ======================================
    // Reactivate ports!
    wait_then_write (0x64,0xAE);    // Reenable keyboard port.
    //wait_then_write (0x64,0xA8);  // do NOT reenable the mouse port.


    // We can call this one.
    // wait_then_write (0x64,0xA7);  //Disable mouse port.


    // Wait for nothing!
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);
    kbdc_wait (1);

    // Done.

    //#debug
    printf ("early_ps2_init: done\n");
    refresh_screen();
}



// This is called by gdeshell.
int PS2_initialize(void)
{
	ps2();
	return 0;
}

// this is called during the kernel initialization.
int PS2_early_initialization(void)
{
	early_ps2_init();
	return 0;
}



// See:
// ps2.h
int ps2_ioctl ( int fd, unsigned long request, unsigned long arg )
{
    debug_print("ps2_ioctl: [TODO]\n");
    return -1;
}


//
// End.
//

