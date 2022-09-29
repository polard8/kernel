/*
 * gramcnf.h
 *     This is the main header.
 *  2018 - Created by Fred Nora.
 */

// Config and debug support.
#include "config.h"
#include "debug.h"

// rtl
#include <types.h>
#include <ctype.h>
#include <heap.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// libcore
// #deprecated
//#include <api.h>

// gramc 
#include "gdef.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "tree.h" 
#include "compiler.h" 


//
// Prototypes ===========================================
//

int gramcInitialize (void);

