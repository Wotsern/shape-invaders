#include "Projectile.h"
#include <iostream>

Projectile::Projectile()
{
	m_pCollider					= new Collider();

	m_speed						= ProjectileProperties::c_projectileSpeed;

	m_direction					= sf::Vector2f(0, 0);
	m_savedPosition				= sf::Vector2f(0, 0);

	m_projectileDamage			= 0;
	m_playerProjectileSpeed		= ProjectileProperties::c_playerProjectileSpeed;
	m_playerProjectileDamage	= 1;

	m_playerSizeUpgrade			= false;
	m_canTeleport				= false;
	m_left						= false;
	m_isActive					= false;
	m_playerSpawned				= false;

	m_projectileType			= ProjectileType::Player;

	setOrigin(32, 32);
	setScale(0.3f, 0.3f);
}

Projectile::~Projectile()
{
	if (m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}
}

void Projectile::initialise(TextureHandler* pTextureHandler)
{
	setTextureHandler(pTextureHandler); // Set texture handler.
}

void Projectile::initialise(sf::Vector2f position, float directionX, float directionY)
{
	// This function is called when a new projectile is initialised.
	m_pCollider->initialise(4, getPosition());
	setPosition(position);
	m_direction.x = directionX;
	m_direction.y = directionY;
	m_savedPosition = position;
}

void Projectile::update(float deltaTime)
{
	getCollider()->setPosition(getPosition());  // Update the position of the collider to where the projectile is.
	teleportProjectile();						// Function to teleport the projectile if the upgrade is activated.

	// Update the projectile based on its type.
	switch (m_projectileType)
	{
	case ProjectileType::Player:
		circleProjectile(deltaTime);
		break;
	case ProjectileType::Circle:
		circleProjectile(deltaTime);
		break;
	case ProjectileType::Triangle:
		triangleProjectile(deltaTime);
		break;
	case ProjectileType::Square:
		squareProjectile(deltaTime);
		break;
	case ProjectileType::Pentagon:
		pentagonProjectile(deltaTime);
		break;
	}
}

void Projectile::render(sf::RenderTarget* window)
{
	// Draw the projectile to the screen.
	window->draw(*this);
	m_pCollider->render(window);
}

void Projectile::teleportProjectile()
{
	if (getPosition().y < 0 || getPosition().y > 1000)
	{
		// If the teleport upgrade is activated and the projectile spawned is from the player, this function will determineif it loops back around.
		if (m_canTeleport == true && m_playerSpawned == true)
		{
			// Generate random number.
			int _random = rand() % 5;

			if (_random == 4)
			{
				// If the random number is 4 then the projectile will teleport to the bottom of the screen to attack again.
				setPosition(getPosition().x, 1000);
			}
		}
		else
		{
			// Add the projectile back into the pool.
			setActiveState(false);
		}
	}
}

void Projectile::circleProjectile(float deltaTime)
{
	// Simple move function.
	move((getDirection() * getProjectileSpeed()) * deltaTime);
}

void Projectile::triangleProjectile(float deltaTime)
{
	// This function create a wave effect for the projectile to make it harder to dodge.
	move((getDirection() * getProjectileSpeed()) * deltaTime);

	if (getPosition().x > m_savedPosition.x + 25)
	{
		m_left = true;
	}
	if (getPosition().x < m_savedPosition.x - 25)
	{
		m_left = false;
	}
	if (m_left == false)
	{
		setDirection(sf::Vector2f(getDirection().x + 2 * deltaTime, getDirection().y));
	}
	if (m_left == true)
	{
		setDirection(sf::Vector2f(getDirection().x - 2 * deltaTime, getDirection().y));
	}
}

void Projectile::squareProjectile(float deltaTime)
{
	// Move the projectile down but the lower it gets the bigger -> this makes it harder to see.
	move((getDirection() * getProjectileSpeed()) * deltaTime);

	// Increase the scale overtime.
	setScale(getScale().x + 0.5f * deltaTime, getScale().y + 0.5f * deltaTime);
}

void Projectile::pentagonProjectile(float deltaTime)
{
	// Move projectile down.
	move((getDirection() * getProjectileSpeed()) * deltaTime);
}

