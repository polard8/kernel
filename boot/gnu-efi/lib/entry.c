/*
 * ctors.c
 * Copyright 2019 Peter Jones <pjones@redhat.com>
 *
 */

#include <efi.h>
#include <efilib.h>

typedef void (*funcp)(void);

/*
 * Note that these aren't the using the GNU "CONSTRUCTOR" output section
 * command, so they don't start with a size.  Because of p2align and the
 * end/END definitions, and the fact that they're mergeable, they can also
 * have NULLs which aren't guaranteed to be at the end.
 */
extern funcp __init_array_start[], __init_array_end[];
extern funcp __CTOR_LIST__[], __CTOR_END__[];
extern funcp __fini_array_start[], __fini_array_end[];
extern funcp __DTOR_LIST__[], __DTOR_END__[];

static void ctors(void)
{
	size_t __init_array_length = __init_array_end - __init_array_start;
	for (size_t i = 0; i < __init_array_length; i++) {
		funcp func = __init_array_start[i];
		if (func != NULL)
			func();
	}

	size_t __CTOR_length = __CTOR_END__ - __CTOR_LIST__;
	for (size_t i = 0; i < __CTOR_length; i++) {
		size_t current = __CTOR_length - i - 1;
		funcp func = __CTOR_LIST__[current];
		if (func != NULL)
			func();
	}
}

static void dtors(void)
{
	size_t __DTOR_length = __DTOR_END__ - __DTOR_LIST__;
	for (size_t i = 0; i < __DTOR_length; i++) {
		funcp func = __DTOR_LIST__[i];
		if (func != NULL)
			func();
	}

	size_t __fini_array_length = __fini_array_end - __fini_array_start;
	for (size_t i = 0; i < __fini_array_length; i++) {
		size_t current = __fini_array_length - i - 1;
		funcp func = __fini_array_start[current];
		if (func != NULL)
			func();
	}
}

extern EFI_STATUS efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *systab);

EFI_STATUS _entry(EFI_HANDLE image, EFI_SYSTEM_TABLE *systab)
{
	EFI_STATUS status;
	InitializeLib(image, systab);

	ctors();
	status = efi_main(image, systab);
	dtors();

	return status;
}

// vim:fenc=utf-8:tw=75:noet
