#pragma once

#include <SFML/Graphics.hpp>
#include "Line.h"
class Obstacles
{
public:
	Obstacles();
	void addLine(sf::Vector2f pointA, sf::Vector2f pointB);
	~Obstacles();
	void draw(sf::RenderWindow &window);

private:
	std::vector<Line> lines{};
};

