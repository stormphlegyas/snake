#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/09 19:35:55 by mmoumini          #+#    #+#              #
#    Updated: 2015/05/19 18:56:27 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY = all, clean, fclean, re

NAME = snake

CC = g++

CFLAGS = -Wall -Wextra -Werror

C_LIB = (cd lib/SDL; make; cd ../ncurses; make; cd ../SFML; make)

CLEAN_LIB = (cd lib/SDL; make clean; cd ../ncurses; make clean; cd ../SFML; make clean)

FCLEAN_LIB = (cd lib/SDL; make fclean; cd ../ncurses; make fclean; cd ../SFML;make fclean)

SRC	=	main.cpp		\
		Game.class.cpp	\
		Snake.class.cpp	\
		element.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)


$(NAME): $(OBJ)
		$(C_LIB)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

.%.o: %.cpp
		$(CC) -o $@ -c $< $(INC) $(CFLAGS)

clean:
		rm -rf $(OBJ)
		 $(CLEAN_LIB)

fclean: clean
		rm -rf $(NAME)
		 $(FCLEAN_LIB)

re: fclean all

.PHONY: all clean re fclean