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
# burgundy
	make -C burgundy/server
	make -C burgundy/client
	make -C burgundy/gdm
# blue
	make -C blue/terminal  
# beige
	make -C beige/cmdline
	make -C beige/editor
	make -C beige/fileman
	make -C beige/setup
# attitude
	make -C attitude/browser

clean-all:

	-rm -f attitude/bin/*.BIN
	-rm -f beige/bin/*.BIN
	-rm -f blue/bin/*.BIN
	-rm -f burgundy/bin/*.BIN
	-rm -f libs/libgd/obj/*.o
	-rm -f libs/libgws/obj/*.o
	-rm -f libs/rtl/obj/*.o







