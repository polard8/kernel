
#include <stdio.h>

int main( int argc, char *argv[] ) {
  int i = 0;
  int arraySize;
  int *intArray;
  float *floatArray;

  printf("Enter the array size: ");
  scanf( "%d", &arraySize );
  printf("*** intArray ***\n");

  intArray = (int *) malloc( arraySize * sizeof( int ) );
  printf("sizeof( int ): %d\n", sizeof( int ) );

  for ( i=0; i < arraySize; i++ ) {
    intArray[i] = i * 2;
  }

  for ( i=0; i < arraySize; i++ ) {
    printf( "%d  %d\n", i, intArray[i] );
  }

  free( intArray );

  printf("*** floatArray ***\n");
  floatArray = (float *) malloc( arraySize * sizeof( float ) );
  printf("sizeof( float ): %d\n", sizeof( float ) );

  for ( i=0; i < arraySize; i++ ) {
    floatArray[i] = i * 2.5;
  }

  for ( i=0; i < arraySize; i++ ) {
    printf( "%d  %f\n", i, floatArray[i] );
  }

  return 0;
}

