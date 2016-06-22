// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Sfml.class.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/05/07 15:05:06 by mmoumini          #+#    #+#             //
//   Updated: 2015/06/07 20:05:27 by mmoumini         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Sfml.class.hpp"

Sfml_class::Sfml_class( void ) {

}


Sfml_class::Sfml_class( Sfml_class const &src ){
	*this = src;
}

Sfml_class::~Sfml_class( void ){
	this->app->close();
}

void					Sfml_class::intro( GameEvent & event ){

	if ( event.firstlaunch == false)
		return ;
	sf::Sprite			sprite;
	int					i;
	int					elapse;
	bool				change;
	char                tab[19][3] = { {'0','0', 0 }, {'0', '1', 0}, {'0', '2', 0},
									   {'0', '3', 0}, {'0', '4', 0}, {'0', '5', 0},
									   {'0', '6', 0}, {'0', '7', 0}, {'0', '8', 0},
									   {'0', '9', 0}, {'1', '0', 0}, {'1', '1', 0},
									   {'1', '2', 0}, {'1', '3', 0}, {'1', '4', 0},
									   {'1', '5', 0}, {'1', '6', 0}, {'1', '7', 0},
									   0};

	i = 0;
	elapse = timeline.GetTime_sec();
	change = true;
	switch( elapse )
	{
	case 0 :
		i = 0;
		this->codec->play();
		break;
	case 4 :
		i = 1;
		break;
	case 6 :
		i = 2;
		break;
	case 7 :
		i = 3;
		break;
	case 8 :
		i = 4;
		break;
	case 10 :
		i = 5;
		break;
	case 12 :
		i = 6;
		break;
	case 14 :
		i = 7;
		break;
	case 17 :
		i = 8;
		break;
	case 19 :
		i = 9;
		break;
	case 22 :
		i = 10;
		break;
	case 26 :
		i = 11;
		break;
	case 29 :
		i = 12;
		break;
	case 32 :
		i = 13;
		break;
	case 36 :
		i = 14;
		break;
	case 40 :
		i = 15;
		break;
	case 42 :
		i = 16;
		break;
	case 45 :
		i = 17;
		break;
	default:
		change = false;
		break;
	}
	if (change == true)
	{
		std::stringstream	stream;
		stream << "src/codec/" << tab[i] << ".png";	
		this->app->clear();
		this->image->loadFromFile(stream.str());
		sprite.setTexture(*this->image);
		sprite.setPosition(0, 0);
		this->app->draw(sprite);
		this->app->display();
		while( elapse ==  timeline.GetTime_sec() )
			i = i;		
	}
	if (elapse > 47)
	{
		timeline.Reinitialize();
		event.firstlaunch = false;
		
	}
}

int				Sfml_class::init( GameEvent & event ){

//	this->firstlaunch = true;
	this->app = new sf::RenderWindow(sf::VideoMode(SFML_CASE * event.surface_length, SFML_CASE * event.surface_height, 32), "nibbler");
	this->timer.Start();
	this->timeline.Start();
	this->music = new sf::Music;
	this->codec = new sf::Music;
	this->image = new sf::Texture;
	this->buffer = new sf::SoundBuffer;
	this->sound = new sf::Sound;
	this->totalscore = 0;
	if (!this->font.loadFromFile("src/digital-7.ttf"))
	{
		std::cout << "can't load font!" << std::endl;
	}
	this->score.setFont(this->font);
	this->score.setString("0");
	this->score.setCharacterSize(24);
	this->score.setColor(sf::Color::Green);
	this->score.setPosition(0, 0);
	if (!this->music->openFromFile("src/sound/music.ogg") || !(this->codec->openFromFile("src/sound/intro.ogg")))
	{
		std::cout << "can't load musique.ogg!" << std::endl; 
		return 0;
	}
	this->music->play();
	this->music->setVolume(50);
	this->music->setLoop(true);
	if (!this->buffer->loadFromFile("src/sound/equip.ogg"))
		std::cout << "can't load sound ! : " << "equip.ogg" << std::endl;
	this->sound->setBuffer( *this->buffer );
	this->sound->setVolume(100);
	this->endgame = false;
	return (1);
}

void				Sfml_class::End_trigger( void ){

	std::stringstream	stream;
	char				tab[6][3] = { {'0','0', 0 }, {'0', '1', 0}, {'0', '2', 0},
									  {'0', '3', 0}, {'0', '4', 0}, 0};
	this->music->stop();
	this->timeEnd.Start();
	this->endgame = true;
	stream << "src/sound/end_" << tab[ std::rand() % 5 ] << ".ogg";	
	this->buffer->loadFromFile("src/sound/exclamation.ogg");
	this->sound->setBuffer( *this->buffer );
	this->sound->setVolume(100);
	this->sound->play();
	if (!this->music->openFromFile(stream.str()))
		std::cout << "can't load sound ! : " << stream.str() << std::endl;
	this->music->setLoop(false);
	this->music->setVolume(100);
	this->music->play();
}

