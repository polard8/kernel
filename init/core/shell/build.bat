:Setup
@echo off  

    cd c:\sdk\bin

:Start
echo -{ ...
echo -{ Creating application SHELL.BIN for Norax kernel...
echo -{ Creating head.o ...
	
	
	nasm  c:\norax\init\core\shell\head.s  -felf -o head.o
    rem essa deveria ser crt0.s ? (C RunTime)
	
echo -{ Creating main.o ...
    
	rem crt0.o não deve ser compilado aqui ... isso é só um teste.
    gcc -c c:\norax\init\core\shell\crt0.c     -I c:\norax\include\libc  -o crt0.o 	
	
	gcc -c c:\norax\init\core\shell\main.c     -I c:\norax\include\libc  -o main.o 
    gcc -c c:\norax\init\core\shell\shellui.c  -I c:\norax\include\libc  -o shellui.o
    gcc -c c:\norax\init\core\shell\builtins.c -I c:\norax\include\libc  -o builtins.o	
	gcc -c c:\norax\init\core\shell\desktop.c  -I c:\norax\include\libc  -o desktop.o
	
	
	copy c:\norax\lib\api\api.o  c:\sdk\bin\api.o
	
	copy c:\norax\lib\ctype.o   c:\sdk\bin\ctype.o
	copy c:\norax\lib\stdio.o   c:\sdk\bin\stdio.o
	copy c:\norax\lib\stdlib.o  c:\sdk\bin\stdlib.o
	copy c:\norax\lib\string.o  c:\sdk\bin\string.o
	copy c:\norax\lib\conio.o   c:\sdk\bin\conio.o
	
:SetingObjects		
set myObjects=head.o ^
crt0.o ^
main.o ^
shellui.o ^
api.o ^
ctype.o ^
stdio.o ^
stdlib.o ^
string.o ^
conio.o ^
builtins.o ^
desktop.o 

  


:Linking
echo -{ ...
echo -{ Linking ... 
   ld -T c:\norax\init\core\shell\link.ld -o SHELL.BIN %myObjects% -Map shell_map.s
   
   rem
   rem NÃO pode deletar os objetos que foram incluídos.
   rem @todo: Deve haver uma pasta para biblioteca dentro do /sdk.
   rem ex: /sdk/libc   /sdk/gl.
   rem
   
:Moving
echo -{ Moving ...    
   move SHELL.BIN c:\norax\bin\SHELL.BIN 

:End   
echo End!
	pause