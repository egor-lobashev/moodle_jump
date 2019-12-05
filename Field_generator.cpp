#include <List.h>

class Platform // : Drawable
{
public:
	int x, y, kind;

	Platform(int x, int y, int kind)
	{
		this->x = x;
		this->y = y;
		this->kind = kind;
		this->v = 
	}

	update(int dt)
	{
		if (kind == 2)
		{
			if ((x <= 0) or (x >= max))
				vx *= -1;
			x += v*dt;
		}
	}

	draw(&&sf::RenderWindow window)
	{
		window.blit(...);
	}
}
