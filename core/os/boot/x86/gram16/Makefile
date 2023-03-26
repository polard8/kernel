
# Create BM.BIN.
# No shell.
# This is faster version of the boot manager.
# It initializes the pre-selected graphics mode
# and jumps into the BL.BIN.

all: asm-stuff cp-stuff clean
	@echo "GRAM16.BIN OK ?"
asm-stuff:
	nasm g16load.asm -o G16LOAD.BIN
	nasm g16kern.asm -o G16KERN.BIN
cp-stuff:
	-cp G16LOAD.BIN ../bin/
	-cp G16KERN.BIN ../bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm G16LOAD.BIN
	-rm G16KERN.BIN
clean2:
	-rm G16LOAD.BIN
	-rm G16KERN.BIN
