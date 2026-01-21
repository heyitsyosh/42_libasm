global ft_list_push_front

extern malloc

%include "structs.inc"

section .text
; C Prototype:
;    void ft_list_push_front(t_list **head, void *data);
;
; Description:
;    Inserts a new node at the beginning of the linked list.
;    - Allocates memory for a new node of type t_list.
;    - Assigns the provided data to the new node.
;    - Links the new node to the current head of the list.
;    - Updates the head pointer to point to the newly created node.
;
; Parameters:
;    rdi: Double pointer to the first node of the linked list
;    rsi: Pointer to data to be assigned
;
; Return value:
;    None.
ft_list_push_front:
	push rdi
	push rsi
	sub rsp, 8	; align stack to 16-byte
	mov rdi, t_list_size
	call malloc wrt ..plt
	add rsp, 8
	test rax, rax
	pop rsi
	pop rdi
	jz .end
	mov [rax + t_list.data], rsi
	mov rdx, [rdi]
	mov [rax + t_list.next], rdx
	mov [rdi], rax
.end:
	ret
