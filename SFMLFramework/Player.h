#ifndef PLAYER_H
#define PLAYER_H

#include "AudioHandler.h"
#include "Collider.h"
#include "GameSprite.h"
#include "GameText.h"
#include "Object.h"
#include "ProjectileHandler.h"
#include "TextureHandler.h"

class EnemyHandler;
class Game;
class MainGame;
class ParticleHandler;

class Player : public Object
{
private:
	AudioHandler*		m_pAudioHandler;
	ProjectileHandler*	m_pProjectileHandler;	// Used to reference the projectile handler.
	TextureHandler*		m_pTextureHandler;		// Used to reference the texture handler.
	EnemyHandler*		m_pEnemyHandler;		// Used to reference the Enemy Handler.
	MainGame*			m_pMainGame;			// Used to reference the Main Game.
	ParticleHandler*	m_pParticleHandler;		// Used to reference the Particle Handler.
	Collider*			m_pCollider;			// Used to reference the collider.
	Game*				m_pGame;				// Used to reference the game object.
	
	GameText*			m_pCountdown;			// Gametext object for countdown.
	GameText*			m_pBankText;			// Gametext object for bank text.
	GameText*			m_pBankBalance;			// Gametext object for bank balance.
	GameText*			m_pGameOver;			// Gametext for game over text.
	GameSprite*			m_pHealthBar;			// Gamesprite to display the current health as a healthbar.
	GameSprite*			m_pHearts;				// Gamesprite to display player lives to screen.

	sf::Vector2f		m_position;				// Used for positioning of the player.

	float				m_speed;				// Used to set the speed of the players movement.
	float				m_timer;				// Timer used for countdown.

	int					m_lives;				// Used to hold the amount of lives the player has during gametime.
	int					m_health;				// Holds the health of the player.
	int					m_score;				// Holds the score of the player.
	int					m_bank;					// Holds the bank balance of the player.
	int					m_doubleTapChance;

	bool				m_canShoot;				// Used to enable/disable the player being able to shoot.
	bool				m_isSpaceDown;			// Used to stop the player shooting multiple bullets at once.
	bool				m_isActive;				// Used for update and render functions.
	bool				m_isDead;				// Used to check if the player is dead or alive.
	bool				m_canMove;				// Used to enable/disable player movement.
	bool				m_beginLevel;			// Used to determine what Gamesprites are to show on screen.
	bool				m_gameOver;				// Used to check if the game is finished.
	bool				m_canDoubleTap;			// Used to check if the players double tap upgrade is enabled.

public:
	Player();	// Constructor.
	~Player();	// Deconstructor.

	void initialise(MainGame* pMainGame, ProjectileHandler* projectileHandler, TextureHandler* pTextureHandler, Game* pGame, EnemyHandler* pEnemyHandler, ParticleHandler* pParticleHandler, AudioHandler* pAudioHandler); // Initialiser.
	void initialise(); // Initialiser.
	virtual void update(float deltaTime);					// Update function.
	virtual void render(sf::RenderTarget* window) override; // Render function.
	
	void setPlayerProperties();				// Function to set the player properties.
	void checkPlayerHealth();				// Function to check the players health.
	void checkPlayerLives(float deltaTime);	// Function to check the players lives.
	void movementHandler(float deltaTime);	// Movement handler.
	void projectileHandler();				// Function for handling projectile spawns.
	void userInterface();					// Function that handles user interface.
	void countdown(float deltaTime);		// Function that is used to display the countdown.
	void doubleTap();						// Function that handles the double tap upgrade if it is enabled.

	Collider* getCollider();				// Return the players collider.

	bool getLevelBegin();					// Return to check for if the level has began.
	void setLevelBegin(bool begin);			// Setter for if the level has began or not.
	
	bool getPlayerDead();					// Return the current player dead status.
	void setPlayerDead(bool dead);			// Set the player dead status.

	void setCanShoot(bool canShoot);		// Set if the player can shoot or not.
	void setCanDoubleTap(bool doubleTap);	// Set if the player is able to doubletap.

	int getHealth();						// Return the players health.
	void setHealth(int health);				// Set the players health.
	
	int getDoubleTapChance();				// Return the players health.
	void setDoubleTapChance(int chance);	// Set the players health.

	int getLives();							// Return the players health.
	void setLives(int lives);				// Set the players health.

	float getSpeed();						// Return the players speed.
	void setSpeed(float speed);				// Set the movement speed of the player.

	int getScore();							// Return the bank balance.
	void setScore(int score);				// Set the bank balance.

	int getBank();							// Return the bank balance.
	void setBank(int money);				// Set the bank balance.
};

#endif //!PLAYER_H