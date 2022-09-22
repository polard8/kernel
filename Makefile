
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


