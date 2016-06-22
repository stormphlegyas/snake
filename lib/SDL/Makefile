#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/09 19:35:55 by mmoumini          #+#    #+#              #
#    Updated: 2015/06/06 17:05:14 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY = all, clean, fclean, re

NAME = sdl.so

CC = g++


CFLAGS = -Wall -Wextra -Werror

LIB_PATH = -L./lib -lSDL2 -framework OpenGL -framework AppKit -framework IOKit -framework CoreServices -framework Carbon -framework OpenAL -framework ForceFeedback

SRC	=	sdl_gesture.cpp	\
		sdl.class.cpp	

OBJ = $(SRC:.cpp=.o)

all: $(NAME)


$(NAME): $(OBJ)
		$(CC) -shared -fPIC -o $(NAME) $(OBJ) $(LIB_PATH) $(CFLAGS)

.%.o: %.cpp
		$(CC) -shared -fPIC -o $@ -c $< $(INC) $(CFLAGS)

clean:
		rm -rf $(OBJ) 

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean