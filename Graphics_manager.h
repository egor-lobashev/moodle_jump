#ifndef __GRAPHICS_MANAGER__
#define __GRAPHICS_MANAGER__

#include "List.h"
#include "Drawable.h"


class Graphics_manager
{
private:
	List<Drawable> objects;
public:
	void draw_all(sf::RenderWindow& window);
	void add(Drawable& new_object);
	void remove(Drawable& rm_object);
};

#endif
