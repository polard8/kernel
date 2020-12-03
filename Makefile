# License: BSD License
PRODUCT_NAME  = Gramado Operating System
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = 174
# See: config/version.h

# Documentation.
# See: docs/
# To see the targets execute "make help".

# That's our default target when none is given on the command line.
PHONY := _all
_all: all
	@echo "That's all!"

# ==========================================
# Variables.
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

## ===============================================================
## Step0 build-system-files - Libraries and apps.
## Step1 build-applications - setupx files. 
## Step2 /mnt/gramadovhd    - Creating the directory to mount the VHD.
## Step3 vhd-mount          - Mounting the VHD.
## Step4 vhd-copy-files     - Copying files into the mounted VHD.
## Step5 vhd-unmount        - Unmounting the VHD.
## Step6 clean              - Deleting the object files. 


PHONY := all

# All the steps.
all:  \
build-system-files \
build-applications \
/mnt/gramadovhd  \
vhd-mount \
vhd-copy-files \
vhd-unmount \
clean \
clean-system-files

# Giving permitions to run ./run hahaha
	chmod 755 ./run

# Product info:
	@echo "$(PRODUCT_NAME) $(KERNELVERSION)"
#	@echo "$(ARCH)"


#===================================================
#:::0
# ~ Step 0: Building system files.
PHONY := build-system-files
build-system-files: \
/usr/local/gramado-build \
ge-boot \
ge-kernel \
ge-rtl \
ge-lib \
ge-init \
ge-aurora \
ge-services    

/usr/local/gramado-build:
	-sudo mkdir /usr/local/gramado-build

ge-boot:
	#::boot
	@echo "=================== "
	@echo "Compiling boot/ ... "
	$(Q) $(NASM)    ge/boot/x86/0vhd/main.asm -I ge/boot/x86/0vhd/ -o GRAMADO.VHD   
	$(Q) $(MAKE) -C ge/boot/x86/1bm/ 
	$(Q) $(MAKE) -C ge/boot/x86/2bl/ 

# KERNEL.BIN  - Creating the kernel image.
ge-kernel:
	#::kernel
	@echo "================================="
	@echo "(Step 1) Creating the kernel image ..."
	$(Q) $(MAKE) -C ge/kernel
ge-rtl:
	#::rtl
	@echo "==================="
	@echo "Compiling rtl ..."
	$(Q) $(MAKE) -C ge/rtl/
ge-lib:
	#::lib
	@echo "==================="
	@echo "Compiling  lib ..."
	$(Q) $(MAKE) -C ge/lib/
ge-init:
	#::init
	@echo "==================="
	@echo "Compiling init ..."
	$(Q) $(MAKE) -C ge/init/
ge-aurora:
	#::aurora Aurora Window Server.
	@echo "==================="
	@echo "Compiling Aurora window server ..."
	$(Q) $(MAKE) -C ge/aurora/
ge-services:
	#::services Services
	@echo "==================="
	@echo "Compiling services..."
	$(Q) $(MAKE) -C ge/services/gnssrv/ 



#===================================================
#:::1
# ~ Step 1 Setup directories.
PHONY := build-applications 
build-applications: \
setup0-grass \
setup1-apps \
setup1-net \
setup2-cmd    

setup0-grass:
	#::grass
	$(Q) $(MAKE) -C setup0/grass/
setup1-apps:
	#::apps
	$(Q) $(MAKE) -C setup1/apps/
setup1-net:
	#::net
	$(Q) $(MAKE) -C setup1/net/
setup2-cmd:
	#::cmd
	$(Q) $(MAKE) -C setup2/cmd/


#===================================================
#:::2
# Step 2: /mnt/gramadovhd  - Creating the directory to mount the VHD.
/mnt/gramadovhd:
	@echo "================================="
	@echo "(Step 2) Creating the directory to mount the VHD ..."
	sudo mkdir /mnt/gramadovhd


#===================================================
#:::3
# ~ Step 3: vhd-mount  - Mounting the VHD.
vhd-mount:
	@echo "================================="
	@echo "(Step 3) Mounting the VHD ..."
	-sudo umount /mnt/gramadovhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadovhd/

