NAME = libasm.a

SRCS_DIR = srcs
OBJS_DIR = objs
TESTS_DIR = tests

FILES = ft_strlen\
		ft_strcpy\
		ft_strcmp\
		ft_read\
		ft_write\
		ft_strdup\
		ft_atoi_base\
		ft_list_push_front\
		ft_list_size\
		ft_list_sort\
		ft_list_remove_if
TEST_FILES = main

OBJS = $(foreach src, $(FILES), $(OBJS_DIR)/$(src).o)
TEST_OBJS = $(foreach src, $(TEST_FILES), $(OBJS_DIR)/$(src).o)

INCLUDES = -I ./includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror
# -g3 -fsanitize=address

ASMFLAGS = -f elf64

#--------------------------------------------------------------------------#

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(TESTS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.s | $(OBJS_DIR)
	nasm $(ASMFLAGS) $(INCLUDES) $< -o $@

$(NAME): $(OBJS)
	ar rcs $@ $^

test: $(NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(NAME) -o test_exec

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus test clean fclean re
