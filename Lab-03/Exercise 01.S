.globl cswitch
cswitch:
    # Save old context
    movl 4(%esp), %eax       # Get pointer to old kctx
    popl 0(%eax)             # Save EIP (return address)
    movl %esp, 4(%eax)       # Save ESP
    movl %ebp, 8(%eax)       # Save EBP
    movl %ebx, 12(%eax)      # Save EBX
    movl %esi, 16(%eax)      # Save ESI
    movl %edi, 20(%eax)      # Save EDI

    # Load new context
    movl 8(%esp), %eax       # Get pointer to new kctx
    movl 20(%eax), %edi      # Restore EDI
    movl 16(%eax), %esi      # Restore ESI
    movl 12(%eax), %ebx      # Restore EBX
    movl 8(%eax), %ebp       # Restore EBP
    movl 4(%eax), %esp       # Restore ESP
    pushl 0(%eax)            # Push EIP to stack
    ret                      # Return to new EIP