#===================================================
#:::4
# ~ Step 4 vhd-copy-files  - Copying files into the mounted VHD.
vhd-copy-files:
	@echo "================================="
	@echo "(Step 4) Copying files into the mounted VHD ..."

	#
	# == ge ======================================
	#

	# ====================================================
	# 1) First of all
	# bm, bl, kernel, init, gdeshell.
	# Only on ge/

	sudo cp ge/boot/x86/bin/BM.BIN  base/
	sudo cp ge/boot/x86/bin/BM.BIN  base/BOOT
	sudo cp ge/boot/x86/bin/BM.BIN  base/PORTALS

	sudo cp ge/boot/x86/bin/BL.BIN  base/
	sudo cp ge/boot/x86/bin/BL.BIN  base/BOOT
	sudo cp ge/boot/x86/bin/BL.BIN  base/PORTALS

	sudo cp ge/kernel/KERNEL.BIN  base/
	sudo cp ge/kernel/KERNEL.BIN  base/BOOT
	sudo cp ge/kernel/KERNEL.BIN  base/PORTALS

	sudo cp ge/init/INIT.BIN  base/
	sudo cp ge/init/INIT.BIN  base/PORTALS

	sudo cp setup0/grass/bin/GDESHELL.BIN  base/
	sudo cp setup0/grass/bin/GDESHELL.BIN  base/PORTALS

	# setup
	#-sudo cp setup0/grass/bin/*.BIN    base/

	sudo cp setup0/grass/bin/LAUNCHER.BIN  base/
	sudo cp setup0/grass/bin/GRAMCODE.BIN  base/
	sudo cp setup0/grass/bin/GFE.BIN       base/
	sudo cp setup0/grass/bin/SYSMON.BIN    base/
	#sudo cp setup0/grass/bin/NORATERM.BIN  base/

	#tests interpreters.
	#sudo cp setup0/grass/bin/C4.BIN       base/
	#sudo cp setup0/grass/bin/GRAMC.BIN    base/
	sudo cp setup0/grass/bin/GRAMC4.BIN   base/
	#sudo cp setup0/grass/bin/GRAMCNF.BIN  base/
	
	# ====================================================

	# apps
