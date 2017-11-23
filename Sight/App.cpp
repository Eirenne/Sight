#include "App.h"



App::App() : window(sf::VideoMode(WIDTH, HEIGHT), "Sight")
{
	window.setFramerateLimit(60);
	source = LightSource(30);
	source.setPosition(0, 0);
	source.setFillColor(sf::Color::Yellow);
	source.setPointCount(100);
	unity.addBlock(sf::Vector2f(50, 30), 150, 60);
	unity.addBlock(sf::Vector2f(30, 70), 20, 120);
	unity.addBlock(sf::Vector2f(20, 20), 200, 200);
	leftButtonPressed = false;
	
}


App::~App()
{
}


void App::run()
{
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}


void App::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
		{

		}break;
		case sf::Event::MouseButtonPressed:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				leftButtonPressed = true;
				if (source.containsPoint(event.mouseButton.x, event.mouseButton.y)) {
					dragged = &source;
				}

				std::cout << "the left button was pressed" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl;
			}
		}break;
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				leftButtonPressed = false;
				dragged = NULL;
				std::cout << "the left button was released" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl;
			}
		}break;
		case sf::Event::MouseMoved:
		{
			if (leftButtonPressed)
			{
				if (dragged != NULL) {

					int w = dragged->getGlobalBounds().width;
					int h = dragged->getGlobalBounds().height;
					int newX = std::min(static_cast<int>(window.getSize().x - w / 2), std::max(0 + w / 2, event.mouseMove.x)) - w / 2;
					int newY = std::min(static_cast<int>(window.getSize().y - h / 2), std::max(0 + h / 2, event.mouseMove.y)) - h / 2;
					std::cout << newX << " " << newY << std::endl;
					dragged->setPosition(newX, newY);
				}
			}
		}break;
		}

		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void App::update()
{
}

void App::render()
{
	window.clear(sf::Color(63, 81, 181));

	unity.draw(&window);
	window.draw(source);

	window.display();
}
