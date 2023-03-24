
// atainfo.c
// Show information about ata support.
// 2021 - Created by Fred Nora.

#include <kernel.h>  


void ata_show_ata_controller_info(void)
{
    if (g_ata_driver_initialized != TRUE)
        return;
// Print data.
    switch (AtaController.controller_type)
    {
        case ATA_IDE_CONTROLLER:
            printf("IDE controller\n");
            break;
        case ATA_RAID_CONTROLLER:
            printf("RAID controller\n");
            break;
        case ATA_AHCI_CONTROLLER:
            printf("AHCI controller\n");
            break;
        case ATA_UNKNOWN_CONTROLLER:
        default:
            printf("Unknown controller type\n");
            break;
    };

    
}

// ata_show_ide_info:
// Mostrar as informações obtidas 
// na inicializações do controlador.
void ata_show_ide_info(void)
{
    int i=0;

    printf("\n");
    printf ("ata_show_ide_info: ide ports\n");

    for ( i=0; i<4; i++ )
    {
        printf("\n");
        printf ("id=%d \n", ide_ports[i].id );
        printf ("channel=%d dev_num=%d \n", 
            ide_ports[i].channel, 
            ide_ports[i].dev_num );
        //printk ("used=%d magic=%d \n", 
        //    ide_ports[i].used, 
        //    ide_ports[i].magic );
        printf ("type=%d      \n", ide_ports[i].type );
        printf ("base_port=%x \n", ide_ports[i].base_port );
        printf ("name=%s      \n", ide_ports[i].name );
        
        printf ("Size in sectors = %d \n", 
            ide_ports[i].size_in_sectors );
    };

//
// # debug.
//

// primary secondary  ... master slave
    // printf ( " channel=%d dev=%d \n", ata_controller.channel, ata_controller.dev_num );

/*
	// Estrutura 'ata'
	// Qual lista ??
	//pegar a estrutura de uma lista.

	//if( ata != NULL )
	//{
		printf("ata:\n");
 	    printf("type={%d}\n", (int) ata_controller.chip_control_type);
	    printf("channel={%d}\n", (int) ata_controller.channel);
	    printf("devType={%d}\n", (int) ata_controller.dev_type);
	    printf("devNum={%d}\n", (int) ata_controller.dev_num);
	    printf("accessType={%d}\n", (int) ata_controller.access_type);
	    printf("cmdReadMode={%d}\n", (int) ata_controller.cmd_read_modo);
	    printf("cmdBlockBaseAddress={%d}\n", (int) ata_controller.cmd_block_base_address);
	    printf("controlBlockBaseAddress={%d}\n", (int) ata_controller.ctrl_block_base_address);
		printf("busMasterBaseAddress={%d}\n", (int) ata_controller.bus_master_base_address);
		printf("ahciBaseAddress={%d}\n", (int) ata_controller.ahci_base_address);
	//};
*/
}


// Show info of the list of devices.
void ata_show_device_list_info(void)
{
    struct ata_device_d  *sd;
    unsigned long mb28=0;
    unsigned long mb48=0;

    printf("ata_show_device_list_info:\n");
    printf("Printing information about all the\n");
    printf("ata devices in the list\n");

// The head of the list
    sd = (struct ata_device_d *) ready_queue_dev;
    
    while ( (void *) sd != NULL ){

    if(sd->boottime_device == TRUE){
        printf("\n");
        printf("The boot device is the port %d\n",sd->dev_nport);
    }

    printf("PORT %d: lba28{%d} lba48{%d}\n",
        sd->dev_nport, 
        sd->dev_total_num_sector,
        sd->dev_total_num_sector_lba48 );

    //#debug
    //printf("PORT %d: LBA28 v1{%d} v2{%d} \n",
        //sd->dev_nport, 
        //sd->lba28_value1,
        //sd->lba28_value2 );

    //#debug
    //printf("PORT %d: LBA48 v1{%d} v2{%d} v3{%d} v4{%d}\n",
        //sd->dev_nport, 
        //sd->lba48_value1,
        //sd->lba48_value2,
        //sd->lba48_value3,
        //sd->lba48_value4 );

    mb28 = (unsigned long) (((sd->dev_total_num_sector * 512)/1024)/1024);
    mb48 = (unsigned long) (((sd->dev_total_num_sector_lba48 * 512)/1024)/1024);

    printf("LBA28 {%d MB} LBA48{%d MB}\n",
        mb28, mb48 );

    sd = (struct ata_device_d *) sd->next;

    };
}




