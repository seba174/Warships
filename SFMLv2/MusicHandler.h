#pragma once
#include <SFML/Audio.hpp>
#include <map>

enum MusicName {MenuTheme, GameTheme};

class MusicHandler
{
	sf::Music mMusic;
	std::map<MusicName, std::string> mFilenames;
	float inGameVolume, menuVolume;
	float mVolume;
	MusicName lastMusicName;

	void setQuieterVolume();

public:
	MusicHandler();

	void play(MusicName theme);

	void stop() { mMusic.stop(); }

	void setPausedAction(bool paused);

	void setDefaultVolume(float volume) { mVolume = volume; }

	void setInGameVolume(float volume) { inGameVolume = volume; }

	void setMenuVolume(float volume) { menuVolume = volume; }

	void updateMusicVolume();
};

