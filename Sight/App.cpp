#include "App.h"

void OnButtonClick() {
	std::cout << "WORLD" << std::endl;
}





App::App() : window(sf::VideoMode(WIDTH, HEIGHT), "Sight", sf::Style::Close)
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
	initialize_gui();	
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
		desktop.HandleEvent(event);
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void App::update()
{
}

void App::render()
{

	desktop.Update(1.0f);
	window.clear(sf::Color(63, 81, 181));

	unity.draw(&window);
	window.draw(source);
	gui.Display(window);
	window.display();
}




void App::initialize_gui() {
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
	auto button = sfg::Button::Create("Hello");
	button->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind(&OnButtonClick)
	);

	box->Pack(button);

	box->Pack(sfg::Separator::Create());

	radio_button1 = sfg::RadioButton::Create("Either this");
	radio_button2 = sfg::RadioButton::Create("Or this", radio_button1->GetGroup());
	radio_button3 = sfg::RadioButton::Create("Or maybe even this", radio_button1->GetGroup());

	radio_button3->SetActive(true);

	auto button_select = [&] {
		if (radio_button1->IsActive()) {
			my_window->SetTitle("First button selected");
		}
		else if (radio_button2->IsActive()) {
			my_window->SetTitle("Second button selected");
		}
		else if (radio_button3->IsActive()) {
			my_window->SetTitle("Third button selected");
		}
	};

	radio_button1->GetSignal(sfg::ToggleButton::OnToggle).Connect(button_select);
	radio_button2->GetSignal(sfg::ToggleButton::OnToggle).Connect(button_select);
	radio_button3->GetSignal(sfg::ToggleButton::OnToggle).Connect(button_select);

	box->Pack(radio_button1);
	box->Pack(radio_button2);
	box->Pack(radio_button3);


	my_window = sfg::Window::Create(sfg::Window::BACKGROUND);
	my_window->SetTitle("Hello world!");
	my_window->SetPosition(sf::Vector2f(50.f, 50.f));
	my_window->Add(box);

	desktop.Add(my_window);
}
