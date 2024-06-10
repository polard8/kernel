#include <efi.h>
#include <efilib.h>

// 101 in init_array, 65434 in ctors
static void __attribute__((constructor(101))) EFI_NO_TAIL_CALL ctors101() {
    Print(L"1) ctor with lower numbered priority \r\n");
}

// 65434 in init_array, 101 in ctors
static void __attribute__((constructor(65434))) EFI_NO_TAIL_CALL ctors65434() {
    Print(L"2) ctor with higher numbered priority \r\n");
}

// 101 in fini_array, 65434 in dtors
static void __attribute__((destructor(101))) EFI_NO_TAIL_CALL dtors101() {
    Print(L"4) dtor with lower numbered priority \r\n");
}

// 65434 in fini_array, 101 in dtors
static void __attribute__((destructor(65434))) EFI_NO_TAIL_CALL dtors65434() {
    Print(L"3) dtor with higher numbered priority \r\n");
}

EFI_STATUS
efi_main (EFI_HANDLE image EFI_UNUSED, EFI_SYSTEM_TABLE *systab EFI_UNUSED)
{
    Print(L"Main function \r\n");
    return EFI_SUCCESS;
}