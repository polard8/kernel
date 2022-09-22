/*
 * File: menu.h 
 * 
 * 
 *     This header should be included by including "gws.h".
 */


#ifndef __LIBGWS_MENU_H
#define __LIBGWS_MENU_H  1

struct gws_menu_item_d
{
    int id;

    int window;
    
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
    
    unsigned long color;
    
    int selected;

    struct gws_menu_item_d *next;
};


struct gws_menu_d
{

    int window;
    int parent;

    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;

    unsigned long color;
    
    int highlight; //item em destaque
    
    //list
    int itens_count;
    struct gws_menu_item_d *list;
};


#endif    


