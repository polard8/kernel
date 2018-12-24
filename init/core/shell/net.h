


//uint8_t mac_broadcast[6] =  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
//uint8_t xxx_ipv4[4] = { 0 };	
 


int netStream ( FILE *stream, int option );
int netSocket ( struct socket_d *socket, int option );
int netBuffer ( unsigned long buffer_address, int option );


void shellSocketTest();


