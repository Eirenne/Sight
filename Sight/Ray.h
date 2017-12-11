#pragma once

#include <SFML/Graphics.hpp>
#include "VecProducts.h"
#include "approximation.h"
class Ray
{
public:
	Ray(sf::Vector2f pos, sf::Vector2f dir);
	~Ray();
	bool intersects(sf::Vector2f start, sf::Vector2f end, sf::Vector2f &intersection);

	sf::Vector2f position;
	sf::Vector2f direction;

};

