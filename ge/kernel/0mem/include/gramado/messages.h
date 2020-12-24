/*
 * File: messages.h
 *
 *    Messages support.
 */


#ifndef __MESSAGES_H
#define __MESSAGES_H  1

struct message_d
{
    pid_t m_sender;
    pid_t m_receiver;

    void             *opaque;
    int               msg;
    unsigned long     long1;
    unsigned long     long2;
};

#endif    



