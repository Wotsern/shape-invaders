#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"
#include "Settings.h"

class ProjectileHandler
{
private:
	Projectile*		m_pProjectiles;		// Array of projectiles.

public:
	ProjectileHandler();	// Constructor.
	~ProjectileHandler();	// Deconstructor.

	void initialise(TextureHandler* pTextureHandler);	// Initialiser.
	void update(float deltaTime);						// Update function.
	void render(sf::RenderTarget* window);				// Render function.

	bool spawnProjectile(sf::Vector2f position, float directionX, float directionY, bool playerSpawned, ProjectileType projectileType); // Spawn bullet function.

	Projectile* getProjectiles(int i); // Return the projectiles in the array.
};

#endif //!PROJECTILEHANDLER_H