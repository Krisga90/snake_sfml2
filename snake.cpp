#include "Snake.h"
#include <iostream>

const int SPEED = 20;
//metody klasy Body

Body::Body(int x, int y)
{
	pos_x_past_m=pos_x_m = x;
	pos_y_past_m=pos_y_m = y;
}
//gotowe

int Body::pos_x()
{
	return pos_x_m;
}
//gotowe

int Body::pos_y()
{
	return pos_y_m;
}
//gotowe



int Body::past_pos_x()
{
	return pos_x_past_m;
}
//gotowe

int Body::past_pos_y()
{
	return pos_x_past_m;

}
//gotowe


void Body::Move(const Body & k)
{
	pos_x_past_m = pos_x_m;
	pos_x_m = k.pos_x_past_m;
	pos_y_past_m = pos_y_m;
	pos_y_m = k.pos_y_past_m;

}
//gotowe

/*
void Body::Move(Snake & s)
{
	pos_x_past_m = pos_x_m;
	pos_x_m = s.past_pos_x();
	pos_y_past_m = pos_y_m;
	pos_y_m = s.past_pos_y();
}
*/

void Body::add_x(int x)
{
	pos_x_past_m = pos_x_m;
	pos_x_m += x;
	pos_y_past_m = pos_y_m;
}

void Body::add_y(int y)
{
	pos_y_past_m = pos_y_m;
	pos_y_m += y;
	pos_x_past_m = pos_x_m;
}

void Body::set_x(int x)
{
	pos_x_m = x;
}

void Body::set_y(int y)
{
	pos_y_m = y;
}

//gotowe


//metody klasy Snake

Snake::Snake(int s_pos_x, int s_pos_y, int s_speed, const int win_width, const int win_hight)
	:Body(s_pos_x,s_pos_y)
{
	dir_m = STAY;
	speed_m = s_speed;
	win_size_x_m = win_width;
	win_size_y_m = win_hight;
}

/*
Snake::Snake(int pos_x, int pos_y, int size_x, int size_y, kierunki dir, int speed, int nr)
{
	dir_m = dir;
	switch (dir)
	{
	case LEFT:
		pos_x_m = pos_x + size_x;
		pos_y_m = pos_y;
		break;
	case RIGHT:
		pos_x_m = pos_x - size_x;
		pos_y_m = pos_y;
		break;
	case DOWN:
		pos_x_m = pos_x ;
		pos_y_m = pos_y-size_y;
		break;
	case UP:
		pos_x_m = pos_x;
		pos_y_m = pos_y+size_y;
		break;

	}
	speed = 1;
	size_x_m = size_y_m = 5;
	nr_segmentu_m = 1;
}
*/


Snake::~Snake()
{
}


void Snake::Move()
{
	if (dir_m == LEFT || dir_m == RIGHT)
	{
		add_x( speed_m * int(dir_m) / 2);
		if (pos_x() < 0)
			 set_x(win_size_x_m);
		else if (pos_x() > win_size_x_m)
			set_x(0);
	}

	else if (dir_m == UP || dir_m == DOWN)
	{
		add_y( speed_m * -int(dir_m));
		if (pos_y() < 0)
			set_y(win_size_y_m);
		else if (pos_y() > win_size_y_m)
			set_y(0);
	}
}

void Snake::dir(kierunki a)
{
	switch (a)
	{
	case LEFT:
		if (dir_m != RIGHT)
			dir_m = LEFT;
		break;
	case DOWN:
		if (dir_m != UP)
			dir_m = DOWN;
		break;
	case UP:
		if (dir_m != DOWN)

			dir_m = UP;
		break;
	case RIGHT:
		if (dir_m != LEFT)
			dir_m = RIGHT;
		break;
	}
} 
//zrobione

//metody klasy Window

