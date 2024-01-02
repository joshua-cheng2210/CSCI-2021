// Returns i if i > j
// Otherwise returns j
// Examples: max(4, 8) returns 8
//           max(16, 15) returns 16
int my_max(int i, int j) {
    if (i > j) {
        return i;
    }
    return j;
}

//  my_max function
//  Input: %rdi - i, %rsi - j
//  Output: %rax - result
/*
my_max:
    cmp %rdi, %rsi        # Compare i and j
    jg greater            # Jump to greater if i > j
    mov %rsi, %rax        # Set result to j
    ret

greater:
    mov %rdi, %rax        # Set result to i
    ret
*/



// Returns base^exp
// Examples: pow(2, 3) returns 8
//           pow(5, 4) returns 625
int my_pow(int base, int exp) {
    int result = base;
    for (int i = 2; i <= exp; i++) {
        result *= base;
    }
    return result;
}


//  my_pow function
//  Input: %rdi - base, %rsi - exp
//  Output: %rax - result

/*
my_pow:
    mov $1, %rax          # Initialize result to 1
    cmp $1, %rsi          # Compare exp to 1
    jle done              # If exp <= 1, return 1
    mov %rdi, %rax        # Set result to base

loop_start:
    dec %rsi              # Decrement exp
    jz done               # If exp is zero, we are done
    imul %rdi, %rax       # Multiply result by base
    jmp loop_start        # Repeat the loop

done:
    ret
*/