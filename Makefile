# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrehberg <maxrehberg@posteo.de>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 10:49:02 by nrenz             #+#    #+#              #
#    Updated: 2023/01/04 16:54:24 by mrehberg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	main.c

OBJS =	$(SRCS:.c=.o)

LIBFTDIR = ./libft/

LIBFT = libft.a

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

libft_make:
	@make -C $(LIBFTDIR)

INCDIR := -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) $(INCDIR) -lncurses -o $(NAME)
			
e:	all
	./$(NAME)

clean:
			rm -f $(OBJS)

fclean:	clean
			rm -f $(NAME)
			rm -f *.out
#make fclean -C $(LIBFTDIR)

re:		fclean all

norm:
		

leaks:
		make
		leaks --atExit -- ./minishell

.PHONY: all clean fclean re norm leaks
