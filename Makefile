
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

clean-all:
# In gramland/
	-rm gramland/attitude/bin/*.BIN
	-rm gramland/beige/bin/*.BIN
	-rm gramland/blue/bin/*.BIN
	-rm gramland/burgundy/bin/*.BIN
# In meta/
	-rm meta/bin/*.BIN
# In base/
	-rm base/control/new/KERNEL.BIN
	-rm base/control/newm0/MOD0.BIN
	-rm base/exposed/arctic/bin/INIT.BIN



