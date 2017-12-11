#include "Obstacles.h"



Obstacles::Obstacles()
{
}


Obstacles::~Obstacles()
{
}

void Obstacles::addLine(sf::Vector2f pointA, sf::Vector2f pointB)
{
	lines.push_back(Line(pointA, pointB));
}

void Obstacles::draw(sf::RenderWindow &window)
{
	for (auto value : lines) {
		value.draw(window, sf::RenderStates::Default);
	}
}
