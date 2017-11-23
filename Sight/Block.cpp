#include "Block.h"



Block::Block(sf::Vector2f dimensions) : sf::RectangleShape(dimensions)
{
	setFillColor(sf::Color::Red);
	setOutlineColor(sf::Color::White);
	setOutlineThickness(3);
}


Block::~Block()
{
}

bool Block::containsPoint(int x, int y) {
	return getGlobalBounds().contains(x, y);
};

sf::Vector2f* Block::getVertices() {
	sf::Vector2f vertices[4];
	vertices[0] = getTransform().transformPoint(sf::Vector2f(0, 0));
	vertices[1] = getTransform().transformPoint(sf::Vector2f(getSize().x, 0));
	vertices[2] = getTransform().transformPoint(sf::Vector2f(0, getSize().y));
	vertices[3] = getTransform().transformPoint(sf::Vector2f(getSize().x, getSize().y));
	return vertices;
}


