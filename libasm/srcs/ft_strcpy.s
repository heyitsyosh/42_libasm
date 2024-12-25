global ft_strcpy

section .text
; Parameters
; 	(dest = rdi, src = rsi)
; Return
; 	rax: pointer to dest
ft_strcpy:
	xor rcx, rcx
	mov rax, rdi
.loop
	mov bl, byte [rsi + rcx]
	mov byte [rdi + rcx], bl
	inc rcx
	test bl, bl
	jne .loop
	ret
