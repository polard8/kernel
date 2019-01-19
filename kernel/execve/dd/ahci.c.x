//ahci support (examples)
//credits: osdev forum.
//https://wiki.osdev.org/AHCI

// #obs:
// Provavelmente na ultima BAR pegaremos o endereço base dos registradores.
//

//Detect attached SATA devices

/*
The Port Implemented register (HBA_MEM.pi) is a 32 bit value and each bit represents a port. 
If the bit is set, the according port has a device attached, otherwise the port is free.
*/


//2) What kind of device is attached

/*
There are four kinds of SATA devices, and their signatures are defined as below.
*/

#define	SATA_SIG_ATA	0x00000101	// SATA drive
#define	SATA_SIG_ATAPI	0xEB140101	// SATAPI drive
#define	SATA_SIG_SEMB	0xC33C0101	// Enclosure management bridge
#define	SATA_SIG_PM	0x96690101	// Port multiplier
 
#define AHCI_DEV_NULL 0
#define AHCI_DEV_SATA 1
#define AHCI_DEV_SEMB 2
#define AHCI_DEV_PM 3
#define AHCI_DEV_SATAPI 4
 
#define HBA_PORT_IPM_ACTIVE 1
#define HBA_PORT_DET_PRESENT 3
 
void probe_port(HBA_MEM *abar)
{
	// Search disk in impelemented ports
	uint32_t pi = abar->pi;
	int i = 0;
	while (i<32)
	{
		if (pi & 1)
		{
			int dt = check_type(&abar->ports[i]);
			if (dt == AHCI_DEV_SATA)
			{
				trace_ahci("SATA drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_SATAPI)
			{
				trace_ahci("SATAPI drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_SEMB)
			{
				trace_ahci("SEMB drive found at port %d\n", i);
			}
			else if (dt == AHCI_DEV_PM)
			{
				trace_ahci("PM drive found at port %d\n", i);
			}
			else
			{
				trace_ahci("No drive found at port %d\n", i);
			}
		}
 
		pi >>= 1;
		i ++;
	}
}
 
// Check device type
static int check_type(HBA_PORT *port)
{
	uint32_tssts = port->ssts;
 
	uint8_t ipm = (ssts >> 8) & 0x0F;
	uint8_t det = ssts & 0x0F;
 
	if (det != HBA_PORT_DET_PRESENT)	// Check drive status
		return AHCI_DEV_NULL;
	if (ipm != HBA_PORT_IPM_ACTIVE)
		return AHCI_DEV_NULL;
 
	switch (port->sig)
	{
	case SATA_SIG_ATAPI:
		return AHCI_DEV_SATAPI;
	case SATA_SIG_SEMB:
		return AHCI_DEV_SEMB;
	case SATA_SIG_PM:
		return AHCI_DEV_PM;
	default:
		return AHCI_DEV_SATA;
	}
}



//AHCI port memory space initialization

/*
BIOS may have already configured all the necessary AHCI memory spaces. 
But the OS usually needs to reconfigure them to make them fit its requirements. 
It should be noted that Command List must be located at 1K aligned memory address and Received FIS be 256 bytes aligned.

Before rebasing Port memory space, OS must wait for current pending commands to finish and 
tell HBA to stop receiving FIS from the port. Otherwise an accidently incoming FIS may be 
written into a partially configured memory area. This is done by checking and setting 
corresponding bits at the Port Command And Status register (HBA_PORT.cmd).
The example subroutines stop_cmd() and start_cmd() do the job.

*/

#define	AHCI_BASE	0x400000	// 4M
 
#define HBA_PxCMD_ST    0x0001
#define HBA_PxCMD_FRE   0x0010
#define HBA_PxCMD_FR    0x4000
#define HBA_PxCMD_CR    0x8000
 
void port_rebase(HBA_PORT *port, int portno)
{
	stop_cmd(port);	// Stop command engine
 
	// Command list offset: 1K*portno
	// Command list entry size = 32
	// Command list entry maxim count = 32
	// Command list maxim size = 32*32 = 1K per port
	port->clb = AHCI_BASE + (portno<<10);
	port->clbu = 0;
	memset((void*)(port->clb), 0, 1024);
 
	// FIS offset: 32K+256*portno
	// FIS entry size = 256 bytes per port
	port->fb = AHCI_BASE + (32<<10) + (portno<<8);
	port->fbu = 0;
	memset((void*)(port->fb), 0, 256);
 
	// Command table offset: 40K + 8K*portno
	// Command table size = 256*32 = 8K per port
	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)(port->clb);
	for (int i=0; i<32; i++)
	{
		cmdheader[i].prdtl = 8;	// 8 prdt entries per command table
					// 256 bytes per command table, 64+16+48+16*8
		// Command table offset: 40K + 8K*portno + cmdheader_index*256
		cmdheader[i].ctba = AHCI_BASE + (40<<10) + (portno<<13) + (i<<8);
		cmdheader[i].ctbau = 0;
		memset((void*)cmdheader[i].ctba, 0, 256);
	}
 
	start_cmd(port);	// Start command engine
}
 
// Start command engine
void start_cmd(HBA_PORT *port)
{
	// Wait until CR (bit15) is cleared
	while (port->cmd & HBA_PxCMD_CR);
 
	// Set FRE (bit4) and ST (bit0)
	port->cmd |= HBA_PxCMD_FRE;
	port->cmd |= HBA_PxCMD_ST; 
}
 
// Stop command engine
void stop_cmd(HBA_PORT *port)
{
	// Clear ST (bit0)
	port->cmd &= ~HBA_PxCMD_ST;
 
	// Wait until FR (bit14), CR (bit15) are cleared
	while(1)
	{
		if (port->cmd & HBA_PxCMD_FR)
			continue;
		if (port->cmd & HBA_PxCMD_CR)
			continue;
		break;
	}
 
	// Clear FRE (bit4)
	port->cmd &= ~HBA_PxCMD_FRE;
}




//AHCI & ATAPI

/*
The documentation regarding using the AHCI interface to access an ATAPI device 
(most likely an optical drive) is rather poorly explained in the specification.
However, once you understand that the HBA does most of the work for you it is rather simple. 
The AHCI/ATAPI method works by issuing the ATA PACKET command (0xA0) instead of the READ 
(READ is shown in the example below) and populating the ACMD field of the HBA_CMD_TBL with 
the 12/16 byte ATAPI command and setting the 'a' field to 1 in the HBA_CMD_HEADER which tells the
HBA to perform the multi-step process (all done automatically) of transmitting the PACKET command, 
then sending the ATAPI device the ACMD.
*/

//Example - Read hard disk sectors
/*
The code example shows how to read "count" sectors 
from sector offset "starth:startl" to "buf" with LBA48 mode from HBA "port". 
Every PRDT entry contains 8K bytes data payload at most.
*/



#define ATA_DEV_BUSY 0x80
#define ATA_DEV_DRQ 0x08
 
bool read(HBA_PORT *port, uint32_t startl, uint32_t starth, uint32_t count, uint16_t *buf)
{
	port->is = (uint32_t) -1;		// Clear pending interrupt bits
	int spin = 0; // Spin lock timeout counter
	int slot = find_cmdslot(port);
	if (slot == -1)
		return false;
 
	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER*)port->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D)/sizeof(uint32_t);	// Command FIS size
	cmdheader->w = 0;		// Read from device
	cmdheader->prdtl = (uint16_t)((count-1)>>4) + 1;	// PRDT entries count
 
	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL*)(cmdheader->ctba);
	memset(cmdtbl, 0, sizeof(HBA_CMD_TBL) +
 		(cmdheader->prdtl-1)*sizeof(HBA_PRDT_ENTRY));
 
	// 8K bytes (16 sectors) per PRDT
	for (int i=0; i<cmdheader->prdtl-1; i++)
	{
		cmdtbl->prdt_entry[i].dba = (uint32_t) buf;
		cmdtbl->prdt_entry[i].dbc = 8*1024-1;	// 8K bytes (this value should always be set to 1 less than the actual value)
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4*1024;	// 4K words
		count -= 16;	// 16 sectors
	}
	// Last entry
	cmdtbl->prdt_entry[i].dba = (uint32_t) buf;
	cmdtbl->prdt_entry[i].dbc = (count<<9)-1;	// 512 bytes per sector
	cmdtbl->prdt_entry[i].i = 1;
 
	// Setup command
	FIS_REG_H2D *cmdfis = (FIS_REG_H2D*)(&cmdtbl->cfis);
 
	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;	// Command
	cmdfis->command = ATA_CMD_READ_DMA_EX;
 
	cmdfis->lba0 = (uint8_t)startl;
	cmdfis->lba1 = (uint8_t)(startl>>8);
	cmdfis->lba2 = (uint8_t)(startl>>16);
	cmdfis->device = 1<<6;	// LBA mode
 
	cmdfis->lba3 = (uint8_t)(startl>>24);
	cmdfis->lba4 = (uint8_t)starth;
	cmdfis->lba5 = (uint8_t)(starth>>8);
 
	cmdfis->countl = count & 0xFF;
	cmdfis->counth = (count >> 8) & 0xFF;
 
	// The below loop waits until the port is no longer busy before issuing a new command
	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000)
	{
		spin++;
	}
	if (spin == 1000000)
	{
		trace_ahci("Port is hung\n");
		return FALSE;
	}
 
	port->ci = 1<<slot;	// Issue command
 
	// Wait for completion
	while (1)
	{
		// In some longer duration reads, it may be helpful to spin on the DPS bit 
		// in the PxIS port field as well (1 << 5)
		if ((port->ci & (1<<slot)) == 0) 
			break;
		if (port->is & HBA_PxIS_TFES)	// Task file error
		{
			trace_ahci("Read disk error\n");
			return FALSE;
		}
	}
 
	// Check again
	if (port->is & HBA_PxIS_TFES)
	{
		trace_ahci("Read disk error\n");
		return FALSE;
	}
 
	return true;
}
 
// Find a free command list slot
int find_cmdslot(HBA_PORT *port)
{
	// If not set in SACT and CI, the slot is free
	uint32_t slots = (m_port->sact | m_port->ci);
	for (int i=0; i<cmdslots; i++)
	{
		if ((slots&1) == 0)
			return i;
		slots >>= 1;
	}
	trace_ahci("Cannot find free command list entry\n");
	return -1;
}

