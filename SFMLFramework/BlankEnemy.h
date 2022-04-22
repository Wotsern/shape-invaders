#ifndef BLANKENEMY_H
#define BLANKENEMY_H

#include "Enemy.h"

class BlankEnemy : public Enemy
{
private:

public:
	BlankEnemy();		//Constructor.
	~BlankEnemy();		//Deconstructor.

	void initialise();	//Initialise function.
};

#endif //!BLANKENEMY_H