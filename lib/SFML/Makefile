#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/12 13:41:19 by mmoumini          #+#    #+#              #
#    Updated: 2025/04/12 19:11:18 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifeq ($(OS),Windows_NT)
    RM = rm -f
    RMDIR = rm -rf
    NAME = sfml.dll
    SHARED_FLAG = -shared
    INC = -I./includes/windows
    LIB_PATH = -L./lib/windows \
        -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
        -lopengl32 -lwinmm -lgdi32
else
    RM = rm -f
    RMDIR = rm -rf
    NAME = sfml.so
    SHARED_FLAG = -shared -fPIC
    INC = -I./includes/macos
    LIB_PATH = -L./lib/macos \
        -lFLAC -lsfml-graphics -lvorbis -lfreetype -lsfml-network -lvorbisenc \
        -logg -lsfml-system -lvorbisfile -lsfml-audio -lsfml-window \
        -framework OpenGL -framework AppKit -framework IOKit \
        -framework CoreServices -framework Carbon -framework OpenAL
endif

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17

SRC = sfml_gesture.cpp \
      Timer.cpp \
      Sfml.class.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	$(CC) $(SHARED_FLAG) -o $(NAME) $(OBJ) $(LIB_PATH) $(INC)

%.o: %.cpp
	@echo "Compiling $<..."
	$(CC) -o $@ -c $< $(CFLAGS) $(INC)

clean:
	@echo "Cleaning object files..."
	$(RM) $(OBJ)

fclean: clean
	@echo "Cleaning shared lib..."
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
