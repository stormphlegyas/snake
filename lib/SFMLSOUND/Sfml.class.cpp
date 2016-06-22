// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Sfml.class.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/07 15:05:06 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 22:30:13 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Sfml.class.hpp"

Sfml_music::Sfml_music( void ) {

}


Sfml_music::Sfml_music( Sfml_music const &src ){
	*this = src;
}

Sfml_music::~Sfml_music( void ){
}

int				Sfml_music::init( void ){

	this->music = new sf::Music;
	this->music->setLoop(true);
	return (1);
}

void				Sfml_music::stop( void ){
}

Sfml_music		&	Sfml_music::operator=( Sfml_music const &rhs ) {
	return *this;
}
