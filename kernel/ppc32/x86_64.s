.globl __ISR_trap
__ISR_trap:
	cli
	wbinvd
	mov %rax, __ISR_regs
	lea __ISR_regs, %rax
	mov %rsp, 8(%rax)
	mov %rbp, 16(%rax)
	mov %rbx, 32(%rax)
	mov __ISR_regs, %rbx
	mov %rbx, 24(%rax)
	mov %rcx, 40(%rax)
	mov %rdx, 48(%rax)
	mov %rsi, 56(%rax)
	mov %rdx, 64(%rax)
	mov %r8, 72(%rax)
	mov %r9, 80(%rax)
	mov %r10, 88(%rax)
	mov %r11, 96(%rax)
	mov %r12, 104(%rax)
	mov %r13, 112(%rax)
	mov %r14, 120(%rax)
	mov %r15, 128(%rax)
	lea __ISR_stack, %rbp
	addq 8192, %rbp
	mov %rbp, %rsp
	addq -8, %rsp
	call _ISR
	sti
	rsm

.globl ctx.get
ctx.get:
	movq endget, %rax
	movq %rax, 0(%rdi)
	movq %rsp, 8(%rdi)
	movq %rbp, 16(%rdi)
	movq $0, 24(%rdi)
	movq %rbp, 32(%rdi)
	movq $0, 40(%rdi)
	movq $0, 48(%rdi)
	movq $0, 56(%rdi)
	movq $0, 64(%rdi)
	movq %rdi, 72(%rdi)
	movq $0, 80(%rdi)
	movq $0, 88(%rdi)
	movq $0, 96(%rdi)
	movq $0, 104(%rdi)
	movq %r12, 112(%rdi)
	movq %r13, 120(%rdi)
	movq %r14, 128(%rdi)
	movq %r15, 136(%rdi)
endget:
	ret

.globl ctx.set
ctx.set:
	movq 0(%rdi), %rax
	movq %rax, storage.ip
	movq 8(%rdi), %rsp
	movq 16(%rdi), %rbp
	movq 24(%rdi), %rax
	movq 32(%rdi), %rbx
	movq 40(%rdi), %rbx
	movq 48(%rdi), %rcx
	movq 56(%rdi), %rdx
	movq 64(%rdi), %rsi
	movq 80(%rdi), %r8
	movq 88(%rdi), %r9
	movq 96(%rdi), %r10
	movq 104(%rdi), %r11
	movq 112(%rdi), %r12
	movq 120(%rdi), %r13
	movq 128(%rdi), %r14
	movq 136(%rdi), %r15
	movq 72(%rdi), %rdi
	jmp *(storage.ip)

storage.ip:
	.long 0

.globl __ISR_regs
__ISR_regs:
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0

	.comm __ISR_stack,8192,4
