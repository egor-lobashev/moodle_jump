#include "List.h"
#include <random>
#include "List_of_platforms.h"


void List_of_platforms::move_platforms(float height, float dt)
{
	int dy = height - previous_height;
	
	previous_height = height;

	for (int i = list.length()-1; i >= 0; --i)
	{
		Platform& current_platform = list[i];

		current_platform.y += dy;
		current_platform.update(dt);

		if (current_platform.y > window_height)
		{
			delete &current_platform;
			list.pop(i);
		}
	}
}


void List_of_platforms::generate(float height)
{
	while (height - revealed > -30)
	{
		if ((std::rand()%100 <= 10 + 100/(0.0005*height+1)) or (since_last_normal > max_since_last_normal))
		{
			float x = std::rand() % (window_width - platform_width);
			int kind_randomizer = random() % 100;
			int kind;
			float v = ( 500-500/(0.0001*height+1) )*(random()%2 == 1 ? 1 : -1);

			if ((kind_randomizer <= 10) and (since_last_normal <= max_since_last_normal)) kind = 1;
			else if (kind_randomizer <= 100-100/(0.0001*height+1)) kind = 2;
			else kind = 0;

			if (kind != 1) since_last_normal = 0;

			Platform* new_platform = new Platform(x, height - revealed, kind, v, platform_sprites);
			list.push_front(*new_platform);
		}
		revealed += 30;
		since_last_normal += 1;
	}
}

List_of_platforms::List_of_platforms()
{
	texture_0.loadFromFile("images/platform_0.png");
	texture_1.loadFromFile("images/platform_1.png");
	texture_2.loadFromFile("images/platform_2.png");

	platform_sprites[0].setTexture(texture_0);
	platform_sprites[1].setTexture(texture_1);
	platform_sprites[2].setTexture(texture_2);

	generate(0);
}

void List_of_platforms::update(float height, float dt)
{
	move_platforms(height, dt);
	generate(height);
}

void List_of_platforms::draw(sf::RenderWindow& window)
{
	int amount_of_objects = list.length();
	for(int i = 0;i < amount_of_objects ; i++)
	{
		list[i].draw(window);
	}

}
