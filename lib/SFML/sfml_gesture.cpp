// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   sfml_gesture.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/08 09:59:12 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 20:03:57 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../../includes/nibbler.hpp"
#include "Sfml.class.hpp"

Sfml_class	*sfmlclass = new Sfml_class;	

extern "C" void				init( GameEvent& event )
{
	if (sfmlclass->init(event) == 0)
		exit(EXIT_FAILURE);
}

extern "C" void				check_event( GameEvent & event )
{

	event.currentTime = sfmlclass->timer.GetTime();
	if((event.continuer = sfmlclass->check_event(event)) == false)
		return ;
	if (event.currentTime - event.lastTime > event.interval)
    {
		event.ifmove = true;
		event.lastTime = event.currentTime;
	}
	return ;
}

extern "C" void				draw( GameEvent & event)
{
	if ( sfmlclass->endgame == false)
	{		
		sfmlclass->draw_env(event);
		sfmlclass->intro(event);
	}
	else
		sfmlclass->Game_over(event);
}

extern "C" void				closeWin( void )
{
	sfmlclass->app->close();
	sfmlclass->music->stop();
//	delete sfmlclass;
}
