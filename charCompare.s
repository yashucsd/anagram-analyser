/*
 * Filename: charCompare.s
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function takes two pointers to characters (the prototype
  				uses two void pointers, but it can be assumed that they are char
  				pointers) and compares them.
 * Date: 22 February 2017
 * Sources of Help
 */ 
 	.global charCompare 	! Declares the sumbol to be globally visible so
							! we can call this function from other modules.
	.section ".text"		! The text segment begins here
/*
 * Function name: charCompare()
 * Function prototype: int charCompare( void const * p1, void const * p2 );
 * Description: This function takes two pointers to characters (the prototype
  				uses two void pointers, but it can be assumed that they are char
  				pointers) and compares them. Do not use direct subtraction; in
  				the milestone unit testing we will check for exactly -1, 0, or
  				1. This function must be a leaf subroutine.
 * Parameters:
 * 	arg 1: p1 - the pointer to a char to be compared
 *	arg 2: p2 - the other pointer to a char to be compared
 *
 * Side Effects: None.
 * Error Conditions: None
 * Return Value: -1 if the first char is smaller, 0 if the chars are the same,
 * 				 or +1 if the first char is larger.
 *
 * Registers Used:
 * 	%o2 - stores the character at p1
 * 	%o3 - stores the character at p2
 */

 charCompare:

	ldub	[%o0], %o2 			! saves character at p1 to o0
	ldub	[%o1], %o3			! saves character at p2 to o1

	cmp 	%o2, %o3			! compares characters
	be 		equal
	nop

	cmp 	%o2, %o3 			! compares characters
	bl 		smaller
	nop

	mov 	1, %o0 				! entertains p1 > p2 case
	ba 		end
	nop

equal:
	
	mov 	0, %o0 				! entertains equal case
	ba 		end
	nop

smaller:

	mov 	-1, %o0 			! entertains p1 < p2 case

end:

retl
nop