
# This file builds all the components in gramado/ folder.

all:

# client-side library
	make -C libgws

# Gramado Core
# 'Final' game engine
# This is the end of the system initialization. No apps.
# The window server and the main client
	make -C final/client
	make -C final/server

# Gramado shell
# Extra stuff. Aps after system initialization.
	make -C extra/browser
	make -C extra/cmdline
	make -C extra/editor
	make -C extra/fileman
	make -C extra/logon    
	make -C extra/setup
	make -C extra/terminal  


# Gramado userland
    #make -C userland


# Clean libraries
	-rm -rf libgws/obj/*.o
