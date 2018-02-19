/*
 * Filename: hash.s
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This function will be used to create the hash key of an anagram.
 				This function creates an integer hash key from str by using an
 				algorithm similar to Java’s String.hashCode(), given below. Use
 				the global variables defined in pa3Globals.c to access these
 				constants in assembly (refer to your notes for how to do this).
 * Date: 22 February 2017
 * Sources of Help
 */ 
 	.global hash 			! Declares the sumbol to be globally visible so
							! we can call this function from other modules.
	.section ".text"		! The text segment begins here
/*
 * Function name: hash()
 * Function prototype: int hash( char const * str );
 * Description: This function will be used to create the hash key of an anagram.
 * Parameters:
 * 	arg 1: str - the string to be hashed
 *
 * Side Effects: None.
 * Error Conditions: None
 * Return Value: The hash key of str
 *
 * Registers Used:
 * 	%l0 - hash
 * 	%l1 - str
 * 	%l2 - string length
 * 	%l3 - hash prime
 * 	%l4 - looping index
 */

 hash:

 	save	%sp, -96, %sp		! Save callers window, if different than -96
								! then comment on how that value was calculated\

	set 	HashStartVal, %l0 
	ld  	[%l0], %l0 			! saves hash start value to l0

	mov		%i0, %l1 			! saves the string to l1

	mov 	%i0, %o0
	call 	strlen
	nop

	mov 	%o0, %l2 			! saves the string's length to l2

	set 	HashPrime, %l3 	
	ld 		[%l3], %l3 			! saves hash prime value to l3

	mov 	0, %l4				! loop index

	cmp 	%l4, %l2 			! checks if index >= strlen
	bge 	endloop 			! ends loop if so
	nop

loop:

	mov 	%l0, %o0
	mov		%l3, %o1
	call 	.mul 				! does hash *= hash prime value
	nop

	mov 	%o0, %l0

	add 	%l1, %l4, %l5 		! makes  address of str[index] in l5
	ldub 	[%l5], %l6			! saves str[index] into l6

	add 	%l0, %l6, %l0 		! does hash += str[index]

	inc 	%l4 				! increases index
	
	cmp 	%l4, %l2 			! checks if index < strlen
	bl 		loop 				! continues loop if so
	nop

endloop:

	mov 	%l0, %i0

ret
restore