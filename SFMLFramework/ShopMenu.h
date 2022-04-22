#ifndef SHOPMENU_H
#define SHOPMENU_H

#include "AudioHandler.h"
#include "EnemyHandler.h"
#include "GameText.h"
#include "Object.h"
#include "ObstacleHandler.h"
#include "Player.h"
#include "ProjectileHandler.h"

#include <SFML\Window\Keyboard.hpp>

class Game;
class MainGame;

class ShopMenu
{
private:
	AudioHandler*		m_pAudioHandler;
	EnemyHandler*		m_pEnemyHandler;		// Reference to enemy handler.
	Game*				m_pGame;				// Reference to game.
	ObstacleHandler*	m_pObstacleHandler;		// Reference to obstacle handler.
	Player*				m_pPlayer;				// Reference to player.
	ProjectileHandler*	m_pProjectileHandler;	// Reference to projectile handler.
	TextureHandler*		m_pTextureHandler;		// Reference to texture handler.
	MainGame*			m_pMainGame;

	Object*				m_pMenuSprites;			// Game shop menu sprites.
	GameText*			m_pUpgradeTitle;		// Game shop title.
	GameText*			m_pUpgradeDescription;	// Game shop description.
	GameText*			m_pTitles;				// Upgrade titles.
	GameText*			m_pDescriptions;		// Upgrade descriptions.
	GameText*			m_pInstructions;
	GameText*			m_pBankText;
	GameText*			m_pBankBalance;			// Used to draw game text to the window.
	GameText*			m_pCostText;			// Used to draw cost text to the window.
	GameText*			m_pCostBalance;			// Used to draw cost price to the window.
	GameText*			m_pUpgradeMaxed;		// Used to draw upgrade maxed text if the player has reached the upgrade limit for a specific item.

	int					m_shopState;			// Stores the players hover state to determine the upgrade they want to buy.
	int					m_itemCost[8];			// Stores the item cost.

	int					m_upgradeLimit[8];		// Stores the limit for each upgrade.
	int					m_currentUpgrade[8];	// Holds the current upgrade amount to compare against the limit.

	bool				m_isUpPressed;			// Bool to stop multiple key inputs.
	bool				m_isDownPressed;		// *
	bool				m_isLeftPressed;		// *
	bool				m_isRightPressed;		// *
	bool				m_isSpacePressed;		// *
	bool				m_correctFunds;			// Check for if the player has the correct funds to purchase an upgrade.
	bool				m_maxedUpgrade;			// Bool to handle rendering of the max upgrade text.
	bool				m_defaultBox;			// Bool to show default selection box as there are multiple based of upgrade state.

	float				m_timer;				// Used to determine how long colored selection box should be active.

public:
	ShopMenu();		// Constructor.
	~ShopMenu();	// Deconstructor.

	void initialise(MainGame* pMainGame, Game* pGame, TextureHandler* pTextureHandler, Player* pPlayer, ProjectileHandler* pProjectileHandler, ObstacleHandler* pObstacleHandler, EnemyHandler* pEnemyHandler, AudioHandler* pAudioHandler); // Initialiser.
	void update(float deltaTime);				// Update function.
	void render(sf::RenderTarget* window);		// Render function.

	void setUpgradeLimits();					// Set upgrade limits.
	void loadText();							// Load text required for upgrade titles and descriptions.
	void loadTextures();						// Load the textures required for the menu interface.
	void inputHandler(float deltaTime);			// Input handler used for selecting upgrades.
	void textHandler();							// This function handles updating the text displayed on screen dependant on what upgrade the user is hovering over.
	void upgradeHandler();						// This is called when the user selects an upgrade.
	void colorText();							// Color the text.
	void colorSelectionBox(float deltaTime);	// Handle the colors of the selection box.
	void resetUpgrades();						// Resets upgrades if the game restarts.
};

#endif //!GAME_H