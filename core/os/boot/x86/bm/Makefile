
# Create BM.BIN.
# No shell.
# This is faster version of the boot manager.
# It initializes the pre-selected graphics mode
# and jumps into the BL.BIN.

all: asm-stuff cp-stuff clean
	@echo "BM.BIN OK ?"
asm-stuff:
	nasm main.asm -o BM.BIN
cp-stuff:
	-cp BM.BIN ../bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm BM.BIN
clean2:
	-rm BM.BIN
	
