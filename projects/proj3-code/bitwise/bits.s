# Read the following instructions carefully
# You will provide your solution to this part of the project by
# editing the collection of functions in this source file.
#
# Some rules from Project 2 are still in effect for your assembly code here:
#  1. No global variables are allowed
#  2. You may not define or call any additional functions in this file
#  3. You may not use any floating-point assembly instructions
# You may assume that your machine:
#  1. Uses two's complement, 32-bit representations of integers.

# isZero - returns 1 if x == 0, and 0 otherwise
#   Argument 1: x
#   Examples: isZero(5) = 0, isZero(0) = 1
#   Rating: 1
.global isZero
isZero:
    movl $1, %eax
    cmp $0, %edi
    je isZero_END
    movl $0, %eax
isZero_END:
    ret

# bitNor - ~(x|y)
#   Argument 1: x
#   Argument 2: y
#   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
#   Rating: 1
.global bitNor
bitNor:
    orl %edi, %esi
    notl %esi
    movl %esi, %eax
    ret

# distinctNegation - returns 1 if x != -x.
#     and 0 otherwise
#   Argument 1: x
#   Rating: 2
.global distinctNegation
distinctNegation:
    movl $0, %eax
    cmp $0, %edi
    je distinctNegation_END

    shll $1, %edi
    cmp $0, %edi
    je distinctNegation_END

    movl $1, %eax
distinctNegation_END:
    ret

# dividePower2 - Compute x/(2^n), for 0 <= n <= 30
#  Round toward zero
#   Argument 1: x
#   Argument 2: n
#   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
#   Rating: 2
.global dividePower2
dividePower2:
    cmp $0x80000000, %edi
    je special_case_dividePower2 # handles special case for the most negative number
    movl %edi, %r8d
    movl $31, %ecx
    shrl %ecx, %r8d # %r8d will store the sign of the number x
    cmp $0, %r8d
    je continue_dividePower2 # handles for negative number
    notl %edi # change it into positive number with 2's complement first
    incl %edi

continue_dividePower2: # handles for positive division, negative number will go through this as well but will be changed to a negative number
    movl %esi, %ecx
    sarl %ecx, %edi # dividing by shifting
    movl %edi, %eax
    cmp $1, %r8d # converting back to negative if %edi was negative
    je change_to_neg_dividePower2
    ret

change_to_neg_dividePower2: # handles for negative division
    notl %edi
    incl %edi
    movl %edi, %eax
    ret

special_case_dividePower2: # handle for the disivion of the most negative number
    movl %esi, %ecx
    sarl %ecx, %edi
    movl %edi, %eax
    ret


# getByte - Extract byte n from word x
#   Argument 1: x
#   Argument 2: n
#   Bytes numbered from 0 (least significant) to 3 (most significant)
#   Examples: getByte(0x12345678,1) = 0x56
#   Rating: 2
.global getByte
getByte:
    imull $8, %esi
    movl %esi, %ecx
    shrl %ecx, %edi
    andl $0xFF, %edi
    movl %edi, %eax 
    ret

#    movl $8, %eax          # Load 8 into %eax
#    imul %esi, %eax        # Multiply n by 8, result in %eax
#    movl %eax, %ecx        # Copy the result to %ecx
#    movl $0xFF, %eax       # Load 0xFF into %eax to create a mask
#    shl %cl, %eax          # Shift the mask left by n positions
#    and %edi, %eax         # Apply the mask to x to extract the desired byte
#    ret

# isPositive - return 1 if x > 0, return 0 otherwise
#   Argument 1: x
#   Example: isPositive(-1) = 0.
#   Rating: 2
.global isPositive
isPositive:
    movl $0, %eax
    cmp $0, %edi
    je isPositive_End

    movl $31, %ecx
    shrl %ecx, %edi
    movl %edi, %eax
    xorl $1, %eax
    ret
isPositive_End:
    ret

# floatNegate - Return bit-level equivalent of expression -f for
#   floating point argument f.
#   Both the argument and result are passed as unsigned int's, but
#   they are to be interpreted as the bit-level representations of
#   single-precision floating point values.
#   When argument is NaN, return argument.
#   Argument 1: f
#   Rating: 2
.global floatNegate
floatNegate:
    movl %edi, %esi 

#   checking for the mantissa if it is NAN
    movl $9, %ecx
    shll %ecx, %esi # getting the mantissa
    cmp $0, %esi
    je flip_the_sign_floatNegate

    movl %edi, %esi
#   checking for the exponent if it is NAN
    movl $1, %ecx
    shll %ecx, %esi
    movl $24, %ecx
    shrl %ecx, %esi # esi will now store the exponent
    cmp $0xFF, %esi
#    movl $2, %eax
    jne flip_the_sign_floatNegate

    movl %edi, %eax
    ret

flip_the_sign_floatNegate:
    xorl $0x80000000, %edi
    movl %edi, %eax
    ret


# isLessOrEqual - if x <= y  then return 1, else return 0
#   Argument 1: x
#   Argument 2: y
#   Example: isLessOrEqual(4,5) = 1.
#   Rating: 3
.global isLessOrEqual
isLessOrEqual:
    movl $1, %eax
    cmp %esi, %edi
    jle isLessOrEqual_END

    movl $0, %eax
    ret

isLessOrEqual_END:
    ret

