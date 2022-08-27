
// nicintel.h
// see: e1000/e1000.c

#ifndef ____NICINTEL_H
#define ____NICINTEL_H    1


#define TDESC_STA_DD    0x01 /* indicates hardware done with descriptor */
#define TDESC_CMD_EOP   0x01 /* indicates end of packet */
#define TDESC_CMD_IFCS  0x02 /* insert frame checksum (FCS) */
#define TDESC_CMD_RS    0x08 /* requests status report */



// Transmit Descriptor
struct legacy_tx_desc 
{
    //uint64_t addr;
    uint32_t addr;  //endereço físico do buffer.
    uint32_t addr2;

    uint16_t length;
    uint8_t cso;      /* checksum offset */
    uint8_t cmd;

    uint8_t status;   /* status and reserved */
    uint8_t css;      /* checksum start */
    uint16_t special;
};

// Receive Descriptor
struct legacy_rx_desc 
{
    //uint64_t buffer_addr; // Address of the descriptor's data buffer 
    uint32_t addr;
    uint32_t addr2;

    uint16_t length;     // Length of data DMAed into data buffer 
    uint16_t csum;       // Packet checksum 
    uint8_t status;      // Descriptor status 
    uint8_t errors;      // Descriptor Errors 
    uint16_t special;
};


// arp cache item
struct arp_cache_item_d
{
    int used;
    int magic;
    uint8_t mac_address[6];
    uint8_t ipv4_address[4];
};


// ## device info ##
// #bugbug
// Me parece que isso deve ser usado apenas para dispositivos  
// Intel. Pois cada marca terá suas características.
struct intel_nic_info_d
{
    object_type_t objectType;
    object_class_t objectClass;

// Validação da estrutura.
// Se as flags estiverem acionadas, devemos procurar 
// as informações na estrutura de dispositivo pci.
    int used;
    int magic;

// Salvando o endereço base.
    unsigned long registers_base_address;
    unsigned long DeviceControl;
    unsigned long DeviceStatus;

    uint8_t mac_address[6];
    uint8_t ip_address[4];

    uint16_t rx_cur;
    uint16_t tx_cur;

    int eeprom;
    int use_io;

    uint16_t io_base;
    uint32_t mem_base;    // #bugbug:  32bit address?

// rx
    struct legacy_rx_desc *legacy_rx_descs; //rx ring virtual address
    unsigned long rx_descs_virt[32];
// tx
    struct legacy_tx_desc *legacy_tx_descs; //tx ring virtual address
    unsigned long tx_descs_virt[8];

// physical address.
    unsigned long rx_descs_phys;  //rx ring physical address
    unsigned long tx_descs_phys;  //tx ring physical address

    struct arp_cache_item_d arp_cache[32];

//pci device.
    struct pci_device_d *pci;

    int interrupt_count;

    // rede.
    //struct network_info_d *network;
    //struct device_d     *device;
    //struct intel_nic_info_d *next;
};

// #bugbug
// Esse nome genério não deveria ser usado para o caso 
// específico da intel.
extern struct intel_nic_info_d  *currentNIC;
// ...

// Lista de placas de rede.
// #todo:
// O valor máximo precisa ser definido. 
extern unsigned long nicList[8]; 

extern int e1000_interrupt_flag;
extern int e1000_irq_count;







//
// == Prototypes ========
//

int 
e1000_init_nic ( 
    unsigned char bus, 
    unsigned char dev, 
    unsigned char fun, 
    struct pci_device_d *pci_device );

#endif    




