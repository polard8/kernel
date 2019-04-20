/*
 * File: device\device.c 
 *
 * Descrição: 
 *     Arquivo principal do device manager. 
 *     Device manager do kernel. 
 *
 * In shutdown process all devices need to be turnedoff.
 *
 * 2015 - Created by Fred Nora.
 */
 
 
#include <kernel.h>


/*
    As classes poderiam ter nomes amigáveis e 
	respeitarem o nível de experiência do usuário:

Iniciante:
   +identificação do computador
   +identificação do processador
   +identificação da placa de video
  
Intermediário:
   +identificação do computador
   +identificação do processador
   +identificação da placa de video
   +identificação dos discos
   
Avançado:
   +identificação do computador
   +identificação do processador
   +identificação da placa de video
   +identificação dos discos
   +identificação de componentes do sistema
   +Outros (Todo o resto sistemicamente não importante)

*/

/*
typedef enum {
	device_class_null,
	device_class_motherboard,
	device_class_processors,
	device_class_videocards,
	device_class_disks,
	device_class_systemcomponents,
	device_class_others,
}device_class_t;
*/

//Variáveis internas
//int devicemanagerStatus;
//int devicemanagerError;
//...



/*
 * init_device_manager:
 */

void init_device_manager (void)
{	
    //
}


/*
int devicemanagerInit()
{}
*/

//int deveiceInit(){
//	
//}

//
//fim
//

