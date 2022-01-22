	.file	"thread_test.cc"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.text._ZNKSt6chrono8durationIlSt5ratioILl1ELl1000000000EEE5countEv,"axG",@progbits,_ZNKSt6chrono8durationIlSt5ratioILl1ELl1000000000EEE5countEv,comdat
	.align 2
	.weak	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1000000000EEE5countEv
	.type	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1000000000EEE5countEv, @function
_ZNKSt6chrono8durationIlSt5ratioILl1ELl1000000000EEE5countEv:
.LFB1771:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1771:
	.size	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1000000000EEE5countEv, .-_ZNKSt6chrono8durationIlSt5ratioILl1ELl1000000000EEE5countEv
	.section	.text._ZNSt6chrono8durationIlSt5ratioILl1ELl1000000000EEEC1IlvEERKT_,"axG",@progbits,_ZNSt6chrono8durationIlSt5ratioILl1ELl1000000000EEEC1IlvEERKT_,comdat
	.align 2
	.weak	_ZNSt6chrono8durationIlSt5ratioILl1ELl1000000000EEEC1IlvEERKT_
	.type	_ZNSt6chrono8durationIlSt5ratioILl1ELl1000000000EEEC1IlvEERKT_, @function
_ZNSt6chrono8durationIlSt5ratioILl1ELl1000000000EEEC1IlvEERKT_:
.LFB1776:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1776:
	.size	_ZNSt6chrono8durationIlSt5ratioILl1ELl1000000000EEEC1IlvEERKT_, .-_ZNSt6chrono8durationIlSt5ratioILl1ELl1000000000EEEC1IlvEERKT_
	.section	.text._ZNSt6chrono15duration_valuesIlE4zeroEv,"axG",@progbits,_ZNSt6chrono15duration_valuesIlE4zeroEv,comdat
	.weak	_ZNSt6chrono15duration_valuesIlE4zeroEv
	.type	_ZNSt6chrono15duration_valuesIlE4zeroEv, @function
_ZNSt6chrono15duration_valuesIlE4zeroEv:
.LFB1778:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1778:
	.size	_ZNSt6chrono15duration_valuesIlE4zeroEv, .-_ZNSt6chrono15duration_valuesIlE4zeroEv
	.section	.rodata
	.align 4
	.type	_ZN9__gnu_cxxL21__default_lock_policyE, @object
	.size	_ZN9__gnu_cxxL21__default_lock_policyE, 4
_ZN9__gnu_cxxL21__default_lock_policyE:
	.long	2
	.type	_ZStL13allocator_arg, @object
	.size	_ZStL13allocator_arg, 1
_ZStL13allocator_arg:
	.zero	1
	.type	_ZStL6ignore, @object
	.size	_ZStL6ignore, 1
_ZStL6ignore:
	.zero	1
	.section	.text._ZNSt6thread2idC2Ev,"axG",@progbits,_ZNSt6thread2idC5Ev,comdat
	.align 2
	.weak	_ZNSt6thread2idC2Ev
	.type	_ZNSt6thread2idC2Ev, @function
_ZNSt6thread2idC2Ev:
.LFB2691:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2691:
	.size	_ZNSt6thread2idC2Ev, .-_ZNSt6thread2idC2Ev
	.weak	_ZNSt6thread2idC1Ev
	.set	_ZNSt6thread2idC1Ev,_ZNSt6thread2idC2Ev
	.section	.text._ZNSt6threadD2Ev,"axG",@progbits,_ZNSt6threadD5Ev,comdat
	.align 2
	.weak	_ZNSt6threadD2Ev
	.type	_ZNSt6threadD2Ev, @function
_ZNSt6threadD2Ev:
.LFB2698:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6thread8joinableEv
	testb	%al, %al
	je	.L9
	call	_ZSt9terminatev@PLT
.L9:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2698:
	.size	_ZNSt6threadD2Ev, .-_ZNSt6threadD2Ev
	.weak	_ZNSt6threadD1Ev
	.set	_ZNSt6threadD1Ev,_ZNSt6threadD2Ev
	.section	.text._ZNKSt6thread8joinableEv,"axG",@progbits,_ZNKSt6thread8joinableEv,comdat
	.align 2
	.weak	_ZNKSt6thread8joinableEv
	.type	_ZNKSt6thread8joinableEv, @function
_ZNKSt6thread8joinableEv:
.LFB2705:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6thread2idC1Ev
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, %rsi
	movq	(%rdx), %rdi
	call	_ZSteqNSt6thread2idES0_
	xorl	$1, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2705:
	.size	_ZNKSt6thread8joinableEv, .-_ZNKSt6thread8joinableEv
	.section	.text._ZSteqNSt6thread2idES0_,"axG",@progbits,_ZSteqNSt6thread2idES0_,comdat
	.weak	_ZSteqNSt6thread2idES0_
	.type	_ZSteqNSt6thread2idES0_, @function
_ZSteqNSt6thread2idES0_:
.LFB2717:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	cmpq	%rax, %rdx
	sete	%al
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2717:
	.size	_ZSteqNSt6thread2idES0_, .-_ZSteqNSt6thread2idES0_
	.section	.rodata
.LC0:
	.string	"sleep start"
.LC1:
	.string	"sleep end"
	.text
	.globl	_Z10sleep_testv
	.type	_Z10sleep_testv, @function
