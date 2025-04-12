/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 15:05:06 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/12 16:09:16 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Ncurses.class.hpp"

Ncurses_class::Ncurses_class( void ) {

}


Ncurses_class::Ncurses_class( Ncurses_class const &src ){
	*this = src;
}

Ncurses_class::~Ncurses_class( void ){
	endwin();
}

int				Ncurses_class::init( GameEvent & event ){
	(void)event; // Suppress unused parameter warning

	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, true);
	nodelay(stdscr, true);
	start_color();
	cbreak();
	init_pair(1, COLOR_WHITE, COLOR_BLACK );
	attron(COLOR_PAIR(1));
	return (1);
}

bool			Ncurses_class::check_event( GameEvent & event ){
	
	bool		continuer;
	int			input;

	input = 0;
	continuer = true;
	event.changedir = true;
	input = getch();
	switch (input)
	{
	case KEY_LEFT:
		event.direct = west;
		break;
	case KEY_RIGHT:
		event.direct = east;
		break;
	case KEY_UP:
		event.direct = north;
		break;
	case KEY_DOWN:
		event.direct = south;
		break;
	case 27:
		continuer = false;
		event.changedir = false;
		break;
	case 119:
		if (event.wall == true)
			event.wall = false;
		else
			event.wall = true;
		break;
	case 50:
		event.changelib = true;
		event.lib = 2;
		break;
	case 49:
		event.changelib = true;
		event.lib = 1;
		break;
	}
	return continuer;
}

void				Ncurses_class::draw_head( GameEvent & event ){

	std::list<t_pos>::iterator			it;

	it = event.snakePos.pos.begin();
	mvaddch((*it).y, (*it).x, '@');
}

void				Ncurses_class::draw_body( GameEvent & event ){

	std::list<t_pos>::iterator		it;

	it = event.snakePos.pos.begin();
	it++;
	for (; it != event.snakePos.pos.end(); ++it)
		mvaddch((*it).y, (*it).x, 'X');
}

void				Ncurses_class::draw_env( GameEvent & event ){
	clear();
	this->draw_head(event);
	this->draw_body(event);
	mvaddch(event.elem.y, event.elem.x,  '&' );
	refresh();
}

Ncurses_class & Ncurses_class::operator=( Ncurses_class const &rhs ) {
	(void)rhs; // Suppress unused parameter warning
	return *this;
}