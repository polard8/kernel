/*
 * File: dev/devmgr.c 
 * 
 * Descrição: 
 *     Arquivo principal do device manager. 
 *     Device manager do kernel. 
 *
 * In shutdown process all devices need to be turnedoff.
 *
 * 2015 - Created by Fred Nora.
 */


// #importante
// Usado para gerenciar a tabela de montagem.
// O nome do dispositivo é um pathname usado pelo
// sistema de arquivos.
// See: Olhar a estrutura de dispositivo 
// e o elemento 'name'.
 
 
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




// Initialize the list.
int devmgr_init_device_list(void)
{
    int i=0;

    debug_print ("devmgr_init_device_list: Initializing the mount table. deviceList[].\n");

    for (i=0; i<DEVICE_LIST_MAX; i++)
    {
        deviceList[i] = 0; 
    };

    //...
    
    return 0;
}


/*
// Mount a device into the deviceList[].
// IN: Device id.
struct device_d *do_mount (int dev);
struct device_d *do_mount (int dev)
{
    struct device_d *d;
    
    d = (struct device_d *) devmgr_device_object();
    
    if ( (void*) == NULL )
       return (struct device_d *) 0;


    //d->? = dev;
    
    return (struct device_d *) d;
}
*/




/*
// Mount root device.
int mount_root (void);
int mount_root (void)
{
   return -1;
}
*/



// OUT: 
// A pointer to a void mounted device.
// Retorna um ponteiro de estrutura do tipo dispositivo.

struct device_d *devmgr_device_object (void){

    struct device_d *d;
    
    unsigned long __tmp=0;
    int i=0;
    
    char __noname[] = "no-name";


    // Procura um slot vazio.

    for (i=0; i<DEVICE_LIST_MAX; i++)
    {
         __tmp = (unsigned long) deviceList[i];
    
         // slot livre.
         if ( __tmp == 0 )  //unsigned long
         {
             
             d = (struct device_d *) kmalloc ( sizeof (struct device_d) );
             
             // #debug
             if ( (void *) d == NULL ){
                 panic ("devmgr_device_object: d"); 
             }

             d->index = i;
             d->used = 1;
             d->magic = 1234;
             
            
             //#todo
             //d->name 
             d->name[0] = 'x';
             d->name[1] = 0;
             
             //
             // ...
             //
             
             // Salva.
             deviceList[i] = (unsigned long) d;
             
             // Done.
             return (struct device_d *) d;
         }
    };

    // fail
    panic ("devmgr_device_object: Overflow!");
    //return NULL;
}



//==============
// registrando um dispositivo dado o ponteiro para o arquivo
// que representa seu objeto.
// #todo: 
// Tem vários argumentos.
// Possivelmente ampliaremos o número de argumentos no futuro.

//
// This is called by pciHandleDevice() in pci.c to register
// every found device and for the ps2 devices initialization.
// The pcidevice argument is null in this case.
//

int 
devmgr_register_device ( 
    file *f, 
    char *name,
    int class, 
    int type,
    struct pci_device_d *pci_device,
    struct ttydrv_d *tty_driver )
{

    struct device_d *d;
    int id= -1;


    // mount point
    char __tmp_mount_point[64];
    char *new_mount_point;


    debug_print ("devmgr_register_device:\n");


    new_mount_point = (char *) kmalloc(64);
    
    if ( (void*) new_mount_point == NULL )
    {
        panic ("devmgr_register_device: new_mount_point");
    }

    // =======================
    // FILE. Device object.

    if ( (void *) f == NULL )
    {
        panic ("devmgr_register_device: [FAIL] f \n");
    }

    if ( f->used != 1 || f->magic != 1234){
        panic("devmgr_register_device: f validation \n");
    }

    if ( f->isDevice != 1 ){
        panic ("devmgr_register_device: This file is NOT a device!\n");
    }

    // =======================
    // Device structure. (It is NOT the pci device struct)

    d = (struct device_d *) devmgr_device_object();
        
    if ( (void *) d == NULL )
    {
        panic ("devmgr_register_device: d. Couldn't create device object\n");
    }

    if ( d->used != 1 || d->magic != 1234 )
    {
        panic ("devmgr_register_device: d validation \n");
    }

    // ID
    
    id = d->index;
            
    if (id < 0 || id >= DEVICE_LIST_MAX )
    {
        panic ("devmgr_register_device: id limits \n");
    }

    // Saving.
    f->device = (struct device_d *) d;
    
    
    f->deviceId = d->index; 
    

    d->__file = (file *) f;
    d->__class = class;
    d->type = type;

    // #test 
    //Todo: create the file.
    
    sprintf( (char *) &__tmp_mount_point[0], "/DEV%d", id);
    strcpy (new_mount_point,__tmp_mount_point);

    // /dev/tty0
    d->mount_point = (char *) new_mount_point; 
   
    // DEV_8086_8086
    //d->name ??
    
    //#todo
    d->name[0] = 'x';
    d->name[0] = 0;
    
    //
    // The PCI device structure. It is NOT the device structure.
    //

    // pci device.
    // Passado via argumento
    d->pci_device = (struct pci_device_d *) pci_device;

    // tty driver.
    // Passado via argumento.
    d->ttydrv = (struct ttydrv_d *) tty_driver;

    // #todo
    // We really need this thing. 
    // But it will use a lot of memory.
    
    // #bugbug: 
    // It fail. Crash!!
    // We don't have all these resources for now.
    // Let the ps2 devices create their own tty for now.

    //d->tty = (struct tty_d *) tty_create();

    // ...

    return 0;
}


// Show device list.
void devmgr_show_device_list(void)
{
    struct device_d *d;
    register int i=0;


    printf ("\n devmgr_show_device_list: \n");

    for (i=0; i<DEVICE_LIST_MAX; ++i)
    {
        d = ( struct device_d *) deviceList[i];

        if ( (void *) d != NULL )
        {
            //dispositivo válido.
            if ( d->used == 1 && 
                 d->magic == 1234 )
            {
                //#todo: more ...
                printf ( "id=%d class=%d type=%d name={%s} mount_point={%s} \n", 
                    d->index, 
                    d->__class, 
                    d->type, 
                    d->name,
                    d->mount_point );  //#todo
            }
            
            //printf (".");
        }
    };

    printf ("Done\n");
    refresh_screen();
}


/*
 ********************************
 * init_device_manager:
 * 
 */

void init_device_manager (void)
{
    debug_print ("init_device_manager:\n");
 
    devmgr_init_device_list();
    //...
}



//
// End.
//

