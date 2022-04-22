#ifndef PENTAGONENEMY_H
#define PENTAGONENEMY_H

#include "Enemy.h"

class PentagonEnemy : public Enemy
{
private:
	bool		m_beginAttack;		// Bool to handle attack state.
	bool		m_randomChosen;		// Bool to see if a random number was chosen.

	float		m_timer;			// Timer for loop delay.
	float		m_lerpTimer;		// Timer to handle lerp speed.

	int			m_rand;				// Generate a random number.

public:
	PentagonEnemy();	// Constructor.
	~PentagonEnemy();	// Deconstructor.

	void initialise();	// Initialise function.

	virtual void loadTexture() override;					// Override function for loading the correct texture.
	virtual void fireProjectile() override;					// Called when the enemy is to fire a projectile.
	virtual void finishingMove(float deltaTime) override;	// Finishing move handler.
};

#endif //!PENTAGONENEMY_H