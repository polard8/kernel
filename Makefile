
# Build Gramado OS.

PHONY := all
all: step3-havefun step2-gui step1-base
	@echo "Done"


PHONY := step3-havefun
step3-havefun:
	make -C  havefun

PHONY := step2-gui
step2-gui:
	make -C  gui

PHONY := step1-base
step1-base:
	make -C  base

clean-all:
# In base/
	-rm base/control/new/KERNEL.BIN
	-rm base/control/newm0/MOD0.BIN
	-rm base/exposed/arctic/bin/INIT.BIN
# In gui/
	-rm gui/attitude/bin/*.BIN
	-rm gui/beige/bin/*.BIN
	-rm gui/blue/bin/*.BIN
	-rm gui/burgundy/bin/*.BIN
# In havefun/
	-rm havefun/bin/*.BIN

