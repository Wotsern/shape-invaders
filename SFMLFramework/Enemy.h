#ifndef ENEMY_H
#define ENEMY_H

#include "Collider.h"
#include "Object.h"
#include "Settings.h"
#include "ProjectileHandler.h"
#include "Player.h"
#include "TextureHandler.h"

class EnemyHandler;
class ParticleHandler;

enum class EnemyType
{
	Circle,
	Triangle,
	Square,
	Pentagon,
	Hexagon,
	Octagon,
	Blank
};

class Enemy : public Object
{
private:
	EnemyType			m_enemyType;				//Type of enemy that spawns.

	bool				m_isActive;					//Used for update/render.
	bool				m_targetPlayer;				//Used for target locking.
	bool				m_explode;					//Used for portal.
	bool				m_spriteAnimationStatus;	//Checks for animated sprite.
	bool				m_fireAnimationStatus;		//Effect when a projectile is fired.
	bool				m_finishingMove;			//Check for enemy final attack.
	bool				m_inFormation;				//Check for if the enemy is in position.
	bool				m_healthSet;				//Check to make sure the enemies health is set correctly.

	sf::Vector2f		m_startingPosition;
	sf::Vector2f		m_desiredPosition;

	float				m_speed;					//Default speed at which the enemy will move.
	float				m_lerpPositionValue;		//Used to keep lerp at consistant speed.
	float				m_timer;					//Timer.
	float				m_lerpTimer;				//Lerp timer used to keep framerate consistant.

	int					m_health;					//Enemy health value.
	int					m_finishTrigger[6];			//Trigger array that holds the final attack trigger.

	Player*				m_pPlayer;					//Player reference.
	Collider*			m_pCollider;				//Collider reference.
	ProjectileHandler*	m_pProjectileHandler;		//Projectile Handler reference.
	EnemyHandler*		m_pEnemyHandler;			//Enemy Handler reference.
	ParticleHandler*	m_pParticleHandler;			//Particle Handler reference.

public:
	Enemy();
	~Enemy();

	void initialise(Player* player, ProjectileHandler* projectileHandler, TextureHandler* pTextureHandler, EnemyHandler* pEnemyHandler, ParticleHandler* pParticleHandler); //Initialise required pointers.
	virtual void update(float deltaTime);				//Update function.
	virtual void render(sf::RenderTarget* window);		//Render function.

	virtual void targetPlayer(float deltaTime);			//Function that moves this object towards the player.
	virtual void animationHandler();					//Function that handles animations.
	virtual void loadTexture();							//Load the desired textures.
	virtual void fireProjectile();						//Instantiate a projectile when this function is called.
	virtual void fireAnimation(float deltaTime);		//Animate enemy when a projectile is fired.
	virtual void finishingMove(float deltaTime);		//Function that executes final attack.
	
	void moveIntoFormation(float deltaTime);			//Move the enemies into position at level start.
	void setEnemyHealth(EnemyType type);				//Set the enemies health based on enemy type.
	void loadEnemy(sf::Vector2f desired);				//Load the enemy and its properties.
	void loadTriggerValues();							//Set the trigger values.
	void resetEnemy();									//Reset the enemy to the correct values based on type.
	void checkEnemyHealth();							//Function that handles enemy health and executed the code based on return value.
	void checkAttackState();							//Checks for if the enemy is to do their final attack.
	void setBankValue();								//Update player bank value.

	Collider* getCollider();							//Return the collider of this object.

	float getLerpTimer();								//Return the lerp timer.
	void setLerpTimer(float lerpTimer);					//Set the lerp timer.

	bool getFinishingMove();							//Return the finishing move.
	void setFinishingMove(bool finisher);				//Set the finishing move.

	int getHealth();									//Return the enemy health.
	void setHealth(int health);							//Set the enemy health.

	EnemyType getEnemyType();							//Return the enemy type.
	void setEnemyType(EnemyType enemyType);				//Set the enemy type.

	bool getActiveState();								//Return the active state.
	void setActiveState(bool active);					//Set the active state.

	sf::Vector2f getDesiredPosition();					//Return the desired position the enemy will lerp towards.
	void setDesiredPosition(sf::Vector2f position);		//Set the desired position.

	bool getTargetStatus();								//Return the target status.
	void setTargetStatus(bool target);					//Set the target status.

	bool getPortalStatus();								//Return the portal status.
	void setPortalStatus(bool explode);					//Set the portal status.

	bool getSpriteAnimationStatus();					//Return the animation status.
	void setSpriteAnimationStatus(bool animation);		//Set the animation status.

	bool getFireAnimationStatus();						//Return the fire animation status.
	void setFireAnimationStatus(bool animation);		//Set the fire animation status.

	ProjectileHandler* getProjectileHandler();							//Return the Projectile Handler.
	void setProjectileHandler(ProjectileHandler* projectileHandler);	//Set the Projectile Handler.

	EnemyHandler* getEnemyHandler();									//Return the Enemy Handler.
	void setEnemyHandler(EnemyHandler* pEnemyHandler);					//Set the Enemy Handler.

	ParticleHandler* getParticleHandler();								//Return the Particle Handler.
	void setParticleHandler(ParticleHandler* pParticleHandler);			//Set the Particle Handler.

	Player* getPlayer();												//Return the Player.
	void setPlayer(Player* player);										//Set the Player.
};

#endif //!ENEMY_H