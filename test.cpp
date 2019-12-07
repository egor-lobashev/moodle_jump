#include "List_of_platforms.h"
#include <iostream>
#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(window_width, window_heghth), "Moodle Jump");

	sf::Texture txtr;
	txtr.loadFromFile("assets/images/moodler.png");

	sf::Sprite spr;
	spr.setTexture(txtr);

	window.draw(spr);
	window.display();

	int a;
	std::cin >> a;

	return 0;
}
