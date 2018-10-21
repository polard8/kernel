#include <stdio.h>
#include <strings.h>
#include "list.h"

list_t* newList() {
  list_t* temp;
  temp = (list_t*) malloc( sizeof( list_t ) );
  temp -> first_p = NULL;
  temp -> numElements = 0;
}

int size( list_t* list ) {
  return list -> numElements;
}

void add( list_t* list, int index, char* newItem ) {
  if ( (index > ( list -> numElements ) + 1) || (index < 1) ) {
    fprintf( stderr, "List Add Failure: size = %d, index = %d\n",
             list -> numElements, index );
    exit( 1 );
  }

  listElem_t* newElement = (listElem_t*) malloc( sizeof( listElem_t ));
  newElement -> item = strdup( newItem );

  if ( index == 1 ) {
    newElement -> next_p = list -> first_p;
    list -> first_p = newElement;
  }

  else {
    int i;
    listElem_t* curr = list -> first_p;
    for ( i = 1; i < index-1; i++ ) {
      curr = curr -> next_p;
    }
    newElement -> next_p = curr -> next_p;
    curr -> next_p = newElement;
  }
  list -> numElements++;
}

char* get( list_t* list, int index ) {
  if ( (index > ( list -> numElements )) || (index < 1) ) {
    fprintf( stderr, "List Get Failure: size = %d, index = %d\n",
             list -> numElements, index );
    exit( 1 );
  }

  int i;
  listElem_t* curr = list -> first_p;
  for ( i = 1; i < index; i++ ) {
    curr = curr -> next_p;
  }
  return strdup( curr -> item );
}

void removeAll( list_t* list ) {
  listElem_t *curr;
  listElem_t *next;

  curr = list -> first_p;
  while ( curr != NULL ) {
    next = curr -> next_p;
    free( curr -> item );
    free( curr );
    curr = next;
  }
  list -> numElements = 0;
  list -> first_p = NULL;
}
