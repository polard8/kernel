
# Build Gramado OS.

PHONY := secret-chord
secret-chord: step2-desktop step3-core
	@echo "Done"

PHONY := step2-desktop
step2-desktop:
	make -C  desktop

PHONY := step3-core
step3-core:
	make -C  core

PHONY := clean
clean: clean-all

PHONY := clean-all
clean-all: clean-desktop clean-core

PHONY := clean-desktop
clean-desktop:
# In desktop/
	-rm desktop/gramland/bin/*.BIN
	-rm desktop/burgundy/bin/*.BIN
	-rm desktop/blue/bin/*.BIN
	-rm desktop/beige/bin/*.BIN

PHONY := clean-core
clean-core:
# In core/
	-rm core/GRAMADO.VHD
	-rm core/MBR0.BIN
	-rm core/exposed/arctic/bin/*.BIN
	-rm core/exposed/azure/bin/*.BIN
	-rm core/exposed/indigo1/bin/*.BIN
	-rm core/exposed/indigo2/bin/*.BIN
	-rm core/os/newm0/MOD0.BIN
	-rm core/os/kernel/KERNEL.BIN
# Clear the disk cache
	-rm -rf core/os/disk/*.BIN 
	-rm -rf core/os/disk/*.BMP
	-rm -rf core/os/disk/EFI/BOOT/*.EFI 
	-rm -rf core/os/disk/GRAMADO/*.BIN 
	-rm -rf core/os/disk/PROGRAMS/*.BIN 
	-rm -rf core/os/disk/USERS/*.BIN 




