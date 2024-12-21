#include <stdio.h>

extern int ft_strlen(const char * str);
extern int ft_strcmp(const char * str, const char * cmp);
// extern int ft_strlen(int); //abi

int c_strlen(char * str) {
    int len = 0;
	while (str[len])
		len++;
	return len;
}

int c_strcmp(char *str1, char *str2) {
    int len = 0;
	while (str1[len]) {
        char delta = str1[len] - str2[len];
        if (delta != 0) {
            return delta;
        }
		len++;
    }
    return 0;
}

void test_strlen() {
    char *str = "hello";
    int from_c = c_strlen(str);
    int from_asm = ft_strlen(str);
    printf("C strlen: %d, ASM strlen: %d\n", from_c, from_asm);
}

void test_strcmp() {
   char *str = "yoshi";
   char *cmp = "yokshi";
   int from_c = c_strcmp(str, cmp);
   int from_asm = ft_strcmp(str, cmp);
    printf("C strcmp: %d, ASM strlen: %d\n", from_c, from_asm);
}

int main() {
    printf("Running tests\n");
    printf("Running strlen\n");
    test_strlen();
    test_strcmp();
	return 0;
}
