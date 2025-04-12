/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.class.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/09 18:51:20 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/12 09:49:42 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "sdl.class.hpp"

Sdl_class::Sdl_class( void ) {
}


Sdl_class::Sdl_class( Sdl_class const &src ){
    *this = src;
}

Sdl_class::~Sdl_class( void ){
	std::list<SDL_Texture*>::iterator		it;

	SDL_DestroyRenderer(this->pRenderer);
	for (it = this->pTexture.begin() ; it != this->pTexture.end(); it++)
		SDL_DestroyTexture(*it);
	SDL_DestroyWindow(this->screen);
	this->file.clear();
	this->pTexture.clear();
	this->snk_body.clear();
	SDL_Quit();
}

int				Sdl_class::init( GameEvent & event ){
//	Uint32 rmask, gmask, bmask, amask;

	std::list<SDL_IOStream*>::iterator		itrw;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cerr << "Erreur d'initialisation de la SDL : \n";
			std::cerr << "Erreur d'initialisation de la SDL : "; 
		std::cerr << SDL_GetError() << std::endl;
		SDL_Quit();
		return (0);
	}
/*
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif*/
	this->back = SDL_CreateSurface(SDL_CASE * event.surface_length,
                               SDL_CASE * event.surface_height,
                               SDL_PIXELFORMAT_ARGB8888);
	this->screen = SDL_CreateWindow("Snake", SDL_CASE * event.surface_length,
                                SDL_CASE * event.surface_height,
                                SDL_WINDOW_OPENGL); 
	this->back = SDL_CreateSurface(SDL_CASE * event.surface_length,
		SDL_CASE * event.surface_height,
		SDL_PIXELFORMAT_ARGB8888);
	this->pRenderer = SDL_CreateRenderer(this->screen, NULL);
	this->backTex = SDL_CreateTextureFromSurface(this->pRenderer, this->back);
	this->file.push_back(SDL_IOFromFile("./src/sprite/head_right.bmp", "rb"));
	this->file.push_back(SDL_IOFromFile("./src/sprite/head_up.bmp", "rb"));
	this->file.push_back(SDL_IOFromFile("./src/sprite/head_down.bmp", "rb")); 
	this->file.push_back(SDL_IOFromFile("./src/sprite/head_left.bmp", "rb"));

	this->file.push_back(SDL_IOFromFile("./src/sprite/tails_right.bmp", "rb"));	
	this->file.push_back(SDL_IOFromFile("./src/sprite/tails_up.bmp", "rb"));	
	this->file.push_back(SDL_IOFromFile("./src/sprite/tails_down.bmp", "rb"));  
	this->file.push_back(SDL_IOFromFile("./src/sprite/tails_left.bmp", "rb"));

	this->file.push_back(SDL_IOFromFile("./src/fox.bmp", "rb"));

	this->file.push_back(SDL_IOFromFile("./src/sprite/body_vert.bmp", "rb"));
	this->file.push_back(SDL_IOFromFile("./src/sprite/body_hori.bmp", "rb"));

	this->file.push_back(SDL_IOFromFile("./src/sprite/right_down.bmp", "rb"));  
	this->file.push_back(SDL_IOFromFile("./src/sprite/right_up.bmp", "rb"));	
	this->file.push_back(SDL_IOFromFile("./src/sprite/left_up.bmp", "rb"));	
	this->file.push_back(SDL_IOFromFile("./src/sprite/left_down.bmp", "rb"));
	for (itrw = this->file.begin() ; itrw != this->file.end(); itrw++)
	{
		this->snk = SDL_LoadBMP_IO(*itrw, true);
		SDL_SetSurfaceColorKey(
			this->snk,
			true,
			SDL_MapRGB(
				SDL_GetPixelFormatDetails(this->snk->format),
				nullptr,
				0, 0, 255
			)
		);
		this->snk_body.push_back(this->snk);
		this->pTexture.push_back(SDL_CreateTextureFromSurface(pRenderer, this->snk));
	}
	this->itbdy = this->pTexture.begin();
	std::advance( this->itbdy, 4 );
	this->itbdy2 = this->itbdy;
	std::advance( this->itbdy2, 5 );
	this->ititem = this->pTexture.begin();
	this->newposition.h = SDL_CASE;
	this->newposition.w = SDL_CASE;
	std::advance( this->ititem, 8 );
	if ( this->screen == NULL)
		std::cout << "Impossible de charger le mode vidéo\n";
	return (1);
}

void					Sdl_class::draw_head( GameEvent & event ){

	std::list<t_pos>::iterator			it;
	std::list<SDL_Texture*>::iterator	itsrf;

	it = event.snakePos.pos.begin();
	this->newposition.x = (*it).x * SDL_CASE;
	this->newposition.y = (*it).y * SDL_CASE;
	itsrf = this->pTexture.begin();
	switch ((*it).direction)
	{
	case north:
		itsrf++;
		break;
	case south:
		std::advance( itsrf, 2 );
		break;
	case west:
		std::advance( itsrf, 3 );
		break;
	default:
		// Do nothing
		break;
	}
	SDL_FRect dst = {
		static_cast<float>(this->newposition.x),
		static_cast<float>(this->newposition.y),
		static_cast<float>(this->newposition.w),
		static_cast<float>(this->newposition.h)
	};
	SDL_RenderTexture(pRenderer, *itsrf, NULL, &dst);
}

