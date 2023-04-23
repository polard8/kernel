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
	make -C ventana/libs/rtl/
	make -C ventana/libs/libgws/
	make -C ventana/libs/libdisp/
	make -C ventana/libs/libgr/
	make -C ventana/libs/libgr3d/

# ----------------
# Gramland window server.
	make -C ventana/gramland/

# ----------------
# Shell

# apps: Unit 3
	make -C ventana/apps/client
	make -C ventana/apps/gdm
	make -C ventana/apps/setup
# apps: Unit 2
	make -C ventana/apps/terminal  
# apps: Unit 1
	make -C ventana/apps/cmdline
	make -C ventana/apps/editor
	make -C ventana/apps/browser
	make -C ventana/apps/docv

# ----------------
# demos/

# Graphics engine. (3D demos)
	make -C demos/eng/

clean-all:
	-rm -f demos/eng/bin/*.BIN
	-rm -f ventana/gramland/bin/*.BIN
	-rm -f ventana/apps/bin/*.BIN
	-rm -f ventana/libs/libgws/obj/*.o
	-rm -f ventana/libs/libgr/obj/*.o
	-rm -f ventana/libs/libgr3d/obj/*.o
	-rm -f ventana/libs/libdisp/obj/*.o
	-rm -f ventana/libs/rtl/obj/*.o
	








