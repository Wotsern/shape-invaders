#include "Helpers.h"
#include "ShopMenu.h"
#include "Game.h"
#include <iostream>
#include <sstream>

ShopMenu::ShopMenu()
{
	m_pAudioHandler			= nullptr;
	m_pEnemyHandler			= nullptr;
	m_pGame					= nullptr;
	m_pObstacleHandler		= nullptr;
	m_pPlayer				= nullptr;
	m_pProjectileHandler	= nullptr;
	m_pTextureHandler		= nullptr;
	m_pMainGame				= nullptr;

	m_pMenuSprites			= new Object[2];
	m_pUpgradeTitle			= new GameText();
	m_pUpgradeDescription	= new GameText();
	m_pTitles				= new GameText[8];
	m_pDescriptions			= new GameText[8];
	m_pInstructions			= new GameText[2];
	m_pBankText				= new GameText();
	m_pBankBalance			= new GameText();
	m_pCostText				= new GameText();
	m_pCostBalance			= new GameText();
	m_pUpgradeMaxed			= new GameText();

	m_shopState				= 0;

	m_isUpPressed			= false;
	m_isDownPressed			= false;
	m_isLeftPressed			= false;
	m_isRightPressed		= false;
	m_isSpacePressed		= false;
	m_correctFunds			= false;
	m_maxedUpgrade			= false;
	m_defaultBox			= true;

	m_timer					= 0;
}

ShopMenu::~ShopMenu()
{
	safeDeletePointerArray(m_pMenuSprites);
	safeDeletePointer(m_pUpgradeTitle);
	safeDeletePointer(m_pUpgradeDescription);
	safeDeletePointerArray(m_pTitles);
	safeDeletePointerArray(m_pDescriptions);
	safeDeletePointerArray(m_pInstructions);
	safeDeletePointer(m_pBankText);
	safeDeletePointer(m_pBankBalance);
	safeDeletePointer(m_pCostText);
	safeDeletePointer(m_pCostBalance);
	safeDeletePointer(m_pUpgradeMaxed);
}

void ShopMenu::initialise(MainGame* pMainGame, Game* pGame, TextureHandler* pTextureHandler, Player* pPlayer, ProjectileHandler* pProjectileHandler, ObstacleHandler* pObstacleHandler, EnemyHandler* pEnemyHandler, AudioHandler* pAudioHandler)
{
	m_pAudioHandler = pAudioHandler;
	m_pGame = pGame;
	m_pTextureHandler = pTextureHandler;
	m_pPlayer = pPlayer;
	m_pProjectileHandler = pProjectileHandler;
	m_pObstacleHandler = pObstacleHandler;
	m_pEnemyHandler = pEnemyHandler;
	m_pMainGame = pMainGame;

	m_pUpgradeTitle->initialise(Fonts::SciFi);
	m_pUpgradeTitle->setScale(0.5f, 0.5f);
	m_pUpgradeTitle->setPosition(60, 710);

	m_pUpgradeDescription->initialise(Fonts::SciFi);
	m_pUpgradeDescription->setScale(0.5f, 0.5f);
	m_pUpgradeDescription->setPosition(60, 750);

	for (int i = 0; i < 2; i++)
	{
		m_pInstructions[i].initialise(Fonts::SciFi);
		m_pInstructions[i].setScale(0.5f, 0.5f);
	}

	m_pInstructions[0].setPosition(550, 20);
	m_pInstructions[1].setPosition(440, 860);

	m_pBankText->initialise(Fonts::SciFi);
	m_pBankText->setPosition(15, 20);
	m_pBankText->setScale(0.5f, 0.5f);
	m_pBankText->setString("BANK BALANCE");

	m_pBankBalance->initialise(Fonts::Jersey);
	m_pBankBalance->setPosition(15, 50);
	m_pBankBalance->setScale(1.0f, 1.0f);
	m_pBankBalance->setFillColor(sf::Color(0, 128, 0, 200));

	m_pCostText->initialise(Fonts::SciFi);
	m_pCostText->setPosition(60, 865);
	m_pCostText->setScale(0.5f, 0.5f);

	m_pCostBalance->initialise(Fonts::Jersey);
	m_pCostBalance->setPosition(130, 865);
	m_pCostBalance->setScale(0.5f, 0.5f);

	m_pUpgradeMaxed->initialise(Fonts::SciFi);
	m_pUpgradeMaxed->setPosition(250, 125);
	m_pUpgradeMaxed->setCharacterSize(100);
	m_pUpgradeMaxed->setFillColor(sf::Color(255, 0, 0, 200));
	m_pUpgradeMaxed->setString("Upgrade\n Maxed");

	m_itemCost[0] = 10;
	m_itemCost[1] = 20;
	m_itemCost[2] = 30;
	m_itemCost[3] = 40;
	m_itemCost[4] = 50;
	m_itemCost[5] = 60;
	m_itemCost[6] = 70;
	m_itemCost[7] = 80;
	
	loadTextures();
	loadText();
	textHandler();
	setUpgradeLimits();
}

