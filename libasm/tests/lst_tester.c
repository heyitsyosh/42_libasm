#include "libasm.h"
#include "tester.h"
#include <stdlib.h> // malloc, free

/* ── helpers ──────────────────────────────────────────────────── */

static t_list	*make_node(void *data, t_list *next)
{
	t_list	*n = malloc(sizeof(t_list));

	if (!n)
		return (NULL);
	n->data = data;
	n->next = next;
	return (n);
}

static void	free_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

static int	lists_equal(t_list *a, t_list *b)
{
	while (a && b)
	{
		if (a->data != b->data)
			return (0);
		a = a->next;
		b = b->next;
	}
	return (a == NULL && b == NULL);
}

static void	print_list(t_list *head)
{
	if (!head)
	{
		printf("(null)\n");
		return ;
	}
	while (head)
	{
		printf("%s", head->data ? (char *)head->data : "(null)");
		head = head->next;
		if (head)
			printf(" -> ");
	}
	printf("\n");
}

static void	check(const char *desc, t_list *input, t_list *result, t_list *expected)
{
	int	ok = lists_equal(result, expected);

	printf("%s %s\n", ok ? PASS_TAG : FAIL_TAG, desc);
	printf(GRAY "input   : ");
	print_list(input);
	printf("result  : ");
	print_list(result);
	if (!ok)
	{
		printf("actual  : ");
		print_list(expected);
	}
	printf(RESET);
}

static void	check_size(const char *desc, t_list *input, int result, int expected)
{
	int	ok = (result == expected);

	printf("%s %s\n", ok ? PASS_TAG : FAIL_TAG, desc);
	printf(GRAY "input   : ");
	print_list(input);
	printf("result  : %d\n", result);
	if (!ok)
		printf("actual  : %d\n", expected);
	printf(RESET);
}

/* ── ft_list_push_front ───────────────────────────────────────── */

static void	test_list_push_front(void)
{
	printf("\n--- ft_list_push_front ---\n");

	/* null guard test */
	ft_list_push_front(NULL, "X");
	printf("%s  null list pointer " GRAY "(no crash)\n" RESET, PASS_TAG);

	t_list	*head = NULL;
	t_list	*input;
	t_list	*expected;

	input = make_node("one", make_node("two", make_node("three", NULL)));
	ft_list_push_front(&head, "one");
	ft_list_push_front(&head, "two");
	ft_list_push_front(&head, "three");
	expected = make_node("three", make_node("two", make_node("one", NULL)));
	check("push three items in order", input, head, expected);
	free_list(head);
	free_list(expected);
	free_list(input);

	/* single push */
	head = NULL;
	input = make_node("one", NULL);
	ft_list_push_front(&head, "one");
	expected = make_node("one", NULL);
	check("push onto empty list", input, head, expected);
	free_list(head);
	free_list(expected);
	free_list(input);

	/* null data is valid */
	head = NULL;
	input = make_node(NULL, NULL);
	ft_list_push_front(&head, NULL);
	expected = make_node(NULL, NULL);
	check("push NULL data", input, head, expected);
	free_list(head);
	free_list(expected);
	free_list(input);
}

/* ── ft_list_size ─────────────────────────────────────────────── */

static void	test_list_size(void)
{
	printf("\n--- ft_list_size ---\n");

	t_list	*list;

	/* null */
	check_size("NULL list", NULL, ft_list_size(NULL), 0);

	/* single node */
	list = make_node("one", NULL);
	check_size("one node", list, ft_list_size(list), 1);
	free_list(list);

	/* three nodes */
	list = make_node("one", make_node("two", make_node("three", NULL)));
	check_size("three nodes", list, ft_list_size(list), 3);
	free_list(list);
}

/* ── ft_list_remove_if ────────────────────────────────────────── */

static int	cmp_str(void *a, void *b)
{
	char *s1 = (char *)a;
	char *s2 = (char *)b;
	
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static void	test_list_remove_if(void)
{
	printf("\n--- ft_list_remove_if ---\n");

	t_list	*head;
	t_list	*input;

	/* null guard */
	ft_list_remove_if(NULL, "x", cmp_str, NULL);
	printf("%s  NULL head pointer (no crash)\n", PASS_TAG);

	/* remove single matching element */
	head = make_node("a", make_node("b", make_node("c", NULL)));
	input = make_node("a", make_node("b", make_node("c", NULL)));
	ft_list_remove_if(&head, "b", cmp_str, NULL);
	t_list *expected = make_node("a", make_node("c", NULL));
	check("remove middle element\ntarget  : \"b\"", input, head, expected);
	free_list(head);
	free_list(expected);
	free_list(input);

	/* remove head */
	head = make_node("a", make_node("b", make_node("c", NULL)));
	input = make_node("a", make_node("b", make_node("c", NULL)));
	ft_list_remove_if(&head, "a", cmp_str, NULL);
	expected = make_node("b", make_node("c", NULL));
	check("remove head element\ntarget  : \"a\"", input, head, expected);
	free_list(head);
	free_list(expected);
	free_list(input);

	/* remove tail */
	head = make_node("a", make_node("b", make_node("c", NULL)));
	input = make_node("a", make_node("b", make_node("c", NULL)));
	ft_list_remove_if(&head, "c", cmp_str, NULL);
	expected = make_node("a", make_node("b", NULL));
	check("remove tail element\ntarget  : \"c\"", input, head, expected);
	free_list(head);
	free_list(expected);
	free_list(input);

	/* remove multiple matches */
	head = make_node("a", make_node("b", make_node("a", make_node("a", NULL))));
	input = make_node("a", make_node("b", make_node("a", make_node("a", NULL))));
	ft_list_remove_if(&head, "a", cmp_str, NULL);
	expected = make_node("b", NULL);
	check("remove multiple matching elements\ntarget  : \"a\"", input, head, expected);
	free_list(head);
	free_list(expected);
	free_list(input);

	/* remove all elements */
	head = make_node("x", make_node("x", make_node("x", NULL)));
	input = make_node("x", make_node("x", make_node("x", NULL)));
	ft_list_remove_if(&head, "x", cmp_str, NULL);
	check("remove all elements\ntarget  : \"x\"", input, head, NULL);
	free_list(input);

	/* no match found */
	head = make_node("a", make_node("b", make_node("c", NULL)));
	input = make_node("a", make_node("b", make_node("c", NULL)));
	ft_list_remove_if(&head, "42", cmp_str, NULL);
	expected = make_node("a", make_node("b", make_node("c", NULL)));
	check("no match found\ntarget  : \"42\"", input, head, expected);
	free_list(head);
	free_list(expected);
	free_list(input);

	/* empty list */
	head = NULL;
	ft_list_remove_if(&head, "x", cmp_str, NULL);
	check("empty list\ntarget  : \"x\"", NULL, head, NULL);
}

/* ── entry point ──────────────────────────────────────────────── */

void	run_lst_tests(void)
{
	printf("========================================\n");
	printf("             LIST TESTS                 \n");
	printf("========================================\n");

	test_list_push_front();
	test_list_size();
	// test_list_sort();
	test_list_remove_if();
}
