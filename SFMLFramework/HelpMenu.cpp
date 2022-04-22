#include "Game.h"
#include "HelpMenu.h"
#include "Helpers.h"
#include "Player.h"
#include "Settings.h"
#include <SFML\Window\Keyboard.hpp>

HelpMenu::HelpMenu()
{
	m_pGame = nullptr;
	m_pHowToPlay = new GameSprite;

	m_isEnterPressed = false;

	m_timer = 0;
}

HelpMenu::~HelpMenu()
{
	// Safe delete pointer.
	safeDeletePointer(m_pHowToPlay);
}

void HelpMenu::initialise(TextureHandler* pTextureHandler,	Game* pGame)
{
	// Reference the game object.
	m_pGame = pGame;
	// Set the texture of 'How to play'.
	m_pHowToPlay->setTexture(pTextureHandler->getTexture(TextureType::HowToPlay));
}

void HelpMenu::update(float deltaTime)
{
	// Stop the user from pressing too fast.
	m_timer += deltaTime;
	if (m_timer > 1)
	{
		inputHandler();
	}
}

void HelpMenu::render(sf::RenderTarget* window)
{
	// Render the how to play instructions to the screen.
	window->draw(*m_pHowToPlay);
}

void HelpMenu::inputHandler()
{
	// Check for 'ENTER' key pressed.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_isEnterPressed == false)
	{
		m_timer = 0;
		m_isEnterPressed = true;
		// Redirect the player to the main menu.
		m_pGame->setCurrentState(GameStates::StartMenu);
	}
	else
	{
		m_isEnterPressed = false;
	}
}
