#E - Facility I
#core
# Gramado Kernel
# License: BSD License
# Compiling on gcc 9.4.0
# Linking on ld 2.34


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

# verbose
# Quiet compilation or not.
ifndef CONFIG_USE_VERBOSE
	CONFIG_USE_VERBOSE = 1
endif

ifeq ($(CONFIG_USE_VERBOSE),1)
	Q =
else
	Q = @
endif

# --------------------------------------
# == Start ====
# build: User command.
PHONY := all
all:  \
build-gramado-os \
copy-extras \
/mnt/gramadoxvhd \
vhd-mount \
vhd-copy-files \
vhd-unmount \
clean    

# Giving permitions to run.
	chmod 755 ./run
	chmod 755 ./runkvm
	@echo "Done?"

# --------------------------------------
# build: Developer comand 1.
# install
# Build the images and put them all into os/disk/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-os  


# --------------------------------------
# build: Developer comand 2.
# image
# Copy all the files from os/disk/ to the VHD.
PHONY := image
image: do_image
do_image: \
/mnt/gramadoxvhd    \
vhd-mount          \
vhd-copy-files     \
vhd-unmount        \

# --------------------------------------
#::0
# ~ Step 0: gramado files.
PHONY := build-gramado-os  
build-gramado-os:     
	@echo ":: [] Building VHD, bootloaders and kernel image."
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
	$(Q)$(NASM) os/boot/vd/fat/main.asm \
	-I os/boot/vd/fat/ \
	-o GRAMADO.VHD 

# Create backup for mbr.
	$(Q)$(NASM) os/boot/vd/fat/stage1.asm \
	-I os/boot/vd/fat/ \
	-o MBR0.BIN
	sudo cp MBR0.BIN  os/disk/

# ::Build BM.BIN.
	$(Q)$(MAKE) -C os/boot/x86/bm/ 
# Copy to the target folder.
	sudo cp os/boot/x86/bin/BM.BIN  os/disk/

# ::Build BL.BIN.
	$(Q)$(MAKE) -C os/boot/x86/bl/ 
# Copy to the target folder.
	sudo cp os/boot/x86/bin/BL.BIN  os/disk/

# ::Build kernel image.
	$(Q)$(MAKE) -C os/kernel/
# Copy to the target folder.
	sudo cp os/kernel/KERNEL.BIN  os/disk/GRAMADO

# ::Build the ring0 module image.
	$(Q)$(MAKE) -C os/newm0/
# Copy the ring0 module image.
	sudo cp os/newm0/MOD0.BIN  os/disk/

