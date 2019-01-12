/*
 * Arquivo: device.h  
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
typedef struct devices_d devices_t;
struct devices_d 
{
	object_type_t objectType;
	object_class_t objectClass;	
	
	//
    // @todo
	//
	
	int deviceId;
	int deviceUsed;
	int deviceMagic;
    char *name;

	//Se o dispositivo petence ao grupo dos prioritários.
    int Light;
	
	
	//Fila de dispositivos que está esperando
	//por esse dispositivo.
	//Na verdade podemos usar uma lista linkada ou outro recurso.
	//de gerenciamento.
	//int pid;
	//unsigned long queue[8];
	//struct process_d *list;
	
	
	
	//struct devices_d *next;
	//
	// Continua ...
	//
	
};
devices_t *devices;
//devices_t *Devices;
//devices_t *CurrentDevice;
//...

//
// @todo: Parece uma lista muito grande para o número de dispositivos.
//        mas se estamos falando de dispositivos PCI a lista é grande mesmo.
//
unsigned long deviceList[256];    


//
// Protótipo de funções.
//



void init_device_manager();

//
// Fim.
//