void Projectile::setProjectileProperties(ProjectileType projectileType)
{
	// Set the projectile type retrieved from the parameter.
	m_projectileType = projectileType;

	// Based on the projectile type, different values will be set.
	switch (projectileType)
	{
	case ProjectileType::Player:
		setProjectileDamage(m_playerProjectileDamage);
		setScale(0.3f, 0.3f);
		setProjectileSpeed(ProjectileProperties::c_playerProjectileSpeed);	
		setTexture(getTextureHandler()->getTexture(TextureType::PlayerProjectile));
		if (m_playerSizeUpgrade == true)
		{
			setScale(0.6f, 0.6f);
			m_pCollider->setRadius(8);
		}
		break;
	case ProjectileType::Circle:
		setProjectileDamage(1);
		setScale(0.35f, 0.35f);
		m_pCollider->setRadius(4);
		setProjectileSpeed(ProjectileProperties::c_circleProjectileSpeed);
		setTexture(getTextureHandler()->getTexture(TextureType::CircleProjectile));
		break;
	case ProjectileType::Triangle:
		setProjectileDamage(3);
		setScale(0.4f, 0.4f);
		m_pCollider->setRadius(4);
		setProjectileSpeed(ProjectileProperties::c_triangleProjectileSpeed);
		setTexture(getTextureHandler()->getTexture(TextureType::TriangleProjectile));
		break;
	case ProjectileType::Square:
		setProjectileDamage(4);
		setScale(0, 0);
		m_pCollider->setRadius(0.4f);
		setProjectileSpeed(ProjectileProperties::c_squareProjectileSpeed);
		setTexture(getTextureHandler()->getTexture(TextureType::SquareProjectile));
		break;
	case ProjectileType::Pentagon:
		setProjectileDamage(5);
		setScale(0.5f, 0.5f);
		m_pCollider->setRadius(4);
		setProjectileSpeed(ProjectileProperties::c_pentagonProjectileSpeed);
		setTexture(getTextureHandler()->getTexture(TextureType::PentagonProjectile));
		break;
	}
}

float Projectile::getProjectileSpeed()
{
	return m_speed; // Return projectile speed.
}

void Projectile::setProjectileSpeed(float speed)
{
	m_speed = speed; // Set the projectile speed.
}

Collider* Projectile::getCollider()
{
	return m_pCollider; // Return the collider.
}

bool Projectile::getActiveState()
{
	return m_isActive; // Return the active state of the projectile.
}

void Projectile::setActiveState(bool active)
{
	m_isActive = active; // Set the active state.
}

void Projectile::setCanTeleport(bool teleport)
{
	m_canTeleport = teleport; // Set if the projectile can teleport.
}

void Projectile::setSizeIncrease(bool upgrade)
{
	m_playerSizeUpgrade = upgrade; // Set the size of the players projectile.
}

int Projectile::getProjectileDamage()
{
	return m_projectileDamage; // Return the projectile damage.
}

void Projectile::setProjectileDamage(int damage)
{
	m_projectileDamage = damage; // Set the projectile damage.
}

int Projectile::getPlayerProjectileDamage()
{
	return m_playerProjectileDamage; // Returns the player projectile damage.
}

void Projectile::setPlayerProjectileDamage(int damage)
{
	m_playerProjectileDamage = damage; // Sets the player projectile damage.
}

int Projectile::getPlayerProjectileSpeed()
{
	return m_playerProjectileSpeed;	// Return the players projectile speed.
}

void Projectile::setPlayerProjectileSpeed(int speed)
{
	m_playerProjectileSpeed = speed; // Set the speed of the players projectile.
}


bool Projectile::getPlayerSpawned()
{
	return m_playerSpawned; // Return if the projectile is player spawned or not.
}

void Projectile::setPlayerSpawned(bool playerSpawned)
{
	m_playerSpawned = playerSpawned; // Set bool if projectile is player spawned or not.
}

void Projectile::setDirection(sf::Vector2f direction)
{
	m_direction = direction; // Set direction of the projectile.
}

sf::Vector2f Projectile::getDirection()
{
	return m_direction; // Return the direction of the projectile.
}