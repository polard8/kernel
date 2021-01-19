// UNAME.BIN

#include <stdio.h>
#include <sys/utsname.h>


/*
//crazy test
void print_4_chars( unsigned long value )
{
    char chars[4];
    
    chars[0] = (char) value;
    chars[1] = (char) (value >> 8);
    chars[2] = (char) (value >> 16);
    chars[3] = (char) (value >> 24);

    printf ("%c%c%c%c",
        chars[0],chars[1],chars[2],chars[3]); 
    fflush(stdout);
}
*/

int main (int argc, char **argv)
{
    struct utsname name;

    uname(&name);

    printf ("%s version %s %s, on %s machine named %s.\n",
        name.sysname, 
        name.release, 
        name.version,
        name.machine, 
        name.nodename );

    //crazy test  efgh
    //while(1){
    //    print_4_chars(0xFFFFFFFF);
    //}
    
    return 0;
}





