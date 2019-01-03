:SetUp
@echo off

    rem
	rem Objetivo:
    rem Esse código cria um VHD com MBR e código de boot no começo do disco,
	rem e também os elementos básicos do sistema de arquivos fat16, como
	rem vbr, fat, root ...
    rem
	rem nasm 2.05.01
	rem imdisk 2.0.9
	rem
    rem SET BuildFlags=-h
    rem if "%BuildFlags%" == "-h" goto HowItWorks
    rem if "%BuildFlags%" == "-?" goto Usage	
    rem ...
	
:readNotification:	
echo -{ ...
echo -{ Warning: This script will create a VHD and install Gramado on it.
echo -{ Warning: You need to run this script as administrator.
	pause

    rem
	rem Ordem de montagem:
	rem stage1, stage2, msm, bl, kernel, browser, fat16 stuff and vhd footer.
	rem
	
	
	cd c:\sdk\bin

:Start 
echo -{ ... 	
echo -{ Creating a formated VHD. 

    rem Obs: O disco é criado já com a primeira partição formatada.
	
    rem SET ROOT=C:\gramado\g03\branch\boot\vhd\v8.9
	rem cd %ROOT%
	
	nasm -I c:/gramado/arch/x86/boot/vhd/stage1/ ^
	-I c:/gramado/arch/x86/boot/vhd/stage2/ ^
	-I c:/gramado/arch/x86/boot/vhd/stage2/lib16/ ^
	-I c:/gramado/arch/x86/boot/vhd/stage2/include/ ^
	-I c:/gramado/arch/x86/boot/vhd/msm/ ^
	-I c:/gramado/arch/x86/boot/vhd/msm/lib32/ ^
	-I c:/gramado/arch/x86/boot/vhd/msm/include/ ^
	-I c:/gramado/arch/x86/boot/vhd/msm/kernel/ ^
	-I c:/gramado/arch/x86/boot/vhd/msm/fs/ ^
	-I c:/gramado/arch/x86/boot/vhd/msm/shell/ ^
	-I c:/gramado/arch/x86/boot/vhd/msm/drivers/ ^
	-I c:/gramado/arch/x86/boot/vhd/bl/ ^
	-I c:/gramado/arch/x86/boot/vhd/kernel/ ^
	-I c:/gramado/arch/x86/boot/vhd/browser/  c:/gramado/arch/x86/boot/vhd/main.asm  -o  GRAMADO.VHD


echo -{ ...
echo -{ Size={31MB}
echo -{ Volume letter F:
echo -{ FAT16 File system. 
echo -{ Partition starts on sector 63.

:attachingVHD
	rem Montando um disco já formatado.
	imdisk -a -f GRAMADO.VHD -s 31M -m F: -b 63b
		
:Copying
echo -{ ...

    rem copiando todos os binários do norax para o gramado. 
	rem copy c:\norax\bin\*.BIN c:\gramado\bin\*.BIN
	copy c:\norax\bin\BM.BIN      c:\gramado\bin\BM.BIN
	copy c:\norax\bin\BL.BIN      c:\gramado\bin\BL.BIN
	copy c:\norax\bin\KERNEL.BIN  c:\gramado\bin\KERNEL.BIN
	copy c:\norax\bin\*.FON       c:\gramado\bin\*.FON
	REM continua ...

    rem Principais.
	copy c:\gramado\bin\BM.BIN       F:\
    copy c:\gramado\bin\BL.BIN       F:\
	copy c:\gramado\bin\KERNEL.BIN   F:\
    copy c:\gramado\bin\INIT.BIN     F:\   
    copy c:\gramado\bin\SHELL.BIN    F:\  
    copy c:\gramado\bin\TASKMAN.BIN  F:\   	
	
	rem config stuff
    copy c:\gramado\arch\x86\boot\vhd\INIT.TXT     F:\
    copy c:\gramado\arch\x86\boot\vhd\USER.TXT     F:\
	copy c:\gramado\arch\x86\boot\vhd\GRAMADO.TXT  F:\
	
	REM copy c:\gramado\arch\x86\boot\vhd\FILE2KB.TXT  F:\
	
	rem BMPs
	copy c:\gramado\arch\x86\boot\vhd\images\*.BMP  F:\*.BMP
	
	
	rem
	rem ## TESTS ##
    rem 
	
	rem font
	copy c:\gramado\bin\NC2.FON F:\
	
	rem test  ... fasm
	copy c:\gramado\bin\FASM.EXE    F:\
	
	rem testando programa em assembly
	copy c:\gramado\bin\APPASM.BIN    F:\
	
	rem copy c:\gramado\bin\GRAMCC.BIN    F:\
	
	copy c:\gramado\bin\GRAMC.BIN    F:\
	
	rem FASM WITH LIC INTERFACE
	copy c:\gramado\bin\FASM.BIN      F:\
	copy c:\gramado\bin\GRAMCODE.BIN  F:\
	copy c:\gramado\bin\FCLASS.BIN    F:\
    copy c:\gramado\bin\JACKPOT.BIN   F:\	
	copy c:\gramado\bin\TASCII.BIN    F:\
	copy c:\gramado\bin\TGFE.BIN      F:\
    copy c:\gramado\bin\TPRINTF.BIN   F:\
	copy c:\gramado\bin\TCTYPE.BIN    F:\
	copy c:\gramado\bin\TBST.BIN      F:\
	copy c:\gramado\bin\TBST2.BIN     F:\
    copy c:\gramado\bin\TBST3.BIN     F:\
	
	
	rem arquivos de texto.
	copy c:\gramado\arch\x86\boot\vhd\tests\*.C    F:\*.C 
	copy c:\gramado\arch\x86\boot\vhd\tests\*.TXT  F:\*.TXT
	copy c:\gramado\arch\x86\boot\vhd\tests\*.ASM  F:\*.ASM
	REM copy c:\gramado\arch\x86\boot\vhd\tests\TEST.C F:\
	rem copy tests\TEST2.C  F:\
	rem copy tests\REGRAS.TXT   F:\
	rem copy tests\REGRA1.TXT   F:\
	
	rem scripts
	copy c:\gramado\arch\x86\boot\vhd\tests\TEST1.SH1   F:\
	
	
	rem ...
	
:creatingFolders:

    REM ESSA ROTINA DEVERÁ SER FEITA PELO INSTALADOR.
	REM MAS NO CASO ESSE É O INSTALADOR POR ENQUANTO.

    rem #todo 	
	rem #importante:
	rem O host Windows usa letras maiúsculas para criar os diretórios.
    rem O usuário digita letras minúsculas, mas o Gramado procura pode letras 
	rem maiúsculas.
	rem Esse problema aparecerá em todos os sistemas operacionais que usaram 
	rem o Windows como host.
	rem 
	
    rem unix-like
	rem só o makefile criará essas pastas.
	
	REM Única pasta criada com o bat.
	mkdir F:\WIN
	copy c:\gramado\arch\x86\boot\vhd\images\*.BMP  F:\WIN\*.BMP
	

:detachingVHD
echo -{ ...
	imdisk -D -m F:
	
:vhd	
echo -{ ...
    echo -{ copying vhd
	copy GRAMADO.VHD c:\gramado\GRAMADO.VHD	
    goto End

:HowItWorks	
    echo -{ ...
	echo -{ How it works ?
	echo -{ + nasm.exe mount the main.asm file creating the SYSTEM.VHD file.
	echo -{ + The main.asm file has a MBR, VBR, FATs, ROOTDIR, DATAAREA and a vhd footer.
	echo -{   So the SYSTEM.VHD is created as a formated disk.
    echo -{ + imdisk.exe attachs the VHD disk, mounting it on the host OS.
	echo -{ + The script moves all the .bin files to the mounted disk.
    echo -{ + imdisk.exe detachs the VHD disk.
    echo -{ + The script ends.
    echo -{ Warning: You need to run this script as administrator.	
    goto End
	
:Usage
    echo -{ ...
	echo -{ Usage:
    echo -{ Warning: This script will create a VHD and install Gramado on it.
    echo -{ Warning: You need to run this script as administrator.
	echo -{ -? flag shows this usage message.
	echo -{ @todo
:End
echo -{ ...
echo -{ End.
	pause


