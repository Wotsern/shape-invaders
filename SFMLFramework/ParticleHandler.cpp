#include "ParticleHandler.h"
#include <iostream>

ParticleHandler::ParticleHandler()
{
	m_pPlayer					= nullptr;
	m_pBackgroundParticles		= new Particle[EffectProperties::c_maxParticleCount];
	m_pBurstParticles			= new Particle[EffectProperties::c_maxParticleCount];
	m_pPlayerParticles			= new Particle[15];

	m_particle					= ParticleType::Circle;

	m_speed						= 0;
	m_timer						= 0;

	m_currentBackgroundParticle = 0;
	m_currentBurstParticle		= 0;
	m_currentPlayerParticle		= 0;
	m_toSpawn					= 0;
	m_scale						= 0;
}

ParticleHandler::~ParticleHandler()
{
	safeDeletePointerArray(m_pBackgroundParticles);
	safeDeletePointerArray(m_pBurstParticles);
	safeDeletePointerArray(m_pPlayerParticles);
}

// Generate background particles.
void ParticleHandler::generateBackgroundParticles()
{
	m_direction.x = generateRandomFloat(-5, 5);
	m_direction.y = generateRandomFloat(-5, 5);
	m_speed = rand() % (40 - 50 + 1) + 40;
	m_position.x = rand() % WindowProperties::c_width;
	m_position.y = rand() % WindowProperties::c_height;
	m_particle = ParticleType(rand() % sizeof(ParticleType));

	if (m_direction.x == 0 || m_speed == 0) //Keep the particles moving (sometimes would be at 0,0 with no speed).
	{
		generateBackgroundParticles();
	}

	m_pBackgroundParticles[m_currentBackgroundParticle].spawnParticle(m_position, m_direction, m_speed, m_particle, false);
}

// Generate burst particles.
void ParticleHandler::generateBurstParticles(sf::Vector2f position, int type)
{
	m_direction.x = generateRandomFloat(-1, 1);
	m_direction.y = generateRandomFloat(-1, 1);
	m_speed = rand() % (100 - 150 + 1) + 100;
	m_position = position;

	switch (type)
	{
	case 0:
		m_particle = ParticleType::Circle;
		break;
	case 1:
		m_particle = ParticleType::Triangle;
		break;
	case 2:
		m_particle = ParticleType::Square;
		break;
	case 3:
		m_particle = ParticleType::Pentagon;
		break;
	case 8:
		m_particle = ParticleType::Player;
		break;
	}

	if (m_direction.x == 0 || m_speed == 0) //Keep the particles moving (sometimes would be at 0,0 with no speed).
	{
		generateBurstParticles(position, type);
	}

	m_pBurstParticles[m_currentBurstParticle].spawnParticle(m_position, m_direction, m_speed, m_particle, true);
}

//Generate player particles.
void ParticleHandler::generatePlayerParticles()
{
	m_direction.x = generateRandomFloat(-1, 1);
	m_direction.y = generateRandomFloat(-1, 1);
	m_speed = rand() % (100 - 150 + 1) + 100;
	m_position = m_pPlayer->getPosition();

	m_particle = ParticleType::Player;


	if (m_direction.x == 0 || m_speed == 0) //Keep the particles moving (sometimes would be at 0,0 with no speed).
	{
		generatePlayerParticles();
	}

	m_pPlayerParticles[m_currentPlayerParticle].spawnParticle(m_position, m_direction, m_speed, m_particle, true);
}

// Handle background particles.
void ParticleHandler::backgroundParticles()
{
	for (int i = 0; i < EffectProperties::c_backgroundParticleCount; i++)
	{
		if (m_pBackgroundParticles[i].getActiveState() == false)
		{
			m_currentBackgroundParticle = i;
			m_pBackgroundParticles[i].setActiveState(true);
			generateBackgroundParticles();
		}
	}
}

