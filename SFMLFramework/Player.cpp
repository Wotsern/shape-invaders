#include <conio.h>
#include <iostream>
#include <sstream>

#include <SFML\Window\Keyboard.hpp>

#include "EnemyHandler.h"
#include "Game.h"
#include "Helpers.h"
#include "Object.h"
#include "ParticleHandler.h"
#include "Player.h"
#include "PlayerProjectile.h"
#include "MainGame.h"
#include "Settings.h"

Player::Player()
{
	m_pAudioHandler				= nullptr;
	m_pProjectileHandler		= nullptr;
	m_pTextureHandler			= nullptr;
	m_pEnemyHandler				= nullptr;
	m_pMainGame					= nullptr;
	m_pParticleHandler			= nullptr;
	m_pCollider					= new Collider();

	m_pGame						= nullptr;

	m_pBankText					= new GameText();
	m_pBankBalance				= new GameText();
	m_pGameOver					= new GameText();
	m_pHealthBar				= new GameSprite();
	m_pCountdown				= new GameText();
	m_pHearts					= new GameSprite[3];

	m_doubleTapChance			= PlayerProperties::c_doubleTapChance;

	m_speed						= PlayerProperties::c_speed;
	m_timer						= 3;

	m_lives						= PlayerProperties::c_playerLives;
	m_health					= PlayerProperties::c_health;
	m_score						= 0;
	m_bank						= 0;
	m_doubleTapChance			= PlayerProperties::c_doubleTapChance;

	m_canShoot					= false;
	m_isSpaceDown				= false;
	m_isActive					= true;
	m_canMove					= true;
	m_beginLevel				= false;
	m_gameOver					= false;
	m_canDoubleTap				= false;

	setPlayerProperties();
}

Player::~Player()
{
	safeDeletePointer(m_pCollider);
	safeDeletePointer(m_pBankText);
	safeDeletePointer(m_pBankBalance);
	safeDeletePointer(m_pGameOver);
	safeDeletePointer(m_pHealthBar);
	safeDeletePointer(m_pCountdown);
	safeDeletePointerArray(m_pHearts);
}

void Player::initialise(MainGame* pMainGame, ProjectileHandler* projectileHandler, TextureHandler* pTextureHandler, Game* pGame, EnemyHandler* pEnemyHandler, ParticleHandler* pParticleHandler, AudioHandler* pAudioHandler)
{
	m_pAudioHandler = pAudioHandler;
	// Initialise a collider for the player.
	m_pCollider->initialise(32, getPosition());
	// Set the Projectile Handler.
	m_pProjectileHandler = projectileHandler;
	// Set the Texture Handler.
	m_pTextureHandler = pTextureHandler;
	// Set the Game reference.
	m_pGame = pGame;
	// Set the Enemy Handler.
	m_pEnemyHandler = pEnemyHandler;
	// Set the Main Game reference.
	m_pMainGame = pMainGame;
	// Set the Particle Handler.
	m_pParticleHandler = pParticleHandler;

	// Set the desired text and texture needed alongside position and scale.
	setTexture(m_pTextureHandler->getTexture(TextureType::Player));
	m_pHealthBar->setTexture(m_pTextureHandler->getTexture(TextureType::Health100));
	m_pHealthBar->setPosition(600, 875);

	m_pBankText->initialise(Fonts::SciFi);
	m_pBankText->setPosition(15, 900);
	m_pBankText->setScale(0.5f, 0.5f);
	m_pBankText->setString("BANK");

	m_pBankBalance->initialise(Fonts::Jersey);
	m_pBankBalance->setPosition(80, 900);
	m_pBankBalance->setScale(0.5f, 0.5f);

	m_pCountdown->initialise(Fonts::Jersey);
	m_pCountdown->setPosition(275, 100);
	m_pCountdown->setCharacterSize(500);

	m_pGameOver->initialise(Fonts::SciFi);
	m_pGameOver->setString("GAME\nOVER");
	m_pGameOver->setCharacterSize(200);
	m_pGameOver->setPosition(180, 125);

	int xPos = 535;
	for (int i = 0; i < PlayerProperties::c_playerLives; i++)
	{
		m_pHearts[i].setTexture(m_pTextureHandler->getTexture(TextureType::Heart));
		m_pHearts[i].setPosition(xPos, 875);
		xPos -= 50;
	}
}

void Player::initialise()
{
	
}

