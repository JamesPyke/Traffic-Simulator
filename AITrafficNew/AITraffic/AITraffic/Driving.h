#pragma once
#include "State.h"
#include "Util.h"

class Car;

class Driving : public State
{

private:

	sf::Vector2i prevPos;
	sf::Vector2i* currentPos;

	bool isCellWithinBounds(const sf::Vector2i &cell);
	bool atJunction;

	float getDistance(sf::Vector2i destination, sf::Vector2i otherCell);

public:
	
	Driving(int x, int y, bool atJunction, sf::Vector2i &currentPos);
	void entry(gridVector &grid);
	void update(Car &car);

	bool shouldTransition();
	State *newState();
	sf::Vector2i getNextTile();
	sf::Vector2i getNextTile(Car &car);

	gridVector levelGrid;

};

