all:

# The libs for ring3
	make -C libs/
#	make -C toolkits/

# The init process
	make -C init/

# Shells
	make -C pubsh/
	make -C sh7/
	make -C shell/
#	make -C shell00/

	make -C tascii/
	make -C tprintf/

# FTP server
#	make -C ftpd/client/
	make -C ftpd/server/

# Network server
	make -C netd/client/ 
	make -C netd/server/

# Telnet server
#	make -C telnetd/client/
	make -C telnetd/server/

# VGA driver
#	make -C vgad/client/
	make -C vgad/server/

# Web server
#	make -C webd/client/
	make -C webd/server/

# ...

clean:
	-rm -f *.o
	-rm -f bin/*.BIN

clean-all:
	-rm -f *.o
	-rm -f bin/*.BIN

	-rm -f libs/libgns/obj/*.o
	-rm -f libs/rtl/obj/*.o
#	-rm -f toolkits/*.o

	-rm -f init/*.o

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

