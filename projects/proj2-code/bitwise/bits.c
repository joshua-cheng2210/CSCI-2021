/*
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

// #include <stdio.h>
#if 0
/*
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to this part of the project by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc program (described in the spec) to check the legality of
     your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the spec and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *
 *      YOU WILL RECEIVE NO CREDIT IF YOUR CODE DOES NOT PASS THIS CHECK.
 *
 *   2. Use the btest checker to verify that your solutions produce the
 *      correct answers.
 */

#endif

/*
 * isZero - returns 1 if x == 0, and 0 otherwise
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x) {
    //since any number other than zero is true, !true = false and ! false (when x = 0) = true
    return !x;
}

/*
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
    //using de morgan's law
    return ~x & ~y;
}

/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
int distinctNegation(int x) {
    // ^ will return 0 if a ^ a
    // !! will turn 1 for any non-zero number and 0 for zero
    return !!(x ^ (~x + 1));
    // return !!(x << 1);
}

/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n) {
    // ((x >> 31) & ((1 << n) + ~0)) is to calculate the bias. bias = 1 will only be added to x when 1) x < 0 and 2) n > 0
    // (x >> 31) checks for the sign. -1 for negative and 0 for positive
    // ((1 << n) + ~0)) checks for the power n. 0 for the right most bit for n = 0 and 1 for the right most bit for n > 0
    return (x + ((x >> 31) & ((1 << n) + ~0))) >> n;
}

/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    // (n << 3) is (n * 8) bits
    // shift the number x by (n*8) bits to the left
    // & (0b11111111) -> checks for the right 8 most bits
    return (x >> (n << 3)) & ~(~0 << 8);
}

/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int isPositive(int x) {
    // ~(x >> 31) is to calculate the bias. bias = 0 for negative number and -1 else
    // using the modified number. shift 31 bits to the right and return the right most digits
    return !(((x + ~(x >> 31)) >> 31) & 1);
}

/*
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
    // int sign_bit = uf & 0x80000000;             // only remain the position of the sign
    int exponent = (uf & 0x7F800000) >> 23;     // finding the exponent
    int mantissa = uf & 0x7FFFFF;               // only remain the mantissa

    // the if statements catches for NAN values
    //  it will be NAN if 1) mantissa are all 0s 2) exponent are all 1s
    if (mantissa != 0 && (exponent ^ 0xFF) == 0){
        return uf;
    }

    return uf ^ (1 << 31);          // changing the signs of the uf
}

/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // using the signs to compare. if the signs are same, subtract each other and find the sign of the answer; if the signs are different then compare with the signs
    int sign_x = (x >> 31); // 1 for x < 0; 0 for x >=0
    int sign_y = (y >> 31); // 1 for y < 0; 0 for y >=0
    int sign_diff = sign_x ^ sign_y; // 1 for different signs; 0 for same

    // ((!sign_diff) & (!((y + (~x + 1)) >> 31))) -> takes care if the signs of x and y are the same -> subtracts x and y and check the sign of the answer
    // !!(sign_diff & sign_x) -> takes care if the signs are different -> no need to subtract x and y. 
    return ((!sign_diff) & (!((y + (~x + 1)) >> 31))) | !!(sign_diff & sign_x);
}

/*
 * bitMask - Generate a mask consisting of all 1's between
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
    // put 1 on all the wanted bits and 0 on all the unwanted bits
    int left = ~(~0 << highbit << 1); // make all the bits after the highbits (to the left) all zero
    int right = (~0 << lowbit); // makes all the bits before the lowbits (to the right) all zero


    return left & right;
}

/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    // determine using the signs of x and y.

    // sign_x -> sign of x; sign_y -> sign_y
    int sign_x = x >> 31; 
    int sign_y = y >> 31; 

    // sign_diff -> 0 for same; 1 for diff;
    int sign_diff_x_y = sign_x ^ sign_y;

    int sum = x + y;
    // sign_sum -> sign of the sum
    int sign_sum = sum >> 31; 

    // return 1 for overflow; 0 for else
    // overflow happens when 1) sign_diff_x_y == 0 2) sign_sum != sign_x) 
    return !((!sign_diff_x_y) & (sign_sum ^ sign_x));
}

/*
 * floatScale64 - Return bit-level equivalent of expression 64*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 35
 *   Rating: 4
 */
unsigned floatScale64(unsigned uf) {
    int sign_bit = uf & 0x80000000;             // only remain the position of the sign
    int exponent = (uf & 0x7F800000) >> 23;     // finding the exponent
    int mantissa = uf & 0x7FFFFF;               // only remain the mantissa

    if (exponent == 0xFF){              // cehcking for NaN (0xFF = 1111 1111)
        return uf; 
    } else if (exponent > 248){         // if no. * 64 == num overflow -> make infinity
        exponent = 0xFF;                
        mantissa = 0;                   
    } else if (exponent > 0){           // *2^6 == *64
        exponent += 6;
    } else if (mantissa <= 0x1FFFF){    // if exponent == 0000 0000 and mantissa can << 6 without overflowing -> mantissa << 6
        mantissa = mantissa << 6;
    } else {                            // else (last condition) if exponent = 0000 0000 and << 6 to mantissa will cause overflow -> mantissa << left until right b4 it overflows, add 7- num_shift to exponent
        exponent = 7;
        while (mantissa < 0x800000){
            mantissa = mantissa << 1;
            exponent--;
        }
        mantissa = mantissa & 0x7FFFFF;
    }

    return sign_bit | (exponent << 23) | mantissa;
}



/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    int sign = 0;
    int exponent = 0;
    int mantissa = 0;

    if (x > 127){                               // 127 is the last exponent X b4 the float + num overflows
        return 0x7F800000;                      // creating infinity
    } else if (x < -149){                       // -129 is the last exponent x b4 the float - num underflow
        return 0;
    } else if (x > -127){                       // if exponent x > -127 -> x + bias(127)
        exponent = x + 127;
    } else {                                    // if (-149 << exponent << -127) -> mantissa << (149 + x)
        mantissa = (0x1 << (149 + x));
    }
    return sign | (exponent << 23) | mantissa;
    // return 2;
}
