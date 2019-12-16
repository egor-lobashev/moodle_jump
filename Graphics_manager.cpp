#include "Graphics_manager.h"


void Graphics_manager::draw_all(sf::RenderWindow& window)
{
	int len = objects.length();

	for (int i = 0; i < len; ++i)
	{
		objects[i].draw(window);
	}
}

void Graphics_manager::add(Drawable& new_object)
{
	objects.push_front(new_object);
}

void Graphics_manager::remove(Drawable& rm_object)
{
	objects.remove(rm_object);
}
