#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/09 19:35:55 by mmoumini          #+#    #+#              #
#    Updated: 2025/04/12 19:35:07 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    ifneq ($(findstring MINGW,$(UNAME_S)),)
        RM = rm -f
        RMDIR = rm -rf
    else
        RM = del /F /Q
        RMDIR = rmdir /S /Q
    endif

    NAME = sdl.dll
    SHARED_FLAG = -shared
    INC = -I./include/windows/
    LIB_PATH = -L./lib/windows ./lib/windows/SDL3.dll \
        -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lversion \
        -luuid -lshell32 -lsetupapi
else
    RM = rm -f
    RMDIR = rm -rf
    NAME = sdl.so
    SHARED_FLAG = -shared -fPIC
    INC = -I./include/macos
    LIB_PATH = -L./lib/macos -lSDL3 \
        -framework OpenGL \
        -framework AppKit \
        -framework IOKit \
        -framework CoreServices \
        -framework Carbon \
        -framework AudioToolbox \
        -framework CoreAudio \
        -framework AVFoundation \
        -framework CoreMedia \
        -framework CoreVideo \
        -framework GameController \
        -framework QuartzCore \
        -framework Metal \
        -framework CoreHaptics \
        -framework UniformTypeIdentifiers \
        -framework ForceFeedback
endif

CC = g++
CFLAGS = -Wall -Wextra -Werror

SRC = sdl_gesture.cpp \
      sdl.class.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	$(CC) $(SHARED_FLAG) -o $(NAME) $(OBJ) $(LIB_PATH) $(INC)

%.o: %.cpp
	@echo "Compiling $<..."
	$(CC) -c $< -o $@ $(CFLAGS) $(INC)

clean:
	@echo "Cleaning object files..."
	$(RM) $(OBJ)

fclean: clean
	@echo "Cleaning executable..."
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re