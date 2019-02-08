
// File: gde.h
//     header de mais alto nivel do ambiente gde.

//level 1:
//    +gde.h
//level 2:
//    +gdeapi.h
//    +gdelib.h
//level 3:
//    +todas as outras libs.
//


//8.3


//wrappers para rotinas de alto nivel.
#include "gdeapi.h"

//wrapper para rotinas de baixo nivel.
#include "gdelib.h"


void *gde_system_call ( unsigned long ax, 
                        unsigned long bx, 
				        unsigned long cx, 
				        unsigned long dx );







