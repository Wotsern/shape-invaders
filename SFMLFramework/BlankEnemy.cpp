#include "BlankEnemy.h"

BlankEnemy::BlankEnemy()
{
	initialise();
}

BlankEnemy::~BlankEnemy()
{
}

void BlankEnemy::initialise()
{
	// Set the enemy type to blank.
	setEnemyType(EnemyType::Blank);
}
