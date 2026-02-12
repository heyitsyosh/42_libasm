global ft_list_remove_if

extern free

%include "structs.inc"

%define PREV r12
%define NEXT r13

section .text
; C Prototype:
;    void ft_list_remove_if(t_list **head, void *data_ref,
;                           int (*cmp)(data, data_ref), void (*free_fct)(void *));
; 
; Description:
;    Removes elements from a linked list if data matches 'data_ref'.
;    - Uses 'cmp' to compare each element's data with 'data_ref'.
;    - If 'cmp' returns 0, the element is removed and freed.
;    - Comparison and freeing is done by user-provided functions.
;
; Parameters:
;    rdi: Double pointer to the first node of the linked list
;    rsi: Pointer to the data reference value for comparison
;    rdx: Pointer to the comparison function
;    rcx: Pointer to the function for freeing data
;
; Return value:
;    None.
ft_list_remove_if:
	test rdi, rdi	; Null guard list head
	jz .end
	test rdx, rdx	; Null guard comparison function
	jz .end

	push rbx		; Save original state of callee-saved registers
	push NEXT
	push PREV

	xor PREV, PREV
	mov rbx, [rdi]	; Dereference list head
.loop:
	test rbx, rbx
	jz .restore		; No node

	push rdi		; Save parameters
	push rsi
	push rdx
	push rcx

	mov rdi, [rbx + t_list.data]
	call rdx

	pop rcx			; Restore parameters
	pop rdx
	pop rsi
	pop rdi

	test rax, rax
	jz .remove_node

	mov PREV, rbx
	mov rbx, [rbx + t_list.next]
	jmp .loop
.remove_node:
	mov NEXT, [rbx + t_list.next]
	push rdi		; Save parameters
	push rsi
	push rdx
	push rcx

	test rcx, rcx
	jz .skip_free_function
	mov rdi, [rbx + t_list.data]
	call rcx

.skip_free_function:
	mov rdi, rbx
	call free wrt ..plt

	pop rcx			; Restore parameters
	pop rdx
	pop rsi
	pop rdi

	test PREV, PREV
	jz .update_head

	mov [PREV + t_list.next], NEXT
	mov rbx, NEXT
	jmp .loop
.update_head:
	mov [rdi], NEXT
	mov rbx, NEXT
	jmp .loop
.restore:
	pop PREV
	pop NEXT
	pop rbx
.end:
	ret
