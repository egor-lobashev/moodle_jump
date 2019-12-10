#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>


const int window_height = 600, window_width = 200,
		platform_height = 10, platform_width = 30,
		platforms_rate = 100;

const sf::Sprite platform_sprites[3];


void init_platform_sprites()
{
	for (int i = 0; i<3; ++i)
	{
		sf::Image image;
		image.loadFromFile("platform_" + i + ".png");
		sf::Texture texture;
		texture.loadFromImage(background);
		platform_sprites[i].setTexture(background_texture);
	}
}


class Platform // : Drawable
{
public:
	int x, y, v, kind;

	Platform(int x, int y, int kind, int v)
	{
		this->x = x;
		this->y = y;
		this->kind = kind;
		this->v = v;
	}

	void update(float dt)
	{
		if (kind == 2)
		{
			if ((x < 0) or (x > window_width - platform_width))
				v *= -1;
			x += v * dt;
		}
	}

	draw(&sf::RenderWindow window)
	{
		sprite.setPosition(x,y);
		window.draw(platform_sprites[i]);
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
