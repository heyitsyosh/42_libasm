global ft_list_sort

extern ft_list_size

%define HEAD_PP 8
%define LEFT_NODE 16
%define RIGHT_NODE 24
%define CMP_FUNC 32

%include "structs.inc"

section .text
; C Prototype:
;    void ft_list_sort(t_list **head, int (*cmp)(data1, data2));
;
; Description:
;    Sorts the elements of a linked list in ascending order using 'cmp'.
;
; Parameters:
;    rdi: Double pointer to the first node of the linked list
;    rsi: Pointer to the comparison function
;
; Return value:
;    None.
ft_list_sort:
	test rdi, rdi
	jz .end				; if (!head) return
	test rsi, rsi
	jz .end				; if (!cmp) return
	mov rcx, [rdi]
	test rcx, rcx
	jz .end				; if (!*head) return
	cmp qword [rcx + t_list.next], 0
	jz .end

	enter 32, 0
	mov [rbp - HEAD_PP], rdi
	mov [rbp - CMP_FUNC], rsi
	mov [rbp - LEFT_NODE], rcx ; Save left node

	mov rdi, rcx
	call ft_list_size

	inc eax
	shr eax, 1					; eax = (list_size + 1) / 2

	xor edx, edx				; edx = i
	xor ecx, ecx				; ecx = previous node
	mov r8, [rbp - LEFT_NODE]	; r8 = current node
.loop_to_middle_node:
	cmp edx, eax
	je .unlink_nodes

	mov rcx, r8
	mov r8, [r8 + t_list.next]
	inc edx
	jmp .loop_to_middle_node
.unlink_nodes:
	mov [rbp - RIGHT_NODE], r8			; Save right node
	mov qword [rcx + t_list.next], 0	; Split!

.divide:
	lea rdi, [rbp - LEFT_NODE]
	mov rsi, [rbp - CMP_FUNC]
	call ft_list_sort	; Recursively divide left side

	lea rdi, [rbp - RIGHT_NODE]
	mov rsi, [rbp - CMP_FUNC]
	call ft_list_sort	; Recursively divide right side

; Recursive calls returned. Sublists have been sorted.
	mov rdi, [rbp - LEFT_NODE]
	mov rsi, [rbp - RIGHT_NODE]
	mov rdx, [rbp - CMP_FUNC]
	call merge			; t_list *merge(t_list *left, t_list *right, int *cmp())
.merge_done:
	mov rdi, [rbp - HEAD_PP]
	mov [rdi], rax 		; *head = merged_head

.restore:
	leave
.end:
	ret

; C Prototype:
;    t_list *merge(t_list *left, t_list *right, int *cmp())
;
; Description:
;    Sorts the elements of two linked lists in ascending order using 'cmp'.
;
; Parameters:
;    rdi: Pointer to the first node of the left linked list
;    rsi: Pointer to the first node of the right linked list
;    rdx: Pointer to the comparison function
;
; Return value:
;    Rax: Pointer to the first node of the merge-sorted list.
merge:
	push r12
	push r13
	push r14
	push r15

	mov r12, rdi		; r12 = left
	mov r13, rsi		; r13 = right
	mov r14, rdx		; r14 = cmp

	sub rsp, 8
	mov qword [rsp], 0	; merged_head = NULL
	lea r15, [rsp]		; r15 = tail = pointer to last_node of merged_head (t_list **)

.merge_loop:
	test r12, r12
	jz .merge_right_remainder
	test r13, r13
	jz .merge_left_remainder

	mov rdi, [r12 + t_list.data]
	mov rsi, [r13 + t_list.data]
	call r14			; cmp(left->data, right->data)

	cmp eax, 0
	jg .merge_right_node
.merge_left_node:
	mov [r15], r12					; *tail = left; Add node to end of tail
	lea r15, [r12 + t_list.next]	; tail = &(left->next); Update tail
	mov r12, [r12 + t_list.next]	; left = left->next; Iterate through left list
	jmp .merge_loop
.merge_right_node:
	mov [r15], r13
	lea r15, [r13 + t_list.next]
	mov r13, [r13 + t_list.next]
	jmp .merge_loop
.merge_left_remainder:
	mov [r15], r12
	jmp .merge_done
.merge_right_remainder:
	mov [r15], r13
.merge_done:
	mov rax, [rsp]		; Return merged head

	add rsp, 8
	pop r15
	pop r14
	pop r13
	pop r12
	ret
