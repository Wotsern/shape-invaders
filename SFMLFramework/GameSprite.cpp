#include "GameSprite.h"
#include "Settings.h"
#include "Helpers.h"

GameSprite::GameSprite()
{
	// Set the reference null as it will be set when called for in the setter function.
	m_pTextureHandler	= nullptr;

	m_loopAnimation		= true;
}

GameSprite::~GameSprite()
{

}

// Set the size of the rectangle source sprite.
void GameSprite::setRectSourceSprite(int width, int height)
{
	m_rectSourceSprite.width = width;
	m_rectSourceSprite.height = height;
}

// Return the size of the rectangle source sprite.
sf::IntRect GameSprite::getRectSourceSprite()
{
	return m_rectSourceSprite;
}

// Set the rectangle source position.
void GameSprite::setRectSourcePos(int position)
{
	m_rectSourceSprite.left = position;
}

// Get the rectangle source position.
int GameSprite::getRectSourcePos()
{
	return m_rectSourceSprite.left;
}

// Set the texture handler.
void GameSprite::setTextureHandler(TextureHandler* pTextureHandler)
{
	m_pTextureHandler = pTextureHandler;
}

// Return the texture handler.
TextureHandler* GameSprite::getTextureHandler()
{
	return m_pTextureHandler;
}

// Draw a sprite to the window.
void GameSprite::drawSprite(int sprite)
{
	m_rectSourceSprite.left = sprite;
	setTextureRect(m_rectSourceSprite);
}

// Animate a sprite to the window.
void GameSprite::animateSprite(float animationSpeed, int imageWidth, int totalImageWidth, bool loop)
{
	if (m_loopAnimation == true)
	{
		if (m_clock.getElapsedTime().asSeconds() >= animationSpeed)
		{
			if (m_rectSourceSprite.left == totalImageWidth)
			{
				m_loopAnimation = loop;
				m_rectSourceSprite.left = 0;
			}
			else
			{
				m_rectSourceSprite.left += imageWidth;
			}
			setTextureRect(m_rectSourceSprite);
			m_clock.restart();
		}
	}
}