void					Sdl_class::draw_turn_body( dir curent, dir prev ){
	
	std::list<SDL_Texture*>::iterator   itsrf;

	itsrf = itbdy2;
	std::advance( itsrf, 2 );
	if (curent == west || curent == east)
	{
		switch (prev)
		{
		case south:
			if (curent == west) {
                // No change to itsrf
            } else if (curent == east) {
				std::advance( itsrf, 3 );
            }
			break;
		case north:
			if (curent == west) {
				itsrf++;
            } else if (curent == east) {
			    std::advance( itsrf, 2 );
            }
			break;
		default:
			// Do nothing
			break;
		}
	}
	else if (curent == north || curent == south)
	{
		switch (prev)
		{
		case east:
			if (curent == north) {
				// No change to itsrf
            } else if (curent == south) {
				itsrf++;
            }
			break;
		case west:
			if (curent == north) {
				std::advance( itsrf, 3 );
            } else if (curent == south) {
				std::advance( itsrf, 2 );
            }
			break;
		default:
			// Do nothing
			break;
		}
	}
	SDL_FRect dst = {
		static_cast<float>(this->newposition.x),
		static_cast<float>(this->newposition.y),
		static_cast<float>(this->newposition.w),
		static_cast<float>(this->newposition.h)
	};
	SDL_RenderTexture(pRenderer, *itsrf, NULL, &dst);
}

void					Sdl_class::draw_tail( dir prev ){
	
	std::list<SDL_Texture*>::iterator	itsrf;

	itsrf = itbdy;
	switch (prev)
	{
		case north:
			itsrf++;
			break;
		case south:
			std::advance( itsrf, 2 );
			break;
		case west:
			std::advance( itsrf, 3 );
			break;
		default:
			// Do nothing
			break;
	}
	SDL_FRect dst = {
		static_cast<float>(this->newposition.x),
		static_cast<float>(this->newposition.y),
		static_cast<float>(this->newposition.w),
		static_cast<float>(this->newposition.h)
	};
	SDL_RenderTexture(pRenderer, *itsrf, NULL, &dst);
}

void					Sdl_class::draw_body( GameEvent & event ){

	std::list<t_pos>::iterator			it;
	std::list<SDL_Texture*>::iterator	itsrf;
	std::list<SDL_Texture*>::iterator	itsrf2;
	dir									curent;
	dir									prev;

	it = event.snakePos.pos.begin();
	prev = (*it).direction;
	it++;
	for (; it != event.snakePos.pos.end(); ++it)
	{
		itsrf = itbdy;
		itsrf2 = itbdy2;
		this->newposition.x = (*it).x * SDL_CASE;
		this->newposition.y = (*it).y * SDL_CASE;
		curent = (*it).direction;
		switch ((*it).direction)
		{
		case north:
			itsrf++;
			break;
		case south:
			std::advance( itsrf, 2 );
			break;
		case west:
			std::advance( itsrf, 3 );
			itsrf2++;
			break;
		default:
			// Do nothing for itsrf
			itsrf2++;
		}
		it++;
		if (it == event.snakePos.pos.end())
			this->draw_tail(prev);
		else if (curent != prev)
			this->draw_turn_body(curent, prev);
		else {
			SDL_FRect dst = {
				static_cast<float>(this->newposition.x),
				static_cast<float>(this->newposition.y),
				static_cast<float>(this->newposition.w),
				static_cast<float>(this->newposition.h)
			};
			SDL_RenderTexture(pRenderer, *itsrf2, NULL, &dst);
		}
		it--;
		prev = curent;
	}
}

void					Sdl_class::draw_env( GameEvent & event){

	SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
	SDL_RenderClear(pRenderer);
	SDL_RenderTexture(pRenderer, this->backTex, NULL, NULL);

	this->draw_head( event);
	this->draw_body( event );
	this->newposition.x = event.elem.x * SDL_CASE;
	this->newposition.y = event.elem.y * SDL_CASE;
	SDL_FRect dst = {
		static_cast<float>(this->newposition.x),
		static_cast<float>(this->newposition.y),
		static_cast<float>(this->newposition.w),
		static_cast<float>(this->newposition.h)
	};
	SDL_RenderTexture(pRenderer, *ititem, NULL, &dst);
	SDL_RenderPresent(pRenderer);
}

bool					Sdl_class::check_event( GameEvent & event ){

	SDL_Event			sdleven;
	bool				continuer;

	continuer = true;
	event.changedir = true;
	SDL_PollEvent(&sdleven);
	switch(sdleven.type)
	{
	case SDL_EVENT_QUIT:
		continuer = 0;
		event.changedir = false;
		break;
	case SDL_EVENT_KEY_DOWN: {
		SDL_KeyboardEvent *key = (SDL_KeyboardEvent *)&sdleven;
		switch (key->key)
		{
		case SDLK_UP:
			event.direct = north;
			break;
		case SDLK_DOWN:
			event.direct = south;
			break;
		case SDLK_RIGHT:
			event.direct = east;
			break;
		case SDLK_LEFT:
			event.direct = west;
			break;
		case SDLK_ESCAPE:
			continuer = false;
			event.changedir = false;
			break;
		case SDLK_W:
			event.wall = !event.wall;
			break;
		case SDLK_1:
			event.changelib = true;
			event.lib = 1;
			break;
		case SDLK_3:
			event.changelib = true;
			event.lib = 3;
			break;
		default:
			event.changedir = false;
		}
		break;
	}
}
return continuer;
}

Sdl_class		& Sdl_class::operator=( Sdl_class const &rhs ) {
	this->screen = rhs.screen;
	this->pRenderer = rhs.pRenderer;
	return *this;
}