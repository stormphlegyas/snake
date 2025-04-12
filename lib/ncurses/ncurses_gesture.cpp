/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_gesture.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 09:59:12 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/12 11:32:40 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/nibbler.hpp"
#include "Ncurses.class.hpp"

#ifndef _WIN32
    #include <unistd.h>
#else
    #include <windows.h>
#endif

Ncurses_class	*ncursesclass = new Ncurses_class;

extern "C" void				init( GameEvent& event )
{
	if (ncursesclass->init(event) == 0)
		exit(EXIT_FAILURE);
}

extern "C" void				check_event( GameEvent & event )
{
	if((event.continuer = ncursesclass->check_event(event)) == false)
		return;
	event.ifmove = true;

#ifndef _WIN32
	usleep(90000);
#else
	Sleep(90);
#endif

	return;
}

extern "C" void				draw( GameEvent & event)
{
	ncursesclass->draw_env(event);
}

extern "C" void				closeWin( void )
{
	endwin();
}
