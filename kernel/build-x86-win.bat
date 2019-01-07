
:SetUp
@echo off

rem 
rem Compiling a kernel base for x86 processors.
rem The binary format is PE. $.
rem This script generate the file KERNEL.BIN.
rem 
rem  gcc 3.4.2 mingw-special
rem  nasm 2.05.01
rem  ld 2.19
rem
rem (c) Copyright 2005-2018 Fred Nora.
rem

    rem set GramadoDrive=c:
    set NoraxDrive=c:
   
    rem set GramadoRoot=%GramadoDrive%\gramado
	set NoraxRoot=%NoraxDrive%\norax

    rem cd c:\sdk\bin
    rem cd %GramadoDrive%\sdk\bin
	cd %NoraxDrive%\sdk\bin
	
echo ~{ ...
echo ~{ Norax 0.1


:Start_Job0
rem Main.
echo ~{ ...
echo ~{ Compiling norax KERNEL.BIN ...

rem echo ~{ ...
echo ~{ /3rdparty
    gcc -c c:/norax/kernel/3rdparty/kernel/disk/disk1.c   -I c:/norax/include -o disk1.o
	
rem echo ~{ ...
echo ~{ /entry

	rem head.s
	nasm  -I  c:/norax/kernel/entry/x86/head/  c:/norax/kernel/entry/x86/head/head.s  -f elf -o head.o
	
	rem x86main.o
	gcc -c c:/norax/kernel/entry/x86/x86main.c -I c:/norax/include -o x86main.o 
	
:Hal_Job1	
rem hal	
rem echo ~{ ...
echo ~{ ux4 /hal	
	gcc -c c:/norax/kernel/hal/hal.c -I c:/norax/include -o hal.o	
	gcc -c c:/norax/kernel/hal/arch/detect.c   -I c:/norax/include -o detect.o
	gcc -c c:/norax/kernel/hal/arch/amd/cpuamd.c   -I c:/norax/include -o cpuamd.o
	gcc -c c:/norax/kernel/hal/arch/x86/portsx86.c    -I c:/norax/include -o portsx86.o
	gcc -c c:/norax/kernel/hal/arch/x86/syscall.c  -I c:/norax/include -o syscall.o		
    gcc -c c:/norax/kernel/hal/arch/x86/x86.c      -I c:/norax/include -o x86.o	
	
:Microkernel_Job2	
rem echo ~{ ...
echo ~{ ux3 /mk
	
    rem c. 
    gcc -c  c:/norax/kernel/mk/mk.c -I c:/norax/include  -o mk.o
	
	rem cpu
	gcc -c  c:/norax/kernel/mk/arch/x86/x86cont.c   -I c:/norax/include  -o x86cont.o
	gcc -c  c:/norax/kernel/mk/arch/x86/x86start.c  -I c:/norax/include  -o x86start.o
	
	rem
	rem /pc process control ( ipc, sched, mm )
	rem
	
	gcc -c  c:/norax/kernel/mk/pc/action/ts.c        -I c:/norax/include  -o ts.o	
    gcc -c  c:/norax/kernel/mk/pc/action/dispatch.c  -I c:/norax/include  -o dispatch.o	
	gcc -c  c:/norax/kernel/mk/pc/action/queue.c     -I c:/norax/include  -o queue.o
	gcc -c  c:/norax/kernel/mk/pc/action/process.c   -I c:/norax/include  -o process.o
    gcc -c  c:/norax/kernel/mk/pc/action/pheap.c     -I c:/norax/include  -o pheap.o	
    gcc -c  c:/norax/kernel/mk/pc/action/thread.c    -I c:/norax/include  -o thread.o		
    gcc -c  c:/norax/kernel/mk/pc/action/threadi.c   -I c:/norax/include  -o threadi.o
    gcc -c  c:/norax/kernel/mk/pc/action/theap.c     -I c:/norax/include  -o theap.o
    gcc -c  c:/norax/kernel/mk/pc/action/tstack.c    -I c:/norax/include  -o tstack.o	
    gcc -c  c:/norax/kernel/mk/pc/action/tasks.c     -I c:/norax/include  -o tasks.o	
	gcc -c  c:/norax/kernel/mk/pc/action/create.c    -I c:/norax/include  -o create.o
	gcc -c  c:/norax/kernel/mk/pc/action/spawn.c     -I c:/norax/include  -o spawn.o
	
	rem mk/pc/ipc 
	gcc -c  c:/norax/kernel/mk/pc/ipc/callout.c  -I c:/norax/include  -o callout.o
	gcc -c  c:/norax/kernel/mk/pc/ipc/callfar.c  -I c:/norax/include  -o callfar.o
    gcc -c  c:/norax/kernel/mk/pc/ipc/ipc.c      -I c:/norax/include  -o ipc.o	
    gcc -c  c:/norax/kernel/mk/pc/ipc/sem.c      -I c:/norax/include  -o sem.o
	rem ...
	
	rem mk/pc/sched
    gcc -c  c:/norax/kernel/mk/pc/sched/sched.c  -I c:/norax/include -o sched.o
    gcc -c  c:/norax/kernel/mk/pc/sched/schedi.c -I c:/norax/include -o schedi.o    	
	
	rem /mk/pc/mm (memory manager)
    gcc -c  c:/norax/kernel/mk/pc/mm/memory.c  -I c:/norax/include -o memory.o    
    gcc -c  c:/norax/kernel/mk/pc/mm/pages.c   -I c:/norax/include -o pages.o 	
	
	gcc -c  c:/norax/kernel/mk/request.c -I c:/norax/include -o request.o	
	
	gcc -c  c:/norax/kernel/mk/arch/x86/x86fault.c  -I c:/norax/include -o x86fault.o		
	
	
:Executive_Job3	
rem echo ~{ ...
echo ~{ ux2 /execve
	
	rem /execve
	gcc -c c:/norax/kernel/execve/execve.c  -I c:/norax/include -o execve.o	
	
	rem /crts
    gcc -c c:/norax/kernel/execve/crts/libc/cedge.c  -I c:/norax/include -o cedge.o	
	gcc -c c:/norax/kernel/execve/crts/libc/ctype.c  -I c:/norax/include -o ctype.o	
	gcc -c c:/norax/kernel/execve/crts/libc/stdlib.c -I c:/norax/include -o stdlib.o
	gcc -c c:/norax/kernel/execve/crts/libc/stdio.c  -I c:/norax/include -o stdio.o
    gcc -c c:/norax/kernel/execve/crts/libc/string.c -I c:/norax/include -o string.o	
	
    rem /dd
	gcc -c c:/norax/kernel/execve/dd/apic.c      -I c:/norax/include -o apic.o 	
	gcc -c c:/norax/kernel/execve/dd/hdd.c       -I c:/norax/include -o hdd.o	
	gcc -c c:/norax/kernel/execve/dd/pic.c       -I c:/norax/include -o pic.o 
	gcc -c c:/norax/kernel/execve/dd/rtc.c       -I c:/norax/include -o rtc.o	
	gcc -c c:/norax/kernel/execve/dd/screen.c    -I c:/norax/include -o screen.o 	
    gcc -c c:/norax/kernel/execve/dd/timer.c     -I c:/norax/include -o timer.o		
	gcc -c c:/norax/kernel/execve/dd/video.c     -I c:/norax/include -o video.o  
	gcc -c c:/norax/kernel/execve/dd/vsync.c     -I c:/norax/include -o vsync.o 

    gcc -c c:/norax/kernel/execve/dd/serial.c     -I c:/norax/include -o serial.o 

	
    rem dd/devmgr
	gcc -c c:/norax/kernel/execve/dd/devmgr/devmgr.c  -I c:/norax/include -o devmgr.o

	rem dd/i8042
	gcc -c c:/norax/kernel/execve/dd/i8042/i8042.c     -I c:/norax/include -o i8042.o
    gcc -c c:/norax/kernel/execve/dd/i8042/ps2mouse.c  -I c:/norax/include -o ps2mouse.o
    gcc -c c:/norax/kernel/execve/dd/i8042/ps2kbd.c    -I c:/norax/include -o ps2kbd.o  	
	gcc -c c:/norax/kernel/execve/dd/i8042/keyboard.c  -I c:/norax/include -o keyboard.o
    gcc -c c:/norax/kernel/execve/dd/i8042/mouse.c     -I c:/norax/include -o mouse.o  		
	
	rem dd/ldisc
	gcc -c c:/norax/kernel/execve/dd/ldisc/ldisc.c     -I c:/norax/include -o ldisc.o 
		
	rem dd/pci
	gcc -c c:/norax/kernel/execve/dd/pci/pci.c       -I c:/norax/include -o pci.o  

	
	
	rem dd/network
	gcc -c c:/norax/kernel/execve/dd/network/intel.c    -I c:/norax/include -o nicintel.o
	gcc -c c:/norax/kernel/execve/dd/network/network.c  -I c:/norax/include -o network.o
	gcc -c c:/norax/kernel/execve/dd/network/socket.c   -I c:/norax/include -o socket.o
	
	rem dd/tty
    gcc -c c:/norax/kernel/execve/dd/tty/tty.c         -I c:/norax/include -o tty.o		
	
	rem dd/usb
	gcc -c c:/norax/kernel/execve/dd/usb/usb.c       -I c:/norax/include -o usb.o		
	
	rem execve/fs
    gcc -c c:/norax/kernel/execve/fs/fs.c     -I c:/norax/include -o fs.o						
    gcc -c c:/norax/kernel/execve/fs/read.c   -I c:/norax/include -o read.o			
    gcc -c c:/norax/kernel/execve/fs/write.c  -I c:/norax/include -o write.o			
    gcc -c c:/norax/kernel/execve/fs/cf.c     -I c:/norax/include -o cf.o			
    gcc -c c:/norax/kernel/execve/fs/search.c -I c:/norax/include -o search.o			
    gcc -c c:/norax/kernel/execve/fs/format.c -I c:/norax/include -o format.o	
    gcc -c c:/norax/kernel/execve/fs/vfs.c    -I c:/norax/include -o vfs.o			
	
	rem execve/sci
    gcc -c c:/norax/kernel/execve/sci/services.c  -I c:/norax/include -o services.o			
	
 
 	rem execve/sm
    gcc -c c:/norax/kernel/execve/sm/init/init.c    -I c:/norax/include -o init.o
	gcc -c c:/norax/kernel/execve/sm/ob/object.c    -I c:/norax/include -o object.o		    
	gcc -c c:/norax/kernel/execve/sm/sys/modules.c  -I c:/norax/include -o modules.o
    gcc -c c:/norax/kernel/execve/sm/sys/proc.c     -I c:/norax/include -o proc.o	
    gcc -c c:/norax/kernel/execve/sm/sys/abort.c    -I c:/norax/include -o abort.o		
    gcc -c c:/norax/kernel/execve/sm/sys/info.c     -I c:/norax/include -o info.o	
    gcc -c c:/norax/kernel/execve/sm/sys/sm.c       -I c:/norax/include -o sm.o
    gcc -c c:/norax/kernel/execve/sm/sys/channel.c  -I c:/norax/include -o channel.o	
    gcc -c c:/norax/kernel/execve/sm/sys/signal.c   -I c:/norax/include -o signal.o	
    gcc -c c:/norax/kernel/execve/sm/sys/system.c   -I c:/norax/include -o system.o
	gcc -c c:/norax/kernel/execve/sm/sys/io.c       -I c:/norax/include -o io.o	
	gcc -c c:/norax/kernel/execve/sm/rt/runtime.c   -I c:/norax/include -o runtime.o
	gcc -c c:/norax/kernel/execve/sm/disk/diskvol.c    -I c:/norax/include -o diskvol.o
    gcc -c c:/norax/kernel/execve/sm/install/install.c -I c:/norax/include -o install.o    
	gcc -c c:/norax/kernel/execve/sm/debug/debug.c     -I c:/norax/include -o debug.o	

	
rem echo ~{ ...
echo ~{ ux1 /gws \o/
    	
    
	rem k\gws\gws	
    rem Norax Window Server.
    gcc -c c:/norax/kernel/gws/gws/char.c     -I c:/norax/include -o char.o
    gcc -c c:/norax/kernel/gws/gws/pixel.c    -I c:/norax/include -o pixel.o 
    gcc -c c:/norax/kernel/gws/gws/line.c     -I c:/norax/include -o line.o	
    gcc -c c:/norax/kernel/gws/gws/rect.c     -I c:/norax/include -o rect.o 
    gcc -c c:/norax/kernel/gws/gws/dtext.c    -I c:/norax/include -o dtext.o
    gcc -c c:/norax/kernel/gws/gws/font.c     -I c:/norax/include -o font.o	
    gcc -c c:/norax/kernel/gws/gws/createw.c  -I c:/norax/include -o createw.o    
    gcc -c c:/norax/kernel/gws/gws/grid.c     -I c:/norax/include -o grid.o 
    gcc -c c:/norax/kernel/gws/gws/sbar.c     -I c:/norax/include -o sbar.o 
    gcc -c c:/norax/kernel/gws/gws/menubar.c   -I c:/norax/include -o menubar.o 
    gcc -c c:/norax/kernel/gws/gws/menu.c      -I c:/norax/include -o menu.o 
    gcc -c c:/norax/kernel/gws/gws/bmp.c       -I c:/norax/include -o bmp.o 
    gcc -c c:/norax/kernel/gws/gws/button.c    -I c:/norax/include -o button.o 
	gcc -c c:/norax/kernel/gws/gws/bg.c        -I c:/norax/include -o bg.o  
    gcc -c c:/norax/kernel/gws/gws/window.c    -I c:/norax/include -o window.o  
    
	rem norax logon e logoff
    gcc -c c:/norax/kernel/gws/logon/logon.c    -I c:/norax/include -o logon.o 
    gcc -c c:/norax/kernel/gws/logoff/logoff.c  -I c:/norax/include -o logoff.o 

	rem norax/user
	gcc -c c:/norax/kernel/gws/user/userenv.c   -I c:/norax/include -o userenv.o 	
    gcc -c c:/norax/kernel/gws/user/desktop.c   -I c:/norax/include -o desktop.o  
    gcc -c c:/norax/kernel/gws/user/room.c      -I c:/norax/include -o room.o    
    gcc -c c:/norax/kernel/gws/user/usession.c  -I c:/norax/include -o usession.o   
	
	rem *gui (norax)
    gcc -c c:/norax/kernel/gws/gws.c   -I c:/norax/include -o gws.o    	
	
	
	

rem 
rem ## Objects ##
rem 
	
:Objects	
set myObjects=head.o ^
x86main.o ^
io.o ^
hal.o ^
mk.o ^
execve.o ^
video.o ^
screen.o ^
runtime.o ^
portsx86.o ^
x86.o ^
stdio.o ^
stdlib.o ^
string.o ^
tty.o ^
init.o ^
logon.o ^
logoff.o ^
detect.o ^
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
devmgr.o ^
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
x86start.o ^
x86cont.o ^
tasks.o ^
ts.o ^
queue.o ^
sched.o ^
schedi.o ^
dispatch.o ^
sem.o ^
modules.o ^
nicintel.o ^
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
disk1.o ^
diskvol.o ^
fs.o ^
vfs.o ^
cedge.o ^
ctype.o ^
request.o ^
info.o ^
signal.o ^
system.o ^
bg.o ^
grid.o ^
sbar.o ^
menubar.o ^
menu.o ^
i8042.o ^
ps2mouse.o ^
ps2kbd.o ^
button.o ^
char.o ^
pixel.o ^
line.o ^
rect.o ^
dtext.o ^
font.o ^
vsync.o ^
bmp.o ^
createw.o ^
window.o ^
desktop.o ^
room.o ^
usession.o ^
gws.o ^
object.o ^
userenv.o ^
proc.o ^
syscall.o ^
install.o ^
serial.o ^
debug.o ^
abort.o ^
x86fault.o ^
services.o  



:Linking_Job4 
echo ~{ ...
echo ~{ Linking objects ...
   ld -T c:/norax/kernel/link.ld -o KERNEL.BIN %myObjects% -Map c:\norax\kernel\kmap.s
   
:Moving_Job5  
echo ~{ ...
echo ~{ Moving ...   
    move KERNEL.BIN c:\norax\bin\KERNEL.BIN
	
:Clean_Job6	
rem echo ~{ ...
echo ~{ Clean.
    del *.o
 
:End 
echo End!
	pause
	