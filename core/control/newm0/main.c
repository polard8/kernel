
// main file for the ring 0 kernel module.
// called by ./crt0.c
// #todo: Do not use 'interrupts'.

#include "newm0.h"

struct module_initialization_d  ModuleInitialization;


// kernel sysboltable address.
// unsigned long imported_functions[32];
unsigned long *kfunctions;
int DIE=0;      //it works
int PUTCHARK=1; //it works
int REBOOT=2;   //it works
int REFESHSCREEN=3;
int PUTCHAR_FGCONSOLE=4;  //(1arg)
// #todo: Call dead thread collector, scheduler ...
// read flags
// read messages
// ...

// -------------------

static void caller0(unsigned long function_address);
static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 );

static inline void do_int3(void);
static inline void do_hlt(void);

int module_strlen(const char *s);
void *memset ( void *ptr, int value, int size );
char *strcpy ( char *to, const char *from );
char *kinguio_itoa (int val, char *str);
void 
kinguio_i2hex( 
    unsigned int val, 
    char *dest, 
    int len );
    
static int newm0_1001(void);
static int newm0_initialize(void);
static void newm0_print_string (char *s);

// printf support.
void kinguio_puts(const char* str);
static char *_vsputs_r(char *dest, char *src);
int 
kinguio_vsprintf(
    char *str, 
    const char *fmt, 
    va_list ap );
int kinguio_printf(const char *fmt, ...);
int mysprintf(char *buf, const char *fmt, ...);

#define printf   kinguio_printf
#define printk   kinguio_printf
#define sprintf  mysprintf


// -----------------------------

//strlen
// strlen:
//    Give the string lenght in bytes.

int module_strlen(const char *s)
{
    register int i=0;

//#todo
    //if ( (void *) s == NULL ){ return -1; }

    for ( i=0; s[i] != '\0'; ++i )
    {
    };

    return (int) i;
}

void *memset ( void *ptr, int value, int size )
{
    register int i=0;

    if ( ptr != NULL && size > 0 )
    {
        //#bugbug.
        unsigned char *temp = ptr;

        for ( i=0; i < size; i++ )
        {
            *temp++ = (unsigned char) value;
        };
    }

    return (void *) ptr;
}

// strcpy:  
//     Copy a string
char *strcpy ( char *to, const char *from )
{
    register int i=0;

    while ( to[i] = from[i] )
    {
        i += 1;
    };

    return (to);
}

char *kinguio_itoa (int val, char *str) 
{
    int value = val;
    char *valuestring = (char *) str;
    int min_flag=0;
    char swap=0; 
    char *p;

    if (0 > value)
    {
        *valuestring++ = '-';
        value = -____INT_MAX> value ? min_flag = ____INT_MAX : -value;
    }

    p = valuestring;

    do {
         *p++ = (char) (value % 10) + '0';
         value /= 10;
    } while (value);

    if (min_flag != 0)
    {
        ++*valuestring;
    }

    *p-- = '\0';

    while (p > valuestring)
    {
        swap = *valuestring;
        *valuestring++ = *p;
        *p-- = swap;
    };

    return str;
}

void 
kinguio_i2hex( 
    unsigned int val, 
    char *dest, 
    int len )
{
    char *cp;
    register int i=0;
    int x=0;
    unsigned n=0;  //??

    if (val == 0)
    {
        cp = &dest[0];
        *cp++ = '0';
        *cp = '\0';
        return;
    }

    n = val;
    cp = &dest[len];

    while (cp > dest)
    {
        x = (n & 0xF);
        n >>= 4;
        
        // #
        *--cp = x + ((x > (HEX_LEN+1)) ? 'A' - 10 : '0');
    };

    dest[len] = '\0';

    cp = &dest[0];

    for (i=0; i<len; i++)
    {
        if (*cp == '0'){
            cp++;
        }else{
            strcpy (dest,cp);
            break;
        };
    }

    cp = &dest[0];
    n = module_strlen(cp);

    memset( (dest+n), 0, (8-n) );
}



// Print a string.
void kinguio_puts(const char* str)
{
    register int i=0;
    ssize_t StringLen=0;
    int _char=0;

    if (ModuleInitialization.initialized != 1){
        return;
    }

    if (!str){
        return;
    }

    StringLen = (ssize_t) module_strlen(str);
    if (StringLen<=0)
        return;

// Print chars. 
    for (i=0; i<StringLen; i++)
    {
        _char = (int) ( str[i] & 0xFF );
        caller1( 
            kfunctions[PUTCHAR_FGCONSOLE], 
            _char ); 
    };
}

static char *_vsputs_r(char *dest, char *src)
{
    unsigned char *usrc = (unsigned char *) src;
    unsigned char *udest = (unsigned char *) dest;

    while ( *usrc )
    { 
        *udest++ = *usrc++; 
    };

    return (char *) udest;
}


