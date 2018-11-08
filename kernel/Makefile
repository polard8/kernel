# test #
# tentando compilar o kernel.bin do sistema gramado.

# Specify compiler
gcc=gcc.exe
  
# Specify linker
ld=ld.exe
  
#objetos usados  
#myObjects=head.o ^
myObjects=main.o \
io.o \
hal.o \
mk.o \
execve.o \
video.o \
screen.o \
runtime.o \
ports.o \
x86.o \
stdio.o \
stdlib.o \
string.o \
tty.o \
init.o \
logon.o \
logoff.o \
cpux86.o \
cpuamd.o \
memory.o \
pages.o \
apic.o \
pic.o \
timer.o \
rtc.o \
keyboard.o \
mouse.o \
ldisc.o \
hdd.o \
pci.o \
usb.o \
device.o \
spawn.o \
callout.o \
callfar.o \
process.o \
pheap.o \
thread.o \
threadi.o \
theap.o \
tstack.o \
create.o \
start.o \
context.o \
tasks.o \
ts.o \
queue.o \
sched.o \
schedi.o \
dispatch.o \
sem.o \
modules.o \
nic.o \
network.o \
socket.o \
sm.o \
channel.o \
ipc.o \
read.o \
write.o \
cf.o \
search.o \
format.o \
disk.o \
volume.o \
fs.o \
vfs.o \
misc.o \
request.o \
info.o \
signal.o \
system.o \
bg.o \
grid.o \
sbar.o \
menubar.o \
menu.o \
mbox.o \
dbox.o \
button.o \
char.o \
pixel.o \
line.o \
rect.o \
dtext.o \
font.o \
vsync.o \
bmp.o \
createw.o \
window.o \
desktop.o \
wstation.o \
usession.o \
gramado.o \
object.o \
userenv.o \
proc.o \
syscall.o \
install.o \
debug.o \
abort.o \
faults.o \
services.o  \  




all: head.o $(myObjects)
#	ld -T link.ld $(myObjects) -o kernel
	
	
#:Microkernel_Job2	
#echo ~{ ...
#echo ~{ ux3 /mk
    
#	rem head.s
head.o: k/mk/head/x86/head.s k/mk/head/x86/headlib.s k/mk/head/x86/hw.inc k/mk/head/x86/hwlib.inc k/mk/head/x86/sw.inc k/mk/head/x86/swlib.inc \
    nasm -I./k/mk/head/x86/ -f elf k/mk/head/x86/head.s  -o head.o 	
#nasm -I./k/mk/head/x86/ k/mk/head/x86/head.s -f elf -o head.o 		
	
#.PHONY: all
#all: $(myObjects) KERNEL.BIN movebin clean endmake

#:Linking_Job4 
# ~{ ...
# ~{ Linking objects ...
#KERNEL.BIN: ld -T link.ld -o KERNEL.BIN $(myObjects) 



#:Start_Job0
#rem Main.
#echo ~{ ...
#echo ~{ Compiling KERNEL.BIN ...
#echo ~{ Main.
main.o: gcc -c k/main.c -I./include -o main.o 

#:Hal_Job1	
#rem hal	
#echo ~{ ...
#echo ~{ ux4 /hal	
hal.o:gcc -c k/hal/hal.c -I./include -o hal.o	
	
	

	
#    rem c. 
mk.o: gcc -c k/mk/mk.c -I./include -o mk.o 

context.o: gcc -c  k/mk/cpu/context.c -I./include  -o context.o

start.o: gcc -c  k/mk/cpu/start.c -I./include  -o start.o

#	rem
#	rem /pc process control ( ipc, sched, mm )
#	rem

ts.o: gcc -c k/mk/pc/ts.c -I./include -o ts.o 

dispatch.o: gcc -c k/mk/pc/dispatch.c -I./include -o dispatch.o 

queue.o: gcc -c k/mk/pc/queue.c -I./include -o queue.o 

