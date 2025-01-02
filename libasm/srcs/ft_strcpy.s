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
	xor ecx, ecx
	mov rax, rdi
.loop:
	mov dl, byte [rsi + rcx]
	mov byte [rdi + rcx], dl
	inc rcx
	test dl, dl
	jnz .loop
	ret
