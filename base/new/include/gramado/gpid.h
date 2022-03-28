
// gpid.h
// Managing the helper processes.


#ifndef __GPID_H
#define __GPID_H    1


//
// Maind processes
//

#define GRAMADO_PID_KERNEL    0
#define GRAMADO_PID_INIT      1
// ...

#define GRAMADO_PID_BASE    GRAMADO_PID_KERNEL



// #deprecated.
// Usaremos os valores acima.
// Bases para a contagem de processos, do sistema e de usu�rios. 
//Primeiro �ndice na contagem das processos do sistema.
//#define SYSTEM_BASE_PID 0
//Primeiro �ndice na contagem das processos dos usu�rios.  
//#define USER_BASE_PID 100    





// First of all.
// we need to register some processes.
// Registering 'folders'.



// 1) boot/
// This is the pre-kernel stuff.
// Register this folder is gonna be a noop.
// oops. pode existir nessa pasta também um processo
// de configuração da inicialização. why not?!
pid_t __gpidBoot;
//int register_bootsrv_process ( pid_t pid );


// 2) include/
pid_t __gpidInclude;
//int register_include_process ( pid_t pid ); //Noop!


// 3) init/
// init.bin
pid_t __gpidInit;
//int register_init_process ( pid_t pid );

// 4) install/
pid_t __gpidInstall;
//??

// 5) logoff
pid_t __gpidLogoff;
//int register_logoff_process ( pid_t pid );


// 6) logon/
pid_t __gpidLogon;
//int register_logon_process ( pid_t pid );


// 7) net/
// The net server.
// netsrv.bin
pid_t __gpidNetServer;
//int register_netsrv_process ( pid_t pid );


// 8) notify/
pid_t __gpidNotificationServer;
//int register_notify_process ( pid_t pid );


// 9) sci/
// SCIServer ??
pid_t __gpidSCI;
// ??


// 10) security/
pid_t __gpidSecurityServer;
// ??

// 11) 
pid_t __gpidSysIO;
// ??

// 12)
pid_t __gpidSysLib;
// ??

// 13) sysmk/
pid_t __gpidSysMK;
// ??

// 14) syssm/ 
//system management
// system server
pid_t __gpidSysSM;
// ??

// 15) wm/
// See: kgwm.c
pid_t __gpidWindowManager;
//int register_wm_process ( pid_t pid );


// 16) ws/
// See: kgws.c
pid_t __gpidWindowServer;
int register_ws_process ( pid_t pid );


#endif    


