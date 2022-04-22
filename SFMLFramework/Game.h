#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "AudioHandler.h"
#include "ColliderHandler.h"
#include "EnemyHandler.h"
#include "HelpMenu.h"
#include "HighscoreMenu.h"
#include "MainGame.h"
#include "MainMenu.h"
#include "ObstacleHandler.h"
#include "ParticleHandler.h"
#include "Player.h"
#include "ProjectileHandler.h"
#include "ShopMenu.h"
#include "TextureHandler.h"

enum class GameStates { StartMenu, MainGame, Shop, HighscoreMenu, HelpMenu };

class Game
{
private:
	AudioHandler*		m_pAudioHandler;
	MainGame*			m_pMainGame;			// Reference to main game.
	MainMenu*			m_pMainMenu;			// Reference to main menu.
	ParticleHandler*	m_pParticleHandler;		// Reference to particle handler.
	ShopMenu*			m_pShopMenu;			// Reference to shop menu.	
	TextureHandler*		m_pTextureHandler;		// Reference to texture handler.
	HighscoreMenu*		m_pHighscoreMenu;		// Reference to Highscore Menu.
	HelpMenu*			m_pHelpMenu;			// Reference to Help Menu.

	sf::Clock			m_clock;				// Clock used for global update functions (keeps constant frame rate).
	sf::RenderWindow	m_displayWindow;		// Window to display the game.

	GameStates			m_currentState;			// Handles the current state of the game.

public:
	Game();		// Constructor.
	~Game();	// Deconstructor.
	
	void initialise();						// Initialiser.
	void update(float deltaTime);			// Update function.
	void render();							// Render function.

	void run();								// Run function for game.
	void handleWindowProperties();			// Function used for setting window properties.

	GameStates getCurrentState();			// Return current game state.
	void setCurrentState(GameStates state);	// Set the current game state.

	HighscoreMenu* getHighscoreMenu();
};

#endif //!GAME_H