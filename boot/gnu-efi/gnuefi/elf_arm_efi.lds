OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
  .text 0 : {
    *(.text.head)
    _text = .;
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
    *(.plt)
    . = ALIGN(16);
    _evtext = .;
    . = ALIGN(4096);
    _etext = .;
  } =0
  _text_vsize = _evtext - _text;
  _text_size = _etext - _text;
  . = ALIGN(4096);
  _reloc = .;
  .areloc : {
    *(.areloc)
    _evreloc = .;
    . = ALIGN(4096);
    _ereloc = .;
  } =0
  _reloc_vsize = _evreloc - _reloc;
  _reloc_size = _ereloc - _reloc;
  . = ALIGN(65536);
  _data = .;
  .dynamic  : { *(.dynamic) }
  . = ALIGN(4096);
  .data :
  {
   *(.sdata)
   *(.data)
   *(.data1)
   *(.data.*)
   *(.got.plt)
   *(.got)

   /*
    * Note that these aren't the using the GNU "CONSTRUCTOR" output section
    * command, so they don't start with a size.  Because of p2align and the
    * end/END definitions, and the fact that they're mergeable, they can also
    * have NULLs which aren't guaranteed to be at the end.
    */
   . = ALIGN(16);
   __init_array_start = .;
   *(SORT(.init_array.*))
   *(.init_array)
   __init_array_end = .;
  . = ALIGN(16);
   __CTOR_LIST__ = .;
   *(SORT(.ctors.*))
   *(.ctors)
   __CTOR_END__ = .;
  . = ALIGN(16);
   __DTOR_LIST__ = .;
   *(SORT(.dtors.*))
   *(.dtors)
   __DTOR_END__ = .;
   . = ALIGN(16);
   __fini_array_start = .;
   *(SORT(.fini_array.*))
   *(.fini_array)
   __fini_array_end = .;

   /* the EFI loader doesn't seem to like a .bss section, so we stick
      it all into .data: */
   . = ALIGN(16);
   _bss = .;
   *(.sbss)
   *(.scommon)
   *(.dynbss)
   *(.bss)
   *(.bss.*)
   *(COMMON)
   . = ALIGN(16);
   _bss_end = .;
   _evdata = .;
   . = ALIGN(4096);
   _edata = .;
  } =0
  _data_vsize = _evdata - _data;
  _data_size = _edata - _data;

  . = ALIGN(4096);
  _rodata = .;
  .rel :
  {
    *(.rel.text*)
    *(.rel.data*)
    *(.rel.got)
    *(.rel.dyn)
    *(.rel.stab)
    *(.rel.init_array*)
    *(.rel.fini_array*)
    *(.rel.ctors*)
    *(.rel.dtors*)

  }
  . = ALIGN(4096);
  .rel.plt : { *(.rel.plt) }
  . = ALIGN(4096);
  .rodata : {
    *(.rodata*)
    _evrodata = .;
    . = ALIGN(4096);
    _erodata = .;
  } =0
  _rodata_vsize = _evrodata - _rodata;
  _rodata_size = _erodata - _rodata;
  _image_end = .;
  _alldata_size = _image_end - _reloc;

  . = ALIGN(4096);
  .dynsym   : { *(.dynsym) }
  . = ALIGN(4096);
  .dynstr   : { *(.dynstr) }
  . = ALIGN(4096);
  .note.gnu.build-id : { *(.note.gnu.build-id) }
  . = ALIGN(4096);
  .hash : { *(.hash) }
  . = ALIGN(4096);
  .gnu.hash : { *(.gnu.hash) }
  . = ALIGN(4096);
  .ARM.exidx : { *(.ARM.exidx*) }
  .ARM.extab : { *(.ARM.extab*) }
  /DISCARD/ :
  {
    *(.rel.areloc)
    *(.note.GNU-stack)
  }
  .comment 0 : { *(.comment) }
}
