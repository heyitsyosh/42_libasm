global ft_strlen

section .text
; C Prototype:
;    size_t strlen(const char *s);
;
; Description:
;    Calculates the length of a string.
;
; Parameters:
;    rdi: Pointer to the input string
;
; Return:
;    rax: Number of bytes in the string
ft_strlen:
	xor eax, eax
.loop:
	mov dl, byte [rdi + rax]
	test dl, dl
	jz .end
	inc rax
	jmp .loop
.end:
	ret
