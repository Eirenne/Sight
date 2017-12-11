#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include "LightSource.h"
#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Widgets.hpp>
#include "BlockUnity.h"
#include "Ray.h"
#include "Obstacles.h"

#define WIDTH 1000
#define HEIGHT 600

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
	void initialize_gui();
	void OnButtonClick();

	sf::RenderWindow window;
	LightSource source;
	BlockUnity unity;
	Obstacles obstacles;
	bool leftButtonPressed;
	sf::Shape *dragged;
	sfg::SFGUI gui;
	sfg::Desktop desktop;
	std::shared_ptr<sfg::RadioButton> radio_button1;
	std::shared_ptr<sfg::RadioButton> radio_button2;
	std::shared_ptr<sfg::RadioButton> radio_button3;
	std::shared_ptr<sfg::Window> my_window;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> walls;
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> playground_walls;
	std::vector<sf::Vector2f> playground_vertices;
	std::vector <sf::Vector2f> vertices;
	std::vector <sf::Vector2f> drawable_vertices;
};

