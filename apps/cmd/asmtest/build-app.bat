:SetUp
@echo off  

    cd c:\sdk\bin

:Monting
echo -{ ...
echo -{ Creating application APPASM.BIN ...

	echo -{ 1 ...
	nasm c:\gramado\cmd\asmtest\appasm.asm -I c:\gramado\include\asm\  -f elf -o appasm.o

    
	
    rem move a lib para se juntar com o objeto do aplicativo.
	echo -{ 2 ...
	copy c:\gramado\lib\asm.o  c:\sdk\bin\asm.o
 
 
:Objects	
set myObjects=appasm.o ^
asm.o  


:Linking  
echo -{ ...
echo -{ Linking objects ... 
   
   echo -{ 3 ...
   ld -T c:\gramado\cmd\asmtest\link.ld -o APPASM.BIN %myObjects% 
   
   rem Não deletar os objetos.
 
:Moving  
    echo -{ 4 ... 
    move APPASM.BIN c:\gramado\bin\APPASM.BIN
   
:End   
echo End!
	pause