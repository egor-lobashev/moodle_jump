#include "List.h"
#include <random>


class List_of_platforms
{
private:
	bool initialized = false;
	int previous_height = 0, speed = 1;

	void move_platforms(int height, float dt)
	{
		int dy = height - previous_height;
		std::cout << dy << "\n";
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

	void generate(int height)
	{
		while (height - revealed > -platform_height)
		{
			if (std::rand()%100 <= platforms_rate)
			{
				int x = std::rand() % (window_width - platform_width);
				int kind_randomizer = random() % 100;
				int kind;
				int v = speed*(random()%2 == 1 ? 1 : -1);

				if (kind_randomizer <= 10) kind = 1;
				else if (kind_randomizer <= 30) kind = 2;
				else kind = 0;

				Platform* new_platform = new Platform(x, height - revealed, kind, v);
				list.push_front(new_platform);
			}
			revealed += platform_height;
		}
	}

public:
	List list;
	int revealed = -window_height;

	void init()
	{
		generate(0);
		init_platform_sprites();
	}

	void update(int height, float dt)
	{
		move_platforms(height, dt);
		generate(height);
	}
};
