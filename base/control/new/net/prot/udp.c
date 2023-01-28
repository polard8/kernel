
// udp.c

#include <kernel.h>

char udp_payload[1024];

void 
network_handle_udp( 
    const unsigned char *buffer, 
    ssize_t size )
{
    struct udp_d *udp;

    printf("network_handle_ipv4: ==== UDP ====\n");

    udp = (struct udp_d *) buffer;
    if ( (void*) buffer == NULL )
        return;

    uint16_t sport = (uint16_t) FromNetByteOrder16(udp->uh_sport);
    uint16_t dport = (uint16_t) FromNetByteOrder16(udp->uh_dport);
    printf ("sp ={%d}\n",sport);
    printf ("dp ={%d}\n",dport);

    printf ("len={%d}\n",udp->uh_ulen);
    printf ("sum={%d}\n",udp->uh_sum);

    memset(udp_payload,0,sizeof(udp_payload));
    strncpy(
        udp_payload,
        (buffer + 6),
        512 );

    printf ("MESSAGE={%s}\n",udp_payload);

// Is it a valid port?
// Hang if the port is valid.
    if (dport == 34884){
        printf("udp: breakpoint\n");
        die();
    }
}


