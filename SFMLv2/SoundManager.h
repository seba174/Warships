#pragma once
#include <SFML/Audio.hpp>
#include <forward_list>
#include <map>
#include "enumSoundsNames.h"


class SoundManager
{
	std::forward_list<sf::Sound> sounds;
	std::map<SoundsNames, sf::SoundBuffer> soundBuffers;

	float soundsVolume;

public:
	SoundManager();

	void playSound(SoundsNames soundName);

	void clearManager();

	void setSoundsVolume(float newSoundsVolume) { soundsVolume = newSoundsVolume; }
};

