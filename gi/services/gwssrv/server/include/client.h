
// Nesse arquivo fica a estrutura de cliente.
// Essa estrutura vai conter as informações
// e características dos clientes.


//
// Current
//

// Mandaremos as mensages para a fila de mensagens do cliente atual
// para isso o window server precisa constantemente ler sua fila de
// mensagens.
// O kernel alimenta a fila de mensagens do ws qunado tem um ws
// instalado.

int current_client;


struct gws_client_d
{
    int id;
    
    // structure validation
    int used;
    int magic;
    

    
    // ??
    // The PID of the client.
    int pid; //pid_t
    
    
    //Message queue.

    //
    // Queue. (list)
    //

    struct window_d  *window_list[32];
    int               msg_list[32];
    unsigned long     long1_list[32];
    unsigned long     long2_list[32];
    int tail_pos;
    int head_pos;


    // ...
};



