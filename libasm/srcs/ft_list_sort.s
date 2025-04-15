global ft_list_sort

%include "structs.inc"

section .text
; C Prototype:
;    void ft_list_sort(t_list **head, int (*cmp)());
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
	;