void ShopMenu::update(float deltaTime)
{
	inputHandler(deltaTime);
	colorSelectionBox(deltaTime);
	//resetUpgrades();

	m_currentUpgrade[1] = m_pPlayer->getLives();;

	std::stringstream bankBalance;
	bankBalance << m_pPlayer->getBank(); //Return bank balance as string stream so it can be displayed from int to string.
	m_pBankBalance->setString(bankBalance.str()); //Display bank balance.

	std::stringstream itemCost;
	itemCost << m_itemCost[m_shopState]; //Return bank balance as string stream so it can be displayed from int to string.
	m_pCostBalance->setString(itemCost.str()); //Display bank balance.
}

void ShopMenu::render(sf::RenderTarget* window)
{
	for (int i = 0; i < 2; i++)
	{
		window->draw(m_pMenuSprites[i]);
		window->draw(m_pInstructions[i]);
	}
	m_pUpgradeTitle->render(window);
	m_pUpgradeDescription->render(window);
	m_pBankText->render(window);
	m_pBankBalance->render(window);
	m_pCostText->render(window);
	m_pCostBalance->render(window);
	if (m_maxedUpgrade == true)
	{
		m_pUpgradeMaxed->render(window);
	}
}

void ShopMenu::setUpgradeLimits()
{
	m_upgradeLimit[0] = ShopProperties::c_playerSpeedLimit;
	m_upgradeLimit[1] = ShopProperties::c_livesLimit;
	m_upgradeLimit[2] = ShopProperties::c_damageLimit;
	m_upgradeLimit[3] = ShopProperties::c_teleportLimit;
	m_upgradeLimit[4] = ShopProperties::c_mineLimit;
	m_upgradeLimit[5] = ShopProperties::c_sizeLimit;
	m_upgradeLimit[6] = ShopProperties::c_doubleTapLimit;
	m_upgradeLimit[7] = ShopProperties::c_projectileSpeedLimit;
}

void ShopMenu::loadText()
{
	m_pTitles[0].setString("Speed Boost");
	m_pTitles[1].setString("Health Upgrade");
	m_pTitles[2].setString("Damage Increase");
	m_pTitles[3].setString("Projectile Portal");
	m_pTitles[4].setString("Extra Mine");
	m_pTitles[5].setString("Projectile Size Increase");
	m_pTitles[6].setString("Double Tap Chance Increase");
	m_pTitles[7].setString("Projectile Speed Increase");

	m_pDescriptions[0].setString("Increase your players speed to help dodge those \nshaped projectiles.");
	m_pDescriptions[1].setString("Increase the max health of your shape to make \nit harder for the enemies to kill you.");
	m_pDescriptions[2].setString("Upgrade the damage of your projectiles to penetrate \nthrough the enemies armour in order to kill them faster.");
	m_pDescriptions[3].setString("Give each projectile fired a chance to portal itself back \ntowards the enemy.");
	m_pDescriptions[4].setString("Add an extra mine to the map to help defend off the \nenemy projectiles.");
	m_pDescriptions[5].setString("Increase the size of your projectiles in order to allow for \na greater chance of hitting your target.");
	m_pDescriptions[6].setString("Increase the chance of summoning an extra projectile \nthat will shadow the projectile fired in order to allow \nfor a double hit.");
	m_pDescriptions[7].setString("This upgrade will increase the speed at which the \nprojectile shoots towards the enemy; thus increasing \nyour accuracy too.");

	m_pInstructions[0].setString("Press enter to load \nnext level...");
	m_pInstructions[1].setString("Press space to purchase...");

	m_pCostText->setString("Cost");
}

void ShopMenu::loadTextures()
{
	m_pMenuSprites[0].setTexture(m_pTextureHandler->getTexture(TextureType::ShopBGD)); //Shop background.
	m_pMenuSprites[1].setTexture(m_pTextureHandler->getTexture(TextureType::ShopSelection)); //Selection box.

	m_pMenuSprites[1].setPosition(15, 320); //195
}

