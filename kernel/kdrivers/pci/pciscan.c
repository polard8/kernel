

//pciscan.c

#include <kernel.h>


/*
 ***********************************************************************
 * pci_setup_devices:
 *     Encontrar os dispositivos PCI e salvar as informações sobre eles
 * em suas respectivas estruturas.
 *     #importante: Isso pode ser usado em futuras sondagens por dispositivo.
 *     É só procurarmos pelo dispositivo nessa lista.
 *
 * @todo: 
 *     Completar toda a estrutura, ainda faltam elementos.
 *     Obs: A estrutura está em pci.h.    
 *
 * #importante:
 * #todo
 * Quando sondamos os dispositivos pci usando for, podemos checar a
 * classe e a subclasse dos dispositivos e se encontrarmos a combilaçao desejada
 * entao inicializamos o dispositivo.
 */


//##bugbug
//Não precisamos inicialziar os dispositivos nesse momento.
//somente colocar na estrutura

int pci_setup_devices (){	
	
    unsigned short Vendor;    //Offset 0.
	unsigned short Device;    //Offset 2.
	
	//@todo: rever tamanho
	//unsigned char ClassCode;
	//unsigned char SubClassCode;
	//unsigned char ProgIF;	
	
 	
	unsigned char i = 0; //Bus.
    unsigned char j = 0; //Devices. (Slots).
	unsigned char k = 0; //Functions
	
 
    printf("Detecting PCI Devices..\n");
	
	unsigned char HeaderType;
	int funcCount;
	
	//Bus.
	for( i=0; i < PCI_MAX_BUSES; i++)   
	{
		//Device.
	    for( j=0; j < PCI_MAX_DEVICES; j++)
        {
			
		    // Valid device ?
			
		    Vendor = (unsigned short) pciCheckVendor (i,j);			
		    
			if ( Vendor != 0 && Vendor != PCI_INVALID_VENDORID )
		    { 
				
				printf("vendor=%x\n",Vendor);
				// Multifunction ??
				//Se o bit 7 estiver acionado, entao e' multifunction.
				
				HeaderType = pciGetHeaderType (i,j);
                
				funcCount = HeaderType & PCI_TYPE_MULTIFUNC ? PCI_MAX_FUNCTIONS : 1;
				
				//function
			    for( k=0; k<funcCount; k++)
			    {
				    //k=0;
					printf("+");
				    pciHandleDevice ( i, j, k );			
			    }; //fuction for.
				
		    };				
					
		};  // Device for.		
		
	};  //bus for.
	


    printf("Detecting PCI Devices completes..\n");
	
	debug_print("Detecting PCI Devices completes..\n");
	//refresh_screen();
	//while(1){}

    return 0; 
}

//procurar na lista de dispositivos por um dispositivo de 
//determinados vendor e device.

struct pci_device_d *scan_pci_device_list ( unsigned short vendor, 
										    unsigned short device )
{
    struct pci_device_d *D;
	
	int i;
	
	//#bugbug
	//Nossa lista só tem 32 slots por enquanto.
	
	for ( i=0; i<32; i++ )
	{
	    D = (void *) pcideviceList[i];
		
		if ( (void *) D != NULL )
		{
			if ( D->used == 1 && D->magic == 1234 )
			{
			    if ( D->Vendor == vendor && D->Device == device )
				{
					return (struct pci_device_d *) D;
				}	
			}
		}
	}
	
    return NULL;
} 

		
//procurar na lista de dispositivos por um dispositivo de 
//determinada classe e subclasse.
struct pci_device_d *scan_pci_device_list2 ( unsigned char class, 
										    unsigned char subclass )
{
    struct pci_device_d *D;
	
	int i;
	
	//#bugbug
	//Nossa lista só tem 32 slots por enquanto.
	
	for ( i=0; i<32; i++ )
	{
	    D = (void *) pcideviceList[i];
		
		if ( (void *) D != NULL )
		{
			if ( D->used == 1 && D->magic == 1234 )
			{
			    if ( D->classCode == class && D->subclass == subclass )
				{
					return (struct pci_device_d *) D;
				}	
			}
		}
	}
	
    return NULL;
} 







