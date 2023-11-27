
//grinput.h

#ifndef __DISPLAY_GRINPUT_H
#define __DISPLAY_GRINPUT_H    1


// Basic block of data to handle input events.
// Used PS2 keyboard and PS2 mouse for now.
// See: grinput.c
struct input_block_d
{
    int ev_code;
    unsigned long long1;
    unsigned long long2;
};


struct input_event_d
{
// data
    struct input_block_d  in;
    int type;  // input type
    unsigned long jiffies;   // time
    // ...
};

//
// Input events:
//

int wmMouseEvent(int event_id,long long1, long long2);
int 
wmKeyEvent(
    unsigned char raw_byte,
    int prefix );
int wmTimerEvent(int signature);

int 
keProcessInput ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );


#endif    

