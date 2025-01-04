global ft_list_size

%include "structs.inc"

section .text
; C Prototype:
;    int ft_list_size(t_list *head);
;
; Description:
;    Counts the number of nodes in a linked list.
;
; Parameters:
;    rdi: Pointer to the first node of linked list
;
; Return value:
;    rax: The number of nodes in the linked list
ft_list_size:
	xor eax, eax
.loop:
	test rdi, rdi
	jz .end
	inc rax
	mov rdi, [ rdi + t_list.next ]
	jmp .loop
.end:
	ret
