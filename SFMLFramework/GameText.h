#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

enum Fonts { Arial, SciFi, Jersey };

class GameText : public sf::Text
{
private:
	sf::Font	m_font;	// Font to use.

public:
	GameText();			// Constructor.
	~GameText();		// Deconstructor.

	void initialise(Fonts font);			// Initialiser.
	void render(sf::RenderTarget* window);	// Render text to screen.
};

#endif //!GAMETEXT_H