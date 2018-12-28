:Setup
@echo off  

    cd c:\sdk\bin

:Start
echo -{ ...
echo -{ Creating application SHELL.BIN ...
echo -{ Creating head.o ...
	
	
	nasm  c:\gramado\init\core\shell\head.s  -felf -o head.o
    rem essa deveria ser crt0.s ? (C RunTime)
	
echo -{ Creating main.o ...
    
	rem crt0.o não deve ser compilado aqui ... isso é só um teste.
    gcc -c c:\gramado\init\core\shell\crt0.c     -I c:\gramado\include\libc  -o crt0.o 	
	
	gcc -c c:\gramado\init\core\shell\main.c     -I c:\gramado\include\libc  -o main.o 
    gcc -c c:\gramado\init\core\shell\shellui.c  -I c:\gramado\include\libc  -o shellui.o
    gcc -c c:\gramado\init\core\shell\builtins.c -I c:\gramado\include\libc  -o builtins.o	
	gcc -c c:\gramado\init\core\shell\desktop.c  -I c:\gramado\include\libc  -o desktop.o
	
	gcc -c c:\gramado\init\core\shell\parser.c  -I c:\gramado\include\libc  -o parser.o
	gcc -c c:\gramado\init\core\shell\lexer.c  -I c:\gramado\include\libc  -o lexer.o
	
	gcc -c c:\gramado\init\core\shell\net.c  -I c:\gramado\include\libc  -o net.o	
	
	copy c:\gramado\lib\api\api.o  c:\sdk\bin\api.o
	
	copy c:\gramado\lib\ctype.o   c:\sdk\bin\ctype.o
	copy c:\gramado\lib\stdio.o   c:\sdk\bin\stdio.o
	copy c:\gramado\lib\stdlib.o  c:\sdk\bin\stdlib.o
	copy c:\gramado\lib\string.o  c:\sdk\bin\string.o
	
	copy c:\gramado\lib\conio.o   c:\sdk\bin\conio.o
	copy c:\gramado\lib\wait.o   c:\sdk\bin\wait.o
	
	copy c:\gramado\lib\unistd.o   c:\sdk\bin\unistd.o
	
	
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
unistd.o ^
builtins.o ^
desktop.o ^
parser.o ^
lexer.o ^
wait.o ^
net.o   

   



  


  


:Linking
echo -{ ...
echo -{ Linking ... 
   ld -T c:\gramado\init\core\shell\link.ld -o SHELL.BIN %myObjects% -Map shell_map.s
   
   rem
   rem NÃO pode deletar os objetos que foram incluídos.
   rem @todo: Deve haver uma pasta para biblioteca dentro do /sdk.
   rem ex: /sdk/libc   /sdk/gl.
   rem
   
:Moving
echo -{ Moving ...    
   move SHELL.BIN c:\gramado\bin\SHELL.BIN 

:End   
echo End!
	pause