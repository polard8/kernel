
   // Os cpodigos da libgws vão precisar disso 
   // pra se conectarem com o Window Server. gws
   
#ifndef _GWS_CONNECT_H_
#define _GWS_CONNECT_H_



int gws_connect (void);
int gws_get_connect_status(void);
int gws_get_client_fd(void);
int gws_get_desktop_id(void);
int gws_initialize_connection(void);
unsigned long gws_get_message_buffer(void);




#endif 







