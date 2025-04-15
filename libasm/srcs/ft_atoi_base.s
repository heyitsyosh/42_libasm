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
	;

; https://github.com/heyitsyosh/42_c_piscine/blob/main/submissions/CPC04/ex05/ft_atoi_base.c
; • Write a function that converts the initial portion of the string pointed by str to int
; representation.
; • str is in a specific base given as a second parameter.
; • excepted the base rule, the function should work exactly like ft_atoi.
; • If there’s an invalid argument, the function should return 0. Examples of invalid
; arguments :
; ◦ base is empty or size of 1;
; ◦ base contains the same character twice ;
; ◦ base contains + or - or whitespaces;
; • Here’s how it should be prototyped :
; int ft_atoi_base(char *str, char *base);

