#pragma once
# include <SFML\Graphics.hpp>

// Dot Product

inline float dot(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.x + a.y * b.y;
}

// Cross Product
inline float cross(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.y - a.y * b.x;
};


// squared distance between two points
inline float distance_squared(sf::Vector2f a, sf::Vector2f b)
{
	return dot(a-b,a-b);
};
