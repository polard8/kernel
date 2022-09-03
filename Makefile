# License: BSD License
# Product configuration
# See: 0config/version.h

PRODUCT_NAME  = Gramado
EDITION_NAME  = Angels/Warden

VERSION_MAJOR = 1
VERSION_MINOR = 5
VERSION_BUILD = 295
# test: Compiling on gcc 11.2

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
	chmod 755 ./runkvm
	
# Product info:
	@echo "$(PRODUCT_NAME) $(EDITION_NAME) $(KERNELVERSION)"
#	@echo "$(ARCH)"


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
	$(Q) $(NASM) control/boot/vd/fat/main.asm \
	-I control/boot/vd/fat/ \
	-o GRAMADO.VHD 


# ::Build BM.BIN.
	$(Q) $(MAKE) -C control/boot/x86/bm/ 
# Copy to the target folder.
	sudo cp control/boot/x86/bin/BM.BIN  control/disk/

# ::Build BL.BIN.
	$(Q) $(MAKE) -C control/boot/x86/bl/ 
# Copy to the target folder.
	sudo cp control/boot/x86/bin/BL.BIN  control/disk/


# ::Build kernel image.
	$(Q) $(MAKE) -C control/new/
# Copy to the target folder.
	sudo cp control/new/KERNEL.BIN  control/disk/GRAMADO


# ::Build the ring0 module image.
	$(Q) $(MAKE) -C control/newm0/
# Copy the ring0 module image.
	sudo cp control/newm0/MOD0.BIN  control/disk/

# Install BMPs
	sudo cp control/data/themes/field/*.BMP  control/disk/
#...


#2
exposed-tier:
	@echo ":: Building libraries and network server."

#========================================
# ::Build libraries.
	$(Q) $(MAKE) -C exposed/lib/
# Don't copy to the disk.

#========================================
# ::Building init process.
	$(Q) $(MAKE) -C exposed/arctic/
# Copy to the target folder.
	-sudo cp exposed/arctic/bin/INIT.BIN  control/disk/ 

#========================================
# ::Building userland commands.
# userland
	@echo ":: Making userland."
	$(Q) $(MAKE) -C exposed/azure/
# Copy to the target folder.
	-sudo cp exposed/azure/bin/SHUTDOWN.BIN  control/disk/

	-sudo cp exposed/azure/bin/REBOOT.BIN    control/disk/
	-sudo cp exposed/azure/bin/VGA1.BIN      control/disk/

	-sudo cp exposed/azure/bin/SHELL.BIN     control/disk/
	-sudo cp exposed/azure/bin/CAT.BIN       control/disk/
	-sudo cp exposed/azure/bin/TPRINTF.BIN   control/disk/
	-sudo cp exposed/azure/bin/SHOWFUN.BIN   control/disk/
	-sudo cp exposed/azure/bin/UNAME.BIN     control/disk/
	-sudo cp exposed/azure/bin/CMP.BIN       control/disk/
	-sudo cp exposed/azure/bin/SUM.BIN       control/disk/
	-sudo cp exposed/azure/bin/TASCII.BIN    control/disk/
	-sudo cp exposed/azure/bin/FALSE.BIN     control/disk/
	-sudo cp exposed/azure/bin/TRUE.BIN      control/disk/
	#...

#========================================
# ::Build network server.
	$(Q) $(MAKE) -C exposed/indigo/ 
# Copy to the target folder.
	-sudo cp exposed/indigo/bin/GNSSRV.BIN  control/disk/
	-sudo cp exposed/indigo/bin/GNS.BIN     control/disk/

#========================================
	@echo ":: Copying Window server and clients."
# test ---------------------------
# Importing from another project.
#burgundy
#bugbug: This client has some special calls.
#do not use it for tests here.
	-sudo cp ../hot/burgundy/bin/GWSSRV.BIN  control/disk/
	#-sudo cp ../hot/burgundy/bin/GWS.BIN     control/disk/
	-sudo cp ../hot/burgundy/bin/GDM.BIN     control/disk/
	-sudo cp ../hot/burgundy/bin/GDM2.BIN    control/disk/
#blue
	-sudo cp ../hot/blue/bin/TERMINAL.BIN  control/disk/
#beige
	-sudo cp ../hot/beige/bin/EDITOR.BIN    control/disk/
	-sudo cp ../hot/beige/bin/FILEMAN.BIN   control/disk/
	-sudo cp ../hot/beige/bin/CMDLINE.BIN   control/disk/
#attitude
	-sudo cp ../hot/attitude/bin/BROWSER.BIN   control/disk/


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
	@echo ":)"

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

	@echo "Done ?"

usage:
	@echo "Building everything:"
	@echo "make all"
	@echo "Clear the mess to restart:"
	@echo "make clean-all"
	@echo "Testing on qemu:"
	@echo "./run"
	@echo "./runkvm"

# End.

