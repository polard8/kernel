/*
 * crt0-efi-mips64el.S - PE/COFF header for MIPS64 EFI applications
 *
 * Copright (C) 2014 Linaro Ltd. <ard.biesheuvel@linaro.org>
 * Copright (C) 2017 Heiher <r@hev.cc>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice and this list of conditions, without modification.
 * 2. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License as published by the Free Software Foundation;
 * either version 2 of the License, or (at your option) any later version.
 */

	.section	.text.head

	/*
	 * Magic "MZ" signature for PE/COFF
	 */
	.globl	ImageBase
ImageBase:
	.ascii	"MZ"
	.skip	58				// 'MZ' + pad + offset == 64
	.4byte	pe_header - ImageBase		// Offset to the PE header.
pe_header:
	.ascii	"PE"
	.2byte 	0
coff_header:
	.2byte	0x166				// MIPS little endian
	.2byte	2				// nr_sections
	.4byte	0 				// TimeDateStamp
	.4byte	0				// PointerToSymbolTable
	.4byte	0				// NumberOfSymbols
	.2byte	section_table - optional_header	// SizeOfOptionalHeader
	.2byte	0x206				// Characteristics.
						// IMAGE_FILE_DEBUG_STRIPPED |
						// IMAGE_FILE_EXECUTABLE_IMAGE |
						// IMAGE_FILE_LINE_NUMS_STRIPPED
optional_header:
	.2byte	0x20b				// PE32+ format
	.byte	0x02				// MajorLinkerVersion
	.byte	0x14				// MinorLinkerVersion
	.4byte	_edata - _start			// SizeOfCode
	.4byte	0				// SizeOfInitializedData
	.4byte	0				// SizeOfUninitializedData
	.4byte	_start - ImageBase		// AddressOfEntryPoint
	.4byte	_start - ImageBase		// BaseOfCode

extra_header_fields:
	.8byte	0				// ImageBase
	.4byte	0x20				// SectionAlignment
	.4byte	0x8				// FileAlignment
	.2byte	0				// MajorOperatingSystemVersion
	.2byte	0				// MinorOperatingSystemVersion
	.2byte	0				// MajorImageVersion
	.2byte	0				// MinorImageVersion
	.2byte	0				// MajorSubsystemVersion
	.2byte	0				// MinorSubsystemVersion
	.4byte	0				// Win32VersionValue

	.4byte	_edata - ImageBase		// SizeOfImage

	// Everything before the kernel image is considered part of the header
	.4byte	_start - ImageBase		// SizeOfHeaders
	.4byte	0				// CheckSum
	.2byte	EFI_SUBSYSTEM			// Subsystem
	.2byte	0				// DllCharacteristics
	.8byte	0				// SizeOfStackReserve
	.8byte	0				// SizeOfStackCommit
	.8byte	0				// SizeOfHeapReserve
	.8byte	0				// SizeOfHeapCommit
	.4byte	0				// LoaderFlags
	.4byte	0x10				// NumberOfRvaAndSizes

	.8byte	0				// ExportTable
	.8byte	0				// ImportTable
	.8byte	0				// ResourceTable
	.8byte	0				// ExceptionTable
	.8byte	0				// CertificationTable
	.8byte	0				// BaseRelocationTable
	.8byte	0				// Debug
	.8byte	0				// Architecture
	.8byte	0				// Global Ptr
	.8byte	0				// TLS Table
	.8byte	0				// Load Config Table
	.8byte	0				// Bound Import
	.8byte	0				// IAT
	.8byte	0				// Delay Import Descriptor
	.8byte	0				// CLR Runtime Header
	.8byte	0				// Reserved, must be zero

	// Section table
section_table:

	/*
	 * The EFI application loader requires a relocation section
	 * because EFI applications must be relocatable.  This is a
	 * dummy section as far as we are concerned.
	 */
	.ascii	".reloc"
	.byte	0
	.byte	0			// end of 0 padding of section name
	.4byte	0
	.4byte	0
	.4byte	0			// SizeOfRawData
	.4byte	0			// PointerToRawData
	.4byte	0			// PointerToRelocations
	.4byte	0			// PointerToLineNumbers
	.2byte	0			// NumberOfRelocations
	.2byte	0			// NumberOfLineNumbers
	.4byte	0x42100040		// Characteristics (section flags)


	.ascii	".text"
	.byte	0
	.byte	0
	.byte	0        		// end of 0 padding of section name
	.4byte	_edata - _start		// VirtualSize
	.4byte	_start - ImageBase	// VirtualAddress
	.4byte	_edata - _start		// SizeOfRawData
	.4byte	_start - ImageBase	// PointerToRawData

	.4byte	0		// PointerToRelocations (0 for executables)
	.4byte	0		// PointerToLineNumbers (0 for executables)
	.2byte	0		// NumberOfRelocations  (0 for executables)
	.2byte	0		// NumberOfLineNumbers  (0 for executables)
	.4byte	0xe0500020	// Characteristics (section flags)

	.set		push
	.set		noreorder
	.align		4

	.globl	_start
	.ent	_start
	.type	_start, @function
_start:
	daddiu		$sp, -32
	sd		$ra, ($sp)

	// Get pc & gp
	.align		3
	bal		1f
	sd		$gp, 8($sp)
_pc:
	.dword		_gp
	.dword		_DYNAMIC
	.dword		_relocate
1:
	// pc in ra
	ld		$gp, ($ra)
	dli		$t0, _pc
	dsubu		$gp, $t0
	daddu		$gp, $ra

	sd		$a0, 16($sp)
	sd		$a1, 24($sp)

	// a2: ImageHandle
	move		$a2, $a0
	// a3: SystemTable
	move		$a3, $a1
	// a0: ImageBase
	dli		$t1, ImageBase - _pc
	daddu		$a0, $ra, $t1
	// a1: DynamicSection
	ld		$t1, 8($ra)
	dsubu		$t1, $t0
	daddu		$a1, $ra, $t1
	// call _relocate
	ld		$t1, 16($ra)
	dsubu		$t1, $t0
	daddu		$t9, $ra, $t1
	jalr		$t9
	nop
	bnez		$v0, 1b
	nop

	// a0: ImageHandle
	ld		$a0, 16($sp)
	// call _start
	dla		$t9, _entry
	jalr		$t9
	// a1: SystemTable
	ld		$a1, 24($sp)

1:
	ld		$gp, 8($sp)
	ld		$ra, ($sp)
	jr		$ra
	daddiu		$sp, 32
	.end		_start

	.set		pop

#if defined(__ELF__) && defined(__linux__)
	.section .note.GNU-stack,"",%progbits
#endif
