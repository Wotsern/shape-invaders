#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tchar.h>

#include "Game.h"
#include "Helpers.h"
#include "Particle.h"

EnemyHandler::EnemyHandler()
{
	m_xPos					= EnemyProperties::c_startingXPos;
	m_yPos					= EnemyProperties::c_startingYPos;
	m_speed					= EnemyProperties::c_movementSpeed;
	m_levelCompleteTimer	= 0;

	m_rows					= EnemyProperties::c_enemyRows;
	m_columns				= EnemyProperties::c_enemyColumns;
	m_currentEnemy			= 0;
	m_enemyCount			= 0;
	m_enemiesKilled			= 0;
	m_currentLevel			= 1;
	m_index					= 0;

	m_moveLeft				= false;
	m_enemiesMoved			= false;
	m_showLevelComplete		= false;

	m_pProjectileHandler	= nullptr;
	m_pGame					= nullptr;
	m_pPlayer				= nullptr;
	m_pTextureHandler		= nullptr;
	m_pObstacleHandler		= nullptr;

	m_pLevelComplete		= new GameText();
}

EnemyHandler::~EnemyHandler()
{
	// Safe delete all enemy pointers.
	for (auto p : m_enemies)
	{
		delete p;
		p = nullptr;
	}
	// Clear enemy array.
	m_enemies.clear();
	// Safe delete level complete pointer.
	safeDeletePointer(m_pLevelComplete);
}

void EnemyHandler::initialise(ProjectileHandler* projectileHandler, Game* pGame, Player* pPlayer, TextureHandler* pTextureHandler, ObstacleHandler* pObstacleHandler, ParticleHandler* pParticleHandler)
{
	// Set the pointers from the data passed through the parameters.
	m_pProjectileHandler = projectileHandler;
	m_pGame = pGame;
	m_pPlayer = pPlayer;
	m_pTextureHandler = pTextureHandler;
	m_pObstacleHandler = pObstacleHandler;

	// Load and set level complete text.
	m_pLevelComplete->initialise(Fonts::SciFi);
	m_pLevelComplete->setString("   LEVEL \nCOMPLETE");
	m_pLevelComplete->setPosition(200, 300);
	m_pLevelComplete->setCharacterSize(100);

	// Resize the enemy vector array.
	m_enemies.resize(120);
	int amount = 24;
	int current = 0;

	// Pre-load all of the enemies so they can be reused throughout the levels.
	for (auto& enemy : m_enemies)
	{
		if (current < amount)
		{
			enemy = new BlankEnemy();
		}
		else if (current <= amount * 2)
		{
			enemy = new CircleEnemy();
		}
		else if (current <= amount * 3)
		{
			enemy = new TriangleEnemy();
		}
		else if (current <= amount * 4)
		{
			enemy = new SquareEnemy();
		}
		else if (current <= amount * 5)
		{
			enemy = new PentagonEnemy();
		}
		// Initialise all enemies.
		enemy->initialise(m_pPlayer, m_pProjectileHandler, m_pTextureHandler, this, pParticleHandler);
		current++;
	}
	// Set the enemy designated positions.
	setEnemyPositions();
}

void EnemyHandler::update(float deltaTime)
{
	// Loop through enemy vector array and update those that are active.
	for (auto& enemy : m_enemies)
	{
		if (enemy->getActiveState() == true)
		{
			enemy->update(deltaTime);
			enemy->animationHandler();
		}
	}

	// Function that handles enemy movement.
	enemyMovement(deltaTime);
	// Function that handles projectile generation.
	bulletGenerator();

	// Display level complete text.
	if (m_showLevelComplete == true)
	{
		m_levelCompleteTimer += deltaTime;
		if (m_levelCompleteTimer >= EnemyProperties::c_countdownTimer)
		{
			m_showLevelComplete = false;
			m_levelCompleteTimer = 0;
			// Disable player shooting.
			m_pPlayer->setCanShoot(false);
			// Direct the player to the Shop Menu.
			m_pGame->setCurrentState(GameStates::Shop);
		}
	}
}

void EnemyHandler::render(sf::RenderTarget* window)
{
	// Render all active enemies to the window.
	for (auto& enemy : m_enemies)
	{
		if (enemy->getActiveState())
		{
			enemy->render(window);
		}
	}

	// Draw level complete game text to the window if the level was complete.
	if (m_showLevelComplete == true)
	{
		window->draw(*m_pLevelComplete);
	}
}

