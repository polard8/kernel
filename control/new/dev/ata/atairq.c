// atairq.c

#include <kernel.h>  


static int ata_irq_invoked = FALSE;

//
// == Private functions: Prototypes ======================
//

// Handlers for irqs.
static void DeviceInterface_PrimaryIDE(void);
static void DeviceInterface_SecondaryIDE(void);

static int disk_get_ata_irq_invoked (void);
static void disk_reset_ata_irq_invoked (void);

// ========================================================

static void DeviceInterface_PrimaryIDE(void)
{
    // Device not initialized.
    if ( __breaker_ata1_initialized == FALSE )
        return;

// Profiler: Counting interrupts.
    g_profiler_ints_irq14++;

// Set flag.
    ata_irq_invoked = TRUE;
}


static void DeviceInterface_SecondaryIDE(void)
{
    // Device not initialized.
    if ( __breaker_ata2_initialized == FALSE )
        return;

// Profiler: Counting interrupts.
    g_profiler_ints_irq15++;

// Set flag.
    ata_irq_invoked = TRUE;
}


//local
static int disk_get_ata_irq_invoked (void)
{
    return (int) ata_irq_invoked;
}

//local
static void disk_reset_ata_irq_invoked (void)
{
    ata_irq_invoked = FALSE;
}



// global
__VOID_IRQ 
irq14_PRIMARY_IDE (void)
{
    debug_print("irq14_PRIMARY_IDE:\n");
    DeviceInterface_PrimaryIDE();
}


// global
__VOID_IRQ 
irq15_SECONDARY_IDE (void)
{
    debug_print("irq15_SECONDARY_IDE:\n");
    DeviceInterface_SecondaryIDE();
}


/*
 * ata_wait_irq:
 * 
 */

// #bugbug
// Veja se é possível mudar o retorno para 'int'.
// #obs: Tem uma função semelhante logo abaixo.

unsigned char ata_wait_irq (void)
{
    unsigned long tmp = 0x10000;
    unsigned char data=0;


    while (!ata_irq_invoked)
    {
        data = ata_status_read();

        if ( (data & ATA_SR_ERR) )
        {
            ata_irq_invoked = FALSE;

            // #bugbug: 
            // Returning -1 on unsigned char.

            return -1;
        }

        // ns
        if (--tmp){ 
            ata_wait(400);
        }else{
            ata_irq_invoked = FALSE;
            return 0x80;
        };

    };

    disk_reset_ata_irq_invoked();
    //ata_irq_invoked = FALSE;
    
    return 0;
}


/*
 * disk_ata_wait_irq:
 *     Esperando pela interrupção.
 *
 */

// #obs: Tem uma função semelhante logo acima.

// OUT:
//     0    = ok por status da interrupção. 
//     -1   = ok por status do controlador.
//     0x80 = ok por tempo esperado.

int disk_ata_wait_irq (void)
{
    unsigned long tmp = 0x10000;
    unsigned char data=0;

    while (!ata_irq_invoked)
    {
        data = ata_status_read();
        
        if ( (data & ATA_SR_ERR) )
        {
            // ok por status do controlador.
            ata_irq_invoked = FALSE;
            
            return (int) -1;
        }

        //ns
        if (tmp--){
            ata_wait(400);
        }else{

            //ok por tempo esperado.
            ata_irq_invoked = FALSE;

            return (int) 0x80;
        };
    };

// ok por status da interrupção.
    ata_irq_invoked = FALSE;
    return 0;
}

