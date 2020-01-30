#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	rect.setFillColor(sf::Color::Black);
	rect.setSize(sf::Vector2f(50, 50));
	rect.setPosition(0, 300);

	circle.setFillColor(sf::Color::Yellow);
	circle.setRadius(50);
	circle.setPosition(200, 200);

	circle2.setFillColor(sf::Color::Red);
	circle2.setRadius(20);
	circle2.setPosition(20, 20);


	speed = 100.f;
	speed2 = 50.f;
	speed3 = 100.f;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Up))
	{
		circle.move(0, -speed2 * dt);
	}
	else if (input->isKeyDown(sf::Keyboard::Down))
	{
		circle.move(0, speed2 * dt);
	}
	else if (input->isKeyDown(sf::Keyboard::Right))
	{
		circle.move(speed2 * dt, 0);
	}
	else if (input->isKeyDown(sf::Keyboard::Left))
	{
		circle.move(-speed2 * dt, 0);
	}
}

// Update game objects
void Level::update(float dt)
{
	
	sf::Vector2u pos = window->getSize();
	sf::Vector2f rectpos=rect.getPosition();
	sf::Vector2f circlepos = circle.getPosition();
	sf::Vector2f circle2pos = circle2.getPosition();

	
	//stop rectangle at window edge
	if (rectpos.x > pos.x-50)
	{
		speed = -speed;
	}
	else if (rectpos.x < 0)
	{
		speed = 100.f;
	}
	
	//move rectangle
	rect.move(speed * dt, 0);

	//stop circle 1 at window edge
	//for more precise number, using radius
	if (circlepos.x >( pos.x -  (circle.getRadius()*2)))
	{
		//first set a return location, being the position back at the edge of the window
		float x = pos.x - (circle.getRadius()*2);
		//then tell the circle to return to that location
		//y is just the last position that y was.
		circle.setPosition(x, circle.getPosition().y);

	}
	else if (circlepos.x < 0)
	{
		//left hand side, position we want to return to is just x
		float x = 0;
		circle.setPosition(x, circle.getPosition().y);
	}
	else if (circlepos.y > pos.y - (circle.getRadius()*2))
	{
		float y = pos.y - (circle.getRadius() * 2);
		circle.setPosition(circle.getPosition().x, y);

	}
	else if (circlepos.y < 0)
	{
		float y = 0;
		circle.setPosition(circle.getPosition().x, y);
	}

	
	//circle 2 collision
	if (circle2pos.x > (pos.x - (circle2.getRadius() * 2)))
	{
		
		float x = pos.x - (circle2.getRadius() * 2);
		circle2.setPosition(x, circle2.getPosition().y);

	}
	else if (circle2pos.x < 0)
	{
		float x = 0;
		circle2.setPosition(x, circle2.getPosition().y);
	}
	else if (circle2pos.y > pos.y - (circle2.getRadius() * 2))
	{
		float y = pos.y - (circle2.getRadius() * 2);
		circle2.setPosition(circle2.getPosition().x, y);

	}
	else if (circle2pos.y < 0)
	{
		float y = 0;
		circle2.setPosition(circle2.getPosition().x, y);
	}
	
	//circle 2 movement
	circle2.move(speed3 * dt, speed3 * dt);
}

// Render level
void Level::render()
{
	beginDraw();
	
	window->draw(rect);
	window->draw(circle);
	window->draw(circle2);

	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}