// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   element.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/12 00:04:56 by mmoumini          #+#    #+#             //
//   Updated: 2015/04/13 19:59:08 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _ELEMENT_ 
#define _ELEMENT_

#include "nibbler.hpp"
#include "enumSnake.hpp"

class element
{

public:
	int					x;
	int					y;
	dir					direction;
	element_type		type;

	element( void );
	~element( void );
	element(element const &);
	element & operator=(element const &);
};

bool	operator==(element const &, element const &);

#endif