Window::Window(int size_x , int size_y )
{
	size_Snake_m = SPEED;
	int pos_x = size_x / 2;
	int pos_y = size_y / 2;
	Node * add = new Node;
	head_m = new Snake(pos_x, pos_y, SPEED, size_x, size_y);
	first_m=last_m = nullptr;
	number_of_parts_m = 1;
}

int Window::Width()
{
	return size_window_x_m;
}

int Window::Hight()
{
	return size_window_y_m;
}

void Window::Add_new()
{
	if (last_m != nullptr)
	{
		Node * add = new Node;
		add->next = nullptr;
		add->item = new Body(last_m->item->past_pos_x(), last_m->item->past_pos_y());
		last_m->next = add;
		last_m = add;
		last_m->next = nullptr;
		number_of_parts_m++;
	}
	 else if (first_m == nullptr)
	{
		Node * add = new Node;
		add->next = nullptr;
		add->item = new Body(head_m->past_pos_x(),head_m->past_pos_y());
		first_m = add;
		number_of_parts_m++;

	}
	else
	{
		Node * add = new Node;
		add->next = nullptr;
		add->item = new Body(first_m->item->past_pos_x(), first_m->item->past_pos_y());
		first_m->next = add;
		last_m = add;
		last_m->next = nullptr;
		number_of_parts_m++;
	}
}

Window::~Window()
{
	delete head_m;
	Node * temp;
	while (first_m!=nullptr)
	{
		temp = first_m;
		first_m = first_m->next;
		delete temp;
	}
}

void Window::Move()
{
	head_m->Move();
	Node * temp = nullptr;
	for (int i = 0; i < number_of_parts_m-1; i++)
	{

		if (i >1)
		{
			temp->next->item->Move(*temp->item);
			temp = temp->next;
		}
		else if (i == 0)
		{
			first_m->item->Move(*head_m);
			temp = first_m->next;

		}
		else
		{
			temp->item->Move(*first_m->item);
			temp =first_m->next;
		}
	}
}

int Window::Size()
{
	return size_Snake_m;
}

int Window::Snake_pos_x()
{
	return head_m->pos_x();
}

int Window::Snake_pos_y()
{
	return head_m->pos_y();
}

void Window::dir(kierunki a)
{
	head_m->dir(a);
}

int * Window::Body_pos_x()
{
	int * temp = new int[How_many_parts()];
	temp[0] = head_m->pos_x();
	if (number_of_parts_m >1)
		temp[1] = first_m->item->pos_x();
	int i = 2;
	if (number_of_parts_m > 2)
	{
		Node * temp1 = first_m->next;
		for (i = 2; i < number_of_parts_m; i++)
		{
			temp[i] = temp1->item->pos_x();
			temp1 = temp1->next;
		}
	}
	return temp;
}

int * Window::Body_pos_y()
{
	int * temp = new int[How_many_parts()];
	temp[0] = head_m->pos_y();
	if (number_of_parts_m > 1)
		temp[1] = first_m->item->pos_y();
	int i = 2;
	if (number_of_parts_m > 2)
	{
		Node * temp1 = first_m->next;
		for (i = 2; i < number_of_parts_m; i++)
		{
			temp[i] = temp1->item->pos_y();
			temp1 = temp1->next;
		}
	}
	
	return temp;
}

int Window::How_many_parts()
{
	return number_of_parts_m;
}

bool Window::Colision()
{
	bool colision=false;
	Node * temp;
	if (first_m != nullptr)
	{
		temp = first_m;
		double x_s = head_m->pos_x();
		double y_s = head_m->pos_y();
		while (temp->next != nullptr)
		{
			double x_b = temp->item->pos_x();
			double y_b = temp->item->pos_y();
			if (x_s +  size_Snake_m > x_b & x_s - size_Snake_m < x_b & y_s +  size_Snake_m > y_b & y_s -  size_Snake_m < y_b)
			{
				colision = true;
				break;
			}
			temp = temp->next;
		}
	}
	return colision;
}