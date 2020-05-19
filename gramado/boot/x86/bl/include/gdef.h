/*
 * File: gdef.h
 * 
 * Global definitions for the boot loader.
 * Put this in the top of the includes.
 *
 * History
 *     2016 - Created by Fred Nora.
 */


// ??
int gdefTesting;


// + Objects.
// + Global structs.
// ...



// Essa flag será lida pela rotina de falta de página.
// para ignorar e não parar o sistema.
int ____testing_memory_size_flag;
unsigned long __last_valid_address; //salvando o úlltimo endereço válido


//
// End.
//

