#include <stdio.h>		//printf
#include <string.h>		//strlen, strcpy, strcmp, strdup
#include <unistd.h>		//read, write, lseek
#include <stdlib.h>		//free
#include <fcntl.h>		//open
#include <sys/types.h>
#include <sys/stat.h>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

typedef struct s_list {
	void *data;
	struct s_list *next;
} t_list;

extern int ft_strlen(const char * str);
extern char *ft_strcpy(char *dest, const char *src);
extern int ft_strcmp(const char * str, const char * cmp);
extern ssize_t ft_write(int fd, const void *buf, size_t count);
extern ssize_t ft_read(int fd, void *buf, size_t count);
extern char *ft_strdup(const char *s);
extern int ft_atoi_base(char *str, char *base);
extern void ft_list_push_front(t_list **head, void *data);
extern int ft_list_size(t_list *head);
extern void ft_list_sort(t_list **head, int (*cmp)());
extern void ft_list_remove_if(t_list **head, void *data_ref, \
							int (*cmp)(), void (*free_fct)(void *));

#define TEST_INT(func, original, input) do { \
	int expected = original(input); \
	int result = func(input); \
	if (expected != result) { \
		printf(RED"[FAIL] %s(\"%s\") -> Expected: %d, Got: %d\n" RESET, #func, input, expected, result); \
	} else { \
		printf(GREEN"[PASS] %s(\"%s\") -> %d\n" RESET, #func, input, result); \
	} \
} while (0)

#define TEST_STR_CMP(func, original, s1, s2) do { \
    int expected = original(s1, s2); \
    int result = func(s1, s2); \
    if (expected != result) { \
        printf(RED"[FAIL] %s(\"%s\", \"%s\") -> Expected: %d, Got: %d\n" RESET, #func, s1, s2, expected, result); \
    } else { \
        printf(GREEN"[PASS] %s(\"%s\", \"%s\") -> %d\n" RESET, #func, s1, s2, result); \
    } \
} while (0)

#define TEST_IO(func, original, fd, size) do { \
    char expected[size], result[size]; \
    lseek(fd, 0, SEEK_SET); \
    ssize_t expected_bytes = original(fd, expected, size); \
    lseek(fd, 0, SEEK_SET); \
    ssize_t result_bytes = func(fd, result, size); \
    if (expected_bytes != result_bytes || memcmp(expected, result, size) != 0) { \
        printf(RED"[FAIL] %s(fd) -> Expected %zd bytes, Got %zd bytes\n" RESET, #func, expected_bytes, result_bytes); \
    } else { \
        printf(GREEN"[PASS] %s(fd) -> %zd bytes read correctly\n" RESET, #func, result_bytes); \
    } \
} while (0)

void run_tests() {
    printf("Running tests...\n");

    // **String functions**
    TEST_INT(ft_strlen, strlen, "hello world");
    TEST_INT(ft_strlen, strlen, "");
    // TEST_STR(ft_strdup, strdup, "example string");

    // **Comparison functions**
    TEST_STR_CMP(ft_strcmp, strcmp, "hello", "hello");
    TEST_STR_CMP(ft_strcmp, strcmp, "abc", "def");
    TEST_STR_CMP(ft_strcmp, strcmp, "test", "testing");
    TEST_STR_CMP(ft_strcmp, strcmp, "", "non-empty");
    TEST_STR_CMP(ft_strcmp, strcmp, "same", "same");

    // **Integer conversion**

    // **File I/O Tests**
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }
    write(fd, "file test", 10);
    TEST_IO(ft_read, read, fd, 10);
    close(fd);
    remove("test.txt");

    printf("Tests completed.\n");
}

int main() {
	run_tests();
	return 0;
}

//test malloc

//test NUll input
//clean up makefile
// movsx
//test speed
// strdupの中でmallocに失敗した際、raxレジスタにはNULLが格納され、
// errnoが設定されると思います。ikedaさんのコードだと、NULL(0x0)をerrnoに上書きしてしまっているようです。errnoの上書きをせずにstrdupの処理を終了させるようにするといいと思います。
// -g3 -fsanitize=address
// atoi_baseの314進数は対応不可なのでYesにしています。
// We tested the mandatory part and it was working as expected, in the bonus part i'm not sure how to make a base 314 so i'm not sure about it result, thank you for being friendly and explaining things to me, good luck !!!

// ft_strcmpでs1とs2が途中まで同じ文字で、s1が先にnullになったときに、return が0になっていて、もともとのstrcmpと挙動が違います。readとwriteがファイルディスクリプタが違うときに異なる挙動をしていました。
// 説明が難しかったと思いましたが、お疲れ様でした。
// シグナルハンドラを使ったsegfault, sig abortの捕捉方法
// stackの16byteルール
// writeの挙動（nbyteがint_maxまで）
// strdup 内の malloc の返り値のチェックは一応つけておいたほうがいいですが、それ以外は完璧だったと思います！