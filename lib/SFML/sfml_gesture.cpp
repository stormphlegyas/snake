/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sfml_gesture.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 09:59:12 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/12 17:39:22 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/nibbler.hpp"
#include "Sfml.class.hpp"
#include "sfml_exports.hpp"

Sfml_class	*sfmlclass = new Sfml_class;	

DLL_EXPORT void				init( GameEvent& event )
{
	if (sfmlclass->init(event) == 0)
		exit(EXIT_FAILURE);
}

DLL_EXPORT void				check_event( GameEvent & event )
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

DLL_EXPORT void				draw( GameEvent & event)
{
	if ( sfmlclass->endgame == false)
	{		
		sfmlclass->draw_env(event);
		sfmlclass->intro(event);
	}
	else
		sfmlclass->Game_over(event);
}

DLL_EXPORT void				closeWin( void )
{
	sfmlclass->app->close();
	sfmlclass->music->stop();
//	delete sfmlclass;
}
