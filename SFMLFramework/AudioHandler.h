#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <map>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/String.hpp>

enum class SoundEffect
{
	FireProjectile,
	SelectionBox,
	ShopFail,
	MenuButton,
	BackgroundMusic
};

class AudioHandler : public sf::Sound
{
private:
	sf::Sound		m_sound;
	sf::Sound		m_music;

	std::map<SoundEffect, sf::SoundBuffer*>		m_soundContainer;

public:
	AudioHandler();		// Constructor.
	~AudioHandler();	// Deconstructor.

	void initialise();	// Initialiser.
	void loadSound(SoundEffect sound, const sf::String& fileAddress); // Load sound function.
	void playSound(SoundEffect sound); // Play sound function.
};

#endif //!AUDIOHANDLER_H