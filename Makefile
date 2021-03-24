# License: BSD License
# Product configuration
# See: 0config/version.h
PRODUCT_NAME  = Gramado
EDITION_NAME  = Land
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = 226
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
build-gws-files    \
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
land-os    


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

	#::libcore
	@echo "==================="
	@echo "Compiling libcore ..."
	$(Q) $(MAKE) -C landlib/libcore/

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


#===================================================
#:::1
# ~ Step 1 - Gramado Window System files.

PHONY := build-gws-files 
build-gws-files: \
gramado-cmd \
gramado-setup \
gramado-core \
gramado-shell \
gramado-edge \
desert    

# order
# cmd > setup > core > edge > desert

#cmd - commands.
gramado-cmd:
	#::cmd
	$(Q) $(MAKE) -C gramado/cmd/
	-sudo cp gramado/cmd/bin/CAT.BIN        base/
#	-sudo cp gramado/cmd/bin/FALSE.BIN      base/
	-sudo cp gramado/cmd/bin/REBOOT.BIN     base/
	-sudo cp gramado/cmd/bin/SHUTDOWN.BIN     base/
#	-sudo cp gramado/cmd/bin/TRUE.BIN       base/

#	-sudo cp gramado/cmd/bin/SHOWFUN.BIN    base/
#	-sudo cp gramado/cmd/bin/UNAME.BIN      base/

gramado-setup:
	#::setup
	$(Q) $(MAKE) -C gramado/setup/

	sudo cp gramado/setup/bin/GDESHELL.BIN  base/
	sudo cp gramado/setup/bin/GRAMCODE.BIN  base/
	sudo cp gramado/setup/bin/SYSMON.BIN    base/

	sudo cp gramado/setup/bin/LAUNCHER.BIN  base/

	#sudo cp gramado/setup/bin/C4.BIN       base/
	#sudo cp gramado/setup/bin/GRAMC.BIN    base/
	#sudo cp gramado/setup/bin/GRAMC4.BIN   base/
	#sudo cp gramado/setup/bin/GRAMCNF.BIN  base/

	#sudo cp gramado/setup/bin/GFE.BIN       base/
	#sudo cp gramado/setup/bin/REBOOT2.BIN       base/
	#sudo cp gramado/setup/bin/REBOOT3.BIN       base/
	
gramado-core:
	#::hard Services
	@echo "==================="
	@echo "Compiling hard..."
	$(Q) $(MAKE) -C gramado/core/gnssrv/ 
	# gns
	-sudo cp gramado/core/gnssrv/bin/GNS.BIN     base/
	-sudo cp gramado/core/gnssrv/bin/GNSSRV.BIN  base/


	#::aurora Aurora Window Server.
	@echo "==================="
	@echo "Compiling Aurora window server ..."
	$(Q) $(MAKE) -C gramado/core/aurora/
	# gws
	-sudo cp gramado/core/aurora/bin/GWS.BIN     base/ 
	-sudo cp gramado/core/aurora/bin/GWSSRV.BIN  base/


gramado-shell:

	#::apps
	$(Q) $(MAKE) -C gramado/shell/apps/
	-sudo cp gramado/shell/apps/bin/EDITOR.BIN     base/
	-sudo cp gramado/shell/apps/bin/FILEMAN.BIN    base/
	-sudo cp gramado/shell/apps/bin/GWM.BIN        base/
#	-sudo cp gramado/shell/apps/bin/S2.BIN         base/
#	-sudo cp gramado/shell/apps/bin/S3.BIN         base/
	-sudo cp gramado/shell/apps/bin/TERMINAL.BIN   base/

	#::ui
	$(Q) $(MAKE) -C gramado/shell/ui/
	-sudo cp gramado/shell/ui/bin/LAUNCH1.BIN      base/

gramado-edge:

	# todo aqui é frescura.
	# podemos colocar no subdiretorio gramado/
	# com isso vamos iniciar a aventura de pegar as coisas em subdiretórios.

	#::net
	$(Q) $(MAKE) -C gramado/edge/net/
	-sudo cp gramado/edge/net/bin/*.BIN      base/PROGRAMS/

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
	-rm -rf landlib/libcore/obj/*.o
	-rm -rf landlib/lib/libgns/obj/*.o
	-rm -rf landlib/lib/libgws/obj/*.o
	-rm -rf landlib/lib/libio01/obj/*.o
	@echo "Success?"
# clean ISO and VHD.
clean2:
	-rm *.ISO
	-rm *.VHD
# clean gramado
clean3:
	-rm gramado/cmd/bin/*.BIN
	-rm gramado/setup/bin/*.BIN
	-rm gramado/shell/apps/bin/*.BIN
	-rm gramado/shell/ui/bin/*.BIN
	-rm gramado/edge/net/bin/*.BIN

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

	-rm -rf gramado/cmd/bin/*.BIN
	-rm -rf gramado/setup/bin/*.BIN
	-rm -rf gramado/core/aurora/bin/*.BIN
	-rm -rf gramado/core/gnssrv/bin/*.BIN
	-rm -rf gramado/shell/apps/bin/*.BIN
	-rm -rf gramado/shell/ui/bin/*.BIN
	-rm -rf gramado/edge/net/bin/*.BIN
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
	@echo " $ make gramado-core  - make gramado os core applications"
	@echo " $ make gramado-cmd   - make gramado os commands"
	@echo " $ make gramado-setup - make gramado os setup applications"
	@echo " $ make gramado-shell - make gramado os shell applications"
	@echo " $ make gramado-edge  - make gramado os edge applications"
	@echo " $ make clean         - Remove all .o files"
	@echo " $ make clean-all     - Remove all the object files"
	@echo " $ ./run              - Run the system on qemu"
	
