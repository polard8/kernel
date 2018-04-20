:SetUp
@echo off

rem 
rem Compiling a kernel base for x86 processors.
rem The binary format is PE. $.
rem This script generate the file KERNEL.BIN.
rem (c) Copyright 2005-2017 Fred Nora.
rem

rem
rem Compila o Kernel e coloca o arquivo binário em /bin.
rem
rem { Engloba as 3 partes: Hal, Microkernel, Executive }
rem
rem Obs: 
rem Um benefício imediato dessa nova organização de classes é trabalhar 
rem primeiramente nas partes desbloqueadas deixando as partes bloqueadas 
rem para depois.
rem

:Start_Job0
rem Main.
echo -{ ...
echo -{ Compiling KERNEL.BIN ...
echo -{ Main.
	gcc -c k/main.c  -I./include -o main.o 
	
:Hal_Job1	
rem hal	
echo -{ ...
echo -{ ux4 /hal	
    rem -save-temps
	rem hal .. arquivo principal do hal
	gcc -c k/hal/hal.c     -I./include -o hal.o	
	
	
	
:Microkernel_Job2	
rem kernel mínimo. (tasks)
echo -{ ...
echo -{ ux3 /microkernel
    
	rem começamos com os principais módulos do microkernel.
	rem (head e microkernel)  
	rem head.s
	nasm  -I./k/microkernel/head/x86/  k/microkernel/head/x86/head.s  -f elf -o head.o
    rem c. 
    gcc -c  k/microkernel/microkernel.c -I./include  -o microkernel.o
	
	rem cpu (lidam com registradores) (K4)
	gcc -c  k/microkernel/cpu/context.c     -I./include  -o context.o
	gcc -c  k/microkernel/cpu/start.c       -I./include  -o start.o

	
	rem dma (K3)
	rem @todo gcc -c  k/microkernel/dma/dma.c  -I./include  -o dma.o
	
	rem
	rem /pc process control (ipc,scheduler,mm)
	rem
	
	gcc -c  k/microkernel/pc/taskswitch.c  -I./include  -o taskswitch.o	
    gcc -c  k/microkernel/pc/dispatch.c    -I./include  -o dispatch.o	
	gcc -c  k/microkernel/pc/queue.c       -I./include  -o queue.o
	gcc -c  k/microkernel/pc/process.c     -I./include  -o process.o
    gcc -c  k/microkernel/pc/pheap.c       -I./include  -o pheap.o	
    gcc -c  k/microkernel/pc/thread.c      -I./include  -o thread.o		
    gcc -c  k/microkernel/pc/threadi.c     -I./include  -o threadi.o
    gcc -c  k/microkernel/pc/theap.c       -I./include  -o theap.o
    gcc -c  k/microkernel/pc/tstack.c      -I./include  -o tstack.o	
    gcc -c  k/microkernel/pc/tasks.c       -I./include  -o tasks.o	
	gcc -c  k/microkernel/pc/create.c      -I./include  -o create.o
	
	rem microkernel/pc/ipc (callouts)
	gcc -c  k/microkernel/pc/ipc/spawn.c       -I./include  -o spawn.o
	gcc -c  k/microkernel/pc/ipc/callout.c       -I./include  -o callout.o
	gcc -c  k/microkernel/pc/ipc/callfar.c       -I./include  -o callfar.o
    gcc -c  k/microkernel/pc/ipc/ipc.c         -I./include  -o ipc.o	
    gcc -c  k/microkernel/pc/ipc/semaphore.c   -I./include  -o semaphore.o
	rem ...
	
	rem microkernel/pc/scheduler
    gcc -c  k/microkernel/pc/scheduler/scheduler.c   -I./include  -o scheduler.o
    gcc -c  k/microkernel/pc/scheduler/scheduleri.c  -I./include  -o scheduleri.o    	

	
	
	rem k/microkernel/pc/ram
	
	rem (RAM) (K5) módulo principal do executive
	rem /microkernel/pc/mm (memory manager)
    gcc -c k/microkernel/pc/mm/memory.c  -I./include -o memory.o    
	rem /microkernel/pc/mm (memory manager)
    gcc -c k/microkernel/pc/mm/pages.c   -I./include -o pages.o 	
	
	
	rem pertencem ao microkernel mas não são controles de processos.
	gcc -c  k/microkernel/request.c     -I./include  -o request.o	
	gcc -c  k/microkernel/faults.c      -I./include  -o faults.o		
	
	
:Executive_Job3	
rem drivers VIP em kernel mode.	
rem o executive é formado por três grupos: /sm,/uitm e /uigm.
echo -{ ...
echo -{ ux2 /executive
	rem /executive
	gcc -c k/executive/executive.c  -I./include -o executive.o	
	
	rem services (atende as systemcalls) 
    gcc -c k/executive/sci/services.c  -I./include -o services.o		
	
    rem executive/dd
	
	
	rem O que segue são os módulos secundários do executive (sm,uitm,uigm).
	
	rem sm
	rem /executive/init
    gcc -c k/executive/dd/sm/init/init.c  -I./include -o init.o
	
	rem sm
	
	rem sm
	rem /executive/sm/ob
	gcc -c k/executive/dd/sm/ob/object.c  -I./include -o object.o		
	
	rem sm
	rem /executive/network
	gcc -c k/executive/dd/sm/network/nic.c     -I./include -o nic.o
	gcc -c k/executive/dd/sm/network/network.c -I./include -o network.o
	gcc -c k/executive/dd/sm/network/socket.c  -I./include -o socket.o
	rem System Management.
	
	rem /executive/sm/sys
    rem system
    gcc -c k/executive/dd/sm/sys/modules.c  -I./include -o modules.o
    rem procedure
    gcc -c k/executive/dd/sm/sys/procedure.c  -I./include -o procedure.o	
    rem abort
    gcc -c k/executive/dd/sm/sys/abort.c  -I./include -o abort.o		
    rem info
    gcc -c k/executive/dd/sm/sys/info.c  -I./include -o info.o	
    rem server manager
    gcc -c k/executive/dd/sm/sys/sm.c  -I./include -o sm.o
    rem channel
    gcc -c k/executive/dd/sm/sys/channel.c  -I./include -o channel.o	
	rem signal
    gcc -c k/executive/dd/sm/sys/signal.c  -I./include -o signal.o	
    rem system
    gcc -c k/executive/dd/sm/sys/system.c  -I./include -o system.o
	rem io
	gcc -c k/executive/dd/sm/sys/io.c -I./include -o io.o	
	
    rem sm
	rem /executive/rt (runtime)
	gcc -c k/executive/dd/sm/rt/runtime.c -I./include -o runtime.o
	
	rem tty
    gcc -c k/executive/dd/tty/tty.c   -I./include -o tty.o		
	
	rem uitm
	rem /executive/uitm/libk
    gcc -c k/executive/dd/uitm/libk/misc.c   -I./include -o misc.o	
	
	rem uitm
	rem /executive/uitm/libc
	gcc -c k/executive/dd/uitm/libc/stdlib.c -I./include -o stdlib.o
	gcc -c k/executive/dd/uitm/libc/stdio.c  -I./include -o stdio.o
    gcc -c k/executive/dd/uitm/libc/string.c -I./include -o string.o
	
	rem uigm Nothing for now.	
		
	rem sm
	rem /executive/sm/disk
    gcc -c k/executive/dd/sm/disk/disk.c   -I./include -o disk.o						
    gcc -c k/executive/dd/sm/disk/volume.c -I./include -o volume.o	
	
  	rem sm
    gcc -c k/executive/dd/sm/install/install.c -I./include -o install.o    
	
	rem sm
	rem /executive/debug
	gcc -c k/executive/dd/sm/debug/debug.c -I./include -o debug.o	
	
	
	gcc -c k/executive/dd/device/device.c  -I./include -o device.o
	
	rem (unblocked) legados (K2).
	gcc -c k/executive/dd/unblocked/video.c   -I./include -o video.o  
	gcc -c k/executive/dd/unblocked/screen.c  -I./include -o screen.o 	
	gcc -c k/executive/dd/unblocked/keyboard.c  -I./include -o keyboard.o
    gcc -c k/executive/dd/unblocked/mouse.c  -I./include -o mouse.o  	
	gcc -c k/executive/dd/unblocked/ldisc.c  -I./include -o ldisc.o    	
	gcc -c k/executive/dd/unblocked/hdd.c    -I./include -o hdd.o	
	gcc -c k/executive/dd/unblocked/pic.c   -I./include -o pic.o 
    gcc -c k/executive/dd/unblocked/timer.c     -I./include -o timer.o	
	gcc -c k/executive/dd/unblocked/rtc.c    -I./include -o rtc.o
	gcc -c k/executive/dd/unblocked/vsync.c  -I./include -o vsync.o 
	gcc -c k/executive/dd/unblocked/arch/x86/systemcall.c  -I./include -o systemcall.o		
	gcc -c k/executive/dd/unblocked/arch/x86/cpux86.c  -I./include -o cpux86.o 
    gcc -c k/executive/dd/unblocked/arch/x86/x86.c     -I./include -o x86.o	
	gcc -c k/executive/dd/unblocked/arch/x86/ports.c   -I./include -o ports.o 	
	gcc -c k/executive/dd/unblocked/arch/amd/cpuamd.c  -I./include -o cpuamd.o 	    


	
	rem (blocked) (K1).
	gcc -c k/executive/dd/blocked/pci.c   -I./include -o pci.o
	gcc -c k/executive/dd/blocked/usb.c   -I./include -o usb.o
	gcc -c k/executive/dd/blocked/apic.c  -I./include -o apic.o 

	
	
	rem FILE System
	
	rem /executive/fs
    gcc -c k/executive/fs/fs.c      -I./include -o fs.o						
    gcc -c k/executive/fs/read.c    -I./include -o read.o			
    gcc -c k/executive/fs/write.c   -I./include -o write.o			
    gcc -c k/executive/fs/cf.c      -I./include -o cf.o			
    gcc -c k/executive/fs/search.c  -I./include -o search.o			
    gcc -c k/executive/fs/format.c  -I./include -o format.o			
	

	
echo -{ ...
echo -{ ux1 /gramado \o/	

	rem    ****    COMPILANDO A INTERFACE GRÁFICA    ****
	rem k\gramado\gui
	
    rem char
    gcc -c k/gramado/gui/char.c   -I./include -o char.o
    rem pixel
    gcc -c k/gramado/gui/pixel.c  -I./include -o pixel.o 
    rem line
    gcc -c k/gramado/gui/line.c   -I./include -o line.o	
    rem rect
    gcc -c k/gramado/gui/rect.c   -I./include -o rect.o 
    rem draw
    gcc -c k/gramado/gui/dtext.c  -I./include -o dtext.o
    rem draw
    gcc -c k/gramado/gui/draw.c   -I./include -o draw.o	
    rem createw
    gcc -c k/gramado/gui/createw.c    -I./include -o createw.o    
    rem grid
    gcc -c k/gramado/gui/grid.c       -I./include -o grid.o 
    rem statusbar
    gcc -c k/gramado/gui/statusbar.c  -I./include -o statusbar.o 
    rem menubar
    gcc -c k/gramado/gui/menubar.c    -I./include -o menubar.o 
    rem menu
    gcc -c k/gramado/gui/menu.c       -I./include -o menu.o 
    rem bmp
    gcc -c k/gramado/gui/bmp.c        -I./include -o bmp.o 
    rem button
    gcc -c k/gramado/gui/button.c     -I./include -o button.o 
    rem messagebox
    gcc -c k/gramado/gui/messagebox.c  -I./include -o messagebox.o
    rem dialogboxbox
    gcc -c k/gramado/gui/dialogbox.c   -I./include -o dialogbox.o
	rem background
    gcc -c k/gramado/gui/background.c  -I./include -o background.o  
    rem window
    gcc -c k/gramado/gui/window.c      -I./include -o window.o    
    rem desktop
    gcc -c k/gramado/gui/desktop.c     -I./include -o desktop.o  
    rem window station
    gcc -c k/gramado/gui/wstation.c    -I./include -o wstation.o    
    rem user section
    gcc -c k/gramado/gui/usession.c    -I./include -o usession.o        

    
	rem gramado logon e logoff
	
	rem /gramado/logon
    gcc -c k/gramado/logon/logon.c  -I./include -o logon.o 
	rem /gramado/logoff
    gcc -c k/gramado/logoff/logoff.c  -I./include -o logoff.o 

	rem gramado/user
	gcc -c k/gramado/user/userenv.c -I./include -o userenv.o 	
	

	rem *gui (GRAMADO)
    gcc -c k/gramado/gramado.c         -I./include -o gramado.o    	
	
	rem
	rem Compilando o módulo **** SYSTEM MANAGER ****
	rem
	 
    REM Ordem: Hardware, Kernel, GUI (embrulo).
	REM Ordem: Fica em último as rotinas usadas com menor frequência.
	REM        Colocar por último, abort, faults...shutdown, reboot.
	REM        Biblioteca padrão deve ir para o começo.
	REM        Quem usa as bibliotecas vai depois.
	REM 
	
:Objects	
set myObjects=head.o ^
main.o ^
io.o ^
hal.o ^
microkernel.o ^
executive.o ^
video.o ^
screen.o ^
runtime.o ^
ports.o ^
x86.o ^
stdio.o ^
stdlib.o ^
string.o ^
tty.o ^
init.o ^
logon.o ^
logoff.o ^
cpux86.o ^
cpuamd.o ^
memory.o ^
pages.o ^
apic.o ^
pic.o ^
timer.o ^
rtc.o ^
keyboard.o ^
mouse.o ^
ldisc.o ^
hdd.o ^
pci.o ^
usb.o ^
device.o ^
spawn.o ^
callout.o ^
callfar.o ^
process.o ^
pheap.o ^
thread.o ^
threadi.o ^
theap.o ^
tstack.o ^
create.o ^
start.o ^
context.o ^
tasks.o ^
taskswitch.o ^
queue.o ^
scheduler.o ^
scheduleri.o ^
dispatch.o ^
semaphore.o ^
modules.o ^
nic.o ^
network.o ^
socket.o ^
sm.o ^
channel.o ^
ipc.o ^
read.o ^
write.o ^
cf.o ^
search.o ^
format.o ^
disk.o ^
volume.o ^
fs.o ^
misc.o ^
request.o ^
info.o ^
signal.o ^
system.o ^
background.o ^
grid.o ^
statusbar.o ^
menubar.o ^
menu.o ^
messagebox.o ^
dialogbox.o ^
button.o ^
char.o ^
pixel.o ^
line.o ^
rect.o ^
dtext.o ^
draw.o ^
vsync.o ^
bmp.o ^
createw.o ^
window.o ^
desktop.o ^
wstation.o ^
usession.o ^
gramado.o ^
object.o ^
userenv.o ^
procedure.o ^
systemcall.o ^
install.o ^
debug.o ^
abort.o ^
faults.o ^
services.o  



:Linking_Job4 
echo -{ ...
echo -{ Linking objects ...
   ld -T link.ld -o KERNEL.BIN %myObjects%  -Map Kernel_Map.s
   
:Moving_Job5  
echo -{ ...
echo -{ Moving ...   
    move KERNEL.BIN bin\KERNEL.BIN
	
:Clean_Job6	
echo -{ ...
echo -{ Clean.
    del *.o
 
:End 
echo End!
	pause
	