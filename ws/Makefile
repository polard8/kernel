all:

# client-side library
	make -C libgws

# The window server and the main client
	make -C server    
	make -C client    

# clients
	make -C gwm
	make -C logon
	make -C editor
	make -C fileman
	make -C terminal  
	make -C browser


# clean the lib
	-rm -rf libgws/obj/*.o
