#ifndef __PERSON__
#define __PERSON__

#include "Drawable.h"

class Person: public Drawable {
    public:
        Person();

        void update(List_of_platforms& platforms,const float& dt,float& height,const int& window_height);
        void draw(sf::RenderWindow& window);
        float get_y_position();
        float get_Vy_speed();
    private:
        float x_position = 160, y_position = 640,
                Vy = -1200, acceleration = 1100;
        const float person_width = 80 , person_height = 90,
                    Vy_value_after_jumping = -700;

        bool right_direction_of_moodler = false;
        sf::Texture texture_of_left_direction , texture_of_right_direction;
        sf::Sprite sprite_of_left_direction , sprite_of_right_direction;
        void recalculate_screen_position(float& height,const float& dt);
        void jump(List_of_platforms& platforms);
        bool is_collide_with_platform(List_of_platforms& platforms);
        void refresh_x_position_if_button_of_moving_is_pressed(float dt);
        void fly(const float& dt);
};

#endif
