#include "LightSource.h"



LightSource::LightSource(float 	radius,
		unsigned int 	pointCount
	) :CircleShape(radius, pointCount) 
{
	
}


LightSource::~LightSource()
{
}

bool LightSource::containsPoint(int x, int y) {
	float r = getRadius();
	sf::Vector2f pos = getPosition();

	return ((x - (pos.x + r)) * (x - (pos.x + r)) + (y - (pos.y + r)) * (y - (pos.y + r))) < r * r;
};
