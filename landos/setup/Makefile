
# history:
# Deleting all the apps the creates windows using the
# kgws resources.

all: 

	# the library.
	make -C libcore

	# These apps do not create windows.
	make -C gdeshell
	make -C c4
	make -C gramc
	make -C gramc4
	make -C gramcnf

	# Clean libcore
	-rm -rf libcore/obj/*.o
	
