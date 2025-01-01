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
	mov dl, byte [rdi + rcx]
	test dl, dl
	jz .end

	mov dh, byte [rsi + rcx]
	sub dl, dh
	mov al, dl
	cmp dl, 0
	jnz .end

	inc rcx
	jmp .loop
.end:
	ret
