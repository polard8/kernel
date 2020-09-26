# License: BSD License
PRODUCT_NAME  = Gramado Operating System
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = 120
# See: config/version.h

# Documentation.
# See: docs/
# To see the targets execute "make help".

# That's our default target when none is given on the command line.
PHONY := _all
_all: all

	@echo "That's all!"

KERNELVERSION = $(VERSION_MAJOR)$(if $(VERSION_MINOR),.$(VERSION_MINOR)$(if $(VERSION_BUILD),.$(VERSION_BUILD)))

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
MAKE    = make
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

	@echo "$(PRODUCT_NAME) $(KERNELVERSION)"
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
	$(Q) $(MAKE) -C gramnt/boot/x86/bm/ 
	$(Q) $(MAKE) -C gramnt/boot/x86/bl/ 

build-portals:
	@echo "==================="
	@echo "Compiling rtl ..."
	$(Q) $(MAKE) -C rtl/

	@echo "==================="
	@echo "Compiling gramci lib ..."
	$(Q) $(MAKE) -C gramci/lib/

	@echo "==================="
	@echo "Compiling init ..."
	$(Q) $(MAKE) -C gramnt/init/

	@echo "==================="
	@echo "Compiling gramci stuff ..."
	$(Q) $(MAKE) -C gramci/setup/
	$(Q) $(MAKE) -C gramci/services/gnssrv/ 
	$(Q) $(MAKE) -C gramci/services/gwssrv/
	$(Q) $(MAKE) -C gramci/shell/apps/
	$(Q) $(MAKE) -C gramci/shell/cmd/
	$(Q) $(MAKE) -C gramci/shell/net/

## Step1 KERNEL.BIN         - Creating the kernel image.
KERNEL.BIN: 
	@echo "================================="
	@echo "(Step 1) Creating the kernel image ..."

	$(Q) $(MAKE) -C gramnt/kernel


## Step3 /mnt/gramadovhd    - Creating the directory to mount the VHD.
/mnt/gramadovhd:
	@echo "================================="
	@echo "(Step 3) Creating the directory to mount the VHD ..."

	sudo mkdir /mnt/gramadovhd


## Step4 vhd-create         - Creating a VHD in Assembly language.
vhd-create:
	@echo "================================="
	@echo "(Step 4) Creating a VHD in Assembly language ..."

	$(NASM) gramnt/boot/x86/vhd/main.asm -I gramnt/boot/x86/vhd/ -o GRAMADO.VHD   


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


	# ====================================================
	# 1) First of all
	# bm, bl, kernel, init, gdeshell.
	sudo cp gramnt/boot/x86/bin/BM.BIN  base/
	sudo cp gramnt/boot/x86/bin/BM.BIN  base/BOOT
	sudo cp gramnt/boot/x86/bin/BM.BIN  base/PORTALS

	sudo cp gramnt/boot/x86/bin/BL.BIN  base/
	sudo cp gramnt/boot/x86/bin/BL.BIN  base/BOOT
	sudo cp gramnt/boot/x86/bin/BL.BIN  base/PORTALS

	sudo cp gramnt/kernel/KERNEL.BIN  base/
	sudo cp gramnt/kernel/KERNEL.BIN  base/BOOT
	sudo cp gramnt/kernel/KERNEL.BIN  base/PORTALS

	sudo cp gramnt/init/INIT.BIN  base/
	sudo cp gramnt/init/INIT.BIN  base/PORTALS

	sudo cp gramci/setup/bin/GDESHELL.BIN  base/
	sudo cp gramci/setup/bin/GDESHELL.BIN  base/PORTALS
	# ====================================================


	# setup
	#-sudo cp gramci/setup/bin/*.BIN    base/

	# sysmon
	sudo cp gramci/setup/bin/SYSMON.BIN base/


	# apps
#	-sudo cp gramci/shell/apps/bin/*.BIN  base/
#	-sudo cp gramci/shell/apps/bin/*.BIN  base/PROGRAMS
	-sudo cp gramci/shell/apps/bin/GWM.BIN     base/
	-sudo cp gramci/shell/apps/bin/EDITOR.BIN  base/
	-sudo cp gramci/shell/apps/bin/LAUNCH1.BIN  base/
	# ...


	# cmd
	#-sudo cp gramci/shell/cmd/bin/*.BIN  base/
	#-sudo cp gramci/shell/cmd/bin/*.BIN  base/BIN
#	-sudo cp gramci/shell/cmd/bin/REBOOT.BIN     base/
	-sudo cp gramci/shell/cmd/bin/CAT.BIN        base/
#	-sudo cp gramci/shell/cmd/bin/TRUE.BIN       base/
#	-sudo cp gramci/shell/cmd/bin/FALSE.BIN      base/
	# ...


	# net
	-sudo cp gramci/shell/net/bin/*.BIN  base/
	-sudo cp gramci/shell/net/bin/*.BIN  base/PROGRAMS

	# gws
	-sudo cp gramci/services/gwssrv/bin/GWS.BIN     base/ 
	-sudo cp gramci/services/gwssrv/bin/GWSSRV.BIN  base/
	-sudo cp gramci/services/gwssrv/bin/GWSSRV.BIN  base/PORTALS

	# gns
	-sudo cp gramci/services/gnssrv/bin/GNS.BIN     base/
	-sudo cp gramci/services/gnssrv/bin/GNSSRV.BIN  base/
	-sudo cp gramci/services/gnssrv/bin/GNSSRV.BIN  base/PORTALS


	#
	# Copy base!
	#

	# sends everything from base to root.
	sudo cp -r base/* /mnt/gramadovhd



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
	-rm -rf rtl/obj/*.o
	
	@echo "Success?"

clean2:
	-rm *.ISO
	-rm *.VHD

clean3:
	-rm gramci/shell/apps/bin/*.BIN
	-rm gramci/shell/cmd/bin/*.BIN
	-rm gramci/shell/net/bin/*.BIN

#Clean base
clean4:
	-rm -rf base/*.BIN 
	-rm -rf base/BOOT/*.BIN 
	-rm -rf base/BIN/*.BIN 
	-rm -rf base/SBIN/*.BIN 
	-rm -rf base/PROGRAMS/*.BIN 
	-rm -rf base/PORTALS/*.BIN 



PHONY := clean-system-files
clean-system-files:
	@echo "==================="
	@echo "Cleaning all system binaries ..."


	# Gramado
	-rm -rf gramnt/boot/x86/bin/*.BIN
	-rm -rf gramnt/kernel/KERNEL.BIN

	# Init
	-rm -rf gramnt/init/*.BIN

	# fonts
	-rm -rf gramci/fonts/bin/*.FON

	# Setup
	-rm -rf gramci/setup/bin/*.BIN
	
	# Services
	-rm -rf gramci/services/gnssrv/bin/*.BIN
	-rm -rf gramci/services/gwssrv/bin/*.BIN
	# ...

	# Shell
	-rm -rf gramci/shell/apps/bin/*.BIN
	-rm -rf gramci/shell/cmd/bin/*.BIN
	-rm -rf gramci/shell/net/bin/*.BIN
# ...


clean-all: clean clean2 clean3 clean4 clean-system-files  

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
	$(NASM) gramnt/kernel/boot/x86/iso/stage1/stage1.asm -f bin -o stage1.bin
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

