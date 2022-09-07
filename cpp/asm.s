	.file	"asm.cpp"
	.text
	.section	.rodata
	.align 4
	.type	_ZL3num, @object
	.size	_ZL3num, 4
_ZL3num:
	.long	1
	.text
	.globl	_Z4callv
	.type	_Z4callv, @function
_Z4callv:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, -4(%rbp)
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	_Z4callv, .-_Z4callv
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
