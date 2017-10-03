# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/15 14:57:05 by qdequele          #+#    #+#              #
#    Updated: 2017/10/03 15:44:26 by qdequele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#Define the program
NAME		=	libft_malloc_$(HOSTTYPE)
LINKNAME	=	libft_malloc.so
EXEC		=	a.out
_SRC		=	free.c\
				malloc.c\
				math.c\
				realloc.c\
				show.c\
				tools.c

_TEST		=	main.c

_INC		=	malloc.h

INC			=	$(addprefix includes/,$(_INC))
SRC			=	$(addprefix srcs/,$(_SRC))
TEST		=	$(addprefix test/,$(_TEST))

OBJ			=	$(SRC:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -fPIC -O3
INCLUDES	=	-I ./includes/
LIB			=	./libft/libft.a -I ./libft/ -Llibft -lft

%.o: %.c
	@echo -n .
	@$gcc $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME) $(INC)

lib: 
	@make -C libft

$(NAME): lib $(OBJ)
	@gcc $(CFLAGS) $(OBJ) $(LIB) -shared -o $(NAME)
	@ln -sF $(NAME) $(LINKNAME)
	@echo $(NAME) " - compiled"

clean:
	@make clean -C libft
	@/bin/rm -rf $(OBJ)
	@echo $(NAME) " - Clean all .o files"

fclean: clean
	@make fclean -C libft
	@/bin/rm -rf $(NAME)
	@echo $(NAME) " - Clean executable"

re: fclean all

test: $(NAME)
	@gcc $(NAME) $(TEST)
	@echo $(NAME) and test exec" - compiled and ready to test"
	@./a.out > test/test.txt

.PHONY: all, clean, fclean, re
