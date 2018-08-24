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

:Start 
echo -{ ... 	
echo -{ Creating BM.BIN 
	
    SET ROOT=C:\gramado\g03\branch\boot\bm\r0001
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
	-I./browser/  main.asm  -o  BM.BIN
	

	
:End
echo -{ ...
echo -{ End.
	pause


