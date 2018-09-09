#include <stdio.h>
#include "list.h"

void printList( list_t* );

int main( int argc, char* argv[] ) {
  list_t* myList = newList();

  add(myList, size(myList)+1, "Hello");
  add(myList, size(myList)+1, "World");
  add(myList, size(myList)+1, "Goodbye");

  printf("List size = %d\n", size( myList ) );
  printList( myList );

  char* myString = "Cruel";
  add(myList, 2, myString );
  printList( myList );

  myString = get( myList, 3 );
  *myString = 'X';
  add( myList, 4, myString );
  printList( myList );
  removeAll( myList );
  printList( myList );
  add( myList, 1, "abc" );
  printList( myList );

}

void printList( list_t* list ) {
  int i;
  printf("***\n"); 
  if ( size( list ) == 0 )
    printf("List is empty\n");
  else {
    for ( i = 1; i <= size( list ); i++ ) {
      printf("%s\n", get( list, i ) );
    }
  }
  printf("***\n"); 
}

