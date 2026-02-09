global ft_isspace

section .text
; C Prototype:
;    int isspace(int c);
;
; Description:
;    Checks whether the given character is a whitespace character.
;
; Parameters:
;    rdi: Character to check (typically promoted from an unsigned char)
;
; Return value:
;    rax: Non-zero if the character is a whitespace character, 0 otherwise.
ft_isspace:
	mov dl, byte [rax]

	cmp dl, ' '
	je .true
	cmp dl, 9
	jb .false
	cmp dl, 13
	jbe .true
.true:
	mov eax, 1
	ret
.false:
	xor eax, eax
	ret
