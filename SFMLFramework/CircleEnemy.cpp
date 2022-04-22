#include <iostream>

#include "CircleEnemy.h"
#include "EnemyHandler.h"
#include "Helpers.h"

CircleEnemy::CircleEnemy()
{
    m_pPortal           = new Portal(); // Pre-load the portal so it can be instantiated when necessary.
    m_portalSpawned     = false;        // Set portal spawned as false.

    initialise();                       // Calls the initialise function straight away (tidier).
}

CircleEnemy::~CircleEnemy()
{
    safeDeletePointer(m_pPortal);       // Delete the pointer.
}

void CircleEnemy::initialise()
{
    setEnemyType(EnemyType::Circle);    // Set enemy type.
}

void CircleEnemy::loadTexture()
{
    setTexture(getTextureHandler()->getTexture(TextureType::CircleEnemy));      // Set the correct texture.
}

void CircleEnemy::render(sf::RenderTarget* window)
{   
    // Check for if the player is active but making sure the portal has not yet been spawned.
    if (getActiveState() == true && getPortalStatus() == false) 
    {
        // If the condition is met this enemy will be drawn to the screen.
        window->draw(*this);                                    
    }

    // Check to see if the portal has been instantiated.
    if (getPortalStatus() == true)                              
    {
        // If the condition is met then the player will no longer be spawned and the portal will be rendered.
        m_pPortal->render(window);
    }
}

void CircleEnemy::fireProjectile()
{
    // Fire a projectile from the enemies current position.
    getProjectileHandler()->spawnProjectile(getPosition(), 0, 1, false, ProjectileType::Circle);
}

void CircleEnemy::finishingMove(float deltaTime)
{
    // If the enemies finising move is active ->
    if (getFinishingMove() == true)
    {
        // If the portal has not yet reached the enemy then enable target mode.
        if (getPortalStatus() == false)
        {
            setTargetStatus(true);
        }

        // If the target status is true then move the enemy towards the target (player).
        if (getTargetStatus() == true)
        {
            targetPlayer(deltaTime);
        }

        // If the return value of the target is true then the portal will be spawned if it hasn't already.
        if (getPortalStatus() == true && m_portalSpawned == false)
        {
            m_portalSpawned = true;
            // Remove this objects collider so it doesn't block player projectiles.
            getCollider()->setRadius(0);
            // Stop any animations.
            setSpriteAnimationStatus(false);
            // Initialise the portal in the position of where the collision between the player and enemy collided.
            m_pPortal->initialise(this, getPosition(), getPlayer(), getTextureHandler());
        }

        // If the portal is active then its update function will run.
        if (getPortalStatus() == true)
        {
            m_pPortal->update(deltaTime);
        }
        
    }
}
