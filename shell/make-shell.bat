:Setup
@echo off  

:Start
echo -{ ...
echo -{ Creating application SHELL.BIN ...
echo -{ Creating head.o ...
	nasm  head.s  -felf -o head.o
    rem essa deveria ser crt0.s ? (C RunTime)
	
echo -{ Creating main.o ...	
	gcc  -c  main.c  -o main.o  
	
:SetingObjects		
set myObjects=head.o ^
main.o ^
api.o ^
stdio.o ^
stdlib.o ^
string.o 





:Linking
echo -{ ...
echo -{ Linking ... 
   ld -T link.ld -o SHELL.BIN %myObjects% -Map shell_map.s
   
   rem
   rem NÃO pode deletar os objetos que foram incluídos.
   rem @todo: Deve haver uma pasta para biblioteca dentro do /sdk.
   rem ex: /sdk/libc   /sdk/gl.
   rem
   
:Moving
echo -{ Moving ...    
   move SHELL.BIN bin\SHELL.BIN 

:End   
echo End!
	pause