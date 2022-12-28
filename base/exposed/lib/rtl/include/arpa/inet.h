
// arpa/inet.h

// Functions for manipulating numeric IP addresses.
// See:
// https://en.wikipedia.org/wiki/Berkeley_sockets


#ifndef _INET_H
#define _INET_H


/*
Description
The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.

The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.

The ntohl() function converts the unsigned integer netlong from network byte order to host byte order.

The ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.  
 
 */


// little endian
//#define ToNetByteOrder16(v) ((v >> 8) | (v << 8))
//#define ToNetByteOrder32(v) (((v >> 24) & 0xFF) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v << 24) & 0xFF000000))
//#define FromNetByteOrder16(v) ((v >> 8) | (v << 8))
//#define FromNetByteOrder32(v) (((v >> 24) & 0xFF) | ((v << 8) & 0xFF0000) | ((v >> 8) & 0xFF00) | ((v << 24) & 0xFF000000))



/*
uint16_t htons(uint16_t hostshort);
uint32_t htonl(uint32_t hostlong);

uint16_t ntohs(uint16_t netshort);
uint32_t ntohl(uint32_t netlong);
*/


// Not tested
uint16_t htons(uint16_t hostshort)
{
    return (uint16_t) ((hostshort >> 8) | (hostshort << 8));
}

// Not tested
uint32_t htonl(uint32_t hostlong)
{
    return (uint32_t) (((hostlong >> 24) & 0xFF) | 
                       ((hostlong << 8)  & 0xFF0000) | 
                       ((hostlong >> 8)  & 0xFF00) | 
                       ((hostlong << 24) & 0xFF000000));
}

// Not tested
uint16_t ntohs(uint16_t netshort)
{
    return (uint16_t) ((netshort >> 8) | (netshort << 8));
}

// Not tested
uint32_t ntohl(uint32_t netlong)
{
    return (uint32_t) (((netlong >> 24) & 0xFF) | 
                       ((netlong << 8)  & 0xFF0000) | 
                       ((netlong >> 8)  & 0xFF00) | 
                       ((netlong << 24) & 0xFF000000));
}


/*
//not tested
uint16_t ____htons (uint16_t  w)
{ 
    return (w & 0xff) << 8 | ((w >> 8) & 0xff); 
}
*/


/*
//not tested
uint16_t ____ntohs (uint16_t  w)
{ 
    return (w & 0xff) << 8 | ((w >> 8) & 0xff); 
}
*/


#endif  //inet.h



