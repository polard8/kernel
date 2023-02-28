
# Build Gramado OS.

PHONY := all
all: step1-meta step2-gramland step3-base
	@echo "Done"

#D8
PHONY := step1-meta
step1-meta:
	make -C  meta

#A15
PHONY := step2-gramland
step2-gramland:
	make -C  gramland

#E25
PHONY := step3-base
step3-base:
	make -C  base


PHONY := clean
clean: clean-all

PHONY := clean-all
clean-all: clean-meta clean-gramland clean-base

PHONY := clean-meta
clean-meta:
# In meta/
	-rm meta/bin/*.BIN

PHONY := clean-gramland
clean-gramland:
# In gramland/
	-rm gramland/burgundy/bin/*.BIN
	-rm gramland/blue/bin/*.BIN
	-rm gramland/beige/bin/*.BIN

PHONY := clean-base
clean-base:
# In base/
	-rm base/exposed/arctic/bin/*.BIN
	-rm base/exposed/azure/bin/*.BIN
	-rm base/exposed/indigo1/bin/*.BIN
	-rm base/exposed/indigo2/bin/*.BIN
	-rm base/control/newm0/MOD0.BIN
	-rm base/control/new/KERNEL.BIN
# Clear the disk cache
	-rm -rf base/control/disk/*.BIN 
	-rm -rf base/control/disk/*.BMP
	-rm -rf base/control/disk/EFI/BOOT/*.EFI 
	-rm -rf base/control/disk/GRAMADO/*.BIN 
	-rm -rf base/control/disk/PROGRAMS/*.BIN 
	-rm -rf base/control/disk/USERS/*.BIN 




