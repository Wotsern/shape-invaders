#include "TriangleEnemy.h"
#include <iostream>

TriangleEnemy::TriangleEnemy()
{
    initialise(); // Call the initialise function.
}

TriangleEnemy::~TriangleEnemy()
{
}

void TriangleEnemy::initialise()
{ 
    setEnemyType(EnemyType::Triangle); // Set the enemy type.
}

void TriangleEnemy::loadTexture()
{
    setTexture(getTextureHandler()->getTexture(TextureType::TriangleEnemy)); // Set the correct texture.
}

void TriangleEnemy::fireProjectile()
{
    getProjectileHandler()->spawnProjectile(getPosition(), 0, 1, false, ProjectileType::Triangle); // Function that is called when a projectile is to be fired.
}

void TriangleEnemy::finishingMove(float deltaTime)
{
    if (getFinishingMove() == true)
    {
        // Rotate the enemy to add a 'charge effect'.
        setRotation(getRotation() + 1000 * deltaTime); 
        // Move the enemy downwards.
        setPosition(getPosition().x, getPosition().y + 500 * deltaTime); 
        // If the enemy goes off screen, disable it.
        if (getPosition().y > 1000) 
        {
            setHealth(0);
        }
    }
}
