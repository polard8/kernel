


// ===========================
// #todos
// post_message(?);  
// the server is posting a message to the client ...
// meybe some kind of dual communication ...
// its good in some kind of servers ... may not in the window server.
//it looks like a post_reaponse()

// handle_messages(?) //??



// #todo
void drain_message_from_client (struct socket_d *sock);
void drain_message_from_client (struct socket_d *sock){

    int nreads = 0;
    char buffer[512];

    if ( (void *) sock == NULL ){
        printf("drain_message_from_client: Couldn't drain message\n");
        refresh_screen();
        return -1;
    }

    for(;;){
    
        nreads = (int) recv (sock->_file, buffer, sizeof(buffer), 0 );
        if(nreads == 0){
            return;   // #test: Return for now.
        }

        printf(">>> %s \n",buffer);
    }
}
