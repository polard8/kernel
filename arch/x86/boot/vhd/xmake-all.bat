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

:Start 
echo -{ ... 	
echo -{ Creating a formated VHD. 

    rem Obs: O disco é criado já com a primeira partição formatada.
	
    SET ROOT=C:\gramado\g03\branch\boot\vhd\v8.9
	cd %ROOT%
	
	nasm -I./stage1/ ^
	-I./stage2/ ^
	-I./stage2/lib16/ ^
	-I./stage2/include/ ^
	-I./msm/ ^
	-I./msm/lib32/ ^
	-I./msm/include/ ^
	-I./msm/kernel/ ^
	-I./msm/fs/ ^
	-I./msm/shell/ ^
	-I./msm/drivers/ ^
	-I./bl/ ^
	-I./kernel/ ^
	-I./browser/  main.asm  -o  GRAMADO.VHD


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
	copy BM.BIN    F:\
    copy BL.BIN    F:\
    copy INIT.TXT  F:\
    copy USER.TXT  F:\
	
	rem Gramado Core
	copy KERNEL.BIN   F:\
    copy INIT.BIN     F:\
    copy SHELL.BIN    F:\
    copy TASKMAN.BIN  F:\

    rem Gramado Cali

    rem Gramado LA	
	

	rem BMPs
	copy images\BMP1.BMP   F:\
	copy images\MOUSE.BMP  F:\
	copy images\DENNIS.BMP    F:\
	copy images\APP.BMP    F:\
	copy images\FILE.BMP    F:\
	copy images\FOLDER.BMP    F:\
	copy images\TERMINAL.BMP    F:\
	
	REM copy FREDNORA.BMP  F:\
	REM copy SPOON.BMP     F:\
	REM copy FERRIS2.BMP   F:\
	REM copy GOONIES.BMP   F:\
	rem copy GRAMADO.BMP   F:\
	
	

	rem
	rem ## TESTS ##
    rem 
	
	rem font
	copy tests\NC2.FON       F:\
	
	copy tests\TASCII.BIN    F:\
	copy tests\TEDITOR.BIN   F:\
	copy tests\TPRINTF.BIN   F:\	
	copy tests\TSCROLL.BIN   F:\
	copy tests\TGFE.BIN      F:\
	copy tests\TMETRICS.BIN  F:\
	copy tests\JACKPOT.BIN   F:\
	
	copy tests\TSCANF.BIN   F:\
	
	
	copy tests\FCLASS.BIN   F:\
	
	
	REM copy TESTTEST.BIN  F:\
	REM copy LONGEST1.BIN  F:\
    REM copy OPER1.BIN     F:\
	
	rem compiladores
	
    copy tests\FNCC.BIN      F:\	
    copy tests\GRAMCC.BIN      F:\		
	rem copy tests\C4.BIN F:\
	
	rem arquivos de texto.
	copy tests\TEST.C F:\
	copy tests\TEST2.C  F:\
	copy tests\REGRAS.TXT   F:\
	copy tests\REGRA1.TXT   F:\
	
	rem scripts
	copy tests\TEST1.SH1   F:\
	
	
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


