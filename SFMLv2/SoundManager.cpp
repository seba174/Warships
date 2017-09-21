#include "SoundManager.h"


SoundManager::SoundManager()
{
	if (!soundBuffers[SoundsNames::Explosion].loadFromFile("Sounds/Explosion.wav"))
		throw std::runtime_error("Sound Explosion.wav could not be loaded");
	if(!soundBuffers[SoundsNames::Splash].loadFromFile("Sounds/Splash.wav"))
		throw std::runtime_error("Sound Splash.wav could not be loaded");
	soundsVolume = 100;
}

void SoundManager::playSound(SoundsNames soundName)
{
	sounds.push_front(sf::Sound(soundBuffers[soundName]));
	
	auto it = sounds.begin();
	it->setVolume(soundsVolume);
	it->play();
}

void SoundManager::clearManager()
{
	sounds.clear();
}

