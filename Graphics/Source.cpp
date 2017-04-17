#include <SFML/Graphics.hpp>
#include <Windows.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	sf::Texture *wiz = new sf::Texture;
	wiz->loadFromFile("Wizard.png");
	sf::RectangleShape wizard(sf::Vector2f(128., 128.));
	wizard.setTexture(wiz);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(wizard);
		window.display();
		wizard.move(sf::Vector2f(2, 0));
		Sleep(100);
	}
	return 0;
}