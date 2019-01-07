:Setup
@echo off  

rem
rem File: makeApi.bat
rem
rem Esse script compila a API para sistema de 32bit para desktop.
rem Apenas gera um arquivo objeto, que será incluído na aplicação
rem em tempo de compilação.
rem Sep 2016.
rem

    cd c:\sdk\bin

:Compiling
echo -{ Gramado API
echo -{ ...
echo -{ Compiling api.c
    gcc -c c:\norax\lib\api-src\src\api.c -I c:\norax\lib\api-src\include -o api.o -save-temps 
    rem Nothing.
	
:Moving
echo -{ ...
echo -{ Moving ...	
    rem move *.o obj/
	move api.o c:\norax\lib\api\api.o
	
	
:End
echo -{ ...
echo Done!
    pause