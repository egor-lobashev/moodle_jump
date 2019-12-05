#include <stdio.h>

class Platform // : Drawable
{
public:
	int x, y, v, kind;

	Platform(int x, int y, int kind)
	{
		this->x = x;
		this->y = y;
		this->kind = kind;
		this->v = 1;
	}
/*
	update(int dt)
	{
		if (kind == 2)
		{
			if ((x <= 0) or (x >= max))
				vx *= -1;
			x += v*dt;
		}
	}

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
