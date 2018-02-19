/*
 * Filename: loadDict.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function will open and read the dictionary file word by
 * 				word into memory. First open the file for reading using
 *				fopen(), remember to check for permission error and invalid
 *				file error. If you encounter an error, simply print the proper
 *				error message and return.
 * Date: 28 February 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pa3.h"

/*
 * Function name: loadDict()
 * Function prototype: int loadDict(char * filename, struct HashTable * table);
 * Description: This function will open and read the dictionary file word by
				word into memory. First open the file for reading using
				fopen(), remember to check for permission error and invalid
				file error. If you encounter an error, simply print the proper
				error message and return.
 * Parameters:
 * 		arg 1: filename -- the name of the file being loaded
 *  	arg 2: table -- the table being loaded into
 * 
 * Side Effects: none
 * Error Conditions: fopen error, initanagram failure, memalloc fails
 * Return Value: 
 */

int loadDict(char * filename, struct HashTable * table) {
	
	FILE * fileplace = fopen(filename, "r");

	if(!fileplace){ //checks if file is valid
		char buffer [BUFSIZ];
        snprintf(buffer, BUFSIZ, filename);
        perror(buffer);
		return -1;
	}

	char buffer[BUFSIZ]; // reads words from file
	char* input = fgets(buffer, BUFSIZ, fileplace);

	struct HashTable * tbPtr = table;

	while(input != '\0'){ // checks if the next word is null

		*(strchr(input, '\n')) = '\0'; // swaps the new line char for null char

		struct Anagram * inPtr = malloc(sizeof(struct Anagram));
		if(initAnagram(input, inPtr) == -1) return -1;
		// creates a new, temporary, anagram object and checks if it fails

		int tbIdx = getTableIndex(inPtr -> sortedWord, tbPtr -> size);
		struct TableEntry * etrPtr = (tbPtr -> entryPtr) + tbIdx;
		// gets table index and points to the entry w etrPtr

		if(etrPtr -> anagramPtr != NULL){ //checks if entry is in table

			int notFound = 1; // sees if input is in the anagram array

			for (unsigned int j = 0; j < etrPtr -> numAnagrams; ++j){
				// loops through anagram objects at this entry for input

				struct Anagram * jptr = (etrPtr -> anagramPtr) + j;
				// points to the anagram object at the j'th index
				
				if(!strncmp(inPtr -> sortedWord, jptr -> sortedWord, BUFSIZ)){
					// checks if input and j anagram are of same word

					int numberOfCombos = jptr -> numWords;
					// saves the current number of cominations in words[]

					char * *ptr = realloc(jptr -> words, 
						(numberOfCombos + 1) * sizeof(char *));
					// reallocates enough room for adding the input

					jptr -> words = ptr;
					// copies new pointer into proper array pointer

					ptr = (jptr -> words) + numberOfCombos;
					// set the pointer to the new combo location

					*ptr = calloc(strlen(input) + 1, sizeof(char));
					strncpy(*ptr, input, sizeof(char *));
					// copy input into the new spot

					(jptr -> numWords)++;
					// increases length of the array

					notFound = 0; // marks that the anagram object was found

					// free(ptr);
				}

				// free(jptr);
			}

			if(notFound){
				// entertains case that the appropriate anagram wasn't found

				int numberOfAnagrams = etrPtr -> numAnagrams;
				// stores length of anagram array at this index

				struct Anagram * ptr = realloc(etrPtr -> anagramPtr,
					(numberOfAnagrams + 1) * sizeof(struct Anagram));
				// reallocates enough room for the new anagram object

				etrPtr -> anagramPtr = ptr;
				// copies new pointer into the proper anagram array pointer

				ptr = (etrPtr -> anagramPtr) + numberOfAnagrams;
				// sets the pointer to the new anagram's new location

				ptr = malloc(sizeof(struct Anagram));
				ptr = inPtr;
				memcpy(ptr, inPtr, sizeof(struct Anagram));
				// copies the new anagram into this new spot

				(etrPtr -> numAnagrams)++; //increase the number of anagrams

				// free(ptr);
			}
		} else { // entertains case that there is no anagram array at index
			etrPtr -> anagramPtr = inPtr; // copies temp to proper position
			etrPtr -> numAnagrams = 1; // starts the array of anagrams here
		}

		input = fgets(buffer, BUFSIZ, fileplace);
		// free(etrPtr);
		// free(inPtr);
	}

	// free(tbPtr)

	fclose(fileplace);
	return 0;
}