void Player::update(float deltaTime)
{	
	if (m_isActive == true)
	{
		m_pCollider->setPosition(getPosition());	// Always update collider position to player position.
		movementHandler(deltaTime);					// Constantly check for user input.
		projectileHandler();						// Constantly call for new projectiles if the count has been added to.
		checkPlayerHealth();						// Function to check the players current health.
		checkPlayerLives(deltaTime);				// Function to handle player lives.
		userInterface();							// Function to keep user interface updated.
		countdown(deltaTime);						// Function to handle countdown.
	}
}

void Player::render(sf::RenderTarget* window)
{
	if (m_isActive == true)
	{
		m_pBankText->render(window);
		m_pBankBalance->render(window);
		m_pCollider->render(window);
		window->draw(*m_pHealthBar);
		
		// Draw the player to the screen.
		if (m_gameOver == false && m_isDead == false)
		{
			window->draw(*this);
		}

		// Display the correct amount of lives dependant on how many lives the player has.
		for (int i = 0; i < m_lives; i++)
		{
			window->draw(m_pHearts[i]);
		}

		// If a new level loads, this will display as the level has not begun.
		if (m_beginLevel == false)
		{
			window->draw(*m_pCountdown);
		}

		// If the game is over, this will display.
		if (m_gameOver == true)
		{
			window->draw(*m_pGameOver);
		}
	}
}

void Player::movementHandler(float deltaTime)
{
	// Reset rotation if no keys are pressed.
	setRotation(0);

	// Check for if the player can move or not.
	if (m_canMove == true)
	{
		// Check for if 'UP' key is pressed.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && getPosition().y > PlayerProperties::c_topBoundary)
		{
			move(0, -m_speed * deltaTime); // Move the player up the Y axis.
		}
		// Check for if the 'DOWN' key is pressed.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && getPosition().y < PlayerProperties::c_bottomBoundary)
		{
			move(0, m_speed * deltaTime); // Move the player down the Y axis.
		}
		// Check for if the 'LEFT' key is pressed.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getPosition().x > 10)
		{
			move(-m_speed * deltaTime, 0);	// Move the player down the X axis.
			setRotation(-10.0f);			// Rotate the sprite for effect.
		}
		// Check for if the 'RIGHT' key is pressed.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getPosition().x < 720)
		{
			move(m_speed * deltaTime, 0);	// Move the player up the X axis.
			setRotation(10.0f);				// Rotate the sprite for effect.
		}
	}
}

void Player::projectileHandler()
{
	// Check for if the space key is pressed.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// Check for is the player is able to shoot.
		if (m_isSpaceDown == false && m_canShoot == true)
		{
			m_pAudioHandler->playSound(SoundEffect::FireProjectile);
			m_isSpaceDown = true;
			// Spawn a projectile with the correct properties.
			m_pProjectileHandler->spawnProjectile(sf::Vector2f(getPosition().x, getPosition().y - 20), 0, -1, true, ProjectileType::Player);
			doubleTap();
		}
	}
	else
	{
		// Reset space down.
		m_isSpaceDown = false;
	}
}

void Player::checkPlayerHealth()
{
	// Check to see if the player has died.
	if (m_health <= 0 && m_isDead == false)
	{
		// Hide collider.
		m_pCollider->setRadius(0);
		// Set player dead to true.
		m_isDead = true;
		// Disable player movement.
		m_canMove = false;
		// Spawn particles.
			m_pParticleHandler->playerParticles();
	}
}

void Player::checkPlayerLives(float deltaTime)
{
	// If the player has no lives left then this function will run and reset the game and its properties.
	if (m_lives == 0)
	{
		m_isDead = true;
		m_gameOver = true;
		m_timer -= deltaTime;
		if (m_timer <= 0)
		{
			m_gameOver = false;
			// Reset the entire game.
			m_pMainGame->resetGame();
			m_pGame->getHighscoreMenu()->returnToMenu(false);
			// Change the current game state to the Highscore Menu.
			m_pGame->setCurrentState(GameStates::HighscoreMenu);
		}
	}

	if (m_beginLevel == true)
	{
		// Disable all movement if the player is dead.
		if (m_isDead == true)
		{
			m_canMove = false;
			m_canShoot = false;
		}
		else
		{
			m_canMove = true;
			m_canShoot = true;
		}
	}
}

