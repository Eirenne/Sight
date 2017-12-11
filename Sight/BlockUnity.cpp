#include "BlockUnity.h"



BlockUnity::BlockUnity()
{
}


BlockUnity::~BlockUnity()
{
}

void BlockUnity::addBlock(sf::Vector2f dimensions, int x, int y) {
	Block a(dimensions);
	a.setPosition(x, y);
	blocks.push_back(a);
}

void BlockUnity::draw(sf::RenderWindow *window) {
	for (auto value : blocks) {
		window->draw(value);
		sf::VertexArray points(sf::Points, 3);
		std::vector<sf::Vector2f> temp = value.getVertices();
		for (int i = 0; i < 4; i++) {
			sf::Vertex vertex;

			// set its position
			vertex.position = sf::Vector2f(temp[i].x, temp[i].y);

			// set its color
			vertex.color = sf::Color::Black;

			points.append(vertex);
		}
		window->draw(points);
	}
}

size_t BlockUnity::getSize() {
	return blocks.size();
}

std::vector<sf::Vector2f> BlockUnity::getVertices() {
	std::vector<sf::Vector2f> vec;
	for (auto value : blocks) {
		std::vector<sf::Vector2f> temp = value.getVertices();
		for (int i = 0; i < 4; i++) {
			vec.push_back(temp[i]);
		}
	}
	return vec;
}

std::vector < std::pair < sf::Vector2f, sf::Vector2f >> BlockUnity::getWalls() {
	std::vector<std::pair < sf::Vector2f, sf::Vector2f >> vec;
	for (auto value : blocks) {
		std::vector<std::pair < sf::Vector2f, sf::Vector2f >> temp = value.getWalls();
		for (int i = 0; i < 4; i++) {
			vec.push_back(temp[i]);
		}
	}
	return vec;
}
