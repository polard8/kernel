
# Build Gramado OS.

PHONY := all
all: step1-meta step2-desktop step3-core
	@echo "Done"

#D8
PHONY := step1-meta
step1-meta:
	make -C  meta

#A15
PHONY := step2-desktop
step2-desktop:
	make -C  desktop

#E25
PHONY := step3-core
step3-core:
	make -C  core


PHONY := clean
clean: clean-all

PHONY := clean-all
clean-all: clean-meta clean-desktop clean-core

PHONY := clean-meta
clean-meta:
# In meta/
	-rm meta/bin/*.BIN

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
	-rm core/exposed/arctic/bin/*.BIN
	-rm core/exposed/azure/bin/*.BIN
	-rm core/exposed/indigo1/bin/*.BIN
	-rm core/exposed/indigo2/bin/*.BIN
	-rm core/control/newm0/MOD0.BIN
	-rm core/control/new/KERNEL.BIN
# Clear the disk cache
	-rm -rf core/control/disk/*.BIN 
	-rm -rf core/control/disk/*.BMP
	-rm -rf core/control/disk/EFI/BOOT/*.EFI 
	-rm -rf core/control/disk/GRAMADO/*.BIN 
	-rm -rf core/control/disk/PROGRAMS/*.BIN 
	-rm -rf core/control/disk/USERS/*.BIN 




