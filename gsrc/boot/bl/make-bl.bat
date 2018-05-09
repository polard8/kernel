:SetUp
@echo off 

    rem
    rem Esse script compila o Boot Loader. (BL.BIN).
    rem	 

:Start
echo -{ ...
echo -{ Boot Loader - (BL.BIN)
	gcc  -c  src/main.c  -I./include  -o main.o 

echo -{ ...
echo -{ Loader	
    gcc  -c  src/loader/loader.c  -I./include  -o loader.o	
	
echo -{ ...
echo -{ Core
    rem head.s
	nasm  -I./src/core/head/x86/   src/core/head/x86/head.s  -felf -o head.o

    rem c. 
    gcc  -c  src/core/faults.c  -I./include  -o faults.o
	gcc  -c  src/core/pages.c   -I./include  -o pages.o

echo -{ ...
echo -{ Libc
    gcc -c src/libc/stdio.c     -I./include  -o stdio.o
    gcc -c src/libc/string.c    -I./include  -o string.o
	gcc -c src/libc/stdlib.c    -I./include  -o stdlib.o
		
echo -{ ...
echo -{ Init
    gcc -c src/init/init.c -I./include  -o init.o 		
	
echo -{ ...
echo -{ Sys
    gcc -c src/sys/procedure.c   -I./include -o procedure.o	
    gcc -c src/sys/services.c    -I./include -o services.o		
    gcc -c src/sys/abort.c       -I./include -o abort.o		
	
echo -{ ...
echo -{ Arch
    gcc -c src/arch/x86/x86.c               -I./include  -o x86.o
	gcc -c src/arch/x86/ports.c             -I./include  -o ports.o 
    gcc -c src/arch/x86/drivers/pci.c       -I./include  -o pci.o	
    gcc -c src/arch/x86/drivers/hdd.c       -I./include  -o hdd.o	
	gcc -c src/arch/x86/drivers/keyboard.c  -I./include  -o keyboard.o
    gcc -c src/arch/x86/drivers/timer.c     -I./include  -o timer.o	
	
echo -{ ...
echo -{ Fs
    gcc -c src/fs/fs.c  -I./include  -o fs.o						

echo -{ ...
echo -{ Shell
    gcc -c src/shell/shell.c  -I./include  -o shell.o


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
stdlib.o ^
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
    ld -T link.ld -o BL.BIN %my_objects% -Map BL_map.s
   
:Moving   
echo -{ ...
echo -{ Movendo ...   
    move BL.BIN bin\BL.BIN

:Clean	
echo -{ ...
echo -{ Clean
    del *.o

:End	
echo END!
	pause
	
	