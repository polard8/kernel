# makefile para criar um vhd com um sistema 
# para a arquitetura x86 


vhd-x86:
	nasm -I arch/x86/boot/vhd/stage1/ \
	-I arch/x86/boot/vhd/stage2/ \
	-I arch/x86/boot/vhd/stage2/lib16/ \
	-I arch/x86/boot/vhd/stage2/include/ \
	-I arch/x86/boot/vhd/msm/ \
	-I arch/x86/boot/vhd/msm/lib32/ \
	-I arch/x86/boot/vhd/msm/include/ \
	-I arch/x86/boot/vhd/msm/kernel/ \
	-I arch/x86/boot/vhd/msm/fs/ \
	-I arch/x86/boot/vhd/msm/shell/ \
	-I arch/x86/boot/vhd/msm/drivers/ \
	-I arch/x86/boot/vhd/bl/ \
	-I arch/x86/boot/vhd/kernel/ \
	-I arch/x86/boot/vhd/browser/  arch/x86/boot/vhd/main.asm  -o  GRAMADO.VHD
	
	
vhd-mount:
	-sudo umount /mnt/holambravhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/holambravhd/

##
# Copy content to disk
##
vhd-copy-files:
	sudo cp bin/BM.BIN       /mnt/holambravhd
	sudo cp bin/BL.BIN       /mnt/holambravhd
	sudo cp bin/KERNEL.BIN   /mnt/holambravhd
	sudo cp bin/INIT.BIN     /mnt/holambravhd
	sudo cp bin/SHELL.BIN    /mnt/holambravhd
	sudo cp bin/TASKMAN.BIN  /mnt/holambravhd
	
	sudo cp bin/JACKPOT.BIN  /mnt/holambravhd
	sudo cp bin/TASCII.BIN   /mnt/holambravhd
	sudo cp bin/CHTEST.BIN   /mnt/holambravhd
	
# configs
	sudo cp arch/x86/boot/vhd/INIT.TXT /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/USER.TXT /mnt/holambravhd

# bitmaps
	sudo cp arch/x86/boot/vhd/images/BMP1.BMP      /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/MOUSE.BMP     /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/DENNIS.BMP    /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/APP.BMP       /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/FILE.BMP      /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/FOLDER.BMP    /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/TERMINAL.BMP  /mnt/holambravhd
	sudo cp arch/x86/boot/vhd/images/CURSOR.BMP    /mnt/holambravhd

# fonts
	sudo cp bin/NC2.FON /mnt/holambravhd

	# sudo cp bin/FCLASS.BIN   /mnt/noraxvhd
	# sudo cp bin/GRAMCC.BIN   /mnt/noraxvhd
	# sudo cp bin/JACKPOT.BIN  /mnt/noraxvhd
	# sudo cp bin/TASCII.BIN   /mnt/noraxvhd
	# sudo cp bin/TEDITOR.BIN  /mnt/noraxvhd
	# sudo cp bin/TGFE.BIN     /mnt/noraxvhd

# umount
vhd-unmount:
	sudo umount /mnt/holambravhd




/mnt/holambravhd:
	sudo mkdir /mnt/holambravhd
	
	