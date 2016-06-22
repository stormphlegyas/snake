// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   nibbler.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/09 18:05:31 by mmoumini          #+#    #+#             //
//   Updated: 2016/06/23 00:43:02 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef _SNAKE_
#define _SNAKE_

#include <dlfcn.h>
#include <iostream>
#include "enumSnake.hpp"
#include <list>

//#define HEIGHT_SURFACE 12
//#define LENGTH_SURFACE 16
#define INTERVAL 230

typedef struct s_pos {
	int			x;
	int			y;
	dir			direction;
}				t_pos;

typedef struct s_snakePos {
	std::list<t_pos>	pos;
}						t_snkPos;

typedef struct s_Event {
	bool		wall;
	int			surface_height;
	int			surface_length;
	int			lastTime;
	int			currentTime;
	int			interval;
	bool		continuer;
	bool		ifmove;
	bool		changedir;
	bool		changelib;
	bool		firstlaunch;
	int			lib;
	dir			direct;
	t_pos		elem;
	int			elemvalue;
	t_snkPos	snakePos;
}               GameEvent;


#endif
