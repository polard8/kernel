
// globals.h

#ifndef __GLOBALS_H
#define __GLOBALS_H    1

// We need 2 asm statement inside a block {} to fill
// a single structure.
struct metadata_d
{
    int id;
    int initialized;

    char name[64];
    int name_size;

    char content[128];
    int content_size;
};
extern struct metadata_d  metadata[32];

// Contador para não estourar a lista. 
extern int keyword_count; 
extern int identifier_count; 
extern int constant_count; 
extern int string_count; 
extern int separator_count; 
extern int special_count;

extern int maxtoken;       /* Current length of token buffer */
extern char *token_buffer; /* Pointer to token buffer */

#define MAXTOKEN  256 
extern char real_token_buffer[MAXTOKEN];

#endif    


