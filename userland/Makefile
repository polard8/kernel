all:

# The libs for ring3
	make -C libs/
# The init process
	make -C init/

#	make -C drivers/
#	make -C servers/

# The Gramado Network Server and the first client
	make -C netd/server/
	make -C netd/client/ 


clean:
	-rm -f libs/libgns/obj/*.o
	-rm -f libs/rtl/obj/*.o

	-rm -f init/*.o

	-rm -f netd/server/*.o
	-rm -f netd/client/*.o

	-rm -f bin/*.BIN

