#include "Obstacle.h"
#include "Settings.h"
#include <iostream>

Obstacle::Obstacle()
{
	m_pCollider			= new Collider();

	m_isActive			= false;
	m_updateSprite		= false;
	m_obstacleDestroyed = false;

	m_position			= sf::Vector2f(0, 0);

	m_health			= 0;
}

Obstacle::~Obstacle()
{
	if (m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}
}

void Obstacle::initialise(TextureHandler* pTextureHandler, sf::Vector2f position)
{	
	m_position = position;
	setTextureHandler(pTextureHandler);
	m_pCollider->initialise(32, getPosition());
	setDefaultProperties();
}

void Obstacle::update(float deltaTime)
{
	if (m_isActive == true)
	{
		shakeObstacle(deltaTime);
		checkObstacleHealth();
		m_pCollider->setRadius(32);
	}
	else
	{
		m_pCollider->setRadius(0);
	}
}

void Obstacle::render(sf::RenderTarget* window)
{
	if (m_isActive == true)
	{
		window->draw(*this);
		m_pCollider->render(window);
	}
}

void Obstacle::setDefaultProperties()
{
	// This function resets the obstacle properties, ready for the next level.
	m_pCollider->setRadius(32);
	setUpdateSprite(false);
	setRectSourcePos(0);
	setDestroyed(false);
	setHealth(ObstacleProperties::c_health);
	setRectSourceSprite(64, 64);
	setOrigin(32, 32);
	setTexture(getTextureHandler()->getTexture(TextureType::MineObstacle));
}

void Obstacle::checkObstacleHealth()
{
	// Check for obstacle health.
	if (m_health <= 0) 
	{
		// Remove the collider.
		m_pCollider->setRadius(0);
		// Allow the sprite to be updated.
		m_updateSprite = true;
		// Sets the obstacle to destroyed.
		m_obstacleDestroyed = true;
	}

	// This handles what sprite is shown.
	if (m_obstacleDestroyed == false && m_updateSprite == false)
	{
		switch (m_health)
		{
		case 5: case 10: case 15: case 20:
			m_updateSprite = true;
			setRectSourcePos(getRectSourcePos() + 64);
			break;
		case 0:
			setRectSourcePos(0);
			break;
		}
		drawSprite(getRectSourcePos());
	}

	if (m_obstacleDestroyed == true)
	{
		// Change the texture to the obstacle exploding.
		setTexture(getTextureHandler()->getTexture(TextureType::RockExplode));
		// Change the size of the source sprite.
		setRectSourceSprite(160, 160);
		// Re-position the origin to the centre of the image.
		setOrigin(80, 80);
		// Animate the sprite.
		animateSprite(0.03f, 160, 2560, false);
		// If the animation has played it will disable the obstacle.
		if (getRectSourcePos() >= 2560)
		{
			m_isActive = false;
		}
	}

	
}

void Obstacle::shakeObstacle(float deltaTime)
{
	// Based on the obstacles health depends on how much it shakes.
	if (m_health > 0)
	{		
		float shakeRate = rand() % 100 / m_health * 100 * deltaTime;
		setPosition(sf::Vector2f(m_position.x + shakeRate, m_position.y + shakeRate));
	}
}

void Obstacle::setActiveStatus(bool active)
{
	m_isActive = active; // Sets the active state of the obstacle.
}

int Obstacle::getHealth()
{
	return m_health; // Return the health of the obstacle
}

void Obstacle::setHealth(int health)
{
	m_health = health; // Set the health of the obstacle.
}

int Obstacle::getDestroyed()
{
	return m_obstacleDestroyed; // Returns if the obstacle is destroyed or not.
}

void Obstacle::setDestroyed(bool destroyed)
{
	m_obstacleDestroyed = destroyed; // Set the obstacle destroyed.
}

Collider* Obstacle::getCollider()
{
	return m_pCollider; // Return the collider.
}

void Obstacle::setUpdateSprite(bool update)
{
	m_updateSprite = update; // Set update sprite.
}

