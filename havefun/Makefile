#D8 - Facility III
#havefun 
#codename: "Because the biggest challenge for the creator is boredom" - (T. Davis)

PHONY := all
all:
	make -C libs/rtl
	make -C libs/libgws
	make -C libs/libgd
	make -C demo1
	make -C demo2
	make -C game1
	make -C game2
	
clean-all:
	-rm -f libs/libgd/obj/*.o
	-rm -f libs/libgws/obj/*.o
	-rm -f libs/rtl/obj/*.o
	-rm bin/*.BIN
	



