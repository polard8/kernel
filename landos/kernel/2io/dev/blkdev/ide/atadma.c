/*
 * File: atadma.c
 *    DMA part of the ide driver support.
 *    ring 0 only.
 *    kernel base persistent driver.
 *
 * Credits: 
 *     2018 - Original by Nelson Cole.
 *     2019 - Fred Nora.
 */



#include <kernel.h>


/*
 * ata_set_device_and_sector:
 * #bugbug Essa função não foi declarada no header e não foi usada.
 */

/*
static inline void ata_set_device_and_sector ( unsigned long count, unsigned long long addr,\
                                                int access_type, char nport )
{
    ata_assert_dever(nport);

	//
	// Access type.
	//
	
    switch ( access_type )
	{
		//Mode LBA28
	    case 28:
	        out8 ( ata.cmd_block_base_address + ATA_REG_SECCOUNT, count );   // Sector Count 7:0
	        out8 ( ata.cmd_block_base_address + ATA_REG_LBA0, addr );		 // LBA 7-0   
	        out8 ( ata.cmd_block_base_address + ATA_REG_LBA1, addr >> 8 );   // LBA 15-8
	        out8 ( ata.cmd_block_base_address + ATA_REG_LBA2, addr >> 16 );  // LBA 23-16
            
			// Modo LBA active, Select device, and LBA 27-24
            out8 ( ata.cmd_block_base_address + ATA_REG_DEVSEL, 
			    0x40 | (ata.dev_num << 4) | (addr >> 24 &0x0f) );
            
			// Verifique se e a mesma unidade para não esperar pelos 400ns.
			
            if ( ata_record_dev != ata.dev_num && 
			     ata_record_channel != ata.channel )
			{
                ata_wait(400);
                
				//verifique erro
                ata_record_dev = ata.dev_num;
                ata_record_channel  = ata.channel;
			};
            break;
			
		//Mode LBA48	
        case 48:
            
            out8( ata.cmd_block_base_address + ATA_REG_SECCOUNT,0);	      // Sector Count 15:8
	        out8( ata.cmd_block_base_address + ATA_REG_LBA0,addr >> 24);  // LBA 31-24   
	        out8( ata.cmd_block_base_address + ATA_REG_LBA1,addr >> 32);  // LBA 39-32
	        out8( ata.cmd_block_base_address + ATA_REG_LBA2,addr >> 40);  // LBA 47-40
	        out8( ata.cmd_block_base_address + ATA_REG_SECCOUNT,count);   // Sector Count 7:0
	        out8( ata.cmd_block_base_address + ATA_REG_LBA0,addr);		  // LBA 7-0   
	        out8( ata.cmd_block_base_address + ATA_REG_LBA1,addr >> 8);   // LBA 15-8
	        out8( ata.cmd_block_base_address + ATA_REG_LBA2,addr >> 16);  // LBA 23-16
            
			out8 ( ata.cmd_block_base_address + ATA_REG_DEVSEL,
			    0x40 | ata.dev_num << 4 );   // Modo LBA active, Select device,        
            
			// Verifique se e a mesma unidade para não esperar pelos 400ns.
            if( ata_record_dev != ata.dev_num && 
			    ata_record_channel != ata.channel )
			{
                ata_wait(400);
                ata_record_dev     = ata.dev_num;
                ata_record_channel = ata.channel;
			};
            break;
			
        // Modo CHS
        // not supported			
        case 0:
            break;

        // Default ??
    };
};
*/



/*
 ****************************************
 * ide_dma_data:
 *     O que segue é um suporte ao controlador de DMA para uso nas rotinas de IDE. 
 *     #todo Nelson, Não se esqueça de habiliatar o // Bus Master Enable
 *  no espaço de configuraçao PCI (offset 0x4 Command Register)
 *
 * 2018 - Created by Nelson Cole. 
 */

void 
ide_dma_data ( 
    void *addr, 
    uint16_t byte_count,
    uint8_t flg,
    uint8_t nport )
{

    unsigned char data=0;
    uint32_t phy=0;


	// #todo: 
	// Check limits.

	// #todo: (&~1)sera que e necessario?


    ide_dma_prdt[nport].addr = (unsigned long) addr;  
    ide_dma_prdt[nport].len  = byte_count | 0x80000000;

    phy = (uint32_t) &ide_dma_prdt[nport];

    // prds physical.
    out32 ( ata.bus_master_base_address + ide_dma_reg_addr, phy );

	// (bit 3 read/write)
	// 0 = Memory reads.
	// 1 = Memory writes.

    data = in8 ( ata.bus_master_base_address + ide_dma_reg_cmd ) &~8;

    // #todo: bit 8, Confilito no Oracle VirtualBox
	// #obs: Isso foi enviado via argumento e agora foi alerado.

    flg = 1;  

    out8 ( ata.bus_master_base_address + ide_dma_reg_cmd, data | flg << 3 );

	// Limpar o bit de interrupção e 
	// o bit de erro no registo de status.

    data = in8 ( ata.bus_master_base_address + ide_dma_reg_status );
    out8 ( ata.bus_master_base_address + ide_dma_reg_status, data &~6 );
}



// ide_dma_start:
//     2018 - Created by Nelson Cole. 

void ide_dma_start (void)
{
    unsigned char data = in8 ( ata.bus_master_base_address + ide_dma_reg_cmd );

    out8 ( ata.bus_master_base_address + ide_dma_reg_cmd, data | 1 );
}


// ide_dma_stop:
//     2018 - Created by Nelson Cole. 

void ide_dma_stop (void)
{
    unsigned char data = in8 ( ata.bus_master_base_address + ide_dma_reg_cmd ); 

    out8 ( ata.bus_master_base_address + ide_dma_reg_cmd, data &~1);

    data = in8 ( ata.bus_master_base_address + ide_dma_reg_status );

    out8 ( ata.bus_master_base_address + ide_dma_reg_status, data &~6);
}


/*
 * ide_dma_read_status:
 *     DMA read status.
 *     2018 - Created by Nelson Cole.  
 */

int ide_dma_read_status (void)
{
    return in8 ( ata.bus_master_base_address + ide_dma_reg_status );
}


//
// End.
//




