


#include <kernel.h>

static unsigned long ata_irq_invoked = 0;

/*
 ***********************************
 * diskATAIRQHandler1
 *     irq 14 handler
 */
void diskATAIRQHandler1 (){
	
    ata_irq_invoked = 1;  
};


/*
 ***********************************
 * diskATAIRQHandler2
 *     irq 15 handler
 */
void diskATAIRQHandler2 (){
	
    ata_irq_invoked = 1;   
};


int disk_get_ata_irq_invoked (){
	
	return (int) ata_irq_invoked;
};


void disk_reset_ata_irq_invoked (){
	
	ata_irq_invoked = 0;
};


unsigned char ata_wait_irq (){
	
   unsigned long tmp = 0x10000;
   unsigned char data;
   
    while (!ata_irq_invoked)
    {
        data = ata_status_read();
        
		if ( (data &ATA_SR_ERR) )
		{
            ata_irq_invoked = 0;
            return -1;
        }
        
        //ns
        if(--tmp)ata_wait(100);
        else{
            ata_irq_invoked = 0;
            return 0x80;
        }
    };
 
    ata_irq_invoked = 0;
    
	return 0;
};


//esperando pela interrupção.
//OUT:
// 0    = ok por status da interrupção. 
// -1   = ok por status do controlador.
// 0x80 = ok por tempo esperado.

int disk_ata_wait_irq (){
	
   unsigned long tmp = 0x10000;
   unsigned char data;
   
    while (!ata_irq_invoked)
    {
        data = ata_status_read ();
        
		if ( (data &ATA_SR_ERR) )
		{
			
			//ok por status do controlador.
            ata_irq_invoked = 0;
            
			return (int) -1;
        }
        
		//ns
        if (tmp--)  //??
		{
			ata_wait (100);
        
		}else{
			
            //ok por tempo esperado.
			ata_irq_invoked = 0;
			
			return (int) 0x80;
        };
    };
 
    //ok por status da interrupção.
	ata_irq_invoked = 0;
	
	// ok 
	
    return (int) 0;
};








