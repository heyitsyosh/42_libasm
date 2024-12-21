global ft_strlen

section .text
ft_strlen:
	xor rax, rax
.loop:
	mov bl, byte [rdi + rax]
	test bl, bl
	je .end
	inc rax
	jmp .loop
.end:
	ret