int 
kinguio_vsprintf(
    char *str, 
    const char *fmt, 
    va_list ap )
{
    char *str_tmp = str;
    int index=0;
    unsigned char u=0;
    int d=0;
    char c=0; 
    char *s;
    char buffer[256];  //#bugbug: Too short.
    char _c_r[] = "\0\0";

    while ( fmt[index] )
    {
        switch (fmt[index]){

        case '%':

            ++index;

            switch (fmt[index]){

            case 'c':
                *_c_r = c = (char) va_arg (ap, int);
                str_tmp = _vsputs_r(str_tmp,_c_r);
                break;

            case 's':
                s = va_arg (ap, char*);
                str_tmp = _vsputs_r(str_tmp,s);
                break;

            case 'd':
            case 'i':
                d = va_arg (ap, int);
                kinguio_itoa (d,buffer);
                str_tmp = _vsputs_r(str_tmp,buffer);
                break;

            case 'u':
                u = va_arg (ap, unsigned int);
                kinguio_itoa (u,buffer);
                str_tmp = _vsputs_r(str_tmp,buffer);
                break;

            case 'X':
            case 'x':
                d = va_arg (ap, int);
                kinguio_i2hex(d, buffer,8);
                str_tmp = _vsputs_r(str_tmp,buffer);
                break;

            default:
                str_tmp = _vsputs_r(str_tmp,"%%");
                break;
            }
            break;

        default:
            *_c_r = fmt[index];
            str_tmp = _vsputs_r(str_tmp,_c_r);
            break;
        }
        ++index;
    }

    return (int) ( (long) str_tmp - (long) str );
}


// printf implementation.
// Credits:
// Nelson Cole. Kinguio/Sirius OS.
int kinguio_printf(const char *fmt, ...)
{
    static char data_buffer[1024];
    int ret=0;

/*
// If the virtual console isn't full initialized yet.
    if (Initialization.console_log != TRUE){
        return -1;
    }
*/
    memset (data_buffer, 0, 1024); 

//----------
    va_list ap;
    va_start(ap, fmt);
    ret = kinguio_vsprintf(data_buffer, fmt, ap);
    va_end(ap);
//-----------

// Print the data buffer.
    kinguio_puts(data_buffer);

    return (int) ret;
}
// ===================================

// mysprintf: (sprintf)
// Variable parameter form to achieve sprintf.
int mysprintf(char *buf, const char *fmt, ...)
{
    int i=0;

// Write the fmt format string to the buffer buf 
    va_list args;
    va_start(args, fmt);
    i = kinguio_vsprintf(buf, fmt, args);
    va_end(args);

    return (int) i;
}



static inline void do_int3(void)
{
    asm ("int $3");
}

static inline void do_hlt(void)
{
    asm ("hlt");
}

static void caller0(unsigned long function_address)
{
    asm ("call *%0" : : "r"(function_address));
}

static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 )
{

    int x = (int) (data0 & 0xFF);
    int y = (int) (data0 & 0xFF);

// #todo: Simplify

    asm ("movl %1, %%eax;"
         "movl %%eax, %0;"
         "movl %%eax, %%edi;"
         :"=r"(y)        /* output */
         :"r"(x)         /* input */
         :"%eax"         /* clobbered register */
    );   

    //asm (" movq $65, %rdi ");
    
    asm ("call *%0" : : "r"(function_address));
}

static void newm0_print_string (char *s)
{
    register int i=0;
    int size=0;
    size = module_strlen(s);
    if (size <= 0)
        return;
    for (i=0; i<size; i++)
    {
        caller1( 
            kfunctions[PUTCHAR_FGCONSOLE], 
            s[i] );
    };
}

static int newm0_initialize(void)
{

// The kernel static entry point.
// #bugbug: It's not safe.
// We need a random address.
    unsigned char *k = (unsigned char *) 0x30001000;

// #test
// Lookup for "__GRAMADO__"
// see: head_64.asm
    register int i=0;
    int Found=0;  //FALSE
    unsigned long __function_table=0;

    ModuleInitialization.initialized = 0;

    for (i=0; i<100; i++)
    {
        if (k[i+0]  == '_' &&
            k[i+1]  == '_' &&
            k[i+2]  == 'G' &&
            k[i+3]  == 'R' &&
            k[i+4]  == 'A' &&
            k[i+5]  == 'M' &&
            k[i+6]  == 'A' &&
            k[i+7]  == 'D' &&
            k[i+8]  == 'O' &&
            k[i+9]  == '_' &&
            k[i+10] == '_')
        {
            Found = 1;
            // The function table starts here.
            __function_table = (unsigned long) &k[i+11];
        }
    };

// Symbol table 'exported' hehe by the kernel.
    //unsigned long *kfunctions = (unsigned long *) __function_table;
    kfunctions = (unsigned long *) __function_table;

// done?
    // TRUE
    if (Found==1)
    {
        ModuleInitialization.initialized = 1;
        newm0_print_string("newm0_initialize: Initialized\n");
        return 0;
    }

fail:
    ModuleInitialization.initialized = 0;
    return -1;
}


static int newm0_1001(void)
{
    if (ModuleInitialization.initialized != 1){
        return -1;
    }
    newm0_print_string("newm0_1001: reason 1001\n");

    //for (i=0; i<100; i++)
    //    caller0( (unsigned long) kfunctions[PUTCHARK] );

    //caller0( (unsigned long) kfunctions[DIE] );
    //caller0( (unsigned long) kfunctions[PUTCHARK] );
    //caller0( (unsigned long) kfunctions[REBOOT] );
    //do_int3();
    //caller1( kfunctions[PUTCHAR_FGCONSOLE], 'x');

// #testing printf
    int value=1234;
    printf("mod0.bin: {%d} Testing printf :)\n",value);

// Done
    return 0;
}

// ---------------------------
// main:
int main( int arc, char *argv[], int reason )
{

    if (reason<0)
        return -1;

    switch (reason){
        case 1000:
            return (int) newm0_initialize();
            break;
        case 1001:
            return (int) newm0_1001();
            break;
        default:
            return -1;
            break;
    };

    return -1;
}

