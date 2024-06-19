
// i8042.c
// Intel 8042 keyboard/mouse controller.
// Created by Fred Nora.

#include <kernel.h>  

// ??
// #todo
// Were was defined the 'PS2' confugyration structure?
// See: input/i8042/ps2.h


//Initialising the PS/2 Controller (OSDev Wiki)
//Step 1: Initialise USB Controllers
//Step 2: Determine if the PS/2 Controller Exists
//Step 3: Disable Devices
//Step 4: Flush The Output Buffer
//Step 5: Set the Controller Configuration Byte
//Step 6: Perform Controller Self Test
//Step 7: Determine If There Are 2 Channels
//Step 8: Perform Interface Tests
//Step 9: Enable Devices
//Step 10: Reset Devices

// ------------------------------------
// #local
// #bugbug?
// Is this the best option for x86_64?
#define __local_out_any_b(p)  \
    asm volatile ("outb %%al, %0" :: "dN"((p)) : "eax")


// List of legacy devices.
// 'file->device'
struct device_d  *PS2KeyboardDevice;
struct device_d  *PS2MouseDevice;
// ...

// Objects
file *PS2KeyboardDeviceObject;
file *PS2MouseDeviceObject;
// ...

// ttys
struct tty_d *PS2KeyboardDeviceTTY;
struct tty_d *PS2MouseDeviceTTY;
// ...

// tty drivers
struct ttydrv_d *PS2KeyboardDeviceTTYDriver;
struct ttydrv_d *PS2MouseDeviceTTYDriver;
// ...

/*
// #todo: Get these info with HAL.
static int i8042_keyboard_irq=0;
static int i8042_mouse_irq=0;
static unsigned long i8042_keyboard_interrupt_handler=0;
static unsigned long i8042_mouse_interrupt_handler=0;
*/

static void __ps2_wait(unsigned char type);

//-------------------------------------

void I8042Controller_do_drain(void)
{
    unsigned char status=0;
    unsigned char byte=0;

    //debug_print("I8042Controller_do_drain:\n");
    while (1){
        status = (unsigned char) in8(0x64);
        // Empty?
        if (!(status & I8042_STATUS_OUTPUT_BUFFER_FULL)){
            return;
        }  
        byte = (unsigned char) in8(0x60);
    };
}

// __ps2_wait:
// Espera por flag de autorização para ler ou escrever.
// #todo: Descreva pra que serve o bit 1. valor 2.
static void __ps2_wait (unsigned char type)
{
    unsigned char StatusChar=0;
    unsigned char Type = (type & 0xFF);
    int i=0;
    int timeout=10000;

// =====================================
// 0 = READ
// Sinalizado que o buffer ta cheio.
// # Somente para mouse.
// See: serenity os.
// Quando for '1' eu saio.
    if (Type==0)
    {
        for (i=0; i<timeout; i++) 
        {
            StatusChar = (unsigned char) in8(0x64);
            if ( (StatusChar & I8042_STATUS_OUTPUT_BUFFER_FULL) != 0 )
            {
               __local_out_any_b (0x80);
               return;
            }
        };
        return;
    }

// =====================================
// 1 = WRITE
// Quando for '0', eu saio.
    if (Type==1)
    {
        for (i=0; i<timeout; i++)
        {
            if ( !(in8(0x64) & I8042_STATUS_INPUT_BUFFER_FULL) )
            {
                __local_out_any_b (0x80);
                return;
            }
        };
        return;
    }
}  

void prepare_for_input(void)
{
// 0 = READ
    __ps2_wait(0);
}

void prepare_for_output(void)
{
// 1 = WRITE
    __ps2_wait(1);
}

// =======================
// wait then ...

unsigned char wait_then_read(int port)
{
    prepare_for_input();
    return (unsigned char) in8(port);
}

void wait_then_write( int port, int data )
{
    prepare_for_output();
    out8( port, data );
}

// ??
int PS2_initialize(void)
{
    debug_print ("PS2_initialize: [TODO]\n");
    //ps2();
    return 0;
}

// Early initialization
// + Only keyboard.
// + No mouse initialization.
int PS2_early_initialization(void)
{
    debug_print ("PS2_early_initialization:\n");

// Port 1: keyboard
    ps2kbd_initialize_device();
    PS2.keyboard_initialized = TRUE;

// Port 2: Mouse
// We will not call the mouse initialization 
// in the early ps2 initialization routine.
    PS2.mouse_initialized = FALSE;
    PS2Mouse.initialized = FALSE;

    PS2.pooling = FALSE;
    PS2.used = TRUE;
    PS2.magic = 1234;

    return 0;
}

