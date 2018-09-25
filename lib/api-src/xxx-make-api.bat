:Setup
@echo off  

rem
rem File: make-api.bat
rem
rem Esse script compila a API para sistema de 32bit para desktop.
rem Apenas gera um arquivo objeto, que será incluído na aplicação
rem em tempo de compilação.
rem Sep 2016.
rem

:Compiling
echo -{ API
echo -{ ...
echo -{ Compiling api.c
    gcc -c src/api.c -I./include -o api.o -save-temps 
    rem Nothing.
	
:Moving
echo -{ ...
echo -{ Moving ...	
    move *.o obj/
	
:End
echo -{ ...
echo Done!
    pause