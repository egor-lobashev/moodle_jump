#include <SFML/Graphics.hpp>
#include <string>
#include "List_of_platforms.h"
#include "Person.h"
#include "Graphics_manager.h"


class Background: public Drawable
{
public:
	sf::Texture texture;
	sf::Sprite sprite;

	Background(const std::string& filename)
	{
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
};
	
bool is_mouse_position_in_district_of_button()
{
	int mouse_x = sf::Mouse::getPosition().x, mouse_y = sf::Mouse::getPosition().y;
	int button_x = 220, button_y = 600;

	if(mouse_x >= button_x && mouse_x <= button_x + 200 &&
	mouse_y >= button_y && mouse_y <= button_y + 50 )
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

	Background background("images/background.png");

	List_of_platforms platforms;
	Person person;

	Graphics_manager graphics_manager;
	graphics_manager.add(person);
	graphics_manager.add(platforms);
	graphics_manager.add(background);
	
	

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

		graphics_manager.draw_all(window);
		window.display();
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
