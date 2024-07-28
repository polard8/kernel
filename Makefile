# Gramado Kernel
# License: BSD License
# Compiling on gcc 11.4.0
# Linking on ld 2.38

BASE    = your/base

# Levels
DEP_L3  = ../aurora
DEP_L2  = ../commands
DEP_L1  = ../de

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
	cp userland/bin/INIT.BIN      $(BASE)/
	-cp userland/bin/PUBSH.BIN    $(BASE)/
	-cp userland/bin/SH7.BIN      $(BASE)/
	-cp userland/bin/SHELL.BIN    $(BASE)/
#	-cp userland/bin/SHELL00.BIN  $(BASE)/
	-cp userland/bin/TASCII.BIN   $(BASE)/PROGRAMS/
	-cp userland/bin/TPRINTF.BIN  $(BASE)/PROGRAMS/
	-cp userland/bin/NETD.BIN     $(BASE)/
	-cp userland/bin/NET.BIN      $(BASE)/

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

# ------------------------
# LEVEL 3: (aurora/) 3D demos.
	-cp $(DEP_L3)/bin/DEMO00.BIN  $(BASE)/
	-cp $(DEP_L3)/bin/DEMO01.BIN  $(BASE)/

# ------------------------
# LEVEL 2: (commands/)  Posix comands.
	-cp $(DEP_L2)/base/bin/CAT.BIN       $(BASE)/
	-cp $(DEP_L2)/base/bin/FALSE.BIN     $(BASE)/
	-cp $(DEP_L2)/base/bin/REBOOT.BIN    $(BASE)/
	-cp $(DEP_L2)/base/bin/SHUTDOWN.BIN  $(BASE)/
	-cp $(DEP_L2)/base/bin/TRUE.BIN      $(BASE)/
	-cp $(DEP_L2)/base/bin/UNAME.BIN     $(BASE)/
# use '@' prefix.
	-cp $(DEP_L2)/sdk/bin/GRAMCNF.BIN  $(BASE)/GRAMADO/
	#-cp $(DEP_L2)/sdk/bin/N9.BIN      $(BASE)/GRAMADO/
	#-cp $(DEP_L2)/sdk/bin/N10.BIN     $(BASE)/GRAMADO/
	#-cp $(DEP_L2)/sdk/bin/N11.BIN     $(BASE)/GRAMADO/
# Use '#' prefix.
	-cp $(DEP_L2)/extra/bin/CMP.BIN       $(BASE)/PROGRAMS/
	-cp $(DEP_L2)/extra/bin/SHOWFUN.BIN   $(BASE)/PROGRAMS/
	-cp $(DEP_L2)/extra/bin/SUM.BIN       $(BASE)/PROGRAMS/
	#-cp $(DEP_L2)/extra/bin/UDPTEST.BIN  $(BASE)/PROGRAMS/

# ------------------------
# LEVEL 1: (de/) Display servers and applications.
	-cp $(DEP_L1)/core/ds00/bin/DS00.BIN   $(BASE)/
	#-cp $(DEP_L1)/core/ds01/bin/DS01.BIN  $(BASE)/
	-cp $(DEP_L1)/core/dsx/bin/DSX.BIN     $(BASE)/
	-cp $(DEP_L1)/shell/bin/TASKBAR.BIN    $(BASE)/
	-cp $(DEP_L1)/shell/bin/TERMINAL.BIN   $(BASE)/
	-cp $(DEP_L1)/shell/bin/GDM.BIN        $(BASE)/
	-cp $(DEP_L1)/shell/bin/EDITOR.BIN     $(BASE)/
	-cp $(DEP_L1)/shell/bin/XTB.BIN        $(BASE)/
# use '@' prefix.
	#-cp $(DEP_L1)/shell/bin/GWS.BIN      $(BASE)/GRAMADO/
# Use '#' prefix.
	-cp $(DEP_L1)/shell/bin/PUBTERM.BIN  $(BASE)/PROGRAMS/
	-cp $(DEP_L1)/shell/bin/DOC.BIN      $(BASE)/PROGRAMS/
# Teabox web browser
	-cp $(DEP_L1)/teabox/bin/TEABOX.BIN  $(BASE)/PROGRAMS/

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
	sudo dd if=./GRAMHV.VHD of=/dev/sda
danger-install-sdb:
	sudo dd if=./GRAMHV.VHD of=/dev/sdb

qemu-instance:
	-cp ./GRAMHV.VHD ./QEMU.VHD 
#xxx-instance:
#	-cp ./GRAMHV.VHD ./XXX.VHD 


# End

