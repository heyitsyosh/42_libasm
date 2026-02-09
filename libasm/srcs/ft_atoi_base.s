global ft_atoi_base

section .text
; C Prototype:
;    int ft_atoi_base(char *str, char *base);
;
; Description:
;    Converts the input string to an integer in the specified base.
;    (Leading whitespaces and optional signs in the input are handled.)
;
;    Base Validation Rules:
;    - The base must contain at least 2 characters.
;    - The base must not contain duplicate characters.
;    - The base must not contain '+' or '-' or any whitespace characters.
;
; Parameters:
;    rdi: Pointer to the input string
;    rsi: Pointer to the base string
;
; Return value:
;    rax: The integer representation of the string in the specified base,
;         or 0 if the input or base is invalid.
ft_atoi_base:
	test rdi, rdi
	jz .error_end		; Null guard base string
	test rsi, rsi
	jz .error_end		; Null guard base string
	xor eax, eax
.validate_base:
	mov dl, byte [rsi + rax]
	test dl, dl
	jz .validate_length
	
	cmp dl, '+'
	je .error_end
	cmp dl, '-'
	je .error_end

	cmp dl, ' '
	je .error_end
	cmp dl, 9
	jb .check_for_duplicates
	cmp dl, 13
	jbe .error_end		; Whitespace found in base
.check_for_duplicates:	; Compare current base character against all following characters
	mov ecx, eax		; Copy base character index (eax) to inner loop index
.check_for_duplicates_loop:
	inc ecx
	mov r8b, byte [rsi + rcx]
	test r8b, r8b
	jz .no_duplicate_found

	cmp dl, r8b
	je .error_end		; Duplicate found in base

	jmp .check_for_duplicates_loop
.no_duplicate_found:
	inc eax
	jmp .validate_base
.validate_length:
	cmp eax, 2
	jb .error_end		; Ensure that base is more than 1 character
	.atoi
.atoi:
.error_end:
	xor eax, eax
	ret

; https://github.com/heyitsyosh/42_c_piscine/blob/main/submissions/CPC04/ex05/ft_atoi_base.c
; ft_atoi_base
• Write a function that converts the initial portion of the string pointed to by str
into an integer representation.
• str is in a specific base, given as a second parameter.
• Except for the base rule, the function should behave exactly like ft_atoi.
• If an invalid argument is provided, the function should return 0.
Examples of invalid arguments:
◦ The base is empty or has only one character.
◦ The base contains duplicate characters.
◦ The base contains +, -, or whitespace characters.
