#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include "TextureHandler.h"

class GameSprite : public sf::Sprite
{
private:
	TextureHandler*		m_pTextureHandler;	// Reference to texture handler.	

	sf::Clock			m_clock;			// Clock used for animation time handling.
	sf::IntRect			m_rectSourceSprite; // Rectangle source sprite reference.

	bool				m_loopAnimation;	// Bool to determine if the animation is to be looped.

public:
	GameSprite();	// Constructor.
	~GameSprite();	// Deconstructor.

	sf::IntRect getRectSourceSprite();							// Return rectangle source sprite.
	void setRectSourceSprite(int width, int height);			// Set the size of the rectangle source sprite.

	int getRectSourcePos();										// Return rectangle position.
	void setRectSourcePos(int position);						// Set rectangle position.

	TextureHandler* getTextureHandler();						// Return texture handler.
	void setTextureHandler(TextureHandler* pTextureHandler);	// Set texture handler.

	virtual void drawSprite(int sprite);																// Function to draw a single sprite instead of rendering an animation.
	virtual void animateSprite(float animationSpeed, int imageWidth, int totalImageWidth, bool loop);	// Function for animated sprites.
};

#endif // GAMESPRITE_H
