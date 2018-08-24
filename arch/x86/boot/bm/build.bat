:SetUp
@echo off

:readNotification:	
echo -{ ...
echo -{ Warning: This script will create the Boot Manager for Gramado.
echo -{ Warning: ...
	pause

    rem
	rem Ordem de montagem:
	rem stage1, stage2, msm, bl, kernel, browser, fat16 stuff and vhd footer.
	rem

	
	cd c:\sdk\bin
	
:Start 
echo -{ ... 	
echo -{ Creating BM.BIN 
	
    rem SET ROOT=C:\gramado\g03\branch\boot\bm\r0001
	rem cd %ROOT%
	
	nasm -I c:/gramado/arch/x86/boot/bm/stage1/ ^
	-I c:/gramado/arch/x86/boot/bm/stage2/ ^
	-I c:/gramado/arch/x86/boot/bm/stage2/lib16/ ^
	-I c:/gramado/arch/x86/boot/bm/stage2/include/ ^
	-I c:/gramado/arch/x86/boot/bm/msm/ ^
	-I c:/gramado/arch/x86/boot/bm/msm/lib32/ ^
	-I c:/gramado/arch/x86/boot/bm/msm/include/ ^
	-I c:/gramado/arch/x86/boot/bm/msm/kernel/ ^
	-I c:/gramado/arch/x86/boot/bm/msm/fs/ ^
	-I c:/gramado/arch/x86/boot/bm/msm/shell/ ^
	-I c:/gramado/arch/x86/boot/bm/msm/drivers/ ^
	-I c:/gramado/arch/x86/boot/bm/bl/ ^
	-I c:/gramado/arch/x86/boot/bm/kernel/ ^
	-I c:/gramado/arch/x86/boot/bm/browser/  c:/gramado/arch/x86/boot/bm/main.asm  -o  BM.BIN
	
:Copying
    copy BM.BIN c:\gramado\bin\BM.BIN 
	
:End
echo -{ ...
echo -{ End.
	pause


