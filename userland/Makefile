all:

# The libs for ring3
	make -C core00/libs/
#	make -C core00/toolkits/

# The init process
	make -C core01/init/

# Shells
	make -C core02/pubsh/
	make -C core02/sh7/
	make -C core02/shell/
#	make -C core02/shell00/

	make -C core03/tascii/
	make -C core03/tprintf/

# FTP server
#	make -C ftpd/client/
#	make -C ftpd/server/

# Network server
#	make -C netd/client/ 
#	make -C netd/server/

# Telnet server
#	make -C telnetd/client/
#	make -C telnetd/server/

# VGA driver
#	make -C vgad/client/
	make -C vgad/server/

# Web server
#	make -C webd/client/
#	make -C webd/server/
# ...

clean:
	-rm -f *.o
	-rm -f bin/*.BIN
clean-all:
	-rm -f *.o
	-rm -f bin/*.BIN

	-rm -f core00/libs/libgns/obj/*.o
	-rm -f core00/libs/rtl/obj/*.o
#	-rm -f core00/toolkits/*.o

	-rm -f core01/init/*.o

#	-rm -f core02/*.o

#	-rm -f core03/*.o

#	-rm -f ftpd/server/*.o
#	-rm -f ftpd/client/*.o

#	-rm -f netd/server/*.o
#	-rm -f netd/client/*.o

#	-rm -f telnetd/server/*.o
#	-rm -f telnetd/client/*.o

	-rm -f vgad/server/*.o
	-rm -f vgad/client/*.o

#	-rm -f webd/server/*.o
#	-rm -f webd/client/*.o

# ...