void EnemyHandler::setEnemyPositions()
{
	// Set the correct positions.
	for (int i = 0; i < 24; i++)
	{
		m_xPos += EnemyProperties::c_gapBetweenEnemies;
		m_enemyPositions[i] = sf::Vector2f(m_xPos, m_yPos);

		m_currentEnemy++;
		// Check the amount of enemies in a row and lower to the next line if a certain value.
		if (m_currentEnemy % EnemyProperties::c_enemyColumns == 0)
		{
			m_xPos = EnemyProperties::c_startingXPos;
			m_yPos += EnemyProperties::c_gapBetweenEnemies;
		}
	}
	loadLevel();
}

void EnemyHandler::loadLevel()
{
	std::string mapChoice;

	//Level number as argument.
	switch (m_currentLevel) {
	case 1:
		//Load this text file if the desired level is '1'.
		mapChoice = "LevelManager/level1.txt";
		break;
	case 2:
		//Load this text file if the desired level is '2'.
		mapChoice = "LevelManager/level2.txt";
		break;
	case 3:
		//Load this text file if the desired level is '3'.
		mapChoice = "LevelManager/level3.txt";
		break;
	case 4:
		//Load this text file if the desired level is '4'.
		mapChoice = "LevelManager/level4.txt";
		break;
	case 5:
		//Load this text file if the desired level is '5'.
		mapChoice = "LevelManager/level5.txt";
		break;
	case 6:
		//Load this text file if the desired level is '6'.
		mapChoice = "LevelManager/level6.txt";
		break;
	case 7:
		//Load this text file if the desired level is '7'.
		mapChoice = "LevelManager/level7.txt";
		break;
	case 8:
		//Load this text file if the desired level is '8'.
		mapChoice = "LevelManager/level8.txt";
		break;
	}
	//Grab text file.
	std::ifstream mapFile(mapChoice);

	//Loop for the amount of rows.
	for (int mapRow = 0; mapRow < m_rows; mapRow++) 
	{
		//Grab current file row in the text file.
		std::string fileRow; 
		std::getline(mapFile, fileRow);

		//Grab strings within the current row.
		std::stringstream stringstream(fileRow); 

		//Loop for the amount of columns.
		for (int mapColumn = 0; mapColumn < m_columns; mapColumn++)
		{
			//Seperate strings vis ','.
			std::string mapElement;
			std::getline(stringstream, mapElement, ','); 

			//Convert data gathered, ready to input into an array.
			std::stringstream converter(mapElement); 
			//Store the converted values into a 2D array.
			converter >> m_enemyArray[mapRow][mapColumn]; 
		}
	}
	// Spawn the enemies as the level layout has been set.
	spawnEnemies();
}

void EnemyHandler::spawnEnemies()
{
	// Create pointer to 'Enemy'.
	Enemy* enemy;

	// Loop that will go through the enemy array loaded from the previous function.
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_columns; c++)
		{
			// If any of the arguments are met then it will load the correct enemy.
			switch (m_enemyArray[r][c])
			{
			case 1:
				enemy = spawnEnemy(EnemyType::Circle);
				break;
			case 2:
				enemy = spawnEnemy(EnemyType::Triangle);
				break;
			case 3:
				enemy = spawnEnemy(EnemyType::Square);
				break;
			case 4:
				enemy = spawnEnemy(EnemyType::Pentagon);
				break;
			default:
				enemy = spawnEnemy(EnemyType::Blank);
				break;
			}
			// Allocate the enemy a desired position.
			enemy->loadEnemy(m_enemyPositions[m_index]);
			// Increase index so the enemies are all set differentdesired locations.
			m_index++;
		}
	}
	// Reset index value.
	m_index = 0;
}

