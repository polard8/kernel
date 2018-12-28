
// sh.h 

//onde ficarão todos os header se possível. 


//Setup current compiler 
#include "compiler.h"


//lib C
//Isso deveria estar em um mesmo lugar para todos os aplicativos.
//ex: c:\gramado\g02\branch\libc
#include <types.h>
#include <stddef.h>
#include <stdarg.h>   
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>

#include <sys/wait.h>

#include <unistd.h>

//shell stuff 
#include "shell.h"
#include "globals.h"
#include "builtins.h"


//#test
#include <api/api.h>
//#include "api.h"

#include "desktop.h"

//# bash 1.05 stuff #
#include "variables.h"
#include "general.h"
#include "flags.h"
#include "alias.h"
#include "ndir.h"
#include "version.h"
//...

#include "lexer.h"
#include "parser.h"

#include "net.h"





