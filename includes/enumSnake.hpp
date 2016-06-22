// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   enumSnake.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 23:57:20 by mmoumini          #+#    #+#             //
//   Updated: 2016/06/23 00:42:29 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ENUMSNAKE_HPP
# define ENUMSNAKE_HPP

enum element_type {
	snake_head = 1,
	snake_body = 2,
	apple = 3
};

enum dir {
	south,
	north,
	east,
	west
};

enum keyPlayer1 {
	none,
	up,
	down,
	left,
	right
};

enum keyGameLogic {
	none2,
	escape,
	gui1,
	gui2,
	gui3
};

#endif
