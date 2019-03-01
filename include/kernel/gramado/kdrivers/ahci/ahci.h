
//ahci.h


struct pci_device_d sata_pci;


int diskSATAPCIConfigurationSpace ( char bus, char dev, char fun );
int ahciSATAInitialize ( int ataflag );


