
// events.h


#ifndef __EVENTS_H
#define __EVENTS_H    1


// It is global. 
// Valid for all the system.
// #performance
// Maybe change this can affect the performance.

#define MAXEVENTS 32
//#define MAXEVENTS 64


// tatamento de eventos como input de teclado e input de mouse.


// responders.
// id da janela(objeto) que responte a determonado evento.

int current_keyboard_responder;
int current_mouse_responder;
// ...


// event types.
// #remember:
// We are using window messages to handle the events.
// But all these types looks good to me.

typedef enum {

	EventTypeKeyDown,
	EventTypeKeyUp,
	EventSystemTypeKeyDown,
	EventSystemTypeKeyUp,
	EventTypeClick,
	EventTypeDoubleClick,
	EventTypeClickAndHold,
	EventTypeDragAndDrop,
	EventTypeMouseButtonDown,
	EventTypeMouseButtonUp,
	EventTypeMouseMove,
	EventTypeMouseOver,
	EventTypeMouseWheel,
	EventTypeMousePressed,
	EventTypeMouseReleased,
	EventTypeMouseClicked,
	EventTypeMouseEntered,
	EventTypeMouseExited,
	EventTypeMouseMoveByOffset,
	EventTypeMouseMoveToElement,
	// ...

}event_type_t;


//event classes.
typedef enum {

	EventClassKeyboard,
	EventClassMouse,
	//...

}event_class_t;



/*
typedef struct responder_d responder_t;
struct responder_d
{
};
*/


/*
typedef struct event_d event_t;
struct event_d
{
	event_type_t   EventType;
	event_class_t  EventClass;
	//...
}
*/


//
// == prototypes ======================================
//

void set_current_keyboard_responder ( int i );
int get_current_keyboard_responder (void);

void set_current_mouse_responder ( int i );
int get_current_mouse_responder (void);


#endif    