_Z10sleep_testv:
.LFB2729:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movl	$5, -20(%rbp)
	leaq	-20(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IivEERKT_
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE
	leaq	.LC1(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L16
	call	__stack_chk_fail@PLT
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2729:
	.size	_Z10sleep_testv, .-_Z10sleep_testv
	.globl	_Z11thread_testv
	.type	_Z11thread_testv, @function
_Z11thread_testv:
.LFB2730:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2730
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-40(%rbp), %rax
	leaq	_Z10sleep_testv(%rip), %rsi
	movq	%rax, %rdi
.LEHB0:
	call	_ZNSt6threadC1IRFvvEJEvEEOT_DpOT0_
.LEHE0:
	movl	$3, -44(%rbp)
	leaq	-44(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IivEERKT_
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
.LEHB1:
	call	_ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE
.LEHE1:
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6threadD1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L19
	jmp	.L21
.L20:
	endbr64
	movq	%rax, %rbx
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6threadD1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
.L21:
	call	__stack_chk_fail@PLT
.L19:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2730:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2730:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2730-.LLSDACSB2730
.LLSDACSB2730:
	.uleb128 .LEHB0-.LFB2730
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB2730
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L20-.LFB2730
	.uleb128 0
	.uleb128 .LEHB2-.LFB2730
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE2730:
	.text
	.size	_Z11thread_testv, .-_Z11thread_testv
	.section	.text._ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv,"axG",@progbits,_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv,comdat
	.align 2
	.weak	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	.type	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv, @function
_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv:
.LFB2969:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2969:
	.size	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv, .-_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	.section	.text._ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IlvEERKT_,"axG",@progbits,_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC5IlvEERKT_,comdat
	.align 2
	.weak	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IlvEERKT_
	.type	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IlvEERKT_, @function
_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IlvEERKT_:
.LFB2971:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2971:
	.size	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IlvEERKT_, .-_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IlvEERKT_
	.weak	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IlvEERKT_
	.set	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IlvEERKT_,_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IlvEERKT_
	.section	.text._ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IivEERKT_,"axG",@progbits,_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC5IivEERKT_,comdat
	.align 2
	.weak	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IivEERKT_
	.type	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IivEERKT_, @function
_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IivEERKT_:
.LFB3003:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3003:
	.size	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IivEERKT_, .-_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IivEERKT_
	.weak	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IivEERKT_
	.set	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IivEERKT_,_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC2IivEERKT_
	.section	.text._ZNSt6chronoleIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE,"axG",@progbits,_ZNSt6chronoleIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE,comdat
	.weak	_ZNSt6chronoleIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE
	.type	_ZNSt6chronoleIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE, @function
_ZNSt6chronoleIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE:
.LFB3006:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chronoltIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE
	xorl	$1, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3006:
	.size	_ZNSt6chronoleIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE, .-_ZNSt6chronoleIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE
	.section	.text._ZNSt6chrono8durationIlSt5ratioILl1ELl1EEE4zeroEv,"axG",@progbits,_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEE4zeroEv,comdat
	.weak	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEE4zeroEv
	.type	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEE4zeroEv, @function
_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEE4zeroEv:
.LFB3007:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	call	_ZNSt6chrono15duration_valuesIlE4zeroEv
	movq	%rax, -24(%rbp)
	leaq	-24(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IlvEERKT_
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L30
	call	__stack_chk_fail@PLT
.L30:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3007:
	.size	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEE4zeroEv, .-_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEE4zeroEv
	.section	.text._ZNSt6chronoltIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE,"axG",@progbits,_ZNSt6chronoltIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE,comdat
	.weak	_ZNSt6chronoltIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE
	.type	_ZNSt6chronoltIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE, @function
_ZNSt6chronoltIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE:
.LFB3008:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	movq	%rax, %rbx
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	cmpq	%rax, %rbx
	setl	%al
	movq	-24(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L33
	call	__stack_chk_fail@PLT
.L33:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3008:
	.size	_ZNSt6chronoltIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE, .-_ZNSt6chronoltIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE
	.section	.text._ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1EEEElS3_EENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES7_E4typeERKNS1_IT0_T1_EE,"axG",@progbits,_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1EEEElS3_EENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES7_E4typeERKNS1_IT0_T1_EE,comdat
	.weak	_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1EEEElS3_EENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES7_E4typeERKNS1_IT0_T1_EE
	.type	_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1EEEElS3_EENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES7_E4typeERKNS1_IT0_T1_EE, @function
_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1EEEElS3_EENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES7_E4typeERKNS1_IT0_T1_EE:
.LFB3009:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1EEEES3_lLb1ELb1EE6__castIlS3_EES4_RKNS1_IT_T0_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3009:
	.size	_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1EEEElS3_EENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES7_E4typeERKNS1_IT0_T1_EE, .-_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1EEEElS3_EENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES7_E4typeERKNS1_IT0_T1_EE
	.section	.text._ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1EEEES3_lLb1ELb1EE6__castIlS3_EES4_RKNS1_IT_T0_EE,"axG",@progbits,_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1EEEES3_lLb1ELb1EE6__castIlS3_EES4_RKNS1_IT_T0_EE,comdat
	.weak	_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1EEEES3_lLb1ELb1EE6__castIlS3_EES4_RKNS1_IT_T0_EE
	.type	_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1EEEES3_lLb1ELb1EE6__castIlS3_EES4_RKNS1_IT_T0_EE, @function
_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1EEEES3_lLb1ELb1EE6__castIlS3_EES4_RKNS1_IT_T0_EE:
.LFB3010:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	movq	%rax, -24(%rbp)
	leaq	-24(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IlvEERKT_
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L38
	call	__stack_chk_fail@PLT
.L38:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3010:
	.size	_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1EEEES3_lLb1ELb1EE6__castIlS3_EES4_RKNS1_IT_T0_EE, .-_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1EEEES3_lLb1ELb1EE6__castIlS3_EES4_RKNS1_IT_T0_EE
	.section	.text._ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1000000000EEEElS2_ILl1ELl1EEEENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES8_E4typeERKNS1_IT0_T1_EE,"axG",@progbits,_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1000000000EEEElS2_ILl1ELl1EEEENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES8_E4typeERKNS1_IT0_T1_EE,comdat
	.weak	_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1000000000EEEElS2_ILl1ELl1EEEENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES8_E4typeERKNS1_IT0_T1_EE
	.type	_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1000000000EEEElS2_ILl1ELl1EEEENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES8_E4typeERKNS1_IT0_T1_EE, @function
_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1000000000EEEElS2_ILl1ELl1EEEENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES8_E4typeERKNS1_IT0_T1_EE:
.LFB3011:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1000000000EEEES2_ILl1000000000ELl1EElLb0ELb1EE6__castIlS2_ILl1ELl1EEEES4_RKNS1_IT_T0_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3011:
	.size	_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1000000000EEEElS2_ILl1ELl1EEEENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES8_E4typeERKNS1_IT0_T1_EE, .-_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1000000000EEEElS2_ILl1ELl1EEEENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES8_E4typeERKNS1_IT0_T1_EE
	.section	.text._ZNSt6chronomiIlSt5ratioILl1ELl1EElS2_EENSt11common_typeIJNS_8durationIT_T0_EENS4_IT1_T2_EEEE4typeERKS7_RKSA_,"axG",@progbits,_ZNSt6chronomiIlSt5ratioILl1ELl1EElS2_EENSt11common_typeIJNS_8durationIT_T0_EENS4_IT1_T2_EEEE4typeERKS7_RKSA_,comdat
	.weak	_ZNSt6chronomiIlSt5ratioILl1ELl1EElS2_EENSt11common_typeIJNS_8durationIT_T0_EENS4_IT1_T2_EEEE4typeERKS7_RKSA_
	.type	_ZNSt6chronomiIlSt5ratioILl1ELl1EElS2_EENSt11common_typeIJNS_8durationIT_T0_EENS4_IT1_T2_EEEE4typeERKS7_RKSA_, @function
_ZNSt6chronomiIlSt5ratioILl1ELl1EElS2_EENSt11common_typeIJNS_8durationIT_T0_EENS4_IT1_T2_EEEE4typeERKS7_RKSA_:
.LFB3012:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-72(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -56(%rbp)
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	movq	%rax, %rbx
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	subq	%rax, %rbx
	movq	%rbx, %rax
	movq	%rax, -40(%rbp)
	leaq	-40(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEEC1IlvEERKT_
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L43
	call	__stack_chk_fail@PLT
.L43:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3012:
	.size	_ZNSt6chronomiIlSt5ratioILl1ELl1EElS2_EENSt11common_typeIJNS_8durationIT_T0_EENS4_IT1_T2_EEEE4typeERKS7_RKSA_, .-_ZNSt6chronomiIlSt5ratioILl1ELl1EElS2_EENSt11common_typeIJNS_8durationIT_T0_EENS4_IT1_T2_EEEE4typeERKS7_RKSA_
	.section	.text._ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE,"axG",@progbits,_ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE,comdat
	.weak	_ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE
	.type	_ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE, @function
_ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE:
.LFB3005:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	call	_ZNSt6chrono8durationIlSt5ratioILl1ELl1EEE4zeroEv
	movq	%rax, -32(%rbp)
	leaq	-32(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chronoleIlSt5ratioILl1ELl1EElS2_EEbRKNS_8durationIT_T0_EERKNS3_IT1_T2_EE
	testb	%al, %al
	jne	.L52
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1EEEElS3_EENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES7_E4typeERKNS1_IT0_T1_EE
	movq	%rax, -48(%rbp)
	leaq	-48(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chronomiIlSt5ratioILl1ELl1EElS2_EENSt11common_typeIJNS_8durationIT_T0_EENS4_IT1_T2_EEEE4typeERKS7_RKSA_
	movq	%rax, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6chrono13duration_castINS_8durationIlSt5ratioILl1ELl1000000000EEEElS2_ILl1ELl1EEEENSt9enable_ifIXsrNS_13__is_durationIT_EE5valueES8_E4typeERKNS1_IT0_T1_EE
	movq	%rax, -40(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	movq	%rax, -32(%rbp)
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1000000000EEE5countEv
	movq	%rax, -24(%rbp)
.L50:
	leaq	-32(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	nanosleep@PLT
	cmpl	$-1, %eax
	jne	.L47
	call	__errno_location@PLT
	movl	(%rax), %eax
	cmpl	$4, %eax
	jne	.L47
	movl	$1, %eax
	jmp	.L48
.L47:
	movl	$0, %eax
.L48:
	testb	%al, %al
	je	.L44
	jmp	.L50
.L52:
	nop
.L44:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L51
	call	__stack_chk_fail@PLT
.L51:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3005:
	.size	_ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE, .-_ZNSt11this_thread9sleep_forIlSt5ratioILl1ELl1EEEEvRKNSt6chrono8durationIT_T0_EE
	.section	.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_,"axG",@progbits,_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_,comdat
	.align 2
	.weak	_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_
	.type	_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_, @function
_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_:
.LFB3016:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3016
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6thread2idC1Ev
	movq	pthread_create@GOTPCREL(%rip), %rax
	movq	%rax, -32(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rdx
	leaq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB3:
	call	_ZNSt6thread14__make_invokerIRFvvEJEEENS_8_InvokerISt5tupleIJNSt5decayIT_E4typeEDpNS5_IT0_E4typeEEEEEOS6_DpOS9_
	leaq	-48(%rbp), %rax
	leaq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6thread13_S_make_stateINS_8_InvokerISt5tupleIJPFvvEEEEEEESt10unique_ptrINS_6_StateESt14default_deleteIS8_EEOT_
.LEHE3:
	movq	-32(%rbp), %rdx
	leaq	-48(%rbp), %rcx
	movq	-56(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
.LEHB4:
	call	_ZNSt6thread15_M_start_threadESt10unique_ptrINS_6_StateESt14default_deleteIS1_EEPFvvE@PLT
.LEHE4:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED1Ev
	nop
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L55
	jmp	.L57
.L56:
	endbr64
	movq	%rax, %rbx
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED1Ev
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB5:
	call	_Unwind_Resume@PLT
.LEHE5:
.L57:
	call	__stack_chk_fail@PLT
.L55:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3016:
	.section	.gcc_except_table
.LLSDA3016:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3016-.LLSDACSB3016
.LLSDACSB3016:
	.uleb128 .LEHB3-.LFB3016
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB3016
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L56-.LFB3016
	.uleb128 0
	.uleb128 .LEHB5-.LFB3016
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE3016:
	.section	.text._ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_,"axG",@progbits,_ZNSt6threadC5IRFvvEJEvEEOT_DpOT0_,comdat
	.size	_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_, .-_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_
	.weak	_ZNSt6threadC1IRFvvEJEvEEOT_DpOT0_
	.set	_ZNSt6threadC1IRFvvEJEvEEOT_DpOT0_,_ZNSt6threadC2IRFvvEJEvEEOT_DpOT0_
	.section	.text._ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1000000000EEEES2_ILl1000000000ELl1EElLb0ELb1EE6__castIlS2_ILl1ELl1EEEES4_RKNS1_IT_T0_EE,"axG",@progbits,_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1000000000EEEES2_ILl1000000000ELl1EElLb0ELb1EE6__castIlS2_ILl1ELl1EEEES4_RKNS1_IT_T0_EE,comdat
	.weak	_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1000000000EEEES2_ILl1000000000ELl1EElLb0ELb1EE6__castIlS2_ILl1ELl1EEEES4_RKNS1_IT_T0_EE
	.type	_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1000000000EEEES2_ILl1000000000ELl1EElLb0ELb1EE6__castIlS2_ILl1ELl1EEEES4_RKNS1_IT_T0_EE, @function
_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1000000000EEEES2_ILl1000000000ELl1EElLb0ELb1EE6__castIlS2_ILl1ELl1EEEES4_RKNS1_IT_T0_EE:
.LFB3139:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNKSt6chrono8durationIlSt5ratioILl1ELl1EEE5countEv
	imulq	$1000000000, %rax, %rax
	movq	%rax, -24(%rbp)
	leaq	-24(%rbp), %rdx
	leaq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt6chrono8durationIlSt5ratioILl1ELl1000000000EEEC1IlvEERKT_
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L60
	call	__stack_chk_fail@PLT
.L60:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3139:
	.size	_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1000000000EEEES2_ILl1000000000ELl1EElLb0ELb1EE6__castIlS2_ILl1ELl1EEEES4_RKNS1_IT_T0_EE, .-_ZNSt6chrono20__duration_cast_implINS_8durationIlSt5ratioILl1ELl1000000000EEEES2_ILl1000000000ELl1EElLb0ELb1EE6__castIlS2_ILl1ELl1EEEES4_RKNS1_IT_T0_EE
	.section	.text._ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB3140:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3140:
	.size	_ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZNSt5tupleIJPFvvEEEC2EOS2_,"axG",@progbits,_ZNSt5tupleIJPFvvEEEC5EOS2_,comdat
	.align 2
	.weak	_ZNSt5tupleIJPFvvEEEC2EOS2_
	.type	_ZNSt5tupleIJPFvvEEEC2EOS2_, @function
_ZNSt5tupleIJPFvvEEEC2EOS2_:
.LFB3157:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPFvvEEEC2EOS2_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3157:
	.size	_ZNSt5tupleIJPFvvEEEC2EOS2_, .-_ZNSt5tupleIJPFvvEEEC2EOS2_
	.weak	_ZNSt5tupleIJPFvvEEEC1EOS2_
	.set	_ZNSt5tupleIJPFvvEEEC1EOS2_,_ZNSt5tupleIJPFvvEEEC2EOS2_
	.section	.text._ZNSt5tupleIJPFvvEEEC2IvLb1EEERKS1_,"axG",@progbits,_ZNSt5tupleIJPFvvEEEC5IvLb1EEERKS1_,comdat
	.align 2
	.weak	_ZNSt5tupleIJPFvvEEEC2IvLb1EEERKS1_
	.type	_ZNSt5tupleIJPFvvEEEC2IvLb1EEERKS1_, @function
_ZNSt5tupleIJPFvvEEEC2IvLb1EEERKS1_:
.LFB3160:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPFvvEEEC2ERKS1_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3160:
	.size	_ZNSt5tupleIJPFvvEEEC2IvLb1EEERKS1_, .-_ZNSt5tupleIJPFvvEEEC2IvLb1EEERKS1_
	.weak	_ZNSt5tupleIJPFvvEEEC1IvLb1EEERKS1_
	.set	_ZNSt5tupleIJPFvvEEEC1IvLb1EEERKS1_,_ZNSt5tupleIJPFvvEEEC2IvLb1EEERKS1_
	.section	.text._ZNSt11_Tuple_implILm0EJPFvvEEEC2ERKS1_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPFvvEEEC5ERKS1_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EJPFvvEEEC2ERKS1_
	.type	_ZNSt11_Tuple_implILm0EJPFvvEEEC2ERKS1_, @function
_ZNSt11_Tuple_implILm0EJPFvvEEEC2ERKS1_:
.LFB3163:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm0EPFvvELb0EEC2ERKS1_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3163:
	.size	_ZNSt11_Tuple_implILm0EJPFvvEEEC2ERKS1_, .-_ZNSt11_Tuple_implILm0EJPFvvEEEC2ERKS1_
	.weak	_ZNSt11_Tuple_implILm0EJPFvvEEEC1ERKS1_
	.set	_ZNSt11_Tuple_implILm0EJPFvvEEEC1ERKS1_,_ZNSt11_Tuple_implILm0EJPFvvEEEC2ERKS1_
	.section	.text._ZNSt10_Head_baseILm0EPFvvELb0EEC2ERKS1_,"axG",@progbits,_ZNSt10_Head_baseILm0EPFvvELb0EEC5ERKS1_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0EPFvvELb0EEC2ERKS1_
	.type	_ZNSt10_Head_baseILm0EPFvvELb0EEC2ERKS1_, @function
_ZNSt10_Head_baseILm0EPFvvELb0EEC2ERKS1_:
.LFB3166:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3166:
	.size	_ZNSt10_Head_baseILm0EPFvvELb0EEC2ERKS1_, .-_ZNSt10_Head_baseILm0EPFvvELb0EEC2ERKS1_
	.weak	_ZNSt10_Head_baseILm0EPFvvELb0EEC1ERKS1_
	.set	_ZNSt10_Head_baseILm0EPFvvELb0EEC1ERKS1_,_ZNSt10_Head_baseILm0EPFvvELb0EEC2ERKS1_
	.section	.text._ZNSt6thread14__make_invokerIRFvvEJEEENS_8_InvokerISt5tupleIJNSt5decayIT_E4typeEDpNS5_IT0_E4typeEEEEEOS6_DpOS9_,"axG",@progbits,_ZNSt6thread14__make_invokerIRFvvEJEEENS_8_InvokerISt5tupleIJNSt5decayIT_E4typeEDpNS5_IT0_E4typeEEEEEOS6_DpOS9_,comdat
	.weak	_ZNSt6thread14__make_invokerIRFvvEJEEENS_8_InvokerISt5tupleIJNSt5decayIT_E4typeEDpNS5_IT0_E4typeEEEEEOS6_DpOS9_
	.type	_ZNSt6thread14__make_invokerIRFvvEJEEENS_8_InvokerISt5tupleIJNSt5decayIT_E4typeEDpNS5_IT0_E4typeEEEEEOS6_DpOS9_, @function
_ZNSt6thread14__make_invokerIRFvvEJEEENS_8_InvokerISt5tupleIJNSt5decayIT_E4typeEDpNS5_IT0_E4typeEEEEEOS6_DpOS9_:
.LFB3141:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rbx
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIRFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNSt5tupleIJPFvvEEEC1IvLb1EEERKS1_
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L69
	call	__stack_chk_fail@PLT
.L69:
	movq	-40(%rbp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3141:
	.size	_ZNSt6thread14__make_invokerIRFvvEJEEENS_8_InvokerISt5tupleIJNSt5decayIT_E4typeEDpNS5_IT0_E4typeEEEEEOS6_DpOS9_, .-_ZNSt6thread14__make_invokerIRFvvEJEEENS_8_InvokerISt5tupleIJNSt5decayIT_E4typeEDpNS5_IT0_E4typeEEEEEOS6_DpOS9_
	.section	.text._ZNSt6thread13_S_make_stateINS_8_InvokerISt5tupleIJPFvvEEEEEEESt10unique_ptrINS_6_StateESt14default_deleteIS8_EEOT_,"axG",@progbits,_ZNSt6thread13_S_make_stateINS_8_InvokerISt5tupleIJPFvvEEEEEEESt10unique_ptrINS_6_StateESt14default_deleteIS8_EEOT_,comdat
	.weak	_ZNSt6thread13_S_make_stateINS_8_InvokerISt5tupleIJPFvvEEEEEEESt10unique_ptrINS_6_StateESt14default_deleteIS8_EEOT_
	.type	_ZNSt6thread13_S_make_stateINS_8_InvokerISt5tupleIJPFvvEEEEEEESt10unique_ptrINS_6_StateESt14default_deleteIS8_EEOT_, @function
_ZNSt6thread13_S_make_stateINS_8_InvokerISt5tupleIJPFvvEEEEEEESt10unique_ptrINS_6_StateESt14default_deleteIS8_EEOT_:
.LFB3168:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE
	movq	%rax, %r12
	movl	$16, %edi
	call	_Znwm@PLT
	movq	%rax, %rbx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	call	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC1EOS6_
	movq	-24(%rbp), %rax
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC1IS3_vEEPS1_
	movq	-24(%rbp), %rax
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3168:
	.size	_ZNSt6thread13_S_make_stateINS_8_InvokerISt5tupleIJPFvvEEEEEEESt10unique_ptrINS_6_StateESt14default_deleteIS8_EEOT_, .-_ZNSt6thread13_S_make_stateINS_8_InvokerISt5tupleIJPFvvEEEEEEESt10unique_ptrINS_6_StateESt14default_deleteIS8_EEOT_
	.section	.text._ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED2Ev,"axG",@progbits,_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED5Ev,comdat
	.align 2
	.weak	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED2Ev
	.type	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED2Ev, @function
_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED2Ev:
.LFB3178:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L73
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EE11get_deleterEv
	movq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRPNSt6thread6_StateEEONSt16remove_referenceIT_E4typeEOS5_
	movq	(%rax), %rax
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNKSt14default_deleteINSt6thread6_StateEEclEPS1_
.L73:
	movq	-24(%rbp), %rax
	movq	$0, (%rax)
	nop
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3178:
	.size	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED2Ev, .-_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED2Ev
	.weak	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED1Ev
	.set	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED1Ev,_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EED2Ev
	.section	.text._ZNSt11_Tuple_implILm0EJPFvvEEEC2EOS2_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPFvvEEEC5EOS2_,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EJPFvvEEEC2EOS2_
	.type	_ZNSt11_Tuple_implILm0EJPFvvEEEC2EOS2_, @function
_ZNSt11_Tuple_implILm0EJPFvvEEEC2EOS2_:
.LFB3224:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_
	movq	%rax, %rdi
	call	_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNSt10_Head_baseILm0EPFvvELb0EEC2IS1_EEOT_
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3224:
	.size	_ZNSt11_Tuple_implILm0EJPFvvEEEC2EOS2_, .-_ZNSt11_Tuple_implILm0EJPFvvEEEC2EOS2_
	.weak	_ZNSt11_Tuple_implILm0EJPFvvEEEC1EOS2_
	.set	_ZNSt11_Tuple_implILm0EJPFvvEEEC1EOS2_,_ZNSt11_Tuple_implILm0EJPFvvEEEC2EOS2_
	.section	.text._ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE,"axG",@progbits,_ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE,comdat
	.weak	_ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE
	.type	_ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE, @function
_ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE:
.LFB3226:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3226:
	.size	_ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE, .-_ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE
	.section	.text._ZNSt6thread6_StateC2Ev,"axG",@progbits,_ZNSt6thread6_StateC5Ev,comdat
	.align 2
	.weak	_ZNSt6thread6_StateC2Ev
	.type	_ZNSt6thread6_StateC2Ev, @function
_ZNSt6thread6_StateC2Ev:
.LFB3229:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVNSt6thread6_StateE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3229:
	.size	_ZNSt6thread6_StateC2Ev, .-_ZNSt6thread6_StateC2Ev
	.weak	_ZNSt6thread6_StateC1Ev
	.set	_ZNSt6thread6_StateC1Ev,_ZNSt6thread6_StateC2Ev
	.section	.text._ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC2EOS5_,"axG",@progbits,_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC5EOS5_,comdat
	.align 2
	.weak	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC2EOS5_
	.type	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC2EOS5_, @function
_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC2EOS5_:
.LFB3232:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt5tupleIJPFvvEEEC1EOS2_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3232:
	.size	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC2EOS5_, .-_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC2EOS5_
	.weak	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC1EOS5_
	.set	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC1EOS5_,_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC2EOS5_
	.section	.text._ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC2EOS6_,"axG",@progbits,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC5EOS6_,comdat
	.align 2
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC2EOS6_
	.type	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC2EOS6_, @function
_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC2EOS6_:
.LFB3234:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6thread6_StateC2Ev
	leaq	16+_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE(%rip), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-24(%rbp), %rax
	leaq	8(%rax), %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardINSt6thread8_InvokerISt5tupleIJPFvvEEEEEEOT_RNSt16remove_referenceIS7_E4typeE
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEC1EOS5_
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3234:
	.size	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC2EOS6_, .-_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC2EOS6_
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC1EOS6_
	.set	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC1EOS6_,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEC2EOS6_
	.section	.text._ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC2IS3_vEEPS1_,"axG",@progbits,_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC5IS3_vEEPS1_,comdat
	.align 2
	.weak	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC2IS3_vEEPS1_
	.type	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC2IS3_vEEPS1_, @function
_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC2IS3_vEEPS1_:
.LFB3237:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3237
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC1EPS1_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3237:
	.section	.gcc_except_table
.LLSDA3237:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3237-.LLSDACSB3237
.LLSDACSB3237:
.LLSDACSE3237:
	.section	.text._ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC2IS3_vEEPS1_,"axG",@progbits,_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC5IS3_vEEPS1_,comdat
	.size	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC2IS3_vEEPS1_, .-_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC2IS3_vEEPS1_
	.weak	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC1IS3_vEEPS1_
	.set	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC1IS3_vEEPS1_,_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EEC2IS3_vEEPS1_
	.section	.text._ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv,"axG",@progbits,_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv
	.type	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv, @function
_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv:
.LFB3239:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3239:
	.size	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv, .-_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv
	.section	.text._ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EE11get_deleterEv,"axG",@progbits,_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EE11get_deleterEv,comdat
	.align 2
	.weak	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EE11get_deleterEv
	.type	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EE11get_deleterEv, @function
_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EE11get_deleterEv:
.LFB3240:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE10_M_deleterEv
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3240:
	.size	_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EE11get_deleterEv, .-_ZNSt10unique_ptrINSt6thread6_StateESt14default_deleteIS1_EE11get_deleterEv
	.section	.text._ZSt4moveIRPNSt6thread6_StateEEONSt16remove_referenceIT_E4typeEOS5_,"axG",@progbits,_ZSt4moveIRPNSt6thread6_StateEEONSt16remove_referenceIT_E4typeEOS5_,comdat
	.weak	_ZSt4moveIRPNSt6thread6_StateEEONSt16remove_referenceIT_E4typeEOS5_
	.type	_ZSt4moveIRPNSt6thread6_StateEEONSt16remove_referenceIT_E4typeEOS5_, @function
_ZSt4moveIRPNSt6thread6_StateEEONSt16remove_referenceIT_E4typeEOS5_:
.LFB3241:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3241:
	.size	_ZSt4moveIRPNSt6thread6_StateEEONSt16remove_referenceIT_E4typeEOS5_, .-_ZSt4moveIRPNSt6thread6_StateEEONSt16remove_referenceIT_E4typeEOS5_
	.section	.text._ZNKSt14default_deleteINSt6thread6_StateEEclEPS1_,"axG",@progbits,_ZNKSt14default_deleteINSt6thread6_StateEEclEPS1_,comdat
	.align 2
	.weak	_ZNKSt14default_deleteINSt6thread6_StateEEclEPS1_
	.type	_ZNKSt14default_deleteINSt6thread6_StateEEclEPS1_, @function
_ZNKSt14default_deleteINSt6thread6_StateEEclEPS1_:
.LFB3242:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	testq	%rax, %rax
	je	.L89
	movq	(%rax), %rdx
	addq	$8, %rdx
	movq	(%rdx), %rdx
	movq	%rax, %rdi
	call	*%rdx
.L89:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3242:
	.size	_ZNKSt14default_deleteINSt6thread6_StateEEclEPS1_, .-_ZNKSt14default_deleteINSt6thread6_StateEEclEPS1_
	.section	.text._ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_
	.type	_ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_, @function
_ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_:
.LFB3284:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm0EPFvvELb0EE7_M_headERS2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3284:
	.size	_ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_, .-_ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_
	.section	.text._ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE,"axG",@progbits,_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE,comdat
	.weak	_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	.type	_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE, @function
_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE:
.LFB3285:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3285:
	.size	_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE, .-_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	.section	.text._ZNSt10_Head_baseILm0EPFvvELb0EEC2IS1_EEOT_,"axG",@progbits,_ZNSt10_Head_baseILm0EPFvvELb0EEC5IS1_EEOT_,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0EPFvvELb0EEC2IS1_EEOT_
	.type	_ZNSt10_Head_baseILm0EPFvvELb0EEC2IS1_EEOT_, @function
_ZNSt10_Head_baseILm0EPFvvELb0EEC2IS1_EEOT_:
.LFB3287:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3287:
	.size	_ZNSt10_Head_baseILm0EPFvvELb0EEC2IS1_EEOT_, .-_ZNSt10_Head_baseILm0EPFvvELb0EEC2IS1_EEOT_
	.weak	_ZNSt10_Head_baseILm0EPFvvELb0EEC1IS1_EEOT_
	.set	_ZNSt10_Head_baseILm0EPFvvELb0EEC1IS1_EEOT_,_ZNSt10_Head_baseILm0EPFvvELb0EEC2IS1_EEOT_
	.section	.text._ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC2EPS1_,"axG",@progbits,_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC5EPS1_,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC2EPS1_
	.type	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC2EPS1_, @function
_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC2EPS1_:
.LFB3290:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC1IS2_S4_Lb1EEEv
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE6_M_ptrEv
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3290:
	.size	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC2EPS1_, .-_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC2EPS1_
	.weak	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC1EPS1_
	.set	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC1EPS1_,_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EEC2EPS1_
	.section	.text._ZSt3getILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_,"axG",@progbits,_ZSt3getILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_,comdat
	.weak	_ZSt3getILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_
	.type	_ZSt3getILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_, @function
_ZSt3getILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_:
.LFB3292:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm0EPNSt6thread6_StateEJSt14default_deleteIS1_EEERT0_RSt11_Tuple_implIXT_EJS5_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3292:
	.size	_ZSt3getILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_, .-_ZSt3getILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_
	.section	.text._ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE10_M_deleterEv,"axG",@progbits,_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE10_M_deleterEv,comdat
	.align 2
	.weak	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE10_M_deleterEv
	.type	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE10_M_deleterEv, @function
_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE10_M_deleterEv:
.LFB3293:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm1EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3293:
	.size	_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE10_M_deleterEv, .-_ZNSt15__uniq_ptr_implINSt6thread6_StateESt14default_deleteIS1_EE10_M_deleterEv
	.section	.text._ZNSt10_Head_baseILm0EPFvvELb0EE7_M_headERS2_,"axG",@progbits,_ZNSt10_Head_baseILm0EPFvvELb0EE7_M_headERS2_,comdat
	.weak	_ZNSt10_Head_baseILm0EPFvvELb0EE7_M_headERS2_
	.type	_ZNSt10_Head_baseILm0EPFvvELb0EE7_M_headERS2_, @function
_ZNSt10_Head_baseILm0EPFvvELb0EE7_M_headERS2_:
.LFB3327:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3327:
	.size	_ZNSt10_Head_baseILm0EPFvvELb0EE7_M_headERS2_, .-_ZNSt10_Head_baseILm0EPFvvELb0EE7_M_headERS2_
	.section	.text._ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC2IS2_S4_Lb1EEEv,"axG",@progbits,_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC5IS2_S4_Lb1EEEv,comdat
	.align 2
	.weak	_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC2IS2_S4_Lb1EEEv
	.type	_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC2IS2_S4_Lb1EEEv, @function
_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC2IS2_S4_Lb1EEEv:
.LFB3329:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3329:
	.size	_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC2IS2_S4_Lb1EEEv, .-_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC2IS2_S4_Lb1EEEv
	.weak	_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC1IS2_S4_Lb1EEEv
	.set	_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC1IS2_S4_Lb1EEEv,_ZNSt5tupleIJPNSt6thread6_StateESt14default_deleteIS1_EEEC2IS2_S4_Lb1EEEv
	.section	.text._ZSt12__get_helperILm0EPNSt6thread6_StateEJSt14default_deleteIS1_EEERT0_RSt11_Tuple_implIXT_EJS5_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EPNSt6thread6_StateEJSt14default_deleteIS1_EEERT0_RSt11_Tuple_implIXT_EJS5_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EPNSt6thread6_StateEJSt14default_deleteIS1_EEERT0_RSt11_Tuple_implIXT_EJS5_DpT1_EE
	.type	_ZSt12__get_helperILm0EPNSt6thread6_StateEJSt14default_deleteIS1_EEERT0_RSt11_Tuple_implIXT_EJS5_DpT1_EE, @function
_ZSt12__get_helperILm0EPNSt6thread6_StateEJSt14default_deleteIS1_EEERT0_RSt11_Tuple_implIXT_EJS5_DpT1_EE:
.LFB3331:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEE7_M_headERS5_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3331:
	.size	_ZSt12__get_helperILm0EPNSt6thread6_StateEJSt14default_deleteIS1_EEERT0_RSt11_Tuple_implIXT_EJS5_DpT1_EE, .-_ZSt12__get_helperILm0EPNSt6thread6_StateEJSt14default_deleteIS1_EEERT0_RSt11_Tuple_implIXT_EJS5_DpT1_EE
	.section	.text._ZSt3getILm1EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_,"axG",@progbits,_ZSt3getILm1EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_,comdat
	.weak	_ZSt3getILm1EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_
	.type	_ZSt3getILm1EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_, @function
_ZSt3getILm1EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_:
.LFB3332:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm1ESt14default_deleteINSt6thread6_StateEEJEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3332:
	.size	_ZSt3getILm1EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_, .-_ZSt3getILm1EJPNSt6thread6_StateESt14default_deleteIS1_EEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS9_
	.section	.text._ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC2Ev,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC5Ev,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC2Ev
	.type	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC2Ev, @function
_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC2Ev:
.LFB3366:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC2Ev
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3366:
	.size	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC2Ev, .-_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC2Ev
	.weak	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC1Ev
	.set	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC1Ev,_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEEC2Ev
	.section	.text._ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEE7_M_headERS5_,"axG",@progbits,_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEE7_M_headERS5_,comdat
	.weak	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEE7_M_headERS5_
	.type	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEE7_M_headERS5_, @function
_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEE7_M_headERS5_:
.LFB3368:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EE7_M_headERS3_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3368:
	.size	_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEE7_M_headERS5_, .-_ZNSt11_Tuple_implILm0EJPNSt6thread6_StateESt14default_deleteIS1_EEE7_M_headERS5_
	.section	.text._ZSt12__get_helperILm1ESt14default_deleteINSt6thread6_StateEEJEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm1ESt14default_deleteINSt6thread6_StateEEJEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm1ESt14default_deleteINSt6thread6_StateEEJEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	.type	_ZSt12__get_helperILm1ESt14default_deleteINSt6thread6_StateEEJEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE, @function
_ZSt12__get_helperILm1ESt14default_deleteINSt6thread6_StateEEJEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE:
.LFB3369:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEE7_M_headERS4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3369:
	.size	_ZSt12__get_helperILm1ESt14default_deleteINSt6thread6_StateEEJEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE, .-_ZSt12__get_helperILm1ESt14default_deleteINSt6thread6_StateEEJEERT0_RSt11_Tuple_implIXT_EJS4_DpT1_EE
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC2Ev,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC5Ev,comdat
	.align 2
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC2Ev
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC2Ev, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC2Ev:
.LFB3388:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC2Ev
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3388:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC2Ev, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC2Ev
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC1Ev
	.set	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC1Ev,_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEEC2Ev
	.section	.text._ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC2Ev,"axG",@progbits,_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC5Ev,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC2Ev
	.type	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC2Ev, @function
_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC2Ev:
.LFB3391:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3391:
	.size	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC2Ev, .-_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC2Ev
	.weak	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC1Ev
	.set	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC1Ev,_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EEC2Ev
	.section	.text._ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EE7_M_headERS3_,"axG",@progbits,_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EE7_M_headERS3_,comdat
	.weak	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EE7_M_headERS3_
	.type	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EE7_M_headERS3_, @function
_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EE7_M_headERS3_:
.LFB3393:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3393:
	.size	_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EE7_M_headERS3_, .-_ZNSt10_Head_baseILm0EPNSt6thread6_StateELb0EE7_M_headERS3_
	.section	.text._ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEE7_M_headERS4_,"axG",@progbits,_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEE7_M_headERS4_,comdat
	.weak	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEE7_M_headERS4_
	.type	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEE7_M_headERS4_, @function
_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEE7_M_headERS4_:
.LFB3394:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EE7_M_headERS4_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3394:
	.size	_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEE7_M_headERS4_, .-_ZNSt11_Tuple_implILm1EJSt14default_deleteINSt6thread6_StateEEEE7_M_headERS4_
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC2Ev,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC5Ev,comdat
	.align 2
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC2Ev
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC2Ev, @function
_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC2Ev:
.LFB3402:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3402:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC2Ev, .-_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC2Ev
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC1Ev
	.set	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC1Ev,_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EEC2Ev
	.section	.text._ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EE7_M_headERS4_,"axG",@progbits,_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EE7_M_headERS4_,comdat
	.weak	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EE7_M_headERS4_
	.type	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EE7_M_headERS4_, @function
_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EE7_M_headERS4_:
.LFB3404:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3404:
	.size	_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EE7_M_headERS4_, .-_ZNSt10_Head_baseILm1ESt14default_deleteINSt6thread6_StateEELb1EE7_M_headERS4_
	.weak	_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.section	.data.rel.ro.local._ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,"awG",@progbits,_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,comdat
	.align 8
	.type	_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, @object
	.size	_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, 40
_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE:
	.quad	0
	.quad	_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.quad	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED1Ev
	.quad	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev
	.quad	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv
	.section	.text._ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev,"axG",@progbits,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED5Ev,comdat
	.align 2
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev
	.type	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev, @function
_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev:
.LFB3408:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	leaq	16+_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE(%rip), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6thread6_StateD2Ev@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3408:
	.size	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev, .-_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED1Ev
	.set	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED1Ev,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED2Ev
	.section	.text._ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev,"axG",@progbits,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED5Ev,comdat
	.align 2
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev
	.type	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev, @function
_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev:
.LFB3410:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED1Ev
	movq	-8(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3410:
	.size	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev, .-_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEED0Ev
	.weak	_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.section	.data.rel.ro._ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,"awG",@progbits,_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,comdat
	.align 8
	.type	_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, @object
	.size	_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, 24
_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.quad	_ZTINSt6thread6_StateE
	.weak	_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE
	.section	.rodata._ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,"aG",@progbits,_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE,comdat
	.align 32
	.type	_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, @object
	.size	_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE, 59
_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE:
	.string	"NSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEEE"
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB3427:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L125
	cmpl	$65535, -8(%rbp)
	jne	.L125
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
.L125:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3427:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.section	.text._ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv,"axG",@progbits,_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv,comdat
	.align 2
	.weak	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv
	.type	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv, @function
_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv:
.LFB3428:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEclEv
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3428:
	.size	_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv, .-_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJPFvvEEEEEE6_M_runEv
	.section	.text._ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEclEv,"axG",@progbits,_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEclEv,comdat
	.align 2
	.weak	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEclEv
	.type	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEclEv, @function
_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEclEv:
.LFB3429:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEE9_M_invokeIJLm0EEEEvSt12_Index_tupleIJXspT_EEE
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L129
	call	__stack_chk_fail@PLT
.L129:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3429:
	.size	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEclEv, .-_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEEclEv
	.section	.text._ZNSt6thread8_InvokerISt5tupleIJPFvvEEEE9_M_invokeIJLm0EEEEvSt12_Index_tupleIJXspT_EEE,"axG",@progbits,_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEE9_M_invokeIJLm0EEEEvSt12_Index_tupleIJXspT_EEE,comdat
	.align 2
	.weak	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEE9_M_invokeIJLm0EEEEvSt12_Index_tupleIJXspT_EEE
	.type	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEE9_M_invokeIJLm0EEEEvSt12_Index_tupleIJXspT_EEE, @function
_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEE9_M_invokeIJLm0EEEEvSt12_Index_tupleIJXspT_EEE:
.LFB3430:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRSt5tupleIJPFvvEEEEONSt16remove_referenceIT_E4typeEOS6_
	movq	%rax, %rdi
	call	_ZSt3getILm0EJPFvvEEEONSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEOS6_
	movq	%rax, %rdi
	call	_ZSt8__invokeIPFvvEJEENSt15__invoke_resultIT_JDpT0_EE4typeEOS3_DpOS4_
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3430:
	.size	_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEE9_M_invokeIJLm0EEEEvSt12_Index_tupleIJXspT_EEE, .-_ZNSt6thread8_InvokerISt5tupleIJPFvvEEEE9_M_invokeIJLm0EEEEvSt12_Index_tupleIJXspT_EEE
	.section	.text._ZSt4moveIRSt5tupleIJPFvvEEEEONSt16remove_referenceIT_E4typeEOS6_,"axG",@progbits,_ZSt4moveIRSt5tupleIJPFvvEEEEONSt16remove_referenceIT_E4typeEOS6_,comdat
	.weak	_ZSt4moveIRSt5tupleIJPFvvEEEEONSt16remove_referenceIT_E4typeEOS6_
	.type	_ZSt4moveIRSt5tupleIJPFvvEEEEONSt16remove_referenceIT_E4typeEOS6_, @function
_ZSt4moveIRSt5tupleIJPFvvEEEEONSt16remove_referenceIT_E4typeEOS6_:
.LFB3432:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3432:
	.size	_ZSt4moveIRSt5tupleIJPFvvEEEEONSt16remove_referenceIT_E4typeEOS6_, .-_ZSt4moveIRSt5tupleIJPFvvEEEEONSt16remove_referenceIT_E4typeEOS6_
	.section	.text._ZSt3getILm0EJPFvvEEEONSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEOS6_,"axG",@progbits,_ZSt3getILm0EJPFvvEEEONSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEOS6_,comdat
	.weak	_ZSt3getILm0EJPFvvEEEONSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEOS6_
	.type	_ZSt3getILm0EJPFvvEEEONSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEOS6_, @function
_ZSt3getILm0EJPFvvEEEONSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEOS6_:
.LFB3433:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt3getILm0EJPFvvEEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS6_
	movq	%rax, %rdi
	call	_ZSt7forwardIOPFvvEEOT_RNSt16remove_referenceIS3_E4typeE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3433:
	.size	_ZSt3getILm0EJPFvvEEEONSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEOS6_, .-_ZSt3getILm0EJPFvvEEEONSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeEOS6_
	.section	.text._ZSt8__invokeIPFvvEJEENSt15__invoke_resultIT_JDpT0_EE4typeEOS3_DpOS4_,"axG",@progbits,_ZSt8__invokeIPFvvEJEENSt15__invoke_resultIT_JDpT0_EE4typeEOS3_DpOS4_,comdat
	.weak	_ZSt8__invokeIPFvvEJEENSt15__invoke_resultIT_JDpT0_EE4typeEOS3_DpOS4_
	.type	_ZSt8__invokeIPFvvEJEENSt15__invoke_resultIT_JDpT0_EE4typeEOS3_DpOS4_, @function
_ZSt8__invokeIPFvvEJEENSt15__invoke_resultIT_JDpT0_EE4typeEOS3_DpOS4_:
.LFB3434:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	movq	%rax, %rdi
	call	_ZSt13__invoke_implIvPFvvEJEET_St14__invoke_otherOT0_DpOT1_
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L138
	call	__stack_chk_fail@PLT
.L138:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3434:
	.size	_ZSt8__invokeIPFvvEJEENSt15__invoke_resultIT_JDpT0_EE4typeEOS3_DpOS4_, .-_ZSt8__invokeIPFvvEJEENSt15__invoke_resultIT_JDpT0_EE4typeEOS3_DpOS4_
	.section	.text._ZSt3getILm0EJPFvvEEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS6_,"axG",@progbits,_ZSt3getILm0EJPFvvEEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS6_,comdat
	.weak	_ZSt3getILm0EJPFvvEEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS6_
	.type	_ZSt3getILm0EJPFvvEEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS6_, @function
_ZSt3getILm0EJPFvvEEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS6_:
.LFB3435:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt12__get_helperILm0EPFvvEJEERT0_RSt11_Tuple_implIXT_EJS2_DpT1_EE
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3435:
	.size	_ZSt3getILm0EJPFvvEEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS6_, .-_ZSt3getILm0EJPFvvEEERNSt13tuple_elementIXT_ESt5tupleIJDpT0_EEE4typeERS6_
	.section	.text._ZSt7forwardIOPFvvEEOT_RNSt16remove_referenceIS3_E4typeE,"axG",@progbits,_ZSt7forwardIOPFvvEEOT_RNSt16remove_referenceIS3_E4typeE,comdat
	.weak	_ZSt7forwardIOPFvvEEOT_RNSt16remove_referenceIS3_E4typeE
	.type	_ZSt7forwardIOPFvvEEOT_RNSt16remove_referenceIS3_E4typeE, @function
_ZSt7forwardIOPFvvEEOT_RNSt16remove_referenceIS3_E4typeE:
.LFB3436:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3436:
	.size	_ZSt7forwardIOPFvvEEOT_RNSt16remove_referenceIS3_E4typeE, .-_ZSt7forwardIOPFvvEEOT_RNSt16remove_referenceIS3_E4typeE
	.section	.text._ZSt13__invoke_implIvPFvvEJEET_St14__invoke_otherOT0_DpOT1_,"axG",@progbits,_ZSt13__invoke_implIvPFvvEJEET_St14__invoke_otherOT0_DpOT1_,comdat
	.weak	_ZSt13__invoke_implIvPFvvEJEET_St14__invoke_otherOT0_DpOT1_
	.type	_ZSt13__invoke_implIvPFvvEJEET_St14__invoke_otherOT0_DpOT1_, @function
_ZSt13__invoke_implIvPFvvEJEET_St14__invoke_otherOT0_DpOT1_:
.LFB3437:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt7forwardIPFvvEEOT_RNSt16remove_referenceIS2_E4typeE
	movq	(%rax), %rax
	call	*%rax
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3437:
	.size	_ZSt13__invoke_implIvPFvvEJEET_St14__invoke_otherOT0_DpOT1_, .-_ZSt13__invoke_implIvPFvvEJEET_St14__invoke_otherOT0_DpOT1_
	.section	.text._ZSt12__get_helperILm0EPFvvEJEERT0_RSt11_Tuple_implIXT_EJS2_DpT1_EE,"axG",@progbits,_ZSt12__get_helperILm0EPFvvEJEERT0_RSt11_Tuple_implIXT_EJS2_DpT1_EE,comdat
	.weak	_ZSt12__get_helperILm0EPFvvEJEERT0_RSt11_Tuple_implIXT_EJS2_DpT1_EE
	.type	_ZSt12__get_helperILm0EPFvvEJEERT0_RSt11_Tuple_implIXT_EJS2_DpT1_EE, @function
_ZSt12__get_helperILm0EPFvvEJEERT0_RSt11_Tuple_implIXT_EJS2_DpT1_EE:
.LFB3438:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt11_Tuple_implILm0EJPFvvEEE7_M_headERS2_
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3438:
	.size	_ZSt12__get_helperILm0EPFvvEJEERT0_RSt11_Tuple_implIXT_EJS2_DpT1_EE, .-_ZSt12__get_helperILm0EPFvvEJEERT0_RSt11_Tuple_implIXT_EJS2_DpT1_EE
	.text
	.type	_GLOBAL__sub_I__Z10sleep_testv, @function
_GLOBAL__sub_I__Z10sleep_testv:
.LFB3439:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3439:
	.size	_GLOBAL__sub_I__Z10sleep_testv, .-_GLOBAL__sub_I__Z10sleep_testv
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z10sleep_testv
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
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
