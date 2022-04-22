#include "ProjectileHandler.h"
#include <iostream>
#include "Helpers.h"

ProjectileHandler::ProjectileHandler()
{
	// Load all of the projectiles needed into the game.
	m_pProjectiles = new Projectile[ProjectileProperties::c_maxProjectiles];
}

ProjectileHandler::~ProjectileHandler()
{
	// Delete the pointer array.
	safeDeletePointerArray(m_pProjectiles);
}

void ProjectileHandler::initialise(TextureHandler* pTextureHandler)
{
	// Initialise all projectile and pass through the Texture Handler.
	for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
	{
		m_pProjectiles[i].initialise(pTextureHandler);
	}
}

void ProjectileHandler::update(float deltaTime)
{
	// Update all projectiles if their current active state is true.
	for (int bulletCount = 0; bulletCount < ProjectileProperties::c_maxProjectiles; bulletCount++)
	{	
		if (m_pProjectiles[bulletCount].getActiveState() == true)
		{
			m_pProjectiles[bulletCount].update(deltaTime);
		}
	}
}

bool ProjectileHandler::spawnProjectile(sf::Vector2f position, float directionX, float directionY, bool playerSpawned, ProjectileType projectileType)
{
	// If this function is called, it will loop through all projectiles within the game ->
	for (int bulletCount = 0; bulletCount < ProjectileProperties::c_maxProjectiles; bulletCount++)
	{
		Projectile& projectile = m_pProjectiles[bulletCount];
		if (m_pProjectiles[bulletCount].getActiveState() == false) // -> and check for if there are any inactive ones.
		{
			// If the condition is met then a projectile will be initialise with the designated properties.
			projectile.setProjectileProperties(projectileType);
			projectile.setActiveState(true);
			projectile.setPlayerSpawned(playerSpawned);
			projectile.initialise(position, directionX, directionY);
			return true;
		}
	}
	return false;
}

void ProjectileHandler::render(sf::RenderTarget* window)
{
	// Render for all active projectiles.
	for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
	{
		if (m_pProjectiles[i].getActiveState() == true)
		{
			m_pProjectiles[i].render(window);
		}
	}
}

Projectile* ProjectileHandler::getProjectiles(int i)
{
	return &m_pProjectiles[i]; // Return projectile array.
}
