/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 10:54:59 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/12 20:36:33 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Game.class.hpp"
#include "nibbler.hpp"
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <list>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <dlfcn.h>
#endif

// Dynamic library extension depending on OS
#ifdef _WIN32
#define LIB_EXT ".dll"
#else
#define LIB_EXT ".so"
#endif

// Add a new position element to the snake's position list
void add_pos(std::list<t_pos>& pos, dir direction, int x, int y) {
	t_pos newelem = {x, y, direction};
	pos.push_back(newelem);
}

// Update the game event with the current snake and item positions
void update_pos(GameEvent& event, Game* game) {
	event.snakePos.pos.clear();
	event.elem.x = game->item->x;
	event.elem.y = game->item->y;
	for (auto& elem : game->player1->snake)
		add_pos(event.snakePos.pos, elem.direction, elem.x, elem.y);
}

// Open the specified graphics library
void* openlib(const std::string& arg) {
	std::string libname = arg;
	for (auto& c : libname) c = std::tolower(c);

	if (libname != "sdl" && libname != "sfml" && libname != "ncurses") {
		std::cerr << "Unknown library: " << arg << std::endl;
		return nullptr;
	}

	std::string libfile = libname + LIB_EXT;

#ifdef _WIN32
	if (libname == "ncurses") {
		std::cerr << "Error: ncurses is not supported on Windows." << std::endl;
		return nullptr;
	}
	HMODULE handle = LoadLibraryA(libfile.c_str());
	if (!handle) {
		DWORD err = GetLastError();
		std::cerr << "[ERROR] LoadLibraryA failed: code " << err << std::endl;

		LPVOID msgBuf;
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
					   NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					   (LPSTR)&msgBuf, 0, NULL);
		std::cerr << "[ERROR] System message: " << (char*)msgBuf << std::endl;
		LocalFree(msgBuf);
	}
	return (void*)handle;
#else
	void* handle = dlopen(libfile.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!handle) std::cerr << "[ERROR] dlopen: " << dlerror() << std::endl;
	return handle;
#endif
}

// Change the graphics library at runtime
void* ChangeLib(GameEvent& event) {
	event.currentTime = 0;
	event.lastTime = 0;
	std::string lib;

	switch (event.lib) {
		case 1: lib = "sfml"; break;
		case 2: lib = "sdl"; break;
#ifndef _WIN32
		case 3: lib = "ncurses"; break;
#else
		case 3:
			std::cerr << "Cannot switch to ncurses on Windows." << std::endl;
			return nullptr;
#endif
		default: return nullptr;
	}

	lib += LIB_EXT;

#ifdef _WIN32
	return (void*)LoadLibraryA(lib.c_str());
#else
	return dlopen(lib.c_str(), RTLD_LAZY | RTLD_LOCAL);
#endif
}

// Windows-specific functions for dynamic library handling
#ifdef _WIN32
void* win_dlsym(void* handle, const char* symbol) {
	return (void*)GetProcAddress((HMODULE)handle, symbol);
}

int win_dlclose(void* handle) {
	return FreeLibrary((HMODULE)handle) ? 0 : 1;
}
#endif

// Change the game dimensions based on the command line argument
void change_dim(GameEvent& event, char* arg) {
	if (strlen(arg) == 1 && isdigit(arg[0])) {
		int i = atoi(arg);
		if (i >= 1 && i <= 3) {
			event.surface_length = 16 * i;
			event.surface_height = 12 * i;
			return;
		}
	}
	throw std::invalid_argument("Invalid dimension");
}

// Safely attempt to change the game dimensions
void dime_mult(GameEvent& event, char* arg) {
	try {
		change_dim(event, arg);
	} catch (...) {
		std::cout << "Error: invalid size. Choose between 1 and 3." << std::endl;
	}
}

int main(int argc, char** argv) {
	if (argc < 2 || argc > 3) {
		std::cout << "usage : ./snake SDL | SFML [1-3]" << std::endl;
#ifndef _WIN32
		std::cout << "       ./snake ncurses [1-3]" << std::endl;
#endif
		return 0;
	}

	// Initialize game objects
	Game* game = new Game;
	GameEvent event{};
	event.interval = INTERVAL;
	event.firstlaunch = true;
	event.surface_length = 16;
	event.surface_height = 12;

	// Load the graphics library
	void* dl_handle = openlib(argv[1]);
	if (!dl_handle) {
		std::cerr << "Error: unable to load library " << argv[1] << std::endl;
		delete game;
		return 1;
	}

	// Get function pointers from the library
#ifdef _WIN32
	auto init_ptr        = (void(*)(GameEvent&))win_dlsym(dl_handle, "init");
	auto check_event_ptr = (void(*)(GameEvent&))win_dlsym(dl_handle, "check_event");
	auto draw_ptr        = (void(*)(GameEvent&))win_dlsym(dl_handle, "draw");
	auto close_ptr       = (void(*)(void))win_dlsym(dl_handle, "closeWin");
#else
	auto init_ptr        = (void(*)(GameEvent&))dlsym(dl_handle, "init");
	auto check_event_ptr = (void(*)(GameEvent&))dlsym(dl_handle, "check_event");
	auto draw_ptr        = (void(*)(GameEvent&))dlsym(dl_handle, "draw");
	auto close_ptr       = (void(*)(void))dlsym(dl_handle, "closeWin");
#endif

	// Process game size argument if provided
	if (argc == 3)
		dime_mult(event, argv[2]);

	// Initialize the graphics library
	init_ptr(event);
	event.continuer = true;

	// Main game loop
	while (event.continuer) {
		// Process user input
		check_event_ptr(event);

		// Handle direction changes
		if (event.changedir) {
			switch (event.direct) {
				case north: game->key1Up(); break;
				case south: game->key1Down(); break;
				case east:  game->key1Right(); break;
				case west:  game->key1Left(); break;
			}
			event.changedir = false;
		}

		// Update game state and redraw if needed
		if (event.ifmove) {
			event.continuer = game->move(event);
			update_pos(event, game);
			draw_ptr(event);
			event.ifmove = false;
		}

		// Handle library switching
		if (event.changelib) {
			close_ptr();
			dl_handle = ChangeLib(event);
			if (!dl_handle) break;

#ifdef _WIN32
			init_ptr        = (void(*)(GameEvent&))win_dlsym(dl_handle, "init");
			check_event_ptr = (void(*)(GameEvent&))win_dlsym(dl_handle, "check_event");
			draw_ptr        = (void(*)(GameEvent&))win_dlsym(dl_handle, "draw");
			close_ptr       = (void(*)(void))win_dlsym(dl_handle, "closeWin");
#else
			init_ptr        = (void(*)(GameEvent&))dlsym(dl_handle, "init");
			check_event_ptr = (void(*)(GameEvent&))dlsym(dl_handle, "check_event");
			draw_ptr        = (void(*)(GameEvent&))dlsym(dl_handle, "draw");
			close_ptr       = (void(*)(void))dlsym(dl_handle, "closeWin");
#endif
			init_ptr(event);
			event.changelib = false;
			event.lib = 0;
		}
	}

	// Cleanup resources
	close_ptr();
	delete game;

#ifdef _WIN32
	win_dlclose(dl_handle);
#else
	dlclose(dl_handle);
#endif

	return 0;
}