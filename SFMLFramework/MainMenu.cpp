#include "EnemyHandler.h"
#include "Game.h"
#include "Helpers.h"
#include "HighscoreMenu.h"
#include "MainMenu.h"

#include <SFML\Window\Keyboard.hpp>

MainMenu::MainMenu()
{
	m_pAudioHandler		= nullptr;
	m_pGame				= nullptr;
	m_pEnemyHandler		= nullptr;
	m_pHighscoreMenu	= nullptr;

	m_pGameText			= new GameText[5];

	m_pMascot			= new GameSprite();

	m_buttonState		= 0;
	m_isUpPressed		= false;
	m_isDownPressed		= false;
}

MainMenu::~MainMenu()
{
	// Delete GameText array.
	safeDeletePointerArray(m_pGameText);
	safeDeletePointer(m_pMascot);
}

void MainMenu::initialise(Game* pGame, EnemyHandler* pEnemyHandler, HighscoreMenu* pHighscoreMenu, TextureHandler* pTextureHandler, AudioHandler* pAudioHandler)
{
	m_pAudioHandler = pAudioHandler;
	m_pGame = pGame;
	m_pEnemyHandler = pEnemyHandler;
	m_pHighscoreMenu = pHighscoreMenu;

	// Initialise Main Menu text, initialising them with the SciFi font.
	for (int i = 0; i < 4; i++) 
	{
		m_pGameText[i].initialise(Fonts::SciFi);
	}

	// Initialise this specific GameText as arial as it is a symbol and SciFi font doesn't support symbols.
	m_pGameText[4].initialise(Fonts::Arial);


	// Set the different strings correctly ready to be rendered.
	m_pGameText[0].setString("Start Invasion");
	m_pGameText[1].setString("How to Play");
	m_pGameText[2].setString("Highscores");
	m_pGameText[3].setString("Exit");
	m_pGameText[4].setString(">");

	// Set all positions.
	m_pGameText[0].setPosition(230, 580);
	m_pGameText[1].setPosition(260, 650);
	m_pGameText[2].setPosition(280, 720);
	m_pGameText[3].setPosition(355, 790);
	m_pGameText[4].setPosition(195, 860);

	m_pMascot->setTexture(pTextureHandler->getTexture(TextureType::Mascot));
}

void MainMenu::update(float deltaTime)
{
	// This is to stop the player from accidently starting the game on start-up.
	m_inputTimer += deltaTime;
	if (m_inputTimer > 0.5f)
	{
		inputHandler();
	}
}

void MainMenu::render(sf::RenderTarget* window)
{
	// Render each button texts to the screen.
	for (int i = 0; i < 4; i++)
	{
		m_pGameText[i].render(window);
	}
	window->draw(*m_pMascot);
}

void MainMenu::inputHandler()
{
	// Check for if the 'DOWN' key is pressed.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_buttonState < 3)
	{
		// This bool stops the user input being recongised more thann once (stops loop).
		if (m_isDownPressed == false)
		{
			// Increase the button state count for game navigation.
			m_buttonState++;
			m_isDownPressed = true;
			m_pAudioHandler->playSound(SoundEffect::MenuButton);
			// Set the position of the cursor.
			m_pGameText[4].setPosition(m_pGameText[4].getPosition().x, m_pGameText[m_buttonState].getPosition().y);
		}
	}
	else
	{
		m_isDownPressed = false;
	} 
	// Check for if the 'UP' key was pressed.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_buttonState > 0)
	{
		// Stop loop.
		if (m_isUpPressed == false)
		{
			m_buttonState--;
			m_isUpPressed = true;
			m_pAudioHandler->playSound(SoundEffect::MenuButton); 
			// Set the position of the cursor.
			m_pGameText[4].setPosition(m_pGameText[4].getPosition().x, m_pGameText[m_buttonState].getPosition().y);
		}
	}
	else
	{
		m_isUpPressed = false;
		// Set the text to the correct colours.
		colorText();
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_pAudioHandler->playSound(SoundEffect::SelectionBox);
		m_inputTimer = 0;
		switch (m_buttonState)
		{
			// Navigate the player to the Main Game.
		case 0:
			m_pGame->setCurrentState(GameStates::MainGame);
			break;
		case 1:
			m_pGame->setCurrentState(GameStates::HelpMenu);
			// Navigate the player to the 'How to play' menu.
			break;
		case 2:
			// Navigate the player to the Highscore Menu.
			m_pHighscoreMenu->returnToMenu(true);
			m_pGame->setCurrentState(GameStates::HighscoreMenu);
			break;
		case 3:
			// Exit out of the game.
			exit(0);
			break;
		}
	}
}

void MainMenu::colorText()
{
	// Set all text color to white.
	for (int i = 0; i < 4; i++)
	{
		m_pGameText[i].setFillColor(sf::Color::White);
	}
	// Set the current button state game text to green.
	m_pGameText[m_buttonState].setFillColor(sf::Color::Green);
}
