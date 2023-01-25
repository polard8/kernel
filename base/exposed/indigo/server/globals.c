

#include <gnsint.h>


// Buffer for the messages.
// see: global.h
char __buffer[GNS_BUFFER_SIZE];

// Buffer
// This is the buffer ussed for the next response.
// Marsheling ...
// Esses valores serão enviados como
// resposta ao serviço atual.
// Eles são configurados pelo dialogo na hora da
// prestação do serviço.
// No início desse array fica o header.
// see: globals.h
unsigned long next_response[32];

