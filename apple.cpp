#include "apple.h"
#include <random>




Object::Object(int width, int hight, int size)
{
	std ::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution<int> distribution1(20, width- 20);
	std::uniform_int_distribution<int> distribution2(20, hight - 20);
	distribution1.reset();
	pos_x_m = distribution1(gen);
	distribution2.reset();
	pos_y_m = distribution2(gen);
	size_m = size;
}

bool Object::Colision(int x, int y, int size)
{
	if ((x+size ) > (pos_x_m - size_m/2) && (x- size) < (pos_x_m + size_m/2) && (y-size ) < (pos_y_m + size_m/2) &&( y+size ) > (pos_y_m - size_m/2))
		return true;
	else
		return false;

}

int Object::Size()
{
	return size_m;
}


Apple::Apple(int width, int hight, int size)
:Object(width,hight,size)
{
}

Apple::~Apple()
{
}

bool Apple::Colision(int x, int y, int size)
{
	return Object::Colision(x, y, size);
}
