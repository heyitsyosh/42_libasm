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
	xor ecx, ecx
.loop:
	mov al, byte [rdi + rcx]
	mov dl, byte [rsi + rcx]
	cmp al, dl
	jne .diff
	test al, al
	jz .end
	inc rcx
	jmp .loop
.diff:
	movzx eax, al
	movzx edx, dl
	sub eax, edx
    ret

.end:
	xor eax, eax
	ret
