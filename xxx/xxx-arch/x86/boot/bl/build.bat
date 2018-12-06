:SetUp
@echo off 

    rem
    rem Esse script compila o Boot Loader. (BL.BIN).
    rem	 
	
	cd c:\sdk\bin

:Start
echo -{ ...
echo -{ Boot Loader - (BL.BIN)
	gcc  -c  c:/gramado/arch/x86/boot/bl/src/main.c  -I c:/gramado/arch/x86/boot/bl/include  -o main.o 

rem echo -{ ...
echo -{ Loader	
    gcc  -c  c:/gramado/arch/x86/boot/bl/src/loader/loader.c  -I c:/gramado/arch/x86/boot/bl/include  -o loader.o	
	
rem echo -{ ...
echo -{ Core
    rem head.s
	nasm  -I c:/gramado/arch/x86/boot/bl/src/core/head/x86/   c:/gramado/arch/x86/boot/bl/src/core/head/x86/head.s  -felf -o head.o

    rem c. 
    gcc  -c  c:/gramado/arch/x86/boot/bl/src/core/faults.c  -I c:/gramado/arch/x86/boot/bl/include  -o faults.o
	gcc  -c  c:/gramado/arch/x86/boot/bl/src/core/pages.c   -I c:/gramado/arch/x86/boot/bl/include  -o pages.o

rem echo -{ ...
echo -{ Libc
    gcc -c c:/gramado/arch/x86/boot/bl/src/libc/stdio.c     -I c:/gramado/arch/x86/boot/bl/include  -o stdio.o
    gcc -c c:/gramado/arch/x86/boot/bl/src/libc/string.c    -I c:/gramado/arch/x86/boot/bl/include  -o string.o
		
rem echo -{ ...
echo -{ Init
    gcc -c c:/gramado/arch/x86/boot/bl/src/init/init.c -I c:/gramado/arch/x86/boot/bl/include  -o init.o 		
	
rem echo -{ ...
echo -{ Sys
    gcc -c c:/gramado/arch/x86/boot/bl/src/sys/procedure.c   -I c:/gramado/arch/x86/boot/bl/include -o procedure.o	
    gcc -c c:/gramado/arch/x86/boot/bl/src/sys/services.c    -I c:/gramado/arch/x86/boot/bl/include -o services.o		
    gcc -c c:/gramado/arch/x86/boot/bl/src/sys/abort.c       -I c:/gramado/arch/x86/boot/bl/include -o abort.o		
	
rem echo -{ ...
echo -{ Arch
    gcc -c c:/gramado/arch/x86/boot/bl/src/arch/x86/x86.c               -I c:/gramado/arch/x86/boot/bl/include  -o x86.o
	gcc -c c:/gramado/arch/x86/boot/bl/src/arch/x86/ports.c             -I c:/gramado/arch/x86/boot/bl/include  -o ports.o 
    gcc -c c:/gramado/arch/x86/boot/bl/src/arch/x86/drivers/pci.c       -I c:/gramado/arch/x86/boot/bl/include  -o pci.o	
    gcc -c c:/gramado/arch/x86/boot/bl/src/arch/x86/drivers/hdd.c       -I c:/gramado/arch/x86/boot/bl/include  -o hdd.o	
	gcc -c c:/gramado/arch/x86/boot/bl/src/arch/x86/drivers/keyboard.c  -I c:/gramado/arch/x86/boot/bl/include  -o keyboard.o
    gcc -c c:/gramado/arch/x86/boot/bl/src/arch/x86/drivers/timer.c     -I c:/gramado/arch/x86/boot/bl/include  -o timer.o	
	
rem echo -{ ...
echo -{ Fs
    gcc -c c:/gramado/arch/x86/boot/bl/src/fs/fs.c  -I c:/gramado/arch/x86/boot/bl/include  -o fs.o						

rem echo -{ ...
echo -{ Shell
    gcc -c c:/gramado/arch/x86/boot/bl/src/shell/shell.c  -I c:/gramado/arch/x86/boot/bl/include  -o shell.o


	REM Ordem: Fica em último as rotinas usadas com menor frequência.
	
:Objects	
set my_objects=head.o ^
main.o ^
loader.o ^
init.o ^
ports.o ^
x86.o ^
stdio.o ^
string.o ^
keyboard.o ^
pci.o ^
hdd.o ^
timer.o ^
pages.o ^
procedure.o ^
fs.o ^
shell.o ^
services.o ^
abort.o ^
faults.o  


:Linking  
echo -{ ...
echo -{ Linking objects ... 
    ld -T c:/gramado/arch/x86/boot/bl/link.ld -o BL.BIN %my_objects% -Map bl_map.s
   
:Moving   
echo -{ ...
echo -{ Movendo ...   
    move BL.BIN c:\gramado\bin\BL.BIN

:Clean	
echo -{ ...
echo -{ Clean
    del *.o

:End	
echo END!
	pause
	
	