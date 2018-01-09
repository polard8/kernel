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
	
    SET ROOT=c:\gsrc\boot\vhd\v8.5
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
	-I./browser/  main.asm  -o  SYSTEM.VHD


echo -{ ...
echo -{ Size={31MB}
echo -{ Volume letter F:
echo -{ FAT16 File system. 
echo -{ Partition starts on sector 63.

:attachingVHD
	rem Montando um disco já formatado.
	imdisk -a -f SYSTEM.VHD -s 31M -m F: -b 63b
	
:Copying
echo -{ ...

    copy BM.BIN        F:\
    copy BL.BIN        F:\
    copy KERNEL.BIN    F:\
    copy INIT.BIN      F:\
    copy SHELL.BIN     F:\
    copy TASKMAN.BIN   F:\
    copy INIT.TXT      F:\
	
	REM TESTANDO BMPS.
	
	copy BMP1.BMP      F:\
	REM copy FREDNORA.BMP      F:\
	REM copy DENNIS.BMP      F:\
	REM copy SPOON.BMP      F:\
	REM copy FERRIS2.BMP      F:\
	REM copy GOONIES.BMP      F:\
	rem copy GRAMADO.BMP      F:\
	
	rem ...

:detachingVHD
echo -{ ...
	imdisk -D -m F:
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


