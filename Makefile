
# Build Gramado OS.

PHONY := all
all: step1-gui step2-havefun step3-kernel
	@echo "Done"

#A15
PHONY := step1-gui
step1-gui:
	make -C  gui

#D8
PHONY := step2-havefun
step2-havefun:
	make -C  havefun

#E25
PHONY := step3-kernel
step3-kernel:
	make -C  kernel

clean-all:
# In gui/
	-rm gui/attitude/bin/*.BIN
	-rm gui/beige/bin/*.BIN
	-rm gui/blue/bin/*.BIN
	-rm gui/burgundy/bin/*.BIN
# In havefun/
	-rm havefun/bin/*.BIN
# In kernel/
	-rm kernel/control/new/KERNEL.BIN
	-rm kernel/control/newm0/MOD0.BIN
	-rm kernel/exposed/arctic/bin/INIT.BIN
