#include "Ray.h"



Ray::Ray(sf::Vector2f pos, sf::Vector2f dir)
{
	position = pos;
	direction = dir;
}


bool Ray::intersects(sf::Vector2f start, sf::Vector2f end, sf::Vector2f &intersection) {
	sf::Vector2f OStart = start - position;
	sf::Vector2f segDirection = end - start;
	float crossDirs = cross(direction, segDirection);
	if (approximatelyEqual(crossDirs, 0.f, std::numeric_limits<float>::epsilon())) {
		return false;
	}
	float t = cross(OStart, segDirection) / crossDirs;
	float u = cross(OStart, direction) / crossDirs;
	if (definitelyLessThan(t, 0.f, std::numeric_limits<float>::epsilon()) || definitelyLessThan(u, 0.f, std::numeric_limits<float>::epsilon())
		|| definitelyGreaterThan(u, 1.f, std::numeric_limits<float>::epsilon())) {
		return false;
	}

	intersection = position + direction*t;
	return true;

}


Ray::~Ray()
{
}
