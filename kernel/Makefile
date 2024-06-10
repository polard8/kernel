
# Makefile for the Gramado kernel.

# Tools
include kctl/arch/x86_64/makeinc

linkTarget = KERNEL.BIN

# See: https://linux.die.net/man/1/ld
# -s --strip-all:   Omit all symbol information from the output file.
# -x --discard-all: Delete all local symbols.
# -static: Do not link against shared libraries. 
# -T scriptfile

linkFlags := -m elf_x86_64 \
-s \
-x \
-static \
-T kctl/arch/x86_64/link.ld   

#
# Config
#

# Quit mode?
ifndef CONFIG_USE_VERBOSE
	CONFIG_USE_VERBOSE = 0
endif

# ' ' = Print
# '@' = Do not print.
ifeq ($(CONFIG_USE_VERBOSE),1)
	Q =
else
	Q = @
endif

# test: gramado 64bit
# See: https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html
CFLAGS := \
	-Wall \
	-Wundef \
	-Wmissing-prototypes \
	-Wno-uninitialized \
	-Wno-format-security \
	-Wno-trigraphs \
	-Werror=strict-prototypes \
	-Werror=implicit-function-declaration \
	-Werror=implicit-int \
	-Werror=return-type \
	-std=gnu89 \
	-m64 \
	-s \
	-static \
	-fcommon \
	-fgnu89-inline \
	-finline-functions \
	-fshort-wchar \
	-ffreestanding \
	-fleading-underscore \
	-fstrict-overflow \
	-nostdlib \
	-nodefaultlibs \
	-nostdinc \
	-fno-builtin \
	-fno-stack-protector \
	-fno-strict-aliasing \
	-fno-PIE \
	-fno-pie \
	-fno-omit-frame-pointer \
	-fno-optimize-sibling-calls    


# ========================
# Config

#test
#CONFIG_MAIN=y
# ...

# ========================
# Objects

# ========================
# :: kctl - Resource controllers.
objects-y := head_64.o 
objects-y += ar_crt.o  
#objects-y += ar_mod.o  
objects-y += ar_zcall.o

# ========================
# :: kres - Kernel resources
objects-y += ar_dev.o  
objects-y += ar_fs.o  
objects-y += ar_gramk.o  
objects-y += ar_ke.o  
objects-y += ar_mm.o  
objects-y += ar_net.o    

# ========================
PHONY := all
all: k1 k2 \
link-kernel \
clean    

	@echo "Done?"

#----------------
# Resource controllers.
k1:
	@echo "Compiling: Compiling k1"
# Kernel arch - Startup and entry code.
	$(MAKE) -C kctl/arch/x86_64/
# Kernel core - Top level routines.
	$(MAKE) -C kctl/core/

#----------------
# Kernel resources
k2:
	@echo "Compiling: Compiling k2"
	$(MAKE) -C lib/
	$(MAKE) -C kres/dev/
	$(MAKE) -C kres/fs/
	$(MAKE) -C kres/gramk/
	$(MAKE) -C kres/ke/
	$(MAKE) -C kres/mm/
	$(MAKE) -C kres/net/

#----------------
link-kernel:
	@echo "Linking: Linking the kernel image ..."
	$(LD) $(linkFlags) -o $(linkTarget) $(objects-y)    
clean:
	rm -rf *.o   
	@echo "~clean"
clean-all:
	rm -rf *.o   
	rm -rf *.BIN   
	@echo "~clean-all"




