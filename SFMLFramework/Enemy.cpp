#include "Enemy.h"
#include <random>
#include <iostream>
#include "Helpers.h"

#include "EnemyHandler.h"
#include "ParticleHandler.h"

Enemy::Enemy()
{
	m_enemyType = EnemyType::Blank;

	m_isActive					= false;			// Disable the enemy on first initialise.
	m_targetPlayer				= false;			// Disable target player.
	m_explode					= false;			// Disable enemy explosion.
	m_spriteAnimationStatus		= false;			// Disable any animations until game start.
	m_fireAnimationStatus		= false;			// Disable any fire animations till a projectile is fired.
	m_finishingMove				= false;			// Disable finishing move state.
	m_inFormation				= false;			// Set enemy in position to false.
	m_healthSet					= false;			// Disable the health being set until level loads.

	m_lerpPositionValue			= 0;				// Set lerp position value to 0.
	m_timer						= 0;				// Timer to handle movement.
	m_lerpTimer					= 0;				// Timer to handle smooth lerp movement.

	m_health					= 0;				// Set enemy health to 0 as the properties of the enemies are set when they are loaded.

	m_pCollider					= new Collider();	// Create an object collider.
	m_pPlayer					= nullptr;			// Make the pointer null so it can be set in initialise.
	m_pProjectileHandler		= nullptr;			// *
	m_pEnemyHandler				= nullptr;			// *
	m_pParticleHandler			= nullptr;			// *

	m_speed						= EnemyProperties::c_defaultSpeed;	// Set the speed from the settings file.
	
	setRectSourceSprite(64, 64);					// Set the size of the rectangle sprite used for animations.
	setOrigin(32, 32);								// Set the origin to the center of the sprite.
}

Enemy::~Enemy()
{
	safeDeletePointer(m_pCollider);
}

void Enemy::initialise(Player* player, ProjectileHandler* projectileHandler, TextureHandler* pTextureHandler, EnemyHandler* pEnemyHandler, ParticleHandler* pParticleHandler)
{
	m_pCollider->initialise(32, getPosition());		// Initialise the collider.
	setProjectileHandler(projectileHandler);		// Set the Projectile Handler.
	setParticleHandler(pParticleHandler);			// Set the Particle Handler.
	setEnemyHandler(pEnemyHandler);					// Set the Enemy Handler.
	setPlayer(player);								// Set the Player.
	setTextureHandler(pTextureHandler);				// Set the Texture Handler.
	loadTexture();									// Load all enemy textures.
	loadTriggerValues();							// Load all trigger values used for enemy finishing moves.
	animateSprite(0.0f, 0, 64, false);				// Set animate sprites to false.
}

void Enemy::update(float deltaTime)
{
	// Move the enemy into its desired position within the formation set.
	moveIntoFormation(deltaTime);

	// If the player is active and it is in position then the required update functions will run.
	if (m_isActive == true && m_inFormation == true)
	{
		// Constantly reposition the collider based on the enemies position.
		m_pCollider->setPosition(getPosition());
		// Check for enemy health.
		checkEnemyHealth();
		// Check to see if the enemy should do their final attack.
		checkAttackState();
		// Fire animation constantly updates to check for if a new projectile is fired.
		fireAnimation(deltaTime);
		// If attack state is true then the enemy will execute their finishing move.
		finishingMove(deltaTime);
	}
}

void Enemy::render(sf::RenderTarget* window)
{
	// If the enemy is active it will draw to the screen.
	if (m_isActive == true)
	{
		window->draw(*this);
		// This renders the collider for debug purposes (not active in game as its circle is deactivated).
		m_pCollider->render(window);
	}
}

void Enemy::resetEnemy()
{
	// Reset the size of the collider.
	m_pCollider->setRadius(32);

	// Set the health of the enemy based on its type.
	setEnemyHealth(m_enemyType);

	// Reset the rotation of the enemy.
	setRotation(0);

	// Disable the portal target status.
	setPortalStatus(false);

	// Reset lerp value for smooth movement transitions.
	m_lerpPositionValue = 0;

	// In formation set false so when a new level loads the enemy will move into position.
	m_inFormation		= false;

	// Disable target player so the enemy doesn't lock onto the player.
	m_targetPlayer		= false;

	// Disable the finishing move so it doesn't execute when a new level loads.
	m_finishingMove		= false;
}

void Enemy::targetPlayer(float deltaTime)
{
	// Move the enemy towards the player. 
	if (m_targetPlayer == true && m_isActive == true)
	{
		moveTowards(getPosition(), getPlayer()->getPosition(), this, deltaTime, EnemyProperties::c_targetSpeed, true);
	}
}

