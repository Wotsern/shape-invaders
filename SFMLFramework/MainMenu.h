#ifndef MAINMENU_H
#define MAINMENU_H

#include "AudioHandler.h"
#include "GameText.h"

class EnemyHandler;
class Game; //Game class reference.
class HighscoreMenu;

class MainMenu
{
private:
	AudioHandler*		m_pAudioHandler;
	Game*				m_pGame;			// Pointer to game.
	GameText*			m_pGameText;		// Used for an array of text to show on the menu.
	EnemyHandler*		m_pEnemyHandler;
	HighscoreMenu*		m_pHighscoreMenu;
	GameSprite*			m_pMascot;

	int					m_buttonState;		// Used to locate the player to the correct state based on button choice.

	bool				m_isUpPressed;		// Bool used to stop multiple inputs.
	bool				m_isDownPressed;	// Bool used to stop multiple inputs.

	float				m_inputTimer;		// Float used to display user input.

public:
	MainMenu();		// Constructor.
	~MainMenu();	// Deconstructor.

	void initialise(Game* pGame, EnemyHandler* pEnemyHandler, HighscoreMenu* pHighscoremenu, TextureHandler* pTextureHandler, AudioHandler* pAudioHandler);	// Initialiser.
	void update(float deltaTime);								// Update function.
	void render(sf::RenderTarget* window);						// Render function.

	void inputHandler();	// Input handler used for button selection.
	void colorText();		// Handles the text colouring so the player can see selection.
};

#endif //!GAME_H