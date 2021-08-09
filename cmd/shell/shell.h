
// shell.h

int main ( int argc, char *argv[] );

unsigned long shellCompare (void);

int 
shellProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

void shellPrompt (void); 

void shell_clear_screen(void);

void 
__shell_draw_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height,
    int color );

void 
__shell_refresh_rectangle ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long width, 
    unsigned long height );
    




