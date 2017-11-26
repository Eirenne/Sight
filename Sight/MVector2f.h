#pragma once

#include <SFML/Graphics.hpp>
class MVector2f : public sf::Vector2f
{
public:
	MVector2f();
	MVector2f(float x, float y);

	~MVector2f();
};

