// atairq.c

#include <kernel.h>  



static unsigned long ata_irq_invoked = 0; 


//local
int disk_get_ata_irq_invoked (void);
void disk_reset_ata_irq_invoked (void);




void DeviceInterface_PrimaryIDE(void)
{
    // Se o ata1 não estiver inicializado !
    if ( __breaker_ata1_initialized == 0 )
        return;

    //
    // profiler
    //

    // Contando as interrupções desse tipo.
    g_profiler_ints_irq14++;

    ata_irq_invoked = TRUE;
}

void DeviceInterface_SecondaryIDE(void)
{
    // Se o ata2 não estiver inicializado !
    if ( __breaker_ata2_initialized == 0 )
        return;

    //
    // profiler
    //

    // Contando as interrupções desse tipo.
    g_profiler_ints_irq15++;

    ata_irq_invoked = TRUE;
}



__VOID_IRQ 
irq14_PRIMARY_IDE (void)
{
    debug_print("irq14_PRIMARY_IDE:\n");
}

__VOID_IRQ 
irq15_SECONDARY_IDE (void)
{
    debug_print("irq15_SECONDARY_IDE:\n");
}    


//local
int disk_get_ata_irq_invoked (void)
{
    return (int) ata_irq_invoked;
}

//local
void disk_reset_ata_irq_invoked (void)
{
    ata_irq_invoked = 0;
}










