#include <stdio.h>		// printf
#include <string.h>		// strlen, strcpy, strcmp, strdup, memcmp
#include <unistd.h>		// read, write, lseek
#include <stdlib.h>		// free, atoi
#include <fcntl.h>		// open
#include <sys/types.h>	// ssize_t
#include <sys/stat.h>	// stat
#include <errno.h>		// errno

#define BLUE   "\033[34m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

typedef struct s_list {
	void *data;
	struct s_list *next;
} t_list;

extern int ft_strlen(const char *str);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char *s1, const char *s2);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *s);

#define TEST_INT(func, original, input) do { \
	int expected = original(input); \
	int result = func(input); \
	if (expected != result) { \
		printf(RED"[FAIL] (\"%s\") -> Expected: %d, Got: %d\n" RESET, input, expected, result); \
	} else { \
		printf(GREEN"[PASS] (\"%s\") -> %d\n" RESET,  input, result); \
	} \
} while (0)

#define TEST_STRCPY(func, original, src) do { \
	char expected[100]; \
	char result[100]; \
	original(expected, src); \
	func(result, src); \
	if (strcmp(expected, result) != 0) { \
		printf(RED"[FAIL] (\"%s\") -> Expected: \"%s\", Got: \"%s\"\n" RESET, src, expected, result); \
	} else { \
		printf(GREEN"[PASS] (\"%s\") -> \"%s\"\n" RESET, src, result); \
	} \
} while (0)

#define TEST_STR(func, original, input) do { \
	char *expected = original(input); \
	char *result = func(input); \
	if (!expected || !result || strcmp(expected, result) != 0) { \
	printf(RED"[FAIL] (\"%s\") -> Expected: \"%s\", Got: \"%s\"" RESET, input, expected ? expected : "(null)", result ? result : "(null)"); \
	} else { \
		printf(GREEN"[PASS] (\"%s\") -> \"%s\"\n" RESET, input, result); \
	} \
	free(expected); \
	free(result); \
} while (0)

#define TEST_STR_CMP(func, original, s1, s2) do { \
	int expected = original(s1, s2); \
	int result = func(s1, s2); \
	if ((expected > 0 && result <= 0) || (expected < 0 && result >= 0) || (expected == 0 && result != 0)) { \
		printf(RED"[FAIL] (\"%s\", \"%s\") -> Expected: %d, Got: %d\n" RESET, s1, s2, expected, result); \
	} else { \
		printf(GREEN"[PASS] (\"%s\", \"%s\") -> %d\n" RESET, s1, s2, result); \
	} \
} while (0)

#define TEST_IO_READ(func, original, fd, size) do { \
	char expected[size], result[size]; \
	lseek(fd, 0, SEEK_SET); \
	ssize_t expected_bytes = original(fd, expected, size); \
	int expected_errno = errno; \
	lseek(fd, 0, SEEK_SET); \
	ssize_t result_bytes = func(fd, result, size); \
	int result_errno = errno; \
	if ((expected_bytes != result_bytes) || (expected_bytes > 0 && memcmp(expected, result, size) != 0)) { \
		printf(RED"[FAIL] (fd) -> Expected %zd bytes, Got %zd bytes\n" RESET, expected_bytes, result_bytes); \
	} else if (expected_errno != result_errno) { \
		printf(RED"[FAIL] (fd) -> Expected %d errno, Got %d errno\n" RESET, expected_errno, result_errno); \
	} else { \
		printf(GREEN"[PASS] (fd) -> %zd\n" RESET, result_bytes); \
	} \
} while (0)

#define TEST_IO_WRITE(func, original, fd, text, size) do { \
	lseek(fd, 0, SEEK_SET); \
	ssize_t expected_bytes = original(fd, text, size); \
	lseek(fd, 0, SEEK_SET); \
	ssize_t result_bytes = func(fd, text, size); \
	if (expected_bytes != result_bytes) { \
		printf(RED"[FAIL] %s(fd) -> Expected %zd bytes written, Got %zd bytes\n" RESET, #func, expected_bytes, result_bytes); \
	} else { \
		printf(GREEN"[PASS] %s(fd) -> %zd\n" RESET, #func, result_bytes); \
	} \
} while (0)

// Helper functions

int simple_cmp(void *a, void *b) {
	return strcmp((char *)a, (char *)b);
}

// Tests

void run_tests() {
	printf("Running tests...\n");

	printf(BLUE"FORMAT: (expected) -> actual\n"RESET);
	
	// 1. Strlen
	printf("\n[STRLEN]\n");
	TEST_INT(ft_strlen, strlen, "hello world");
	TEST_INT(ft_strlen, strlen, "");

	// 2. Strcpy
	printf("\n[STRCPY]\n");
	TEST_STRCPY(ft_strcpy, strcpy, "hello world");
	TEST_STRCPY(ft_strcpy, strcpy, "");
	TEST_STRCPY(ft_strcpy, strcpy, "1234567890");
	TEST_STRCPY(ft_strcpy, strcpy, "special!@#$%^&*()_+");

	// 3. Strcmp
	printf("\n[STRCMP]\n");
	TEST_STR_CMP(ft_strcmp, strcmp, "abc", "abc");
	TEST_STR_CMP(ft_strcmp, strcmp, "abc", "abd");
	TEST_STR_CMP(ft_strcmp, strcmp, "abc", "ab");
	TEST_STR_CMP(ft_strcmp, strcmp, "", "nonempty");
	TEST_STR_CMP(ft_strcmp, strcmp, "nonempty", "");

	// 3. Write, Read
	int fd = open("testfile.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0) {
		perror("open");
		return;
	}
	write(fd, "testing123", 10);


	printf("\n[READ]\n");
	TEST_IO_READ(ft_read, read, fd, 10);
	TEST_IO_READ(ft_read, read, fd + 3, 10);

	lseek(fd, 0, SEEK_SET);
	
	printf("\n[WRITE]\n");
	TEST_IO_WRITE(ft_write, write, fd, "testing123", 10);
	TEST_IO_WRITE(ft_write, write, fd + 3, "testing123", 10);

	close(fd);
	remove("testfile.txt");

	// Strdup
	printf("\n[STRDUP]\n");
	TEST_STR(ft_strdup, strdup, "duplicate me!");
	TEST_STR(ft_strdup, strdup, "");

	printf("\nTests completed.\n");
}

int main() {
	run_tests();
	return 0;
}
