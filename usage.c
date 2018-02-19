/*
 * Filename: usage.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Print the appropriate usage message to the specified stream.
 * 				If the usageMode is USAGE_SHORT, print the short usage message.
 * 				Otherwise, print the long usage message (see pa3.h and
 * 				pa3Strings.h).
 * Date: 28 February 2017
 * Sources of Help
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function name: usage()
 * Function prototype: void usage( FILE * stream, enum usageMode u, 
 						const char * progName );
 * Description: Print the appropriate usage message to the specified stream.
				If the usageMode is USAGE_SHORT, print the short usage message.
				Otherwise, print the long usage message (see pa3.h and
				pa3Strings.h).
 * Parameters:
 * 		arg 1: stream -- stream to print usage to
 *  	arg 2: usageMode u -- long or short usage
 * 		arg 3: progName -- input for the program name
 * 
 * Side Effects: none
 * Error Conditions: none
 * Return Value: none
 */

void usage( FILE * stream, enum usageMode u, const char * progName ){
	if(u == USAGE_SHORT)
		fprintf(stream, STR_USAGE_SHORT, progName, progName);
	else
		fprintf(stream, STR_USAGE_LONG, progName, MIN_SIZE, MAX_SIZE);
}
