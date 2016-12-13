#pragma once
#include "State.h"
#include "Util.h"
#include <random>

class Car;

class Waiting :
	public State

{

private:

	sf::Clock clock;
	sf::Time elapsed;

public:

	Waiting(int x, int y);

	void entry(gridVector &grid);
	void update(Car &car);
	bool shouldTransition();
	State *newState();
	int getRandomRoute();

};

