global ft_strdup

extern ft_strlen
extern ft_strcpy
extern malloc
extern __errno_location

section .text
; C Prototype:
;    char *strdup(const char *s);
;
; Description:
;    Duplicates a string into newly allocated memory.
;
; Parameters:
;    rdi: Pointer to the source string
;
; Return:
;    rax: Pointer to the newly allocated duplicate string
;         (NULL if memory allocation fails)
ft_strdup:
	push rdi		; Save s in stack and align stack to 16-byte
	call ft_strlen
	inc rax			; Increment len to allocate '\0'

	mov rdi, rax
	call malloc wrt ..plt
	test rax, rax
	jz .error_handle

	mov rdi, rax	; Set dest
	mov rsi, [rsp]	; Set src
	call ft_strcpy	; ft_strlcpy(dest, src)
	add rsp, 8		; Discard pushed s
	ret

.error_handle:
	add rsp, 8		; Discard pushed s
	xor eax, eax
	ret
