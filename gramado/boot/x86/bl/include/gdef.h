/*
 * gdef.h
 * 
 * Descrição:
 *     Definições globais para o Boot Loader.
 *     Obs: Esse arquivo deve ficar no topo dos includes.
 *
 * Histórico:
 *     Versão 1.0, Oct 2016 - Created.
 */


int gdefTesting;

//+Objects.
//+Global structs.
//...


   // Essa flag será lida pela rotina de falta de página.
   // para ignorar e não parar o sistema.
int ____testing_memory_size_flag;
unsigned long __last_valid_address; //salvando o úlltimo endereço válido


//
// End.
//

