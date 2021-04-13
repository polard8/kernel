# License: BSD License
# Product configuration
# See: 0config/version.h
PRODUCT_NAME  = Gramado
EDITION_NAME  = Land
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = 229
KERNELVERSION = $(VERSION_MAJOR)$(if $(VERSION_MINOR),.$(VERSION_MINOR)$(if $(VERSION_BUILD),.$(VERSION_BUILD)))

# Documentation.
# See: base/GRAMADO/DOCS/
# To see the targets execute "make help".

# That's our default target when none is given on the command line.
PHONY := _all
_all: all
	@echo "That's all!"

# =========================================
# Variables.

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
## Step0 build-landos-files - landos files.
## Step1 build-gws-files    - Gramado Window System files. 
## Step2 /mnt/gramadovhd    - Creating the directory to mount the VHD.
## Step3 vhd-mount          - Mounting the VHD.
## Step4 vhd-copy-files     - Copying files into the mounted VHD.
## Step5 vhd-unmount        - Unmounting the VHD.
## Step6 clean              - Deleting the object files. 


PHONY := all

# All the steps.
all:  \
build-landos-files \
build-gramado-files \
/mnt/gramadovhd    \
vhd-mount          \
vhd-copy-files     \
vhd-unmount        \
clean              \
clean-system-files \
generate    


# Giving permitions to run ./run hahaha
	chmod 755 ./run

# Product info:
	@echo "$(PRODUCT_NAME) $(KERNELVERSION)"
#	@echo "$(ARCH)"



#===================================================
#:::0
# ~ Step 0: landos files.

PHONY := build-landos-files
build-landos-files: \
/usr/local/gramado-build \
land-boot \
land-lib \
land-os \
land-cmd \
land-setup    



/usr/local/gramado-build:
	-sudo mkdir /usr/local/gramado-build

land-boot:
	#::boot
	@echo "=================== "
	@echo "Compiling landboot/ ... "
	# todo: Create a makefile inside  the boot/ folder.

	# virtual disks.
	# Generic name to avoid proprietary stuff.
	$(Q) $(NASM)  landboot/vd/fat/main.asm -I landboot/vd/fat/ -o GRAMADO.VHD 
#	$(Q) $(NASM)  landboot/vd/mbr/main.asm -I landboot/vd/mbr/ -o GRAMADO.VHD 
# ...

	$(Q) $(MAKE) -C landboot/bm1632/x86/ 
	$(Q) $(MAKE) -C landboot/bl32/x86/ 

	# O mbr só consegue ler o root dir para pegar o BM.BIN
	# See: stage1.asm
	# O BM.BIN só consegue ler o root dir pra pegar o BL.BIN
	# See: main.asm
	
	sudo cp landboot/bin/BM.BIN  base/
	sudo cp landboot/bin/BL.BIN  base/

land-lib:
	#::rtl
	@echo "==================="
	@echo "Compiling rtl ..."
	$(Q) $(MAKE) -C landlib/rtl/

	#::lib
	@echo "==================="
	@echo "Compiling  lib ..."
	$(Q) $(MAKE) -C landlib/lib/

land-os:

	# KERNEL.BIN  - Creating the kernel image.
	#::kernel
	# The boot loader will search on /GRAMADO/
	@echo "================================="
	@echo "(Step 1) Creating the kernel image ..."
	$(Q) $(MAKE) -C landos/kernel

	# O BL.BIN procura o kernel no diretorio GRAMADO/
	# See: fs/loader.c
	sudo cp landos/kernel/KERNEL.BIN  base/GRAMADO

	#::init
	@echo "==================="
	@echo "Compiling init ..."
	$(Q) $(MAKE) -C landos/init/

	# O kernel carrega o initi do diretorio raiz.
	# só consegue dessa forma por enquanto.
	# See: x86/x86init.c
	sudo cp landos/init/INIT.BIN  base/

#cmd - commands.
land-cmd:
	#::cmd
	$(Q) $(MAKE) -C landos/cmd/
	-sudo cp landos/cmd/bin/CAT.BIN        base/
