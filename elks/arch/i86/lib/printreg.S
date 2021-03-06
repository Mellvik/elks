#include <linuxmt/config.h>

/* This file contains print_regs, which will dump out all of the registers
 * and print them out.  This is probably one of the sickest routines ever
 * written :) - Chad
 *
 * void print_regs(void);
 * void print_sp(void);
 */
	.code16
	.text

	.global print_regs
	.global print_sp
	.extern	printk

print_regs:
	push %bp
	push %ss
	push %es
	push %ds
	push %cs
	push %si
	push %di
	push %dx
	push %cx
	push %bx
	push %ax
	mov  $fmtprg,%ax
	push %ax
	call printk
	pop %ax
	pop %ax
	pop %bx
	pop %cx
	pop %dx
	pop %di
	pop %si
	pop %ds		// Can not pop cs.
	pop %ds
	pop %es
	pop %ss
	pop %bp
	ret

print_sp:
	mov %sp,%ax
	add $2,%ax
	push %ax
	push %ss
	mov $msg,%ax
	push %ax
	call printk
	pop %ax
	pop %ax
	pop %ax
	ret

	.data
msg:	.ascii	"SP=%x:%x\n"
	.byte	0
fmtprg:	.ascii	"AX=%x BX=%x CX=%x DX=%x DI=%x SI=%x\nCS=%x DS=%x ES=%x SS=%x BP=%x\n"
	.byte	0
