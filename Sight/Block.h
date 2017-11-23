#pragma once
#include <SFML/Graphics.hpp>
class Block : public sf::RectangleShape
{
public:
	Block(sf::Vector2f dimensions = sf::Vector2f(30, 30));
	~Block();
	bool containsPoint(int x, int y);
	sf::Vector2f * getVertices();
};

