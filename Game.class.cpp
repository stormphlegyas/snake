// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Game.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/11 15:33:11 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 19:42:32 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "includes/Game.class.hpp"
#include "includes/Snake.class.hpp"
#include "includes/element.hpp"
#include "includes/nibbler.hpp"
#define HEIGHT_SURFACE 12
#define LENGTH_SURFACE 16
Game::Game( void ) {
	this->player1 = new Snake(LENGTH_SURFACE / 2, HEIGHT_SURFACE / 2);
	this->player2 = NULL;
	this->item = new element;
	this->item->x = std::rand() % LENGTH_SURFACE;
	this->item->y = std::rand() % HEIGHT_SURFACE;
	this->item->type = apple;
}


Game::Game( Game const &src ){
	*this = src;
}

bool			Game::move( GameEvent & event ){

	std::list<element>::iterator        it;
	element head = *this->player1->snake.begin();

	if (event.wall)
	{
		if ( this->player1->move_WallOption(event) == false )
			return( false );
	}
	else
		this->player1->move(event);
	it = this->player1->snake.begin();
	it++;
	while (it != this->player1->snake.end())
	{
		if ( *it == *this->player1->snake.begin())
		{
			return (false);
		}
		it++;
	}
	it = this->player1->snake.begin();
	if ((*it) == *this->item)
	{
		this->player1->eatApple();
		this->item->x = std::rand() % event.surface_length;
		this->item->y = std::rand() % event.surface_height;
	}
//	if (this->player2 != NULL)
//		this->player2->move();
	return (true);
}

Game::~Game( void ){
}


Game		& Game::operator=( Game const &rhs ) {
	this->player1 = rhs.player1;
	return *this;
}

void		Game::key1Left( void ) {
	this->player1->changeDirection(west);
}

void		Game::key1Right( void ) {
	this->player1->changeDirection(east);
}

void		Game::key1Down( void ) {
	this->player1->changeDirection(south);
}

void		Game::key1Up( void ) {
	this->player1->changeDirection(north);
}
