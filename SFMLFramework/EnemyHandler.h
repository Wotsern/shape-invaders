#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>

#include "Object.h"
#include "ObstacleHandler.h"
#include "Settings.h"
#include "BlankEnemy.h"
#include "TriangleEnemy.h"
#include "SquareEnemy.h"
#include "CircleEnemy.h"
#include "PentagonEnemy.h"
#include "ProjectileHandler.h"

class ParticleHandler;

class EnemyHandler
{
private:
	sf::Clock			m_clock;				// Clock used for limiting loop iterations.
	sf::Time			m_randomNumberTimer;	// Timer used for random number generation.

	std::vector<Enemy*> m_enemies;																			// Demonstrating use of std::vector.
	sf::Vector2f		m_enemyPositions[EnemyProperties::c_enemyRows * EnemyProperties::c_enemyColumns];	// Array that stores positions of where the enmy is to go to at game start.

	float				m_movementTimer;		// Limits how much the enemies move.
	float				m_xPos;					// Holds the X position of the enemy positions.
	float				m_yPos;					// Holds the Y position of the enemy positions.
	float				m_speed;				// Holds the speed of the movement.
	float				m_levelCompleteTimer;	// Time before next level loads.

	int					m_enemyArray[EnemyProperties::c_enemyRows][EnemyProperties::c_enemyColumns];	// Stores the enemy types from file.
	int					m_rows;																			// Stores the amount of rows.
	int					m_columns;																		// Stores the amount of columns.
	int					m_currentEnemy;																	// Stores the current enemy loaded to make sure all are loaded.
	int					m_enemyCount;																	// Counts the amount of enemies on screen.
	int					m_enemiesKilled;																// Counts the amount of enemies killed.
	int					m_currentLevel;																	// Used to hold the current level.
	int					m_index;																		// Index of enemy spawned.

	bool				m_moveLeft;				// Bool that determines direction of enemy movement.
	bool				m_enemiesMoved;			// Check for if the enemies were moved.
	bool				m_showLevelComplete;	// Bool to display level complete text.

	ProjectileHandler*	m_pProjectileHandler;	// Reference to Projectile Handler.
	Game*				m_pGame;				// Reference to Game.
	Player*				m_pPlayer;				// Reference to Player.
	TextureHandler*		m_pTextureHandler;		// Reference to Texture Handler.
	ObstacleHandler*	m_pObstacleHandler;		// Reference to Obstacle Handler.

	GameText*			m_pLevelComplete;		// Text display for level complete.

public:
	EnemyHandler();
	~EnemyHandler();

	void initialise(ProjectileHandler* projectileHandler, Game* pGame, Player* pPlayer, TextureHandler* pTextureHandler, ObstacleHandler* pObstacleHandler, ParticleHandler* pParticleHandler); //Initialiser.
	void update(float deltaTime);				// Update function.
	void render(sf::RenderTarget* window);		// Render function.

	void setEnemyPositions();			// Function used to load the correct enemy positions for formation purposes.
	void loadLevel();					// Used to load the correct level from a folder.
	Enemy* spawnEnemy(EnemyType type);	// Spawn enemy function to summon the correct enemy.
	void spawnEnemies();				// Function to load enemies into the game.
	void checkEnemyCount();				// Check for enemy count.
	void resetLevelProperties();		// Function to reset all level properties.

	void enemyMovement(float deltaTime);	// Function that handles enemy movement.
	void moveEnemiesDown();					// Function to move enemies down when they hit the edge of the screen.
	void bulletGenerator();					// Bullet generator.

	int getCurrentLevel();				// Return the current game level.
	void setCurrentLevel(int level);	// Set the current game level.

	void clearProjectiles();			// Clear all projectiles from the screen.
	void clearEnemies();				// Clear all enemies from the screen.

	std::vector<Enemy*> getEnemies();
};

#endif //!ENEMYHANDLER_H