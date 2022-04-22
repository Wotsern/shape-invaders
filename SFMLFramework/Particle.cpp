#include "Particle.h"
#include "ParticleHandler.h"
#include <iostream>

Particle::Particle()
{
	m_pParticleHandler		= nullptr;

	m_isActive				= false;
	m_burstParticle			= false;

	m_direction				= sf::Vector2f(0, 0);
	m_position				= sf::Vector2f(0, 0);

	m_speed					= 0;

	m_particle				= ParticleType::Circle;

	m_maxVanishX			= EffectProperties::c_maxVanishPointX;
	m_minVanishX			= EffectProperties::c_minVanishPointX;
	m_minVanishY			= EffectProperties::c_minVanishPointY;
	m_maxVanishY			= EffectProperties::c_maxVanishPointY;

	float r					= rand() % (3 - 10 + 1) + 3;
	setScale(r / 10, r/ 10);
}

Particle::~Particle()
{
}

void Particle::initialise(TextureHandler* pTextureHandler, ParticleHandler* pParticleHandler)
{
	// Set the Particle Handler.
	m_pParticleHandler = pParticleHandler;
	// Set the Texture Handler.
	setTextureHandler(pTextureHandler);
}

void Particle::update(float deltaTime)
{
	// Move the particle at a constant speed.
	move(m_direction * m_speed * deltaTime);

	// Check for if the particle goes off screen; if it does it will be set inactive.
	if (getPosition().x < m_minVanishX || getPosition().x > m_maxVanishX || getPosition().y < m_minVanishY || getPosition().y > m_maxVanishY)
	{
		m_isActive = false;
	}
}

void Particle::render(sf::RenderTarget* window)
{
	// Draw the particle to the window.
	window->draw(*this);
}

void Particle::spawnParticle(sf::Vector2f position, sf::Vector2f direction, int speed, ParticleType particle, bool burstParticle)
{
	// Determine whether the particle to be spawned is for the background or enemies death animaton.
	m_burstParticle = burstParticle;
	// Set the movement direction of the particle.
	m_direction = direction;
	// Set the position of where the particle is to be spawned from.
	setPosition(position);
	// Set the speed of the particle.
	m_speed = speed;

	// If the particle is for the background this statement will be entered.
	if (burstParticle == false)
	{
		// Spawn the correct particle based on the particle type.
		switch (particle)
		{
		case ParticleType::Circle:
			setTexture(getTextureHandler()->getTexture(TextureType::CircleBGD));
			break;
		case ParticleType::Triangle:
			setTexture(getTextureHandler()->getTexture(TextureType::TriangleBGD));
			break;
		case ParticleType::Square:
			setTexture(getTextureHandler()->getTexture(TextureType::SquareBGD));
			break;
		case ParticleType::Pentagon:
			setTexture(getTextureHandler()->getTexture(TextureType::PentagonBGD));
			break;
		}
	}
	else
	{
		// Spawn the correct particle based on the enemy type.
		// Resize the particles.
		setScale(0.1f, 0.1f);
		switch (particle)
		{
		case ParticleType::Circle:
			setTexture(getTextureHandler()->getTexture(TextureType::CircleProjectile));
			break;
		case ParticleType::Triangle:
			setTexture(getTextureHandler()->getTexture(TextureType::TriangleProjectile));
			break;
		case ParticleType::Square:
			setTexture(getTextureHandler()->getTexture(TextureType::SquareProjectile));
			break;
		case ParticleType::Pentagon:
			setTexture(getTextureHandler()->getTexture(TextureType::PentagonProjectile));
			break;
		case ParticleType::Player:
			// Set the scale of the player dead particles.
			setScale(0.4f, 0.4f);
			setTexture(getTextureHandler()->getTexture(TextureType::PlayerParticle));
			break;
		}
	}
}

// Return the active state of the particle.
bool Particle::getActiveState()
{
	return m_isActive;
}

// Set the active state of the particle.
void Particle::setActiveState(bool active)
{
	m_isActive = active;
}

// Return the particle speed.
float Particle::getParticleSpeed()
{
	return m_speed;
}

// Set the particle speed.
void Particle::setParticleSpeed(float speed)
{
	m_speed = speed;
}

// Set the direction the particle will move in.
void Particle::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}

// Return the particle direction.
sf::Vector2f Particle::getDirection()
{
	return m_direction;
}

