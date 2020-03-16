/*
 * File: devmgr/devmgr.c 
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





int devmgr_init_device_list(void)
{
    int i;

    for (i=0; i<NUMBER_OF_FILES; i++)
    {
        deviceList[i] = 0; 
    }

    //...
    
    return 0;
}



struct device_d *devmgr_device_object (void)
{
    struct device_d *d;
    unsigned long __tmp;
    int i;
    
    
    for (i=0; i<NUMBER_OF_FILES; i++)
    {
         __tmp = deviceList[i];
    
         // slot livre.
         if ( __tmp == 0 )  //unsigned long
         {
             
             d = (struct device_d *) kmalloc ( sizeof (struct device_d) );
             
             if ( (void *) d == NULL )
             {
                 panic ("devmgr_device_object: d"); 
             }

             d->deviceId = i;
             
             d->deviceUsed = 1;
             d->deviceMagic = 1234;
             
             deviceList[i] = (unsigned long) d;
             
             return (struct device_d *) d;
         }
    };

    // fail
    return NULL;
}


// #todo: 
// Tem vários argumentos.
// Possivelmente ampliaremos o número de argumentos no futuro.

int 
devmgr_register_device ( FILE *stream, 
                         char *name,
                         int class, 
                         int type,
                         struct pci_device_d *pci_device,
                         struct ttydrv_d *tty_driver )
{
	int id;
    struct device_d *d;
    
    
    
    if ( (void *) stream == NULL )
    {
		printf ("devmgr_register_device: stream \n");
		die ();
		//return -1;
    }else{
		
		if ( stream->used != 1 || stream->magic != 1234)
		{
		    printf ("devmgr_register_device: stream validation \n");
		    die ();
			//return -1;
		}
	    
	    if ( stream->isDevice != 1 )
	    {
			//printf ("This stream is NOT a device!\n");
		    printf ("devmgr_register_device: This stream is NOT a device!\n");
		    die ();
			//return -1;
		}
		
        
        d = (struct device_d *) devmgr_device_object ();
        
        if ( (void *) d == NULL )
        {
		    printf ("devmgr_register_device: d\n");
		    die ();
			//return -1;
        }else{
			
			if ( d->deviceUsed != 1 || d->deviceMagic != 1234 )
			{
		        printf ("devmgr_register_device: d validation \n");
		        die ();				
				//return -1;
			}
			
			id = d->deviceId;
            
            if (id < 0 || id >= NUMBER_OF_FILES )
            {
		        printf ("devmgr_register_device: id limits \n");
		        die ();				
			    //return -1;
            }

            stream->deviceId = d->deviceId; 
			
			d->stream = (FILE *) stream;
			d->__class = class;
			d->type = type;
			d->name = (char *) name;
			
			d->pci_device = (struct pci_device_d *) pci_device;
			d->ttydrv = (struct ttydrv_d *) tty_driver;
		
		    // continua ...
		};
        
        //...
	};

    return 0;
}


/*
 * init_device_manager:
 */

void init_device_manager (void)
{
    devmgr_init_device_list ();

    //...
}


/*
int devicemanagerInit()
{}
*/

//int deveiceInit(){
//
//}


//
// End.
//

