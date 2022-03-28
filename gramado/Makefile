
# This file builds all the components in gramado/ folder.

all:

# client-side library
	make -C libgws

# Gramado Core
# The window server and the main client
	make -C core/cmdline
	make -C core/client
	make -C core/server

# Gramado setup
	make -C setup/client

# Gramado logon
	make -C logon/client    

# Gramado shell
	make -C shell/browser
	make -C shell/editor
	make -C shell/fileman
	make -C shell/terminal  

# Gramado userland
    #make -C userland


# Clean libraries
	-rm -rf libgws/obj/*.o
