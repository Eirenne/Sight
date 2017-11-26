#pragma once
# include <SFML\Graphics.hpp>

// Dot Product

float dot(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

// Cross Product
float cross(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.y - a.y * b.x;
};
