#D8 - Facility III
#meta
# Games
#codename: "Because the biggest challenge for the creator is boredom" - (T. Davis)

PRODUCT_NAME  = Gramado Games
EDITION_NAME  = ?

VERSION_MAJOR = ?
VERSION_MINOR = ?
VERSION_BUILD = ?

PHONY := all
all:
	make -C libs/rtl
	make -C libs/libgws
	make -C libs/libdisp

# Gramado game engine.
	make -C game1

clean-all:
	-rm -f libs/libdisp/obj/*.o
	-rm -f libs/libgws/obj/*.o
	-rm -f libs/rtl/obj/*.o
	-rm game1/*.o
	-rm bin/*.BIN
	