#	-sudo cp setup1/apps/bin/*.BIN  base/
#	-sudo cp setup1/apps/bin/*.BIN  base/PROGRAMS
	#-sudo cp setup1/apps/bin/GWM.BIN     base/
	-sudo cp setup1/apps/bin/EDITOR.BIN  base/
	-sudo cp setup1/apps/bin/FILEMAN.BIN  base/
	-sudo cp setup1/apps/bin/LAUNCH1.BIN  base/
	#-sudo cp setup1/apps/bin/TERMINAL.BIN  base/
	
	-sudo cp setup1/net/bin/*.BIN  base/PROGRAMS

	# net
	-sudo cp setup1/net/bin/*.BIN  base/

	# ...

	# cmd
	#-sudo cp setup2/cmd/bin/*.BIN  base/
	#-sudo cp setup2/cmd/bin/*.BIN  base/BIN
	-sudo cp setup2/cmd/bin/REBOOT.BIN     base/
	-sudo cp setup2/cmd/bin/CAT.BIN        base/
	-sudo cp setup2/cmd/bin/FASM.BIN       base/
#	-sudo cp setup2/cmd/bin/TRUE.BIN       base/
#	-sudo cp setup2/cmd/bin/FALSE.BIN      base/
#	-sudo cp setup2/cmd/bin/SHOWFUN.BIN       base/
	# ...

	#-sudo cp setup2/cmd/bin/SHELL.BIN       base/
	
	# gws
	-sudo cp ge/aurora/bin/GWS.BIN     base/ 
	-sudo cp ge/aurora/bin/GWSSRV.BIN  base/
	-sudo cp ge/aurora/bin/GWSSRV.BIN  base/PORTALS

	# gns
	-sudo cp ge/services/gnssrv/bin/GNS.BIN     base/
	-sudo cp ge/services/gnssrv/bin/GNSSRV.BIN  base/
	-sudo cp ge/services/gnssrv/bin/GNSSRV.BIN  base/PORTALS


	# Copy base
	# sends everything from base to root.
	sudo cp -r base/* /mnt/gramadovhd


#===================================================
#:::5
# ~ Step 5 vhd-unmount  - Unmounting the VHD.
vhd-unmount:
	@echo "================================="
	@echo "(Step 5) Unmounting the VHD ..."
	sudo umount /mnt/gramadovhd


#
# == clean ====================================
#

clean-all: \
clean clean2 clean3 clean4 clean-system-files  
	@echo "==================="
	@echo "ok ?"

#===================================================
#:::6
# ~ Step 6 clean  - Deleting the object files.           
clean:
	@echo "================================="
	@echo "(Step 6) Deleting the object files ..."
	-rm *.o
	-rm -rf ge/rtl/obj/*.o
	@echo "Success?"
# clean ISO and VHD.
clean2:
	-rm *.ISO
	-rm *.VHD
# clean setup
clean3:
	-rm setup0/grass/bin/*.BIN
	-rm setup1/apps/bin/*.BIN
	-rm setup1/net/bin/*.BIN
	-rm setup2/cmd/bin/*.BIN
# clean base
clean4:
	-rm -rf base/*.BIN 
	-rm -rf base/BOOT/*.BIN 
	-rm -rf base/BIN/*.BIN 
	-rm -rf base/SBIN/*.BIN 
	-rm -rf base/PROGRAMS/*.BIN 
	-rm -rf base/PORTALS/*.BIN 
# clean system files.
PHONY := clean-system-files
clean-system-files:
	@echo "==================="
	@echo "Cleaning all system binaries ..."
	# Gramado
	-rm -rf ge/boot/x86/bin/*.BIN
	-rm -rf ge/kernel/KERNEL.BIN
	# Init
	-rm -rf ge/init/*.BIN
	# fonts
	-rm -rf ge/fonts/bin/*.FON
	# aurora
	-rm -rf ge/aurora/bin/*.BIN
	# Services
	-rm -rf ge/services/gnssrv/bin/*.BIN
	# ...
	# Setup
	-rm -rf setup0/grass/bin/*.BIN
	-rm -rf setup1/apps/bin/*.BIN
	-rm -rf setup1/net/bin/*.BIN
	-rm -rf setup2/cmd/bin/*.BIN
# ...


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
	$(NASM) ge/kernel/boot/x86/iso/stage1/stage1.asm -f bin -o stage1.bin
	cp stage1.bin bin/boot/gramado/
	rm stage1.bin

	#.ISO
#	mkisofs -R -J -c boot/gramado/boot.catalog -b boot/gramado/stage1.bin -no-emul-boot -boot-load-size 4 -boot-info-table -o GRAMADO.ISO bin
	
	@echo "iso Success?"	



#
# == HDD ================================
#


hdd-mount:
	-sudo umount /mnt/gramadohdd
	sudo mount -t vfat -o loop,offset=32256 /dev/sda /mnt/gramadohdd/
#	sudo mount -t vfat -o loop,offset=32256 /dev/sdb /mnt/gramadohdd/
	
hdd-unmount:
	-sudo umount /mnt/gramadohdd
	
hdd-copy-kernel:
	sudo cp bin/boot/KERNEL.BIN /mnt/gramadohdd/BOOT 

# Danger!!
# This is gonna copy th image into the real HD.
# My host is running on sdb and i copy the image into sda.
# It is because the sda is in primary master IDE.
danger-hdd-clone-vhd:
	sudo dd if=./GRAMADO.VHD of=/dev/sda
#	sudo dd if=./GRAMADO.VHD of=/dev/sdb


#
# == VM ====================
#

# Oracle Virtual Box 
# This target runs the image in the virtual box emulator.
# I use a virtual machine called "Gramado"
oracle-virtual-box-test:
	VBoxManage startvm "Gramado"


# qemu 
# This target runs the image in the qemu emulator.
# You also van use a script called "./run". 
qemu-test:
	qemu-system-x86_64 -hda GRAMADO.VHD -m 512 -serial stdio 
#	qemu-system-x86_64 -hda GRAMADO.VHD -m 128 -device e1000 -show-cursor -serial stdio -device e1000

# ??
test-sda:
	sudo qemu-system-i386 -m 512 -drive file=/dev/sda,format=raw

# ??
test-sdb:
	sudo qemu-system-i386 -m 512 -drive file=/dev/sdb,format=raw


#install-kvm-qemu:
#	sudo pacman -S virt-manager qemu vde2 ebtables dnsmasq bridge-utils openbsd-netcat



#
# == SERIAL DEBUG ===============================
#

# It shows the serial debug output file.
# fixme.
serial-debug:
#	cat ./docs/sdebug.txt


#
# Image support.
#

kernel-version:
	@echo $(KERNELVERSION)

image-name:
	@echo $(KBUILD_IMAGE)

kernel-file-header:
#	-rm docs/KFH.TXT
#	readelf -h bin/boot/KERNEL.BIN > docs/KFH.TXT
#	cat docs/KFH.TXT

kernel-program-headers:
#	-rm docs/KPH.TXT
#	readelf -l bin/boot/KERNEL.BIN > docs/KPH.TXT
#	cat docs/KPH.TXT

kernel-section-headers:
	-rm docs/KSH.TXT
	readelf -S bin/boot/KERNEL.BIN > docs/KSH.TXT
	cat docs/KSH.TXT
	


#
# gcc support
#

gcc-test:
#	chmod 755 ./scripts/gcccheck
#	./scripts/gcccheck


#
# == USAGE ========
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

