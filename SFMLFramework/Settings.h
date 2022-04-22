#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/System/String.hpp>

//This settings file is to make it easy to edit values of the game without having to dive deep into the code.

namespace WindowProperties
{
	const int			c_posX = 500;
	const int			c_posY = 20;
	const int			c_height = 950;
	const int			c_width = 800;
	const sf::String	c_title = "Shape Invaders";
}

namespace BankProperties
{
	const int			c_circleValue =			2;
	const int			c_triangleValue =		3;
	const int			c_squareValue =			4;
	const int			c_pentagonValue =		5;
}

namespace SpritePaths
{
	const sf::String	c_playerSprite =		"Assets/Sprites/s_player.png";
	const sf::String	c_projectilePlayer =	"Assets/Sprites/s_playerProjectile.png";
	const sf::String	c_projectileCircle =	"Assets/Sprites/s_circleProjectile.png";
	const sf::String	c_playerParticle =		"Assets/Sprites/s_playerParticle.png";
	const sf::String	c_projectileTriangle =	"Assets/Sprites/s_triangleProjectile.png";
	const sf::String	c_projectileSquare =	"Assets/Sprites/s_squareProjectile.png";
	const sf::String	c_projectilePentagon =	"Assets/Sprites/s_pentagonProjectile.png";
	const sf::String	c_circleEnemy =			"Assets/Sprites/s_circleEnemy.png";
	const sf::String	c_triangleEnemy =		"Assets/Sprites/s_triangleEnemy.png";
	const sf::String	c_squareEnemy =			"Assets/Sprites/s_squareEnemy.png";
	const sf::String	c_pentagonEnemy =		"Assets/Sprites/s_pentagonEnemy.png";
	const sf::String	c_explosion =			"Assets/Sprites/s_explosion.png";
	const sf::String	c_mineObstacle =		"Assets/Sprites/s_mineObstacle.png";
	const sf::String	c_rockExploding =		"Assets/Sprites/s_rockExploding.png";
	const sf::String	c_portal =				"Assets/Sprites/s_portal.png";
	const sf::String	c_bgdCircle =			"Assets/Sprites/s_bgdCircle.png";
	const sf::String	c_bgdTriangle =			"Assets/Sprites/s_bgdTriangle.png";
	const sf::String	c_bgdSquare =			"Assets/Sprites/s_bgdSquare.png";
	const sf::String	c_bgdPentagon =			"Assets/Sprites/s_bgdPentagon.png";
	const sf::String	c_bgdShop =				"Assets/Sprites/s_shopMenu.png";
	const sf::String	c_shopSelection =		"Assets/Sprites/s_shopSelection.png";
	const sf::String	c_shopPurchased =		"Assets/Sprites/s_shopSelectionPurchased.png";
	const sf::String	c_shopFailed =			"Assets/Sprites/s_shopSelectionFailed.png";
	const sf::String	c_health100 =			"Assets/Sprites/s_healthBar100.png";
	const sf::String	c_health80 =			"Assets/Sprites/s_healthBar80.png";
	const sf::String	c_health60 =			"Assets/Sprites/s_healthBar60.png";
	const sf::String	c_health40 =			"Assets/Sprites/s_healthBar40.png";
	const sf::String	c_health20 =			"Assets/Sprites/s_healthBar20.png";
	const sf::String	c_health0 =				"Assets/Sprites/s_healthBar0.png";
	const sf::String	c_heart =				"Assets/Sprites/s_heart.png";
	const sf::String	c_cursor =				"Assets/Sprites/s_cursor.png";
	const sf::String	c_howToPlay =			"Assets/Sprites/s_howToPlay.png";
	const sf::String	c_mascot =				"Assets/Sprites/s_mascot.png";
}

namespace ProjectileProperties
{
	const int			c_projectileSpeed = 1000;
	const int			c_maxProjectiles = 100;
	const int			c_playerProjectileSpeed = 800;
	const int			c_circleProjectileSpeed = 700;
	const int			c_triangleProjectileSpeed = 300;
	const int			c_squareProjectileSpeed = 500;
	const int			c_pentagonProjectileSpeed = 400;
}

namespace PlayerProperties
{
	const float			c_speed = 150.0f;
	const float			c_speedIncrease = 50.0f;
	const int			c_topBoundary = 710;
	const int			c_bottomBoundary = 850;
	const int			c_health = 10;
	const int			c_healthIncrease = 2;
	const int			c_playerLives = 3;
	const int			c_startingPosX = 400;
	const int			c_startingPosY = 800;
	const int			c_doubleTapChance = 20;
}

namespace EnemyProperties
{	
	const float			c_defaultSpeed = 0.05f;
	const float			c_movementSpeed = 100.0f;
	const float			c_randomNumberTimer = 0.2f;
	const float			c_targetSpeed = 1.5f;
	const float			c_portalForce = 1.2f;
	const float			c_startingXPos = 100;
	const float			c_startingYPos = 60;
	const float			c_gapBetweenEnemies = 80;
	const int			c_enemyRows = 4;
	const int			c_enemyColumns = 6;
	const int			c_maxEnemies = c_enemyRows * c_enemyColumns;
	const int			c_spawnProjectilePercent = 10;
	const int			c_shinePercent = 10000;
	const int			c_moveEnemyDown = 5;
	const int			c_countdownTimer = 3;
}

namespace ObstacleProperties
{
	const int			c_obstacleCount = 10;
	const int			c_defaultCount = 5;
	const int			c_rotationSpeed = 20;
	const int			c_startingPosX = 60;
	const int			c_startingPosY = 550;
	const int			c_secondPosY = 625;
	const int			c_obstacleGap = 170;
	const int			c_health = 25;
}

namespace EffectProperties
{
	const int			c_portalTimer = 5;
	const int			c_portalRotationSpeed = 100;
	const int			c_maxParticleCount = 500;
	const int			c_backgroundParticleCount = 300;
	const int			c_minParticleSpeed = 10;
	const int			c_maxParticleSpeed = 20;
	const int			c_minVanishPointX = -75;
	const int			c_maxVanishPointX = 850;
	const int			c_minVanishPointY = -75;
	const int			c_maxVanishPointY = 1000;
}

namespace ShopProperties
{
	const int			c_playerSpeedLimit = 5;
	const int			c_livesLimit = 3;
	const int			c_damageLimit = 3;
	const int			c_teleportLimit = 1;
	const int			c_mineLimit = 5;
	const int			c_sizeLimit = 3;
	const int			c_doubleTapLimit = 3;
	const int			c_projectileSpeedLimit = 4;
}
#endif //!SETTINGS_H