# bitMask - Generate a mask consisting of all 1's between
#   lowbit and highbit
#   Argument 1: highbit
#   Argument 2: lowbit
#   Examples: bitMask(5,3) = 0x38
#   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
#   If lowbit > highbit, then mask should be all 0's
#   Rating: 3
.global bitMask
bitMask:
    movl $-1, %edx # setting everything to 1
	movl %edx, %eax
	movl %edi, %ecx # shift by high bit to the left later
	shll %ecx, %eax 
    movl $1, %ecx # shift to the left by 1 more bit later
	shll %ecx, %eax
	notl %eax # invert all the bits
	movl %esi, %ecx # shift by low bit to the right and then left immediately later
	shrl %ecx, %eax
	shll %ecx, %eax
	ret

# addOK - Determine if can compute x+y without overflow
#   Argument 1: x
#   Argument 2: y
#   Example: addOK(0x80000000,0x80000000) = 0,
#            addOK(0x80000000,0x70000000) = 1,
#   Rating: 3
.global addOK
addOK:
    movl $1, %eax # default %ex to 1
    movl %edi, %r8d 
    movl %esi, %r9d 
    movl $31, %ecx
    sarl %ecx, %r8d # sign of x
    sarl %ecx, %r9d # sign of y
    cmp %r8d, %r9d
    je check_for_overflow_addOK
    
    
addOK_END:
    ret

check_for_overflow_addOK:
    addl %esi, %edi # %edi will store x + y
    sarl %ecx, %edi # %edi will now store the sign of x + y
    cmp %edi, %r9d
    je addOK_END
    movl $0, %eax
    ret




# floatScale64 - Return bit-level equivalent of expression 64*f for
#   floating point argument f.
#   Both the argument and result are passed as unsigned int's, but
#   they are to be interpreted as the bit-level representation of
#   single-precision floating point values.
#   When argument is NaN, return argument
#   Argument 1: f
#   Rating: 4
.global floatScale64
floatScale64:
    movl %edi, %esi 

#   checking for the mantissa if it is NAN
    movl $9, %ecx
    shll %ecx, %esi # getting the mantissa
    cmp $0, %esi
    je mul_64_floatscale64

#   checking for the exponent if it is NAN
    movl %edi, %eax # move ecx = uf 
    shrl $23, %eax # uf >> 23 
    andl $255, %eax # (uf >> 23) & 255 exponent = eax
    cmp $0xFF, %eax
    jne mul_64_floatscale64

ret_original_floatScale64:
    movl %edi, %eax
    ret

mul_64_floatscale64:
    movl %edi, %r9d
    andl $0x80000000, %r9d # %r9d will now store the sign of the float number
    movl %edi, %esi
    andl $0x7F800000, %esi # %esi will now store the exponent of the float number
    movl %edi, %edx
    andl $0x007FFFFF, %edx # %edx will now store the mantissa of the float number

# if exponent is > 248, return infinity
    cmp $0x7C000000, %esi
    jg make_infinity_floatScale64

# if exponent is > 0, return infinity
    cmp $0, %esi
    jg add_6_to_exponent_floatScale64

# if the exponent is 0, check if can mantissa << 6
#    cmp $0x0, %edx
#    je ret_original_floatScale64
    cmp $0x0001FFFF, %edx
    jle shift_left_by_6_to_mantissa_floatScale64

# last condition
last_condition_floatScale64:
    movl $7, %esi
    movl $1, %ecx
    jmp last_condition_loop_floatScale64

make_infinity_floatScale64:
    movl $0x7F800000, %esi
    movl $0, %edx
    jmp ret_floatscale64

add_6_to_exponent_floatScale64:
    movl $23, %ecx
    sarl %ecx, %esi
    addl $6, %esi
    sall %ecx, %esi
    jmp ret_floatscale64

shift_left_by_6_to_mantissa_floatScale64:
    movl $6, %ecx
    shll %ecx, %edx
    jmp ret_floatscale64

last_condition_loop_floatScale64:
    cmp $0x00800000, %edx
    jge last_condition_exit_loop_floatScale64
    shll %ecx, %edx
    decl %esi
    jmp last_condition_loop_floatScale64

last_condition_exit_loop_floatScale64:
    andl $0x007FFFFF, %edx
    jmp ret_floatscale64

ret_floatscale64:
    orl %esi, %edx
    orl %r9d, %edx
    movl %edx, %eax
    ret
    


# floatPower2 - Return bit-level equivalent of the expression 2.0^x
#   (2.0 raised to the power x) for any 32-bit integer x.
#
#   The unsigned value that is returned should have the identical bit
#   representation as the single-precision floating-point number 2.0^x.
#   If the result is too small to be represented as a denorm, return
#   0. If too large, return +INF.
#
#   Argument 1: x
#   Rating: 4
.global floatPower2
floatPower2:
    movl $0, %esi # %esi will store the sign
    movl $0, %r8d # %edi will store the exponent
    movl $0, %r9d # r9d will store the mantissa

    movl $0x7F800000, %eax
    cmp $127, %edi # too big exponent
    jg ret_floatPower2

    movl $0, %eax
    cmp $-149, %edi # too small exponent
    jl ret_floatPower2

    movl %edi, %eax
    addl $127, %eax
    movl $23, %ecx
    shll %ecx, %eax
    cmp $-127, %edi # if exponent x > -127 -> x + bias(127)
    jg ret_floatPower2

    movl %edi, %ecx
    addl $149, %ecx
    movl $1, %eax
    shll %ecx, %eax

ret_floatPower2:
    ret
