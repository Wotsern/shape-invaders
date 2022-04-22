#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>

#include "Collider.h"
#include "Object.h"
#include "Settings.h"

enum class ProjectileType 
{
	Player,
	Circle,
	Triangle,
	Square,
	Pentagon,
	Hexagon,
	Heptagon,
	Octagon
};

class Projectile : public Object
{
private:
	Collider*		m_pCollider;				// Instantiate a collider for the projectile.

	float			m_speed;					// Speed at which the bullet will move.

	sf::Vector2f	m_direction;				// Int value used to determine which direction the bullet will move (up for player, down for enemy).
	sf::Vector2f	m_savedPosition;

	int				m_projectileDamage;			// Damage of projectile.
	int				m_playerProjectileSpeed;	// Handles the speed of the players projectile.
	int				m_playerProjectileDamage;	// Handles the damage of the players projectile.

	bool			m_playerSizeUpgrade;		// Used to determine if the players projectile are to be upgraded.
	bool			m_canTeleport;				// Used to activate teleport bullets.
	bool			m_left;						// Used for bullet wave effect.
	bool			m_isActive;					// Projectile active state.
	bool			m_playerSpawned;			// Bool used for collision handling.

	ProjectileType	m_projectileType;			// Used to set the correct projetile type so its properties can be assigned.
	
public:
	Projectile();	// Constructor.
	~Projectile();	// Deconstructor.

	void			initialise(TextureHandler* pTextureHandler);							// This is instantiated before anything else so the texture can be loaded correctly.
	void			initialise(sf::Vector2f position, float directionX, float directionY);	// This is used when re-initialising the projectile after shooting.

	void			update(float deltaTime);				// Update function.
	virtual void	render(sf::RenderTarget* window);		// Render function.
	
	void			teleportProjectile();					// Function that handles projectile teleportation if enabled.
	void			circleProjectile(float deltaTime);		// Function to handle circle projectile movement.
	void			triangleProjectile(float deltaTime);	// Function to handle triangle projectile movement.
	void			squareProjectile(float deltaTime);		// Function to handle square projectile movement.
	void			pentagonProjectile(float deltaTime);	// Function to handle pentagon projectile movement.

	Collider*		getCollider();							// Return the collider of this object.

	sf::Vector2f	getDirection();							// Return the direction the projectile is going.
	void			setDirection(sf::Vector2f direction);	// Set the direction the projectile is going.

	float			getProjectileSpeed();					// Return the projectile speed.
	void			setProjectileSpeed(float speed);		// Set the projectile speed.

	bool			getActiveState();						// Return the active state of the projectile.
	void			setActiveState(bool active);			// Set the active state of the projectile.

	void			setCanTeleport(bool teleport);			// Used to enable/disable projectile teleportation.

	void			setSizeIncrease(bool increase);			// Set the active state of the projectile.

	int				getProjectileDamage();					// Return the damage of the projectile.
	void			setProjectileDamage(int damage);		// Set the damage of the projectile.
	
	int				getPlayerProjectileDamage();			// Return the damage of the projectile.
	void			setPlayerProjectileDamage(int damage);	// Set the damage of the projectile.

	int				getPlayerProjectileSpeed();				// Return the damage of the projectile.
	void			setPlayerProjectileSpeed(int speed);	// Set the damage of the projectile. 

	void			setProjectileProperties(ProjectileType projectileType); // Set the properties of the projectile (suited for the type of object that shot it).

	bool			getPlayerSpawned();						// Check for if the projectile was spawned by enemy or player.
	void			setPlayerSpawned(bool playerSpawned);	// Set if the projectile was shot by the player or not.
};

#endif //!PROJECTILE_H