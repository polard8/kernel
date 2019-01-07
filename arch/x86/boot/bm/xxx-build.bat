:SetUp
@echo off

:readNotification:	
echo -{ ...
echo -{ Warning: This script will create the Boot Manager for Norax kernel.
echo -{ Warning: ...
	pause

    rem
    rem Ordem de montagem:
    rem stage1, stage2, msm, bl, kernel, browser, fat16 stuff and vhd footer.
    rem


    cd c:\sdk\bin

:Start 
echo -{ ... 
echo -{ Creating BM.BIN for Norax

    rem SET ROOT=C:\gramado\g03\branch\boot\bm\r0001
    rem cd %ROOT%

    nasm -I c:/norax/arch/x86/boot/bm/stage1/ ^
         -I c:/norax/arch/x86/boot/bm/stage2/ ^
         -I c:/norax/arch/x86/boot/bm/stage2/include/ ^
         -I c:/norax/arch/x86/boot/bm/stage2/lib16/ ^
         -I c:/norax/arch/x86/boot/bm/stage3/ ^
         -I c:/norax/arch/x86/boot/bm/stage3/drivers/ ^
         -I c:/norax/arch/x86/boot/bm/stage3/fs/ ^
         -I c:/norax/arch/x86/boot/bm/stage3/include/ ^
         -I c:/norax/arch/x86/boot/bm/stage3/kernel/ ^
         -I c:/norax/arch/x86/boot/bm/stage3/lib32/ ^
         -I c:/norax/arch/x86/boot/bm/stage3/shell/  c:/norax/arch/x86/boot/bm/main.asm  -o  BM.BIN


:Copying
    copy BM.BIN c:\norax\bin\BM.BIN 

:End
echo -{ ...
echo -{ End.
	pause


