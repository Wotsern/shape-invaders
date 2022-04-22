#include "AudioHandler.h"

AudioHandler::AudioHandler()
{
	initialise();
}

AudioHandler::~AudioHandler()
{
	for (auto audio : m_soundContainer)
	{
		delete audio.second;
		audio.second = nullptr;
	}
}

void AudioHandler::initialise() // Load the sound from file.
{

	loadSound(SoundEffect::BackgroundMusic, "Assets/Audio/a_music.wav");
	loadSound(SoundEffect::FireProjectile, "Assets/Audio/a_shoot.wav");
	loadSound(SoundEffect::SelectionBox, "Assets/Audio/a_moveBox.wav");
	loadSound(SoundEffect::ShopFail, "Assets/Audio/a_shopFail.wav");
	loadSound(SoundEffect::MenuButton, "Assets/Audio/a_menuButton.wav");	
}

// Load the sound function.
void AudioHandler::loadSound(SoundEffect sound, const sf::String& fileAddress)
{
	m_soundContainer[sound] = new sf::SoundBuffer();
	bool loaded = m_soundContainer[sound]->loadFromFile(fileAddress);
}

// Function called to play the sound.
void AudioHandler::playSound(SoundEffect sound)
{
	auto audioMatch = m_soundContainer.find(sound);

	switch (sound) // Play the desired sound.
	{
	case SoundEffect::FireProjectile:
		m_sound.setBuffer(*audioMatch->second);
		m_sound.play();
		break;
	case SoundEffect::SelectionBox:
		m_sound.setBuffer(*audioMatch->second);
		m_sound.play();
		break;
	case SoundEffect::ShopFail:
		m_sound.setBuffer(*audioMatch->second);
		m_sound.play();
		break;
	case SoundEffect::MenuButton:
		m_sound.setBuffer(*audioMatch->second);
		m_sound.play();
		break;
	case SoundEffect::BackgroundMusic:
		m_music.setBuffer(*audioMatch->second);
		m_music.setVolume(15);
		m_music.setLoop(true);
		m_music.play();
		break;
	}
}
