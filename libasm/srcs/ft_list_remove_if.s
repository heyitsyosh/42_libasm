global ft_list_remove_if

; extern free

%include "structs.inc"

section .text
; C Prototype:
;    void ft_list_remove_if(t_list **head, void *data_ref,
;                           int (*cmp)(), void (*free_fct)(void *));
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
	;
