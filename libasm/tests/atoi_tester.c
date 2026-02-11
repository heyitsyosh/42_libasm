#include "libasm.h"
#include "tester.h"

/* ── test macros ──────────────────────────────────────────────── */

#define TEST_ATOI_BASE(str, base, expected) do { \
	int result = ft_atoi_base((char *)(str), (char *)(base)); \
	if (result != (expected)) \
		printf("%s str=\"%s\" base=\"%s\" Expected: %d, Got: %d\n", \
			FAIL_TAG, str, base, expected, result); \
	else \
		printf("%s str=\"%s\" base=\"%s\" " GRAY "Result: %d" RESET "\n", \
			PASS_TAG, str, base, result); \
} while (0)

/* ── tests ────────────────────────────────────────────────────── */

static void	test_atoi_base_decimal(void)
{
	printf("\n--- ft_atoi_base : decimal ---\n");
	TEST_ATOI_BASE("42",      "0123456789", 42);
	TEST_ATOI_BASE("   42",   "0123456789", 42);
	TEST_ATOI_BASE("   -42",  "0123456789", -42);
	TEST_ATOI_BASE("   +42",  "0123456789", 42);
	TEST_ATOI_BASE("   --42", "0123456789", 42);
	TEST_ATOI_BASE("   ---42","0123456789", -42);
}

static void	test_atoi_base_hex(void)
{
	printf("\n--- ft_atoi_base : hexadecimal ---\n");
	TEST_ATOI_BASE("2A",     "0123456789ABCDEF", 42);
	TEST_ATOI_BASE("ff",     "0123456789abcdef", 255);
	TEST_ATOI_BASE("   -ff", "0123456789abcdef", -255);
}

static void	test_atoi_base_binary(void)
{
	printf("\n--- ft_atoi_base : binary ---\n");
	TEST_ATOI_BASE("101010",  "01", 42);
	TEST_ATOI_BASE("-101010", "01", -42);
}

static void	test_atoi_base_custom(void)
{
	printf("\n--- ft_atoi_base : custom base ---\n");
	TEST_ATOI_BASE("p*00", "0*p", 63);
	TEST_ATOI_BASE("aaaa", "a",    0);
	TEST_ATOI_BASE("abc",  "abca", 0);
}

static void	test_atoi_base_irregular(void)
{
	printf("\n--- ft_atoi_base : edge cases ---\n");
	TEST_ATOI_BASE("1234",  "012",        5);
	TEST_ATOI_BASE("12x34", "0123456789", 12);
	TEST_ATOI_BASE("",    "0123456789", 0);
	TEST_ATOI_BASE("   ", "0123456789", 0);
	TEST_ATOI_BASE("+",   "0123456789", 0);
	TEST_ATOI_BASE("-",   "0123456789", 0);
	TEST_ATOI_BASE("+-42","0123456789", -42);
	TEST_ATOI_BASE("-+42","0123456789", -42);
}

/* ── entry point ──────────────────────────────────────────────── */

void	run_atoi_tests(void)
{
	printf("========================================\n");
	printf("             ATOI TESTS                 \n");
	printf("========================================\n");

	test_atoi_base_decimal();
	test_atoi_base_hex();
	test_atoi_base_binary();
	test_atoi_base_custom();
	test_atoi_base_irregular();

	printf("\n\n");
}
