
// kernel.h
// Created by Fred Nora.
// Gramado OS headers.

#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...

// Order:
// configuration, libc, devices ...

//
// Configuration of product and version.
//


// ==================================
// config/
// Product and version.
#include "config/product.h"  // Product type
#include "config/version.h"  // Product version
#include "config/config.h"

// ==================================
// ke/
// System major info.
#include "../kres/ke/system/bootinfo.h"
#include "../kres/ke/system/mode.h"
#include "../kres/ke/system/state.h"

// ==================================
// config/
// utsname
// Structure describing the system and machine
#include "config/utsname.h"
#include "config/u.h"          // User

// ==================================
// virt/
// system
#include "../kctl/core/system.h"

// ==================================
// ke/
// Supervisor:
// Kernel configuration.
// Compiling.
#include "../kres/ke/system/klimits2.h"
#include "../kres/ke/gdef.h"

// ==================================
// dev/
#include "../kres/dev/gdevice.h"
#include "../kres/dev/ginput.h"  // input manager support.

// ==================================
// ke/
#include "../kres/ke/gspin.h"
#include "../kres/ke/gwd.h"     // whatch dogs.
#include "../kres/ke/pints.h"   // profiler
#include "../kres/ke/kinit.h"   // kernel initialization.

// ===============================
// virt/
#include "../kctl/core/info.h"
#include "../kctl/core/request.h"
#include "../kctl/core/debug.h"

// ==================================
// ke/
// Gramado configuration.
#include "../kres/ke/jiffies.h"

// ==================================
// dev/
// Setup input mode.
#include "../kres/dev/io_ctrl.h"

// ==================================
// crt/
// Libc support.
#include "../lib/ktypes.h"
#include "../lib/ktypes2.h"

// ke/
#include "../kres/ke/kobject.h"

// lib/
// Legacy stuff.
#include "../lib/kstdarg.h"
#include "../lib/kerrno.h"
#include "../lib/kcdefs.h"
#include "../lib/kstddef.h"
#include "../lib/klimits.h"
#include "../lib/kstdio.h"
#include "../lib/kstdlib.h"
#include "../lib/kstring.h"
#include "../lib/kctype.h"
#include "../lib/kiso646.h"
#include "../lib/ksignal.h"
#include "../lib/kunistd.h"
#include "../lib/kfcntl.h"
#include "../lib/kioctl.h"
#include "../lib/kioctls.h"
#include "../lib/ktermios.h"
#include "../lib/kttydef.h"

// ==================================
// ke/
// Globals. PIDs support.
#include "../kres/ke/kpid.h"

// ==================================
// mm/
// Memory management.
#include "../kres/mm/mmsize.h"
#include "../kres/mm/x86_64/x64gpa.h"
#include "../kres/mm/x86_64/x64gva.h"
#include "../kres/mm/gentry.h"
#include "../kres/mm/mm.h"
#include "../kres/mm/memmap.h" 
#include "../kres/mm/x86_64/intelmm.h"
#include "../kres/mm/mmblock.h"
#include "../kres/mm/mmusage.h"
#include "../kres/mm/x86_64/x64mm.h"
#include "../kres/mm/mmft.h"
#include "../kres/mm/mmglobal.h"  // Deve ficar mais acima.
#include "../kres/mm/heap.h"      // Heap pointer support.
#include "../kres/mm/aspace.h"    // Address Space, (data base account).
#include "../kres/mm/bank.h"      // Bank. database

// ==================================
// ke/
// hal
#include "../kres/ke/ports64.h"
#include "../kres/ke/cpu.h"
#include "../kres/ke/arch/x86_64/tss.h"
#include "../kres/ke/arch/x86_64/x64gdt.h"
#include "../kres/ke/arch/x86_64/x64.h"
#include "../kres/ke/detect.h"
// ==================================
// ke/
// hv
#include "../kctl/core/hv.h"
// hal cpu
#include "../kres/ke/arch/x86_64/cpuid.h"
#include "../kres/ke/up.h"

#include "../kres/ke/arch/x86_64/smp/mp.h"

// hal pic/apic/ioapic
#include "../kres/ke/arch/x86_64/pic.h"

#include "../kres/ke/arch/x86_64/smp/apic.h"
#include "../kres/ke/arch/x86_64/smp/apictim.h"
#include "../kres/ke/arch/x86_64/smp/ioapic.h"

#include "../kres/ke/breaker.h"
// hal timers.
#include "../kres/ke/pit.h"
#include "../kres/ke/rtc.h"
// ==================================
// ke/
// hal global
#include "../kres/ke/hal.h"

// ==================================
// dev/
// PCI bus.
#include "../kres/dev/pci.h"
// ==================================
// dev/
// io
#include "../kres/dev/io.h"
// ==================================
// dev/
// Devices
// primeiro char, depois block, depois network.
// tty
#include "../kres/dev/chardev/tty/ttyldisc.h"
#include "../kres/dev/chardev/tty/ttydrv.h"
#include "../kres/dev/chardev/tty/tty.h"
#include "../kres/dev/chardev/tty/pty.h"
#include "../kres/dev/chardev/tty/console.h"

