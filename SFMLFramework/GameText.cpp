#include "GameText.h"

GameText::GameText()
{
	// Set the default character size.
	setCharacterSize(50);
}

GameText::~GameText()
{

}

void GameText::initialise(Fonts font)
{
	// Initialiser called to set the correct font based on font type.
	switch (font) {
	case Arial:
		m_font.loadFromFile("Assets/Fonts/f_arialFont.ttf");
		break;
	case SciFi:
		m_font.loadFromFile("Assets/Fonts/f_gameFont.ttf");
		break;
	case Jersey:
		m_font.loadFromFile("Assets/Fonts/f_jerseyFont.ttf");
		break;
	}
	// Set the font.
	setFont(m_font);
}

void GameText::render(sf::RenderTarget* window)
{
	// Render the font to the window.
	window->draw(*this);
}
