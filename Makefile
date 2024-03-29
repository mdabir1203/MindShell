NAME =	minishell

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

LIBFT = libs/libft/libft.a
LIBFTDIR = libs/libft

LIBS = $(LIBFT) -lreadline -lncurses -L$(HOME)/goinfre/.brew/opt/readline/lib/ 
INC = -I libs/libft -I inc -I $(HOME)/goinfre/.brew/opt/readline/include/

SRC_DIR = src
OBJ_DIR = obj

SRCS =	src/main.c \
		src/ft_clean_up.c \
		src/ft_clean_up_utils.c \
		src/ft_echo.c \
		src/ft_exit.c \
		src/ft_env.c \
		src/ft_init.c \
		src/ft_error.c \
		src/ft_split_lexer_utils_2.c \
		src/ft_split_lexer_utils.c \
		src/ft_split_lexer.c \
		src/tests.c \
		src/ft_make_env_arr.c \
		src/ft_check_if_cmd.c \
		src/ft_check_if_cmd_utils.c \
		src/ft_message.c \
		src/ft_categorize.c \
		src/ft_parser.c \
		src/ft_parser_utils_3.c \
		src/ft_parser_utils_2.c \
		src/ft_parser_utils.c \
		src/ft_executer.c \
		src/ft_export.c \
		src/ft_export_sub.c \
		src/ft_export_sub_sub.c \
		src/ft_unset.c \
		src/ft_expand_variables_utils.c \
		src/ft_expand_variables.c \
		src/ft_cd.c \
		src/ft_pwd.c \
		src/ft_clear.c \
		src/ft_redirect_and_pipe_helpers.c \
		src/ft_heredoc.c \
		src/ft_helpers_builtins.c \
		src/ft_helpers_fds.c \
		src/ft_wait_and_exit.c


## Substitutes all the SRC_DIR to SRCS --> A short alternative to $(SRCS)/%.c = $(OBJS)/%.o
## Also used dir which extracts the SRC_DIR compiled objects to obj directory
## might need to look at if we actually need both readline or not
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Producing Objects: $(OBJS)"
	@make -C $(LIBFTDIR) bonus
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "Shell building on Process $<"

re:	fclean all

e: all
	./$(NAME)

l: all
	leaks --atExit -- ./$(NAME)

vg: re
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.ignore_readline.supp ./$(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.ignore_readline -s ./$(NAME)

start: re
	./$(NAME)

clean:
	@make -C $(LIBFTDIR) clean
	@rm -f $(OBJ_DIR)/*.o

fclean:	clean
	@make -C $(LIBFTDIR) fclean
	@rm -f $(NAME)

norm:
	norminette ./src/

.PHONY: all clean fclean re norm leaks
.NOTPARALLEL: all clean fclean re norm leaks vg