all:

	make -C libs/

# The init process
	make -C init/

# The Gramado Network Server
	make -C hvnetd/server/
# First client for GNS.
	make -C hvnetd/client/ 
	
clean:
	-rm -f libs/libgns/obj/*.o
	-rm -f libs/rtl/obj/*.o

	-rm -f init/*.o

	-rm -f hvnetd/server/*.o
	-rm -f hvnetd/client/*.o

	-rm -f bin/*.BIN

