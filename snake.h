#pragma once


class Body
{
private:
	int pos_x_m, pos_y_m;
	int pos_x_past_m, pos_y_past_m;
public:
	Body(int x=0, int y=0); //gotowe
	int pos_x();		//gotowe
	int pos_y();		//gotowe
	int past_pos_x();	//gotowe
	int past_pos_y();	//gotowe
	void Move(const Body & k);	//gotowe
protected:
	void add_x(int x);		//gotowe
	void add_y(int y);		//gotowe
	void set_x(int x);		//gotowe
	void set_y(int y);		//gotowe
};


enum kierunki{LEFT=-2,DOWN=-1,STAY=0,RIGHT=2,UP=1};
class Snake: public Body
{
	int speed_m;
	int win_size_x_m, win_size_y_m;
	kierunki dir_m;

public:
	Snake(int s_pos_x=0,int s_pos_y=0, int s_speed=8, const int win_width=400, const int win_hight=300);	//gotowe
	~Snake();
	void Move();		//gotowe
	void dir(kierunki a);	//gotowe
	
};

class Window
{
private:
	struct Node
	{
		Body *item;
		struct Node* next;
	};
	int size_window_x_m;
	int size_window_y_m;
	int size_Snake_m;
	Snake *head_m;
	Node * first_m;
	Node * last_m;
	int number_of_parts_m;
	bool Colision();
public:
	Window(int size_x=400, int y=400);
	int Width();
	int Hight();
	void Add_new();
	void Move();
	int Size();
	int Snake_pos_x();
	int Snake_pos_y();
	int * Body_pos_x();
	int * Body_pos_y();
	int How_many_parts();
	void dir(kierunki a);
	int Score() { return number_of_parts_m;}
	bool Win(int max_score = 10) { return number_of_parts_m >= max_score; }
	bool lose() { return Colision(); }
	~Window();


};






