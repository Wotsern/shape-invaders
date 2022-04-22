#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Collider.h"
#include "Object.h"
#include "TextureHandler.h"

class Obstacle : public Object
{
private:
	Collider*			m_pCollider;			// Instantiate a collider.

	bool				m_isActive;				// Check for if the obstacle is active for render and update purposes.
	bool				m_updateSprite;			// Bool to stop updating the sprite every frame.
	bool				m_obstacleDestroyed;	// Check for if the obstacle is destroyed or not (used for last animation phase).

	sf::Vector2f		m_position;				// Set the position of the obstacle.

	int					m_health;				// Health of the obstacle.

public:
	Obstacle();		// Constructor
	~Obstacle();	// Deconstructor

	void initialise(TextureHandler* pTextureHandler, sf::Vector2f position);	// Initialiser.
	void update(float deltaTime);												// Update function.
	void render(sf::RenderTarget* window);										// Render function.
	
	void checkObstacleHealth();				// Function to check health state of the obstacle.
	void shakeObstacle(float deltaTime);	// Function to shake the obstacle as the health lowers.
	void setDefaultProperties();

	void setActiveStatus(bool active);	// Set the active state of the obstacle.

	int getHealth();			// Return the health of the obstacle.
	void setHealth(int health);	// Set the health of the obstacle.

	int getDestroyed();
	void setDestroyed(bool destroyed);

	Collider* getCollider();			// Return the collider of the obstacle.

	void setUpdateSprite(bool update);	// Function to update sprite.
};

#endif //!OBSTACLE_H