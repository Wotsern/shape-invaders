#ifndef TriangleEnemy_H
#define TriangleEnemy_H

#include "Enemy.h"
#include "PlayerProjectile.h"

class TriangleEnemy : public Enemy
{
private:

public:
	TriangleEnemy();	// Constructor.
	~TriangleEnemy();	// Deconstructor.

	void initialise();	// Initialise function.

	virtual void loadTexture() override;					// Override function for loading the correct texture.
	virtual void fireProjectile() override;					// Called when the enemy is to fire a projectile
	virtual void finishingMove(float deltaTime) override;	// Finishing move handler.
};

#endif //!TriangleEnemy_H