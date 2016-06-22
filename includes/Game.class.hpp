// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Game.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 15:33:14 by mmoumini          #+#    #+#             //
//   Updated: 2015/05/25 05:26:49 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _Game_
#define _Game_

#include "nibbler.hpp"
#include "element.hpp"
#include "Snake.class.hpp"
//class element;

//class Snake;
class Game {

public:
	Snake		*player1;
	Snake		*player2;
	element		*item;

	Game( void );
	Game( Game const &src );
	~Game( void );
	Game	& operator=( Game const &rhs);


bool		move( GameEvent & event);
void		key1Left( void );
void		key1Right( void );
void		key1Down( void );
void		key1Up( void );
};

#endif
