// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   sdl.class.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/01/15 23:10:50 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 19:45:30 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _SDL_CLASS_
#define _SDL_CLASS_

#include <dlfcn.h>
#include <iostream>
#include <list>
//#include "Headers/SDL.h"
#include "SDL2/SDL.h"
#include "../../includes/nibbler.hpp"
#include "../../includes/IGui.hpp"

#define SDL_CASE 50


class Sdl_class : public IGui {
private:
	std::list<SDL_RWops*>		file;
	int							lastTime;
    int							currentTime;
	SDL_Surface					*back;
	SDL_Texture					*backTex;
	SDL_Renderer				*pRenderer;
	std::list<SDL_Texture*>		pTexture;
public:
	SDL_Window					*screen;
	SDL_Surface					*snk;
	std::list<SDL_Surface*>		snk_body;
	SDL_Rect					newposition;
	std::list<SDL_Texture*>::iterator   itbdy;
	std::list<SDL_Texture*>::iterator   itbdy2;
	std::list<SDL_Texture*>::iterator   ititem;

	Sdl_class( void );
	Sdl_class( Sdl_class const &src );
	~Sdl_class( void );
	Sdl_class	& operator=( Sdl_class const &rhs);
	int			init( GameEvent & event );
	bool		check_event( GameEvent & event );
	void		draw_env( GameEvent & event );
	void		draw_head( GameEvent & event );
	void		draw_body( GameEvent & event );
	void		draw_tail( dir prev );
	void		draw_turn_body( dir curent, dir prev );
};

#endif
