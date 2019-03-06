
//ahci.h


//struct pci_device_d sata_pci;


int ahciSetupDeviceStructure ( struct pci_device_d *D, char bus, char dev, char fun );

int ahciSATAInitialize ( int ataflag );


