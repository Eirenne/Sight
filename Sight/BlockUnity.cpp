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
	}
}

int BlockUnity::getSize() {
	return blocks.size();
}

std::vector<sf::Vector2f> BlockUnity::getVertices() {
	std::vector<sf::Vector2f> vec;
	for (auto value : blocks) {
		sf::Vector2f * temp = value.getVertices();
		for (int i = 0; i < 4; i++) {
			vec.push_back(temp[i]);
		}
	}
	return vec;
}