void ShopMenu::inputHandler(float deltaTime)
{
	Object* selection = &m_pMenuSprites[1];

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_shopState > 3)
	{
		m_defaultBox = true;
		screenShake = false;
		if (m_isUpPressed == false)
		{
		m_pAudioHandler->playSound(SoundEffect::SelectionBox);
			m_shopState -= 4;
			m_isUpPressed = true;
			selection->setPosition(selection->getPosition().x, selection->getPosition().y - 170);
			textHandler();
		}
	}
	else
	{
		m_isUpPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_shopState < 4)
	{
		m_defaultBox = true;
		screenShake = false;
		if (m_isDownPressed == false)
		{
		m_pAudioHandler->playSound(SoundEffect::SelectionBox);
			m_shopState += 4;			
			m_isDownPressed = true;
			selection->setPosition(selection->getPosition().x, selection->getPosition().y + 170);
			textHandler();
		}
	}
	else
	{
		m_isDownPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_defaultBox = true;
		screenShake = false;
		if (m_isLeftPressed == false)
		{
			if (m_shopState != 0 && m_shopState != 4)
			{
		m_pAudioHandler->playSound(SoundEffect::SelectionBox);
				m_shopState -= 1;
				m_isLeftPressed = true;
				selection->setPosition(selection->getPosition().x - 192, selection->getPosition().y);
				textHandler();
			}
		}
	}
	else
	{
		m_isLeftPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_defaultBox = true;
		screenShake = false;
		if (m_isRightPressed == false)
		{
			if (m_shopState != 3 && m_shopState != 7)
			{
				m_pAudioHandler->playSound(SoundEffect::SelectionBox);
				m_shopState += 1;
				m_isRightPressed = true;
				selection->setPosition(selection->getPosition().x + 192, selection->getPosition().y);
				textHandler();
			}
		}
	}
	else
	{
		m_isRightPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		m_pEnemyHandler->setCurrentLevel(m_pEnemyHandler->getCurrentLevel() + 1);
		m_pMainGame->resetGame();
		m_pGame->setCurrentState(GameStates::MainGame);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_defaultBox = false;
		if (m_isSpacePressed == false)
		{
			m_isSpacePressed = true;
			if (m_pPlayer->getBank() >= m_itemCost[m_shopState] && m_currentUpgrade[m_shopState] < m_upgradeLimit[m_shopState])
			{
				m_correctFunds = true;
				m_currentUpgrade[m_shopState] += 1;
				m_pPlayer->setBank(m_pPlayer->getBank() - m_itemCost[m_shopState]);
				upgradeHandler();
			}
			else
			{
				m_pAudioHandler->playSound(SoundEffect::ShopFail);
				m_correctFunds = false;
			}
			if (m_currentUpgrade[m_shopState] == m_upgradeLimit[m_shopState])
			{
				m_maxedUpgrade = true;
			}
		}
	}
	else
	{
		m_isSpacePressed = false;
	}

	if (m_maxedUpgrade == true)
	{
		m_timer += deltaTime;
		if (m_timer >= 2)
		{
			m_timer = 0;
			m_maxedUpgrade = false;
		}
	}
}

void ShopMenu::textHandler()
{
	m_pUpgradeTitle->setString(m_pTitles[m_shopState].getString());
	m_pUpgradeDescription->setString(m_pDescriptions[m_shopState].getString());
}

void ShopMenu::upgradeHandler()
{
	switch (m_shopState)
	{
	case 0: //Player movement speed.
		m_pPlayer->setSpeed(m_pPlayer->getSpeed() + PlayerProperties::c_speedIncrease);
		break;
	case 1: //Player lives count.
		if (m_pPlayer->getLives() < 3)
		{
			m_pPlayer->setLives(m_pPlayer->getLives() + 1);
		}
		else
		{
			m_pPlayer->setBank(m_pPlayer->getBank() + m_itemCost[1]);
		}
		break;
	case 2: //Player projectile damage.
		for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
		{
			Projectile* projectile = m_pProjectileHandler->getProjectiles(i);
			projectile->setPlayerProjectileDamage(projectile->getPlayerProjectileDamage() + 1);
		}
		break;
	case 3: //Projectile teleportation.
		for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
		{
			m_pProjectileHandler->getProjectiles(i)->setCanTeleport(true);
		}
		break;
	case 4: //Extra mine.
		m_pObstacleHandler->setExtraObstacles(m_pObstacleHandler->getExtraObstacles() + 1);
		break;
	case 5: //Projectile size increase.
		for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
		{
			m_pProjectileHandler->getProjectiles(i)->setSizeIncrease(true);
		}
		break;
	case 6: //Double tap chance.
		m_pPlayer->setCanDoubleTap(true);
		m_pPlayer->setDoubleTapChance(m_pPlayer->getDoubleTapChance() - 5);
		break;
	case 7: //Projectile speed increase.
		for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
		{
			Projectile* projectile = m_pProjectileHandler->getProjectiles(i);
			projectile->setPlayerProjectileSpeed(projectile->getProjectileSpeed() + 50);
		}
		break;
	}
	m_pObstacleHandler->setObstacleProperties();
}

void ShopMenu::colorText()
{
}

void ShopMenu::colorSelectionBox(float deltaTime)
{
	if (m_defaultBox == false)
	{
		m_timer += deltaTime;
		if (m_timer >= 0.8f)
		{
			m_timer = 0;
			m_defaultBox = true;
			screenShake = false;
		}
	}
	if (m_correctFunds == true && m_defaultBox == false)
	{
		m_pMenuSprites[1].setTexture(m_pTextureHandler->getTexture(TextureType::ShopSelectionPurchased));
	}
	if (m_correctFunds == false && m_defaultBox == false)
	{
		screenShake = true;
		m_pMenuSprites[1].setTexture(m_pTextureHandler->getTexture(TextureType::ShopSelectionFailed));
	}
	if (m_defaultBox == true)
	{
		m_pMenuSprites[1].setTexture(m_pTextureHandler->getTexture(TextureType::ShopSelection));
	}
}

void ShopMenu::resetUpgrades()
{
	for (int i = 0; i < sizeof(m_currentUpgrade); i++)
	{
		m_currentUpgrade[i] = 0;
	}
}