// This is called during the kernel initialization.
// Called by I_x64main in x64init.c
int PS2_initialization(void)
{
    debug_print("PS2_initialization:\n");

// Port 1: Keyboard
    ps2kbd_initialize_device();
    PS2.keyboard_initialized = TRUE;

// Port 2: Mouse
    ps2mouse_initialize_device();
    PS2.mouse_initialized = TRUE;

    PS2.pooling = FALSE;
    PS2.used = TRUE;
    PS2.magic = 1234;

    return 0;
}


/*
 * ps2:
 *     Inicializa o controlador ps2.
 *     Essa rotina de inicialização do controlador 
 * poderá ter seu próprio módulo.
 *     Inicializa a porta do teclado no controlador.
 *     Inicializa a porta do mouse no controlador.
 *     Obs: *importante: A ordem precisa ser respeitada.
 *     As vezes os dois não funcionam ao mesmo tempo se a 
 *     inicialização não for feita desse jeito. 
 */
// Essa é uma inicializaçao completa.
// See:
// https://wiki.osdev.org/%228042%22_PS/2_Controller

void ps2(void)
{
// PS2 full initialization.

    int keyboard_available = FALSE;
    int mouse_available = FALSE;
    unsigned char configuration=0;
    int is_dual_channel=0;

    // #debug
    printk ("ps2: Initializing..\n");
    //refresh_screen();

    // The main structure fisrt of all.
    // #todo: create ps_initialize_main_structure();
    PS2.used = TRUE;
    PS2.magic = 1234;
    PS2.keyboard_initialized = FALSE;
    PS2.mouse_initialized = FALSE;
    PS2.pooling = FALSE;

// Zerando as estruturas que precisam serem reinicializadas.

// keyboard
    PS2KeyboardDeviceObject    = NULL;
    PS2KeyboardDevice          = NULL;
    PS2KeyboardDeviceTTYDriver = NULL;
    PS2KeyboardDeviceTTY       = NULL;
// mouse
    PS2MouseDeviceObject    = NULL;
    PS2MouseDevice          = NULL;
    PS2MouseDeviceTTYDriver = NULL;
    PS2MouseDeviceTTY       = NULL;

// See the steps in:
// https://wiki.osdev.org/%228042%22_PS/2_Controller

// ======================================
// Disable devices
// Deactivate ports!
    wait_then_write (0x64,0xAD);  // Disable keyboard port.
    wait_then_write (0x64,0xA7);  // Disable mouse port. ignored if it doesn't exist
    // =================

// Drain buffers
    I8042Controller_do_drain();

//
// configuration byte
//

    // # todo
    // # Essa rotina desabilita as irqs
    // precisamos reabilita-las ao fim da inicializaçao
    wait_then_write(0x64, I8042_READ);    // I8042_READ = 0x20    
    configuration = wait_then_read(0x60);
    //wait_then_write (0x64,I8042_WRITE);   // I8042_WRITE = 0x60
    //configuration &= ~3; // Disable IRQs for all
    //wait_then_write (0x60,configuration);   

// Check if ti is dual channel or not.
// Checa um bit.
// While you've got the Configuration Byte, 
// test if bit 5 was set. If it was clear, 
// then you know it can't be a "dual channel" PS/2 controller 
// (because the second PS/2 port should be disabled). 
// #todo: Create a flag in the structure to indicate this feature.

    is_dual_channel = (configuration & (1 << 5)) != 0;
    if (is_dual_channel == 1){ printk("Dual\n");   }
    if (is_dual_channel == 0){ printk("Single\n"); }

    // #define SELF_TEST_SUCCESS 0x55

// Perform controller self-test
// To test the PS/2 controller, send command 0xAA to it. 
// Then wait for its response and check it replied with 0x55.
    
    wait_then_write(I8042_STATUS, 0xAA);
    
    if (wait_then_read(I8042_BUFFER) == 0x55){
        printk( "I8042: Self test OK\n");
        // Restore configuration in case the controller reset
        // At the very least, the Controller Configuration Byte 
        // should be restored for compatibility with such hardware.
        wait_then_write(I8042_STATUS, 0x60);
        wait_then_write(I8042_BUFFER, configuration);
     } else {
         panic ( "I8042: [FATAL.FIXME] Controller self test failed\n");
     };

// Step 8: 
// Perform Interface Tests 
// This step tests the PS/2 ports. 
// Use command 0xAB to test the first PS/2 port, 
// then check the result. 
// Then (if it's a "dual channel" controller) use command 0xA9 
// to test the second PS/2 port, then check the result. 
// Nesse momento podemos desistir se a porta que queremos não
// está disponível. Ou prosseguirmos apenas com o que temos.
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

//#define STAT_OUTFULL         (1<<0)
//#define STAT_INFULL         (1<<1)
//#define STAT_SYSTEM_FLAG      (1<<2)
//#define STAT_FOR_CONTROLER   (1<<3)
//#define STAT_SPECIFIC      (1<<4)
//#define STAT_MOUSE_DATA      (1<<5)
//#define STAT_TIMEOUT_ERR      (1<<6)
//#define STAT_PARITY_ERR      (1<<7)

//#define CONFIG_PORT1_INT      (1<<0)
//#define CONFIG_PORT2_INT      (1<<1)
//#define CONFIG_SYSTEM_FLAG   (1<<2)
//#define CONFIG_ZERO1         (1<<3)
//#define CONFIG_PORT1_CLK_DS   (1<<4)
//#define CONFIG_PORT2_CLK_DS   (1<<5)
//#define CONFIG_PORT1_TRANSL   (1<<6)
//#define CONFIG_ZERO2         (1<<7)

// Step 9: 
// Enable Devices 
// imprimir o resultado da disponibilidade.

    if (keyboard_available == 1){
        //printk("----\n");
        printk("~ Keyboard available\n");
        ps2kbd_initialize_device();
        PS2.keyboard_initialized = TRUE;
        wait_then_write(I8042_STATUS, 0xae);  // enable keyboard port
        
        //ignoramos isso se é single channel
        // configuration |= 1;
        // configuration &= ~(1 << 4);
        // wait_then_write(I8042_STATUS, 0x60);
        // wait_then_write(I8042_BUFFER, configuration);
    }

// If it is dual channel,
// send a command 0xA8 to enable the second PS/2 port and 
// read the Controller Configuration Byte again

    if (mouse_available == 1 ){

        //printk("----\n");
        printk("~ Mouse available\n");

        // #todo
        //ps2mouse_initialize_device();

        PS2.mouse_initialized = TRUE;
        wait_then_write(I8042_STATUS, 0xa8);  // enable mouse port

        //pega o config byte
        wait_then_write (0x64,I8042_READ);    // I8042_READ = 0x20    
        configuration = wait_then_read(0x60);

        // #todo
        // Now bit 5 of the Controller Configuration Byte should be clear - 
        // if it's set then you know it can't be a "dual channel" 
        // PS/2 controller (because the second PS/2 port should be enabled).
        
        configuration |= 2;
        configuration &= ~(1 << 5);
        wait_then_write(I8042_STATUS, 0x60);
        wait_then_write(I8042_BUFFER, configuration);
    
        // If it is a dual channel device, 
        // send a command 0xA7 to disable the second PS/2 port again. 
        // Lembre-se, vamos reabilitar no final.
        wait_then_write (0x64,0xA7);  // Disable mouse port. ignored if it doesn't exist
    }
    // ==============================

    //#todo
    // Enable IRQs for the ports that are usable
    if (keyboard_available || mouse_available) 
    {
        //pega o config byte
        //wait_then_write (0x64,I8042_READ);    // I8042_READ = 0x20    
        //configuration = wait_then_read(0x60);

       configuration &= ~0x30;  // renable clocks
       wait_then_write(I8042_STATUS, 0x60);
       wait_then_write(I8042_BUFFER, configuration);
    }  

//==========================

// Wait for nothing!
    __ps2_wait(1);
    __ps2_wait(1);
    //__ps2_wait(1);
    //__ps2_wait(1);

    //#debug
    printk("ps2: done\n");
}

// #todo
// ioctl
int ps2_ioctl( int fd, unsigned long request, unsigned long arg )
{
    debug_print("ps2_ioctl: [TODO]\n");
    return -1;
}

//
// End
//




