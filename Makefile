# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: William <wbeuil@student.42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 11:26:47 by William           #+#    #+#              #
#    Updated: 2018/02/20 12:56:25 by William          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	example

CC			=	gcc

RM			=	/bin/rm -f

CFLAGS		=	-Wall -Wextra -Werror

DIR			=	./srcs

INCLUDE		=	./includes

SRCS		=	cli_usage.c sections.c utilities.c \
				split.c content.c init.c \
				options_list.c

OBJS		=	$(addprefix $(DIR)/, ${SRCS:.c=.o})

EX_SRC		=	example.c

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@ $(EX_SRC)
	@echo "\033[1;34mcli_args\t\033[1;33mCompilation\t\t\033[0;32m[OK]\033[0m"

clean:
	@$(RM) $(OBJS)
	@echo "\033[1;34mcli_args\t\033[1;33mCleaning Objects\t\033[0;32m[OK]\033[0m"

fclean:	clean
	@$(RM) $(NAME)
	@echo "\033[1;34mcli_args\t\033[1;33mFull Cleaning\t\t\033[0;32m[OK]\033[0m"

re: fclean all

.PHONY: all clean fclean re