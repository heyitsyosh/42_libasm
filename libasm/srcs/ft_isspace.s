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
	mov al, byte [rax]

	cmp al, ' '
	je .true
	cmp al, 9
	jb .false
	cmp al, 13
	jbe .true
.false:
	xor eax, eax
	ret
.true:
	mov eax, 1
	ret
