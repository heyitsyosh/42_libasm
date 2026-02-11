#include "libasm.h"
#include "tester.h"
#include <string.h>		// strlen, strcpy, strcmp, strdup, memcmp
#include <unistd.h>		// read, write, lseek, close
#include <stdlib.h>		// free
#include <fcntl.h>		// open, O_RDWR, O_CREAT, O_TRUNC
#include <sys/types.h>	// ssize_t
#include <sys/stat.h>	// O_CREAT, 0644 (mode flags)
#include <errno.h>		// errno

/* ── test macros ──────────────────────────────────────────────── */

#define TEST_INT(func, original, input) do { \
	int expected = original(input); \
	int result = func(input); \
	if (expected != result) \
		printf("%s (\"%s\") Expected: %d, Got: %d\n", FAIL_TAG, input, expected, result); \
	else \
		printf("%s (\"%s\") " GRAY "Result: %d" RESET "\n", \
			PASS_TAG, input, result); \
} while (0)

#define TEST_STRCPY(func, original, src) do { \
	char expected[100]; \
	char result[100]; \
	original(expected, src); \
	func(result, src); \
	if (strcmp(expected, result) != 0) \
		printf("%s (\"%s\") Expected: \"%s\", Got: \"%s\"\n", FAIL_TAG, src, expected, result); \
	else \
		printf("%s (\"%s\") " GRAY "Result: \"%s\"" RESET "\n", \
			PASS_TAG, src, result); \
} while (0)

#define TEST_STR(func, original, input) do { \
	char *expected = original(input); \
	char *result = func(input); \
	if (!expected || !result || strcmp(expected, result) != 0) \
		printf("%s (\"%s\") Expected: \"%s\", Got: \"%s\"\n", \
			FAIL_TAG, input, \
			expected ? expected : "(null)", \
			result ? result : "(null)"); \
	else \
		printf("%s (\"%s\") " GRAY "Result: \"%s\"" RESET "\n", \
			PASS_TAG, input, result); \
	free(expected); \
	free(result); \
} while (0)

#define TEST_STR_CMP(func, original, s1, s2) do { \
	int expected = original(s1, s2); \
	int result = func(s1, s2); \
	if ((expected > 0 && result <= 0) || \
		(expected < 0 && result >= 0) || \
		(expected == 0 && result != 0)) \
		printf("%s (\"%s\", \"%s\") Expected: %d, Got: %d\n", \
			FAIL_TAG, s1, s2, expected, result); \
	else \
		printf("%s (\"%s\", \"%s\") " GRAY "Result: %d" RESET "\n", \
			PASS_TAG, s1, s2, result); \
} while (0)

#define TEST_IO_READ(func, original, fd, size) do { \
	char expected[size], result[size]; \
	lseek(fd, 0, SEEK_SET); \
	ssize_t expected_bytes = original(fd, expected, size); \
	int expected_errno = errno; \
	lseek(fd, 0, SEEK_SET); \
	ssize_t result_bytes = func(fd, result, size); \
	int result_errno = errno; \
	if ((expected_bytes != result_bytes) || \
		(expected_bytes > 0 && memcmp(expected, result, size) != 0)) \
		printf("%s (fd) Expected %zd bytes, Got %zd bytes\n", \
			FAIL_TAG, expected_bytes, result_bytes); \
	else if (expected_errno != result_errno) \
		printf("%s (fd) Expected errno %d, Got errno %d\n", \
			FAIL_TAG, expected_errno, result_errno); \
	else \
		printf("%s (fd) " GRAY "Result: %zd bytes" RESET "\n", \
			PASS_TAG, result_bytes); \
} while (0)

#define TEST_IO_WRITE(func, original, fd, text, size) do { \
	lseek(fd, 0, SEEK_SET); \
	ssize_t expected_bytes = original(fd, text, size); \
	lseek(fd, 0, SEEK_SET); \
	ssize_t result_bytes = func(fd, text, size); \
	if (expected_bytes != result_bytes) \
		printf("%s %s(fd) Expected %zd bytes, Got %zd bytes\n", \
			FAIL_TAG, #func, expected_bytes, result_bytes); \
	else \
		printf("%s %s(fd) " GRAY "Result: %zd bytes" RESET "\n", \
			PASS_TAG, #func, result_bytes); \
} while (0)

/* ── tests ────────────────────────────────────────────────────── */

static void	test_strlen(void)
{
	printf("\n--- ft_strlen ---\n");
	TEST_INT(ft_strlen, strlen, "hello world");
	TEST_INT(ft_strlen, strlen, "");
	TEST_INT(ft_strlen, strlen, "a");
	TEST_INT(ft_strlen, strlen, "1234567890");
}

static void	test_strcpy(void)
{
	printf("\n--- ft_strcpy ---\n");
	TEST_STRCPY(ft_strcpy, strcpy, "hello world");
	TEST_STRCPY(ft_strcpy, strcpy, "");
	TEST_STRCPY(ft_strcpy, strcpy, "1234567890");
	TEST_STRCPY(ft_strcpy, strcpy, "special!@#$%^&*()_+");
}

static void	test_strcmp(void)
{
	printf("\n--- ft_strcmp ---\n");
	TEST_STR_CMP(ft_strcmp, strcmp, "abc", "abc");
	TEST_STR_CMP(ft_strcmp, strcmp, "abc", "abd");
	TEST_STR_CMP(ft_strcmp, strcmp, "abc", "ab");
	TEST_STR_CMP(ft_strcmp, strcmp, "", "nonempty");
	TEST_STR_CMP(ft_strcmp, strcmp, "nonempty", "");
}

static void	test_read(void)
{
	printf("\n--- ft_read ---\n");
	int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"));
	write(fd, "testing123", 10);
	TEST_IO_READ(ft_read, read, fd, 10);
	TEST_IO_READ(ft_read, read, fd + 3, 10);
	close(fd);
	remove("testfile.txt");
}

static void	test_write(void)
{
	printf("\n--- ft_write ---\n");
	int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"));
	TEST_IO_WRITE(ft_write, write, fd, "testing123", 10);
	TEST_IO_WRITE(ft_write, write, fd + 3, "testing123", 10);
	close(fd);
	remove("testfile.txt");
}

static void	test_strdup(void)
{
	printf("\n--- ft_strdup ---\n");
	TEST_STR(ft_strdup, strdup, "duplicate me!");
	TEST_STR(ft_strdup, strdup, "");
	TEST_STR(ft_strdup, strdup, "1234567890");
}

/* ── entry point ──────────────────────────────────────────────── */

void	run_stdlib_tests(void)
{
	printf("========================================\n");
	printf("           STDLIB TESTS                 \n");
	printf("========================================\n");

	test_strlen();
	test_strcpy();
	test_strcmp();
	test_read();
	test_write();
	test_strdup();

	printf("\n\n");
}
