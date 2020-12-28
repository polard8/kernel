# gramnt - ge

	Gramado New Technologies
	Gramado Engine
	Game Engine environment.

	========================================================
	aurora:
	This is a ring3 window server.

	========================================================
	boot:
	The gramado boot loader.

	========================================================
	fonts:
	The fonts.

	========================================================
	init:
	The init process.
	It's a ring3 process used to initialize the system.

	========================================================
	kernel:
	The base kernel.
	
	========================================================
	The libs:
	
	lib/
	Gramado User-Mode client-side libraries for
	the system services.

	libcore/
	Gramado User-Mode API.
	This is used by the applications to call some GUI routines and some
	system routines inside the kernel via syscalls.
	It uses the kgws windows server, embedded inside the base kernel.
	
	/rtl/
	Gramado User-Mode runtime library.
	It is a ring3 libc plus some wrappers with the rtl_ prefix.

	========================================================
	sevices:
	Some system servies. Drivers and server.