process.o: gcc -c  k/mk/pc/process.c   -I./include  -o process.o 
    
	
pheap.o:	
	gcc -c  k/mk/pc/pheap.c     -I./include  -o pheap.o	
    
thread.o:	
	gcc -c  k/mk/pc/thread.c    -I./include  -o thread.o
    
threadi.o:	
	gcc -c  k/mk/pc/threadi.c   -I./include  -o threadi.o
    
theap.o:	
	gcc -c  k/mk/pc/theap.c     -I./include  -o theap.o
    
tstack.o:	
	gcc -c  k/mk/pc/tstack.c    -I./include  -o tstack.o	
    
tasks.o:	
	gcc -c  k/mk/pc/tasks.c     -I./include  -o tasks.o	
	
	
create.o:	
	gcc -c  k/mk/pc/create.c    -I./include  -o create.o
	
	
#	rem mk/pc/ipc 
spawn.o:
	gcc -c  k/mk/pc/ipc/spawn.c  -I./include  -o spawn.o
	
callout.o:	
	gcc -c  k/mk/pc/ipc/callout.c  -I./include  -o callout.o
	
callfar.o:	
	gcc -c  k/mk/pc/ipc/callfar.c  -I./include  -o callfar.o
    
ipc.o:	
	gcc -c  k/mk/pc/ipc/ipc.c  -I./include  -o ipc.o	
	
sem.o: gcc -c  k/mk/pc/ipc/sem.c  -I./include  -o sem.o \

#	rem ...
#	rem mk/pc/sched
sched.o: gcc -c  k/mk/pc/sched/sched.c  -I./include -o sched.o \

schedi.o: gcc -c  k/mk/pc/sched/schedi.c -I./include -o schedi.o    	
	
#	rem /mk/pc/mm (memory manager)
memory.o: gcc -c k/mk/pc/mm/memory.c  -I./include -o memory.o    
	
#	rem /mk/pc/mm (memory manager)
pages.o: gcc -c k/mk/pc/mm/pages.c   -I./include -o pages.o 	
	
request.o:	gcc -c  k/mk/request.c -I./include -o request.o	
	
faults.o: gcc -c  k/mk/faults.c -I./include -o faults.o		
	
	
#:Executive_Job3	
#echo ~{ ...
#echo ~{ ux2 /execve
#	rem /execve
execve.o:
	gcc -c k/execve/execve.c  -I./include -o execve.o	
	
#	rem services - System Call Interface.  
services.o: gcc -c k/execve/sci/services.c  -I./include -o services.o		
	
#    rem execve/dd
		
#	rem sm
#	rem /execve/init
init.o: gcc -c k/execve/dd/sm/init/init.c -I./include -o init.o
#	rem /execve/sm/ob
	
object.o: gcc -c k/execve/dd/sm/ob/object.c -I./include -o object.o		
#	rem /execve/network
	
nic.o: gcc -c k/execve/dd/sm/network/nic.c     -I./include -o nic.o
	
network.o: gcc -c k/execve/dd/sm/network/network.c -I./include -o network.o
	
socket.o:	
	gcc -c k/execve/dd/sm/network/socket.c  -I./include -o socket.o
#	rem System Management.
	
#	rem /execve/sm/sys
#   rem system
modules.o: gcc -c k/execve/dd/sm/sys/modules.c  -I./include -o modules.o
#    rem procedure
proc.o: gcc -c k/execve/dd/sm/sys/proc.c  -I./include -o proc.o	
#    rem abort
abort.o: gcc -c k/execve/dd/sm/sys/abort.c  -I./include -o abort.o		
#    rem info
info.o: gcc -c k/execve/dd/sm/sys/info.c  -I./include -o info.o	
#    rem server manager
sm.o: gcc -c k/execve/dd/sm/sys/sm.c  -I./include -o sm.o
#    rem channel
channel.o: gcc -c k/execve/dd/sm/sys/channel.c  -I./include -o channel.o	
#	rem signal
signal.o: gcc -c k/execve/dd/sm/sys/signal.c  -I./include -o signal.o	
#    rem system
system.o: gcc -c k/execve/dd/sm/sys/system.c  -I./include -o system.o
#	rem io
io.o: gcc -c k/execve/dd/sm/sys/io.c -I./include -o io.o	
	
