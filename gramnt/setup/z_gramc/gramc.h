/*
 * gramc.h
 *     This is the main header.
 * 
 *  2018 - Created by Fred Nora.
 */


// Config and debug support.
#include "config.h"
#include "debug.h"


// Libc support.
#include <types.h>
#include <ctype.h>
#include <heap.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>


// API.
// Animal and Gramado operating systems.
#include <api.h>



// gramc 
#include "gdef.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "tree.h" 
#include "compiler.h" 



//
// Prototypes.
//


// #bugbug: O lugar disso é no crt0.c. deletar.
int main ( int argc, char *argv[] );

int gramcInitialize (void);







