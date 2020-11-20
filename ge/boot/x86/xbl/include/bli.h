/*
 * File: bli.h
 *
 * Boot Loader Internal. Para rotinas globais começadas com BlXXXX.
 * Acessiveis à todos os módulos do boot loader.
 */


//
// Procedure.
//

unsigned long 
bl_procedure ( 
    unsigned long window,
    int msg, 
    unsigned long long1, 
    unsigned long long2 );


//
// Finalizations support.
//

void BlAbort();


//
// End.
//

