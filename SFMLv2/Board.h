#pragma once
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
	
	virtual bool getplaceShip() const = 0;

	virtual void setPosition(const sf::Vector2f& mousepos) = 0;

	virtual bool placePlayerShip(int **ships, int tabs_size, std::vector<Board*>&) = 0;

	virtual void setplaceShip(bool set) = 0;

	virtual void rotate_ship() = 0;

	virtual sf::RectangleShape& return_ship() = 0;

	virtual void updateTexture(const sf::Time&) = 0;

	virtual void setDestroyedTexture() = 0;

	virtual bool shouldBeDrawed() const { return shouldDraw; }

	virtual void setShouldDraw(bool newValue) { shouldDraw = newValue; }

	virtual ~Board() {};
};

