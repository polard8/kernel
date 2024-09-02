# Gramado Kernel
# License: BSD License
# Compiling on gcc 11.4.0
# Linking on ld 2.38

BASE = your/base

# Display server
DEP_L1  = ../de/ds
# Client-side GUI applications
DEP_L2  = ../de/apps

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

#===================================
# (1) boot/ 

# ::Build stuuf in boot/
	$(Q)$(MAKE) -C boot/

# Copy stuff created in boot/
	cp boot/GRAMHV.VHD  .
	cp boot/MBR0.BIN                $(BASE)/
	cp boot/x86/bsp/bin/BM.BIN      $(BASE)/
	cp boot/x86/bsp/bin/BM2.BIN     $(BASE)/
	cp boot/x86/bsp/bin/BLGRAM.BIN  $(BASE)/


#===================================
# (2) kernel/

# ::Build kernel image.
	$(Q)$(MAKE) -C kernel/

# Copy to the target folder.
# We need a backup
	cp kernel/KERNEL.BIN  $(BASE)/GRAMADO
	cp kernel/KERNEL.BIN  $(BASE)/GRAMRE

#===================================
# (3) mods/

# ::Build the ring0 module image.
	$(Q)$(MAKE) -C mods/

# Copy the ring0 module image.
# Not dynlinked modules.
	cp mods/bin/HVMOD0.BIN  $(BASE)/
#	cp mods/bin/HVMOD1.BIN  $(BASE)/
# ...

#===================================
# (4) userland/ in kernel project
# Build the init process.
# Build the network server and the first client.
# Copy the init process.
# We can't survive without this one. (Only this one).
	$(Q)$(MAKE) -C userland/
	$(Q)$(MAKE) -C userland/commands/

# Copy
	cp userland/bin/INIT.BIN      $(BASE)/
	-cp userland/bin/PUBSH.BIN    $(BASE)/
	-cp userland/bin/SH7.BIN      $(BASE)/
	-cp userland/bin/SHELL.BIN    $(BASE)/
#	-cp userland/bin/SHELL00.BIN  $(BASE)/
	-cp userland/bin/NETD.BIN     $(BASE)/
	-cp userland/bin/NET.BIN      $(BASE)/
	-cp userland/bin/TASCII.BIN   $(BASE)/GRAMADO/
	-cp userland/bin/TPRINTF.BIN  $(BASE)/GRAMADO/

    # Well consolidated applications
	-cp userland/commands/base/bin/CAT.BIN       $(BASE)/
	-cp userland/commands/base/bin/REBOOT.BIN    $(BASE)/
	-cp userland/commands/base/bin/SHUTDOWN.BIN  $(BASE)/
	-cp userland/commands/base/bin/UNAME.BIN     $(BASE)/
	-cp userland/commands/sdk/bin/GRAMCNF.BIN    $(BASE)/
    # Experimental applications
    # These need the '@' prefix.
	-cp userland/commands/base/bin/FALSE.BIN      $(BASE)/GRAMADO/
	-cp userland/commands/base/bin/TRUE.BIN       $(BASE)/GRAMADO/
	-cp userland/commands/extra/bin/CMP.BIN       $(BASE)/GRAMADO/
	-cp userland/commands/extra/bin/SHOWFUN.BIN   $(BASE)/GRAMADO/
	-cp userland/commands/extra/bin/SUM.BIN       $(BASE)/GRAMADO/
#-cp userland/commands/sdk/bin/N9.BIN         $(BASE)/GRAMADO/
#-cp userland/commands/sdk/bin/N10.BIN        $(BASE)/GRAMADO/
#-cp userland/commands/sdk/bin/N11.BIN        $(BASE)/GRAMADO/
#-cp userland/commands/extra/bin/UDPTEST.BIN  $(BASE)/GRAMADO/

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
# LEVEL 1: (de/ds) Display servers

	-cp $(DEP_L1)/ds00/bin/DS00.BIN    $(BASE)/
#-cp $(DEP_L1)/ds01/bin/DS01.BIN    $(BASE)/

# ------------------------
# LEVEL 2: (de/apps) Client-side GUI applications

	-cp $(DEP_L2)/bin/TASKBAR.BIN    $(BASE)/
	-cp $(DEP_L2)/bin/XTB.BIN        $(BASE)/
	-cp $(DEP_L2)/bin/TERMINAL.BIN   $(BASE)/
#-cp $(DEP_L2)/bin/GWS.BIN       $(BASE)/
    # Experimental applications
    # These need the '@' prefix.
	-cp $(DEP_L2)/bin/PUBTERM.BIN  $(BASE)/GRAMADO/
	-cp $(DEP_L2)/bin/DOC.BIN      $(BASE)/GRAMADO/
	-cp $(DEP_L2)/bin/GDM.BIN      $(BASE)/GRAMADO/
	-cp $(DEP_L2)/bin/EDITOR.BIN   $(BASE)/GRAMADO/

# (browser/) browser.
# Teabox web browser
    # Experimental applications
    # These need the '@' prefix.
	-cp $(DEP_L2)/browser/teabox/bin/TEABOX.BIN  $(BASE)/GRAMADO/


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

	-rm boot/*.VHD 

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
	-rm -rf mods/bin/*.BIN

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

	-rm userland/commands/bin/*.BIN
	-rm userland/commands/init/*.o

# ==================
# Clear the disk cache
	-rm -rf $(BASE)/*.BIN 
	-rm -rf $(BASE)/*.BMP
	-rm -rf $(BASE)/EFI/BOOT/*.EFI 
	-rm -rf $(BASE)/GRAMADO/*.BIN 
	-rm -rf $(BASE)/GRAMRE/*.BIN 

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

