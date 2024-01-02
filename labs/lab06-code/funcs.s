.text
.global my_max
.global my_pow

# Computes maximum of 2 arguments
# You can assume argument 1 (x) is in %edi
# You can assume argument 2 (y) is in %esi
# If you need to store temporary values, you may use the following registers:
#   %eax, %ecx, %edx, %esi, %edi, %r8d, %r9d, %r10d, %r11d
# DO NOT USE other registers. We will learn why soon.


my_max:
    cmp %edi, %esi        # comparing esi to edi
    jg greater            # if esi > edi
    mov %edi, %eax        # else if edi > esi -> put edi in eax
    ret

greater:
    mov %esi, %eax        
    ret


# Computes base^exp
# You can assume argument 1 (base) is in %edi
# You can assume argument 2 (exp) is in %esi
# If you need to store temporary values, you may use the following registers:
#   %eax, %ecx, %edx, %esi, %edi, %r8d, %r9d, %r10d, %r11d
# DO NOT USE other registers. We will learn why soon.




my_pow:
    mov $1, %eax          # Initialize result to 1
    cmp $1, %esi          # Compare exp to 1
    jle done              # If exp <= 1 -> return 1

loop_keep_multiplying:
    imul %edi, %eax                     # Multiply result by base
    dec %esi                            # Decrement exp
    jz done                             # If exp is zero -> end the function
    jmp loop_keep_multiplying           # Repeat the loop

done:
    ret

