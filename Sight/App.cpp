#include "App.h"



void App::OnButtonClick() {
	for (auto value : walls) {
		std::cout << value.first.x << " " << value.first.y << " to " << value.second.x << " " << value.second.y << std::endl;
	}
}

App::App() 
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "Sight", sf::Style::Close, settings);
	
	window.setFramerateLimit(60);
	source = LightSource(10);
	source.setPosition(0, 0);
	source.setFillColor(sf::Color::Yellow);
	source.setPointCount(100);
	obstacles.addLine(sf::Vector2f(50, 30), sf::Vector2f(120, 40));
	obstacles.addLine(sf::Vector2f(80, 120), sf::Vector2f(120, 90));
	obstacles.addLine(sf::Vector2f(0, 0), sf::Vector2f(50, 30));
	obstacles.addLine(sf::Vector2f(100, 123), sf::Vector2f(66, 42));
	playground_walls.push_back(std::make_pair(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, 0)));
	playground_walls.push_back(std::make_pair(sf::Vector2f(WIDTH, 0), sf::Vector2f(WIDTH, HEIGHT)));
	playground_walls.push_back(std::make_pair(sf::Vector2f(WIDTH, HEIGHT), sf::Vector2f(0, HEIGHT)));
	playground_walls.push_back(std::make_pair(sf::Vector2f(0, HEIGHT), sf::Vector2f(0, 0)));
	playground_vertices.push_back(sf::Vector2f(0, 0));
	playground_vertices.push_back(sf::Vector2f(WIDTH, 0));
	playground_vertices.push_back(sf::Vector2f(WIDTH, HEIGHT));
	playground_vertices.push_back(sf::Vector2f(0, HEIGHT));
	unity.addBlock(sf::Vector2f(200, 150), 500, 300);
	unity.addBlock(sf::Vector2f(30, 70), 20, 120);
	unity.addBlock(sf::Vector2f(20, 20), 200, 200);
	walls = std::vector <std::pair< sf::Vector2f, sf::Vector2f>>();
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

					float w = dragged->getGlobalBounds().width;
					float h = dragged->getGlobalBounds().height;
					float newX = std::min((window.getSize().x - w / 2), std::max(w / 2, (float)event.mouseMove.x)) - w / 2;
					float newY = std::min((window.getSize().y - h / 2), std::max(h / 2, (float)event.mouseMove.y)) - h / 2;
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


void get_intersection(std::vector<std::pair<sf::Vector2f, sf::Vector2f>> walls, Ray ray, sf::Vector2f &rv) {
	sf::Vector2f intersection;
	rv = sf::Vector2f(-1, -1);
	float dist = 0;
	for (auto value : walls) {
		if (ray.intersects(value.first, value.second, intersection)) {
			if (rv.x == -1) {
				rv = intersection;
				dist = distance_squared(ray.position, intersection);
			}
			else if (distance_squared(ray.position, intersection) < dist) {
				rv = intersection;
				dist = distance_squared(ray.position, intersection);
			}
		}
	}

}


bool less(sf::Vector2f a, sf::Vector2f b, sf::Vector2f center)
{
	if (a.x - center.x >= 0 && b.x - center.x < 0)
		return false;
	if (a.x - center.x < 0 && b.x - center.x >= 0)
		return true;
	if (a.x - center.x == 0 && b.x - center.x == 0) {
		if (a.y - center.y >= 0 || b.y - center.y >= 0)
			return a.y < b.y;
		return b.y < a.y;
	}

	// compute the cross product of vectors (center -> a) x (center -> b)
	float det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
	if (det < 0)
		return false;
	if (det > 0)
		return true;

	// points a and b are on the same line from the center
	// check which point is closer to the center
	float d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
	float d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
	return d1 > d2;
}

void App::update()
{
	float w = source.getGlobalBounds().width;
	float h = source.getGlobalBounds().height;
	float posX = source.getPosition().x + w / 2;
	float posY = source.getPosition().y + h / 2;
	
	walls = unity.getWalls();
	vertices = unity.getVertices();
	drawable_vertices.clear();
	vertices.reserve(vertices.size() + playground_vertices.size());
	vertices.insert(vertices.end(), playground_vertices.begin(), playground_vertices.end());
	walls.reserve(walls.size() + playground_walls.size());
	walls.insert(walls.end(), playground_walls.begin(), playground_walls.end());
	
	sf::Vector2f intersection;
	for (auto& value : vertices) {
		Ray r(sf::Vector2f(posX, posY), sf::Vector2f(value.x - posX, value.y - posY));
		get_intersection(walls, r, intersection);
		drawable_vertices.push_back(intersection);

		sf::Transform rotation;
		rotation.rotate(0.01f, posX, posY);
		Ray r1(sf::Vector2f(posX, posY), rotation.transformPoint(sf::Vector2f(value.x - posX, value.y - posY)));
		get_intersection(walls, r1, intersection);
		drawable_vertices.push_back(intersection);

		rotation.rotate(-0.02f, posX, posY);
		Ray r2(sf::Vector2f(posX, posY), rotation.transformPoint(sf::Vector2f(value.x - posX, value.y - posY)));
		get_intersection(walls, r2, intersection);
		drawable_vertices.push_back(intersection);
	}

	std::sort(drawable_vertices.begin(), drawable_vertices.end(), std::bind(less, std::placeholders::_1, std::placeholders::_2,
		sf::Vector2f(posX, posY)));
	
	
	
}




void App::render()
{
	
	desktop.Update(1.0f);
	window.clear(sf::Color(63, 81, 181));

	unity.draw(&window);


	float w = source.getGlobalBounds().width;
	float h = source.getGlobalBounds().height;
	float posX = source.getPosition().x + w / 2;
	float posY = source.getPosition().y + h / 2;
	sf::VertexArray lines(sf::Lines, 2*drawable_vertices.size());
	for (int i = 0; i < drawable_vertices.size(); i++) {
		lines[2 * i].position = drawable_vertices[i];
		lines[2 * i + 1].position = sf::Vector2f(posX, posY);
	}
	//window.draw(lines);

	sf::VertexArray edges(sf::LinesStrip, drawable_vertices.size() + 1);
	for (int i = 0; i < drawable_vertices.size(); i++) {
		edges[i].position = drawable_vertices[i];
	}
	edges[drawable_vertices.size()] = drawable_vertices[0];
	window.draw(edges);
	window.draw(source);
	gui.Display(window);
	window.display();
}


void App::initialize_gui() {
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.f);
	auto button = sfg::Button::Create("Hello");
	button->GetSignal(sfg::Button::OnLeftClick).Connect(
		std::bind(&App::OnButtonClick, this)
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
	my_window->SetPosition(sf::Vector2f(500.f, 500.f));
	my_window->Add(box);

	desktop.Add(my_window);
}
