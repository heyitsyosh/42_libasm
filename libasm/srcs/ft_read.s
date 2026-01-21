global ft_read

extern __errno_location

section .text
; C Prototype:
;    ssize_t read(int fd, void *buf, size_t count);
;
; Description:
;    Reads data from a file descriptor into a buffer.
;
; Parameters:
;    rdi: File descriptor to read from
;    rsi: Pointer to the buffer to read into
;    rdx: Number of bytes to read
;
; Return value:
;    rax: Number of bytes read (>= 0), or -1 on error
ft_read:
	xor eax, eax
	syscall
	cmp rax, 0
	jl .error_handle
	ret

.error_handle:
	neg rax
	push rax	; Save errno in stack and align stack to 16-byte
	call __errno_location wrt ..plt
	pop rdi
	mov [rax], edi
	mov rax, -1
	ret
