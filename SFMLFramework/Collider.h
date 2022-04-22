#ifndef COLLIDER_H
#define COLLIDER_H

#include "Object.h"

#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\System\Vector2.hpp>

class Collider : public Object
{
private:
	float				m_radius;	// Set the radius of the collider.

	sf::Vector2f		m_position; // Set the position of the collider.

	sf::CircleShape		m_circle;	// Debug (draws circle to screen, not used in actual game).

public:
	Collider();		// Constructor.
	~Collider();	// Deconstructor.

	void initialise(float radius, sf::Vector2f position);	// Initialiser.
	void render(sf::RenderTarget* window);					// Render function.

	sf::Vector2f getPosition();								// Return position of collider.
	void setPosition(sf::Vector2f position);				// Set the position of collider.

	float getRadius();										// Return the radius.
	void setRadius(float radius);							// Set the radius.

	void setCircleOrigin(float x, float y);					// Used for debug purposes.

};

#endif //!COLLIDER_H