global ft_atoi_base

section .text
; C Prototype:
;    int ft_atoi_base(char *str, char *base);
;
; Description:
;    Converts the input string to an integer in the specified base.
;    Ignores leading whitespace, determines the sign from consecutive
;    '+' and '-' characters, and converts until the first character not
;    in the base.
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
	xor r8d, r8d		; i = 0

.validate_base_loop:
	mov dl, byte [rsi + r8]
	test dl, dl
	jz .validate_length
	
	cmp dl, '+'
	je .error_end
	cmp dl, '-'
	je .error_end

	cmp dl, ' '
	je .error_end		; Whitespace found in base
	cmp dl, 9
	jb .check_for_duplicates
	cmp dl, 13
	jbe .error_end		; Whitespace found in base
.check_for_duplicates:	; Compare current base character against all following characters
	mov ecx, r8d		; j = i
.check_for_duplicates_loop:
	inc ecx				; j++
	mov r9b, byte [rsi + rcx]
	test r9b, r9b
	jz .increment_base_index	; No duplicates found, continue validation

	cmp r9b, dl
	je .error_end		; Duplicate found in base
	jmp .check_for_duplicates_loop
.increment_base_index:
	inc r8d				; i++
	jmp .validate_base_loop
.validate_length:
	cmp r8d, 2
	jb .error_end		; Ensure that base_len >= 2

; Parse and convert input string
	xor eax, eax		; Initialize return value to 0
	mov r9d, 1			; Initialize sign to 1 (positive)
						; r8d = base_len
.skip_spaces:
	mov dl, byte [rdi]

	cmp dl, ' '
	je .skip_spaces_loop
	cmp dl, 9
	jb .set_sign
	cmp dl, 13
	ja .set_sign
	inc rdi
	jmp .skip_spaces
.set_sign:
	mov dl, byte [rdi]

	cmp dl, '+'
	je .set_sign_loop
	cmp dl, '-'
	jne .convert

	neg r9d
.set_sign_loop:
	inc rdi
	jmp .parse_sign
.convert:
	mov dl, byte [rdi]
	test dl, dl
	jz .apply_sign

	; get current_digit

	mul eax, r8d
	add eax, current_digit
	inc rdi
	jmp .convert
.apply_sign:
	cmp r9d, 0
	jge .end
	neg rax
.end:
	ret
.error_end:
	xor eax, eax
	ret
