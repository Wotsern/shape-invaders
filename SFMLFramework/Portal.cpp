#include <iostream>

#include "Helpers.h"
#include "Portal.h"
#include "Settings.h"

Portal::Portal()
{		
	m_isActive = true;

	m_pPlayer = nullptr;
	m_pCollider = new Collider();
	m_pEnemy = nullptr;

	m_deltaTime = 0;
	m_timer = 0;

	setScale(2, 2);
	setOrigin(48, 48);
	setPosition(sf::Vector2f(-1000, 0));
}

Portal::~Portal()
{
	safeDeletePointer(m_pCollider);
}

void Portal::initialise(Enemy* enemy, sf::Vector2f position, Player* pPlayer, TextureHandler* pTextureHandler)
{
	// Set the pointer references.
	m_pPlayer = pPlayer;
	m_pEnemy = enemy;

	// Initialise a collider.
	m_pCollider->initialise(120, getPosition());

	// Set position and texture of the portal.
	setPosition(sf::Vector2f(position.x, position.y + 20));
	setTexture(pTextureHandler->getTexture(TextureType::Portal));
}

void Portal::update(float deltaTime)
{
	if (m_isActive == true) 
	{
		m_deltaTime = deltaTime;
		// Check for collision with the player.
		checkCollision(deltaTime);
		// Remove the object from the screen after a set amount of time.
		deleteObject();
	}
}

void Portal::render(sf::RenderTarget* window)
{
	if (m_isActive == true)
	{
		// Draw the portal to the window.
		window->draw(*this);
		// Draw the collider to the window (DEBUG).
		m_pCollider->render(window);
	}
}

void Portal::checkCollision(float deltaTime)
{
	// If the Player pointer reference is no longer null the function will be entered.
	if (m_pPlayer != nullptr)
	{
		// Rotate the portal.
		setRotation(getRotation() + EffectProperties::c_portalRotationSpeed * deltaTime);

		// Check for collision with the player and portal.
		bool collision = checkDistance(getPosition(), m_pPlayer->getPosition(), m_pCollider->getRadius());
		if (collision == true)
		{
			// Shake the screen.
			screenShake = true;
			// Pull the player to the centre of the portal.
			moveTowards(m_pPlayer->getPosition(), getPosition(), m_pPlayer, deltaTime, EnemyProperties::c_portalForce, false);
		}
		else
		{
			screenShake = false;
		}
	}
}

void Portal::deleteObject()
{
	m_timer += m_deltaTime;

	// Check for if the desired seconds were met.
	if (m_timer >= EffectProperties::c_portalTimer)
	{
		// Remove the enemy from the screen.
		m_pEnemy->setHealth(0);
		// Set the portal inactive.
		m_isActive = false;
		//Disable the screen from shaking.
		screenShake = false;
	}
}