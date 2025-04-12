# Snake

A classic Snake game implementation that supports multiple rendering backends (SDL, SFML, and ncurses).

## Overview

This Snake game is a versatile implementation that:
- Dynamically loads different graphics libraries at runtime
- Supports switching between libraries during gameplay (using keys 1, 2, 3)
- Grows the snake each time it eats an apple
- Provides different window size options
- Works on macOS and Windows

## Requirements

### macOS
- GCC/Clang compiler with C++17 support
- SFML and/or SDL libraries (for graphical rendering)
- ncurses library (for terminal rendering)

### Windows
- MSYS2 installed
- You must run `pacman -Syu` at least once to update the package database
- MinGW toolchain installed via: `pacman -S mingw-w64-x86_64-toolchain`
- No need to install SDL or SFML as the necessary files (`.dll`, `.dll.a`, headers) are already included in the project

## Building the Game

### macOS
```bash
make clean
make
```

### Windows (MSYS2/MinGW)
```bash
make clean
make
```

The Makefile automatically detects your operating system and configures the build accordingly.

## Running the Game

```bash
# Launch with SDL
./snake sdl [size]

# Launch with SFML
./snake sfml [size]

# Launch with ncurses (not available on Windows)
./snake ncurses [size]
```

Where `[size]` is an optional parameter from 1 to 3 that determines the size of the game window:
- 1: 800 x 600 (default if no size is specified)
- 2: 1600 x 1200
- 3: 2400 x 1800

## Controls

- Arrow keys: Move the snake
- Space: Skip intro (SFML mode)
- W: Toggle wall mode
- 1, 2, 3: Switch between graphics libraries during gameplay
- Esc: Quit the game

## Features

- Dynamic library loading: The game can load different rendering backends at runtime
- Multiple rendering options: Choose between SDL, SFML, or ncurses (terminal-based)
- Resizable window: Choose from three different window sizes
- Real-time library switching: Change the rendering backend without restarting the game
- Classic snake gameplay: The snake grows each time it eats an apple


## Credits

Created by mmoumini
