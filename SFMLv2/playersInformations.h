#pragma once
#include "SFML/Graphics.hpp"


class playersInformations
{
	std::wstring playerName;
	bool isWinner;
	float accuracy;
	unsigned int totalShots;
	unsigned int totalHits;
	unsigned int maximumShots;
	unsigned int maximumMisses;

public:
	playersInformations(const std::wstring& newName, bool isWinner, float accuracy, unsigned int totalShots, unsigned int totalHits, unsigned int maximumShots, unsigned int maximumMisses)
		:playerName(newName), isWinner(isWinner), accuracy(accuracy), totalShots(totalShots), totalHits(totalHits), maximumMisses(maximumMisses), maximumShots(maximumShots) {}

	std::wstring getPlayerName() const { return playerName; }
	float returnAccuracy() const { return accuracy; } 
	bool isAWinner() const { return isWinner; }
	unsigned int returnTotalShots() const { return totalShots; }
	unsigned int returnTotalHits() const { return totalHits; }
	unsigned int returnMaximumShots() const { return maximumShots; }
	unsigned int returnMaximumMisses() const { return maximumMisses; }

	//void setIsWinner(bool isWinner) { this->isWinner = isWinner; }
	//void setPlayerName(const std::wstring& newName) { playerName = newName; }
};

