#ifndef __PLATFORMS__
#define __PLATFORMS__

#include <SFML/Graphics.hpp>

const int window_height = 650, window_width = 400,
		platform_height = 25, platform_width = 100;

class Platform
{
public:
	float x, y, v;
	int kind;
	sf::Sprite sprite;

	Platform(float x, float y, int kind, float v, sf::Sprite* platform_sprites);
	void update(float dt);
	void draw(sf::RenderWindow& window);
	void operator=(Platform& another);
};

#endif
