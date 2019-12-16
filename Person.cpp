#include <SFML/Graphics.hpp>
#include "List_of_platforms.h"
#include "Person.h"


Person::Person(){
    
    texture_of_left_direction.loadFromFile("images/moodler_left_direction.png");
    texture_of_right_direction.loadFromFile("images/moodler_right_direction.png");

    sprite_of_left_direction.setTexture(texture_of_left_direction);
    sprite_of_right_direction.setTexture(texture_of_right_direction);

}

void Person::update(List_of_platforms& platforms,const float& dt,float& height,const int& window_height){

    jump(platforms);
    refresh_x_position_if_button_of_moving_is_pressed(dt);
    if ( y_position >= 300 || Vy > 0 ){
        fly(dt);
    }
    else{
        recalculate_screen_position(height,dt);
    }

}

void Person::draw(sf::RenderWindow& window){

    if(right_direction_of_moodler){
        
        sprite_of_right_direction.setPosition(x_position,y_position);
        window.draw(sprite_of_right_direction);

    }
    else{

        sprite_of_left_direction.setPosition(x_position,y_position);
        window.draw(sprite_of_left_direction);

    }
}

float Person::get_y_position(){
    return y_position;
}

float Person::get_Vy_speed(){
    return Vy;
}

void Person::recalculate_screen_position(float& height,const float& dt){

    height-=Vy*dt; 
    Vy += acceleration*dt;

}

void Person::jump(List_of_platforms& platforms){

    if(is_collide_with_platform(platforms) && Vy >= 0){
        Vy = Vy_value_after_jumping;
        
    }
}

bool Person::is_collide_with_platform(List_of_platforms& platforms){

    int len_of_list = platforms.list.length();

    for(int i = 0 ; i < len_of_list ; ++i){
        
        
    
        if(x_position + person_width >= platforms.list[i].x && x_position <= platforms.list[i].x + platform_width &&
          y_position + person_height >= platforms.list[i].y && platforms.list[i].y + platform_height >= y_position + person_height )
          { 
              if(platforms.list[i].kind == 1 && Vy >= 0){
                
                    platforms.list.pop(i);
                    return false;

              }
                return true;
                
          }
        
    }
    return false;
}

void Person::refresh_x_position_if_button_of_moving_is_pressed(float dt){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if(x_position + person_width/2 <= window_width ){
            this->x_position += 200*dt;
            right_direction_of_moodler = true;
        }else{
            x_position = -person_width/2;
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if( x_position + person_width/2 >= 0 ){
            this->x_position -= 200*dt;
            right_direction_of_moodler = false;
        }else{
            x_position = window_width - person_width/2;
        }
    }       
}

void Person::fly(const float& dt){
    
    Vy += acceleration*dt;
    y_position += Vy*dt;

}
