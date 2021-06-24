
// i8042.h 

#ifndef ____I8042_H
#define ____I8042_H    1

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


// x86
//#define KEYBOARD_VECTOR 1
//#define MOUSE_VECTOR  12


#define I8042_BUFFER 0x60
#define I8042_STATUS 0x64
#define I8042_BUFFER_FULL 0x01
#define I8042_KEYBOARD_BUFFER 0x00
#define I8042_MOUSE_BUFFER 0x20
#define I8042_WHICH_BUFFER 0x20


#define I8042_DATAPORT          0x60	//Read/Write
#define I8042_STATUSREGISTER    0x64	//Read
#define I8042_COMMANDREGISTER   0x64	//Write


// i8042 commands.
#define I8042_READ                 0x20
#define I8042_WRITE                0x60
#define I8042_DISABLE_SECOND_PORT  0xA7  // Disable second PS/2 port (only if 2 PS/2 ports supported)
#define I8042_ENABLE_SECOND_PORT   0xA8  // Enable second PS/2 port (only if 2 PS/2 ports supported)
#define I8042_TEST_SECOND_PORT     0xA9  // Test second PS/2 port (only if 2 PS/2 ports supported)
#define I8042_TEST_FIRST_PORT      0xAB  // Test first PS/2 port
#define I8042_DISABLE_FIRST_PORT   0xAD  // Disable first PS/2 port
#define I8042_ENABLE_FIRST_PORT    0xAE  // Enable first PS/2 port
//...

// i8042 responses.
#define I8042_ACKNOWLEDGE         0xFA        
#define I8042_RESEND              0xFE

#define I8042_TESTCONTROLLER  0xAA	       // Test PS/2 Controller
#define I8042_TESTCONTROLLER_PASSED  0x55  // test passed
#define I8042_TESTCONTROLLER_FAILED  0xFC  // test failed

 
//TESTING FIRST PORT.
#define I8042_TEST_FIRST_PORT_PASSED      0x00  //test passed
#define I8042_TEST_FIRST_PORT_CLOCK_LOW   0x01  //clock line stuck low
#define I8042_TEST_FIRST_PORT_CLOCK_HIGH  0x02  //clock line stuck high
#define I8042_TEST_FIRST_PORT_DATA_LOW    0x03  //data line stuck low
#define I8042_TEST_FIRST_PORT_DATA_HIGH   0x04  //data line stuck high

//TESTING SECOND PORT.
#define I8042_TEST_SECOND_PORT_PASSED      0x00  //test passed
#define I8042_TEST_SECOND_PORT_CLOCK_LOW   0x01  //clock line stuck low
#define I8042_TEST_SECOND_PORT_CLOCK_HIGH  0x02  //clock line stuck high
#define I8042_TEST_SECOND_PORT_DATA_LOW    0x03  //data line stuck low
#define I8042_TEST_SECOND_PORT_DATA_HIGH   0x04  //data line stuck high

// Configuration Byte
//Bit  Meaning
//0	   First PS/2 port interrupt (1 = enabled, 0 = disabled)
//1	   Second PS/2 port interrupt (1 = enabled, 0 = disabled, only if 2 PS/2 ports supported)
//2	   System Flag (1 = system passed POST, 0 = your OS shouldn't be running)
//3	   Should be zero
//4	   First PS/2 port clock (1 = disabled, 0 = enabled)
//5	   Second PS/2 port clock (1 = disabled, 0 = enabled, only if 2 PS/2 ports supported)
//6	   First PS/2 port translation (1 = enabled, 0 = disabled)
//7	   Must be zero

//Detecting PS/2 Device Types
//Send the "disable scanning" command 0xF5 to the device
//Wait for device to send "ACK" back (0xFA)
//Send the "identify" command 0xF2 to the device
//Wait for device to send "ACK" back (0xFA)
//Wait for device to send up to 2 bytes of reply, with a time-out to determine 
//when it's finished (e.g. in case it only sends 1 byte)

//retorna 1 ou 2 bytes.
#define I8042_DEVICETYPE_STANDARD_PS2_MOUSE       0x00  //Standard PS/2 mouse
#define I8042_DEVICETYPE_MOUSE_WITH_SCROLL_WHELL  0x03  //Mouse with scroll wheel
#define I8042_DEVICETYPE_5BUTTON_MOUSE            0x04  //5-button mouse
//0xAB, 0x41 or 0xAB, 0xC1	MF2 keyboard with translation enabled in the PS/Controller (not possible for the second PS/2 port)
//0xAB, 0x83	MF2 keyboard

//
// == prototypes ==================
//

void I8042Controller_do_drain(void);

void prepare_for_input (void);
void prepare_for_output (void);

unsigned char wait_then_read (int port);
void wait_then_write ( int port, int data );


#endif    



















