	.file	"bits.c"
	.text
	.globl	isZero
	.type	isZero, @function
isZero:
.LFB0:
	.cfi_startproc
	endbr64
	testl	%edi, %edi
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	isZero, .-isZero
	.globl	bitNor
	.type	bitNor, @function
bitNor:
.LFB1:
	.cfi_startproc
	endbr64
	orl	%esi, %edi
	movl	%edi, %eax
	notl	%eax
	ret
	.cfi_endproc
.LFE1:
	.size	bitNor, .-bitNor
	.globl	distinctNegation
	.type	distinctNegation, @function
distinctNegation:
.LFB2:
	.cfi_startproc
	endbr64
	addl	%edi, %edi
	setne	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	distinctNegation, .-distinctNegation
	.globl	dividePower2
	.type	dividePower2, @function
dividePower2:
.LFB3:
	.cfi_startproc
	endbr64
	movl	%esi, %ecx
	movl	%edi, %eax
	sarl	$31, %eax
	movl	$1, %edx
	sall	%cl, %edx
	subl	$1, %edx
	andl	%edx, %eax
	addl	%edi, %eax
	sarl	%cl, %eax
	ret
	.cfi_endproc
.LFE3:
	.size	dividePower2, .-dividePower2
	.globl	getByte
	.type	getByte, @function
getByte:
.LFB4:
	.cfi_startproc
	endbr64
	leal	0(,%rsi,8), %ecx
	sarl	%cl, %edi
	movzbl	%dil, %eax
	ret
	.cfi_endproc
.LFE4:
	.size	getByte, .-getByte
	.globl	isPositive
	.type	isPositive, @function
isPositive:
.LFB5:
	.cfi_startproc
	endbr64
	movl	%edi, %eax
	sarl	$31, %eax
	notl	%eax
	addl	%edi, %eax
	notl	%eax
	shrl	$31, %eax
	ret
	.cfi_endproc
.LFE5:
	.size	isPositive, .-isPositive
	.globl	floatNegate
	.type	floatNegate, @function
floatNegate:
.LFB6:
	.cfi_startproc
	endbr64
	movl	%edi, %eax
	shrl	$23, %eax
	testl	$8388607, %edi
	setne	%dl
	cmpb	$-1, %al
	sete	%al
	testb	%al, %dl
	jne	.L9
	leal	-2147483648(%rdi), %eax
	ret
.L9:
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE6:
	.size	floatNegate, .-floatNegate
	.globl	isLessOrEqual
	.type	isLessOrEqual, @function
isLessOrEqual:
.LFB7:
	.cfi_startproc
	endbr64
	movl	%edi, %ecx
	sarl	$31, %ecx
	movl	%esi, %edx
	sarl	$31, %edx
	subl	%edi, %esi
	cmpl	%edx, %ecx
	sete	%al
	notl	%esi
	shrl	$31, %esi
	andl	%eax, %esi
	notl	%edx
	testl	%ecx, %edx
	setne	%al
	orl	%eax, %esi
	movzbl	%sil, %eax
	ret
	.cfi_endproc
.LFE7:
	.size	isLessOrEqual, .-isLessOrEqual
	.globl	bitMask
	.type	bitMask, @function
bitMask:
.LFB8:
	.cfi_startproc
	endbr64
	movl	$-1, %edx
	movl	%edx, %eax
	movl	%edi, %ecx
	sall	%cl, %eax
	addl	%eax, %eax
	notl	%eax
	movl	%esi, %ecx
	sall	%cl, %edx
	andl	%edx, %eax
	ret
	.cfi_endproc
.LFE8:
	.size	bitMask, .-bitMask
	.globl	addOK
	.type	addOK, @function
addOK:
.LFB9:
	.cfi_startproc
	endbr64
	movl	%edi, %eax
	sarl	$31, %eax
	movl	%esi, %edx
	sarl	$31, %edx
	addl	%esi, %edi
	sarl	$31, %edi
	cmpl	%edx, %eax
	sete	%dl
	movzbl	%dl, %edx
	xorl	%eax, %edi
	testl	%edi, %edx
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE9:
	.size	addOK, .-addOK
	.globl	floatScale64
	.type	floatScale64, @function
floatScale64:
.LFB10:
	.cfi_startproc
	endbr64
	movl	%edi, %r8d
	andl	$-2147483648, %r8d
	movl	%edi, %esi
	shrl	$23, %esi
	movzbl	%sil, %edx
	movl	%edi, %ecx
	andl	$8388607, %ecx
	cmpb	$-1, %sil
	je	.L19
	cmpl	$248, %edx
	jg	.L20
	testl	%edx, %edx
	jle	.L16
	addl	$6, %edx
	jmp	.L15
.L16:
	testl	$8257536, %edi
	jne	.L21
	sall	$6, %ecx
	jmp	.L15
.L18:
	addl	%ecx, %ecx
	subl	$1, %edx
.L17:
	cmpl	$8388607, %ecx
	jle	.L18
	andl	$8388607, %ecx
	jmp	.L15
.L21:
	movl	$7, %edx
	jmp	.L17
.L20:
	movl	$0, %ecx
	movl	$255, %edx
.L15:
	movl	%edx, %eax
	sall	$23, %eax
	orl	%r8d, %eax
	orl	%ecx, %eax
	ret
.L19:
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE10:
	.size	floatScale64, .-floatScale64
	.globl	floatPower2
	.type	floatPower2, @function
floatPower2:
.LFB11:
	.cfi_startproc
	endbr64
	cmpl	$127, %edi
	jg	.L26
	cmpl	$-149, %edi
	jl	.L27
	cmpl	$-126, %edi
	jl	.L24
	leal	127(%rdi), %eax
	movl	$0, %edi
.L25:
	sall	$23, %eax
	orl	%edi, %eax
	ret
.L24:
	leal	149(%rdi), %ecx
	movl	$1, %eax
	sall	%cl, %eax
	movl	%eax, %edi
	movl	$0, %eax
	jmp	.L25
.L26:
	movl	$2139095040, %eax
	ret
.L27:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE11:
	.size	floatPower2, .-floatPower2
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