#    rem sm
#	rem /execve/rt (runtime)
runtime.o: gcc -c k/execve/dd/sm/rt/runtime.c -I./include -o runtime.o
	
#	rem tty
tty.o: gcc -c k/execve/dd/tty/tty.c -I./include -o tty.o		
	
#	rem uitm
#	rem /execve/uitm/libk
misc.o: gcc -c k/execve/dd/uitm/libk/misc.c   -I./include -o misc.o	
	
#	rem uitm
#	rem /execve/uitm/libc
stdlib.o: gcc -c k/execve/dd/uitm/libc/stdlib.c -I./include -o stdlib.o
	
stdio.o: gcc -c k/execve/dd/uitm/libc/stdio.c  -I./include -o stdio.o
    
string.o: gcc -c k/execve/dd/uitm/libc/string.c -I./include -o string.o
	
#	rem uigm Nothing for now.	
		
#	rem sm
#	rem /execve/sm/disk
    
disk.o:	gcc -c k/execve/dd/sm/disk/disk.c   -I./include -o disk.o						
    
volume.o: gcc -c k/execve/dd/sm/disk/volume.c -I./include -o volume.o	
	
#  	rem sm
install.o: gcc -c k/execve/dd/sm/install/install.c -I./include -o install.o    
	
#	rem sm
#	rem /execve/debug
debug.o: gcc -c k/execve/dd/sm/debug/debug.c -I./include -o debug.o	
	
device.o: gcc -c k/execve/dd/device/device.c -I./include -o device.o
	
#	rem (unblocked) legados (K2).
video.o:
	gcc -c k/execve/dd/unb/video.c   -I./include -o video.o 
	
screen.o:	
	gcc -c k/execve/dd/unb/screen.c  -I./include -o screen.o 	
	
keyboard.o:	
	gcc -c k/execve/dd/unb/keyboard.c  -I./include -o keyboard.o
    
mouse.o:	
	gcc -c k/execve/dd/unb/mouse.c  -I./include -o mouse.o  	
	
ldisc.o:	
	gcc -c k/execve/dd/unb/ldisc.c  -I./include -o ldisc.o    	
	
hdd.o:	
	gcc -c k/execve/dd/unb/hdd.c    -I./include -o hdd.o	
	
pic.o:	
	gcc -c k/execve/dd/unb/pic.c   -I./include -o pic.o 
    
timer.o:	
	gcc -c k/execve/dd/unb/timer.c     -I./include -o timer.o	
	
rtc.o:	
	gcc -c k/execve/dd/unb/rtc.c    -I./include -o rtc.o
	
vsync.o:	
	gcc -c k/execve/dd/unb/vsync.c  -I./include -o vsync.o 
	
syscall.o:	
	gcc -c k/execve/dd/unb/arch/x86/syscall.c  -I./include -o syscall.o		
	
cpux86.o:	
	gcc -c k/execve/dd/unb/arch/x86/cpux86.c  -I./include -o cpux86.o 
    
x86.o:	
	gcc -c k/execve/dd/unb/arch/x86/x86.c     -I./include -o x86.o	
	
ports.o:	
	gcc -c k/execve/dd/unb/arch/x86/ports.c   -I./include -o ports.o 	
	
cpuamd.o:	
	gcc -c k/execve/dd/unb/arch/amd/cpuamd.c  -I./include -o cpuamd.o 	    
	
#	rem (blocked) (K1).
pci.o:
	gcc -c k/execve/dd/b/pci.c -I./include -o pci.o
	
usb.o:	
	gcc -c k/execve/dd/b/usb.c -I./include -o usb.o
	
