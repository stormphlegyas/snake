#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/09 19:35:55 by mmoumini          #+#    #+#              #
#    Updated: 2025/04/12 16:10:50 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    ifneq ($(findstring MINGW,$(UNAME_S)),)
        # MSYS2 (bash sous Windows)
        RM = rm -f
        RMDIR = rm -rf
        NAME = ncurses.dll
        SHARED_FLAG =
        LIB_PATH = -lpdcurses
        INC =
    else
        # CMD / PowerShell
        RM = del /F /Q
        RMDIR = rmdir /S /Q
        NAME = ncurses.dll
        SHARED_FLAG =
        LIB_PATH = -lpdcurses
        INC =
    endif
else
    # Linux/macOS
    RM = rm -f
    RMDIR = rm -rf
    NAME = ncurses.so
    SHARED_FLAG = -shared -fPIC
    LIB_PATH = -lncurses
    INC =
endif

CC = g++
CFLAGS = -Wall -Wextra -Werror

SRC = Ncurses.class.cpp \
      ncurses_gesture.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	$(CC) $(SHARED_FLAG) -o $(NAME) $(OBJ) $(LIB_PATH) $(CFLAGS) $(INC)

%.o: %.cpp
	@echo "Compiling $<..."
	$(CC) -o $@ -c $< $(CFLAGS) $(INC)

clean:
	@echo "Cleaning object files..."
	$(RM) $(OBJ)

fclean: clean
	@echo "Cleaning executable..."
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
