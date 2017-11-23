#pragma once

#include <SFML/Graphics.hpp>
class LightSource : public sf::CircleShape
{
public:
	LightSource(float 	radius = 0,
		unsigned int 	pointCount = 30
	);
	~LightSource();
	bool containsPoint(int x, int y);

private:
};