#	-sudo cp landos/cmd/bin/FALSE.BIN      base/
	-sudo cp landos/cmd/bin/REBOOT.BIN     base/
	-sudo cp landos/cmd/bin/SHUTDOWN.BIN     base/
#	-sudo cp landos/cmd/bin/TRUE.BIN       base/

#	-sudo cp landos/cmd/bin/SHOWFUN.BIN    base/
#	-sudo cp landos/cmd/bin/UNAME.BIN      base/

land-setup:
	#::setup
	$(Q) $(MAKE) -C landos/setup/

	sudo cp landos/setup/bin/GDESHELL.BIN  base/
	sudo cp landos/setup/bin/GRAMCODE.BIN  base/
	sudo cp landos/setup/bin/SYSMON.BIN    base/

	sudo cp landos/setup/bin/LAUNCHER.BIN  base/

	#sudo cp landos/setup/bin/C4.BIN       base/
	#sudo cp landos/setup/bin/GRAMC.BIN    base/
	#sudo cp landos/setup/bin/GRAMC4.BIN   base/
	#sudo cp landos/setup/bin/GRAMCNF.BIN  base/

	sudo cp landos/setup/bin/GFE.BIN       base/
	#sudo cp landos/setup/bin/REBOOT2.BIN       base/
	#sudo cp landos/setup/bin/REBOOT3.BIN       base/

#===================================================
#:::1
# ~ Step 1 - Gramado Window System files.

PHONY := build-gramado-files 
build-gramado-files: \
gramado-ws \
gramado-services \
desert    

gramado-ws:

	#:: Gramado WS
	@echo "==================="
	@echo "Compiling Gramado WS and some clients"
	$(Q) $(MAKE) -C gramado/ws/

	# ws and some clients

# server and main client.
	-sudo cp gramado/ws/bin/GWS.BIN       base/ 
	-sudo cp gramado/ws/bin/GWSSRV.BIN    base/

# well teste clients
	-sudo cp gramado/ws/bin/EDITOR.BIN    base/
	-sudo cp gramado/ws/bin/GWM.BIN       base/
	-sudo cp gramado/ws/bin/TERMINAL.BIN  base/
	-sudo cp gramado/ws/bin/FILEMAN.BIN   base/

