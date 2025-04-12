#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/09 19:35:55 by mmoumini          #+#    #+#              #
#    Updated: 2025/04/12 19:28:52 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

UNAME_S := $(shell uname -s)

ifeq ($(OS),Windows_NT)
    ifneq ($(findstring MINGW,$(UNAME_S)),)
        # MSYS2 / Git Bash 
        RM = rm -f
        RMDIR = rm -rf
        EXT_DLL = .dll
        LIBS_TO_BUILD = SDL SFML
    else
        # PowerShell / CMD
        RM = del /F /Q
        RMDIR = rmdir /S /Q
        EXT_DLL = .dll
        LIBS_TO_BUILD = SDL SFML
    endif
    NAME = snake.exe
    INC = -Iincludes -Ilib/windows/include
    LDFLAGS =
else
    # Linux / macOS
    RM = rm -f
    RMDIR = rm -rf
    NAME = snake
    EXT_DLL = .so
    INC = -Iincludes
    LDFLAGS = -ldl
    LIBS_TO_BUILD = SDL ncurses SFML
endif

C_LIB = $(foreach lib,$(LIBS_TO_BUILD),(cd lib/$(lib) && make);)
CLEAN_LIB = $(foreach lib,$(LIBS_TO_BUILD),(cd lib/$(lib) && make clean);)
FCLEAN_LIB = $(foreach lib,$(LIBS_TO_BUILD),(cd lib/$(lib) && make fclean);)

.PHONY: all clean fclean re

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17

SRC = main.cpp \
      Game.class.cpp \
      Snake.class.cpp \
      element.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)


$(NAME): $(OBJ)
	@$(C_LIB)
ifeq ($(OS),Windows_NT)
	@$(foreach lib,$(LIBS_TO_BUILD),\
		cp lib/$(lib)/$(shell echo $(lib) | tr A-Z a-z)$(EXT_DLL) . 2>/dev/null || true; \
		cp lib/$(lib)/bin/*$(EXT_DLL) . 2>/dev/null || true; \
	)
else
	@$(foreach lib,$(LIBS_TO_BUILD),\
		cp lib/$(lib)/$(shell echo $(lib) | tr A-Z a-z)$(EXT_DLL) . 2>/dev/null || true; \
	)
endif
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(INC)

%.o: %.cpp
	$(CC) -o $@ -c $< $(CFLAGS) $(INC)

clean:
	@echo "Cleaning object files..."
	$(RM) $(OBJ)
	@$(CLEAN_LIB)

fclean: clean
	@echo "Cleaning executable..."
	$(RM) $(NAME)
	@$(RM) *.dll *.so
	@$(FCLEAN_LIB)

re: fclean all
