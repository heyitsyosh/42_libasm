global ft_strcpy

section .text
; C Prototype:
;    char *strcpy(char *dest, const char *src);
;
; Description:
;    Copies a string from source to destination.
;
; Parameters:
;    rdi: Pointer to the destination buffer (dest)
;    rsi: Pointer to the source string (src)
;
; Return:
;    rax: Pointer to the destination string
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
