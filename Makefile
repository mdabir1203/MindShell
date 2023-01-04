# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 10:49:02 by nrenz             #+#    #+#              #
#    Updated: 2023/01/04 19:27:30 by mrehberg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	src/main.c \
	src/clean_up.c \
	src/process_input.c \
	src/ft_echo.c \

OBJS =	$(SRCS:.c=.o)

LIBFTDIR = ./libft/

LIBFT = libft.a

CFLAGS = -Wall -Werror -Wextra

all: libft_make $(NAME)

libft_make:
	@make -C $(LIBFTDIR)

INCDIR := -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

$(NAME):	$(OBJS) $(LIBFT) Makefile
			@cp $(LIBFTDIR)$(LIBFT) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCDIR) -lncurses -o $(NAME) 

$(LIBFT):
			make all -C $(LIBFTDIR)

%.o:%.c $(INC)/minishell.h
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@ -I $(INCDIR) -lreadline

e:	all
	./$(NAME)

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
