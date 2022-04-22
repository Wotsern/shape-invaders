#ifndef SquareEnemy_H
#define SquareEnemy_H

#include "Enemy.h"

class SquareEnemy : public Enemy
{
private:

public:
	SquareEnemy();		// Constructor.
	~SquareEnemy();		// Deconstructor.

	void initialise();	// Initialise function.

	virtual void loadTexture() override;					// Override function for loading the correct texture.
	virtual void fireProjectile() override;					// Called when the enemy is to fire a projectile.
	virtual void finishingMove(float deltaTime) override;	// Finishing move handler.
};

#endif //!SquareEnemy_H