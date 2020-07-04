# License: BSD License
VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 41
EXTRAVERSION = 
NAME = Gramado 1.0

# Documentation.
# See: docs/
# To see the targets execute "make help".


# That's our default target when none is given on the command line.
PHONY := _all
_all: all

	@echo "That's all!"
	


KERNELVERSION = $(VERSION)$(if $(PATCHLEVEL),.$(PATCHLEVEL)$(if $(SUBLEVEL),.$(SUBLEVEL)))$(EXTRAVERSION)

export KBUILD_IMAGE ?= KERNEL.BIN 


srctree := .
objtree := .
src := $(srctree)
obj := $(objtree)
 
 
# Make variables (CC, etc...)
AS	= as
LD	= ld
CC	= gcc
AR	= ar
MAKE	= make
NASM	= nasm
OBJCOPY	= objcopy
OBJDUMP	= objdump
LEX	= flex
YACC	= bison
PERL	= perl
PYTHON	= python
PYTHON2	= python2
PYTHON3	= python3
RUBY	= ruby



# Verbose.

ifndef KBUILD_VERBOSE
  KBUILD_VERBOSE = 1
endif

ifeq ($(KBUILD_VERBOSE),1)
  Q =
else
  Q = @
endif


#
# Begin.
#

## ====================================================================
## Step0 build-system-files - Libraries and apps.
## Step1 KERNEL.BIN         - Creating the kernel image.
## Step2 kernel-image-link  - Linking the kernel image.
## Step3 /mnt/gramadovhd    - Creating the directory to mount the VHD.
## Step4 vhd-create         - Creating a VHD in Assembly language.
## Step5 vhd-mount          - Mounting the VHD.
## Step6 vhd-copy-files     - Copying files into the mounted VHD.
## Step7 vhd-unmount        - Unmounting the VHD.
## Step8 clean              - Deleting the object files.           

PHONY := all

all: build-system-files \
KERNEL.BIN \
/mnt/gramadovhd  \
vhd-create \
vhd-mount \
vhd-copy-files \
vhd-unmount \
clean \
clean-system-files


	#Giving permitions to run ./run hahaha
	chmod 755 ./run

#	@echo "Gramado $(VERSION) $(PATCHLEVEL) $(SUBLEVEL) $(EXTRAVERSION) $(NAME) "
#	@echo "Arch x86"
	@echo "Gramado $(KERNELVERSION) ($(NAME)) "
#	@echo "$(ARCH)"



# Building system files.
# boot, libs, apps and commands.
# #todo: fonts.



PHONY := build-system-files

#Step 0
build-system-files: /usr/local/gramado-build \
build-boot \
build-lib \
build-init \
build-gdeshell \
build-gns \
build-gws \
build-apps \
build-cmd


/usr/local/gramado-build:
	-sudo mkdir /usr/local/gramado-build
	
build-boot:

	@echo "==================="
	@echo "Compiling BM ... "
	$(Q) $(MAKE) -C gramado/boot/x86/bm/ 

	@echo "==================="
	@echo "Compiling BL ... "
	$(Q) $(MAKE) -C gramado/boot/x86/bl/ 
	
build-lib:
#	@echo "==================="
#	@echo "Compiling gramado libs ..."
#	make -C gramado/lib

#	@echo "==================="
#	@echo "Compiling animal libs ..."
#	make -C animal/lib

	@echo "==================="
	@echo "Compiling libs ..."
	$(Q) $(MAKE) -C lib

build-init:
	@echo "==================="
	@echo "Compiling init process ... [TODO]"
	$(Q) $(MAKE) -C gramado/init

build-gdeshell:
	@echo "==================="
	@echo " Compiling the gdeshell"
	$(Q) $(MAKE) -C gramado/gdeshell   


build-gns:
	@echo "==================="
	@echo " Compiling the gns"
	$(Q) $(MAKE) -C services/gns   

build-gws:
	@echo "==================="
	@echo " Compiling the gws"
	$(Q) $(MAKE) -C services/gws   