void EnemyHandler::enemyMovement(float deltaTime)
{
	// This loops through all enemies within the vector array.
	for (auto& enemy : m_enemies)
	{
		// Check for if the enemy is active.
		if (enemy->getActiveState() == true)
		{
			// Check to see if enemy is close to the edge of the screen.
			if (enemy->getPosition().x <= 50 && m_enemiesMoved == false || enemy->getPosition().x >= 750 && m_enemiesMoved == false)
			{
				// Set the movement opposite to its current state if the condition is met.
				m_moveLeft = !m_moveLeft;
				// Move enemies down.
				m_enemiesMoved = true;
				moveEnemiesDown();
			}
		}
	}

	if (m_enemiesMoved == true)
	{
		m_movementTimer += deltaTime;
		if (m_movementTimer > 1)
		{
			m_movementTimer = 0;
			m_enemiesMoved = false;
		}
	}
	// Loop through all enemies stored in the vector array.
	for (auto& enemy : m_enemies)
	{
		// If the enemy isn't in their finishing move state then they will 
		if (enemy->getFinishingMove() == false)
		{
			// Move all enemies to the left.
			if (m_moveLeft == true)
			{
				enemy->setPosition(enemy->getPosition().x - m_speed * deltaTime, enemy->getPosition().y);
			}
			else
			{
				//Move all enemies to the right.
				enemy->setPosition(enemy->getPosition().x + m_speed * deltaTime, enemy->getPosition().y);
			}
		}
	}
}

void EnemyHandler::moveEnemiesDown()
{
	// Loops through the enemy vector array.
	for (auto& enemy : m_enemies)
	{
		// Check for if the enemies has been move already, if not then this function will run.
		if (enemy->getActiveState() == true && enemy->getFinishingMove() == false)
		{
			// Lower the enemies.
			enemy->setPosition(enemy->getPosition().x, enemy->getPosition().y + EnemyProperties::c_moveEnemyDown);
		}
	}
}

void EnemyHandler::bulletGenerator()
{
	// Random bullet generation timer.
	m_randomNumberTimer = m_clock.getElapsedTime();

	// If the timer condition has been met this function will run.
	if (m_randomNumberTimer.asSeconds() > EnemyProperties::c_randomNumberTimer && m_pPlayer->getLevelBegin() == true)
	{
		// Loop through enemy vector array.
		for (auto& enemy : m_enemies)
		{
			// Check to filter out all inacitve enemies.
			if (enemy->getActiveState() == true)
			{
				// Generate a random number.
				int _random = 1 + (rand() % EnemyProperties::c_spawnProjectilePercent);
				// If the number generated is equal to 4 then a projectile will be fired.
				if (_random == 4)
				{
					enemy->fireProjectile();
					enemy->setFireAnimationStatus(true);
				}
			}
		}
		// Restart the clock.
		m_clock.restart();
	}
}

void EnemyHandler::checkEnemyCount()
{
	// Reset enemy count.
	m_enemyCount = -1;
	for (auto& enemy : m_enemies)
	{
		// Check for all active enemies.
		if (enemy->getActiveState() == true)
		{
			// Increase the amount of active enemies.
			m_enemyCount++;
		}
	}

	// If there are no active enemies, start next game phase.
	if (m_enemyCount == 0 && m_pPlayer->getLevelBegin() == true)
	{
		// Display level complete gametext.
		m_showLevelComplete = true;
	}
}

void EnemyHandler::resetLevelProperties()
{
	// Reset all necessary properties that make the game work correctly.
	m_enemyCount = 0;
	m_enemiesKilled = 0;

	// Clear all projectiles from the screen.
	clearProjectiles();
	// Clear all enemies from the array.
	clearEnemies();

	// Load the next level.
	loadLevel();
}

void EnemyHandler::clearProjectiles()
{
	// Remove all projectile from the screen.
	for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++) //Remove all active projectiles from the screen.
	{
		m_pProjectileHandler->getProjectiles(i)->setActiveState(false);
	}
}

void EnemyHandler::clearEnemies()
{
	// Remove all of the enemies from the screen.
	for (auto& enemy : m_enemies)
	{
		if (enemy->getActiveState() == true)
		{
			enemy->setHealth(0);
		}
	}
}

Enemy* EnemyHandler::spawnEnemy(EnemyType type)
{
	// This return the enemy to the array if the conditions are met.
	for (auto& enemy : m_enemies)
	{
		if (enemy->getActiveState() == false && enemy->getEnemyType() == type)
		{
			return enemy;
			break;
		}
	}
	// If condition arent met then return a nullptr.
	return nullptr;
}

std::vector<Enemy*> EnemyHandler::getEnemies()
{
	return m_enemies; // Return the enemy vector array.
}

int EnemyHandler::getCurrentLevel()
{
	return m_currentLevel;  // Return the current level.
}

void EnemyHandler::setCurrentLevel(int level)
{
	m_currentLevel = level; // Set the current level.
}