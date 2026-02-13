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
	jz .error_end		; if (!str) return
	test rsi, rsi
	jz .error_end		; if (!base) return
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
	jz .validate_base_increment	; No duplicates found, continue validation

	cmp r9b, dl
	je .error_end		; Duplicate found in base
	jmp .check_for_duplicates_loop
.validate_base_increment:
	inc r8d				; i++
	jmp .validate_base_loop
.validate_length:
	cmp r8d, 2
	jb .error_end		; Ensure that base_len >= 2

; Parse and convert input string
	xor eax, eax		; return_value = 0
	mov r9d, 1			; sign = +1
						; r8d = base_len
.skip_spaces_loop:
	mov dl, byte [rdi]
	cmp dl, ' '
	je .skip_spaces_increment
	cmp dl, 9
	jb .parse_sign_loop
	cmp dl, 13
	ja .parse_sign_loop
.skip_spaces_increment:
	inc rdi
	jmp .skip_spaces_loop

.parse_sign_loop:
	mov dl, byte [rdi]
	cmp dl, '+'
	je .parse_sign_increment
	cmp dl, '-'
	jne .convert
	neg r9d
.parse_sign_increment:
	inc rdi
	jmp .parse_sign_loop

.convert:
	mov dl, byte [rdi]
	test dl, dl
	jz .apply_sign			; if (str[i] == '\0') → apply sign
	xor ecx, ecx
.find_digit_loop:
	mov r10b, [rsi + rcx]	; Isolate one digit
	test r10b, r10b
	jz .apply_sign			; Digit to convert was not in base → apply sign
	cmp r10b, dl			; Find digit in base
	je .add_one_digit
	inc ecx
	jmp .find_digit_loop
.add_one_digit:
	imul eax, r8d
	add eax, ecx
	inc rdi
	jmp .convert

.apply_sign:
	cmp r9d, 0
	jge .end
	neg eax
.end:
	ret
.error_end:
	xor eax, eax
	ret
