#pragma once
#include <SFML/Graphics.hpp>

class Board
{
protected:
	sf::Vector2i BoardDimensions;
	sf::Vector2f SquareSize;
	sf::Vector2f SetPoints; 
	int counter;
	sf::Time time;
public:
	Board(const sf::Vector2i dim, const sf::Vector2f SquareSize, const sf::Vector2f setpoints) : BoardDimensions(dim), SquareSize(SquareSize), SetPoints(setpoints) { counter = 0; };
	
	virtual bool getplaceShip() const = 0;
	virtual void setPosition(const sf::Vector2f mousepos) = 0;
	virtual bool placePlayerShip(int **ships, int tabs_size, std::vector<Board*>&, sf::Texture* texture) = 0;
	virtual void setplaceShip(bool set) = 0;
	virtual void rotate_ship() = 0;
	virtual sf::RectangleShape& return_ship() = 0;
	virtual void updateTexture(const sf::Time&) = 0;
	virtual ~Board() {};
};

