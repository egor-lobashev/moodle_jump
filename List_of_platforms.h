#include "List.h"
#include <random>

const int window_heghth = 600, window_width = 200,
		platform_heghth = 10, platform_width = 30,
		platforms_rate = 100;


class List_of_platforms: public List
{
private:
	bool initialized = false;
	int previous_heighth = 0;

	void move_platforms(int heghth)
	{
		int dy = heghth - previous_heighth;
		previous_heighth = heghth;

		for (int i = this->length()-1; i >= 0; --i)
		{
			this->find(i).y += dy;
			if (this->find(i).y > window_heghth)
			{
				this->pop(i);
			}
		}
	}

	void generate(int heghth)
	{
		while (heghth - revealed > -platform_heghth)
		{
			if (std::rand()%100 <= platforms_rate)
			{
				int x = std::rand() % (window_width - platform_width);
				this->push_front(Platform(x, heghth - revealed, 0));
			}
			revealed += platform_heghth;
		}
	}

public:
	int revealed = -window_heghth;

	void init()
	{
		generate(0);
	}

	void update(int heghth)
	{
		move_platforms(heghth);
		generate(heghth);
	}
};
