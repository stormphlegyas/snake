/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_gesture.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/09 15:10:36 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/08 20:52:55 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/nibbler.hpp"
#include "sdl.class.hpp"

Sdl_class	*sdlclass;

extern "C" void				init( GameEvent &event )
{
	sdlclass = new Sdl_class;
	if (sdlclass->init(event) == 0)
		exit(EXIT_FAILURE);
	if (sdlclass->screen == NULL)
		exit(EXIT_FAILURE);
}

extern "C" void				check_event( GameEvent & event )
{
	event.currentTime = SDL_GetTicks();
	if ((event.continuer = sdlclass->check_event(event)) == false)
			return ;
	if (event.currentTime - event.lastTime > event.interval)
	{
		event.ifmove = true;
		event.lastTime = event.currentTime;
	}
	else
		SDL_Delay(event.interval - (event.currentTime - event.lastTime));
	return ;
}

extern "C" void				draw( GameEvent & event )
{
	sdlclass->draw_env(event);
}

extern "C" void				closeWin( void )
{
	delete sdlclass;
	sdlclass = NULL;
}
