#include "MainGame.h"
#include "Helpers.h"
#include "ParticleHandler.h"
#include <iostream>

MainGame::MainGame()
{
	m_pPlayer				= new Player;
	m_pEnemyHandler			= new EnemyHandler;
	m_pColliderHandler		= new ColliderHandler;
	m_pProjectileHandler	= new ProjectileHandler;
	m_pObstacleHandler		= new ObstacleHandler;
}

MainGame::~MainGame()
{
	safeDeletePointer(m_pPlayer);
	safeDeletePointer(m_pEnemyHandler);
	safeDeletePointer(m_pColliderHandler);
	safeDeletePointer(m_pProjectileHandler);
	safeDeletePointer(m_pObstacleHandler);
}

void MainGame::initialise(TextureHandler* pTextureHandler, Game* pGame, ParticleHandler* pParticleHandler, AudioHandler* pAudioHandler)
{
	// Initialise everything needed for the Main Game.
	m_pPlayer->initialise(this, m_pProjectileHandler, pTextureHandler, pGame, m_pEnemyHandler, pParticleHandler, pAudioHandler);
	m_pEnemyHandler->initialise(m_pProjectileHandler, pGame, m_pPlayer, pTextureHandler, m_pObstacleHandler, pParticleHandler);
	m_pColliderHandler->initialise(m_pProjectileHandler, m_pEnemyHandler, m_pObstacleHandler, m_pPlayer);
	m_pProjectileHandler->initialise(pTextureHandler);
	m_pObstacleHandler->initialise(pTextureHandler, m_pPlayer);
}

void MainGame::update(float deltaTime)
{
	// Update everything required in order for the Main Game to run smoothly.
	m_pPlayer->update(deltaTime);
	m_pEnemyHandler->update(deltaTime);
	m_pColliderHandler->update();
	m_pProjectileHandler->update(deltaTime);
	m_pObstacleHandler->update(deltaTime);
}

void MainGame::render(sf::RenderTarget* window)
{
	// Render all Game Sprites to the window.
	m_pEnemyHandler->render(window);
	m_pProjectileHandler->render(window);
	m_pObstacleHandler->render(window);
	m_pPlayer->render(window);
}

void MainGame::resetGame()
{
	// If the reset game function is called and the player has no lives left then ->
	if (m_pPlayer->getLives() == 0)
	{
		// -> the players bank will be reset and the level will return to 1.
		m_pPlayer->setBank(0);
		m_pEnemyHandler->setCurrentLevel(1);
	}

	// Reset obstacle properties.
	m_pObstacleHandler->setObstacleProperties();
	// Reset player properties.
	m_pPlayer->setPlayerProperties();
	// Reset enemy handler properties.
	m_pEnemyHandler->resetLevelProperties();
}

// Return the Player pointer.
Player* MainGame::getPlayer()
{
	return m_pPlayer;
}

// Return the Enemy Handler pointer.
EnemyHandler* MainGame::getEnemyHandler()
{
	return m_pEnemyHandler;
}

// Return the Projectile Handler pointer.
ProjectileHandler* MainGame::getProjectileHandler()
{
	return m_pProjectileHandler;
}

// Return the Obstacle Handler pointer.
ObstacleHandler* MainGame::getObstacleHandler()
{
	return m_pObstacleHandler;
}
