global ft_strcmp

section .text
; Parameters
; 	(str1 = rdi, str2 = rsi)
; Return
; 	rax:
; 		0 if strings are equal,
; 		< 0 if str1 is less than str2,
; 		> 0 if str1 is more than str2
ft_strcmp:
	xor rcx, rcx
	xor rax, rax
.loop:
	mov bl, byte [rdi + rcx]
	test bl, bl
	je .end

	mov bh, byte [rsi + rcx]
	sub bl, bh
	mov al, bl
	cmp bl, 0
	jne .end

	inc rcx
	jmp .loop
.end:
	ret