apic.o:	
	gcc -c k/execve/dd/b/apic.c -I./include -o apic.o 

#	rem File system
	
#	rem /execve/fs
fs.o: gcc -c k/execve/fs/fs.c     -I./include -o fs.o						
    
read.o: gcc -c k/execve/fs/read.c   -I./include -o read.o			
   
write.o: gcc -c k/execve/fs/write.c  -I./include -o write.o			
    
cf.o:	
	gcc -c k/execve/fs/cf.c     -I./include -o cf.o			
    
search.o:	
	gcc -c k/execve/fs/search.c -I./include -o search.o			
    
format.o:	
	gcc -c k/execve/fs/format.c -I./include -o format.o	
    
vfs.o:	
	gcc -c k/execve/fs/vfs.c    -I./include -o vfs.o		
	
#echo ~{ ...
#echo ~{ ux1 /gramado \o/	

#	rem k\gramado\gui	
#    rem char
char.o:    
	gcc -c k/gramado/gui/char.c -I./include -o char.o
	
#    rem pixel
pixel.o: gcc -c k/gramado/gui/pixel.c -I./include -o pixel.o 
#    rem line
line.o: gcc -c k/gramado/gui/line.c -I./include -o line.o	
#    rem rect
rect.o: gcc -c k/gramado/gui/rect.c -I./include -o rect.o 
#    rem draw
dtext.o: gcc -c k/gramado/gui/dtext.c -I./include -o dtext.o
#    rem draw
font.o: gcc -c k/gramado/gui/font.c -I./include -o font.o	
#    rem createw
createw.o: gcc -c k/gramado/gui/createw.c -I./include -o createw.o    
#    rem grid
grid.o: gcc -c k/gramado/gui/grid.c -I./include -o grid.o 
#    rem statusbar
sbar.o: gcc -c k/gramado/gui/sbar.c -I./include -o sbar.o 
#    rem menubar
menubar.o: gcc -c k/gramado/gui/menubar.c -I./include -o menubar.o 
#    rem menu
menu.o: gcc -c k/gramado/gui/menu.c -I./include -o menu.o 
#    rem bmp

bmp.o: gcc -c k/gramado/gui/bmp.c -I./include -o bmp.o 
#    rem button

button.o: gcc -c k/gramado/gui/button.c -I./include -o button.o 
#    rem messagebox

mbox.o: gcc -c k/gramado/gui/mbox.c -I./include -o mbox.o
#    rem dialogboxbox

dbox.o: gcc -c k/gramado/gui/dbox.c -I./include -o dbox.o
#	rem background
bg.o: gcc -c k/gramado/gui/bg.c -I./include -o bg.o  
#    rem window
window.o: gcc -c k/gramado/gui/window.c -I./include -o window.o    
#    rem desktop
desktop.o: gcc -c k/gramado/gui/desktop.c -I./include -o desktop.o  
#    rem window station
wstation.o: gcc -c k/gramado/gui/wstation.c -I./include -o wstation.o    
#    rem user section
usession.o: gcc -c k/gramado/gui/usession.c -I./include -o usession.o        
    
#	rem gramado logon e logoff
	
#	rem /gramado/logon
logon.o: gcc -c k/gramado/logon/logon.c -I./include -o logon.o 
#	rem /gramado/logoff
logoff.o: gcc -c k/gramado/logoff/logoff.c -I./include -o logoff.o 

#	rem gramado/user
userenv.o: gcc -c k/gramado/user/userenv.c -I./include -o userenv.o 	

#	rem *gui (GRAMADO)
gramado.o: gcc -c k/gramado/gramado.c -I./include -o gramado.o    	
	

    

#:Moving_Job5  
#echo ~{ ...
#echo ~{ Moving ...   
movebin: 
#move KERNEL.BIN bin\KERNEL.BIN
    
 
#:Clean_Job6	
#echo ~{ ...
#echo ~{ Clean.
clean: 
#del *.o
 
#:End 
#echo End!
endmake: 
#pause
	
	