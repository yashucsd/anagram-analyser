/*
 * Filename: printStats.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function will print out various statistics about the
 * 				hashtable entry at the given index. Search through its array
 * 				of Anagram structs to obtain the needed statistics.
 * Date: 28 February 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pa3.h"

/*
 * Function name: printStats()
 * Function prototype: void printStats( struct HashTable const * table,
 * 							int index );
 * Description: This function will print out various statistics about the
				hashtable entry at the given index. Search through its array
				of Anagram structs to obtain the needed statistics.
 * Parameters:
 * 		arg 1: table -- the table with the statistics
 *  	arg 2: index -- the index for which we're printing stats
 * 
 * Side Effects: none
 * Error Conditions: none
 * Return Value: none
 */

void printStats( struct HashTable const * table, int index ) {

	struct TableEntry * etrPtr = (table -> entryPtr)  + index;

	printf("1. number of collisions: %d\n", etrPtr -> numAnagrams);
	
	int totWords = 0;
	for (unsigned int i = 0; i < (etrPtr -> numAnagrams); ++i)
		totWords += ((etrPtr -> anagramPtr) + i) -> numWords;
	printf("2. number of words: %d\n", totWords);

	unsigned int maxWords = 0;
	unsigned int maxAnagramIndex = 0;
	for (unsigned int i = 0; i < (etrPtr -> numAnagrams); ++i)
		if((((etrPtr -> anagramPtr) + i) -> numWords) > maxWords)
			maxAnagramIndex = i;
	printf("3. %s has the most anagrams at %d variations\n",
		((etrPtr -> anagramPtr) + maxAnagramIndex) -> words[0],
		((etrPtr -> anagramPtr) + maxAnagramIndex) -> numWords);

	unsigned int minWords = maxWords;
	unsigned int minAnagramIndex = 0;
	for (unsigned int i = 0; i < (etrPtr -> numAnagrams); ++i)
		if((((etrPtr -> anagramPtr) + i) -> numWords) < minWords)
			minAnagramIndex = i;
	printf("4. %s has the least anagrams at %d variations\n",
		((etrPtr -> anagramPtr) + minAnagramIndex) -> words[0],
		((etrPtr -> anagramPtr) + minAnagramIndex) -> numWords );

}
