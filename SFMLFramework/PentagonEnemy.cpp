#include "PentagonEnemy.h"
#include "Helpers.h"

PentagonEnemy::PentagonEnemy()
{
	m_beginAttack	= false;
	m_randomChosen	= false;

	m_timer			= 0;
	m_lerpTimer		= 0;

	m_rand			= 0;
	initialise();
}

PentagonEnemy::~PentagonEnemy()
{
}

void PentagonEnemy::initialise()
{
	setEnemyType(EnemyType::Pentagon); // Set the type of the enemy.
}

void PentagonEnemy::loadTexture()
{
	setTexture(getTextureHandler()->getTexture(TextureType::PentagonEnemy)); // Set the texture of the enemy.
}

void PentagonEnemy::fireProjectile()
{
	getProjectileHandler()->spawnProjectile(getPosition(), 0, 1, false, ProjectileType::Pentagon); // Fires a projectile when called.
}

void PentagonEnemy::finishingMove(float deltaTime)
{
	if (getFinishingMove() == true)
	{
		if (m_randomChosen == false)
		{
			m_randomChosen = true;
			// Generate a random number.
			m_rand = rand() % 2;
		}
		if (getPosition().y != 450 && m_beginAttack == false)
		{
			// Based on random number, move enemy towards a set location.
			switch (m_rand)
			{
			case 0:
				moveTowards(this->getPosition(), sf::Vector2f(50, 450), this, deltaTime, 1, false);
				break;
			case 1:
				moveTowards(this->getPosition(), sf::Vector2f(750, 450), this, deltaTime, 1, false);
				break;
			}

			// If the enemy is nearly at the desired location, begin final attack.
			if (getPosition().y > 445)
			{
				m_beginAttack = true;
			}
		}

		// If the final attack has been triggered ->
		if (m_beginAttack == true)
		{
			// -> start the lerp times for smooth movement.
			m_lerpTimer += deltaTime;

			switch (m_rand)
			{
			case 0:
				setPosition(vectorLerp(getPosition(), sf::Vector2f(750, 450), m_lerpTimer * 0.005f));
				break;
			case 1:
				setPosition(vectorLerp(getPosition(), sf::Vector2f(50, 450), m_lerpTimer * 0.005f));
				break;
			}
			//Incease timer based on delta tIme.
			m_timer += deltaTime;
			// Rotate the enemy gamesprite.
			setRotation(getRotation() + 150 * deltaTime);

			// Fire projectile rapidly.
			if (m_timer >= 0.15f)
			{
				m_timer = 0;
				fireProjectile();
			}
		}

		// If the rotation has reached max, remove the enemy.
		if (getRotation() >= 359)
		{
			setHealth(0);
		}
	}
}
