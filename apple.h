#pragma once


class Object
{
private:
	int pos_x_m;
	int pos_y_m;
	int size_m;
public:
	Object(int width, int hight, int size =20);
	virtual bool Colision(int x, int y, int size);
	int Size();
	int Pos_x() { return pos_x_m; }
	int Pos_y() { return pos_y_m; }
};

class Apple : public Object
{
public:
	Apple(int width, int hight, int size=20);
	virtual bool Colision(int x, int y, int size);
	~Apple();
	int Pos_x() { return Object::Pos_x(); }
	int Pos_y() { return Object::Pos_y(); }
};

