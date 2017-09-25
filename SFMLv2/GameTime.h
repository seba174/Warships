#pragma once

class GameTime
{
	sf::Time timer;

public:
	GameTime() {};

	void runGameTimer(const sf::Time& dt);

	std::wstring returnTimeAsString() const;
};

