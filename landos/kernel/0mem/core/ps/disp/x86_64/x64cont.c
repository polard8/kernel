// x64cont.c
// Context support for x86_64 arch.


#include <kernel.h>

// ===============================================


// Context:
// Variáveis para salvar o contexto para x86_64.
// Essas variáveis devem permanecer encapsuladas nesse arquivo 
// do módulo. 
// Somente esse arquivo terá acesso direto à essas informações.
// #importante
// Algumas poucas rotinas vão importar essas variáveis.


unsigned long contextSS;        // User mode.
unsigned long contextRSP;       // User mode.
unsigned long contextRFLAGS; 
unsigned long contextCS;
unsigned long contextRIP;

unsigned long contextDS;
unsigned long contextES;
unsigned long contextFS;  // ?
unsigned long contextGS;  // ?

unsigned long contextRAX;
unsigned long contextRBX;
unsigned long contextRCX;
unsigned long contextRDX;

unsigned long contextRSI;
unsigned long contextRDI;

unsigned long contextRBP;

unsigned long contextR8;
unsigned long contextR9;
unsigned long contextR10;
unsigned long contextR11;
unsigned long contextR12;
unsigned long contextR13;
unsigned long contextR14;
unsigned long contextR15;

// ===============================================

