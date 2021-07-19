# License: BSD License
# Product configuration
# See: 0config/version.h

PRODUCT_NAME  = Gramado
EDITION_NAME  = 64bit
VERSION_MAJOR = 2
VERSION_MINOR = 0
VERSION_BUILD = 264

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

# Verbose.

ifndef KBUILD_VERBOSE
  KBUILD_VERBOSE = 1
endif

ifeq ($(KBUILD_VERBOSE),1)
  Q =
else
  Q = @
endif

PHONY := all

# build: User command.
all:  \
build-gramado-files \
/mnt/gramadoxvhd    \
vhd-mount          \
vhd-copy-files     \
vhd-unmount        \
clean              \
clean4 \
#generate

# Giving permitions to run ./run
	chmod 755 ./run

# Product info:
	@echo "$(PRODUCT_NAME) $(EDITION_NAME) $(KERNELVERSION)"
#	@echo "$(ARCH)"


#----------
# build: Developer comand 1.
# install
# Build the images and put them all into base/ folder.
PHONY := install
install: do_install
do_install: \
build-gramado-files  


#----------
# build: Developer comand 2.
# image
# Copy all the files from base/ to the VHD.
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

PHONY := build-gramado-files
build-gramado-files: \
gramado-kernel \
gramado-lib \
gramado-init \
gramado-cmd \
gramado-setup \
gramado-ws \
gramado-ns \
gramado-boot \
desert    

#1
# the kernel image
# O BL.BIN procura o kernel no diretorio GRAMADO/
# See: fs/loader.c
gramado-kernel:
	@echo "=================="
	@echo "(Step 1) Creating the kernel image ..."

	$(Q) $(MAKE) -C kernel/
	sudo cp kernel/KERNEL.BIN  base/GRAMADO

#2
gramado-lib:

	#::rtl (The libc)
	@echo "==================="
	@echo "Compiling rtl ..."
	$(Q) $(MAKE) -C lib/rtl/

	#::lib (The frameworks)
	@echo "==================="
	@echo "Compiling  lib ..."
	$(Q) $(MAKE) -C lib/lib/

#3
gramado-init:
	$(Q) $(MAKE) -C init/
	sudo cp init/INIT.BIN  base/

#4
gramado-cmd:
	#::cmd
	$(Q) $(MAKE) -C cmd/
	-sudo cp cmd/bin/CAT.BIN        base/
#	-sudo cp cmd/bin/FALSE.BIN      base/
	-sudo cp cmd/bin/REBOOT.BIN     base/
	-sudo cp cmd/bin/SHUTDOWN.BIN     base/
#	-sudo cp cmd/bin/TRUE.BIN       base/
#	-sudo cp cmd/bin/SHOWFUN.BIN    base/
#	-sudo cp cmd/bin/UNAME.BIN      base/

#5
gramado-setup:
	#::setup
	$(Q) $(MAKE) -C setup/
	sudo cp setup/bin/GDESHELL.BIN  base/
	#sudo cp setup/bin/C4.BIN       base/
	#sudo cp setup/bin/GRAMC.BIN    base/
	#sudo cp setup/bin/GRAMC4.BIN   base/
	#sudo cp setup/bin/GRAMCNF.BIN  base/

#6
# Gramado Window System files.
gramado-ws:

	#:: Gramado WS
	@echo "==================="
	@echo "Compiling Gramado WS and some clients"
	$(Q) $(MAKE) -C ws/

# Server and main client.
	-sudo cp ws/bin/GWSSRV.BIN    base/
	-sudo cp ws/bin/GWS.BIN       base/ 

# Clients
	-sudo cp ws/bin/GWM.BIN       base/
	-sudo cp ws/bin/LOGON.BIN     base/
	-sudo cp ws/bin/EDITOR.BIN    base/
	-sudo cp ws/bin/TERMINAL.BIN  base/
	-sudo cp ws/bin/FILEMAN.BIN   base/
	-sudo cp ws/bin/BROWSER.BIN   base/

# Suspended
# Copy the clients in another folder.
#	-sudo cp ws/bin/*.BIN    base/PROGRAMS/

