NAME =	minishell

INC = inc

SRCS =	src/main.c \
	src/clean_up.c \
	src/ft_echo.c \
	src/ft_exit.c \
	src/init.c \
	src/error.c \
	src/ft_split_lexer.c \
	src/tests.c \
	src/make_env_arr.c \
	src/check_if_cmd.c \
	src/ft_message.c \
	src/categorize.c \
	src/parser.c \
	src/parser_utils.c \
	src/executer.c
	

OBJS =	$(SRCS:.c=.o)

LIBFTDIR = ./libft/

LIBFT = libft.a

CFLAGS = -Werror -Wextra -g #-Wall 

all: libft_make $(NAME)

libft_make:
	@make -C $(LIBFTDIR)

INCDIR := -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline -lncurses

$(NAME): $(LIBFT) Makefile $(SRCS) ## without OBJS it works $(OBJS)
			@cp $(LIBFTDIR)$(LIBFT) $(LIBFT)
			$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME) $(INCDIR)

$(LIBFT):
			make all -C $(LIBFTDIR)

%.o:%.c $(INC)/minishell.h
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@ -I $(INCDIR) -lreadline

e:	all
	./$(NAME)

l:	all
	leaks --atExit -- ./$(NAME)

clean:
			make clean -C libft
			rm -f $(OBJS)

fclean:	clean
			rm -f $(NAME)
			rm -f $(LIBFT)

re:		fclean all

norm:


leaks:
		make
		leaks --atExit -- ./minishell

.PHONY: all clean fclean re norm leaks		
