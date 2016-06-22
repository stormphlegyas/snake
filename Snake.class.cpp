// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Snake.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 15:33:11 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 19:41:32 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "includes/Snake.class.hpp"

Snake::Snake( void ) {
	element head;
	head.x = 3;
	head.y = 0;
	head.type = snake_head;
	head.direction = east;
	this->snake.push_back(head);

	element body;
	body.x = 2;
	body.y = 0;
	body.type = snake_body;
	body.direction = east;
	this->snake.push_back(body);

	element body2;
    body2.x = 1;
    body2.y = 0;
    body2.type = snake_body;
    body2.direction = east;
    this->snake.push_back(body2);

	element tail;
	tail.x = 0;
	tail.y = 0;
	tail.type = snake_body;
	tail.direction = east;
	this->snake.push_back(tail);

	this->_direction = east;
}


Snake::Snake( int x, int y ) {
	
	element head;
	head.x = x;
	head.y = y;
	head.type = snake_head;
	head.direction = east;
	this->snake.push_back(head);

	element body;
	body.x = x - 1;
	body.y = y;
	body.type = snake_body;
	body.direction = east;
	this->snake.push_back(body);

	element body2;
    body2.x = x - 1;
    body2.y = y - 1;
    body2.type = snake_body;
    body2.direction = north;
    this->snake.push_back(body2);

	element tail;
	tail.x = x;
	tail.y = y - 1;
	tail.type = snake_body;
	tail.direction = west;
	this->snake.push_back(tail);

	this->_direction = east;
}


Snake::Snake( Snake const &src ){
	*this = src;
}


Snake::~Snake( void ){
}

Snake		& Snake::operator=( Snake const &rhs ) {
		return *this;
}

void		Snake::changeDirection(dir keydir){
	std::list<element>::iterator it = snake.begin();

	if (((*it).direction == east && keydir != west)
		|| ((*it).direction == west && keydir != east)
		|| ((*it).direction == south && keydir != north)
		|| ((*it).direction == north && keydir != south))
		this->_direction = keydir;
}

void		Snake::eatApple( void ){
	snake.push_back(_lastBodyPart);
}

void		Snake::move( GameEvent & event ){

	std::list<element>::iterator it = snake.end();
	int		c;
	element newHead;

	c = 0;
	it--;
	_lastBodyPart = *it;

	snake.pop_back();
	it = snake.begin();

	newHead.x = (*it).x;
	newHead.y = (*it).y;
	newHead.direction = this->_direction;
	newHead.type = snake_head;
	switch ( this->_direction ){
		case east:
			newHead.x++;
			if (newHead.x >= event.surface_length)
				newHead.x = 0;
			break;
		case west:
			newHead.x--;
			if (newHead.x < 0)
				newHead.x = event.surface_length - 1;
			break;
		case north:
			newHead.y--;
			if (newHead.y < 0)
				newHead.y = event.surface_height - 1;
			break;
		case south:
			newHead.y++;
			if (newHead.y >= event.surface_height)
				newHead.y = 0;
			break;
	}
	snake.push_front(newHead);
	it = snake.begin();
	it++;
	(*it).type = snake_body;
}

bool		Snake::move_WallOption( GameEvent & event ){

	std::list<element>::iterator it = snake.end();
	int		c;
	element newHead;
	bool	continuer;

	c = 0;
	it--;
	_lastBodyPart = *it;

	snake.pop_back();
	it = snake.begin();
	continuer = true;
	newHead.x = (*it).x;
	newHead.y = (*it).y;
	newHead.direction = this->_direction;
	newHead.type = snake_head;
	switch ( this->_direction ){
		case east:
			newHead.x++;
			if (newHead.x >= event.surface_length)
				continuer = false;
			break;
		case west:
			newHead.x--;
			if (newHead.x < 0)
				continuer = false;
			break;
		case north:
			newHead.y--;
			if (newHead.y < 0)
				continuer = false;
			break;
		case south:
			newHead.y++;
			if (newHead.y >= event.surface_height)
				continuer = false;
			break;
	}
	snake.push_front(newHead);
	it = snake.begin();
	it++;
	(*it).type = snake_body;
	return (continuer);
}
