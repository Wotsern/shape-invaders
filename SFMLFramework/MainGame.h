#ifndef MAINGAME_H
#define MAINGAME_H

#include "AudioHandler.h"
#include "ColliderHandler.h"
#include "EnemyHandler.h"
#include "ObstacleHandler.h"
#include "ParticleHandler.h"
#include "Player.h"
#include "ProjectileHandler.h"

class ParticleHandler;

class MainGame
{
private:
	ColliderHandler*	m_pColliderHandler;		// Reference to collider handler.
	EnemyHandler*		m_pEnemyHandler;		// Reference to enemy handler.
	ObstacleHandler*	m_pObstacleHandler;		// Reference to obstacle handler.
	Player*				m_pPlayer;				// Reference to player.
	ProjectileHandler*	m_pProjectileHandler;	// Reference to projectile handler.

public:
	MainGame();		// Constructor.
	~MainGame();	// Deconstructor.

	void initialise(TextureHandler* pTextureHandler, Game* pGame, ParticleHandler* pParticleHandler, AudioHandler* pAudioHandler);	// Initialiser.
	void update(float deltaTime);																		// Update function.
	void render(sf::RenderTarget* window);																// Render function.

	void				resetGame();				// Function to reset all game properties.

	Player*				getPlayer();				// Return player object.
	EnemyHandler*		getEnemyHandler();			// Return enemy handler object.
	ProjectileHandler*	getProjectileHandler();		// Return projectile handler object.
	ObstacleHandler*	getObstacleHandler();		// Return obstacle handler.
};

#endif //!MAINGAME_H