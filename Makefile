# License: BSD License
# Product configuration
# See: 0config/version.h

PRODUCT_NAME  = Gramado
EDITION_NAME  = 64bit
VERSION_MAJOR = 1
VERSION_MINOR = 1
VERSION_BUILD = 253

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

# All the steps.
all:  \
build-landos-files \
build-gramado-files \
/mnt/gramadoxvhd    \
vhd-mount          \
vhd-copy-files     \
vhd-unmount        \
clean              \
clean-system-files \
#generate

# Giving permitions to run ./run
	chmod 755 ./run

# Product info:
	@echo "$(PRODUCT_NAME) $(EDITION_NAME) $(KERNELVERSION)"
#	@echo "$(ARCH)"

#===================================================
#::0
# ~ Step 0: landos files.

PHONY := build-landos-files
build-landos-files: \
/usr/local/gramadox-build \
land-boot \
land-lib \
land-os \
land-cmd \
land-setup    


/usr/local/gramadox-build:
	-sudo mkdir /usr/local/gramadox-build
land-boot:
	@echo "==================="
	@echo "Compiling landboot/ ... "

	$(Q) $(NASM)  landboot/vd/fat/main.asm -I landboot/vd/fat/ -o GRAMADO.VHD 
	$(Q) $(MAKE) -C landboot/bm1632/x86/ 
	$(Q) $(MAKE) -C landboot/bl64/x86_64/ 

	# O mbr só consegue ler o root dir para pegar o BM.BIN
	# See: stage1.asm
	# O BM.BIN só consegue ler o root dir pra pegar o BL.BIN
	# See: main.asm

	sudo cp landboot/bin/BM.BIN  base/
	sudo cp landboot/bin/BL.BIN  base/

land-lib:
	# todo: Port ring3 libraries.
land-os:
	@echo "=================="
	@echo "(Step 1) Creating the kernel image ..."

	$(Q) $(MAKE) -C landos/kernel

	# O BL.BIN procura o kernel no diretorio GRAMADO/
	# See: fs/loader.c

	sudo cp landos/kernel/KERNEL.BIN  base/GRAMADO

land-cmd:
	# todo: Port ring3 commands.
land-setup:
	# todo: Port ring3 setup application.

#===================================================
#::1
# ~ Step 1 - Gramado Window System files.

PHONY := build-gramado-files 
build-gramado-files: \
#gramado-ws \
#gramado-services \
#desert    


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
	sudo cp landos/init/INIT.BIN  base/
	
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
clean clean2 clean3 clean4 clean-system-files 
	@echo "==================="
	@echo "ok ?"
clean:
	@echo "==================="
	@echo "(Step 6) Deleting the object files ..."
	-rm *.o
clean2:
	-rm *.ISO
	-rm *.VHD
clean3:
	# todo
clean4:
	-rm -rf base/*.BIN 
	-rm -rf base/GRAMADO/*.BIN 
clean-system-files:
	@echo "==================="
	@echo "Cleaning all system binaries ..."

	-rm -rf landos/kernel/KERNEL.BIN






