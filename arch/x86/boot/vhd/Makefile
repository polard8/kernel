
#history:
#2019 - Created by Luciano Gonçalez.


all: GRAMADO.VHD vhd-mount docopy vhd-unmount finalize
#vhd-unmount

GRAMADO.VHD:

	nasm -I stage1/ \
	-I stage2/ \
	-I stage2/lib16/ \
	-I stage2/include/ \
	-I msm/ \
	-I msm/lib32/ \
	-I msm/include/ \
	-I msm/kernel/ \
	-I msm/fs/ \
	-I msm/shell/ \
	-I msm/drivers/ \
	-I bl/ \
	-I kernel/ \
	-I browser/  main.asm  -o  GRAMADO.VHD


/mnt/gramadovhd:
	sudo mkdir /mnt/gramadovhd

vhd-mount: /mnt/gramadovhd
	-sudo umount /mnt/gramadovhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadovhd

# umount
vhd-unmount:
	sudo umount /mnt/gramadovhd

#COPY-STUFF
docopy: createfolders
#Copying
#echo -{ ...

	cp ../../../../../norax/bin/BM.BIN      ../../../../bin
	cp ../../../../../norax/bin/BL.BIN      ../../../../bin
	cp ../../../../../norax/bin/KERNEL.BIN  ../../../../bin
	cp ../../../../../norax/bin/*.FON       ../../../../bin

#root
	sudo cp ../../../../bin/BM.BIN       /mnt/gramadovhd
	sudo cp ../../../../bin/BL.BIN       /mnt/gramadovhd
	sudo cp ../../../../bin/KERNEL.BIN   /mnt/gramadovhd
	sudo cp ../../../../bin/INIT.BIN     /mnt/gramadovhd
	sudo cp ../../../../bin/SHELL.BIN    /mnt/gramadovhd
	sudo cp ../../../../bin/TASKMAN.BIN  /mnt/gramadovhd
	sudo cp ../../../../arch/x86/boot/vhd/INIT.TXT      /mnt/gramadovhd
	sudo cp ../../../../arch/x86/boot/vhd/USER.TXT      /mnt/gramadovhd
	sudo cp ../../../../arch/x86/boot/vhd/GRAMADO.TXT   /mnt/gramadovhd
	sudo cp ../../../../arch/x86/boot/vhd/images/*.BMP  /mnt/gramadovhd
	sudo cp ../../../../bin/NC2.FON       /mnt/gramadovhd
#	sudo cp ../../../../bin/FASM.EXE /mnt/gramadovhd
	sudo cp ../../../../bin/APPASM.BIN    /mnt/gramadovhd
	sudo cp ../../../../bin/GRAMC.BIN     /mnt/gramadovhd
	sudo cp ../../../../bin/FASM.BIN      /mnt/gramadovhd
	sudo cp ../../../../bin/GRAMCODE.BIN  /mnt/gramadovhd
	sudo cp ../../../../bin/FCLASS.BIN    /mnt/gramadovhd
	sudo cp ../../../../bin/JACKPOT.BIN   /mnt/gramadovhd
	sudo cp ../../../../bin/TASCII.BIN    /mnt/gramadovhd
#	sudo cp ../../../../bin/TGFE.BIN /mnt/gramadovhd
	sudo cp ../../../../bin/TPRINTF.BIN   /mnt/gramadovhd
	sudo cp ../../../../bin/TCTYPE.BIN    /mnt/gramadovhd
	sudo cp ../../../../bin/TBST.BIN      /mnt/gramadovhd
	sudo cp ../../../../bin/TBST2.BIN     /mnt/gramadovhd
	sudo cp ../../../../bin/TBST3.BIN     /mnt/gramadovhd
	sudo cp ../../../../arch/x86/boot/vhd/tests/*.C        /mnt/gramadovhd
#	sudo cp ../../../../arch/x86/boot/vhd/tests/*.TXT  /mnt/gramadovhd
	sudo cp ../../../../arch/x86/boot/vhd/tests/*.ASM      /mnt/gramadovhd
	sudo cp ../../../../arch/x86/boot/vhd/tests/TEST1.SH1  /mnt/gramadovhd


#unix-like folders
	sudo cp ../../../../bin/*.BIN                     /mnt/gramadovhd/bin/
	sudo cp ../../../../arch/x86/boot/vhd/USER.TXT    /mnt/gramadovhd/users/default/
	
	
#WIN folder
	sudo cp ../../../../arch/x86/boot/vhd/images/*.BMP  /mnt/gramadovhd/WIN

createfolders:
	-sudo mkdir /mnt/gramadovhd/WIN

#unix-like folders
	-sudo mkdir /mnt/gramadovhd/boot
	-sudo mkdir /mnt/gramadovhd/bin
	-sudo mkdir /mnt/gramadovhd/dev
	-sudo mkdir /mnt/gramadovhd/lib
	-sudo mkdir /mnt/gramadovhd/sbin
	-sudo mkdir /mnt/gramadovhd/tmp
	-sudo mkdir /mnt/gramadovhd/etc
	-sudo mkdir /mnt/gramadovhd/proc
	-sudo mkdir /mnt/gramadovhd/home
	-sudo mkdir /mnt/gramadovhd/mnt
	-sudo mkdir /mnt/gramadovhd/media
	-sudo mkdir /mnt/gramadovhd/usr
	-sudo mkdir -p /mnt/gramadovhd/usr/bin
	-sudo mkdir -p /mnt/gramadovhd/usr/include
	-sudo mkdir -p /mnt/gramadovhd/usr/lib
	-sudo mkdir -p /mnt/gramadovhd/users
	-sudo mkdir -p /mnt/gramadovhd/users/default


finalize:
	cp GRAMADO.VHD ../../../../
	-rm GRAMADO.VHD  
	
	
