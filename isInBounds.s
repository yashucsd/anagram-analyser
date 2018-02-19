/*
 * Filename: isInBounds.s
 * Author: Yash Nevatia
 * Userid: cs30xpf
 * Description: This assembly module will check if the num is within min and
 *				min+dist, inclusive on both ends. This means if num is equal
 *				to min, it is within the bounds, and if num is equal to
 *				min+dist, it is also within the bounds.
 * Date: 25 January 2017
 * Sources of Help: 
 */ 
 	.global isInBounds	! Declares the sumbol to be globally visible so
						! we can call this function from other modules.
	.section ".text"	! The text segment begins here
/*
 * Function name: isInBounds()
 * Function prototype: long isInBounds( long min, long dist, long num );
 * Description: This assembly module will check if the num is within min and
 *				min+dist, inclusive on both ends. This means if num is equal
 *				to min, it is within the bounds, and if num is equal to
 *				min+dist, it is also within the bounds.
 * Parameters: 	arg 1: long min -- the minimum of this bound
 * 				arg 2: long dist -- the distance between the minimum and max
 * 				arg 3: long num -- the number being surveyed
 * 
 * Side Effects: None.
 * Error Conditions: dist is negative -> return -1
 * 					 overflow occurs in computing min + dist -> return -1
 * Return Value: If any error occurs, return -1. Otherwise, return 1 to
 *				 represent true, 0 to represent false.
 *
 * Registers Used:
 *	%i0 - arg 1 -- the minimum bound
 * 	%i1 - arg 2 -- the distance of bound
 * 	%i2 - arg 3 -- the number being surveyed
 */

isInBounds:
 	save	%sp, -96, %sp	! save callers window, if different than -96

	cmp 	%i1, 0			! compares dist w 0
	bl 		error 			! runs error if dist < 0, or negative
	nop						! delay slot

	addcc 	%i0, %i1, %i3 	! adds min and distance into %i3
	bvs 	error 			! runs error if sum overflows
	nop						! delay slot

	cmp 	%i2, %i0		
	bge 	continue		! checks if i2 >= i0, continues if so
	nop
	
	mov		0, %i0			! entertains case that i2 < i0

	ret						! return from subroutine
	restore					! restore callers window, in "ret" delay shot

continue:
	cmp 	%i2, %i3
	ble 	finish			! checks if i2 <= i3, continues if so
	nop

	mov		0, %i0			! entertains case that i2 > i3
	
	ret
	restore

finish:
	mov		1, %i0			! success, prepares for return

	ret
	restore


error:
	mov		-1, %i0			! entertains error case

	ret
	restore