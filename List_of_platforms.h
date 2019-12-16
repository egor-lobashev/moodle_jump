#ifndef __LIST_OF_PLATFORMS__
#define __LIST_OF_PLATFORMS__

#include "List.h"
#include "Platform.h"
#include "Drawable.h"

class List_of_platforms: public Drawable
{
private:
	bool initialized = false;
	int previous_height = 0;
	int since_last_normal = 0;
	int max_since_last_normal = 6;

	void move_platforms(float height, float dt);
	void generate(float height);

public:
	List<Platform> list;
	int revealed = -window_height;
	sf::Sprite* platform_sprites = new sf::Sprite[3];
	sf::Texture texture_0;
	sf::Texture texture_1;
	sf::Texture texture_2;
	
	List_of_platforms();
	void update(float height, float dt);
	void draw(sf::RenderWindow& window);
};

#endif
