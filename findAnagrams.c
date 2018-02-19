/*
 * Filename: findAnagrams.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function handles the interactive mode of the program. It
 				first prompts the user to enter a word and then prints any
 				matching anagrams of that word, excluding the word itself.
 * Date: 28 February 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function name: findAnagrams()
 * Function prototype:  int findAnagrams( struct HashTable const * table );
 * Description: This function handles the interactive mode of the program. It
 				first prompts the user to enter a word and then prints any
 				matching anagrams of that word, excluding the word itself. This
 				happens in a loop until the user enters ctrl-D (^D) to signify
 				the end of input (EOF), or an error occurs when creating an
 				anagram.
 * Parameters:
 *  arg 1: table -- 
 *
 * Side Effects: none
 * Error Conditions: if initAnagram() returns -1, returns -1.
 * Return Value: 0 on success, -1 on failure
 */

int findAnagrams( struct HashTable const * table ) {
	
	char buffer[BUFSIZ];

	printf("%s", STR_USER_PROMPT);
	char* input = fgets(buffer, BUFSIZ, stdin);
	// prompts and takes user input

	while(input != '\0') {

		*(strchr(input, '\n')) = '\0';
		// swap for the null char

		struct Anagram * inPtr = malloc(sizeof(struct Anagram));
		if(initAnagram(input, inPtr) == -1) return -1;
		// create input pointer to new struct

		int tbIdx = getTableIndex(inPtr -> sortedWord, table -> size);
		// get table index for input

		struct TableEntry * etrPtr  = ((table -> entryPtr) + tbIdx);
		//create a pointer to the entry at that index

		char * srtd = calloc(strlen(input) + 1, sizeof(char));
		upperCaseSortString(input, strlen(input), srtd);
		// create sorted copy of the input

		for (unsigned int j = 0; j < etrPtr -> numAnagrams; ++j){
			// for all the anagram structs at this index

			struct Anagram * ptr = ((etrPtr -> anagramPtr) + j);
			// create pointer to the anagram struct at this index

			if(!strncmp(srtd, ptr -> sortedWord, BUFSIZ)){
				// checks if the sorted input = sorted word of this anagram

				for (unsigned int k = 0; k < ptr -> numWords; ++k){
					// for all the words in this anagram struct

					if(strncmp(input, (ptr -> words)[k], BUFSIZ) != 0){
						// if the word doesn't match the input

						printf("%s\n", (ptr -> words)[k]); //print the anagram
					}
				}
			}
		}

		printf("%s", STR_USER_PROMPT);
		input = fgets(buffer, BUFSIZ, stdin);
		// prompts and takes user input
	}

	return 0;
}