#7
gramado-ns:
	#::hard Services
	@echo "==================="
	@echo "Compiling hard..."
	$(Q) $(MAKE) -C ns/ 
	# gns
	-sudo cp ns/bin/GNSSRV.BIN  base/
	-sudo cp ns/bin/GNS.BIN     base/

#8
gramado-boot:
	@echo "==================="
	@echo "Compiling tools/ and boot ... "

	$(Q) $(NASM) tools/vd/fat/main.asm \
	-I tools/vd/fat/ \
	-o GRAMADO.VHD 

	$(Q) $(MAKE) -C arch/x86/boot/bm/ 
	$(Q) $(MAKE) -C arch/x86/boot/bl/ 

	# O mbr só consegue ler o root dir para pegar o BM.BIN
	# See: stage1.asm
	# O BM.BIN só consegue ler o root dir pra pegar o BL.BIN
	# See: main.asm

	sudo cp arch/x86/boot/bin/BM.BIN  base/
	sudo cp arch/x86/boot/bin/BL.BIN  base/

#9
#========================================
# Installing stuff from another project.
desert:
	# Nothing for now!

#===================================================
#::2
# Step 2: /mnt/gramadoxvhd  - Creating the directory to mount the VHD.
/mnt/gramadoxvhd:
	@echo "========================="
	@echo "(Step 2) Creating the directory to mount the VHD ..."
	sudo mkdir /mnt/gramadoxvhd

#===================================================
#::3
# ~ Step 3: vhd-mount - Mounting the VHD.
vhd-mount:
	@echo "=========================="
	@echo "(Step 3) Mounting the VHD ..."
	-sudo umount /mnt/gramadoxvhd
	sudo mount -t vfat -o loop,offset=32256 GRAMADO.VHD /mnt/gramadoxvhd/

#===================================================
#::4
# ~ Step 4 vhd-copy-files - Copying files into the mounted VHD.
# Copying the base folder into the mounted VHD.
vhd-copy-files:
	@echo "========================="
	@echo "(Step 4) Copying files into the mounted VHD ..."

	#Copy INIT.BIN to base/
	#sudo cp landos/init/INIT.BIN  base/
	
	# Copy base
	# sends everything from base to root.
	sudo cp -r base/*  /mnt/gramadoxvhd

#===================================================
#:::5
# ~ Step 5 vhd-unmount  - Unmounting the VHD.
vhd-unmount:
	@echo "======================"
	@echo "(Step 5) Unmounting the VHD ..."
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
clean clean2 clean3 clean4 clean5  
	@echo "==================="
	@echo "ok ?"
clean:
	@echo "==================="
	@echo "(Step 6) Deleting the object files ..."
	-rm *.o
	-rm -rf lib/rtl/obj/*.o
	-rm -rf lib/lib/libgns/obj/*.o
	-rm -rf lib/lib/libio01/obj/*.o
	@echo "Success?"
clean1: clean
clean2:
	-rm *.VHD
	-rm *.ISO
clean3:
	-rm cmd/bin/*.BIN
	-rm setup/bin/*.BIN
	-rm ws/bin/*.BIN
# clean base
clean4:
	@echo "==================="
	@echo "Cleaning all system binaries ..."
	-rm -rf kernel/KERNEL.BIN
	-rm -rf arch/x86/boot/bin/*.BIN
	-rm -rf init/*.BIN
	-rm -rf cmd/bin/*.BIN
	-rm -rf setup/bin/*.BIN
	-rm -rf ws/bin/*.BIN
	-rm -rf ns/bin/*.BIN
	-rm -rf lib/fonts/bin/*.FON
clean5:
	-rm -rf base/*.BIN 
	-rm -rf base/GRAMADO/*.BIN 
	-rm -rf base/PROGRAMS/*.BIN 
	-rm -rf base/UBASE/BOOT/*.BIN 
	-rm -rf base/UBASE/BIN/*.BIN 
	-rm -rf base/UBASE/SBIN/*.BIN
	
# ...







