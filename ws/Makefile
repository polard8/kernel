all:

# client-side library
	make -C libgws

# The window server and the main client
	make -C server    
	make -C client    

# clients

# Well tested clients
	make -C editor
	make -C fileman
	make -C gwm
	make -C terminal  

# Extra clients
	make -C browser


# clean the lib
	-rm -rf libgws/obj/*.o
