/*
 * Filename: testhash.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Unit test program to test the function hash().
 * Date: 22 February 2017
 * Sources of Help
 */ 

#include "test.h"    /* For TEST() macro and stdio.h */
#include "pa3.h"     /* For charCompare() function prototype */

/*
 * Unit Test for hash.s
 *
 * int hash( char const * str );
 *
 * This function will be used to create the hash key of an anagram. This
 * function creates an integer hash key from str by using an algorithm similar
 * to Java’s String.hashCode()
 */
void testhash() {

  char const * str;

  (void) printf( "Testing hash()\n" );

  str = "yash";
  TEST( hash( str ) == 26881936 );

  str = "foo";
  TEST( hash( str ) == 701039 );

  str = "sdkjf";
  TEST( hash( str ) == 983527849 );

  (void) printf( "Finished running tests on hash()\n" );
}


int main() {
  testhash();

  return 0;
}
