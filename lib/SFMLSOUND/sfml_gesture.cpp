// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   sfml_gesture.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/08 09:59:12 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 21:59:31 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "../../includes/nibbler.hpp"
#include "Sfml.class.hpp"

Sfml_music	*sfmlclass = new Sfml_music;	

extern "C" void				init( void )
{
	if (sfmlclass->init() == 0)
		exit(EXIT_FAILURE);
}

extern "C" void				stop( void )
{
	sfmlclass->stop();
}
