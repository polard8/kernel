
//grinput.h

#ifndef __DISPLAY_GRINPUT_H
#define __DISPLAY_GRINPUT_H    1

//
// Input events:
//

int wmMouseEvent(int event_id,long long1, long long2);
int 
wmKeyEvent(
    unsigned char raw_byte,
    int prefix );
int wmTimerEvent(int signature);


#endif    

