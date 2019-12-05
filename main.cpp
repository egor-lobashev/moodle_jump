#include <SFML/Graphics.hpp>
#include "List_of_platforms.h"

/*
const int window_heghth = 650, window_width = 400,
		platform_heghth = 10, platform_width = 30,
		platforms_rate = 100;
*/


void main_cycle(sf::RenderWindow& window, List_of_platforms& platforms)
{
	int heghth = 0;
	sf::Clock clock;

	while (window.isOpen())
	{
		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		// --control--

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// ...


		// --logics--

		// update objcts
		platforms.update(heghth);


		// --drawing--

		window.clear(sf::Color(255,255,255)); // or background
		// draw objects
		window.display();
	}
}


int main()
{
	// begining
	sf::RenderWindow window(sf::VideoMode(window_width, window_heghth), "Moodle Jump");
	srand(time(nullptr));

	List_of_platforms platforms;
	platforms.init();
	
	main_cycle(window, platforms);

	return 0;
}
