

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
	
	
vhd-mount:
	-sudo umount /mnt/noraxvhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/noraxvhd/
	
	
	
COPY-STUFF:
:Copying
echo -{ ...

 
	copy c:\norax\bin\BM.BIN      c:\gramado\bin\BM.BIN
	copy c:\norax\bin\BL.BIN      c:\gramado\bin\BL.BIN
	copy c:\norax\bin\KERNEL.BIN  c:\gramado\bin\KERNEL.BIN
	copy c:\norax\bin\*.FON       c:\gramado\bin\*.FON
 

 
	copy c:\gramado\bin\BM.BIN    F:\
    copy c:\gramado\bin\BL.BIN    F:\
	
 
	copy c:\gramado\bin\KERNEL.BIN   F:\
    copy c:\gramado\bin\INIT.BIN     F:\   
    copy c:\gramado\bin\SHELL.BIN    F:\  
    copy c:\gramado\bin\TASKMAN.BIN  F:\   

 
	
 
    copy c:\gramado\arch\x86\boot\vhd\INIT.TXT     F:\
    copy c:\gramado\arch\x86\boot\vhd\USER.TXT     F:\
	copy c:\gramado\arch\x86\boot\vhd\GRAMADO.TXT  F:\
	
 
	
 
	copy c:\gramado\arch\x86\boot\vhd\images\*.BMP  F:\*.BMP
	
 
	
 
	copy c:\gramado\bin\NC2.FON F:\
	
 
	copy c:\gramado\bin\FASM.EXE    F:\
	
 
	copy c:\gramado\bin\APPASM.BIN    F:\
	
 
	
	copy c:\gramado\bin\GRAMC.BIN    F:\
	
	
 
	copy c:\gramado\bin\FASM.BIN    F:\
	
	copy c:\gramado\bin\GRAMCODE.BIN   F:\
	
	copy c:\gramado\bin\FCLASS.BIN    F:\
    copy c:\gramado\bin\JACKPOT.BIN   F:\	
	copy c:\gramado\bin\TASCII.BIN    F:\
		
	copy c:\gramado\bin\TGFE.BIN      F:\
    copy c:\gramado\bin\TPRINTF.BIN    F:\
	
	copy c:\gramado\bin\TCTYPE.BIN    F:\
	
	copy c:\gramado\bin\TBST.BIN    F:\
	copy c:\gramado\bin\TBST2.BIN    F:\
    copy c:\gramado\bin\TBST3.BIN    F:\
	
	
 
	copy c:\gramado\arch\x86\boot\vhd\tests\*.C  F:\*.C 
	copy c:\gramado\arch\x86\boot\vhd\tests\*.TXT  F:\*.TXT
	copy c:\gramado\arch\x86\boot\vhd\tests\*.ASM  F:\*.ASM
 
 
	
 
	copy c:\gramado\arch\x86\boot\vhd\tests\TEST1.SH1   F:\
	
	
 
	
:creatingFolders:

 
 
	
	mkdir F:\BIN
	mkdir F:\DEV
	mkdir F:\LIB
    mkdir F:\USR
	mkdir F:\SBIN  
	mkdir F:\TMP
	mkdir F:\ETC 
 
	
	
	mkdir F:\USR\BIN
	mkdir F:\USR\INCLUDE
	mkdir F:\USR\LIB 
	
 
	copy c:\gramado\bin\*.BIN    F:\BIN\*.BIN
	
 
	
    mkdir F:\USERS\DEFAULT
    copy c:\gramado\arch\x86\boot\vhd\USER.TXT    F:\USERS\DEFAULT\USER.TXT	
	
	copy GRAMADO.VHD c:\gramado\GRAMADO.VHD	


# umount
vhd-unmount:
	sudo umount /mnt/noraxvhd


/mnt/noraxvhd:
	sudo mkdir /mnt/noraxvhd