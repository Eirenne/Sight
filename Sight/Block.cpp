#include "Block.h"



Block::Block(sf::Vector2f dimensions) : sf::RectangleShape(dimensions)
{
	setFillColor(sf::Color::Red);
	/*setOutlineColor(sf::Color::White);
	setOutlineThickness(3);*/
}


Block::~Block()
{
}

bool Block::containsPoint(int x, int y) {
	return getGlobalBounds().contains(x, y);
};

std::vector<sf::Vector2f> Block::getVertices() {
	std::vector<sf::Vector2f> vertices;
	vertices.push_back(getTransform().transformPoint(sf::Vector2f(0, 0)));
	vertices.push_back(getTransform().transformPoint(sf::Vector2f(getSize().x, 0)));
	vertices.push_back(getTransform().transformPoint(sf::Vector2f(0, getSize().y)));
	vertices.push_back(getTransform().transformPoint(sf::Vector2f(getSize().x, getSize().y)));
	return vertices;
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>> Block::getWalls() {
	sf::Transform form = getTransform();
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> walls;
	walls.push_back(std::make_pair(form.transformPoint(sf::Vector2f(0, 0)), form.transformPoint(sf::Vector2f(getSize().x, 0))));
	walls.push_back(std::make_pair(form.transformPoint(sf::Vector2f(getSize().x, 0)), form.transformPoint(sf::Vector2f(getSize().x, getSize().y))));
	walls.push_back(std::make_pair(form.transformPoint(sf::Vector2f(getSize().x, getSize().y)), form.transformPoint(sf::Vector2f(0, getSize().y))));
	walls.push_back(std::make_pair(form.transformPoint(sf::Vector2f(0, getSize().y)), form.transformPoint(sf::Vector2f(0, 0))));
	return walls;
}