//Handle burst particles.
void ParticleHandler::burstParticles(sf::Vector2f position, int type)
{
	for (int i = 0; i < EffectProperties::c_maxParticleCount; i++)
	{
		if (m_pBurstParticles[i].getActiveState() == false)
		{
			if (m_toSpawn > 0)
			{
				m_toSpawn--;
				m_currentBurstParticle = i;
				m_pBurstParticles[i].setActiveState(true);
				generateBurstParticles(position, type);
			}
		}
	}
}

// Handle player particles.
void ParticleHandler::playerParticles()
{
	if (m_pPlayer->getPlayerDead() == true)
	{
		for (int i = 0; i < 15; i++)
		{
			if (m_pPlayerParticles[i].getActiveState() == false)
			{
				if (m_pPlayer->getLives() > 0)
				{
					m_currentPlayerParticle = i;
					m_pPlayerParticles[i].setActiveState(true);
					generatePlayerParticles();
				}
			}
		}
	}
}

// Handle player state.
void ParticleHandler::handlePlayerState(float deltaTime)
{
	if (m_pPlayer->getPlayerDead() == true)
	{
		m_timer += deltaTime;
		if (m_timer > 2 && m_pPlayer->getLives() > 0)
		{
			for (int i = 0; i < 15; i++)
			{
				m_pPlayer->getCollider()->setRadius(32);
				m_pPlayerParticles[i].setPosition(vectorLerp(m_pPlayerParticles[i].getPosition(), m_pPlayer->getPosition(), deltaTime * 10));
			}
		}
		if (m_timer > 2.3f)
		{
			if (m_pPlayer->getLives() > 0)
			{
				m_pPlayer->setLives(m_pPlayer->getLives() - 1);
			}
			m_pPlayer->setPlayerDead(false);
			m_pPlayer->setHealth(10);
			for (int i = 0; i < 15; i++)
			{
				m_pPlayerParticles[i].setActiveState(false);
			}
			m_timer = 0;
		}
	}
}

int ParticleHandler::getToSpawn()
{
	return m_toSpawn;
}

void ParticleHandler::setToSpawn(int toSpawn)
{
	m_toSpawn = toSpawn;
}

void ParticleHandler::initialise(TextureHandler* pTextureHandler, Player* pPlayer)
{
	m_pPlayer = pPlayer;
	for (int i = 0; i < EffectProperties::c_maxParticleCount; i++)
	{
		m_pBackgroundParticles[i].initialise(pTextureHandler, this);
		m_pBurstParticles[i].initialise(pTextureHandler, this);
	}
	for (int i = 0; i < 15; i++)
	{
		m_pPlayerParticles[i].initialise(pTextureHandler, this);
	}
}

void ParticleHandler::update(float deltaTime)
{
	backgroundParticles();
	playerParticles();
	handlePlayerState(deltaTime);

	for (int i = 0; i < EffectProperties::c_maxParticleCount; i++)
	{
		if (m_pBackgroundParticles[i].getActiveState() == true || m_pBurstParticles[i].getActiveState() == true)
		{
			m_pBackgroundParticles[i].update(deltaTime);
			m_pBurstParticles[i].update(deltaTime);
		}
	}

	for (int i = 0; i < 15; i++)
	{
		if (m_pPlayerParticles[i].getActiveState() == true)
		{
			m_pPlayerParticles[i].update(deltaTime);
		}
	}
}

void ParticleHandler::render(sf::RenderTarget* window)
{
	for (int i = 0; i < EffectProperties::c_maxParticleCount; i++)
	{
		if (m_pBackgroundParticles[i].getActiveState() == true || m_pBurstParticles[i].getActiveState() == true)
		{
			m_pBackgroundParticles[i].render(window);
			m_pBurstParticles[i].render(window);
		}
	}
	for (int i = 0; i < 15; i++)
	{
		if (m_pPlayerParticles[i].getActiveState() == true)
		{
			m_pPlayerParticles[i].render(window);
		}
	}
}
