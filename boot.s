.arch i8086
.code16

	.section .text
	.globl _start

_start:
	nop # here we go, OS boot
	jmp init # jump to start procedure

init:
	cli # disable interrupts while we make ourselves busy
	xor %ax, %ax
	mov %ax, %ss # stack segment register = 0x0000
	mov %cs, %sp # stack pointer = 0x7c00
	sti # turn interrupts back on, it's showtime
	push %ax # push stuff into the stack
	push %ax

    mov %ax, %ds # data segment = 0x0000
    mov %ax, %es # extra segment = 0x0000
    
    jmp main

main:
    mov $msg1, %ax
    push %ax
    call print
    
    mov $msg2, %ax
    push %ax
    call print

halt:
    hlt
    jmp halt

print:
   mov char_ptr,%di        # Store cursor position at %di
   mov screen, %ax         # Move the video memory address ...
   mov %ax, %es            # ... to the extra segment register
   mov %sp, %bp            # Read string argument from stack
   mov 2(%bp), %si
putchar:
   xor %dx, %dx            # Reset the data register
   mov (%si), %dl          # Move a character to %dl register
   cmp $0, %dl             # Compare ...
   jz print_end            # ... and jump if character is  
   mov %dl, %es:(%di)      # Move the character to video memory
   inc %di                 # Increment the destination index
   mov char_fmt, %dx       # Obtain character format ...
   movb %dl, %es:(%di)     # ... and move it to video memory
   inc %di                 # Increment both pointers
   inc %si
   jmp putchar             # And put the next character
print_end:
   mov %di, %ax            # Get the cursor position
   xor %dx, %dx
   mov $160, %cx
   div %cx                 # Divide it by screen size
   sub %dx, %cx            # Subtract the remainder from screen size
   mov %di, %ax
   add %cx, %ax            # And add it to cursor position
   lea char_ptr, %bp
   mov %ax, (%bp)          # Set the new cursor position
   ret


	.section .data
msg1: .asciz "Hello, world!"
msg2: .asciz "This is a message."
char_ptr: .word 0x0000
char_fmt: .word 0x000f
screen: .word 0xb800
.end
