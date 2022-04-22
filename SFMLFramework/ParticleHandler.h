#ifndef PARTICLEHANDLER_H
#define PARTICLEHANDLER_H

#include "Helpers.h"
#include "Particle.h"
#include "Player.h"
#include "Projectile.h"
#include "Settings.h"

class ParticleHandler
{
private:
	Player*			m_pPlayer;						// Reference to the player.
	Particle*		m_pBackgroundParticles;			// Particle array.
	Particle*		m_pBurstParticles;				// Particle array.
	Particle*		m_pPlayerParticles;				// Particle array.	
	
	ParticleType	m_particle;						// Particle type handler.

	float			m_speed;						// Speed at which the particles move around the screen.
	float			m_timer;
	
	int				m_currentBackgroundParticle;	// Used to initialise all particles correctly.
	int				m_currentBurstParticle;			// Used to initialise all particles correctly.
	int				m_currentPlayerParticle;		// Used to initialise all particles correctly.
	int				m_toSpawn;						// Limits how many particles are to be drawn at a single time.
	int				m_scale;						// Size of the particle (used for random sizing).

	sf::Vector2f	m_direction;					// Direction for desired particle to move.
	sf::Vector2f	m_position;						// Position for desired particle to spawn.

public:
	ParticleHandler();	// Constructor.
	~ParticleHandler();	// Deconstructor.

	void initialise(TextureHandler* pTextureHandler, Player* pPlayer);	// Initialiser.
	void update(float deltaTime);										// Update function for all particles.
	void render(sf::RenderTarget* window);								// Render function that handles the particles being displayed.

	void generateBackgroundParticles();									// Function that is called to handle particle randomisation (size, speed and shape).
	void generateBurstParticles(sf::Vector2f position, int type);		// Function that is called to handle particle randomisation (size, speed and shape).
	void generatePlayerParticles();										// Function that is called to handle particle randomisation (size, speed and shape).
	void backgroundParticles();											// Generate background particles.
	void burstParticles(sf::Vector2f position, int particleType);		// Generate burst particles.
	void playerParticles();												// Generate player particles.
	void handlePlayerState(float deltaTime);							// Handles player particles after they have been spawned.

	int getToSpawn();				// Return the amount of particles to spawn.
	void setToSpawn(int toSpawn);	// Set the amount of particles to spawn.
};

#endif //!PARTICLEHANDLER_H