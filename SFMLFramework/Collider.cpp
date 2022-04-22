#include "Collider.h"
#include "Helpers.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Collider::Collider()
{
	m_radius		= 0;
	m_position		= sf::Vector2f(0, 0);
}

Collider::~Collider()
{

}

void Collider::initialise(float radius, sf::Vector2f position)
{
	// Set the radius of collider used for the getter in collision.
	m_radius = radius;	
	// Set the radius of the collider.
	m_circle.setRadius(radius);
	// Set the circle origin based on the radius.
	setCircleOrigin(radius, radius);
	// Set the fill color of the circle (DEBUG)
	m_circle.setFillColor(sf::Color(100, 250, 50));
	// Set the position of the collider.
	setPosition(sf::Vector2f(position.x, position.y));
}

void Collider::render(sf::RenderTarget* window)
{	
	//window->draw(m_circle);
}

// Set the position of the collider.
void Collider::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_circle.setPosition(m_position);
}

// Return the position of the collider.
sf::Vector2f Collider::getPosition()
{
	return getPosition();
}

// Set the radius of the collider.
void Collider::setRadius(float radius)
{
	m_radius = radius;
	m_circle.setRadius(radius);
}

// Return the radius of the collider.
float Collider::getRadius()
{
	return m_radius;
}

// Set the circle origin of the collider.
void Collider::setCircleOrigin(float x, float y)
{
	m_circle.setOrigin(x, y);
}
