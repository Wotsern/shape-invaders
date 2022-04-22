#include "Object.h"

Object::Object()
{

}

Object::~Object()
{
}

void Object::update(float deltaTime)
{
}

void Object::render(sf::RenderTarget* window)
{
	// Render to window.
	window->draw(*this);
}