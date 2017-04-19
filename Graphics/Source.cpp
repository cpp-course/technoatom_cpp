//#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "objects.h"
#include "TestMap.h"

const size_t myfloor = 400;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Level_1");
	sf::Clock clock;
	//sf::CircleShape shape(100.f);
	//sf::Texture *wiz = new sf::Texture;
	//wiz->loadFromFile("Textures/Wizard.png");
	//sf::RectangleShape wizard(sf::Vector2f(128., 128.));
	//wizard.setTexture(wiz);
	sf::RectangleShape background(sf::Vector2f(800, 600));
	background.setFillColor(sf::Color::White);
	Hero *player = new Wizard(400, myfloor, 128, 128, "Wizard.png", 2, 5, 2, 10);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 10000;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player->direction_ = 1;
			player->Move(time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player->direction_ = 0;
			player->Move(time);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || player->y_ < myfloor)
		{
			player->Jump();
		}
		window.clear();
		window.draw(background);
		window.draw(player->sprite_);
		//window.draw(wizard);
		window.display();
		//wizard.move(sf::Vector2f(2, 0));
		Sleep(50);
	}
	delete player;
	return 0;
}