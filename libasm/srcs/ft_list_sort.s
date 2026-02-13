global ft_list_sort

extern ft_list_size

%define LEFT_NODE   0
%define RIGHT_NODE  8

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

	push r12
	mov r12, rsi		; r12 = cmp (callee-saved)

	mov rcx, [rdi]
	push rdi			; Save t_list **head

	test rcx, rcx
	jz .restore
	cmp qword [rcx + t_list.next], 0
	jz .restore

	; Allocate for left, right head pointers. Padding for 16-byte alignment.
	sub rsp 24
	mov [rsp + LEFT_NODE], rcx ; Save left node

	mov rdi, rcx		; Set ft_list_size arg
	call ft_list_size

	inc eax
	shr eax, 1			; eax = (list_size / 2)

	xor edx, edx		; i
	xor ecx, ecx		; previous node
	mov r8, [rsp + LEFT_NODE] ; current node
.loop_to_middle_node:
	cmp edx, eax
	je .unlink_nodes

	mov rcx, r8
	mov r8, [r8 + t_list.next]
	inc edx
	jmp .loop_to_middle_node
.unlink_nodes:
	mov [rsp + RIGHT_NODE], r8 ; Save right node
	mov [rcx + t_list.next], 0 ; Split!

	mov rdi, [rsp + LEFT_NODE]
	mov rsi, r12
	call ft_list_sort	; Recursively divide left side
	mov rdi, [rsp + RIGHT_NODE]
	mov rsi, r12
	call ft_list_sort	; Recursively divide right side
.merge:
	;
restore:
	add rsp, 24
	pop rdi
	pop r12
.end:
	ret
