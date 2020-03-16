 
  This is the folder for the kernelbase's source code.
  Everything here is gonna run in ring 0, 32bit protected mode.


	2020 - Fred Nora
 
 
 List of folders:
 ================

/arch
    Entry point for different archtechtures.

/devices
    Device manager support.

/execve
    Executive layer inside the kernel base.
    This is the highest layer in the kernel base.
    Here your gonna fine all the wrappers for the services provided
    by the kernel base. crts, device management, systemcall interfaces and system management stuff.

/hal
    Hardware Abstraction Layer support 
    This is the lowest layer of the kernel base.
    Here your gonna find low level routine for archtechture dependent functions.
  
/kdrivers
    Permanent drivers included inside the kernel base.  
    All the drivers here is running in ring 0, inside the kernel base.
    In the future the system will be able to desable some drivers here and select a loadable one or back
    to the permaned kdriver.
    
/kservers
    Permanent servers running inside the kernel base. It has the same rules of the kdrivers, its not for
    controlling devices.    
    
/mk
    Microkernel support.
    Here is all the process structure support.
    It runs on ring 0, inside the kernel base.
    The main parts are, ipc, memory management and scheduler.
    	    

