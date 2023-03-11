
// room.h
// Room support.
// A kind of 'windows station' or 'surfaces station'.

#ifndef __VEM_ROOM_H
#define __VEM_ROOM_H    1

struct room_d
{
    object_type_t  objectType;
    object_class_t objectClass;
// RID - Room ID.
    int id;
    int used;
    int magic;
    uid_t uid;

// Desktops
    unsigned long desktop_list[32];

    struct room_d *room;

// Navigation
    struct room_d *next;
};
// #todo
// Use external reference here.
struct room_d  *room0;
struct room_d  *CurrentRoom;
//...

// List
unsigned long roomList[ROOM_COUNT_MAX];

//
// == prototypes ============================
//

#endif    




