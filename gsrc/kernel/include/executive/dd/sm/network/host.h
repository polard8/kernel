/*
 * Arquivo host.h
 *
 * Descrição:
 *     Gerenciamneto de host.
 *
 * Versão: 1.0, 2016.
 */

/*
   exemplo
   
char *h_name

The real canonical host name.

char **h_aliases

A list of aliases that can be accessed with arrays—the last element is NULL

int h_addrtype

The result's address type, which really should be AF_INET for our purposes.

int length

The length of the addresses in bytes, which is 4 for IP (version 4) addresses.

char **h_addr_list

A list of IP addresses for this host. Although this is a char**, 
it's really an array of struct in_addr*s in disguise. The last array element is NULL.

h_addr

A commonly defined alias for h_addr_list[0]. If you just want any old IP address
 for this host (yeah, they can have more than one) just use this field.
   
*/


/*
   exemplo
The C data structure used to represent addresses and hostnames within the networking API is the following:

 struct addrinfo {
    int     ai_flags;
    int     ai_family;
    int     ai_socktype;
    int     ai_protocol;
    size_t  ai_addrlen;
    struct  sockaddr* ai_addr;
    char*   ai_canonname;     // canonical name 
    struct  addrinfo* ai_next; // this struct can form a linked list 
};


  struct hostent {
            char   *h_name;
            char   **h_aliases;
            int    h_addrtype;
            int    h_length;
            char   **h_addr_list;
          };

struct addrinfo {
          int              ai_flags;  
          int              ai_family;
          int              ai_socktype; 
          int              ai_protocol;
          size_t           ai_addrlen;
          struct sockaddr *ai_addr;
          char            *ai_canonname;
          struct addrinfo *ai_next;
      };

struct sockaddr_in {
    short            sin_family;   //address family, set to AF_INET
    unsigned short   sin_port;     //the port in network byte order
    struct in_addr   sin_addr;     //the inet address
};	  
*/


#define HOST_DEFAULTNAME  "admin" 

typedef struct host_info_d host_info_t;
struct host_info_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
    //id.
	unsigned long host_id;
	
	unsigned long name_address;
	
    //char *name;
	//char *alias;
	
	//int length; The length of the addresses in bytes, which is 4 for IP (version 4) addresses.
	
	//...
};
host_info_t *HostInfo;
//...




//char * get_host_name();



//
//fim.
//

