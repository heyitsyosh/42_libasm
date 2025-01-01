global ft_strcpy

section .text
; C Prototype:
;    char *strcpy(char *dest, const char *src);
;
; Description:
;    Copies a string from source to destination.
;
; Parameters:
;    rdi: Pointer to destination buffer (dest)
;    rsi: Pointer to source string (src)
;
; Return:
;    rax: Pointer to destination
ft_strcpy:
	xor rcx, rcx
	mov rax, rdi
.loop:
	mov bl, byte [rsi + rcx]
	mov byte [rdi + rcx], bl
	inc rcx
	test bl, bl
	jnz .loop
	ret
