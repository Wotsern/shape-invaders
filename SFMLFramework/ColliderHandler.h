#ifndef COLLIDERHANDLER_H
#define COLLIDERHANDLER_H

#include "EnemyHandler.h"
#include "ObstacleHandler.h"
#include "Player.h"
#include "ProjectileHandler.h"

class ColliderHandler
{
private:
	EnemyHandler*			m_pEnemyHandler;		// Used for reference to the enemy handler.
	ProjectileHandler*		m_pProjectileHandler;	// Used for reference to the projectile handler.
	ObstacleHandler*		m_pObstacleHandler;		// Used for reference to the obstacle handler.
	Player*					m_pPlayer;				// Used for reference to the player object.
	Game*					m_pGame;				// Used for reference to the game object.

public:
	ColliderHandler();	// Constructor.
	~ColliderHandler();	// Deconstructor.

	void initialise(ProjectileHandler* projectileHandler, EnemyHandler* enemyHandler, ObstacleHandler* obstacleHandler, Player* player);	// Initialiser.
	void update();																															// Update function.

	void checkEnemyCollision();			// Function to check for collision between projectile and enemy.
	void checkPlayerCollision();		// Function to check for collision between projectile and player.
	void checkObstacleCollision();		// Function to check for collision between projectile and obstacle.
	void checkTargetCollision();		// Function to check if the target collider has been hit.
	void checkTriangleEnemyCollision();	// Function to check for collision between triangle enemy and player.
};

#endif //!COLLIDERHANDLER_H