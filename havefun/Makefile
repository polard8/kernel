#D8 - Facility III
#havefun 
#codename: "Because the biggest challenge for the creator is boredom" - (T. Davis)

PHONY := all
all:
	make -C libs/rtl
	make -C libs/libgws
	make -C libs/libgd

	make -C eng1
	make -C eng2
	make -C eng3
	make -C eng4
# gramado game engine.
	make -C eng5

	make -C demos

clean-all:
	-rm -f libs/libgd/obj/*.o
	-rm -f libs/libgws/obj/*.o
	-rm -f libs/rtl/obj/*.o

	-rm eng1/*.o
	-rm eng2/*.o
	-rm eng3/*.o
	-rm eng4/*.o

	-rm eng5/*.o

	-rm bin/*.BIN
	



