#ifndef OBSTACLEHANDLER_H
#define OBSTACLEHANDLER_H

#include "Object.h"
#include "Obstacle.h"
#include "Player.h"
#include "TextureHandler.h"

class ObstacleHandler
{
private:
	Obstacle*			m_pObstacles;				// Create an array of obstacles.
	TextureHandler*		m_pTextureHandler;			// Reference to the Texture Handler.
	Player*				m_pPlayer;					// Reference to the Player.

	sf::Vector2f		m_position;					// Position of the obstacles.

	int					m_extraObstacles;			// Holds the amount of extra obstacles to spawn.

public:
	ObstacleHandler();	// Constructor.
	~ObstacleHandler();	// Deconstructor.

	void initialise(TextureHandler* pTextureHandler, Player* pPlayer);	// Initialiser.
	void update(float deltaTime);										// Update function.
	void render(sf::RenderTarget* window);								// Render function.

	void loadObstacles();
	void setObstacleProperties();		// Set obstacle properties.

	int getExtraObstacles();			// Return the obstacles.
	void setExtraObstacles(int mines);	// Setter for extra obstacles.

	Obstacle* getObstacles(int i);		// Return all obstacles created.
};

#endif //!OBSTACLEHANDLER_H