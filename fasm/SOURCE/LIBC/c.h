
// c.h 

#include "config.h"
#include "debug.h"


#include <types.h>
#include <ctype.h>

#include "heap.h"
#include "api.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#include "table.h"
#include "lexer.h"
#include "parser.h"

#include "fasm.h"


//fasm support 

FILE *fasm_fopen( const char *filename, const char *mode ); 
void fasm_exit(int code);
void testWrite();
size_t fasm_write (int fd, char *buf, size_t cnt);






