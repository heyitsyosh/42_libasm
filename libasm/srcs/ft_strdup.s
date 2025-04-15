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
	call ft_strlen
	push rdi
	inc rax
	mov rdi, rax
	call malloc wrt ..plt
	jz .error_handle

	pop rsi
	mov rdi, rax
	call ft_strcpy
	ret

.error_handle:
	pop rdi
	neg rax
	mov rdi, rax
	call __errno_location wrt ..plt
	mov [ rax ], rdi
	mov rax, -1
	ret
