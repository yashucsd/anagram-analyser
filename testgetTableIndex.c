/*
 * Filename: testgetTableIndex.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Unit test program to test the function getTableIndex().
 * Date: 22 February 2017
 * Sources of Help
 */ 

#include <stdlib.h>

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"     /* For charCompare() function prototype */

/*
 * Unit Test for getTableIndex.s
 *
 * int getTableIndex( char const * ucSorted, size_t tableSize );
 *
 * Calculates the index of the ucSorted string (uppercase sorted
 * version of the string input by the user) in the hashtable of 
 * size tableSize.
 */
void testgetTableIndex() {

  char * str;
  size_t size;

  (void) printf( "Testing getTableIndex()\n" );

  str = "yash";
  size = 5;
  TEST( getTableIndex( str, size ) == 1 );

  str = "foo";
  size = 200;
  TEST( getTableIndex( str, size ) == 39 );

  str = "sdkjf";
  size = 10;
  TEST( getTableIndex( str, size ) == 9 );

  (void) printf( "Finished running tests on getTableIndex()\n" );
}


int main() {
  testgetTableIndex();

  return 0;
}
