	.text
	.globl	test_and_set

/**
 * test_and_set: assume it's called with test_and_set(&lock);
 * @param lock pointer to a mutex_t variable
 *
 * TODO - add a comment each line describing its action
 */
test_and_set:
	cli
	pushl	%ebx		# preserve contents of the %ebx register, which is about to be modified
	movl	8(%esp), %ebx	# Store the value esp into the ebx register
	movl	$1, %eax	# Store the value $1 into the eax register
	xchg	%eax, (%ebx)	# exchange ebs with eax
	popl	%ebx		# removes ebx from the top of the stack
	sti
	ret			# pops the return address off the stack
