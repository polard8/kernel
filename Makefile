# License: BSD License
# Product configuration
# See: 0config/version.h

PRODUCT_NAME  = Gramado
EDITION_NAME  = ?todo

VERSION_MAJOR = 1
VERSION_MINOR = 3
VERSION_BUILD = 281

KERNELVERSION = $(VERSION_MAJOR)$(if $(VERSION_MINOR),.$(VERSION_MINOR)$(if $(VERSION_BUILD),.$(VERSION_BUILD)))

# Make variables (CC, etc...)
AS      = as
LD      = ld
CC      = gcc
AR      = ar
MAKE    = make
NASM    = nasm
PYTHON  = python
PYTHON2 = python2
PYTHON3 = python3

#
# Config
#

# use verbose
ifndef CONFIG_USE_VERBOSE
    CONFIG_USE_VERBOSE = 1
endif

# ========

# verbose
ifeq ($(CONFIG_USE_VERBOSE),1)
    Q =
else
    Q = @
endif



# ===== Start ====

PHONY := all

# build: User command.
all:  \
build-gramado-os \
/mnt/gramadoxvhd \
vhd-mount \
vhd-copy-files \
vhd-unmount \
clean    


# Giving permitions to run ./run
	chmod 755 ./run

# Product info:
	@echo "$(PRODUCT_NAME) $(EDITION_NAME) $(KERNELVERSION)"
#	@echo "$(ARCH)"


#----------
# build: Developer comand 1.
# install
# Build the images and put them all into base/disk/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-os  


#----------
# build: Developer comand 2.
# image
# Copy all the files from base/disk/ to the VHD.
PHONY := image
image: do_image
do_image: \
/mnt/gramadoxvhd    \
vhd-mount          \
vhd-copy-files     \
vhd-unmount        \

#----------
# build: Developer comand 3.
# run
# run the system on qemu.
PHONY := run
run: do_run
do_run:
	sh ./run


#===================================================
#::0
# ~ Step 0: gramado files.

PHONY := build-gramado-os  
build-gramado-os: \
base-tier \
communication-tier \
presentation-tier    


#1
base-tier:
	@echo ":: Building VHD, bootloaders and kernel image."

# options: 
# main.asm and main2.asm
# O mbr só consegue ler o root dir para pegar o BM.BIN
# See: stage1.asm
# O BM.BIN só consegue ler o root dir pra pegar o BL.BIN
# See: main.asm
# the kernel image
# O BL.BIN procura o kernel no diretorio GRAMADO/
# See: fs/loader.c


# Create the VHD.
	$(Q) $(NASM) base/boot/vd/fat/main.asm \
	-I base/boot/vd/fat/ \
	-o GRAMADO.VHD 
# Build BM.BIN and BL.BIN.
	$(Q) $(MAKE) -C base/boot/x86/bm/ 
	$(Q) $(MAKE) -C base/boot/x86/bl/ 
# Copy to the target folder.
	sudo cp base/boot/x86/bin/BM.BIN  base/disk/
	sudo cp base/boot/x86/bin/BL.BIN  base/disk/
# Build kernel image.
	$(Q) $(MAKE) -C base/new/
# Copy to the target folder.
	sudo cp base/new/KERNEL.BIN  base/disk/GRAMADO

#2
communication-tier:
	@echo ":: Building libraries and network server."

# Build libraries.
# Don't copy.
	$(Q) $(MAKE) -C com/lib/rtl/
	$(Q) $(MAKE) -C com/lib/
# Build network server.
	$(Q) $(MAKE) -C com/gns/ 
# Copy to the target folder.
	-sudo cp com/gns/bin/GNSSRV.BIN  base/disk/
	-sudo cp com/gns/bin/GNS.BIN     base/disk/

#========================================

#3
# The presentation tier.
# Gramado Window System files.
presentation-tier:
	@echo ":: Building Window server, clients and userland."

# Building window server and clients.
	$(Q) $(MAKE) -C gramado/
# Copy to the target folder.
	-sudo cp gramado/bin/GWSSRV.BIN    base/disk/
	-sudo cp gramado/bin/GWS.BIN       base/disk/ 
	-sudo cp gramado/bin/CMDLINE.BIN   base/disk/
	-sudo cp gramado/bin/GWM.BIN       base/disk/
	-sudo cp gramado/bin/LOGON.BIN     base/disk/
	-sudo cp gramado/bin/EDITOR.BIN    base/disk/
	-sudo cp gramado/bin/TERMINAL.BIN  base/disk/
	-sudo cp gramado/bin/FILEMAN.BIN   base/disk/
	-sudo cp gramado/bin/BROWSER.BIN   base/disk/
