/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 23:10:50 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/12 11:29:38 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef _SDL_CLASS_
#define _SDL_CLASS_

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif
#include <iostream>
#include <list>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_filesystem.h>
#include "../../includes/nibbler.hpp"
#include "../../includes/IGui.hpp"

#define SDL_CASE 50


class Sdl_class : public IGui {
private:
	std::list<SDL_IOStream*> 	file;
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
	virtual ~Sdl_class( void );
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