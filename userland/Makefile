all:

# The libs for ring3
	make -C core/libs/
# The init process
	make -C core/userinit/

# The Gramado Network Server and the first client
	make -C netd/server/
	make -C netd/client/ 

#	make -C vgad/server/
#	make -C vgad/client/

#	make -C ftpd/server/
#	make -C ftpd/client/

#	make -C telned/server/
#	make -C telned/client/

#	make -C webd/server/
#	make -C webd/client/

clean:
	-rm -f *.o
	-rm -f bin/*.BIN
clean-all:
	-rm -f *.o
	-rm -f bin/*.BIN

	-rm -f core/libs/libgns/obj/*.o
	-rm -f core/libs/rtl/obj/*.o
	-rm -f core/userinit/*.o

	-rm -f netd/server/*.o
	-rm -f netd/client/*.o

# ...
