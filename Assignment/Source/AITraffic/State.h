#pragma once
#include "Util.h"

class Car;

class State
{
public:
	State(int x, int y) {}
	State() {}
	~State() {}

	virtual void entry(gridVector &grid) = 0;
	virtual void update(Car &car) = 0;
	virtual bool shouldTransition() = 0;
	virtual State *newState() = 0;

protected:
	State* nextState;
	bool transition;

	int _x, _y;

};