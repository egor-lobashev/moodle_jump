#include <stdio.h>
#include <iostream>

const int window_height = 600, window_width = 200,
		platform_height = 10, platform_width = 30,
		platforms_rate = 100;


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
/*
	draw(&sf::RenderWindow window)
	{
		window.blit(...);
	}
*/
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
