# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjones <sjones@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/13 14:13:42 by sjones            #+#    #+#              #
#    Updated: 2018/02/16 16:58:36 by sjones           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm

SRCPATH = src/

OBJPATH = obj/

SRCFILE = main.cpp \
		  Lexer.cpp \
		  OperandFactory.cpp \
		  Parser.cpp \
		  Tokens.cpp

SRC = $(addprefix $(SRCPATH),$(SRCFILE))

OBJFILE = $(SRCFILE:.cpp=.o)

OBJ = $(addprefix $(OBJPATH),$(OBJFILE))

INCLUDES = -I $(SRCPATH)

LEX = tokens.l

TOK = $(LEX:%.l=$(SRCPATH)%.cpp)

CC = clang++

CFLAGS = -std=c++11 -Wextra -Werror -Wall -Wno-deprecated-register

all: $(NAME)

$(NAME): $(TOK) $(OBJ)
	$(CC) $(OBJ) -o $@

$(SRCPATH)%.cpp: $(SRCPATH)%.l
	flex -o $(SRCPATH)Tokens.cpp $(SRCPATH)$(LEX)

$(OBJPATH)%.o: $(SRCPATH)%.cpp
	@mkdir -p $(OBJPATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJPATH)

fclean: clean
	rm -rf $(NAME)

proper: all clean

re: fclean all

.PHONY: all re clean fclean proper
