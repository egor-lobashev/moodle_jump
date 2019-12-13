#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

const int window_height = 650, window_width = 400,
		platform_height = 25, platform_width = 100,
		platforms_rate = 100;


class Platform
{
public:
	float x, y, v;
	int kind;
	sf::Sprite sprite;

	Platform(float x, float y, int kind, float v, sf::Sprite* platform_sprites)
	{
		this->x = x;
		this->y = y;
		this->kind = kind;
		this->v = v;
		sprite = platform_sprites[kind];
	}
	

	void update(float dt)
	{
		if (kind == 2)
		{
			if (((x <= 0) and (v < 0)) or ((x >= window_width - platform_width) and (v > 0)))
				v *= -1;
			x += v * dt;
		}
	}

	void draw(sf::RenderWindow& window)
	{
		sprite.setPosition(x,y);
		window.draw(sprite);
	}

	void print()
	{
		printf("(%d, %d, %d)", x, y, kind);
	}

	void operator=(Platform& another)
	{
		this->x = another.x;
		this->y = another.y;
		this->kind = another.kind;
		this->v = another.v;
	}
};
