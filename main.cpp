#include "SFML/Graphics.hpp"
#include<iostream>
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include<cstdlib>
#include<time.h>
#include<vector>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(600, 400), "Rain");

	//rain
	RectangleShape drop;
	drop.setFillColor(Color::White);
	drop.setSize(Vector2f(1.f, 10.f));
	drop.rotate(30);

	std::vector<RectangleShape> drops;
	drops.push_back(RectangleShape(drop));
	int dropSpawnTimer = 0;

	//Rain angle movement shoud be the same as drop position ("drop.rotate")
	int A = 30;
	float angle = A / 90;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (dropSpawnTimer < 200)
			dropSpawnTimer++;

		if (dropSpawnTimer >= 200)
		{
			drop.setPosition((rand() % int(window.getSize().x + 300)), 0.f);
			drops.push_back(RectangleShape(drop));

			dropSpawnTimer = 0;
		}

		for (size_t i = 0; i < drops.size(); i++)
		{
			drops[i].move(0.05f * -cos(angle), 0.05f * cos(angle));
			if (drops[i].getPosition().y > window.getSize().y)
				drops.erase(drops.begin() + i);
		}

		window.clear(Color::Black);
		for (size_t i = 0; i < drops.size(); i++)
		{
			window.draw(drops[i]);
		}
		window.display();
	}

	return 0;
}