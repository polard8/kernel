
// devmgr.c


#include <kernel.h>  


// Search a neme into the list.
// Used by sys_open();
// OUT: 
// fp or NULL

file *devmgr_search_in_dev_list( char *path )
{
// #todo
// Só podemos chamar isso se a lista ja estiver inicializada.
// precisamos de uma flag.

    int i=0;
    struct device_d *tmp_dev;

    if( (void*) path == NULL )
        return NULL;

    size_t path_size = strlen(path);

    if(path_size>=64)
        return NULL;

    for (i=0; i<DEVICE_LIST_MAX; i++)
    {
        tmp_dev = (struct device_d *) deviceList[i];
    
        // is it a valid device?
        if( (void*) tmp_dev != NULL )
        {
            // is it a valid structure
            if( tmp_dev->magic == 1234 )
            {
                if( (void*) tmp_dev->mount_point != NULL )
                {
                    if( strncmp( tmp_dev->mount_point, path, path_size ) == 0 )
                    {
                        printf ("test: device found in the list\n");
                        refresh_screen();
                        
                        return (file *) tmp_dev->__file;
                    }
                }
            }
        }
    };

    return NULL;
}


// Initialize the list.
int devmgr_init_device_list(void)
{
    register int i=0;

    debug_print ("devmgr_init_device_list: Initializing the mount table. deviceList[].\n");

    for (i=0; i<DEVICE_LIST_MAX; i++)
    {
        deviceList[i] = 0;
    };

    //...
    
    return 0;
}


// Show device list.
void devmgr_show_device_list(int object_type)
{
    file *fp;
    struct device_d  *d;
    register int i=0;

    printf ("\n devmgr_show_device_list: \n");

    for (i=0; i<DEVICE_LIST_MAX; ++i)
    {
        // Get the device structure.

        d = ( struct device_d *) deviceList[i];

        if ( (void *) d != NULL )
        {
            //dispositivo válido.
            if ( d->used  == TRUE && 
                 d->magic == 1234 )
            {

                fp = (file *) d->__file;

                if( (void*) fp != NULL )
                {
                    if( fp->____object == object_type )
                    {

                        //#debug
                        //if ( fp->____object == ObjectTypeTTY )
                        //    printf ("TTY DEVICE: ");
                        //if ( fp->____object == ObjectTypePciDevice )
                        //    printf ("PCI DEVICE: ");

                        //#todo: more ...
                        printf ( "id=%d class=%d type=%d name={%s} mount_point={%s} \n", 
                            d->index, 
                            d->__class, 
                            d->type, 
                            d->name,
                            d->mount_point );  //#todo
                    }
                }
            }
            
            //printf (".");
        }
    };

    printf ("Done\n");
    refresh_screen();
}


/*
 * init_device_manager:
 * 
 */

// Called by init() in init.c.
void init_device_manager (void)
{
    debug_print ("init_device_manager:\n");
 
    devmgr_init_device_list();

    // ...
}

// OUT: 
// A pointer to a void mounted device.
// Retorna um ponteiro de estrutura do tipo dispositivo.

struct device_d *devmgr_device_object (void){

    struct device_d  *d;
    int i=0;
    unsigned long __tmp=0;

    char __noname[] = "no-name";


    // Procura um slot vazio.

    for (i=0; i<DEVICE_LIST_MAX; i++)
    {
         __tmp = (unsigned long) deviceList[i];
    
         // slot livre.
         // unsigned long
         if ( __tmp == 0 ) 
         {
            //
            // Device structure.
            //

            // #bugbug
            // Maybe it will spend a lot of memory.

             d = (struct device_d *) kmalloc ( sizeof (struct device_d) );
             
             // #debug
             if ( (void *) d == NULL ){
                 panic ("devmgr_device_object: [ERROR] d\n"); 
             }
             
             memset( d, 0, sizeof(struct device_d) );

             d->used  = TRUE;
             d->magic = 1234;
             d->index = i;

             //#todo
             //d->name 
             d->name[0] = 'x';
             d->name[1] = 0;
             
             //
             // ...
             //

             // Save and return.

             deviceList[i] = (unsigned long) d;

             return (struct device_d *) d;
         }
    };

    // fail
    panic ("devmgr_device_object: [FAIL] Overflow!\n");
    return NULL;
}

// ==============
// registrando um dispositivo dado o ponteiro para o arquivo
// que representa seu objeto.
// #todo: 
// Tem vários argumentos.
// Possivelmente ampliaremos o número de argumentos no futuro.
// This is called by pciHandleDevice() in pci.c to register
// every found device and for the ps2 devices initialization.
// The pcidevice argument is null in this case.

// #todo
// #bugbug
// Essa rotina tem um parametro para ponteiro de estrutura
// de dispositivo pci.
// #todo: precisamos de uma rotina similar, para registrar
// qualquer tipo de dispositivo e associar um arquivo
// a ele.

int 
devmgr_register_device ( 
    file *f, 
    char *name,
    int class, 
    int type,
    struct pci_device_d *pci_device,
    struct tty_d *tty_device )
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
        panic ("devmgr_register_device: new_mount_point\n");
    }

// =======================
// FILE. Device object.

    if ( (void *) f == NULL )
    {
        panic ("devmgr_register_device: [FAIL] f \n");
    }

    if ( f->used != TRUE || f->magic != 1234 ){
        panic("devmgr_register_device: f validation \n");
    }

    if ( f->isDevice != TRUE ){
        panic ("devmgr_register_device: This file is NOT a device!\n");
    }

// =======================
// Device structure. 
// (It is NOT the pci device struct)

    d = (struct device_d *) devmgr_device_object();
        
    if ( (void *) d == NULL )
    {
        panic ("devmgr_register_device: d. Couldn't create device object\n");
    }

    if ( d->used != TRUE || d->magic != 1234 )
    {
        panic ("devmgr_register_device: d validation \n");
    }

// id
    id = d->index;
    if ( id < 0 || id >= DEVICE_LIST_MAX )
    {
        panic ("devmgr_register_device: id limits \n");
    }

// file
// The file pointer.

    if( (void*) f == NULL ){
        panic ("devmgr_register_device: f\n");
    }

    d->__file  = (file *) f;

// Device structure.
    f->device = (struct device_d *) d;

// Device index into the deviceList[].
    f->deviceId = d->index; 

    d->__class = class;
    d->type    = type;


// name

    // clear buffer
    memset( __tmp_mount_point, 0, 64 );


    // Se um nome não foi indicado.
    if( (void*) name == NULL )
    {
        sprintf ( 
            (char *) &__tmp_mount_point[0], 
            "/DEV%d", 
            id );
            
        strcpy(
            new_mount_point,
            __tmp_mount_point );
    }

    size_t NameSize=0;
 
    // Se um nome foi indicado.
    if( (void*) name != NULL )
    {
        NameSize = (size_t) strlen(name);
        if( NameSize >= 64)
            panic("devmgr_register_device: NameSize");
        
        sprintf ( 
            (char *) &__tmp_mount_point[0], 
            name );
            
        strcpy(
            new_mount_point,
            __tmp_mount_point );

    }

// /dev/tty0
    d->mount_point = (char *) new_mount_point; 


   
    // DEV_8086_8086
    //d->name ??
    
    //#todo
    //d->name[0] = 'x';
    d->name[0] = 0;


// pci device
    d->pci_device = (struct pci_device_d *) pci_device;

// tty device
    d->tty = (struct tty_d *) tty_device;
 

    // ...

    return 0;
}