# Building userland commands.
	$(Q) $(MAKE) -C gramado/userland/
# Copy to the target folder.
	-sudo cp gramado/userland/bin/SHUTDOWN.BIN  base/disk/
	-sudo cp gramado/userland/bin/REBOOT.BIN    base/disk/
	-sudo cp gramado/userland/bin/SHELL.BIN     base/disk/
	-sudo cp gramado/userland/bin/CAT.BIN       base/disk/
#...

# Suspended
# Copy the clients in another folder.
#	-sudo cp gramado/bin/*.BIN    base/disk/PROGRAMS/

# Install BMPs
#	sudo cp gramado/extra/themes/presence/*.BMP  base/disk/
	sudo cp gramado/extra/themes/field/*.BMP  base/disk/
#...

#===================================================
#::2
# Step 2: /mnt/gramadoxvhd  - Creating the directory to mount the VHD.
/mnt/gramadoxvhd:
	@echo "========================="
	@echo "Build: Creating the directory to mount the VHD ..."
	sudo mkdir /mnt/gramadoxvhd

#===================================================
#::3
# ~ Step 3: vhd-mount - Mounting the VHD.
vhd-mount:
	@echo "=========================="
	@echo "Build: Mounting the VHD ..."
	-sudo umount /mnt/gramadoxvhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadoxvhd/

#===================================================
#::4
# ~ Step 4 vhd-copy-files - Copying files into the mounted VHD.
# Copying the base/disk/ folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "Build: Copying files into the mounted VHD ..."

	# Copy base/disk/
	# sends everything from disk/ to root.
	sudo cp -r base/disk/*  /mnt/gramadoxvhd

#===================================================
#:::5
# ~ Step 5 vhd-unmount  - Unmounting the VHD.
vhd-unmount:
	@echo "======================"
	@echo "Build: Unmounting the VHD ..."
	sudo umount /mnt/gramadoxvhd


# Danger!
# This is gonna copy th image into the real HD.
# My host is running on sdb and i copy the image into sda.
# It is because the sda is in primary master IDE.
danger-hdd-clone-vhd:
	sudo dd if=./GRAMADO.VHD of=/dev/sda
#	sudo dd if=./GRAMADO.VHD of=/dev/sdb


#
# == clean ====================================
#

clean-all: \
clean clean1 clean2 clean3    

	-rm *.VHD
	-rm *.ISO

	@echo "==================="
	@echo "ok ?"
clean:
	@echo "==================="
	@echo "Build: Deleting the object files ..."

	-rm *.o

	-rm -rf com/lib/rtl/obj/*.o
	-rm -rf com/lib/libgns/obj/*.o
	-rm -rf com/lib/libio01/obj/*.o

	-rm -rf gramado/final/server/*.o
	-rm -rf gramado/final/client/*.o

	@echo "Success?"

# base-tier
clean1:
# Clear boot images
	-rm -rf base/boot/x86/bin/*.BIN

# Clear newos kernel image
	-rm -rf base/new/KERNEL.BIN

# Clear root dir
	-rm -rf base/disk/*.BIN 
	-rm -rf base/disk/*.BMP
# Clear system folder 
	-rm -rf base/disk/GRAMADO/*.BIN 
# Clear applications folder
	-rm -rf base/disk/PROGRAMS/*.BIN 
# Clear unix-like stuff
	-rm -rf base/disk/UBASE/BOOT/*.BIN 
	-rm -rf base/disk/UBASE/BIN/*.BIN 
	-rm -rf base/disk/UBASE/SBIN/*.BIN

# communication-tier
clean2:

# Clear libraries folder
	-rm -rf com/lib/fonts/bin/*.FON

# Clear commands folder
	-rm -rf com/cmd/bin/*.BIN
# Clear gns service stuff
	-rm -rf com/gns/bin/*.BIN

# todo: 
# We need clean up all the object files
# for the applications.
clean3:

# Clear system folder
	-rm -rf gramado/bin/*.BIN

	-rm gramado/bin/*.BIN
	-rm gramado/userland/bin/*.BIN

usage:
	@echo "Building everything:"
	@echo "make all"
	@echo "Clear the mess to restart:"
	@echo "make clean-all"
	@echo "Testing on qemu:"
	@echo "./run"

# End

