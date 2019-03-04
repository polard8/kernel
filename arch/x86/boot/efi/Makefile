
#obs:
#Tentando entender a compilação de uma aplicação efi de 32bit.
#Isso é um teste. É uma adaptação de um exmplo para 32bit. Pode estar errado.


all: main-file copy-libs ld-stuff objcopy-stuff

main-file:
	gcc -m32 main.c                           \
      -c                                 \
      -fno-stack-protector               \
      -fpic                              \
      -fshort-wchar                      \
      -mno-red-zone                      \
      -I gnuefi/inc        \
      -I gnuefi/inc/ia32 \
      -DEFI_FUNCTION_WRAPPER             \
      -o main.o
	  
	  
copy-libs:
	cp gnuefi/ia32/lib/libefi.a           gnuefi/obj
	cp gnuefi/ia32/gnuefi/libgnuefi.a     gnuefi/obj
	cp gnuefi/ia32/gnuefi/crt0-efi-ia32.o gnuefi/obj
	cp gnuefi/ia32/lib/libefi.a           .
	cp gnuefi/ia32/gnuefi/libgnuefi.a     .
	cp gnuefi/ia32/gnuefi/crt0-efi-ia32.o .
 
ld-stuff:
	ld -m elf_i386 main.o                           \
      gnuefi/gnuefi/crt0-efi-ia32.o     \
     -nostdlib                      \
     -T gnuefi/gnuefi/elf_ia32_efi.lds \
     -shared                        \
     -znocombreloc                  \
     -Bsymbolic                     \
     -L gnuefi/obj               \
     -l:libgnuefi.a                 \
     -l:libefi.a                    \
     -o main.so
 
objcopy-stuff:
	objcopy -j .text                \
          -j .sdata               \
          -j .data                \
          -j .dynamic             \
          -j .dynsym              \
          -j .rel                 \
          -j .rela                \
          -j .reloc               \
          --target=efi-app-ia32   \
          main.so                 \
          BOOTIA32.EFI
		  
  
		  