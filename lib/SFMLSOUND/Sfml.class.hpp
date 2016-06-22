// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Sfml.class.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/07 14:51:21 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 21:55:56 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _SFML_CLASS_
#define _SFML_CLASS_

#include "Timer.hpp"
#include <iostream>
#include <list>
#include "../../includes/nibbler.hpp"
#include "../../includes/IGui.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio.hpp"
#include <CoreFoundation/CoreFoundation.h>
#include <cstdlib>
#include <sstream>
#define SFML_CASE 50

class Sfml_music  {

private:
	sf::Music			*music;

public:
	Sfml_music( void );
	Sfml_music( Sfml_music const &src );
	~Sfml_music( void );

	int				init( void );
	void			stop( void );
	Sfml_music	&	operator=( Sfml_music const &rhs);
};

#endif
