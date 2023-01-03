# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 10:49:02 by nrenz             #+#    #+#              #
#    Updated: 2023/01/03 15:53:29 by nrenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	minishell

SRCS =	main.c

OBJS =	$(SRCS:.c=.o)

LIBFTDIR = ./libft/

LIBFT = libft.a

CFLAGS = -Wall -Werror -Wextra

all: libft_make $(NAME)

libft_make:
	@make -C $(LIBFTDIR)

INCDIR := -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

$(NAME):	$(OBJS) $(LIBFT)
			@cp $(LIBFTDIR)$(LIBFT) $(LIBFT)
			gcc $(CFLAGS) $(OBJS) $(INCDIR) -lncurses -o $(NAME) 
			
$(LIBFT):
			make all -C $(LIBFTDIR)

clean:
			make clean -C libft
			rm -f $(OBJS)

fclean:	clean
			make clean -C libft
			rm -f $(NAME)
			rm -f $(LIBFT)

re:		fclean all

norm:
		

leaks:
		make
		leaks --atExit -- ./minishell

.PHONY: all clean fclean re norm leaks
