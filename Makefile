
# Gramado Kernel
# License: BSD License
# Compiling on gcc 11.4.0
# Linking on ld 2.38

BASE    = your/base

DEP_B1  = ../de/commands
DEP_B2  = ../de/ui
DEP_B3  = ../de/user3d

#DEP_B10 = ../guest0
#DEP_B11 = ../guest1
# ...

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
# Not silent. It prints the commands.
	Q =
else
# silent
	Q = @
endif

# --------------------------------------
# == Start ====
# build: User command.
PHONY := all
all:  \
build-gramado-os \
copy-extras \
/mnt/GRAMVD \
vhd-mount \
vhd-copy-files \
vhd-unmount \
clean    

# Giving permitions to run.
	chmod 755 ./run
	chmod 755 ./runnokvm

# tests
	chmod 755 ./runt1
	chmod 755 ./runt2
	@echo "Done?"

# --------------------------------------
# build: Developer comand 1.
# install
# Build the images and put them all into $(BASE)/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-os  


# --------------------------------------
# build: Developer comand 2.
# image
# Copy all the files from $(BASE)/ to the VHD.
PHONY := image
image: do_image
do_image: \
/mnt/GRAMVD    \
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

#----------------------------------
# (1) boot/

# Create the virtual disk 0.
	$(Q)$(NASM) boot/x86/vd/fat/main.asm \
	-I boot/x86/vd/fat/ \
	-o GRAMHV.VHD 

# Create backup for MBR 0.
	$(Q)$(NASM) boot/x86/vd/fat/stage1.asm \
	-I boot/x86/vd/fat/ \
	-o MBR0.BIN
	cp MBR0.BIN  $(BASE)/

# ::Build BM.BIN. (legacy, no dialog)
	$(Q)$(MAKE) -C boot/x86/bm/ 
# Copy to the target folder.
	cp boot/x86/bin/BM.BIN  $(BASE)/

# #BUGBUG 
# Suspended!
# Something is affecting the window server,
# if we enter in the graphics mode without entering
# the shell first. There are two routines 
# to initialize the gui mode. Only one is good.
# ::Build BM2.BIN. (Interface with dialog)
	$(Q)$(MAKE) -C boot/x86/bm2/ 
# Copy to the target folder.
	cp boot/x86/bin/BM2.BIN  $(BASE)/

# ::Build BL.BIN.
	$(Q)$(MAKE) -C boot/x86/bl/ 
# Copy to the target folder.
	cp boot/x86/bin/BL.BIN  $(BASE)/

#----------------------------------
# (3) /

# ::Build kernel image.
	$(Q)$(MAKE) -C kernel/
# Copy to the target folder.
	cp kernel/KERNEL.BIN  $(BASE)/GRAMADO

#----------------------------------
# (4) mods/

#----------------------------------
# ::Build the ring0 module image.
	$(Q)$(MAKE) -C mods/
# Copy the ring0 module image.
	cp mods/HVMOD0.BIN  $(BASE)/

#----------------------------------
# () userland/
# Build the init process.
# Build the network server and the first client.
# Copy the init process.
# We can't survive without this one. (Only this one).
	make -C userland/
	cp userland/bin/INIT.BIN  $(BASE)/
	cp userland/bin/NETD.BIN  $(BASE)/
	cp userland/bin/NET.BIN   $(BASE)/

