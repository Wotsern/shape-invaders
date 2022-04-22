#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Game.h"
#include "Helpers.h"
#include "Settings.h"
#include <iostream>

void Game::handleWindowProperties()
{
    sf::Event event;
    while (m_displayWindow.pollEvent(event))
    {
		if (event.type == sf::Event::Closed) 
		{
			m_displayWindow.close();
		}
    }
}

Game::Game()
{
	// Load all class pointers.
	m_pAudioHandler			= new AudioHandler;
	m_pMainMenu				= new MainMenu;
	m_pTextureHandler		= new TextureHandler;
	m_pParticleHandler		= new ParticleHandler;
	m_pShopMenu				= new ShopMenu;
	m_pMainGame				= new MainGame;
	m_pHighscoreMenu		= new HighscoreMenu;
	m_pHelpMenu				= new HelpMenu;
	initialise();
}

Game::~Game()
{
	// Safe delete all pointers.
	safeDeletePointer(m_pAudioHandler);
	safeDeletePointer(m_pMainMenu);
	safeDeletePointer(m_pTextureHandler);
	safeDeletePointer(m_pParticleHandler);
	safeDeletePointer(m_pShopMenu);
	safeDeletePointer(m_pMainGame);
	safeDeletePointer(m_pHighscoreMenu);
	safeDeletePointer(m_pHelpMenu);
}

void Game::run()
{
	// Deltatime used for constant fps.
	float deltaTime = 0.0f;

	m_currentState = GameStates::StartMenu;
	m_displayWindow.create(sf::VideoMode(WindowProperties::c_width, WindowProperties::c_height), WindowProperties::c_title);
	m_displayWindow.setPosition(sf::Vector2i(WindowProperties::c_posX, WindowProperties::c_posY));
	
	while (m_displayWindow.isOpen())
	{
		deltaTime = m_clock.restart().asSeconds();
		if (m_currentState != GameStates::HighscoreMenu)
		{
			handleWindowProperties();
		}
		m_displayWindow.clear(sf::Color(0, 14, 23, 23));
		update(deltaTime);
		render();
		m_displayWindow.display();
	}
}

void Game::initialise()
{
	// Initialise all pointers while passing through the correct parameters needed for other classes within the game.
	m_pTextureHandler->initialise();
	m_pParticleHandler->initialise(m_pTextureHandler, m_pMainGame->getPlayer());
	m_pMainGame->initialise(m_pTextureHandler, this, m_pParticleHandler, m_pAudioHandler);
	m_pMainMenu->initialise(this, m_pMainGame->getEnemyHandler(), m_pHighscoreMenu, m_pTextureHandler, m_pAudioHandler);
	m_pShopMenu->initialise(m_pMainGame, this, m_pTextureHandler, m_pMainGame->getPlayer(), m_pMainGame->getProjectileHandler(), m_pMainGame->getObstacleHandler(), m_pMainGame->getEnemyHandler(), m_pAudioHandler);
	m_pHighscoreMenu->initialise(this, m_pMainGame, m_pTextureHandler, &m_displayWindow, m_pMainGame->getPlayer());
	m_pHelpMenu->initialise(m_pTextureHandler, this);
	m_pAudioHandler->playSound(SoundEffect::BackgroundMusic);
}

void Game::update(float deltaTime)
{		
	// Switch to handle what should be updated based on the current Game State.
	switch (m_currentState)
	{
	case GameStates::StartMenu:
		m_pParticleHandler->update(deltaTime);
		m_pMainMenu->update(deltaTime);
		break;
	case GameStates::MainGame:
		m_pParticleHandler->update(deltaTime);
		m_pMainGame->update(deltaTime);
		break;
	case GameStates::Shop:
		m_pParticleHandler->update(deltaTime);
		m_pShopMenu->update(deltaTime);
		break;
	case GameStates::HighscoreMenu:
		m_pParticleHandler->update(deltaTime);
		m_pHighscoreMenu->update(deltaTime);
		break;
	case GameStates::HelpMenu:
		m_pParticleHandler->update(deltaTime);
		m_pHelpMenu->update(deltaTime);
		break;
	}

	// This allows for the screen to shake if the global bool is set to true.
	if (screenShake == true) {
		m_displayWindow.setPosition(sf::Vector2i(500 + rand() % 10, 20 + rand() % 10));
	}
}

void Game::render()
{
	// Switch to handle what should be rendered based on the current Game State.
	switch (m_currentState)
	{
	case GameStates::StartMenu:
		m_pParticleHandler->render(&m_displayWindow);
		m_pMainMenu->render(&m_displayWindow);
		break;
	case GameStates::MainGame:
		m_pParticleHandler->render(&m_displayWindow);
		m_pMainGame->render(&m_displayWindow);
		break;
	case GameStates::Shop:
		m_pParticleHandler->render(&m_displayWindow);
		m_pShopMenu->render(&m_displayWindow);
		break;
	case GameStates::HighscoreMenu:
		m_pParticleHandler->render(&m_displayWindow);
		m_pHighscoreMenu->render(&m_displayWindow);
		break;
	case GameStates::HelpMenu:
		m_pParticleHandler->render(&m_displayWindow);
		m_pHelpMenu->render(&m_displayWindow);
		break;
	}
}

//  Return the current game state.
GameStates Game::getCurrentState()
{
	return m_currentState;
}

// Set the current game state.
void Game::setCurrentState(GameStates state)
{
	m_currentState = state;
}

// Return the highscore menu.
HighscoreMenu* Game::getHighscoreMenu()
{
	return m_pHighscoreMenu;
}
