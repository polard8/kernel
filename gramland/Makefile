#A - Facility II
#gramland
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
	make -C libs/libgd

# burgundy: Unit 3
	make -C burgundy/server
	make -C burgundy/client
	make -C burgundy/gdm
# blue: Unit 2
	make -C blue/terminal  
# beige: Unit 1
	make -C beige/cmdline
	make -C beige/editor
	make -C beige/fileman
	make -C beige/setup
	make -C beige/browser
	make -C beige/docv

clean-all:
	-rm -f beige/bin/*.BIN
	-rm -f blue/bin/*.BIN
	-rm -f burgundy/bin/*.BIN
	-rm -f libs/libgd/obj/*.o
	-rm -f libs/libgws/obj/*.o
	-rm -f libs/rtl/obj/*.o







