NAME        = libasm.a
TEST        = libasm-tester

SRCS_DIR    = srcs
TESTS_DIR   = tests
OBJS_DIR    = objs

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
NASM        = nasm
NASMFLAGS   = -f elf64
INCLUDES    = -I ./includes/

SRCS =	ft_strlen\
		ft_strcpy\
		ft_strcmp\
		ft_read\
		ft_write\
		ft_strdup\
		ft_atoi_base\
		ft_list_push_front\
		ft_list_size
# 		ft_list_sort\
# 		ft_list_remove_if

TEST_SRCS = tester stdlib_tester atoi_tester lst_tester

OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o,$(SRCS)))
TEST_OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o,$(TEST_SRCS)))

# ----------------- Formatting ------------------

OK     = \033[32m✓\033[0m
DEL    = \033[31m✗\033[0m

# ------------------- Rules --------------------
all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.s | $(OBJS_DIR)
	@$(NASM) $(NASMFLAGS) $(INCLUDES) $< -o $@
	@echo "$(OK) nasm  $<"

$(OBJS_DIR)/%.o: $(TESTS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(OK) $(CC)   $<"

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(OK) ar    $(NAME)"

bonus: all

test: $(TEST)

$(TEST): $(NAME) $(TEST_OBJS)
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(NAME) -o $(TEST)
	@echo "$(OK) $(CC)   $(TEST)"

clean:
	@$(RM) -r $(OBJS_DIR)
	@echo "$(DEL) $(RM) $(OBJS_DIR) deleted"

fclean: clean
	@$(RM) $(NAME) $(TEST)
	@echo "$(DEL) $(RM) $(NAME) deleted"
	@echo "$(DEL) $(RM) tests deleted"

re: fclean all

.PHONY: all bonus test clean fclean re
