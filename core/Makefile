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


# == Start ====

PHONY := all

# build: User command.
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


#----------
# build: Developer comand 1.
# install
# Build the images and put them all into control/disk/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-os  


#----------
# build: Developer comand 2.
# image
# Copy all the files from control/disk/ to the VHD.
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

PHONY := runkvm
runkvm: do_runkvm
do_runkvm:
	sh ./runkvm

#===================================================
#::0
# ~ Step 0: gramado files.

PHONY := build-gramado-os  
build-gramado-os: \
control-tier \
exposed-tier    

#1
control-tier:
	@echo ":: [control-tier] Building VHD, bootloaders and kernel image."

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
	$(Q)$(NASM) control/boot/vd/fat/main.asm \
	-I control/boot/vd/fat/ \
	-o GRAMADO.VHD 

# Create backup for mbr.
	$(Q)$(NASM) control/boot/vd/fat/stage1.asm \
	-I control/boot/vd/fat/ \
	-o MBR0.BIN
	sudo cp MBR0.BIN  control/disk/

# ::Build BM.BIN.
	$(Q)$(MAKE) -C control/boot/x86/bm/ 
# Copy to the target folder.
	sudo cp control/boot/x86/bin/BM.BIN  control/disk/

# ::Build BL.BIN.
	$(Q)$(MAKE) -C control/boot/x86/bl/ 
# Copy to the target folder.
	sudo cp control/boot/x86/bin/BL.BIN  control/disk/


# ::Build kernel image.
	$(Q)$(MAKE) -C control/new/
# Copy to the target folder.
	sudo cp control/new/KERNEL.BIN  control/disk/GRAMADO


# ::Build the ring0 module image.
	$(Q)$(MAKE) -C control/newm0/
# Copy the ring0 module image.
	sudo cp control/newm0/MOD0.BIN  control/disk/

# Install BMPs
	sudo cp control/data/themes/537/*.BMP  control/disk/
#...

	@echo "~control-tier"

#2
exposed-tier:
	@echo ":: [exposed-tier] Building libraries and network server."

#========================================
# ::Build libraries.
	$(Q) $(MAKE) -C exposed/libs/
# Don't copy to the disk.

#========================================
# :: Arctic 
# Building init process.
	$(Q) $(MAKE) -C exposed/arctic/
# Copy to the target folder.
	-sudo cp exposed/arctic/bin/INIT.BIN  control/disk/ 

#========================================
# :: Azure 
# Building userland commands.
# userland
	@echo ":: Making userland."
	$(Q) $(MAKE) -C exposed/azure/
# Copy to the target folder.
	-sudo cp exposed/azure/bin/SHUTDOWN.BIN  control/disk/
	-sudo cp exposed/azure/bin/REBOOT.BIN    control/disk/
	-sudo cp exposed/azure/bin/CAT.BIN       control/disk/
	-sudo cp exposed/azure/bin/UNAME.BIN     control/disk/

	-sudo cp exposed/azure/bin/VGA1.BIN      control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/SHELL.BIN     control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/TPRINTF.BIN   control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/SHOWFUN.BIN   control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/CMP.BIN       control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/SUM.BIN       control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/TASCII.BIN    control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/FALSE.BIN     control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/TRUE.BIN      control/disk/PROGRAMS/
	-sudo cp exposed/azure/bin/GRAMCNF.BIN   control/disk/PROGRAMS/
	#...

#========================================
# :: Indigo 1
	$(Q) $(MAKE) -C exposed/indigo1/ 
# Copy to the target folder.
	-sudo cp exposed/indigo1/bin/GNSSRV.BIN  control/disk/
	-sudo cp exposed/indigo1/bin/GNS.BIN     control/disk/

#========================================
# :: Indigo 2
	$(Q) $(MAKE) -C exposed/indigo2/
	-sudo cp exposed/indigo2/bin/N9.BIN   control/disk/PROGRAMS/
	-sudo cp exposed/indigo2/bin/N10.BIN  control/disk/PROGRAMS/
	-sudo cp exposed/indigo2/bin/N11.BIN  control/disk/PROGRAMS/

	@echo "~exposed-tier"

PHONY := copy-extras
copy-extras:
# Let's copy some images from desktop/

	@echo "copy-extras"

#========================================
# :: desktop
# Copying every image from desktop/.

	@echo ":: Copying Window server and clients."

# Graphics engine
	-sudo cp ../desktop/eng/bin/ENG.BIN   control/disk/
# Window server
	-sudo cp ../desktop/gramland/bin/GRAMLAND.BIN   control/disk/

#
# Shell
#

# apps, apps and apps: (Students)

# apps: Unit 3
	-sudo cp ../desktop/apps/bin/GWS.BIN   control/disk/
	-sudo cp ../desktop/apps/bin/GDM.BIN   control/disk/
	-sudo cp ../desktop/apps/bin/GDM2.BIN  control/disk/
# apps: Unit 2
	-sudo cp ../desktop/apps/bin/TERMINAL.BIN  control/disk/
# apps: Unit 1
	-sudo cp ../desktop/apps/bin/EDITOR.BIN   control/disk/
	-sudo cp ../desktop/apps/bin/FILEMAN.BIN  control/disk/
	-sudo cp ../desktop/apps/bin/CMDLINE.BIN  control/disk/PROGRAMS/
	-sudo cp ../desktop/apps/bin/BROWSER.BIN  control/disk/
	-sudo cp ../desktop/apps/bin/DOCV.BIN     control/disk/PROGRAMS/

#========================================
	@echo "~ copy-extras"

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
# Copying the control/disk/ folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "Build: Copying files into the mounted VHD ..."

	# Copy control/disk/
	# sends everything from disk/ to root.
	sudo cp -r control/disk/*  /mnt/gramadoxvhd

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

# Main files.
clean:
	-rm *.o
	@echo "~clean"

clean-all: clean

	-rm *.VHD
	-rm *.ISO

# ==================
# control tier.

# Clear boot images
	-rm -rf control/boot/x86/bin/*.BIN
# Clear newos kernel image
	-rm -rf control/new/KERNEL.BIN
# Clear the ring0 module image
	-rm -rf control/newm0/MOD0.BIN
# Clear the disk cache
	-rm -rf control/disk/*.BIN 
	-rm -rf control/disk/*.BMP
	-rm -rf control/disk/EFI/BOOT/*.EFI 
	-rm -rf control/disk/GRAMADO/*.BIN 
	-rm -rf control/disk/PROGRAMS/*.BIN 
	-rm -rf control/disk/USERS/*.BIN 

# ==================
# exposed tier.

	-rm exposed/arctic/bin/*.BIN
	-rm exposed/arctic/init/*.o
	-rm exposed/azure/bin/*.BIN
	-rm exposed/indigo/bin/*.BIN
	-rm exposed/lib/fonts/bin/*.FON
	-rm exposed/lib/libgns/obj/*.o
	-rm exposed/lib/libio01/obj/*.o
	-rm exposed/lib/rtl/obj/*.o

	@echo "~clean-all"

usage:
	@echo "Building everything:"
	@echo "make all"
	@echo "Clear the mess to restart:"
	@echo "make clean-all"
	@echo "Testing on qemu:"
	@echo "./run"
	@echo "./runkvm"

# End.

