# License: BSD License
VERSION = 1
PATCHLEVEL = 0
SUBLEVEL = 92
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
AS      = as
LD      = ld
CC      = gcc
AR      = ar
MAKE	= make
NASM    = nasm
OBJCOPY = objcopy
OBJDUMP = objdump
LEX     = flex
YACC    = bison
PERL    = perl
PYTHON  = python
PYTHON2 = python2
PYTHON3 = python3
RUBY    = ruby


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
build-portals    


/usr/local/gramado-build:
	-sudo mkdir /usr/local/gramado-build


build-boot:
	@echo "==================="
	@echo "Compiling Boot ... "
	$(Q) $(MAKE) -C gramado/boot/x86/bm/ 
	$(Q) $(MAKE) -C gramado/boot/x86/bl/ 

build-portals:
	@echo "==================="
	@echo "Compiling portals ..."
	$(Q) $(MAKE) -C portals/lib/
	$(Q) $(MAKE) -C portals/init/
	$(Q) $(MAKE) -C portals/setup/
	$(Q) $(MAKE) -C portals/services/gnssrv/ 
	$(Q) $(MAKE) -C portals/services/gwssrv/
	$(Q) $(MAKE) -C portals/shell/apps/
	$(Q) $(MAKE) -C portals/shell/cmd/
	$(Q) $(MAKE) -C portals/shell/net/

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


#
# == Creating folders ======================================
#

	# unix-like stuff.
	# Creating standard folders
	-sudo mkdir /mnt/gramadovhd/BIN
	sudo mkdir /mnt/gramadovhd/BOOT
	-sudo mkdir /mnt/gramadovhd/DEV
	-sudo mkdir /mnt/gramadovhd/DEV/PTS
	-sudo mkdir /mnt/gramadovhd/EFI
	-sudo mkdir /mnt/gramadovhd/EFI/BOOT
	-sudo mkdir /mnt/gramadovhd/ETC
	-sudo mkdir /mnt/gramadovhd/HOME
	-sudo mkdir /mnt/gramadovhd/LIB
	-sudo mkdir /mnt/gramadovhd/MNT
	-sudo mkdir /mnt/gramadovhd/PROGRAMS
	-sudo mkdir /mnt/gramadovhd/PORTALS
	-sudo mkdir /mnt/gramadovhd/SBIN
	-sudo mkdir /mnt/gramadovhd/TMP
	-sudo mkdir /mnt/gramadovhd/USERS
	# -sudo mkdir /mnt/gramadovhd/BREAD-AND-WINE



