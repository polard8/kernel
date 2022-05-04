# License: BSD License
# Product configuration
# See: 0config/version.h

PRODUCT_NAME  = Gramado
EDITION_NAME  = Angels

VERSION_MAJOR = 1
VERSION_MINOR = 4
VERSION_BUILD = 287

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
# Build the images and put them all into basetier/disk/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-os  


#----------
# build: Developer comand 2.
# image
# Copy all the files from basetier/disk/ to the VHD.
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
	$(Q) $(NASM) basetier/boot/vd/fat/main.asm \
	-I basetier/boot/vd/fat/ \
	-o GRAMADO.VHD 


# ::Build BM.BIN.
	$(Q) $(MAKE) -C basetier/boot/x86/bm/ 
# Copy to the target folder.
	sudo cp basetier/boot/x86/bin/BM.BIN  basetier/disk/

# ::Build BL.BIN.
	$(Q) $(MAKE) -C basetier/boot/x86/bl/ 
# Copy to the target folder.
	sudo cp basetier/boot/x86/bin/BL.BIN  basetier/disk/

# ::Build kernel image.
	$(Q) $(MAKE) -C basetier/new/
# Copy to the target folder.
	sudo cp basetier/new/KERNEL.BIN  basetier/disk/GRAMADO

# Install BMPs
	sudo cp basetier/data/themes/field/*.BMP  basetier/disk/
#...


#2
communication-tier:
	@echo ":: Building libraries and network server."

# ::Build libraries.
	$(Q) $(MAKE) -C comtier/lib/
# Don't copy to the disk.

# ::Build network server.
	$(Q) $(MAKE) -C comtier/gns/ 
# Copy to the target folder.
	-sudo cp comtier/gns/bin/GNSSRV.BIN  basetier/disk/
	-sudo cp comtier/gns/bin/GNS.BIN     basetier/disk/

#========================================

#3
# The presentation tier.
# Gramado Window System files.
presentation-tier:
	@echo ":: Building Window server, clients and userland."


# ::Building mod0 and init process.
	$(Q) $(MAKE) -C prestier/init/
# Copy to the target folder.
	-sudo cp prestier/bin/INIT.BIN  basetier/disk/ 
	-sudo cp prestier/bin/MOD0.BIN  basetier/disk/


# test
# Importing from another project.
	-sudo cp ../gws/bin/GWSSRV2.BIN  basetier/disk/
#bugbug: This client has some special calls.
#do not use it for tests here.
	#-sudo cp ../gws/bin/GWS2.BIN     basetier/disk/

	-sudo cp ../gws/bin/TERMINAL.BIN  basetier/disk/
	-sudo cp ../gws/bin/EDITOR.BIN    basetier/disk/
	-sudo cp ../gws/bin/FILEMAN.BIN   basetier/disk/
	-sudo cp ../gws/bin/BROWSER.BIN   basetier/disk/
	-sudo cp ../gws/bin/CMDLINE.BIN   basetier/disk/


# ::Building userland commands.
	$(Q) $(MAKE) -C prestier/userland/
# Copy to the target folder.
	-sudo cp prestier/userland/bin/SHUTDOWN.BIN  basetier/disk/
	-sudo cp prestier/userland/bin/REBOOT.BIN    basetier/disk/
	-sudo cp prestier/userland/bin/SHELL.BIN     basetier/disk/
	-sudo cp prestier/userland/bin/CAT.BIN       basetier/disk/
	-sudo cp prestier/userland/bin/TPRINTF.BIN   basetier/disk/
	-sudo cp prestier/userland/bin/SHOWFUN.BIN   basetier/disk/
	-sudo cp prestier/userland/bin/UNAME.BIN     basetier/disk/
	-sudo cp prestier/userland/bin/CMP.BIN       basetier/disk/
	-sudo cp prestier/userland/bin/SUM.BIN       basetier/disk/
	-sudo cp prestier/userland/bin/TASCII.BIN    basetier/disk/
	-sudo cp prestier/userland/bin/FALSE.BIN     basetier/disk/
	-sudo cp prestier/userland/bin/TRUE.BIN      basetier/disk/
	#...

# Suspended
# Copy the clients in another folder.
#	-sudo cp prestier/userland/bin/*.BIN    basetier/disk/PROGRAMS/

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
# Copying the basetier/disk/ folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "Build: Copying files into the mounted VHD ..."

	# Copy basetier/disk/
	# sends everything from disk/ to root.
	sudo cp -r basetier/disk/*  /mnt/gramadoxvhd

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
# Gramado has been tested on sda
# and the Fred's Linux host machine is on sdb.
danger-install-sda:
	sudo dd if=./GRAMADO.VHD of=/dev/sda
danger-install-sdb:
	sudo dd if=./GRAMADO.VHD of=/dev/sdb


#
# == clean ========
#

clean:

# Main files.
	-rm *.o
	@echo ":)"

clean-all: clean

	-rm *.VHD
	-rm *.ISO

# Base tier.

# Clear boot images
	-rm -rf basetier/boot/x86/bin/*.BIN
# Clear newos kernel image
	-rm -rf basetier/new/KERNEL.BIN

	-rm -rf basetier/disk/*.BIN 
	-rm -rf basetier/disk/*.BMP

	-rm -rf basetier/disk/EFI/BOOT/*.EFI 

	-rm -rf basetier/disk/GRAMADO/*.BIN 
	-rm -rf basetier/disk/PROGRAMS/*.BIN 
	-rm -rf basetier/disk/UBASE/BOOT/*.BIN 
	-rm -rf basetier/disk/UBASE/BIN/*.BIN 
	-rm -rf basetier/disk/UBASE/SBIN/*.BIN


# Communication tier.

	-rm -rf comtier/gns/bin/*.BIN

	-rm -rf comtier/lib/rtl/obj/*.o
	-rm -rf comtier/lib/libgns/obj/*.o
	-rm -rf comtier/lib/libio01/obj/*.o
	-rm -rf comtier/lib/fonts/bin/*.FON

# Presentation tier.

	-rm -rf prestier/bin/*.BIN
	-rm     prestier/bin/*.BIN
	-rm     prestier/userland/bin/*.BIN

	-rm -rf prestier/init/init/*.o
	-rm -rf prestier/init/modr0/*.o

	# ...

	@echo "Done ?"

usage:
	@echo "Building everything:"
	@echo "make all"
	@echo "Clear the mess to restart:"
	@echo "make clean-all"
	@echo "Testing on qemu:"
	@echo "./run"

# End.

