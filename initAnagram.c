/*
 * Filename: initAnagram.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function initializes an anagram struct for the src string
 * 				passed in.
 * Date: 28 February 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pa3.h"

/*
 * Function name: initAnagram()
 * Function prototype:  int initAnagram( char const * src,
 * 							struct Anagram * anagram );
 * Description: This function initializes an anagram struct for the src string
 * 				passed in.
 * Parameters:
 *  	arg 1: src -- the source string for the anagram
 * 		arg 2: anagram -- struct that we're initialising
 * Side Effects: none
 * Error Conditions: memory allocation fails
 * Return Value: 0 if all's well, -1 otherwise
 */

int initAnagram( char const * src, struct Anagram * anagram ){

	char * srtd = calloc(strlen(src) + 1, sizeof(char));
	upperCaseSortString(src, strlen(src) + 1, srtd);
	strncpy(anagram -> sortedWord, srtd, sizeof(char *));
	// sort the input string and add it to the anagram object

	char * *newWords = calloc(1, sizeof(char *)); // start array of words
	if(!newWords) return -1; // entertains case that malloc fails

	newWords[0] = calloc(strlen(src) + 1, sizeof(char)); //allocate room for first word
	if(!newWords[0]) return -1; // entertains case that malloc fails

	strncpy(*newWords, src, sizeof(char *));
	// copy the input as the first word in the word array

	anagram -> words = newWords;
	anagram -> numWords = 1;

	// free(newWords);
	// free(srtd);
	return 0;
}
