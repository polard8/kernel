:SetUp
@echo off

    rem
	rem Objetivo:
    rem Esse código cria um VHD com MBR e código de boot no começo do disco,
	rem e também os elementos básicos do sistema de arquivos fat16, como
	rem vbr, fat, root ...
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

    rem Gramado Boot
	copy c:\gramado\bin\BM.BIN    F:\
    copy c:\gramado\bin\BL.BIN    F:\
	
	rem Gramado Core
	copy c:\gramado\bin\KERNEL.BIN   F:\
    copy c:\gramado\bin\INIT.BIN     F:\
    copy c:\gramado\bin\SHELL.BIN    F:\
    copy c:\gramado\bin\TASKMAN.BIN  F:\

    rem Gramado Cali

    rem Gramado LA	
	
	rem config stuff
    copy c:\gramado\arch\x86\boot\vhd\INIT.TXT  F:\
    copy c:\gramado\arch\x86\boot\vhd\USER.TXT  F:\
	
	rem BMPs
	copy c:\gramado\arch\x86\boot\vhd\images\BMP1.BMP   F:\
	copy c:\gramado\arch\x86\boot\vhd\images\MOUSE.BMP  F:\
	copy c:\gramado\arch\x86\boot\vhd\images\DENNIS.BMP    F:\
	copy c:\gramado\arch\x86\boot\vhd\images\APP.BMP    F:\
	copy c:\gramado\arch\x86\boot\vhd\images\FILE.BMP    F:\
	copy c:\gramado\arch\x86\boot\vhd\images\FOLDER.BMP    F:\
	copy c:\gramado\arch\x86\boot\vhd\images\TERMINAL.BMP    F:\
	
	REM copy FREDNORA.BMP  F:\
	REM copy SPOON.BMP     F:\
	REM copy FERRIS2.BMP   F:\
	REM copy GOONIES.BMP   F:\
	rem copy GRAMADO.BMP   F:\
	
	

	rem
	rem ## TESTS ##
    rem 
	
	rem font
	rem copy tests\NC2.FON       F:\
	copy c:\gramado\bin\NC2.FON F:\
	
	rem copy tests\TASCII.BIN    F:\
	rem copy tests\TEDITOR.BIN   F:\
	rem copy tests\TPRINTF.BIN   F:\	
	rem copy tests\TSCROLL.BIN   F:\
	rem copy tests\TGFE.BIN      F:\
	rem copy tests\TMETRICS.BIN  F:\
	rem copy tests\JACKPOT.BIN   F:\
	
	rem copy tests\TSCANF.BIN   F:\
	
	
	rem copy tests\FCLASS.BIN   F:\
	
	
	REM copy TESTTEST.BIN  F:\
	REM copy LONGEST1.BIN  F:\
    REM copy OPER1.BIN     F:\
	
	rem compiladores
	
    rem copy tests\FNCC.BIN      F:\	
    rem copy tests\GRAMCC.BIN      F:\		
	rem copy tests\C4.BIN F:\
	
	rem arquivos de texto.
	rem copy tests\TEST.C F:\
	rem copy tests\TEST2.C  F:\
	rem copy tests\REGRAS.TXT   F:\
	rem copy tests\REGRA1.TXT   F:\
	
	rem scripts
	rem copy tests\TEST1.SH1   F:\
	
	
	rem ...

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


