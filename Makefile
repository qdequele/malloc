# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/15 14:57:05 by qdequele          #+#    #+#              #
#    Updated: 2017/10/24 15:33:12 by qdequele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#Define the program
NAME		=	libft_malloc_$(HOSTTYPE).so
LINKNAME	=	libft_malloc.so
EXEC		=	a.out
_SRC		=	free.c\
				interface.c\
				malloc.c\
				math.c\
				print.c\
				printhex.c\
				realloc.c\
				show.c\
				test.c\
				tools.c

_TEST		=	main.c

_INC		=	malloc.h

INC			=	$(addprefix includes/,$(_INC))
SRC			=	$(addprefix srcs/,$(_SRC))
TEST		=	$(addprefix test/,$(_TEST))

OBJ			=	$(SRC:.c=.o)

CFLAGS		=	-Wall -Wextra -Werror -fPIC -O3
INCLUDES	=	-I ./includes/

%.o: %.c
	@echo -n .
	@$gcc $(CFLAGS) -c $< -o $@ $(INCLUDES)

all: $(NAME) $(INC)

$(NAME): $(OBJ)
	@gcc $(CFLAGS) $(OBJ) -shared -o $(NAME)
	@ln -sF $(NAME) $(LINKNAME)
	@echo $(NAME) " - compiled"

clean:
	@/bin/rm -rf $(OBJ)
	@echo $(NAME) " - Clean all .o files"

fclean: clean
	@/bin/rm -rf *.so
	@echo $(NAME) " - Clean executable"

re: fclean all

test: $(NAME)
	@gcc $(NAME) $(TEST)
	@echo $(NAME) and test exec" - compiled and ready to test"
	@sh run.sh
	@./a.out

correct: re
	@echo "- Test 0"
	@gcc test/test0.c 2>&-
	@./run.sh /usr/bin/time -l ./a.out 2>&1 | grep "page reclaims"
	@echo "- Test 1"
	@gcc test/test1.c 2>&-
	@./run.sh /usr/bin/time -l ./a.out 2>&1 | grep "page reclaims"
	@echo "- Test 2"
	@gcc test/test2.c 2>&-
	@./run.sh /usr/bin/time -l ./a.out 2>&1 | grep "page reclaims"
	@echo "- Test 3"
	@gcc test/test3.c 2>&-
	@./run.sh ./a.out
	@echo "- Test 3.2"
	@gcc test/test3.2.c 2>&-
	@./run.sh ./a.out
	@echo "- Test 4"
	@gcc test/test4.c 2>&-
	@./run.sh ./a.out
	@echo "- Test 5"
	@gcc test/test5.c libft_malloc.so 2>&-
	@./run.sh ./a.out
	@rm a.out

.PHONY: all, clean, fclean, re
