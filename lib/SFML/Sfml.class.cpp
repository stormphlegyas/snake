/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sfml.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoumini <mmoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 15:05:06 by mmoumini          #+#    #+#             */
/*   Updated: 2025/04/11 11:27:00 by mmoumini         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "Sfml.class.hpp"

Sfml_class::Sfml_class()
: score(font, "", 24)
{
	this->music = nullptr;
	this->codec = nullptr;
	this->image = nullptr;
	this->buffer = nullptr;
	this->sound = nullptr;
	this->app = nullptr;
	this->totalscore = 0;
	this->endgame = false;
}

Sfml_class::Sfml_class(Sfml_class const &src)
: score(font, "", 24)
{
	*this = src;
}

Sfml_class::~Sfml_class() {
	if (this->app)
		this->app->close();
}

void Sfml_class::intro(GameEvent &event) {
	if (!event.firstlaunch)
		return;

	int i = 0;
	int elapse = timeline.GetTime_sec();
	bool change = true;

	char tab[19][3] = {
		{'0','0', 0 }, {'0', '1', 0}, {'0', '2', 0},
		{'0', '3', 0}, {'0', '4', 0}, {'0', '5', 0},
		{'0', '6', 0}, {'0', '7', 0}, {'0', '8', 0},
		{'0', '9', 0}, {'1', '0', 0}, {'1', '1', 0},
		{'1', '2', 0}, {'1', '3', 0}, {'1', '4', 0},
		{'1', '5', 0}, {'1', '6', 0}, {'1', '7', 0},
		{0}
	};

	switch (elapse) {
		case 0: i = 0; this->codec->play(); break;
		case 4: i = 1; break;
		case 6: i = 2; break;
		case 7: i = 3; break;
		case 8: i = 4; break;
		case 10: i = 5; break;
		case 12: i = 6; break;
		case 14: i = 7; break;
		case 17: i = 8; break;
		case 19: i = 9; break;
		case 22: i = 10; break;
		case 26: i = 11; break;
		case 29: i = 12; break;
		case 32: i = 13; break;
		case 36: i = 14; break;
		case 40: i = 15; break;
		case 42: i = 16; break;
		case 45: i = 17; break;
		default: change = false; break;
	}

	if (change) {
		std::stringstream stream;
		stream << "src/codec/" << tab[i] << ".png";

		if (!this->image->loadFromFile(stream.str())) {
			std::cerr << "Erreur chargement image intro: " << stream.str() << std::endl;
			return;
		}

		sf::Sprite sprite(*this->image);
		sprite.setPosition({0.f, 0.f});
		this->app->clear();
		this->app->draw(sprite);
		this->app->display();

		while (elapse == timeline.GetTime_sec()) {}
	}

	if (elapse > 47) {
		timeline.Reinitialize();
		event.firstlaunch = false;
	}
}

int Sfml_class::init(GameEvent &event) {
	sf::Vector2u windowSize(
		static_cast<unsigned int>(SFML_CASE * event.surface_length),
		static_cast<unsigned int>(SFML_CASE * event.surface_height)
	);
	this->app = new sf::RenderWindow(sf::VideoMode(windowSize, 32), "nibbler");

	this->timer.Start();
	this->timeline.Start();

	this->music = new sf::Music;
	this->codec = new sf::Music;
	this->image = new sf::Texture;
	this->buffer = new sf::SoundBuffer;

	if (!this->buffer->loadFromFile("src/sound/equip.ogg")) {
		std::cerr << "can't load sound ! : equip.ogg" << std::endl;
	}
	this->sound = new sf::Sound(*this->buffer);

	this->totalscore = 0;

	if (!this->font.openFromFile("src/digital-7.ttf")) {
		std::cout << "can't load font!" << std::endl;
	}

	this->score = sf::Text(this->font, "0", 24);
	this->score.setFillColor(sf::Color::Green);
	this->score.setPosition({0.f, 0.f});

	if (!this->music->openFromFile("src/sound/music.ogg") || !this->codec->openFromFile("src/sound/intro.ogg")) {
		std::cout << "can't load music.ogg!" << std::endl;
		return 0;
	}

	this->music->play();
	this->music->setVolume(50);
	this->music->setLooping(true);
	this->sound->setVolume(100);
	this->endgame = false;

	return 1;
}

void Sfml_class::End_trigger() {
	std::stringstream stream;
	char tab[6][3] = {
		{'0','0', 0 }, {'0', '1', 0}, {'0', '2', 0},
		{'0', '3', 0}, {'0', '4', 0}, {0}
	};

	this->music->stop();
	this->timeEnd.Start();
	this->endgame = true;

	stream << "src/sound/end_" << tab[std::rand() % 5] << ".ogg";

	if (!this->buffer->loadFromFile("src/sound/exclamation.ogg")) {
		std::cerr << "Erreur chargement son exclamation\n";
	}
	this->sound->setBuffer(*this->buffer);
	this->sound->setVolume(100);
	this->sound->play();

	if (!this->music->openFromFile(stream.str()))
		std::cerr << "can't load sound ! : " << stream.str() << std::endl;

	this->music->setLooping(false);
	this->music->setVolume(100);
	this->music->play();
}

void Sfml_class::Game_over(GameEvent &event) {
	event.continuer = true;
	this->app->clear();

	std::stringstream stream;
	stream << "your score : " << totalscore;
	this->score.setString(stream.str());
	this->score.setCharacterSize(32);
	this->score.setPosition({
		static_cast<float>(SFML_CASE * event.surface_length) / 2.f,
		static_cast<float>(SFML_CASE * event.surface_height) / 2.f
	});

	if (!this->image->loadFromFile("src/codec/game_over.png")) {
		std::cerr << "Erreur chargement image game_over\n";
	}
	sf::Sprite sprite(*this->image);
	sprite.setPosition({0.f, 0.f});

	this->app->draw(sprite);
	this->app->draw(score);
	this->app->display();

	if (timeEnd.GetTime_sec() > 10)
		event.continuer = false;
}

bool Sfml_class::check_event(GameEvent &event) {
    bool continuer = true;
    event.changedir = true;
    if (const std::optional<sf::Event> sfEvent = this->app->pollEvent()) {

        if (sfEvent->is<sf::Event::Closed>()) {
            continuer = false;
            event.changedir = false;
        }
        else if (sfEvent->is<sf::Event::KeyPressed>()) {
\
            const auto* keyEvent = sfEvent->getIf<sf::Event::KeyPressed>();
            const sf::Keyboard::Key key = keyEvent->code;

            switch (key) {
                case sf::Keyboard::Key::Escape:
                    continuer = false;
                    event.changedir = false;
                    break;
                case sf::Keyboard::Key::Left:
                    event.direct = west;
                    break;
                case sf::Keyboard::Key::Right:
                    event.direct = east;
                    break;
                case sf::Keyboard::Key::Up:
                    event.direct = north;
                    break;
                case sf::Keyboard::Key::Down:
                    event.direct = south;
                    break;
                case sf::Keyboard::Key::Space:
                    event.firstlaunch = false;
                    this->codec->stop();
                    break;
                case sf::Keyboard::Key::W:
                    event.wall = !event.wall;
                    break;
                case sf::Keyboard::Key::Num2:
                    event.changelib = true;
                    event.lib = 2;
                    break;
                case sf::Keyboard::Key::Num3:
                    event.changelib = true;
                    event.lib = 3;
                    break;
                default:
                    break;
            }
        }
    }

    return continuer;
}


void Sfml_class::draw_head(GameEvent &event) {
	auto it = event.snakePos.pos.begin();

	sf::RectangleShape rectangle;
	rectangle.setSize({static_cast<float>(SFML_CASE), static_cast<float>(SFML_CASE)});
	rectangle.setPosition({
		static_cast<float>(it->x * SFML_CASE),
		static_cast<float>(it->y * SFML_CASE)
	});
	rectangle.setFillColor(sf::Color(22, 160, 133));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(26, 188, 156));

	this->app->draw(rectangle);
}

void Sfml_class::draw_body(GameEvent &event) {
	auto it = std::next(event.snakePos.pos.begin());

	for (; it != event.snakePos.pos.end(); ++it) {
		sf::RectangleShape rectangle;
		rectangle.setSize({static_cast<float>(SFML_CASE), static_cast<float>(SFML_CASE)});
		rectangle.setPosition({
			static_cast<float>(it->x * SFML_CASE),
			static_cast<float>(it->y * SFML_CASE)
		});
		rectangle.setFillColor(sf::Color(39, 174, 96));
		rectangle.setOutlineThickness(2);
		rectangle.setOutlineColor(sf::Color(46, 204, 113));
		this->app->draw(rectangle);
	}
}

void Sfml_class::draw_env(GameEvent &event) {
	if (event.firstlaunch)
		return;

	if (!event.continuer) {
		this->End_trigger();
		this->Game_over(event);
		event.continuer = true;
		return;
	}

	this->app->clear();
	this->draw_head(event);
	this->draw_body(event);

	sf::RectangleShape rectangle;
	rectangle.setSize({static_cast<float>(SFML_CASE), static_cast<float>(SFML_CASE)});
	rectangle.setPosition({
		static_cast<float>(event.elem.x * SFML_CASE),
		static_cast<float>(event.elem.y * SFML_CASE)
	});
	rectangle.setFillColor(sf::Color(243, 156, 18));
	rectangle.setOutlineThickness(2);
	rectangle.setOutlineColor(sf::Color(241, 196, 15));

	if (prev.x != event.elem.x || prev.y != event.elem.y) {
		totalscore += event.elemvalue;
		event.elemvalue = 110;
		this->sound->play();
		prev = event.elem;
	}

	if (event.elemvalue > 10)
		event.elemvalue -= 5;

	std::stringstream stream;
	stream << totalscore;
	this->score.setString(stream.str());

	this->app->draw(rectangle);
	this->app->draw(this->score);
	this->app->display();
}

Sfml_class &Sfml_class::operator=(Sfml_class const &rhs) {
	if (this != &rhs) {
		// Deep copy si nécessaire
	}
	return *this;
}
