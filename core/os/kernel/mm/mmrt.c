
// mmrt.c
// Runtime support.
// System memory initialization.
// Heap, stack, memory usage and frames.

#include <kernel.h>

static int __init_runtime(int arch_type);


// Private:
// Initializing runtime. 
// Kernel heap and stack initialization.

static int __init_runtime(int arch_type)
{
    int Status=0;

    //debug_print ("init_runtime:\n");
    //debug_print ("[Kernel] init_runtime: Initializing runtime ...\n");

    //if (g_module_runtime_initialized == TRUE){
    //    Already initialized.
    //}

    switch (arch_type){
    // See: mminit.c
    case CURRENT_ARCH_X86_64:
        Status = (int) mmInit();
        if (Status < 0)
        {
            if (Initialization.is_serial_log_initialized == TRUE){
                debug_print("__init_runtime: mmInit fail\n");
            }
            goto fail;
        }
        return TRUE;  // OK.
        break;
    // armmain(); ?
    // ...
    default:
        if (Initialization.is_serial_log_initialized == TRUE){
            debug_print ("__init_runtime: current_arch\n");
        }
        goto fail;
        break; 
    };

// #todo: Testar esses comentários.
// Now we have malloc, free and messages support.
// The video support is using the boot loader configuration yet.
// Provavelmente aqui é o primeiro lugar onde as mensagens funcionam.
// Mas temos um problema no Y.

fail:
    return FALSE;
}


// Called by init.c
int Runtime_initialize(int arch_type)
{
    int Status=0;

    //debug_print ("Runtime_initialize:\n");

    g_module_runtime_initialized = FALSE;

    Status = (int) __init_runtime(arch_type);
    if (Status!=TRUE){
        if (Initialization.is_serial_log_initialized == TRUE){
            debug_print("Runtime_initialize: __init_runtime fail\n");
        }
        die();
    }

    // ...

    //debug_print ("Runtime_initialize: done\n");
    
    g_module_runtime_initialized = TRUE;
    
    return 0;
}

