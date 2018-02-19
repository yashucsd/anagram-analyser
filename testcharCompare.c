/*
 * Filename: testcharCompare.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Unit test program to test the function charCompare().
 * Date: 22 February 2017
 * Sources of Help
 */ 

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"     /* For charCompare() function prototype */


/*
 * Unit Test for charCompare.s
 *
 * int charCompare( void const * p1, void const * p2 );
 *
 * Compares the two characters passed in.  Returns -1 if the first character
 * is smaller, 0 if the characters are the same, or +1 if the first character
 * is larger.
 */
void testcharCompare() {
  char lhs;
  char rhs;

  (void) printf( "Testing charCompare()\n" );

  lhs = 'm';
  rhs = 'j';
  TEST( charCompare( &lhs, &rhs ) == 1 );

  lhs = 'x';
  rhs = 'y';
  TEST( charCompare( &lhs, &rhs ) == -1 );

  rhs = 'x';
  TEST( charCompare( &lhs, &rhs ) == 0 );


  (void) printf( "Finished running tests on charCompare()\n" );
}


int main() {
  testcharCompare();

  return 0;
}