#
# == "/" ====================================================
#

	# 1) First of all
	# bm, bl, kernel, init, gdeshell.
	sudo cp gramado/boot/x86/bin/BM.BIN     /mnt/gramadovhd
	sudo cp gramado/boot/x86/bin/BL.BIN     /mnt/gramadovhd
	sudo cp gramado/kernel/KERNEL.BIN       /mnt/gramadovhd
	sudo cp portals/init/INIT.BIN           /mnt/gramadovhd
	sudo cp portals/setup/bin/GDESHELL.BIN  /mnt/gramadovhd


	# 2) .INI
	sudo cp gramado/base/ini/GUI.INI     /mnt/gramadovhd
	sudo cp gramado/base/ini/INIT.INI    /mnt/gramadovhd
	sudo cp gramado/base/ini/USER.INI    /mnt/gramadovhd

	# 3) .FON
	sudo cp gramado/base/res/fonts/bin/NC2.FON      /mnt/gramadovhd
	sudo cp gramado/base/res/fonts/bin/LIN8X8.FON   /mnt/gramadovhd
	sudo cp gramado/base/res/fonts/bin/LIN8X16.FON  /mnt/gramadovhd

	# 4) .BMP
	sudo cp gramado/base/res/cursors/CURSOR.BMP  /mnt/gramadovhd
	sudo cp gramado/base/res/cursors/MOUSE.BMP   /mnt/gramadovhd
	sudo cp gramado/base/res/icons/APP.BMP       /mnt/gramadovhd
	sudo cp gramado/base/res/icons/BMP1.BMP      /mnt/gramadovhd
	sudo cp gramado/base/res/icons/FILE.BMP      /mnt/gramadovhd
	sudo cp gramado/base/res/icons/FOLDER.BMP    /mnt/gramadovhd
	sudo cp gramado/base/res/icons/TERMINAL.BMP  /mnt/gramadovhd
	# ...

	# 5) .TXT
	sudo cp gramado/base/GRAMADO.TXT     /mnt/gramadovhd


	# 6) from Portals to root.
	-sudo cp portals/services/gwssrv/bin/GWS.BIN     /mnt/gramadovhd
	-sudo cp portals/services/gwssrv/bin/GWSSRV.BIN  /mnt/gramadovhd
	-sudo cp portals/services/gnssrv/bin/GNS.BIN     /mnt/gramadovhd
	-sudo cp portals/services/gnssrv/bin/GNSSRV.BIN  /mnt/gramadovhd
	-sudo cp portals/shell/apps/bin/*.BIN            /mnt/gramadovhd
	#-sudo cp portals/shell/cmd/bin/*.BIN             /mnt/gramadovhd
	-sudo cp portals/shell/net/bin/*.BIN             /mnt/gramadovhd
	#-sudo cp portals/setup/bin/*.BIN                 /mnt/gramadovhd 
	-sudo cp portals/shell/cmd/bin/REBOOT.BIN         /mnt/gramadovhd
	-sudo cp portals/shell/cmd/bin/CAT.BIN            /mnt/gramadovhd
	# ...



#
# == "/BIN" ====================================================
#

# unix-like commands and stuff.
	-sudo cp portals/shell/cmd/bin/*.BIN   /mnt/gramadovhd/BIN

#
# == "/BOOT" ====================================================
#

	sudo cp gramado/boot/x86/bin/BM.BIN    /mnt/gramadovhd/BOOT
	sudo cp gramado/boot/x86/bin/BL.BIN    /mnt/gramadovhd/BOOT
	sudo cp gramado/kernel/KERNEL.BIN      /mnt/gramadovhd/BOOT
#	-sudo cp gramado/base/res/wall/ANIMAL.BMP  /mnt/gramadovhd/BOOT


#
# == "/ETC" =============================================
#

	# 
	-sudo cp docs/*.TXT    /mnt/gramadovhd/ETC
#	-sudo cp gramado/base/tests/*.CPP    /mnt/gramadovhd/ETC
#	-sudo cp gramado/base/tests/*.BAS    /mnt/gramadovhd/ETC
#	-sudo cp gramado/base/tests/*.ASM    /mnt/gramadovhd/ETC
#	-sudo cp gramado/base/res/wall/ANIMAL.BMP   /mnt/gramadovhd/ETC


#
# == "/PROGRAMS" ====================================================
#
	# The applications.
	-sudo cp portals/shell/apps/bin/*.BIN  /mnt/gramadovhd/PROGRAMS
	-sudo cp portals/shell/net/bin/*.BIN   /mnt/gramadovhd/PROGRAMS


#
# == "/PORTALS" ====================================================
#
	# bm, bl, kernel, init, gdeshell.
	sudo cp gramado/boot/x86/bin/BM.BIN     /mnt/gramadovhd/PORTALS
	sudo cp gramado/boot/x86/bin/BL.BIN     /mnt/gramadovhd/PORTALS
	sudo cp gramado/kernel/KERNEL.BIN       /mnt/gramadovhd/PORTALS
	sudo cp portals/init/INIT.BIN           /mnt/gramadovhd/PORTALS
	sudo cp portals/setup/bin/GDESHELL.BIN  /mnt/gramadovhd/PORTALS

	# Services
	-sudo cp portals/services/gwssrv/bin/GWSSRV.BIN  /mnt/gramadovhd/PORTALS
	-sudo cp portals/services/gnssrv/bin/GNSSRV.BIN  /mnt/gramadovhd/PORTALS



#
# == "/SBIN" ====================================================
#

# unix-like commands and stuff.
	-sudo cp portals/shell/cmd/bin/REBOOT.BIN   /mnt/gramadovhd/SBIN
	-sudo cp portals/setup/bin/REBOOT2.BIN      /mnt/gramadovhd/SBIN


#
# == "/USERS" ====================================================
#


#
# == "/TMP" =============================================
#

#	-sudo cp gramado/base/res/wall/ANIMAL.BMP   /mnt/gramadovhd/TMP




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
	-rm portals/shell/apps/bin/*.BIN
	-rm portals/shell/cmd/bin/*.BIN
	-rm portals/shell/net/bin/*.BIN


PHONY := clean-system-files
clean-system-files:
	@echo "==================="
	@echo "Cleaning all system binaries ..."

	# Gramado
	-rm -rf gramado/boot/x86/bin/*.BIN
	-rm -rf gramado/kernel/KERNEL.BIN

	# Init
	-rm -rf portals/init/*.BIN

	# Setup
	-rm -rf portals/setup/bin/*.BIN
	
	# Services
	-rm -rf portals/services/gnssrv/bin/*.BIN
	-rm -rf portals/services/gwssrv/bin/*.BIN
	# ...

	# Shell
	-rm -rf portals/shell/apps/bin/*.BIN
	-rm -rf portals/shell/cmd/bin/*.BIN
	-rm -rf portals/shell/net/bin/*.BIN
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

