#ifndef CircleEnemy_H
#define CircleEnemy_H

#include "Enemy.h"
#include "Portal.h"

class CircleEnemy : public Enemy
{
private:
	Portal*				m_pPortal;			//Create a portal object.
	bool				m_portalSpawned;	//Bool to check if the portal is spawned.

public:
	CircleEnemy();		//Constructor.
	~CircleEnemy();		//Deconstructor.

	void initialise();	//Initialise function.

	virtual void loadTexture() override;	//Override function for loading the correct texture.
	virtual void fireProjectile() override;	//Called when the enemy is to fire a projectile.
	virtual void finishingMove(float deltaTime) override;

	virtual void render(sf::RenderTarget* window) override; //Render function to display the enemy on screen.
};

#endif //!CircleEnemy_H