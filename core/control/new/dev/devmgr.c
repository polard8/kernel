
// devmgr.c

#include <kernel.h>  


unsigned long deviceList[DEVICE_LIST_MAX];


// Lista de placas de rede.
// #todo:
// O valor máximo precisa ser definido. 
// #todo:
// Uma lista de ponteiros para estruturas de 
// tipo generico, esse ponteiro contera um ponteiro
// para uma estrutura de dispositivo nic de marca especifica.
unsigned long nicList[8]; 

// Search a name into the device list.
// Used by sys_open();
// OUT:
// fp or NULL
// #todo
// Só podemos chamar isso se a lista ja estiver inicializada.
// precisamos de uma flag. Pois os valores podem estar sujos.

file *devmgr_search_in_dev_list(char *path)
{
    register int i=0;
    size_t PathSize=0;
    struct device_d *tmp_dev;
    void *p;

    if ( (void*) path == NULL ){
        return NULL;
    }

    PathSize = (size_t) strlen(path);
    if (PathSize >= 64){
        return NULL;
    }

    for (i=0; i<DEVICE_LIST_MAX; i++)
    {
        tmp_dev = (struct device_d *) deviceList[i];
    
        // Is it a valid pointer?
        if ( (void*) tmp_dev != NULL )
        {
            // Is it a valid structure?
            if ( tmp_dev->magic == 1234 )
            {
                // Is this a valid mount point?
                p = (void*) tmp_dev->mount_point;
                if ( (void*) p != NULL )
                {
                    if ( strncmp( p, path, PathSize ) == 0 )
                    {
                        // #debug
                        printf ("Device found!\n");
                        refresh_screen();
                        return (file *) tmp_dev->_fp;
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

    //debug_print ("devmgr_init_device_list: Initializing the mount table. deviceList[].\n");
    debug_print ("devmgr_init_device_list:\n");

    for (i=0; i<DEVICE_LIST_MAX; i++){
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

    printf("\n");
    printf ("devmgr_show_device_list:\n");

// Get the structure pointer and
// show the info if it's a valid device structure.

    for (i=0; i<DEVICE_LIST_MAX; ++i)
    {
        d = ( struct device_d *) deviceList[i];
        if ( (void *) d != NULL )
        {
            if ( d->used  == TRUE && d->magic == 1234 )
            {
                fp = (file *) d->_fp;
                if ( (void*) fp != NULL )
                {
                    if (fp->____object == object_type)
                    {

                        //#debug
                        //if ( fp->____object == ObjectTypeTTY )
                        //    printf ("TTY DEVICE: ");
                        //if ( fp->____object == ObjectTypePciDevice )
                        //    printf ("PCI DEVICE: ");

                        //#todo: more ...
                        printf ( "id=%d class=%d type=%d name={%s} mount_point={%s} \n", 
                            d->index, 
                            d->__class,  // char | block | network
                            d->__type,   // pci  | legacy
                            d->name,
                            d->mount_point );  //#todo
                    }
                }
            }
            //printf (".");
        }
    };
// Done. 
// Show all the strings.
    printf ("Done\n");
    refresh_screen();
}

// init_device_manager:
// Called by init() in init.c.
// Inicializa o gerenciamento de dispositivos.
// Inicializa a lista de dispositivos.
void init_device_manager (void)
{
    debug_print ("init_device_manager:\n");
    devmgr_init_device_list();
    // ...
}

// OUT: 
// A pointer to a void mounted device.
// Retorna um ponteiro de estrutura do tipo dispositivo.
struct device_d *devmgr_device_object (void)
{
    struct device_d  *d;
    register int i=0;
    unsigned long __tmp=0;
    char __noname[] = "no-name";

// Procura um slot vazio.

    for (i=0; i<DEVICE_LIST_MAX; i++)
    {
         // List of pointers.
         __tmp = (unsigned long) deviceList[i];
         if (__tmp == 0) 
         {
             // Device structure.
             // #bugbug
             // Maybe it will spend a lot of memory.
             d = (struct device_d *) kmalloc ( sizeof (struct device_d) );
             // #fatal
             if ( (void *) d == NULL ){
                 panic ("devmgr_device_object: [ERROR] d\n"); 
             }
             memset( d, 0, sizeof(struct device_d) );
             d->used = TRUE;
             d->magic = 1234;
             d->index = i;
             //#todo
             //d->name 
             d->name[0] = 'x';
             d->name[1] = 0;
             // ...
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
// devmgr_register_device:
// Registrando um dispositivo dado o ponteiro para o arquivo
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
// qualquer tipo de dispositivo e associar um arquivo a ele.
// IN:
// fp, pathname, class, type, pcidevice?, ttydevice?

int 
devmgr_register_device ( 
    file *f, 
    char *name,
    unsigned char dev_class, 
    unsigned char dev_type,
    struct pci_device_d *pci_device,
    struct tty_d *tty_device )
{
    struct device_d *d;
    int id= -1;
// mount point
    int PathSize = 64;  // Pathname size.
    char buf[PathSize];
    char *new_mount_point;

    debug_print ("devmgr_register_device:\n");

    new_mount_point = (char *) kmalloc(PathSize);
    if ( (void*) new_mount_point == NULL ){
        panic ("devmgr_register_device: new_mount_point\n");
    }

// =======================
// FILE. Device object.
    if ( (void *) f == NULL ){
        panic ("devmgr_register_device: f\n");
    }
    if ( f->used != TRUE || f->magic != 1234 ){
        panic("devmgr_register_device: f validation\n");
    }
    if ( f->isDevice != TRUE ){
        panic ("devmgr_register_device: This file is NOT a device\n");
    }
// =======================
// Device structure. 
// (It is NOT the pci device struct)
    d = (struct device_d *) devmgr_device_object();        
    if ( (void *) d == NULL ){
        panic ("devmgr_register_device: d\n");
    }
    if ( d->used != TRUE || d->magic != 1234 ){
        panic ("devmgr_register_device: d validation\n");
    }
// id
    id = d->index;
    if ( id < 0 || id >= DEVICE_LIST_MAX ){
        panic ("devmgr_register_device: id\n");
    }
// file
// The file pointer.
    //if( (void*) f == NULL ){
    //    panic ("devmgr_register_device: f\n");
    //}

// #todo
    f->dev_major = 0;
// Device index into the deviceList[].
    f->dev_minor = (short) (d->index & 0xFFFF);


// Device structure.
    f->device = (struct device_d *) d;
// Save the file pointer.
    d->_fp  = (file *) f;
    d->__class = (unsigned char) dev_class;
    d->__type  = (unsigned char) dev_type;

// name

    // clear buffer
    memset( buf, 0, PathSize );

    // Se um nome não foi indicado.
    if ( (void*) name == NULL )
    {
        sprintf ( buf, "/DEV%d", id );
        strcpy( new_mount_point, buf );
    }

    size_t NameSize=0;
 
    // Se um nome foi indicado.
    if ( (void*) name != NULL )
    {
        NameSize = (size_t) strlen(name);
        if (NameSize >= PathSize){
            panic("devmgr_register_device: NameSize");
        }
        sprintf ( buf, name );
        strcpy( new_mount_point, buf );
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