// hw stuff - display device
// display device support.
#include "../kres/dev/chardev/display/display.h"
// bootloader display device
#include "../kres/dev/chardev/display/bldisp/bldisp.h"

// ==================================
// gramk/
// sw - Graphics Engine
#include "../kres/gramk/color.h"
#include "../kres/gramk/fonts.h"
#include "../kres/gramk/ascii.h"
#include "../kres/gramk/bg.h"

// ==================================
// ke/
#include "../kres/ke/intake/msgcode.h"

// ==================================
// gramk/

#include "../kres/gramk/ws2.h"
#include "../kres/gramk/gre/gre.h"
#include "../kres/gramk/ws.h"
#include "../kres/gramk/user/input.h"
#include "../kres/gramk/callback.h"

// ==================================
// dev/

// Serial port. (COM).
#include "../kres/dev/chardev/serial/serial.h"

#include "../kres/dev/chardev/vk.h"
#include "../kres/dev/chardev/kbdabnt2.h"
#include "../kres/dev/chardev/kbdmap.h"

// i8042 (PS/2)
#include "../kres/dev/chardev/i8042/keyboard.h"
#include "../kres/dev/chardev/i8042/ps2kbd.h"
#include "../kres/dev/chardev/i8042/mouse.h"
#include "../kres/dev/chardev/i8042/ps2mouse.h"
#include "../kres/dev/chardev/i8042/i8042.h"

// Block devices
// ata, sata
#include "../kres/dev/blkdev/ata/ata.h"
// Storage manager.
#include "../kres/dev/blkdev/superblk.h"
#include "../kres/dev/blkdev/volume.h"
#include "../kres/dev/blkdev/disk.h"
#include "../kres/dev/blkdev/storage.h"

// Network devices
// primeiro controladoras depois protocolos
// e1000 - nic intel
#include "../kres/dev/netdev/e1000/e1000.h"

// ==================================
// net/ 
// (network, protocols and socket)
// network
#include "../kres/net/mac.h"
#include "../kres/net/host.h"
#include "../kres/net/in.h"
#include "../kres/net/un.h"

//
// Protocols
//

// Core protocols
#include "../kres/net/prot/core/ethernet.h"
#include "../kres/net/prot/core/arp.h"
#include "../kres/net/prot/core/ip.h"
// Commom protocols
#include "../kres/net/prot/tcp.h"
#include "../kres/net/prot/udp.h"
#include "../kres/net/prot/dhcp.h" 
// Extra protocols
#include "../kres/net/prot/icmp.h" 

// Network
#include "../kres/net/nports.h"     //(network) Network Ports  (sw)
#include "../kres/net/inet.h"

#include "../kres/net/socklib.h"     //
#include "../kres/net/socket.h"      //last always

#include "../kres/net/domain.h"
#include "../kres/net/network.h"     //(network) Gerenciamento de rede.  

// ----------------------
// Last:
// Device manager.
#include "../kres/dev/devmgr.h"

// ==================================
// fs/
// File system
// ----------------------
// Depois de devices.
// fs
#include "../kres/fs/path.h"      // path.

#include "../kres/fs/fat/fatlib.h"    // fat16 library.
#include "../kres/fs/fat/fat.h"       // fat16.

#include "../kres/fs/inode.h"
#include "../kres/fs/exec_elf.h"
#include "../kres/fs/pipe.h"
#include "../kres/fs/fs.h"

// ==================================
// ke/
// Process structures
// ps
#include "../kres/ke/intake/prio.h"     // Priority
#include "../kres/ke/intake/quantum.h"  // Quantum
#include "../kres/ke/image.h"

#include "../kres/ke/intake/disp/x86_64/x64cont.h"

#include "../kres/ke/intake/disp/ts.h"

#include "../kres/ke/tasks.h"
#include "../kres/ke/queue.h"
#include "../kres/ke/mk.h"
#include "../kres/ke/intake/dispatch.h"
#include "../kres/ke/intake/msg.h"
#include "../kres/ke/intake/thread.h"
#include "../kres/ke/intake/process.h"

#include "../kres/ke/intake/sched/sched.h"
#include "../kres/ke/intake/sched/schedq.h"

// Precisa de todos os componentes de ke/
#include "../kres/ke/ke.h"

// ==================================
#include "../kctl/core/user.h"

// ==================================
// ke/
#include "../kres/ke/system/reboot.h"

// ==================================
// mod/
#include "../kctl/core/mod.h"

// ==================================
// ke/
// #deprecated?
// This is a work in progress
#include "../kres/ke/system/layer.h"

// ==================================
// virt/
// Syscalls. 
// (Called by the interrups 0x80, 0x81, 0x82, 0x83).
#include "../kctl/core/syscalls.h"
// zero. (Used during the kernel initialization)
#include "../kctl/core/zero.h"

// ==================================
// ke/
// Maskable interrupts
#include "../kres/ke/arch/x86_64/x64mi.h"

// ==================================
// virt/
// Project California
#include "../kctl/core/cali/cali.h"

// Main kernel controller header.
#include "../kctl/kctl.h"




