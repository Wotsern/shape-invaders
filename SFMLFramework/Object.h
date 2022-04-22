#ifndef OBJECT_H
#define OBJECT_H

#include "GameSprite.h"

#include <SFML/Graphics/RenderTarget.hpp>

class Object : public GameSprite
{
private:

public:
	Object();	// Constructor.
	~Object();	// Deconstructor.

	virtual void update(float deltaTime);			// Update function.
	virtual void render(sf::RenderTarget* window);	// Render function.
};

#endif // !OBJECT_H