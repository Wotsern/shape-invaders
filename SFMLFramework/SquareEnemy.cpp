#include "SquareEnemy.h"
#include "Helpers.h"
#include <iostream>

SquareEnemy::SquareEnemy()
{
    initialise(); // Call initialise function.
}

SquareEnemy::~SquareEnemy()
{
}

void SquareEnemy::initialise()
{    
    setEnemyType(EnemyType::Square); // Set the enemy type.
}

void SquareEnemy::loadTexture()
{
    setTexture(getTextureHandler()->getTexture(TextureType::SquareEnemy)); // Load the correct texture.
}

void SquareEnemy::fireProjectile()
{
    getProjectileHandler()->spawnProjectile(getPosition(), 0, 1, false, ProjectileType::Square); // Function that handle firing projectiles.
}

void SquareEnemy::finishingMove(float deltaTime)
{
    if (getFinishingMove() == true)
    {
        //If the enemy is not yet in position, keep its health at 5.
        if (getPosition().y <= 449)
        {
            setHealth(5);
        }
        // Move towards a set position.
        moveTowards(getPosition(), sf::Vector2f(getPlayer()->getPosition().x, 450), this, deltaTime, 2, false);
    }
}
