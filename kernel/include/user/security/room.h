
// room.h

#ifndef ____ROOM_H
#define ____ROOM_H    1

struct room_d
{
    //int dummmy;

    object_type_t  objectType;
    object_class_t objectClass;

    int id;

    int used;
    int magic;

    int userID;

//
// Desktops
//

    unsigned long desktop_list[32];


    struct room_d *room;

    // Navigation
    struct room_d *next;
};

struct room_d  *room0;
struct room_d  *CurrentRoom;
//...

// List
unsigned long roomList[ROOM_COUNT_MAX];


//
// == prototypes ============================
//



#endif    




