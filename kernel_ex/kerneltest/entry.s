	.file	"entry.cpp"
	.text
	.align 16
	.globl	_Z12kernel_entryv
	.type	_Z12kernel_entryv, @function
_Z12kernel_entryv:
.LFB0:
	.cfi_startproc
	subl	$12, %esp
	.cfi_def_cfa_offset 16
	call	_Z22InitializeConstructorsv
	call	main
	call	_Z4Exitv
.L2:
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	_Z12kernel_entryv, .-_Z12kernel_entryv
	.ident	"GCC: (GNU) 7.1.0"