void Enemy::loadTexture()
{
}

void Enemy::moveIntoFormation(float deltaTime)
{
	// Lerp timer for smooth animations.
	m_lerpPositionValue += deltaTime;

	// Lerp the enemy towards the position at a constant speed if not already at the desired position.
	if (m_lerpPositionValue < 1.0f && m_inFormation == false)
	{
		setPosition(vectorLerp(m_startingPosition, m_desiredPosition, m_lerpPositionValue));
	}
	else
	{
		// If in formation, ser the enemy health (bug fix).
		if (m_healthSet == false)
		{
			m_healthSet = true;
			setEnemyHealth(getEnemyType());
		}
		// If the enemy is at its desired position set its in formation position to true.
		m_inFormation = true;
		// Reset lerp value ready for the next wave of enemies if the player progresses onto the next level.
		m_lerpPositionValue = 0.0f;
	}
}

void Enemy::loadEnemy(sf::Vector2f desired)
{
	// Disable the players health from being set until in position.
	m_healthSet = false;

	// Set a random starting position for the enemy to lerp from.
	m_startingPosition = sf::Vector2f(rand() % 1600 + (-800), rand() % 1 + (-200));

	// Set the enemies position in the generated position above.
	setPosition(m_startingPosition);

	// Assign the desired location passed through from the Enemy Handler.
	m_desiredPosition = desired;

	// Set the enemies active state to true.
	m_isActive = true;
}

void Enemy::loadTriggerValues()
{
	// Set the values that will determine when the player will do their final attack/finishing move.
	m_finishTrigger[0] = 2;
	m_finishTrigger[1] = 2;
	m_finishTrigger[2] = 2;
	m_finishTrigger[3] = 3;
	m_finishTrigger[4] = 5;
	m_finishTrigger[5] = 6;
}

void Enemy::checkEnemyHealth()
{
	// Check for if the enemies health is below 0.
	if(m_health <= 0)
	{
		// Function that handles if all enemies have been killed.
		m_pEnemyHandler->checkEnemyCount();

		// When the enemy dies, reset all its properties.
		resetEnemy();

		// Disable the player from being rendered and updated.
		m_isActive = false;

		// Particle handler.
		m_pParticleHandler->setToSpawn(m_pParticleHandler->getToSpawn() + 15);
		m_pParticleHandler->burstParticles(getPosition(), (int)getEnemyType());

		// Increase the player bank value based on enemy type.
		setBankValue();
	}
}

void Enemy::checkAttackState()
{
	int enemyIndex = (int)getEnemyType();

	// Check for finishing move trigger.
	if (m_health <= m_finishTrigger[enemyIndex])
	{
		// If condition is met, activate finishing move.
		setFinishingMove(true);
	}
}

void Enemy::fireProjectile()
{
}

void Enemy::fireAnimation(float deltaTime)
{
	// Animates enemy when a projectile has been shot.
	if (getFireAnimationStatus() == true)
	{
		// Lower the size of the enemy.
		setScale(getScale().x - 2 * deltaTime, getScale().y - 2 * deltaTime);
		if (getScale().x < 0.5f)
		{
			// Reset its size when the animation is complete.
			setFireAnimationStatus(false);
			setScale(1, 1);
		}
	}
}

void Enemy::finishingMove(float deltaTime)
{
}

void Enemy::animationHandler()
{
	// This gives a chance to run the shine animation.
	int _random = rand() % EnemyProperties::c_shinePercent; 
	// When generating a random number, I will always look for 4 as it is my lucky number.
	if (_random == 4)
	{
		// Animate sprite.
		setSpriteAnimationStatus(true);
	}

	// If the animation bool is true, this function will run causing the enemy sprite to step through a spritesheet and create an animation.
	if (getSpriteAnimationStatus() == true && getTexture() != nullptr)
	{
		animateSprite(0.05f, getTexture()->getSize().y, getTexture()->getSize().x, false);
		if (getRectSourcePos() >= getTexture()->getSize().x - getTexture()->getSize().y)
		{
			setSpriteAnimationStatus(false);
			setRectSourcePos(0);
		}
	}
}

void Enemy::setEnemyHealth(EnemyType type)
{
	// Set enemy health based on enemy type.
	switch (type)
	{
	case EnemyType::Blank:
		m_health = 0;
		break;
	case EnemyType::Circle:
		m_health = 3;
		break;
	case EnemyType::Triangle:
		m_health = 3;
		break;
	case EnemyType::Square:
		m_health = 4;
		break;
	case EnemyType::Pentagon:
		m_health = 5;
		break;
	}
}

