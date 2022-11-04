
# Build Gramado OS.

PHONY := all
all: step1-games step2-gui step3-kernel
	@echo "Done"

#D8
PHONY := step1-games
step1-games:
	make -C  games

#A15
PHONY := step2-gui
step2-gui:
	make -C  gui

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
# In games/
	-rm games/bin/*.BIN
# In kernel/
	-rm kernel/control/new/KERNEL.BIN
	-rm kernel/control/newm0/MOD0.BIN
	-rm kernel/exposed/arctic/bin/INIT.BIN
