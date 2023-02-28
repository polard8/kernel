#A - Facility II
#desktop
# Gramado DE

PRODUCT_NAME  = Gramado DE
EDITION_NAME  = GUI

VERSION_MAJOR = ?
VERSION_MINOR = ?
VERSION_BUILD = ?

all:

# libs
	make -C libs/rtl
	make -C libs/libgws
	make -C libs/libdisp

# Gramland window server.
	make -C gramland/

# burgundy: Unit 3
	make -C burgundy/client
	make -C burgundy/gdm
	make -C burgundy/setup
# blue: Unit 2
	make -C blue/terminal  
# beige: Unit 1
	make -C beige/cmdline
	make -C beige/editor
	make -C beige/fileman
	make -C beige/browser
	make -C beige/docv

clean-all:
	-rm -f beige/bin/*.BIN
	-rm -f blue/bin/*.BIN
	-rm -f burgundy/bin/*.BIN
	-rm -f gramland/bin/*.BIN
	-rm -f libs/libdisp/obj/*.o
	-rm -f libs/libgws/obj/*.o
	-rm -f libs/rtl/obj/*.o







