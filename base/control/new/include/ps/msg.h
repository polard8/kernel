
// msg.h

#ifndef __PS_MSG_H
#define __PS_MSG_H    1

// -----------------------------------------------------
// Message structure.
struct msg_d 
{
// validation
    int used;
    int magic;

// -----------------------
// Standard header
    void *opaque_window;
    int msg;
    unsigned long long1;
    unsigned long long2;
// -----------------------
// Extra payload
    unsigned long long3;
    unsigned long long4;

// extention
    pid_t sender_pid;
    pid_t receiver_pid;
    tid_t sender_tid;
    tid_t receiver_tid;
    // ...
    //unsigned long jiffie1;
    //unsigned long jiffie2;
// #todo
// We need some synchronization flags.
// Maybe its better putting this flag into the thread struct.
// t->msg_flags;
    //unsigned long flags;
// navigation?
    struct msg_d *next;
};

#endif    