# Install BMPs from cali assets.
# Copy the assets/
# We can't survive without this one.
	cp your/assets/themes/theme01/*.BMP  $(BASE)/

	@echo "~build-gramado-os end?"

# --------------------------------------
# Let's add a bit of shame in the project.
PHONY := copy-extras
copy-extras:

	@echo "copy-extras"

# -----------------------------
# Survival kit.
# Commands and apps in root directory.

	# Commands
	-cp $(DEP_B1)/bin/CAT.BIN       $(BASE)/
	-cp $(DEP_B1)/bin/REBOOT.BIN    $(BASE)/
	-cp $(DEP_B1)/bin/SHUTDOWN.BIN  $(BASE)/
	-cp $(DEP_B1)/bin/UNAME.BIN     $(BASE)/
	# Apps
	-cp $(DEP_B2)/core/server/bin/GRAMLAND.BIN   $(BASE)/
	-cp $(DEP_B2)/shell/bin/TASKBAR.BIN   $(BASE)/
	-cp $(DEP_B2)/shell/bin/TERMINAL.BIN  $(BASE)/
	-cp $(DEP_B2)/shell/bin/GDM.BIN       $(BASE)/
	-cp $(DEP_B2)/shell/bin/EDITOR.BIN    $(BASE)/
	# Gramado OS 3D demos.
	-cp $(DEP_B3)/bin/ENG.BIN  $(BASE)/
	#-cp $(DEP_B3)/bin/ENG2.BIN  $(BASE)/
	#...

# -----------------------------
# Commands and apps in GRAMADO/ folder.
# Gotta use '@' before the command.

	# Commands
	-cp $(DEP_B1)/bin/SHELL.BIN     $(BASE)/GRAMADO/
	-cp $(DEP_B1)/bin/PUBSH.BIN     $(BASE)/GRAMADO/
	-cp $(DEP_B1)/bin/GRAMCNF.BIN   $(BASE)/GRAMADO/
	# Apps
	#-cp $(DEP_B2)/shell/bin/GWS.BIN      $(BASE)/GRAMADO/
	
# -----------------------------
# Commands and apps in PROGRAMS/ folder.
# Gotta use '#' before the command.

	# Commands
	-cp $(DEP_B1)/bin/FALSE.BIN     $(BASE)/PROGRAMS/
	-cp $(DEP_B1)/bin/TRUE.BIN      $(BASE)/PROGRAMS/
	-cp $(DEP_B1)/bin/TASCII.BIN    $(BASE)/PROGRAMS/
	-cp $(DEP_B1)/bin/TPRINTF.BIN   $(BASE)/PROGRAMS/
	-cp $(DEP_B1)/bin/CMP.BIN       $(BASE)/PROGRAMS/
	-cp $(DEP_B1)/bin/SHOWFUN.BIN   $(BASE)/PROGRAMS/
	-cp $(DEP_B1)/bin/SUM.BIN       $(BASE)/PROGRAMS/
	#	-cp $(DEP_B1)/bin/N9.BIN   $(BASE)/PROGRAMS/
	#	-cp $(DEP_B1)/bin/N10.BIN  $(BASE)/PROGRAMS/
	#	-cp $(DEP_B1)/bin/N11.BIN  $(BASE)/PROGRAMS/
	# Apps
	-cp $(DEP_B2)/shell/bin/PUBTERM.BIN  $(BASE)/PROGRAMS/
	-cp $(DEP_B2)/shell/bin/BROWSER.BIN  $(BASE)/PROGRAMS/
	-cp $(DEP_B2)/shell/bin/DOC.BIN      $(BASE)/PROGRAMS/

	@echo "~ copy-extras"

# --------------------------------------
#::2
# Step 2: /mnt/GRAMVD  - Creating the directory to mount the VHD.
/mnt/GRAMVD:
	@echo "========================="
	@echo "Build: Creating the directory to mount the VHD ..."
	sudo mkdir /mnt/GRAMVD

# --------------------------------------
#::3
# ~ Step 3: vhd-mount - Mounting the VHD.
vhd-mount:
	@echo "=========================="
	@echo "Build: Mounting the VHD ..."
	-sudo umount /mnt/GRAMVD
	sudo mount -t vfat -o loop,offset=32256 GRAMHV.VHD /mnt/GRAMVD/

# --------------------------------------
#::4
# ~ Step 4 vhd-copy-files - Copying files into the mounted VHD.
# Copying the $(BASE)/ folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "Build: Copying files into the mounted VHD ..."
	# Copy $(BASE)/
	# sends everything from disk/ to root.
	sudo cp -r $(BASE)/*  /mnt/GRAMVD

# --------------------------------------
#:::5
# ~ Step 5 vhd-unmount  - Unmounting the VHD.
vhd-unmount:
	@echo "======================"
	@echo "Build: Unmounting the VHD ..."
	sudo umount /mnt/GRAMVD

# --------------------------------------
# Run on qemu using kvm.
PHONY := run
run: do_run
do_run:
	sh ./run

# --------------------------------------
# Run on qemu with no kvm.
PHONY := runnokvm
runnokvm: do_runnokvm
do_runnokvm:
	sh ./runnokvm


# --------------------------------------
# Basic clean.
clean:
	-rm *.o
	-rm *.BIN
	-rm kernel/*.o
	-rm kernel/*.BIN
	@echo "~clean"

# --------------------------------------
# Clean up all the mess.
clean-all: clean

	-rm *.o
	-rm *.BIN
	-rm *.VHD
	-rm *.ISO

# ==================
# (1) boot/
# Clear boot images
#	-rm -rf boot/arm/bin/*.BIN
	-rm -rf boot/x86/bin/*.BIN

# ==================
# (2) kernel/
# Clear kernel image
	-rm kernel/*.o
	-rm kernel/*.BIN
	-rm -rf kernel/KERNEL.BIN

# ==================
# (3) mods/
# Clear the ring0 module images
	-rm -rf mods/*.o
	-rm -rf mods/*.BIN

# ==================
# (4) userland/
# Clear INIT.BIN, HVNETD.BIN and HVNET.BIN.
	-rm userland/bin/*.BIN
	-rm userland/init/*.o
	-rm userland/init/*.BIN 
	-rm userland/netd/client/*.o
	-rm userland/netd/client/*.BIN
	-rm userland/netd/server/*.o
	-rm userland/netd/server/*.BIN 

# ==================
# Clear the disk cache
	-rm -rf $(BASE)/*.BIN 
	-rm -rf $(BASE)/*.BMP
	-rm -rf $(BASE)/EFI/BOOT/*.EFI 
	-rm -rf $(BASE)/GRAMADO/*.BIN 
	-rm -rf $(BASE)/PROGRAMS/*.BIN 
	-rm -rf $(BASE)/USERS/*.BIN 

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
	@echo "./runnokvm"

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

