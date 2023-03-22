
# Create BMSHELL.BIN.
# It initializes the bm-shell in 32bit assembly.
# In this shell we can select the graphics mode
# switching back to realmode.
# This was the legacy version of this program.
#

all: asm-stuff cp-stuff clean
	@echo "BMSHELL.BIN OK ?"
asm-stuff:
	nasm main.asm -o BMSHELL.BIN
cp-stuff:
	-cp BMSHELL.BIN ../bin/
clean:
#	find . -type f -name '*.o' -delete
	-rm BMSHELL.BIN
clean2:
	-rm BMSHELL.BIN
	
