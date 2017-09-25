#include "stdafx.h"
#include "MusicHandler.h"


void MusicHandler::setQuieterVolume()
{
	if (lastMusicName == MusicName::MenuTheme)
		mMusic.setVolume(menuVolume / 2);
	else if (lastMusicName == MusicName::GameTheme)
		mMusic.setVolume(inGameVolume / 2);
	else
		mMusic.setVolume(mVolume / 2);
}

MusicHandler::MusicHandler()
	: mMusic()
	, mFilenames()
	, mVolume(100.0f)
{
	mFilenames[MusicName::MenuTheme] = "Music/MenuTheme.ogg";
	mFilenames[MusicName::GameTheme] = "Music/GameTheme.ogg";
}

void MusicHandler::play(MusicName theme)
{
	std::string fileName = mFilenames[theme];
	if (!mMusic.openFromFile(fileName))
		throw std::runtime_error("Music" + fileName + "could not be loaded");

	lastMusicName = theme;
	if (theme == MusicName::MenuTheme)
		mMusic.setVolume(menuVolume);
	else if (theme == MusicName::GameTheme)
		mMusic.setVolume(inGameVolume);
	else
		mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}

void MusicHandler::setPausedAction(bool paused)
{
	//if (paused && mMusic.getStatus() == mMusic.Playing)
	//	mMusic.pause();
	//else if (!paused && mMusic.getStatus() == mMusic.Paused)
	//	mMusic.play();

	if (paused && mMusic.getStatus() == mMusic.Playing)
		setQuieterVolume();
	else if (!paused)
		updateMusicVolume();
}

void MusicHandler::updateMusicVolume()
{
	if (lastMusicName == MusicName::MenuTheme)
		mMusic.setVolume(menuVolume);
	else if (lastMusicName == MusicName::GameTheme)
		mMusic.setVolume(inGameVolume);
	else
		mMusic.setVolume(mVolume);
}



