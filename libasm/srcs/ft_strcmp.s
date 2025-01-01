global ft_strcmp

section .text
; C Prototype:
;    int strcmp(const char *s1, const char *s2);
;
; Description:
;    Compares two strings lexicographically.
;
; Parameters:
;    rdi: Pointer to the first string (s1)
;    rsi: Pointer to the second string (s2)
;
; Return:
;    rax:
;      0  if s1 == s2
;      <0  if s1 < s2
;      >0  if s1 > s2
ft_strcmp:
	xor rcx, rcx
	xor rax, rax
.loop:
	mov bl, byte [rdi + rcx]
	test bl, bl
	jz .end

	mov bh, byte [rsi + rcx]
	sub bl, bh
	mov al, bl
	cmp bl, 0
	jnz .end

	inc rcx
	jmp .loop
.end:
	ret
