#include <cmath>

struct vector2I{

vector2I(){

x = 0;
y = 0;

}
vector2I(float x , float y){

this->x = x;
this->y = y;

}
vector2I operator+(vector2I vec){

return{x+vec.x,y+vec.y};

}
vector2I operator*(float const1){

x*= const1;
y*= const1;

}
vector2I operator/(float const1){

x/= const1;
y/= const1;

}
void operator=(vector2I vec){

this->x=vec.x;
this->y=vec.y;

}
vector2I to_proect_this_vector_on(vector2I vec){

float cos = (x*vec.x+y*vec.y)/((sqrt(x*x+y*y)*sqrt(vec.x*vec.x+vec.y*vec.y)));
float norm_of_first_vector = sqrt(x*x+y*y);
float norm_of_second_vector = sqrt(vec.x*vec.x+vec.y*vec.y);

return{norm_of_first_vector*cos*vec.x/norm_of_second_vector,norm_of_first_vector*cos*vec.y/norm_of_second_vector};
}

bool operator==(vector2I vector){
if(this->x == vector.x && this->y == vector.y){

return true;
}
else return false;
}

int x = 0,
y = 0;

};
