/*
 * File: io.h
 *
 * Descrição:
 *     Arquivo principal do I/O Manager.
 *     Todo gerenciamento de dispositivos,
 *     toda concessão de acesso passará por 
 *     esse gerenciador, que faz parte da
 *     camada de abstração de hardware oferecidad pelo
 *     kernel base.
 *
 * History:
 *     2016 - Created by Fred Nora.
 */


#ifndef ____IO_H
#define ____IO_H


// Estrutura para gerenciamento de buffer de i/o. 

struct ioBuffer_d
{
    object_type_t objectType;
    object_class_t objectClass;

    struct process_d *OwnerProcess;    // processo dono do buffer.
    unsigned long address;             // Address.
    
    int size;                          // size in number of bytes.
}; 

// #test
struct ioBuffer_d *CurrentIOBuffer;

//struct ioBuffer_d *lineBuffer;    //Buffer para uma linha de caracteres.
//struct ioBuffer_d *fileBuffer;    //buffer para um arquivo de texto.
//struct ioBuffer_d *CurrentBuffer;
//struct ioBuffer_d *ipcBuffer;    //IPC buffer. (Área de transferência.)
// ... 

 
 
 // Escalonamento de dispositivo.
// Todo dispositivo tem uma fila de threads esperando 
// para usar o dispositivo.
// Nessas variáveis colocaremos qual é a thread que 
// está usando o dispositivo no momento.
// #bugbug essa informações deve estar na estrutura de dispositivo.
//
// ## input control 
//

struct ioControl_d
{

    int id;
    int used;
    int magic;

    //identificação do dispisitivo
    int did; 

	// Aqui identificaremos qual a thread que está 
	// usando o dispositivo no momento.

    //identificação da thread.
    int tid; 

    // a janela que esta usando o dispositivo.
    int wid;  
};

struct ioControl_d *ioControl_keyboard;   //0
struct ioControl_d *ioControl_mouse;      //1

unsigned long ioControl[32];



 
//
// Prototypes.
// 
 

// Handler for services.
void *ioServices ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );


int ioInit (void);


#endif   


//
// End.
//

