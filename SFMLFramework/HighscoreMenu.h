#ifndef HIGHSCOREMENU_H
#define HIGHSCOREMENU_H

#include <fstream>
#include <iostream>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>

#include "GameSprite.h"
#include "GameText.h"

class Game;
class MainGame;
class Player;
class TextureHandler;

struct HighscoreData // Struct for data used to store player data.
{
	std::string	name;
	int			score;
};

class HighscoreMenu
{
private:
	HighscoreData		m_highscoreData[21];	// Array of structs used for highscore table.

	sf::RenderWindow*	m_pRenderWindow;		// Reference to the render window to handle 'close' event.
	Game*				m_pGame;				// Reference to the Game object.
	MainGame*			m_pMainGame;			// Reference to the Main Game object.
	Player*				m_pPlayer;				// Reference to the Player object.
	TextureHandler*		m_pTextureHandler;		// Reference to the Texture Handler.

	GameSprite*			m_pCursor;				// Used to display a blinking cursor on screen.

	GameText*			m_pHighscore;			// Gametext object to display highscore text.
	GameText*			m_pEnterName;			// Gametext to display enter name text.
	GameText*			m_pPlayerName;			// Gametext to display players name.
	GameText*			m_pHighscoreName;		// Gametext to display the highscore names.
	GameText*			m_pHighscoreScore;		// Gametext to display the highscore scores.
	GameText*			m_returnToMenu;			// Gametext to display return to menu text.

	float				m_flashTimer;			// Float to handle flash timer.
	float				m_cursorTimer;			// Float to handle cursor flashing.

	int					m_characterEntered;		// Used to make sure player has entered 4 characters.

	bool				m_isBackspacePressed;	// Check for if space is pressed to stop multiple inputs.
	bool				m_isEnterPressed;		// Check to see if enter is pressed to stop multiple inputs.
	bool				m_cursorFlash;			// Check to allow for cursor to flash.
	bool				m_nameEntered;			// Check to see if the player has entered their name.

	std::string			m_name;					// String that holds the players name.

public:
	HighscoreMenu();	// Constructor.
	~HighscoreMenu();	// Deconstructor.

	void initialise(Game* pGame, MainGame* pMainGame, TextureHandler* pTextureHandler, sf::RenderWindow* pRenderWindow, Player* pPlayer); // Initialise function.
	void update(float deltaTime);			// Update function.
	void render(sf::RenderTarget* window);	// Render function.

	void userInput();						// Function to handle user input.
	void loadHighscoresFromFile();			// Function that handles loading the highscores from file.
	void writeHighscoresToFile();			// Function that writes the new highscore to file.
	void sortHighscores();					// Function that sorts highscore array values in descending order.
	void displayHighscores();				// Function that draws the highscores to the window.
	void flashEffect(float deltaTime);		// Function that handles flashing of the 'Highscores' text.
	void colorNewHighscoreEntry();			// Function to highlight the players name and score on the highscore board if they make achieve a highscore.
	void cursorHandler(float deltaTime);	// Function to handle the cursor flashing.

	void returnToMenu(bool canReturn);
};

#endif //!HIGHSCOREMENU_H