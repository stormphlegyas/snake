// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Ncurses.class.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/07 14:51:21 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 19:45:55 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _NCURSES_CLASS_
#define _NCURSES_CLASS_

#include <ncurses.h>
#include <iostream>
#include <list>
#include "../../includes/nibbler.hpp"
#include "../../includes/IGui.hpp"

class Ncurses_class : public IGui {

public:

	Ncurses_class( void );
	Ncurses_class( Ncurses_class const &src );
	~Ncurses_class( void );
	Ncurses_class	& operator=( Ncurses_class const &rhs);
	int			init( GameEvent & event );
	bool		check_event( GameEvent & event );
	void		draw_env( GameEvent & event );
	void		draw_head( GameEvent & event );
	void		draw_body( GameEvent & event );
};

#endif
