#pragma once
#include "Block.h"
#include <SFML/Graphics.hpp>
class BlockUnity
{
public:
	BlockUnity();
	void addBlock(sf::Vector2f dimensions = sf::Vector2f(30,30), int x = 50, int y = 50);
	~BlockUnity();
	void draw(sf::RenderWindow *window);
	int getSize();
	std::vector<sf::Vector2f> getVertices();

private:
	std::vector<Block> blocks;


};

