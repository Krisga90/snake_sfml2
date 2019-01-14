#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "snake.h"
#include "apple.h"
int main()
{

	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
	window.setVerticalSyncEnabled(1);
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	sf::Vector2i a(window.getSize());
	Window waz = Window(a.x, a.y);
	
	Apple * jablko;
	jablko = new Apple(a.x, a.y, 30);

	sf::RectangleShape shape_waz(sf::Vector2f(waz.Size(), waz.Size()));
	sf::RectangleShape shape_apple(sf::Vector2f(jablko->Size(), jablko->Size()));
	sf::RectangleShape shape_apple2(sf::Vector2f(2, 2));
	int korekta_waz = waz.Size() / 2;
	int korekta_jablko = jablko->Size() / 2;
	shape_waz.setPosition(sf::Vector2f(waz.Snake_pos_x(),waz.Snake_pos_y()));
	shape_waz.setFillColor(sf::Color::Green);

	shape_apple.setPosition(sf::Vector2f(jablko->Pos_x(), jablko->Pos_y()));
	shape_apple.setFillColor(sf::Color::Red);
	
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Down:
					waz.dir(DOWN);
					break;
				case sf::Keyboard::Up:
					waz.dir(UP);
					break;
				case sf::Keyboard::Left:
					waz.dir(LEFT);
					break;
				case sf::Keyboard::Right:
					waz.dir(RIGHT);
					break;
				case sf::Keyboard::A:
					std::cout << "waz pos x: " << waz.Snake_pos_x();
					std::cout << "\twaz pos y: " << waz.Snake_pos_y();
					std::cout << "\tjablko pos x: " << jablko->Pos_x();
					std::cout << "\tjablko pos y: " << jablko->Pos_y();
					std::cout << std::endl;
					sf::sleep(sf::seconds(4));
					break;
					
				}
			}
			
		}

		waz.Move();
		int * temp_x = waz.Body_pos_x();
		int * temp_y = waz.Body_pos_y();
		if (jablko->Colision(waz.Snake_pos_x(),waz.Snake_pos_y(), waz.Size()/2))
		{
			waz.Add_new();
			waz.Add_new();
			waz.Add_new();
			waz.Add_new();
			waz.Add_new();

			delete jablko;
			jablko = new Apple(a.x, a.y, 30);
		}
		/*
		for (int i = 0; i < waz.How_many_parts(); i++)
		{
			std::cout << temp_x[i] << "\t" << temp_y[i] << "\n";
		}
		*/
		window.clear();

		for (int i = 0; i < waz.How_many_parts(); i++)
		{
			shape_waz.setPosition(sf::Vector2f(temp_x[i]-korekta_waz, temp_y[i] - korekta_waz));
			shape_waz.setFillColor(sf::Color::Green);
			window.draw(shape_waz);
		}
	
		shape_apple.setPosition(sf::Vector2f (jablko->Pos_x() - korekta_jablko +1, jablko->Pos_y() - korekta_jablko+1));
		shape_apple.setFillColor(sf::Color::Red);
		window.draw(shape_apple);
		shape_apple2.setPosition(sf::Vector2f(jablko->Pos_x(), jablko->Pos_y()));
		shape_apple2.setFillColor(sf::Color::Blue);
		window.draw(shape_apple2);
		if (waz.lose())
		{
			std::cout << "Koniec gry\n";
			std::cout << "Wynik: " << waz.Score();
			window.close();
			break;
		}
		delete[] temp_x;
		delete[] temp_y;
		window.display();
		sf::sleep(sf::milliseconds(10+int((1000+ waz.Score())/ (10+waz.Score()))));
	}

	std::cin.get();
	return 0;
}