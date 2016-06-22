// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 15:33:14 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 19:42:09 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _SNAKE_CLASS_
# define _SNAKE_CLASS_

#include "nibbler.hpp"
#include "element.hpp"

class Snake {
	dir                     _direction;
    element                 _lastBodyPart;

public:
	std::list<element>      snake;

	Snake( void );
	Snake( int x, int y );
	Snake( Snake const &src );
	~Snake( void );
	Snake	& operator=( Snake const &rhs);
	
	void		move( GameEvent & event );
	bool		move_WallOption( GameEvent & event );
	void		changeDirection(dir keydir);
	void		eatApple( void );
};

#endif
