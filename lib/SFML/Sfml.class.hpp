// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Sfml.class.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/07 14:51:21 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 19:47:56 by mmoumini         ###   ########.fr       //
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

class Sfml_class : public IGui {

private:
	bool				firstlaunch;
//	sf::Music			*music;
	sf::Music			*codec;
	sf::Texture			*image;
	Timer				timeline;
	Timer				timeEnd;
	sf::SoundBuffer		*buffer;
	sf::Sound			*sound;
	sf::Font			font;
	sf::Text			score;
	int					totalscore;
	t_pos				prev;

public:
	sf::Music			*music;
	bool				endgame;
	Timer				timer;
	sf::RenderWindow	*app;
	Sfml_class( void );
	Sfml_class( Sfml_class const &src );
	~Sfml_class( void );

	int				init( GameEvent & event );
	bool			check_event( GameEvent & event );
	void			draw_env( GameEvent & event );
	void			draw_head( GameEvent & event );
	void			draw_body( GameEvent & event );
	void			intro( GameEvent & event );
	void			Game_over( GameEvent & event );
	void			End_trigger( void );
	Sfml_class	&	operator=( Sfml_class const &rhs);
};

#endif
