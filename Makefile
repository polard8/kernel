# License: BSD License
# Product configuration
# See: 0config/version.h

PRODUCT_NAME  = Gramado
EDITION_NAME  = 64bit
VERSION_MAJOR = 1
VERSION_MINOR = 1
VERSION_BUILD = 262

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


#----------
# install
# Build the images and put them all into base/ folder.
PHONY := install
install: do_install
do_install: \
build-landos-files \
build-gramado-files \

#----------
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
# run
# run the system on qemu.
PHONY := run
run: do_run
do_run:
	sh ./run


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
	#::rtl
	@echo "==================="
	@echo "Compiling rtl ..."
	$(Q) $(MAKE) -C landlib/rtl/

	#::lib
	@echo "==================="
	@echo "Compiling  lib ..."
	$(Q) $(MAKE) -C landlib/lib/


land-os:
	@echo "=================="
	@echo "(Step 1) Creating the kernel image ..."

	# O BL.BIN procura o kernel no diretorio GRAMADO/
	# See: fs/loader.c

	$(Q) $(MAKE) -C landos/kernel
	sudo cp landos/kernel/KERNEL.BIN  base/GRAMADO

	$(Q) $(MAKE) -C landos/init
	sudo cp landos/init/INIT.BIN  base/

land-cmd:
	#::cmd
	$(Q) $(MAKE) -C landos/cmd/
	-sudo cp landos/cmd/bin/CAT.BIN        base/
#	-sudo cp landos/cmd/bin/FALSE.BIN      base/
	-sudo cp landos/cmd/bin/REBOOT.BIN     base/
	-sudo cp landos/cmd/bin/SHUTDOWN.BIN     base/
#	-sudo cp landos/cmd/bin/TRUE.BIN       base/
#	-sudo cp landos/cmd/bin/SHOWFUN.BIN    base/
#	-sudo cp landos/cmd/bin/UNAME.BIN      base/

land-setup:
	#::setup
	$(Q) $(MAKE) -C landos/setup/
	sudo cp landos/setup/bin/GDESHELL.BIN  base/
	#sudo cp landos/setup/bin/C4.BIN       base/
	#sudo cp landos/setup/bin/GRAMC.BIN    base/
	#sudo cp landos/setup/bin/GRAMC4.BIN   base/
	#sudo cp landos/setup/bin/GRAMCNF.BIN  base/



#===================================================
#::1
# ~ Step 1 - Gramado Window System files.

PHONY := build-gramado-files 
build-gramado-files: \
gramado-ws \
gramado-services \
desert    

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

gramado-services:
	#::hard Services
	@echo "==================="
	@echo "Compiling hard..."
	$(Q) $(MAKE) -C services/gnssrv/ 
	# gns
	-sudo cp services/gnssrv/bin/GNSSRV.BIN  base/
	-sudo cp services/gnssrv/bin/GNS.BIN     base/

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
clean clean2 clean3 clean4 clean-system-files 
	@echo "==================="
	@echo "ok ?"
clean:
	@echo "==================="
	@echo "(Step 6) Deleting the object files ..."
	-rm *.o
	-rm -rf landlib/rtl/obj/*.o
	-rm -rf landlib/lib/libgns/obj/*.o
	-rm -rf landlib/lib/libio01/obj/*.o
	@echo "Success?"
clean2:
	-rm *.VHD
	-rm *.ISO
clean3:
	-rm landos/setup/bin/*.BIN
	-rm landos/cmd/bin/*.BIN
	-rm ws/bin/*.BIN
# clean base
clean4:
	-rm -rf base/*.BIN 
	-rm -rf base/GRAMADO/*.BIN 
	-rm -rf base/PROGRAMS/*.BIN 
	-rm -rf base/UBASE/BOOT/*.BIN 
	-rm -rf base/UBASE/BIN/*.BIN 
	-rm -rf base/UBASE/SBIN/*.BIN
clean-system-files:
	@echo "==================="
	@echo "Cleaning all system binaries ..."
	-rm -rf landboot/bin/*.BIN
	-rm -rf landlib/fonts/bin/*.FON
	-rm -rf landos/kernel/KERNEL.BIN
	-rm -rf landos/init/*.BIN
	-rm -rf landos/cmd/bin/*.BIN
	-rm -rf landos/setup/bin/*.BIN
	-rm -rf ws/bin/*.BIN
	-rm -rf services/gnssrv/bin/*.BIN
# ...







