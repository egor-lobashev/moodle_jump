#ifndef __DRAWABLE__
#define __DRAWABLE__

#include <SFML/Graphics.hpp>


class Drawable
{
public:
	virtual void draw(sf::RenderWindow& window) = 0;
};

#endif