build-apps:
	@echo "==================="
	@echo "Compiling apps ..."
	$(Q) $(MAKE) -C animal/apps

build-cmd:
	@echo "==================="
	@echo "Compiling cmd ..."
	$(Q) $(MAKE) -C animal/cmd
	



## Step1 KERNEL.BIN         - Creating the kernel image.
KERNEL.BIN: 
	@echo "================================="
	@echo "(Step 1) Creating the kernel image ..."

	$(Q) $(MAKE) -C gramado/kernel   


## Step3 /mnt/gramadovhd    - Creating the directory to mount the VHD.
/mnt/gramadovhd:
	@echo "================================="
	@echo "(Step 3) Creating the directory to mount the VHD ..."

	sudo mkdir /mnt/gramadovhd


## Step4 vhd-create         - Creating a VHD in Assembly language.
vhd-create:
	@echo "================================="
	@echo "(Step 4) Creating a VHD in Assembly language ..."

	$(NASM) gramado/boot/x86/vhd/main.asm -I gramado/boot/x86/vhd/ -o GRAMADO.VHD   
	


## Step5 vhd-mount          - Mounting the VHD.
vhd-mount:
	@echo "================================="
	@echo "(Step 5) Mounting the VHD ..."

	-sudo umount /mnt/gramadovhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadovhd/

## Step6 vhd-copy-files     - Copying files into the mounted VHD.
vhd-copy-files:
	@echo "================================="
	@echo "(Step 6) Copying files into the mounted VHD ..."

# ======== Files in the root dir. ========

	# First of all
	# bm, bl, kernel, init, gdeshell.

	sudo cp gramado/boot/x86/bin/BM.BIN    /mnt/gramadovhd
	sudo cp gramado/boot/x86/bin/BL.BIN    /mnt/gramadovhd
	sudo cp gramado/kernel/KERNEL.BIN      /mnt/gramadovhd
	sudo cp gramado/gdeshell/GDESHELL.BIN  /mnt/gramadovhd 
	#sudo cp gramado/install/ISHELL.BIN  /mnt/gramadovhd 
	
	sudo cp gramado/init/INIT.BIN        /mnt/gramadovhd
	sudo cp gramado/base/GRAMADO.TXT     /mnt/gramadovhd
	sudo cp gramado/base/ini/GUI.INI     /mnt/gramadovhd
	sudo cp gramado/base/ini/INIT.INI    /mnt/gramadovhd
	sudo cp gramado/base/ini/USER.INI    /mnt/gramadovhd
	sudo cp gramado/base/res/fonts/bin/NC2.FON        /mnt/gramadovhd
	sudo cp gramado/base/res/fonts/bin/LIN8X8.FON     /mnt/gramadovhd
	sudo cp gramado/base/res/fonts/bin/LIN8X16.FON    /mnt/gramadovhd
	sudo cp gramado/base/res/cursors/CURSOR.BMP  /mnt/gramadovhd
	sudo cp gramado/base/res/cursors/MOUSE.BMP   /mnt/gramadovhd
	sudo cp gramado/base/res/icons/APP.BMP       /mnt/gramadovhd
	sudo cp gramado/base/res/icons/BMP1.BMP      /mnt/gramadovhd
	sudo cp gramado/base/res/icons/FILE.BMP      /mnt/gramadovhd
	sudo cp gramado/base/res/icons/FOLDER.BMP    /mnt/gramadovhd
	sudo cp gramado/base/res/icons/TERMINAL.BMP  /mnt/gramadovhd