void				Sfml_class::Game_over( GameEvent & event ){
	sf::Sprite		sprite;
	std::stringstream	stream;

	event.continuer = true;
	this->app->clear();
	stream << "your score : " << totalscore;
	this->score.setString(stream.str());
	this->score.setCharacterSize(32);
	this->score.setPosition((SFML_CASE * event.surface_length) / 2, (SFML_CASE * event.surface_height) / 2);
	this->image->loadFromFile("src/codec/game_over.png");
	sprite.setTexture(*this->image);
	sprite.setPosition(0, 0);
	this->app->draw(sprite);
	this->app->draw(score);
	this->app->display();
	if ( timeEnd.GetTime_sec() > 10)
		event.continuer = false;
}

bool				Sfml_class::check_event( GameEvent & event ){
	
	bool			continuer;
	sf::Event		appevent;
	sf::Keyboard	key;

	continuer = true;
	event.changedir = true;
	this->app->pollEvent(appevent);
	switch( appevent.type )
	{
	case sf::Event::Closed :
		continuer = false;
		event.changedir = false;
		break;
	case sf::Event::KeyPressed :
		if (key.isKeyPressed( sf::Keyboard::Escape )){
			continuer = false;
			event.changedir = false;
		}
		if (key.isKeyPressed( sf::Keyboard::Left )){
			event.direct = west;
		}
		if (key.isKeyPressed( sf::Keyboard::Right )){
			event.direct = east;
		}
		if (key.isKeyPressed( sf::Keyboard::Up )){
			event.direct = north;
		}
		if (key.isKeyPressed( sf::Keyboard::Down )){
			event.direct = south;
		}
		if (key.isKeyPressed( sf::Keyboard::Space )){
			event.firstlaunch = false;
			this->codec->stop();
		}
		if (key.isKeyPressed( sf::Keyboard::W )){
			if (event.wall == false)
				event.wall = true;
			else
				event.wall = false;
		}
		if (key.isKeyPressed( sf::Keyboard::Num2 )){
			event.changelib = true;
			event.lib = 2;
		}
		if (key.isKeyPressed( sf::Keyboard::Num3 )){
			event.changelib = true;
			event.lib = 3;
		}
		break;
	default:
		break;
	}
	return continuer;
}

void				Sfml_class::draw_head( GameEvent & event ){

	std::list<t_pos>::iterator			it;
	sf::RectangleShape				rectangle;

	it = event.snakePos.pos.begin();
	rectangle.setSize(sf::Vector2f(SFML_CASE, SFML_CASE));
    rectangle.setPosition((*it).x * SFML_CASE, (*it).y * SFML_CASE);
	rectangle.setFillColor(sf::Color(22, 160, 133));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(26, 188, 156));
	this->app->draw(rectangle);
}

void				Sfml_class::draw_body( GameEvent & event ){

	std::list<t_pos>::iterator		it;

	it = event.snakePos.pos.begin();
	it++;
	for (it = it; it != event.snakePos.pos.end(); ++it)
	{
		sf::RectangleShape			rectangle;
		rectangle.setSize(sf::Vector2f(SFML_CASE, SFML_CASE));
		rectangle.setPosition((*it).x * SFML_CASE, (*it).y * SFML_CASE);
		rectangle.setFillColor(sf::Color(39, 174, 96));
		rectangle.setOutlineThickness(2);
		rectangle.setOutlineColor(sf::Color(46, 204, 113));
		this->app->draw(rectangle);
	}
}

void					Sfml_class::draw_env( GameEvent & event ){
	
	std::stringstream	stream;
	sf::RectangleShape	rectangle;

	if ( event.firstlaunch == true)
		return ;
	if ( event.continuer == false)
	{
		this->End_trigger();
		this->Game_over(event);
		event.continuer = true;
		return ;
	}
	this->app->clear();
	this->draw_head(event);
	this->draw_body(event);
	rectangle.setSize(sf::Vector2f(SFML_CASE, SFML_CASE));
	rectangle.setPosition(event.elem.x * SFML_CASE, event.elem.y * SFML_CASE );
	rectangle.setFillColor(sf::Color(243, 156, 18));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(241, 196, 15));
	if ( prev.x != event.elem.x || prev.y != event.elem.y)
	{
		totalscore = totalscore + event.elemvalue;
		event.elemvalue = 110;
		this->sound->play();
		prev.x = event.elem.x;
		prev.y = event.elem.y;
	}
	if (event.elemvalue > 10)
		event.elemvalue = event.elemvalue - 5;
	stream << totalscore;
	this->score.setString(stream.str());
	this->app->draw(rectangle);
	this->app->draw(this->score);
	this->app->display();
}

Sfml_class		&	Sfml_class::operator=( Sfml_class const &rhs ) {
	return *this;
}
