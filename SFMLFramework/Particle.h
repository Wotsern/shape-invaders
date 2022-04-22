#ifndef PARTICLE_H
#define PARTICLE_H

#include "Object.h" //Reference Object header file.
#include "Settings.h" //Reference Settings header file.

enum class ParticleType //Enum for particle type.
{
	Circle,
	Triangle,
	Square,
	Pentagon,
	Hexagon,
	Octagon,
	Player
};

class ParticleHandler;

class Particle : public Object
{
private:
	ParticleHandler* m_pParticleHandler;

	bool			m_isActive;		//Used for render and update functions.
	bool			m_burstParticle;

	sf::Vector2f	m_direction;	//int value used to determine which direction the bullet will move (up for player, down for enemy).
	sf::Vector2f	m_position;		//Position of the particle.

	float			m_speed;		//Speed at which the bullet will move.

	ParticleType	m_particle;		//Reference to ParticleType enum.

	int				m_minVanishX, m_maxVanishX, m_minVanishY, m_maxVanishY; //Boundaries of the particle before it's position is regenerated.

public:
	Particle();		//Constructor.
	~Particle();	//Deconstructor.

	void			initialise(TextureHandler* pTextureHandler, ParticleHandler* pParticleHandler); 
	void			spawnParticle(sf::Vector2f position, sf::Vector2f direction, int speed, ParticleType particle, bool burstParticle); //Particle loader.
	void			update(float deltaTime); //Update function to move particles.
	virtual void	render(sf::RenderTarget* window); //Display particle on screen.

	bool			getActiveState(); //Getter - Particle state.
	void			setActiveState(bool active); //Setter - Particle state.

	float			getParticleSpeed(); //Getter - Particle speed.
	void			setParticleSpeed(float speed); //Setter - Particle speed.

	sf::Vector2f	getDirection(); //Getter - Movement direction.
	void			setDirection(sf::Vector2f direction); //Setter - Movement direction.
};

#endif //!PARTICLE_H