# ...
	
	# optional
	-sudo cp docs/*.TXT        /mnt/gramadovhd
	-sudo cp gramado/base/dev/LOOP0      /mnt/gramadovhd
	-sudo cp gramado/base/dev/NULL       /mnt/gramadovhd
	-sudo cp gramado/base/dev/SDA        /mnt/gramadovhd
	-sudo cp gramado/base/tests/*.CPP    /mnt/gramadovhd
	-sudo cp gramado/base/tests/*.BAS    /mnt/gramadovhd
	-sudo cp gramado/base/tests/*.ASM    /mnt/gramadovhd
	-sudo cp gramado/base/res/wall/ANIMAL.BMP   /mnt/gramadovhd

	-sudo cp services/gns/bin/GNS.BIN       /mnt/gramadovhd
	-sudo cp services/gns/bin/GNST.BIN      /mnt/gramadovhd
	-sudo cp services/gws/bin/GWS.BIN       /mnt/gramadovhd
	-sudo cp services/gws/bin/GWST.BIN      /mnt/gramadovhd
	
	-sudo cp animal/apps/bin/*.BIN         /mnt/gramadovhd
	-sudo cp animal/cmd/bin/*.BIN          /mnt/gramadovhd
# ...


#
# ======== Creating the all the folders in root dir ========
#		

# Creating standard folders
	-sudo mkdir /mnt/gramadovhd/BIN
	-sudo mkdir /mnt/gramadovhd/BOOT
	-sudo mkdir /mnt/gramadovhd/DEV
	-sudo mkdir /mnt/gramadovhd/DEV/PTS
	-sudo mkdir /mnt/gramadovhd/EFI
	-sudo mkdir /mnt/gramadovhd/EFI/BOOT
	-sudo mkdir /mnt/gramadovhd/ETC
	-sudo mkdir /mnt/gramadovhd/HOME
	-sudo mkdir /mnt/gramadovhd/LIB
	-sudo mkdir /mnt/gramadovhd/MNT
	-sudo mkdir /mnt/gramadovhd/SBIN
	-sudo mkdir /mnt/gramadovhd/TMP
	-sudo mkdir /mnt/gramadovhd/TMP/TMP2
# ...


# ======== Files in the /BOOT/ folder. ========
	sudo cp gramado/kernel/KERNEL.BIN    /mnt/gramadovhd/BOOT
	sudo cp gramado/boot/x86/bin/BM.BIN  /mnt/gramadovhd/BOOT
	sudo cp gramado/boot/x86/bin/BL.BIN  /mnt/gramadovhd/BOOT
	
	-sudo cp gramado/base/res/wall/ANIMAL.BMP   /mnt/gramadovhd/BOOT
	-sudo cp gramado/base/res/wall/ANIMAL.BMP   /mnt/gramadovhd/TMP/TMP2


# ======== Files in the /TMP/ folder. ========
#	-sudo cp base/tests/TEST1.C  /mnt/gramadovhd/TMP
#	-sudo cp base/tests/TEST1.C  /mnt/gramadovhd/TMP/TMP2




## Step7 vhd-unmount        - Unmounting the VHD.
vhd-unmount:
	@echo "================================="
	@echo "(Step 7) Unmounting the VHD ..."

	sudo umount /mnt/gramadovhd


## Step8 clean              - Deleting the object files.           
clean:
	@echo "================================="
	@echo "(Step 8) Deleting the object files ..."

	-rm *.o
	@echo "Success?"

clean2:
	-rm *.ISO
	-rm *.VHD
	
clean3:
	-rm animal/apps/bin/*.BIN
	-rm animal/cmd/bin/*.BIN
	
PHONY := clean-system-files
clean-system-files:
	@echo "==================="
	@echo "Cleaning all system binaries ..."

	-rm -rf gramado/boot/x86/bin/*.BIN
	
	-rm -rf gramado/kernel/KERNEL.BIN
	-rm -rf gramado/init/*.BIN
	-rm -rf gramado/gdeshell/*.BIN

	-rm -rf services/gns/bin/*.BIN
	-rm -rf services/gws/bin/*.BIN
	
	-rm -rf animal/apps/bin/*.BIN
	-rm -rf animal/cmd/bin/*.BIN
# ...

clean-all: clean clean2 clean3 clean-system-files  

	@echo "==================="
	@echo "ok ?"


## ==================================================================
## The extra stuff.
## 1) ISO support.
## 2) HDD support.
## 3) VM support.
## 4) Serial debug support.
## 5) Clean files support.
## 6) Usage support.
	
#
# ======== ISO ======== 
#

# test
# todo
# Create a .ISO file using nasm.
makeiso-x86:
	#todo:  
	#nasm -I kernel/boot/x86/iso/stage1/ \
	#-I kernel/boot/x86/iso/???/  kernel/boot/x86/iso/main.asm  -o  GRAMADO.ISO
	
	@echo "#todo Create ISO using nasm"
	
# ISO
# Mount stage1.bin file with nasm.
# Create a .ISO file and move all the content of the /bin folder
# into the .ISO file.
geniso-x86:
	
	#stage1
	$(NASM) kernel/boot/x86/iso/stage1/stage1.asm -f bin -o stage1.bin
	cp stage1.bin bin/boot/gramado/
	rm stage1.bin

	#.ISO
#	mkisofs -R -J -c boot/gramado/boot.catalog -b boot/gramado/stage1.bin -no-emul-boot -boot-load-size 4 -boot-info-table -o GRAMADO.ISO bin
	
	@echo "iso Success?"	




#
# ======== HDD ========
#

	
hdd-mount:
	-sudo umount /mnt/gramadohdd
	sudo mount -t vfat -o loop,offset=32256 /dev/sda /mnt/gramadohdd/
#	sudo mount -t vfat -o loop,offset=32256 /dev/sdb /mnt/gramadohdd/
	
hdd-unmount:
	-sudo umount /mnt/gramadohdd
	
hdd-copy-kernel:
	sudo cp bin/boot/KERNEL.BIN /mnt/gramadohdd/BOOT 

danger-hdd-clone-vhd:
	sudo dd if=./GRAMADO.VHD of=/dev/sda
#	sudo dd if=./GRAMADO.VHD of=/dev/sdb




#
# ======== VM ========
#


# Oracle Virtual Box 
oracle-virtual-box-test:
	VBoxManage startvm "Gramado"
#	VBoxManage startvm "Animal"


# qemu 
qemu-test:
	qemu-system-x86_64 -hda GRAMADO.VHD -m 512 -serial stdio 
#	qemu-system-x86_64 -hda GRAMADO.VHD -m 128 -device e1000 -show-cursor -serial stdio -device e1000


test-sda:
	sudo qemu-system-i386 -m 512 -drive file=/dev/sda,format=raw

test-sdb:
	sudo qemu-system-i386 -m 512 -drive file=/dev/sdb,format=raw



#install-kvm-qemu:
#	sudo pacman -S virt-manager qemu vde2 ebtables dnsmasq bridge-utils openbsd-netcat



#
# ======== SERIAL DEBUG ========
#

serial-debug:
	cat ./docs/sdebug.txt


#
# Image support.
#

kernel-version:
	@echo $(KERNELVERSION)

image-name:
	@echo $(KBUILD_IMAGE)


kernel-file-header:
	-rm docs/KFH.TXT
	readelf -h bin/boot/KERNEL.BIN > docs/KFH.TXT
	cat docs/KFH.TXT
	
kernel-program-headers:
	-rm docs/KPH.TXT
	readelf -l bin/boot/KERNEL.BIN > docs/KPH.TXT
	cat docs/KPH.TXT

kernel-section-headers:
	-rm docs/KSH.TXT
	readelf -S bin/boot/KERNEL.BIN > docs/KSH.TXT
	cat docs/KSH.TXT
	


#
# gcc support
#

gcc-test:
	chmod 755 ./scripts/gcccheck
	./scripts/gcccheck


#
# ======== USAGE ========
#

help:
	@echo " help:"
	@echo " all          - make all"
	@echo " clean        - Remove all .o files"
	@echo " clean2       - Remove .VHD and .ISO files"
	@echo " vhd-mount    - Mount VHD"
	@echo " vhd-unmount  - Unmount VHD"
	@echo " qemu-test    - Run on qemu" 
	@echo " oracle-virtual-box-test - Run on virtual-box"
	@echo " ..."

