# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/15 14:57:05 by qdequele          #+#    #+#              #
#    Updated: 2017/09/28 15:48:07 by qdequele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#Define the program
NAME		=	libft_malloc_$(HOSTTYPE)
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
OBJ			=	$(SRC:.c=.so)
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-I ./includes/

all: $(NAME) $(INC)

$(NAME):
	@gcc $(CFLAGS) $(SRC) $(INCLUDES) -shared -o $(NAME)
	@ln -sF $(NAME) libft_malloc.so
	@echo $(NAME) " - compiled"

clean:
	@/bin/rm -rf $(OBJ)
	@echo $(NAME) " - Clean all .o files"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo $(NAME) " - Clean executable"

re: fclean all

check: fclean
	@gcc $(CFLAGS) $(SRC) $(TEST) $(INCLUDES)
	@echo $(NAME) and test exec" - compiled and ready to test"
	@./a.out > test.txt ; open test.txt &
