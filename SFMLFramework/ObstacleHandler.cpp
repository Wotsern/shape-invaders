#include "Helpers.h"
#include "Settings.h"
#include "ObstacleHandler.h"

ObstacleHandler::ObstacleHandler()
{	
	m_pObstacles		= new Obstacle[10];
	m_pTextureHandler	= nullptr;
	m_pPlayer			= nullptr;

	m_position.x		= ObstacleProperties::c_startingPosX;
	m_position.y		= ObstacleProperties::c_startingPosY;

	m_extraObstacles		= 0;
}

ObstacleHandler::~ObstacleHandler()
{
	safeDeletePointerArray(m_pObstacles);
}

void ObstacleHandler::initialise(TextureHandler* pTextureHandler, Player* pPlayer)
{
	// Set the Texture Handler.
	m_pTextureHandler = pTextureHandler;
	// Set the Player Handler.
	m_pPlayer = pPlayer;

	// Load all obstacles.
	loadObstacles();
	// Set the obstacle properties.
	setObstacleProperties();
}

void ObstacleHandler::update(float deltaTime)
{
	// Update all obstacles.
	for (int i = 0; i < ObstacleProperties::c_obstacleCount; i++)
	{
		m_pObstacles[i].update(deltaTime);
	}
}

void ObstacleHandler::render(sf::RenderTarget* window)
{
	// Render all obstacles.
	for (int i = 0; i < ObstacleProperties::c_obstacleCount; i++)
	{
		m_pObstacles[i].render(window);
	}
}

void ObstacleHandler::loadObstacles()
{
	for (int i = 0; i < ObstacleProperties::c_obstacleCount; i++)
	{
		// Initialise all obstacles.
		m_pObstacles[i].initialise(m_pTextureHandler, m_position);
		// Set the positions of the obstacles.
		m_pObstacles[i].setPosition(m_position);
		m_position.x += ObstacleProperties::c_obstacleGap;

		// Lower the positions of the rest of the projectiles.
		if (i == 4)
		{
			m_position.x = ObstacleProperties::c_startingPosX;
			m_position.y = ObstacleProperties::c_secondPosY;
		}
	}
}

void ObstacleHandler::setObstacleProperties()
{
	// Reset the obstacle properties.
	m_position.x = ObstacleProperties::c_startingPosX;
	for (int i = 0; i < ObstacleProperties::c_defaultCount + m_extraObstacles; i++)
	{
		m_pObstacles[i].setActiveStatus(true);
		m_pObstacles[i].setPosition(m_position); 
		m_pObstacles[i].setDefaultProperties();
		m_position.x += ObstacleProperties::c_obstacleGap;
	}
}

Obstacle* ObstacleHandler::getObstacles(int i)
{
	return &m_pObstacles[i]; // Return the obstacles.
}

int ObstacleHandler::getExtraObstacles()
{
	return m_extraObstacles; // Get the extra obstacles (shop upgraded).
}

void ObstacleHandler::setExtraObstacles(int mines)
{
	m_extraObstacles = mines; // Set how many extra mines needed.
}