void Enemy::setBankValue()
{
	// Increase bank value based on enemy type.
	switch (m_enemyType)
	{
	case EnemyType::Circle:
		getPlayer()->setBank(getPlayer()->getBank() + BankProperties::c_circleValue);
		getPlayer()->setScore(getPlayer()->getScore() + BankProperties::c_circleValue * 15);
		break;
	case EnemyType::Triangle:
		getPlayer()->setBank(getPlayer()->getBank() + BankProperties::c_triangleValue);
		getPlayer()->setScore(getPlayer()->getScore() + BankProperties::c_triangleValue * 15);
		break;
	case EnemyType::Square:
		getPlayer()->setBank(getPlayer()->getBank() + BankProperties::c_squareValue);
		getPlayer()->setScore(getPlayer()->getScore() + BankProperties::c_squareValue * 15);
		break;
	case EnemyType::Pentagon:
		getPlayer()->setBank(getPlayer()->getBank() + BankProperties::c_pentagonValue);
		getPlayer()->setScore(getPlayer()->getScore() + BankProperties::c_pentagonValue * 15);
		break;
	}
	screenShake = false;
}

Collider* Enemy::getCollider()
{
	return m_pCollider; // Return the collider.
}

float Enemy::getLerpTimer()
{
	return m_lerpTimer; // Return the lerp timer.
}

void Enemy::setLerpTimer(float lerpTimer)
{
	m_lerpTimer = lerpTimer; // Set the lerp timer.
}

bool Enemy::getFinishingMove()
{
	return m_finishingMove; // Return the finishing move bool.
}

void Enemy::setFinishingMove(bool finisher)
{
	m_finishingMove = finisher; // Set the finishing move bool value.
}

void Enemy::setHealth(int health)
{
	m_health = health; // Set the enemies health.
}

int Enemy::getHealth()
{
	return m_health; // Return the enemies health.
}

void Enemy::setEnemyType(EnemyType enemyType)
{
	m_enemyType = enemyType; // Set the enemy type.
}

EnemyType Enemy::getEnemyType()
{
	return m_enemyType; // Return the enemy type.
}

void Enemy::setActiveState(bool enemyDead)
{
	m_isActive = enemyDead; // Set the active state of the enemy.
}

bool Enemy::getActiveState()
{
	return m_isActive; // Return the active state of the enemy.
}

void Enemy::setDesiredPosition(sf::Vector2f position)
{
	m_desiredPosition = position; // Set the desired position.
}

sf::Vector2f Enemy::getDesiredPosition()
{
	return m_desiredPosition; // Return the desired position.
}

void Enemy::setTargetStatus(bool target)
{
	m_targetPlayer = target; // Set the target player state.
}

bool Enemy::getTargetStatus()
{
	return m_targetPlayer; // Return the target state.
}

void Enemy::setPortalStatus(bool explode)
{
	m_explode = explode; // Set portal state.
}

bool Enemy::getPortalStatus()
{
	return m_explode; // Return the state.
}

void Enemy::setSpriteAnimationStatus(bool animation)
{
	m_spriteAnimationStatus = animation; // Set the sprite animation status.
}

bool Enemy::getSpriteAnimationStatus()
{
	return m_spriteAnimationStatus; // Return the sprite animation state.
}

void Enemy::setFireAnimationStatus(bool animation)
{
	m_fireAnimationStatus = animation; // Set the fire animation state.
}

bool Enemy::getFireAnimationStatus()
{
	return m_fireAnimationStatus; // Return the fire animation state.
}

void Enemy::setProjectileHandler(ProjectileHandler* projectileHandler)
{
	m_pProjectileHandler = projectileHandler; // Set the Projectile Handler.
}

ProjectileHandler* Enemy::getProjectileHandler()
{
	return m_pProjectileHandler; // Return the Projectile Handler.
}

void Enemy::setEnemyHandler(EnemyHandler* pEnemyHandler)
{
	m_pEnemyHandler = pEnemyHandler; // Set the Enemy Handler.
}

EnemyHandler* Enemy::getEnemyHandler()
{
	return m_pEnemyHandler; // Return the Enemy Handler.
}

void Enemy::setParticleHandler(ParticleHandler* pParticleHandler)
{
	m_pParticleHandler = pParticleHandler; // Set the Particle Handler.
}

ParticleHandler* Enemy::getParticleHandler()
{
	return m_pParticleHandler; // Return the Particle Handler.
}

void Enemy::setPlayer(Player* player)
{
	m_pPlayer = player; // Set the Player.
}

Player* Enemy::getPlayer()
{
	return m_pPlayer; // Return the Player.
}