# Install BMPs
	sudo cp os/data/themes/537/*.BMP  os/disk/

# ::Build libraries.
	$(Q) $(MAKE) -C libs/
# Don't copy to the disk.

# :: init.bin 
# Building init process.
	$(Q) $(MAKE) -C init/
# Copy to the target folder.
	-sudo cp init/bin/INIT.BIN  os/disk/ 

# :: Azure (Commands)
# Building userland commands.
# userland
	@echo ":: Making userland."
	$(Q) $(MAKE) -C commands/
# Copy to the target folder.
	-sudo cp commands/bin/SHUTDOWN.BIN  os/disk/
	-sudo cp commands/bin/REBOOT.BIN    os/disk/
	-sudo cp commands/bin/CAT.BIN       os/disk/
	-sudo cp commands/bin/UNAME.BIN     os/disk/

	-sudo cp commands/bin/VGA1.BIN      os/disk/PROGRAMS/
	-sudo cp commands/bin/SHELL.BIN     os/disk/PROGRAMS/
	-sudo cp commands/bin/TPRINTF.BIN   os/disk/PROGRAMS/
	-sudo cp commands/bin/SHOWFUN.BIN   os/disk/PROGRAMS/
	-sudo cp commands/bin/CMP.BIN       os/disk/PROGRAMS/
	-sudo cp commands/bin/SUM.BIN       os/disk/PROGRAMS/
	-sudo cp commands/bin/TASCII.BIN    os/disk/PROGRAMS/
	-sudo cp commands/bin/FALSE.BIN     os/disk/PROGRAMS/
	-sudo cp commands/bin/TRUE.BIN      os/disk/PROGRAMS/
	-sudo cp commands/bin/GRAMCNF.BIN   os/disk/PROGRAMS/
	#...

	-sudo cp commands/bin/N9.BIN   os/disk/PROGRAMS/
	-sudo cp commands/bin/N10.BIN  os/disk/PROGRAMS/
	-sudo cp commands/bin/N11.BIN  os/disk/PROGRAMS/


# :: Indigo 1 (net)
	$(Q) $(MAKE) -C net/ 
# Copy to the target folder.
	-sudo cp net/bin/GNSSRV.BIN  os/disk/
	-sudo cp net/bin/GNS.BIN     os/disk/

	@echo "~build-gramado-os end?"

# --------------------------------------
PHONY := copy-extras
copy-extras:
# Let's copy some images from desktop/

	@echo "copy-extras"

# :: desktop
# Copying every image from desktop/.

	@echo ":: Copying Window server and clients."

# Graphics engine
	-sudo cp ../desktop/eng/bin/ENG.BIN   os/disk/
# Window server
	-sudo cp ../desktop/gramland/bin/GRAMLAND.BIN   os/disk/

#
# Shell
#

# apps, apps and apps: (Students)

# apps: Unit 3
	-sudo cp ../desktop/apps/bin/GWS.BIN   os/disk/
	-sudo cp ../desktop/apps/bin/GDM.BIN   os/disk/
	-sudo cp ../desktop/apps/bin/GDM2.BIN  os/disk/
# apps: Unit 2
	-sudo cp ../desktop/apps/bin/TERMINAL.BIN  os/disk/
# apps: Unit 1
	-sudo cp ../desktop/apps/bin/EDITOR.BIN   os/disk/
	-sudo cp ../desktop/apps/bin/FILEMAN.BIN  os/disk/
	-sudo cp ../desktop/apps/bin/CMDLINE.BIN  os/disk/PROGRAMS/
	-sudo cp ../desktop/apps/bin/BROWSER.BIN  os/disk/
	-sudo cp ../desktop/apps/bin/DOCV.BIN     os/disk/PROGRAMS/

	@echo "~ copy-extras"

# --------------------------------------
#::2
# Step 2: /mnt/gramadoxvhd  - Creating the directory to mount the VHD.
/mnt/gramadoxvhd:
	@echo "========================="
	@echo "Build: Creating the directory to mount the VHD ..."
	sudo mkdir /mnt/gramadoxvhd

# --------------------------------------
#::3
# ~ Step 3: vhd-mount - Mounting the VHD.
vhd-mount:
	@echo "=========================="
	@echo "Build: Mounting the VHD ..."
	-sudo umount /mnt/gramadoxvhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadoxvhd/

# --------------------------------------
#::4
# ~ Step 4 vhd-copy-files - Copying files into the mounted VHD.
# Copying the os/disk/ folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "Build: Copying files into the mounted VHD ..."
	# Copy os/disk/
	# sends everything from disk/ to root.
	sudo cp -r os/disk/*  /mnt/gramadoxvhd

# --------------------------------------
#:::5
# ~ Step 5 vhd-unmount  - Unmounting the VHD.
vhd-unmount:
	@echo "======================"
	@echo "Build: Unmounting the VHD ..."
	sudo umount /mnt/gramadoxvhd

# --------------------------------------
# Run on qemu.
PHONY := run
run: do_run
do_run:
	sh ./run

# --------------------------------------
# Run on qemu using kvm.
PHONY := runkvm
runkvm: do_runkvm
do_runkvm:
	sh ./runkvm

# --------------------------------------
# Basic clean.
clean:
	-rm *.o
	@echo "~clean"

# --------------------------------------
# Clean up all the mess.
clean-all: clean

	-rm *.VHD
	-rm *.ISO

# ==================
# os tier.

# Clear boot images
	-rm -rf os/boot/x86/bin/*.BIN
# Clear newos kernel image
	-rm -rf os/kernel/KERNEL.BIN
# Clear the ring0 module image
	-rm -rf os/newm0/MOD0.BIN
# Clear the disk cache
	-rm -rf os/disk/*.BIN 
	-rm -rf os/disk/*.BMP
	-rm -rf os/disk/EFI/BOOT/*.EFI 
	-rm -rf os/disk/GRAMADO/*.BIN 
	-rm -rf os/disk/PROGRAMS/*.BIN 
	-rm -rf os/disk/USERS/*.BIN 

# ==================
# exposed tier.

	-rm init/bin/*.BIN
	-rm init/init/*.o
	-rm commands/bin/*.BIN
	-rm indigo/bin/*.BIN
	-rm libs/fonts/bin/*.FON
	-rm libs/libgns/obj/*.o
	-rm libs/libio01/obj/*.o
	-rm libs/rtl/obj/*.o

	@echo "~clean-all"

# --------------------------------------
# Usage instructions.
usage:
	@echo "Building everything:"
	@echo "make all"
	@echo "Clear the mess to restart:"
	@echo "make clean-all"
	@echo "Testing on qemu:"
	@echo "./run"
	@echo "./runkvm"

# --------------------------------------
# Danger zone!
# This is gonna copy th image into the real HD.
# My host is running on sdb and i copy the image into sda.
# It is because the sda is in primary master IDE.
# Gramado has been tested on sda
# and the Fred's Linux host machine is on sdb.
danger-install-sda:
	sudo dd if=./GRAMADO.VHD of=/dev/sda
danger-install-sdb:
	sudo dd if=./GRAMADO.VHD of=/dev/sdb

# End.

