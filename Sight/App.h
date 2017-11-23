#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "LightSource.h"
#include "BlockUnity.h"

#define WIDTH 1000
#define HEIGHT 500

class App
{
public:
	App();
	void run();
	~App();

private:
	void processEvents();
	void update();
	void render();

	sf::RenderWindow window;
	LightSource source;
	BlockUnity unity;
	bool leftButtonPressed;
	sf::Shape *dragged;
};

