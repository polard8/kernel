/*
 * File: device.h  
 *
 * Descrição:
 *     Header para o device manager.
 *     Para gerenciar e listar dispositivos.
 *
 *     Usado para dispositivos que não sejam pci
 * 
 *
 * Obs: Introduzindo aqui o conceito de 'Light' e 'Dark'.
 * O termo Light pode ser usado para descrever os dispositivos
 * mais rápidos, principalmente os que ficam mais pertos do processador,
 * tais como CPU, RAM, VIDEO MEMORY, PLACA DE REDE. Os outros disposisitivos
 * seriam classificados como Dark. Apesar de ser extremamente importante
 * que o disco do sistema seja rápido, ele ficaria sendo classificado como Dark
 * por estar longe do processador. Não há problema se no grupo dos dispositivos Dark
 * pararece algum que apresente bom desempenho, pois é apenas uma forma de se eleger
 * prioridades.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado.
 *     Versão 1.0, 2016 - Revisão.
 *     ... 
 */

 
//
// @todo: 
//     Trocar para device. 
//

//#todo: deletar esse typedef
//typedef struct device_d devices_t;

struct device_d 
{
	object_type_t objectType;
	object_class_t objectClass;
	
	//
    // @todo
	//
	
	int deviceId;

	int deviceUsed;
	int deviceMagic;
	
	FILE *stream;

    char *name;

    // char, block, network
    int __class;

    //pci, legacy ...
    int type;
    
    // se o tipo for pci.
    struct pci_device_d *pci_device;
    
    // se o dispositivo for do tipo legado,
    // como PIC, PIT, ps2, etc ...
    // Qualquer coisa que não esteja na interface pci.
    //struct legacy_device_d *legacy_device;

    //#todo: 
    //estruturas para outros grupos de dispositivos.

    //?? why light - suspenso.
	//Se o dispositivo petence ao grupo dos prioritários.
    //int Light;
	
	
	//Fila de dispositivos que está esperando
	//por esse dispositivo.
	//Na verdade podemos usar uma lista linkada ou outro recurso.
	//de gerenciamento.
	//int pid;
	//unsigned long queue[8];
	//struct process_d *list;


    struct ttydrv_d *ttydrv;

	//struct device_d *next;
	
	//
	// Continua ...
	//
	
};
struct device_d *devices;
//struct device_d *CurrentDevice;
//...


// #todo: 
// Parece uma lista muito grande para o número de dispositivos.
// mas se estamos falando de dispositivos PCI a lista é grande mesmo.

// #importante
// O número de dispositivos será o mesmo número de arquivos
// na lista Streams.
// Se o arquivo for um dispositivo então teremos
// um ponteiro na lista deviceList.

unsigned long deviceList[NUMBER_OF_FILES];    


//
// Protótipo de funções.
//

int devmgr_init_device_list(void);
struct device_d *devmgr_device_object (void);

int 
devmgr_register_device ( FILE *stream, 
                         char *name,
                         int class, 
                         int type,
                         struct pci_device_d *pci_device,
                         struct ttydrv_d *tty_driver );


void init_device_manager (void);

//
// End.
//

