#include "Platform.h"


Platform::Platform(float x, float y, int kind, float v, sf::Sprite* platform_sprites)
{
	this->x = x;
	this->y = y;
	this->kind = kind;
	this->v = v;
	sprite = platform_sprites[kind];
}

void Platform::update(float dt)
{
	if (kind == 2)
	{
		if (((x <= 0) and (v < 0)) or ((x >= window_width - platform_width) and (v > 0)))
			v *= -1;
		x += v * dt;
	}
}

void Platform::draw(sf::RenderWindow& window)
{
	sprite.setPosition(x,y);
	window.draw(sprite);
}

void Platform::operator=(Platform& another)
{
	this->x = another.x;
	this->y = another.y;
	this->kind = another.kind;
	this->v = another.v;
}
