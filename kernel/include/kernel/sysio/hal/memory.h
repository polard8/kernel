/*
 * File: hal\memory.h 
 * 
 * Descrição:
 *    Header para o driver do placa de memória.
 *    Aqui devem ficar informações sobre o hardware 
 *    do cartão de memória, como modelo, velocidade, etc... 
 *
 *    Obs: 
 *    As informções sobre o gerenciamento de memória 
 *    devem ir para um módulo de gerenciamento de memoria 
 *    dentro do executive, chamado mm.h
 *
 * Versão 1.0. 2015, 2016.
 */
 

/*
 * memory_d:
 *     Memory card info structure.
 *     Informações sobre o hardware do cartão de memória.
 *
 */ 
typedef struct memory_d memory_t;
struct memory_d 
{
    object_type_t objectType;
	object_class_t objectClass;
	
	//callback ;d
		
	int type;             //ddr2, ddr3 ...
	unsigned long size;   //
	int channel;          // single ou dual.
	unsigned long nb_frequency;	
	//fsb:dram
	//cas latency cl
	//ras to cas delay
	//ras precharge
	//cycle time
	//row refresh cycle time
	//command rate
	//...
	
	//module size
	//max bandwidth
	//manufacturer 
	//part number
	//serial number
	//week/ year
	//
};
//memory_t *Memory;
//memory_t *MemoryCardInfo;
//...


//
//FIM.
//
