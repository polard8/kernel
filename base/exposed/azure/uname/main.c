
// UNAME.BIN
// 2022 - Fred Nora.

#include <types.h>
//#include <stddef.h>
#include <stdio.h>
#include <sys/utsname.h>

/*
char  sysname[]  Name of this implementation of the operating system. 
char  release[]  Current release level of this implementation. 
char  version[]  Current version level of this release. 
char  nodename[] Name of this node within the communications 
                 network to which this node is attached, if any. 
char  machine[]  Name of the hardware type on which the system is running. 
#todo: domain name.
*/
// See:
// https://man7.org/linux/man-pages/man2/uname.2.html

/*
static int is_64_kernel(void);
static int is_64_kernel(void)
{
    struct utsname un;
    int res=FALSE;

    if (uname (&un) < 0){
        return -1;
    }
    if (strcmp (un.machine, "x86_64") == 0){
        res=TRUE;
    }
    return (int) res;
}
*/


int main (int argc, char **argv)
{
// The kernel will put the strings here. I guess.
    struct utsname  un;


    int fRelease=FALSE;

// #todo: 
// Get parametes.

    uname(&un);

    // #debug
    printf("argc: {%d}\n",argc);

// get flags
    int i=0;
    for (i=0; i<argc; i++)
    {
        //printf("%d: %s\n",i, argv[i]);

        // Se em algum momento a flag for '-r'.
        if ( strncmp( argv[i], "-r", 2 ) == 0 )
        {
            fRelease = TRUE;
        }
    };



//
// Show only the release. (testing flags)
//

    if(fRelease==TRUE){
        printf ("kernel release: %s\n",un.release);
        return 0;
    }

//
// Show all
//

    printf ("\n");
// Kernel info
    printf ("kernel name:    %s\n",un.sysname);  //kernel name.
    printf ("kernel version: %s\n",un.version);  //kernel version.
    printf ("kernel release: %s\n",un.release);  //kernel release name.
// Machine info
    printf ("machine name:   %s\n",un.machine);  //hw name.
    printf ("host name:      %s\n",un.nodename); //node name in the network.
// #todo: Domain name.

    //while(1){
    //};
        
    return 0;
}

