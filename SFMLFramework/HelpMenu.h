#ifndef HELPMENU_H
#define HELPMENU_H

#include "GameSprite.h"
#include "TextureHandler.h"

class Game;
class Player;
class ProjectileHandler;

class HelpMenu
{
private:
	Game*				m_pGame;				// Reference to the Game.

	GameSprite*			m_pHowToPlay;			// Sprite used for displaying instructions.

	float				m_timer;				// Timer to limit user input events.
	bool				m_isEnterPressed;		// Bool to check if enter is pressed.

public:
	HelpMenu();		// Constructor.
	~HelpMenu();	// Deconstructor.

	void initialise(TextureHandler* pTextureHandler, Game* pGame); // Initialiser.
	void update(float deltaTime);				// Update function.
	void render(sf::RenderTarget* window);		// Render function.

	void inputHandler(); // Check for user input.
};

#endif //!HELPMENU_H