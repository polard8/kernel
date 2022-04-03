
// UNAME.BIN

#include <stdio.h>
#include <sys/utsname.h>


/*
char  sysname[]  Name of this implementation of the operating system. 
char  nodename[] Name of this node within the communications 
                 network to which this node is attached, if any. 
char  release[]  Current release level of this implementation. 
char  version[]  Current version level of this release. 
char  machine[]  Name of the hardware type on which the system is running. 
*/

// See:
// https://man7.org/linux/man-pages/man2/uname.2.html

int main (int argc, char **argv)
{
    struct utsname name;

// #??
// Where are the strings?
// Do we have access to these addresses?

    uname(&name);

    //printf ("UNAME.BIN: Initializing ...\n");
    //fflush(stdout);

    printf ("kernel name:    %s \n",name.sysname);  //kernel name.
    printf ("kernel release: %s \n",name.release);  //kernel release name.
    printf ("kernel version: %s \n",name.version);  //kernel version.

    printf ("machine name:   %s \n",name.machine);  // hw name.
    printf ("host name:      %s \n",name.nodename); // node name in the network.

    //printf ("UNAME.BIN: Done\n");
    //fflush(stdout);

    while(1){}
        
    return 0;
}



