#include "ColliderHandler.h"
#include "Helpers.h"
#include <iostream>

#include "Game.h"

ColliderHandler::ColliderHandler()
{
    // All class references are set to nullptr so they can be set correctly in the initialiser.
    m_pEnemyHandler         = nullptr;
    m_pProjectileHandler    = nullptr;
    m_pObstacleHandler      = nullptr;
    m_pPlayer               = nullptr;
    m_pGame                 = nullptr;
}

ColliderHandler::~ColliderHandler()
{
}

void ColliderHandler::initialise(ProjectileHandler* projectileHandler, EnemyHandler* enemyHandler, ObstacleHandler* obstacleHandler, Player* player)
{
    // Reference all classes needed.
    m_pProjectileHandler = projectileHandler; //Initialise the projectile handler object from the Game class.
    m_pEnemyHandler = enemyHandler;
    m_pObstacleHandler = obstacleHandler;
    m_pPlayer = player;
}

void ColliderHandler::update()
{ 
    //Checks for constant collision between objects.
    checkEnemyCollision();
    checkPlayerCollision();
    checkObstacleCollision();
    checkTargetCollision();
    checkTriangleEnemyCollision();
}

void ColliderHandler::checkEnemyCollision()
{
    // Loop through all projectiles.
    for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
    {
        // Loop through all enemies.
        for(auto& enemy : m_pEnemyHandler->getEnemies())      
        {
            sf::Vector2f projectile = m_pProjectileHandler->getProjectiles(i)->getPosition();
            sf::Vector2f enemyPosition = enemy->getPosition();

            // This bool function checks for collision between the enemy and projectiles.
            bool enemyHit = checkDistance(projectile, enemyPosition, enemy->getCollider()->getRadius());
            // If the function returns true then it will damage the enemy and remove the projectile.
            if (enemyHit == true && m_pProjectileHandler->getProjectiles(i)->getPlayerSpawned() == true && enemy->getActiveState() == true)
            {
                m_pProjectileHandler->getProjectiles(i)->setPosition(100, 0); //Stops the bullet doing more than one damage.
                m_pProjectileHandler->getProjectiles(i)->setActiveState(false); //Deactivates the button so it can be spawned again.
                enemy->setHealth(enemy->getHealth() - m_pProjectileHandler->getProjectiles(i)->getProjectileDamage()); //Lowers the collided enemies health by 1.
            }
        }
    }
}

void ColliderHandler::checkPlayerCollision()
{
    // Loop through all projectiles.
    for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
    {
        sf::Vector2f projectile = m_pProjectileHandler->getProjectiles(i)->getPosition();
        sf::Vector2f player = m_pPlayer->getPosition();

        // This bool function checks for collision between the player and enemy spawned projectiles.
        bool playerHit = checkDistance(projectile, player, m_pPlayer->getCollider()->getRadius());
        if (playerHit == true && m_pProjectileHandler->getProjectiles(i)->getPlayerSpawned() == false)
        {
            m_pProjectileHandler->getProjectiles(i)->setPosition(100, 0); //Stops the bullet doing more than one damage.
            m_pProjectileHandler->getProjectiles(i)->setActiveState(false); //Deactivates the button so it can be spawned again.
            m_pPlayer->setHealth(m_pPlayer->getHealth() - m_pProjectileHandler->getProjectiles(i)->getProjectileDamage());
        }
    }
}

void ColliderHandler::checkObstacleCollision()
{
    // Loop through all projectiles.
    for (int i = 0; i < ProjectileProperties::c_maxProjectiles; i++)
    {
        // Loop through all obstacles.
        for (int j = 0; j < ObstacleProperties::c_obstacleCount; j++)
        {
            sf::Vector2f projectile = m_pProjectileHandler->getProjectiles(i)->getPosition();
            sf::Vector2f obstacle = m_pObstacleHandler->getObstacles(j)->getPosition();

            // Check for collision between all projectile and obstacles.
            bool obstacleHit = checkDistance(projectile, obstacle, m_pObstacleHandler->getObstacles(j)->getCollider()->getRadius());
            if (obstacleHit == true)
            {
                m_pProjectileHandler->getProjectiles(i)->setPosition(100, 0); //Stops the bullet doing more than one damage.
                m_pProjectileHandler->getProjectiles(i)->setActiveState(false); //Deactivates the button so it can be spawned again.
                m_pObstacleHandler->getObstacles(j)->setHealth(m_pObstacleHandler->getObstacles(j)->getHealth() - m_pProjectileHandler->getProjectiles(i)->getProjectileDamage()); //Lowers the collided enemies health by 1.
                m_pObstacleHandler->getObstacles(j)->setUpdateSprite(false);
            }
        }
    }
}

void ColliderHandler::checkTargetCollision()
{
    for (auto& enemy : m_pEnemyHandler->getEnemies())
    {
        // Checks for if an enemy has collided with the player.
        bool obstacleHit = checkDistance(m_pPlayer->getPosition(), enemy->getPosition(), enemy->getCollider()->getRadius() * 1.5f);
        if (obstacleHit == true)
        {
            // Summon the portal.
            enemy->setPortalStatus(true);
        }
    }
}

void ColliderHandler::checkTriangleEnemyCollision()
{
    // Loop through enemies.
    for (auto& enemy : m_pEnemyHandler->getEnemies())
    {
        sf::Vector2f enemyPosition = enemy->getPosition();

        // Check for collision between triangle enemy and player.
        bool enemyHit = checkDistance(m_pPlayer->getPosition(), enemyPosition, enemy->getCollider()->getRadius());
        if (enemyHit == true && enemy->getActiveState() == true)
        {
            // Remove the enemy.
            enemy->setHealth(0);
            // Destroy the player.
            m_pPlayer->setHealth(0);
        }
    }
}