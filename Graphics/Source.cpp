//#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <memory>
#include "objects.h"
#include "TestMap.h"

const sf::Vector2f start_point(0, 0);

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Level_1");
	sf::Clock clock;
	//sf::CircleShape shape(100.f);
	//sf::Texture *wiz = new sf::Texture;
	//wiz->loadFromFile("Textures/Wizard.png");
	//sf::RectangleShape wizard(sf::Vector2f(128., 128.));
	//wizard.setTexture(wiz);
	sf::RectangleShape background(sf::Vector2f(WINDOW_X, WINDOW_Y));
	background.setFillColor(sf::Color::White);
	std::shared_ptr<Hero> player(new Wizard(start_point, &window));

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
		
		player->Control();
		player->Physics(time);
		player->Intersection();
		window.clear();
		window.draw(background);
		player->Draw();
		window.display();
		//Sleep(10);
	}
	return 0;
}