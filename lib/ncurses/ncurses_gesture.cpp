// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ncurses_gesture.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/08 09:59:12 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 20:02:43 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../../includes/nibbler.hpp"
#include "Ncurses.class.hpp"
#include <unistd.h>

Ncurses_class	*ncursesclass = new Ncurses_class;

extern "C" void				init( GameEvent& event )
{
	if (ncursesclass->init(event) == 0)
		exit(EXIT_FAILURE);
}

extern "C" void				check_event( GameEvent & event )
{

	if((event.continuer = ncursesclass->check_event(event)) == false)
		return ;
	event.ifmove = true;
	usleep(90000);
	return ;
}

extern "C" void				draw( GameEvent & event)
{
		ncursesclass->draw_env(event);
}

extern "C" void				closeWin( void )
{
	endwin();
}
