#include <SFML/Graphics.hpp>
#include "List_of_platforms.h"
#include "vector2I.h"
#include "Person.h"


bool is_mouse_position_in_district_of_button(){

	vector2I mouse = {sf::Mouse::getPosition().x, sf::Mouse::getPosition().y};
	vector2I button = {220,660};

	if(mouse.x >= button.x && mouse.x <= button.x + 200 &&
		mouse.y >= button.y && mouse.y <= button.y + 50 )
		{
			return true;
		}

	return false;

}


void update_all_objects(List_of_platforms& platforms,Person& person,float& height,float dt){
	platforms.update(height,dt);
	person.update(platforms,dt,height,window_height);
}


void draw_all_objects(sf::RenderWindow& window,List_of_platforms& platforms,Person& person,sf::Sprite& background){

	window.clear(); 
			
	window.draw(background);
	platforms.draw(window);
	person.draw(window);
	
	window.display();
}


bool is_losing_game(float y_position_of_moodler){
	if(y_position_of_moodler >= window_height){
		return true;
	}

	return false;
}


void menu(sf::RenderWindow& window)
{
	sf::Texture for_pressed_button, for_not_pressed_button;
	sf::Sprite pressed_button , not_pressed_button;

	for_pressed_button.loadFromFile("images/menu_pressed.png");
	for_not_pressed_button.loadFromFile("images/menu.png");

	not_pressed_button.setTexture(for_not_pressed_button);
	pressed_button.setTexture(for_pressed_button);

	bool mouse_is_pressed = false;
	bool mouse_was_pressed = false;


	while (window.isOpen())
	{
		mouse_was_pressed = mouse_is_pressed;
		mouse_is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		if (is_mouse_position_in_district_of_button())
		{
			if ((not mouse_is_pressed) and mouse_was_pressed)
				return;
			window.draw(pressed_button);
		} else 
			window.draw(not_pressed_button);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();
			}	   
		}
		window.display();
	}
}


void main_cycle(sf::RenderWindow& window)
{
	float height = 0;
	sf::Clock clock;

	sf::Texture background_texture;
	background_texture.loadFromFile("images/background.png");
	sf::Sprite background;
	background.setTexture(background_texture);

	List_of_platforms platforms;
	Person person;

	while (window.isOpen())
	{
		float dt = clock.getElapsedTime().asSeconds();
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();
			}	   
		}

		if(is_losing_game(person.get_y_position())){
			break;
		}

		update_all_objects(platforms,person,height,dt);
		draw_all_objects(window,platforms,person,background);
	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Moodle Jump");
	srand(time(nullptr));

	while (window.isOpen())
	{
		menu(window);
		main_cycle(window);
	}

	return 0;
}
