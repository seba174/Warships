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
	playersInformations(const std::wstring& Name, bool isWinner, float accuracy, unsigned int totalShots, unsigned int totalHits, unsigned int maximumShots, unsigned int maximumMisses)
		:playerName(Name), isWinner(isWinner), accuracy(accuracy), totalShots(totalShots), totalHits(totalHits), maximumMisses(maximumMisses), maximumShots(maximumShots) {}

	std::wstring getPlayerName() const { return playerName; }

	// returns percentage accuracy of the Players shots
	float returnAccuracy() const { return accuracy; } 

	// returns true when the Player has won the game
	// returns false when the Player has lost the game
	bool isAWinner() const { return isWinner; }
	
	// return total mapSize of shots made by the Player
	unsigned int returnTotalShots() const { return totalShots; }
	
	// return mapSize of shots on target made by the Player
	unsigned int returnTotalHits() const { return totalHits; }
	
	// returns maximum on target hits in a row 
	unsigned int returnMaximumShots() const { return maximumShots; }
	
	// returns maximum misses in a row 
	unsigned int returnMaximumMisses() const { return maximumMisses; }
};