void Player::userInterface()
{
	// Get all desired textures used for the healthbar.
	std::stringstream bankBalance;
	bankBalance << m_bank;
	m_pBankBalance->setString(bankBalance.str());

	switch (m_health)
	{
	case 10: case 9:
		m_pHealthBar->setTexture(m_pTextureHandler->getTexture(TextureType::Health100));
		break;
	case 8: case 7:
		m_pHealthBar->setTexture(m_pTextureHandler->getTexture(TextureType::Health80));
		break;
	case 6: case 5:
		m_pHealthBar->setTexture(m_pTextureHandler->getTexture(TextureType::Health60));
		break;
	case 4: case 3:
		m_pHealthBar->setTexture(m_pTextureHandler->getTexture(TextureType::Health40));
		break;
	case 2: case 1:
		m_pHealthBar->setTexture(m_pTextureHandler->getTexture(TextureType::Health20));
		break;
	}
}

void Player::countdown(float deltaTime)
{
	// If the level has not yet begun, this will run.
	// It is used to display the level countdown text.
	if (m_beginLevel == false)
	{
		m_timer -= deltaTime;
		if (m_timer <= 0)
		{
			m_timer = 3;
			m_canShoot = true;
			m_beginLevel = true;
		}
	}	

	// Set text to the correct number.
	if (m_timer > 0 && m_timer <= 1)
	{
		m_pCountdown->setPosition(320, 100);
		m_pCountdown->setFillColor(sf::Color(255,0,0,100)); //Red.
		m_pCountdown->setString("1");
	}
	if (m_timer > 1 && m_timer <= 2)
	{
		m_pCountdown->setPosition(275, 100);
		m_pCountdown->setFillColor(sf::Color(255,165,0,100)); //Amber.
		m_pCountdown->setString("2");
	}
	if (m_timer > 2 && m_timer <= 3)
	{
		m_pCountdown->setPosition(275, 100);
		m_pCountdown->setFillColor(sf::Color(0,100,0,100)); //Green.
		m_pCountdown->setString("3");
	}
}

void Player::doubleTap()
{
	// If the player has upgraded to double tap, this code will execute giving the projectiles a change to tag team.
	if (m_canDoubleTap == true)
	{
		int _random = rand() % m_doubleTapChance;
		if (_random == 4)
		{
			// If the number is 4, another projectile will spawn, following the previous one.
			m_pProjectileHandler->spawnProjectile(sf::Vector2f(getPosition().x, getPosition().y - 60), 0, -1, true, ProjectileType::Player);
		}
	}
}

// Return the collider attached to this object.
Collider* Player::getCollider()
{
	return m_pCollider;
}

// Return the level begin state.
bool Player::getLevelBegin()
{
	return m_beginLevel;
}

// Set the level begin state.
void Player::setLevelBegin(bool begin)
{
	m_beginLevel = begin;
}

// Return the player dead state.
bool Player::getPlayerDead()
{
	return m_isDead;
}

// Set the player dead state.
void Player::setPlayerDead(bool dead)
{
	m_isDead = dead;
}

// Set the shoot state.
void Player::setCanShoot(bool canShoot)
{
	m_canShoot = canShoot;
}

// Set the double tap state.
void Player::setCanDoubleTap(bool doubleTap)
{
	m_canDoubleTap = doubleTap;
}

// Set the players health.
void Player::setHealth(int health)
{
	m_health = health;
}

// Return the double tap chance.
int Player::getDoubleTapChance()
{
	return m_doubleTapChance;
}

// Set the double tap chance.
void Player::setDoubleTapChance(int chance)
{
	m_doubleTapChance = chance;
}

// Return the player lives.
int Player::getLives()
{
	return m_lives;
}

// Set the player lives.
void Player::setLives(int lives)
{
	m_lives = lives;
}

// Return the player health.
int Player::getHealth()
{
	return m_health;
}

// Return the speed of the
float Player::getSpeed()
{
	return m_speed;
}

// Set the speed of the player.
void Player::setSpeed(float speed)
{
	m_speed = speed;
}

// Return players current score.
int Player::getScore()
{
	return m_score;
}

// Set the players current score.
void Player::setScore(int score)
{
	m_score = score;
}

// Set the bank value.
void Player::setBank(int bank)
{
	m_bank = bank;
}

// Return the bank value.
int Player::getBank()
{
	return m_bank;
}

// Set the player properties.
void Player::setPlayerProperties()
{
	if (m_lives == 0)
	{
		m_bank = 0;
		m_speed = PlayerProperties::c_speed;
		m_lives = PlayerProperties::c_playerLives;
	}
	setOrigin(32, 32);
	setPosition(PlayerProperties::c_startingPosX, PlayerProperties::c_startingPosY);
	setRectSourceSprite(64, 64);

	m_timer = 3;

	m_isActive = true;
	m_isSpaceDown = false;
	m_beginLevel = false;
	m_gameOver = false;

	m_health = PlayerProperties::c_health;
}