
#todo

all: asm-stuff cp-stuff clean
	@echo "taokay?"

asm-stuff:
	nasm -I stage1/ \
	-I stage2/ \
	-I stage2/include/ \
	-I stage2/lib16/ \
	-I stage3/ \
	-I stage3/drivers/ \
	-I stage3/fs/ \
	-I stage3/include/ \
	-I stage3/kernel/ \
	-I stage3/lib32/ \
	-I stage3/shell/  main.asm  -o  BM.BIN


cp-stuff:
	-cp BM.BIN ../../../../bin/


clean:
	-rm BM.BIN
	
	
