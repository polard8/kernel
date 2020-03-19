
Discarded input sections

 .note.GNU-stack
                0x0000000000000000        0x0 socrt0.o
 .eh_frame      0x0000000000000000       0x38 socrt0.o
 .note.GNU-stack
                0x0000000000000000        0x0 somain.o
 .eh_frame      0x0000000000000000       0x38 somain.o

Memory Configuration

Name             Origin             Length             Attributes
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map

LOAD socrt0.o
LOAD somain.o
                0x0000000000000000                . = 0x0
                0x0000000000000000                ImageBase = .

.hash           0x0000000000000000       0x3c
 *(.hash)
 .hash          0x0000000000000000       0x3c socrt0.o

.gnu.hash       0x000000000000003c       0x48
 *(.gnu.hash)
 .gnu.hash      0x000000000000003c       0x48 socrt0.o
                0x0000000000001000                . = ALIGN (0x1000)

.text           0x0000000000001000       0x10
                0x0000000000001000                _text = .
 *(.text)
 .text          0x0000000000001000        0x6 socrt0.o
                0x0000000000001000                socrt0
 .text          0x0000000000001006        0x6 somain.o
                0x0000000000001006                somain
 *(.text.*)
 *(.gnu.linkonce.t.*)
                0x0000000000001010                . = ALIGN (0x10)
 *fill*         0x000000000000100c        0x4 
                0x0000000000001010                _etext = .
                0x0000000000000010                _text_size = (. - _text)

.plt            0x0000000000001010        0x0
 .plt           0x0000000000001010        0x0 socrt0.o

.plt.got        0x0000000000001010        0x0
 .plt.got       0x0000000000001010        0x0 socrt0.o
                0x0000000000002000                . = ALIGN (0x1000)

.sdata          0x0000000000002000        0x0
                0x0000000000002000                _data = .
 *(.got.plt)
 .got.plt       0x0000000000002000        0x0 socrt0.o
 *(.got)
 .got           0x0000000000002000        0x0 socrt0.o
 *(.srodata)
 *(.sdata)
 *(.sbss)
 *(.scommon)
                0x0000000000002000                . = ALIGN (0x1000)

.data           0x0000000000002000        0x0
 *(.rodata*)
 *(.data)
 .data          0x0000000000002000        0x0 socrt0.o
 .data          0x0000000000002000        0x0 somain.o
 *(.data1)
 *(.data.*)
 .data.rel.ro   0x0000000000002000        0x0 socrt0.o
 *(.sdata)
 *(.got.plt)
 *(.got)
 *(.sbss)
 *(.scommon)
 *(.dynbss)
 .dynbss        0x0000000000002000        0x0 socrt0.o
 *(.bss)
 .bss           0x0000000000002000        0x0 socrt0.o
 .bss           0x0000000000002000        0x0 somain.o
 *(COMMON)

.note.gnu.build-id
 *(.note.gnu.build-id)
                0x0000000000002000                . = ALIGN (0x1000)

.dynamic        0x0000000000002000       0x70
 *(.dynamic)
 .dynamic       0x0000000000002000       0x70 socrt0.o
                0x0000000000002000                _DYNAMIC
                0x0000000000003000                . = ALIGN (0x1000)

.rel            0x0000000000003000        0x0
 *(.rel.data)
 *(.rel.data.*)
 *(.rel.got)
 .rel.got       0x0000000000003000        0x0 socrt0.o
 *(.rel.stab)
 *(.data.rel.ro.local)
 *(.data.rel.local)
 *(.data.rel.ro)
 *(.data.rel*)
                0x0000000000003000                _edata = .
                0x0000000000001ff0                _data_size = (. - _etext)

.rel.plt        0x0000000000003000        0x0
 .rel.plt       0x0000000000003000        0x0 socrt0.o

.rel.ifunc      0x0000000000003000        0x0
 .rel.ifunc     0x0000000000003000        0x0 socrt0.o
                0x0000000000003000                . = ALIGN (0x1000)

.reloc
 *(.reloc)
                0x0000000000003000                . = ALIGN (0x1000)

.dynsym         0x0000000000003000       0xa0
 *(.dynsym)
 .dynsym        0x0000000000003000       0xa0 socrt0.o
                0x0000000000004000                . = ALIGN (0x1000)

.dynstr         0x0000000000004000       0x49
 *(.dynstr)
 .dynstr        0x0000000000004000       0x49 socrt0.o

.gnu.version_d  0x000000000000404c        0x0
 .gnu.version_d
                0x000000000000404c        0x0 socrt0.o

.gnu.version    0x000000000000404a        0x0
 .gnu.version   0x000000000000404a        0x0 socrt0.o

.gnu.version_r  0x000000000000404c        0x0
 .gnu.version_r
                0x000000000000404c        0x0 socrt0.o
                0x0000000000005000                . = ALIGN (0x1000)

/DISCARD/
 *(.rel.reloc)
 *(.eh_frame)
 *(.note.GNU-stack)

.comment        0x0000000000000000       0x29
 *(.comment)
 .comment       0x0000000000000000       0x29 socrt0.o
                                         0x2a (size before relaxing)
 .comment       0x0000000000000029       0x2a somain.o
LOAD ./LIBC03.A
OUTPUT(LIBC03.SO elf32-i386)
