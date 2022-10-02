#D8 - Facility III
#havefun 
#codename: "Because the biggest challenge for the creator is boredom" - (T. Davis)

PHONY := all
all:
	make -C libs/rtl
	make -C libs/libgws
	make -C libs/libgd

# gramado game engine.
	make -C game1

clean-all:
	-rm -f libs/libgd/obj/*.o
	-rm -f libs/libgws/obj/*.o
	-rm -f libs/rtl/obj/*.o

	-rm game1/*.o

	-rm bin/*.BIN
	



