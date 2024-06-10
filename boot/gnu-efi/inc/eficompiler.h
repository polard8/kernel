/*++

Copyright (c) 2016 Pete Batard <pete@akeo.ie>

Module Name:

    eficompiler.h

Abstract:

    Compiler specific adjustments

--*/

#ifdef _MSC_EXTENSIONS
#define EFI_UNUSED
#else
#define EFI_UNUSED __attribute__((__unused__))
#endif

#ifdef _MSC_EXTENSIONS
#define EFI_NO_TAIL_CALL
#else
#ifdef __clang__
#define EFI_NO_TAIL_CALL __attribute__((disable_tail_calls))
#else
#define EFI_NO_TAIL_CALL __attribute__((optimize("no-optimize-sibling-calls")))
#endif
#endif

#ifdef _MSC_EXTENSIONS
#define EFI_OPTNONE
#else
#ifdef __clang__
#define EFI_OPTNONE __attribute__((optnone))
#else
#define EFI_OPTNONE __attribute__((__optimize__("0")))
#endif
#endif

#ifdef _MSC_EXTENSIONS
#define ALIGN(x) __declspec(align(x))
#else
#define ALIGN(x) __attribute__((__aligned__(x)))
#endif

/* Also add a catch-all on __attribute__() for MS compilers */
#ifdef _MSC_EXTENSIONS
#define __attribute__(x)
#endif
