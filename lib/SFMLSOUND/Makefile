#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/12 13:41:19 by mmoumini          #+#    #+#              #
#    Updated: 2015/06/07 21:33:11 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY = all, clean, fclean, re

NAME = music.so

CC = g++

CFLAGS = -Wall -Wextra -Werror

C_LIB = (cd ../SFML/lib; make)

CLEAN_LIB = (cd ../SFML/lib; make clean)

FCLEAN_LIB = (cd ../SFML/lib; make fclean)

LIB_PATH = -L../SFML/lib -ljpeg -lfreetype -logg -lvorbis -lvorbisenc -lvorbisfile -lFLAC-static -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -framework OpenGL -framework AppKit -framework IOKit -framework CoreServices -framework Carbon -framework OpenAL

INC = -I./include

SRC	=	sfml_gesture.cpp		\
		Timer.cpp				\
		Sfml.class.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(C_LIB)
		$(CC) -shared -fPIC -o $(NAME) $(OBJ) $(LIB_PATH) $(CFLAGS) $(INC)

.%.o: %.cpp
	$(CC) -o $@ -c $< $(INC) $(CFLAGS)

clean:
		rm -rf $(OBJ)
		$(CLEAN_LIB)

fclean: clean
		$(FCLEAN_LIB)
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean