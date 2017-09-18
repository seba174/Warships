#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
protected:
	sf::Vector2i boardDimensions;
	sf::Vector2f squareSize;
	sf::Vector2f setPoints; 
	int counter;
	sf::Time time;
	bool shouldDraw;

public:
	Board(const sf::Vector2i& dim, const sf::Vector2f& SquareSize, const sf::Vector2f& setpoints)
		: boardDimensions(dim), squareSize(SquareSize), setPoints(setpoints) 
	{
		counter = 0; shouldDraw = true;
	}
	
	virtual bool getPlaceShip() const = 0;

	virtual void setPosition(const sf::Vector2f& mousepos) = 0;

	virtual bool placePlayerShip(std::vector<std::vector<int>>&, int tabs_size, std::vector<Board*>&) = 0;

	virtual void setPlaceShip(bool set) = 0;

	virtual void rotateShip() = 0;

	virtual sf::RectangleShape& returnShip() = 0;

	virtual void updateTexture(const sf::Time&) = 0;

	virtual void setDestroyedTexture() = 0;

	virtual bool shouldBeDrawed() const { return shouldDraw; }

	virtual void setShouldDraw(bool newValue) { shouldDraw = newValue; }

	virtual ~Board() {};
};

