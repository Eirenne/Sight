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
	size_t getSize();
	std::vector<sf::Vector2f> getVertices();
	std::vector < std::pair < sf::Vector2f, sf::Vector2f >> BlockUnity::getWalls();

private:
	std::vector<Block> blocks;


};

