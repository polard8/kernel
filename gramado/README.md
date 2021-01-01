# gramci - setup

	Gramado Consistent Interface
	Setup environment.
	
	
	==========================================
	apps:
	This is the client-side applications for the system services.
	It uses a ring3 loadable window server called gwssrv, 
	codename Aurora. The client-side library for this is called libgws.
	GUI applications.
	It uses socket connections.
	
	==========================================
	cmd:
	Standard unix-like commands.
	It will run on virtual consoles and virtual terminals.
	It uses the rtl.
	
	===========================================
	grass:
	This is ring applications that uses the kernel services and
	the kgws window server embedded inside the base kernel.
	It uses the libcore library.
	GUI applications.

	==========================================
	apps:
	More Aurora apps, but only for network support.
	
	
