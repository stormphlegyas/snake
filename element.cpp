/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/12 00:05:47 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/08 20:52:14 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "includes/element.hpp"

element::element( void ) {
}


element::element( element const &src ){
    *this = src;
}

element::~element( void ){
}

element       & element::operator=( element const &rhs ) {
	this->x = rhs.x;
	this->y = rhs.y;
	this->direction = rhs.direction;
	return *this;
}

bool    operator==(element const & r, element const & l)
{
    return (r.x == l.x && r.y == l.y);
}
