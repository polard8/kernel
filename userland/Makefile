all:

# The libs for ring3
	make -C core/libs/
# The init process
	make -C core/userinit/

#	make -C ftpd/client/
	make -C ftpd/server/

# The Gramado Network Server and the first client
	make -C netd/client/ 
	make -C netd/server/

#	make -C telnetd/client/
	make -C telnetd/server/

#	make -C vgad/client/
	make -C vgad/server/

#	make -C webd/client/
	make -C webd/server/

clean:
	-rm -f *.o
	-rm -f bin/*.BIN
clean-all:
	-rm -f *.o
	-rm -f bin/*.BIN

	-rm -f core/libs/libgns/obj/*.o
	-rm -f core/libs/rtl/obj/*.o
	-rm -f core/userinit/*.o

	-rm -f ftpd/server/*.o
	-rm -f ftpd/client/*.o

	-rm -f netd/server/*.o
	-rm -f netd/client/*.o

	-rm -f telnetd/server/*.o
	-rm -f telnetd/client/*.o

	-rm -f vgad/server/*.o
	-rm -f vgad/client/*.o

	-rm -f webd/server/*.o
	-rm -f webd/client/*.o


# ...
