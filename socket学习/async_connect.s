	.file	"async_connect.c"
	.text
	.section	.rodata
.LC0:
	.string	"%s failed, err: %s \n"
	.text
	.globl	bad_exit
	.type	bad_exit, @function
bad_exit:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	%eax, %edi
	call	strerror@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$-1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE6:
	.size	bad_exit, .-bad_exit
	.section	.rodata
.LC1:
	.string	"client socket"
.LC2:
	.string	"client get flags"
.LC3:
	.string	"client set flags"
.LC4:
	.string	"192.168.1.205"
.LC5:
	.string	"client in_t_p"
.LC6:
	.string	"client connect"
.LC7:
	.string	"socket is in progress "
.LC8:
	.string	"poll"
.LC9:
	.string	"get sock opt"
.LC10:
	.string	"socket error is %s \n"
.LC11:
	.string	"poll end %d \n"
	.text
	.globl	poll_connect_client
	.type	poll_connect_client, @function
poll_connect_client:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$224, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$6, %edx
	movl	$1, %esi
	movl	$2, %edi
	call	socket@PLT
	movl	%eax, -212(%rbp)
	cmpl	$-1, -212(%rbp)
	jne	.L3
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	bad_exit
.L3:
	movl	-212(%rbp), %eax
	movl	$3, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	fcntl@PLT
	movl	%eax, -208(%rbp)
	cmpl	$-1, -208(%rbp)
	jne	.L4
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	bad_exit
.L4:
	orl	$2048, -208(%rbp)
	movl	-208(%rbp), %edx
	movl	-212(%rbp), %eax
	movl	$4, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	fcntl@PLT
	cmpl	$-1, %eax
	jne	.L5
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	bad_exit
.L5:
	leaq	-144(%rbp), %rax
	movq	%rax, -200(%rbp)
	movq	-200(%rbp), %rax
	movw	$2, (%rax)
	movl	$12345, %edi
	call	htonl@PLT
	movl	%eax, %edx
	movq	-200(%rbp), %rax
	movw	%dx, 2(%rax)
	movq	-200(%rbp), %rax
	addq	$4, %rax
	movq	%rax, %rdx
	leaq	.LC4(%rip), %rax
	movq	%rax, %rsi
	movl	$2, %edi
	call	inet_pton@PLT
	cmpl	$-1, %eax
	jne	.L6
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	bad_exit
.L6:
	movq	-200(%rbp), %rcx
	movl	-212(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	connect@PLT
	movl	%eax, -204(%rbp)
	cmpl	$-1, -204(%rbp)
	jne	.L7
	call	__errno_location@PLT
	movl	(%rax), %eax
	cmpl	$115, %eax
	je	.L8
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	bad_exit
.L8:
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L7:
	movl	-212(%rbp), %eax
	movl	%eax, -192(%rbp)
	movw	$29, -188(%rbp)
	leaq	-192(%rbp), %rax
	movl	$2000, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	poll@PLT
	movl	%eax, -204(%rbp)
	cmpl	$-1, -204(%rbp)
	jne	.L9
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	bad_exit
.L9:
	movl	-192(%rbp), %eax
	leaq	-216(%rbp), %rcx
	leaq	-220(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	movl	$4, %edx
	movl	$1, %esi
	movl	%eax, %edi
	call	getsockopt@PLT
	cmpl	$-1, %eax
	jne	.L10
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	bad_exit
.L10:
	movl	-220(%rbp), %eax
	movl	%eax, %edi
	call	strerror@PLT
	movq	%rax, %rsi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-204(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L11
	call	__stack_chk_fail@PLT
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	poll_connect_client, .-poll_connect_client
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	poll_connect_client
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
