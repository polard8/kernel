
// newm0.h

#ifndef __NEWM0_H
#define __NEWM0_H  1

#include "klimits.h"
#include "ktypes.h"
#include "ktypes2.h"
#include "kstddef.h"
#include "kstdarg.h"

struct module_initialization_d
{
    int initialized;
    //unsigned long ksysmboltable_address;
};
extern struct module_initialization_d  ModuleInitialization;



#endif  


