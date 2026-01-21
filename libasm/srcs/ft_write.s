global ft_write

extern __errno_location

section .text
; C Prototype:
;    ssize_t write(int fd, const void *buf, size_t count);
;
; Description:
;    Writes data from a buffer to a file descriptor.
;
; Parameters:
;    rdi: File descriptor to write into
;    rsi: Pointer to the buffer with data to write
;    rdx: Number of bytes to write
;
; Return:
;    rax: Number of bytes written (>= 0), or -1 on error
ft_write:
	mov rax, 1
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
