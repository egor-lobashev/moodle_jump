#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
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
	
bool mouse_in_rect(sf::RenderWindow& window, int button_x, int button_y, int button_w, int button_h)
{
	int mouse_x = sf::Mouse::getPosition(window).x, mouse_y = sf::Mouse::getPosition(window).y;

	if((mouse_x >= button_x) && (mouse_x <= button_x + button_w) &&
		(mouse_y >= button_y) && (mouse_y <= button_y + button_h))
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


class Record
{
public:
	std::string name;
	int result;

	Record(std::string name, int result)
	{
		this->name = name;
		this->result = result;
	}
};


void rewrite_record(std::string name, int result)
{
	Record* records[10] = {nullptr};
	std::ifstream file("records");

	if (file)
	{
		std::string table, current_name, current_result;

		int i;
		for (i = 0; i < 10; ++i)
		{
			file >> current_name >> current_result;
			if (file.eof())
			{
				break;
			}
			Record* record = new Record(current_name, std::stoi(current_result));
			records[i] = record;
		}

		bool found_player = false;
		for (int j = 0; j < i; ++j)
		{	
			if ((records[j]->name == name) and (records[j]->result < result))
			{
				records[j]->result = result;
				found_player = true;
				break;
			}
		}

		if (not found_player)
		{
			if (i < 9)
			{
				Record* new_record = new Record(name, result);
				records[i+1] = new_record;
			}
			int min = 0;
			int min_number = -1;
			for (int j = 0; j < i; ++j)
			{
				if (records[j]->result < min)
				{
					min = records[j]->result;
					min_number = j;
				}
			}

			if (min_number != -1)
			{
				records[min_number]->name = name;
				records[min_number]->result = result;
			}
		}

		for (i = 0; i < 10; ++i)
			delete records[i]; 
	}

	file.close();

	std::ofstream out_file("records");

	for (int i = 0; (i < 10) and (records[i] != nullptr); ++i)
	{
		out_file << records[i]->name.c_str() << ' ' << records[i]->result << std::endl;
	}

	out_file.close();
};


int menu(sf::RenderWindow& window)
{
	sf::Texture for_not_pressed, for_pressed_play, for_pressed_records;
	sf::Sprite not_pressed, pressed_play, pressed_records;

	for_not_pressed.loadFromFile("images/menu.png");
	for_pressed_play.loadFromFile("images/menu_play.png");
	for_pressed_records.loadFromFile("images/menu_records.png");

	not_pressed.setTexture(for_not_pressed);
	pressed_play.setTexture(for_pressed_play);
	pressed_records.setTexture(for_pressed_records);

	bool mouse_is_pressed = false;
	bool mouse_was_pressed = false;

	while (window.isOpen())
	{
		mouse_was_pressed = mouse_is_pressed;
		mouse_is_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

		if (mouse_in_rect(window, 100, 550, 200, 50))
		{
			if ((not mouse_is_pressed) and mouse_was_pressed)
				return 0;
			window.draw(pressed_play);
		}
		else if (mouse_in_rect(window, 50, 450, 300, 50))
		{
			if ((not mouse_is_pressed) and mouse_was_pressed)
				return 1;
			window.draw(pressed_records);
		} else 
			window.draw(not_pressed);

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


void draw_string(sf::RenderWindow& window, std::string txt)
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text_surface(txt, font, 30);
	text_surface.setFont(font);
	text_surface.setPosition(20, 20);
	text_surface.setFillColor(sf::Color::Black);
	window.draw(text_surface);
}


void records(sf::RenderWindow& window)
{
	Background background("images/background.png");

	std::ifstream file("records");

	background.draw(window);

	if (file)
	{
		std::string table, name, record;
		for (int i = 0; i < 10; ++i)
		{
			file >> name >> record;
			if (file.eof())
				break;
			table += '\n' + name + ' ' + record;
		}
		draw_string(window, table);
	}
	file.close();
	window.display();

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed){
				return;
			}
		}
	}
}


void main_cycle(sf::RenderWindow& window, std::string player_name)
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
			rewrite_record(player_name, height);
			break;
		}

		update_all_objects(platforms,person,height,dt);

		graphics_manager.draw_all(window);
		window.display();
	}
}


int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Moodle Jump");
	srand(time(nullptr));

	std::string player_name = (argc > 1 ? argv[1] : "moodler");

	while (window.isOpen())
	{
		int choice = menu(window);
		if (choice == 0)
			main_cycle(window, player_name);
		else if (choice == 1)
			records(window);
	}

	return 0;
}
