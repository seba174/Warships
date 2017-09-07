#include "GameTime.h"



GameTime::GameTime()
{
}

void GameTime::runGameTimer(const sf::Time & dt)
{
	timer += dt;

	// Timer's maximum time is 1 hour
	if (timer.asSeconds() >= 3600)
		timer = timer.Zero;
}

std::wstring GameTime::returnTimeAsString() const
{
	int minutes = floor(timer.asSeconds() / 60);
	int seconds = floor(timer.asSeconds() - minutes * 60);
	std::wstring minutesString, secondsString;

	if (minutes == 0)
		minutesString = L"00";
	else if (minutes < 10)
		minutesString = L'0' + std::to_wstring(minutes);
	else
		minutesString = std::to_wstring(minutes);

	if (seconds == 0)
		secondsString = L"00";
	else if (seconds < 10)
		secondsString = L'0' + std::to_wstring(seconds);
	else
		secondsString = std::to_wstring(seconds);

	return minutesString + L':' + secondsString;
}

