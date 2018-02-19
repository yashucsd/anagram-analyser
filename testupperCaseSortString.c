/*
 * Filename: testupperCaseSortString.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Unit test program to test the function upperCaseSortString().
 * Date: 22 February 2017
 * Sources of Help
 */ 

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"     /* For charCompare() function prototype */

#include <string.h>
#include <stdio.h>


/*
 * Unit Test for upperCaseSortString.c
 *
 * void upperCaseSortString( char const * src, int n, char * dest );
 *
 * This function will take the src string (of length n) and will store a copy in
 * dest where all the characters are converted to uppercase and sorted in
 * alphabetical order.
 */
void testupperCaseSortString() {

  char * src;
  int n;
  char dest [BUFSIZ];

  (void) printf( "Testing upperCaseSortString()\n" );

  src = "yash";
  n = 4;
  upperCaseSortString(src, n, dest);
  TEST( strcmp(dest, "AHSY") == 0 );

  src = "foo";
  n = 3;
  upperCaseSortString(src, n, dest);
  TEST( strcmp(dest, "FOO") == 0 );

  src = "wqIOe";
  n = 5;
  upperCaseSortString(src, n, dest);
  TEST( strcmp(dest, "EIOQW") == 0 );

  (void) printf( "Finished running tests on upperCaseSortString()\n" );
}


int main() {
  testupperCaseSortString();

  return 0;
}
