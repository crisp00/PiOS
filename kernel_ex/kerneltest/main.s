	.file	"main.cpp"
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC0:
	.string	"+-----------------------------------------+\n"
	.align 4
.LC1:
	.string	"|    MOS 32 Bit C++ Kernel Executing!     |\n"
	.align 4
.LC2:
	.string	"+-----------------------------------------+\n\n"
	.align 4
.LC3:
	.string	"\ni as integer ........................"
	.align 4
.LC4:
	.string	"\ni in hex ............................"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC5:
	.string	"\n[%i]"
.LC6:
	.string	"\n[0x%x]"
	.section	.rodata.str1.4
	.align 4
.LC7:
	.string	"\n\nI am preparing to load... Hold on, please... :)"
	.section	.text.startup,"ax",@progbits
	.align 16
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$16, %esp
	pushl	$24
	call	_Z11DebugClrScrt
	popl	%eax
	popl	%edx
	pushl	$4
	pushl	$4
	call	_Z11DebugGotoXYjj
	movl	$23, (%esp)
	call	_Z13DebugSetColorj
	movl	$.LC0, (%esp)
	call	_Z11DebugPrintfPKcz
	movl	$.LC1, (%esp)
	call	_Z11DebugPrintfPKcz
	movl	$.LC2, (%esp)
	call	_Z11DebugPrintfPKcz
	movl	$18, (%esp)
	call	_Z13DebugSetColorj
	movl	$18, (%esp)
	call	_Z13DebugSetColorj
	movl	$.LC3, (%esp)
	call	_Z11DebugPrintfPKcz
	movl	$.LC4, (%esp)
	call	_Z11DebugPrintfPKcz
	popl	%ecx
	popl	%eax
	pushl	$8
	pushl	$25
	call	_Z11DebugGotoXYjj
	movl	$31, (%esp)
	call	_Z13DebugSetColorj
	popl	%eax
	popl	%edx
	pushl	$18
	pushl	$.LC5
	call	_Z11DebugPrintfPKcz
	popl	%ecx
	popl	%eax
	pushl	$18
	pushl	$.LC6
	call	_Z11DebugPrintfPKcz
	popl	%eax
	popl	%edx
	pushl	$16
	pushl	$4
	call	_Z11DebugGotoXYjj
	movl	$31, (%esp)
	call	_Z13DebugSetColorj
	movl	$.LC7, (%esp)
	call	_Z11DebugPrintfPKcz
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	addl	$16, %esp
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 7.1.0"
