
// events.h



// tatamento de eventos como input de teclado e input de mouse.



//
// responders.
//id da janela(objeto) que responte a determonado evento.
//
int current_keyboard_responder;
int current_mouse_responder;
//...


//event types.
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
	
	//...
	
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

void set_current_keyboard_responder( int i );
int get_current_keyboard_responder();
void set_current_mouse_responder( int i );
int get_current_mouse_responder();


