/*
 * Filename: getTableIndex.s
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: Calculate the index of the ucSorted string (uppercase sorted
  				version of the string input by the user) in the hashtable of 
  				size tableSize. You can assume the ucSorted string is all upper 
  				case and sorted alphabetically.
 * Date: 22 February 2017
 * Sources of Help
 */ 
 	.global getTableIndex 	! Declares the sumbol to be globally visible so
							! we can call this function from other modules.
	.section ".text"		! The text segment begins here
/*
 * Function name: getTableIndex()
 * Function prototype: int getTableIndex( char const * ucSorted,
 *											size_t tableSize );
 * Description: 
 * 				1. Calculate the hash key (using your hash() function) of the
 * 					ucSorted string.
 * 				2. Map the hash key to a valid index in the table by modding the
 * 					hash key by the tableSize.
 * 				3. If the index is negative, make it positive.
 * Parameters:
 * 	arg 1: ucSorted - the string to be checked indexed
 *	arg 2: tableSize - the size of the table
 *
 * Side Effects: None.
 * Error Conditions: None
 * Return Value: The index of ucSorted in the hashtable
 *
 */

 getTableIndex:

 	save	%sp, -96, %sp		! Save callers window, if different than -96
								! then comment on how that value was calculated

	mov 	%i0, %o0
	call 	hash 				! hashes the ucSorted string
	nop	

	mov 	%i1, %o1
	call 	.rem 				! does hashed % tableSize
	nop

	mov 	%o0, %i0

	cmp	 	%i0, 0
	bl 		negate 				! negates result if < 0
	nop

	ba end
	nop

negate:
	
	neg 	%i0

end:

ret
restore