/*
 * Filename: upperCaseSortString.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function will take the src string (of length n) and will
 * 				store a copy in dest where all the characters are converted to
 * 				uppercase and sorted in alphabetical order.
 * Date: 22 February 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pa3.h"

/*
 * Function name: upperCaseSortString()
 * Function prototype:  void upperCaseSortString( char const * src, int n,
 							char * dest );
 * Description: You will need to use the C standard library array sorting
 * 				function qsort() to sort the characters in alphabetical order.
 * 				This function takes in a pointer to a comparison function (in
 * 				order to sort the array, you need to provide instructions on how
 * 				to compare the elements of the array--this is the purpose of the
 * 				charCompare() function you will write).

 * Parameters:
 *  arg 1: src -- the string to be manipulated
 * 	arg 2: n -- the length of the src string
 *  arg 3: dest -- where the manipulated copy of the src string ends up
 *
 * Side Effects: none
 * Error Conditions: none
 * Return Value: none
 */

void upperCaseSortString( char const * src, int n, char * dest ) {
	strncpy(dest, src, n);
	dest[n] = '\0';
	
	int i = 0;
	// upper cases each character in dest
	while(dest[i]){
      dest[i] = toupper(dest[i]);
      i++;
   }

   qsort(dest, n, sizeof(char), charCompare);
	//copies src sorted by charCompare function
}
