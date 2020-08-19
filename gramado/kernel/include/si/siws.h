


// window server
int
si_send_to_ws ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
    
    
    
// enviando 4 longs par ao window server.
// todo: a estrutura de thread precisa comportar 
// a lista de mensagens com 4 longs.
// O mouse pode usar isso para enviar um pacote com 3 longs.
int
si_send_longmessage_to_ws ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2,
    unsigned long long3,
    unsigned long long4 );




