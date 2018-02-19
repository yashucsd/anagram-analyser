/*
 * Filename: main.c
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This is the main driver for the program. Its main tasks are to
 				parse the command line arguments, build the hashtable, and
 				enter either interactive mode or statistics mode.
 * Date: 28 February 2017
 * Sources of Help
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>


#include "pa3.h"
#include "pa3Strings.h"

/*
 * Function name: main()
 * Function prototype:  int main( int argc, char * argv[] );
 * Description: This is the main driver for the program. Its main tasks are to
 				parse the command line arguments, build the hashtable, and
 				enter either interactive mode or statistics mode.
 * Parameters:
 * 		arg 1: argc -- number of arguments
 * 		arg 2: argv -- array of arguments
 *
 * Side Effects: none
 * Error Conditions: 
 *  	- (x) Hashtable size contains invalid character
 * 		- (x) Hashtable size is too large to be converted to a long
 * 		- (x) Hashtable index contains invalid characters
 * 		- (x) Hashtable index is too large to be converted to a long
 * 		- (x) getopt() indicates an invalid flag or missing flag argument
 * 		- (x) there are extra arguments left after getopt() completes
 * 		- (x) Hashtable size is not within the bounds [1-1000], inclusive
 * 		- () Hashtable index is not a valid index in the table
 * 		- (x) Ran out of memory when allocating space for the array of
 * 		TableEntry structs (as indicated by calloc())
 * 		- (x)loadDict() failed to populate the hashtable (for this error, the
 * 		error message will have already been printed, so just print the short
 * 		usage and return indicating failure)
 * 		- (x) findAnagrams() indicated an error (for this error, the error
 * 		message will have already been printed,
 * Return Value: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int main(int argc, char * argv[]) {
	int c;
	size_t size;
	long index;
	char * endptr;
	enum usageMode mode = USAGE_SHORT;
	FILE * fileplace;
	char * filename;
	int index_min = MIN_SIZE - 1; //min - 1 to start count at 0
	int index_max = DEFAULT_SIZE - 1; // default - 1 to start at 0

	while ((c = getopt(argc, argv, ARG_STR)) != -1)
		switch (c) {
      		case CHAR_INFO_FLAG:
      			errno = 0;
      			index = strtol(optarg, &endptr, BASE);

      			if(*endptr != 0){
      				fprintf(stderr, STR_ERR_NOTINT, STR_ERR_INDEX);
      				usage(stderr, mode, argv[0]);
					return EXIT_FAILURE;
      			}

      			if(errno != 0){
		            char buffer [BUFSIZ]; //sets buffer for snprintf
		            snprintf(buffer, BUFSIZ, STR_ERR_CONVERTING, optarg, BASE);
		            perror(buffer); // prints error
		            usage(stderr, mode, argv[0]);
					return EXIT_FAILURE;
		        }

      			if(!isInBounds(index_min, index_max - index_min, index)){
      				fprintf(stderr, STR_ERR_RANGE, STR_ERR_INDEX, index_min,
      					index_max);
      				usage(stderr, mode, argv[0]);
					return EXIT_FAILURE;
      			}
      			break;
			case CHAR_SIZE_FLAG:
				errno = 0;
				size = strtol(optarg, &endptr, BASE);

				if(*endptr != 0){
					fprintf(stderr, STR_ERR_NOTINT, STR_ERR_SIZE);
					usage(stderr, mode, argv[0]);
					return EXIT_FAILURE;
				}

				if(errno != 0){
		            char buffer [BUFSIZ]; //sets buffer for snprintf
		            snprintf(buffer, BUFSIZ, STR_ERR_CONVERTING, optarg, BASE);
		            perror(buffer); // prints error
		            usage(stderr, mode, argv[0]);
					return EXIT_FAILURE;
		        }

				if(!isInBounds(MIN_SIZE, MAX_SIZE-MIN_SIZE, size)){
					fprintf(stderr, STR_ERR_RANGE, STR_ERR_SIZE, MIN_SIZE,
						MAX_SIZE);
					usage(stderr, mode, argv[0]);
					return EXIT_FAILURE;
				}

				index_max = size - 1; //new upper limit for index
				break;
			case CHAR_FILE_FLAG:
				filename = optarg;
				break;
			case CHAR_HELP_FLAG:
				mode = USAGE_LONG;
				usage(stdout, mode, argv[0]);
				return EXIT_SUCCESS;
			default:
				usage(stderr, mode, argv[0]);
				return EXIT_FAILURE;
			}

	if(optind < argc){ // entertains case of extra arguments
		fprintf(stderr, STR_ERR_EXTRA_ARGS, argv[optind]);
		usage(stderr, mode, argv[0]);
		return EXIT_FAILURE;
	}

	if(!size) size = DEFAULT_SIZE;

	if(filename[0] == '\0')
		filename = DEFAULT_DICT_FILENAME;

	fileplace = fopen(filename, "r");
	if(!fileplace){
		char buffer [BUFSIZ];
        snprintf(buffer, BUFSIZ, filename);
        perror(buffer);

        //todo: make this work for permission vs invalid file
		fprintf(stderr, STR_ERR_FILE_INVALID);
		usage(stdout, mode, argv[0]);
		return EXIT_FAILURE;
	}

	struct TableEntry* entries = calloc(size, sizeof(struct TableEntry));
	if(!entries) return EXIT_FAILURE; // calloc fails

	struct HashTable table;
	table.entryPtr = entries;
	table.size = size;

	struct HashTable * tbPtr = &table;

	if(loadDict(filename, tbPtr) == -1){
		usage(stderr, mode, "main");
		return EXIT_FAILURE;
	}

	// break me;

	if (index) printStats(tbPtr, index);
	else if(findAnagrams(tbPtr) == -1) return EXIT_FAILURE;

	for (unsigned int i = 0; i < tbPtr->size; ++i) {
		struct TableEntry *tblEtryPtr = tbPtr -> entryPtr + i;
		for (unsigned int j = 0; j < tblEtryPtr -> numAnagrams; ++j) {
			struct Anagram *angPtr = tblEtryPtr -> anagramPtr + j;
			free(angPtr);
		}
		free(tblEtryPtr);
	}

	return EXIT_SUCCESS;
}
