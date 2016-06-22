// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/04 10:54:59 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 21:01:24 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "dlfcn.h"
#include "includes/Game.class.hpp"
#include "includes/nibbler.hpp"
#include <fstream>
#include <ostream>
#include <iostream>
#include <unistd.h>

void			add_pos(std::list<t_pos> & pos, dir direction, int x, int y)
{
	t_pos		newelem;

	newelem.x = x;
	newelem.y = y;
	newelem.direction = direction;
	pos.push_back(newelem);
}

void								update_pos(GameEvent & event, Game *game)
{
	std::list<element>::iterator	it;

	event.snakePos.pos.clear();
	event.elem.x = game->item->x;
	event.elem.y = game->item->y;
	for (it = game->player1->snake.begin(); it != game->player1->snake.end(); it++)
		add_pos(event.snakePos.pos, (*it).direction, (*it).x, (*it).y);

}

void					delete_binar( void )
{
	remove("sdl.so");
	remove("ncurses.so");
	remove("sfml.so");
}

void					cpy_sdl_binar( void )
{
	std::ifstream	src("lib/SDL/sdl.so", std::ios::binary);
	std::ofstream	dst("sdl.so", std::ios::binary);
	dst << src.rdbuf();
	src.close();
	dst.close();
}

void					cpy_ncurses_binar( void )
{
	std::ifstream	src("lib/ncurses/ncurses.so", std::ios::binary);
	std::ofstream	dst("ncurses.so", std::ios::binary);
	dst << src.rdbuf();
	src.close();
	dst.close();
}

void					cpy_sfml_binar( void )
{
	std::ifstream	src("lib/SFML/sfml.so", std::ios::binary);
	std::ofstream	dst("sfml.so", std::ios::binary);
	dst << src.rdbuf();
	src.close();
	dst.close();
}

void					*openlib(char *argv)
{
	cpy_sdl_binar();
	cpy_ncurses_binar();
	cpy_sfml_binar();
	if (strcmp("SDL", argv) == 0)
	 	return(dlopen("sdl.so", RTLD_LAZY | RTLD_LOCAL));
	else if (strcmp("ncurses", argv) == 0 || strcmp("NCURSES", argv) == 0)
	 	return(dlopen("ncurses.so", RTLD_LAZY | RTLD_LOCAL));
	else if (strcmp("SFML", argv) == 0 || strcmp("sfml", argv) == 0 )
	 	return(dlopen("sfml.so", RTLD_LAZY | RTLD_LOCAL));
	return(NULL);
}

void					*ChangeLib( GameEvent & event )
{
	event.currentTime = 0;
	event.lastTime = 0;
	event.currentTime = 0;
	event.lastTime = 0;
	switch (event.lib)
	{
	case 1:
	 	return(dlopen("sfml.so", RTLD_LAZY | RTLD_LOCAL));
	case 2 :
	 	return(dlopen("sdl.so", RTLD_LAZY | RTLD_LOCAL));
	case 3 :
	 	return(dlopen("ncurses.so", RTLD_LAZY | RTLD_LOCAL));
	default :
		return (NULL);
	}
}

void					change_dim( GameEvent &event, char *arg )
{
	int					i;

	if (strlen(arg) == 1 && isdigit(arg[0]) && (i = atoi(arg)) > 0 && i < 4)
	{
		event.surface_length = 16 * i;
		event.surface_height = 12 * i;
	}
	else
		throw std::exception();
		
}

void					dime_mult(GameEvent &event, char *arg)
{
	try 
	{
		change_dim(event, arg);
	}
	catch (std::exception &e)
	{
			std::cout << "choose size between 1 and 3" << std::endl;
	}
}

int						main( int argc, char **argv )
{
	void				*dl_handle;
	void				(*init_ptr)( GameEvent& );
	void				(*check_event_ptr)( GameEvent& );
	void				(*draw_ptr)( GameEvent& );
	void				(*close_ptr)( void );
	Game				*game = new Game;
	GameEvent			event;

	event.lastTime = 0;
	event.firstlaunch = true;
	event.currentTime = 0;
	event.lib = 0;
	event.interval = INTERVAL;
	event.changelib = false;
	event.surface_length = 16;
	event.surface_height = 12;
	if( argc < 2 || argc > 3)
	{
		std::cout << "usage : ./snake SDL" << std::endl;
		std::cout << "or : ./snake ncurses" << std::endl;
		std::cout << "or : ./snake SFML" << std::endl;
		std::cout << "and chose your size : 1 => 800 X 600, 2 => 1600 X 1200, 3 => 2400 X 1800" << std::endl;
		return (0);
	}
	else if ((dl_handle = openlib(argv[1])) == NULL)
	{
		std::cout << "can't open : " << argv[1] << std ::endl;
		delete_binar();
		return (0);
	}

	init_ptr = (void(*)( GameEvent& )) dlsym(dl_handle, "init");
	check_event_ptr = (void(*)(GameEvent&)) dlsym(dl_handle, "check_event");
	draw_ptr = (void(*)(GameEvent&)) dlsym(dl_handle, "draw");
	close_ptr = (void(*)(void)) dlsym(dl_handle, "closeWin");
	if (argc == 3)
		dime_mult(event, argv[2]);

	init_ptr(event);
	std::cout << event.surface_height << std::endl;

	event.continuer = true;
	event.changedir = false;
	event.wall = false;
	event.elemvalue = 0;
	std::cout << event.surface_height << std::endl;

	while (event.continuer)
	{
		check_event_ptr(event);
		if (event.changedir == true)
		{
			switch (event.direct)
			{
			case north:
				game->key1Up();
				break;
			case south:
				game->key1Down();
				break;
			case east:
				game->key1Right();
				break;
			case west:
				game->key1Left();
				break;
			}
			event.changedir = false;
		}
		if (event.ifmove)
		{
			event.continuer = game->move( event );
			update_pos(event, game);
			draw_ptr(event);
			event.ifmove = false;
		}
		if ( event.changelib == true )
		{
			close_ptr();
			dl_handle = ChangeLib(event);
			init_ptr = (void(*)( GameEvent& )) dlsym(dl_handle, "init");
			check_event_ptr = (void(*)(GameEvent&)) dlsym(dl_handle, "check_event");
			draw_ptr = (void(*)(GameEvent&)) dlsym(dl_handle, "draw");
			close_ptr = (void(*)(void)) dlsym(dl_handle, "closeWin");
			init_ptr(event);
			event.changelib = false;
			event.lib = 0;
		}
	}
	close_ptr();
	delete_binar();
	return(0);
}
