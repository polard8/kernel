

//network.h  //header para o gerenciamento de rede.

// >> The register at offset 0x00 is the "IOADDR" window. 
// >> The register at offset 0x04 is the "IODATA" window. 

//packet format
// Ethernet IPv4 TCP/UDP DATA FCS

int networkInit();

//
//fim
//

