


//usb.h  usb header.


/*
    The USB host controllers have their own specifications. 
	With USB 1.1, there were two Host Controller Interface Specifications, 
	UHCI (Universal Host Controller Interface) developed by Intel 
	which puts more of the burden on software (Microsoft) and 
	allowing for cheaper hardware and the OHCI (Open Host Controller Interface) 
	developed by Compaq, Microsoft and National Semiconductor which 
	places more of the burden on hardware(Intel) and makes for simpler software. 
	Typical hardware / software engineer relationship. . .

    With the introduction of USB 2.0 a new Host Controller Interface Specification was needed 
	to describe the register level details specific to USB 2.0. 
	The EHCI (Enhanced Host Controller Interface) was born. 
	Significant Contributors include Intel, Compaq, NEC, Lucent and Microsoft 
	so it would hopefully seem they have pooled together to provide us one 
	interface standard and thus only one new driver to implement in our operating systems. 
	Its about time.
*/

void usbInit();


//
//
//


