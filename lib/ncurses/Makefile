#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/09 19:35:55 by mmoumini          #+#    #+#              #
#    Updated: 2015/05/08 10:07:24 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY = all, clean, fclean, re

NAME = ncurses.so

CC = g++

CFLAGS = -Wall -Wextra -Werror -lncurses

SRC	=	Ncurses.class.cpp		\
		ncurses_gesture.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)


$(NAME): $(OBJ)
		$(CC) -shared -fPIC -o $(NAME) $(OBJ) $(CFLAGS)

.%.o: %.cpp
		$(CC) -shared -fPIC -o $@ -c $< $(INC) $(CFLAGS)

clean:
		rm -rf $(OBJ) 

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean