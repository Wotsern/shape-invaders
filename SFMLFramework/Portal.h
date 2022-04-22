#ifndef PORTAL_H
#define PORTAL_H

#include "Enemy.h"
#include "Object.h" //Reference Object header file.
#include "Player.h" //Reference Player header file.

class Portal : public Object
{
private:
	bool				m_isActive;		//Used for active state of the portal (render and update purposes).

	Player*				m_pPlayer;		//Used for pointer reference.
	Enemy*				m_pEnemy;
	Collider*			m_pCollider;	//Create a collider for portal.

	float				m_deltaTime;	//Used for same framerate throughout the game.
	float				m_timer;		//Used to determine how long portal should be active.

public:
	Portal();	//Constructor.
	~Portal();	//Deconstructor.

	void initialise(Enemy* enemy, sf::Vector2f position, Player* pPlayer, TextureHandler* pTextureHandler); //Initialiser of portal.
	virtual void update(float deltaTime);	//Update function (used for rotation and player collision).
	virtual void render(sf::RenderTarget* window) override; //Render object to screen.

	void checkCollision(float deltaTime);	//Checks for collision between player and portal.
	void deleteObject();					//Remove object from the screen.
};

#endif //!PORTAL_H