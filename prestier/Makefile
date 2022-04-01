
# This file builds all the components in gramado/ folder.

all:

# client-side library
	make -C gws/libgws

# Gramado Core
# 'Final' game engine
# This is the end of the system initialization. No apps.
# The window server and the main client
	make -C gws/client
	make -C gws/server

# Gramado shell
# Extra stuff. Aps after system initialization.
	make -C gws/browser
	make -C gws/cmdline
	make -C gws/editor
	make -C gws/fileman
	make -C gws/logon    
	make -C gws/setup
	make -C gws/terminal  

# Gramado userland
    #make -C userland

# Clean libraries
	-rm -rf final/gws/obj/*.o