# extra clients
	-sudo cp gramado/ws/bin/*.BIN        base/PROGRAMS/


gramado-services:
	#::hard Services
	@echo "==================="
	@echo "Compiling hard..."
	$(Q) $(MAKE) -C gramado/services/gnssrv/ 
	# gns
	-sudo cp gramado/services/gnssrv/bin/GNS.BIN     base/
	-sudo cp gramado/services/gnssrv/bin/GNSSRV.BIN  base/

#========================================

desert:

	# todo aqui é frescura.
	# podemos colocar no subdiretorio gramado/

	# todo
	# Copy only the base of the desert inside the base of gramado.
	#-sudo cp ../desert/base/*.BIN              base/GRAMADO/
	#-sudo cp ../desert/base/*.TXT              base/GRAMADO/
	#-sudo cp ../desert/setup/medium/bin/*.BIN  base/GRAMADO/
	
# 
# more setups ? ...
#


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
# Copying the base folder into the mounted VHD.
vhd-copy-files:
	@echo "================================="
	@echo "(Step 4) Copying files into the mounted VHD ..."

	# Copy base
	# sends everything from base to root.
	sudo cp -r base/*  /mnt/gramadovhd



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
	-rm -rf landlib/rtl/obj/*.o
	-rm -rf landlib/lib/libgns/obj/*.o
	-rm -rf landlib/lib/libio01/obj/*.o

	
	@echo "Success?"
# clean ISO and VHD.
clean2:
	-rm *.ISO
	-rm *.VHD
# clean gramado
clean3:

	-rm landos/setup/bin/*.BIN
	-rm landos/cmd/bin/*.BIN

	-rm gramado/ws/bin/*.BIN

# clean base
clean4:
	-rm -rf base/*.BIN 
	-rm -rf base/GRAMADO/*.BIN 
	-rm -rf base/PROGRAMS/*.BIN 
	-rm -rf base/UBASE/BOOT/*.BIN 
	-rm -rf base/UBASE/BIN/*.BIN 
	-rm -rf base/UBASE/SBIN/*.BIN
 
# clean system files.
PHONY := clean-system-files
clean-system-files:
	@echo "==================="
	@echo "Cleaning all system binaries ..."

	-rm -rf landboot/bin/*.BIN
	-rm -rf landlib/fonts/bin/*.FON
	-rm -rf landos/kernel/KERNEL.BIN
	-rm -rf landos/init/*.BIN
	-rm -rf landos/cmd/bin/*.BIN
	-rm -rf landos/setup/bin/*.BIN

	-rm -rf gramado/ws/bin/*.BIN

	-rm -rf gramado/services/gnssrv/bin/*.BIN
# ...


## ==================================================================
## The extra stuff.
## 2) HDD support.
## 3) VM support.
## 4) Serial debug support.
## 5) Clean files support.
## 6) Usage support.


#
# == HDD ================================
#

# 32256 means the start of the partition in bytes.
# sector 63.
hdd-mount:
	-sudo umount /mnt/gramadohdd
	sudo mount -t vfat -o loop,offset=32256 /dev/sda /mnt/gramadohdd/
#	sudo mount -t vfat -o loop,offset=32256 /dev/sdb /mnt/gramadohdd/
	
hdd-unmount:
	-sudo umount /mnt/gramadohdd
	
hdd-copy-kernel:
	#sudo cp bin/boot/KERNEL.BIN /mnt/gramadohdd/BOOT 

# Danger!!
# This is gonna copy th image into the real HD.
# My host is running on sdb and i copy the image into sda.
# It is because the sda is in primary master IDE.
danger-hdd-clone-vhd:
	sudo dd if=./GRAMADO.VHD of=/dev/sda
#	sudo dd if=./GRAMADO.VHD of=/dev/sdb

# it will generate a file ...
# change the permission using cat MBR.VHD > MBR.BIN
#danger-copy-mbr:
#	sudo dd if=/dev/sda of=./MBR.VHD bs=512 count=1


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
	#-rm docs/KSH.TXT
	#readelf -S bin/boot/KERNEL.BIN > docs/KSH.TXT
	#cat docs/KSH.TXT


#
# gcc support
#

gcc-test:
#	chmod 755 ./scripts/gcccheck
#	./scripts/gcccheck


# product configuration
generate:
	# Create files.
	touch PRODUCT.TXT
	touch EDITION.TXT
	touch MAJOR.TXT
	touch MINOR.TXT
	touch BUILD.TXT
	touch VERSION.TXT
	# Save information.
	@echo $(PRODUCT_NAME)  > PRODUCT.TXT
	@echo $(PRODUCT_NAME) $(VERSION_MAJOR).$(VERSION_MINOR) $(EDITION_NAME)  > EDITION.TXT
	@echo $(VERSION_MAJOR) > MAJOR.TXT
	@echo $(VERSION_MINOR) > MINOR.TXT
	@echo $(VERSION_BUILD) > BUILD.TXT
	@echo $(KERNELVERSION) > VERSION.TXT
	# Install in the base folder.
	-mv PRODUCT.TXT  base/GRAMADO/
	-mv EDITION.TXT  base/GRAMADO/
	-mv MAJOR.TXT    base/GRAMADO/
	-mv MINOR.TXT    base/GRAMADO/
	-mv BUILD.TXT    base/GRAMADO/
	-mv VERSION.TXT  base/GRAMADO/

#
# == USAGE ========
#

help:
	@echo " [Usage]"
	@echo " $ make               - make all"
	@echo " $ make land-boot     - make landos bootloader"
	@echo " $ make land-lib      - make landos library"
	@echo " $ make land-os       - make landos kernel and init process"
	@echo " $ make land-cmd      - make gramado os commands"
	@echo " $ make land-setup    - make gramado os setup applications"
	@echo " $ make gramado-ws - make gramado os ws applications"
	@echo " $ make gramado-services  - make gramado os services applications"
	@echo " $ make clean         - Remove all .o files"
	@echo " $ make clean-all     - Remove all the object files"
	@echo " $ ./run              - Run the system on qemu"
	
