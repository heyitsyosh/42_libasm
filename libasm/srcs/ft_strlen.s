global ft_strlen

section .text
; C Prototype:
;    size_t strlen(const char *s);
;
; Description:
;     Calculates the length of a string.
;
; Parameters:
;    rdi: Pointer to string (s)
;
; Return:
;    rax: Number of bytes in string
ft_strlen:
	xor rax, rax
.loop:
	mov bl, byte [rdi + rax]
	test bl, bl
	jz .end
	inc rax
	jmp .loop
.end:
	ret
