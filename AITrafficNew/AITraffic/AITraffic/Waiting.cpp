#include "Waiting.h"
#include "Car.h"

class Driving;
//Construcor class that passes on the x and y values
Waiting::Waiting(int x, int y)
{
	_x = x;
	_y = y;
}
//upon entry of the state restarts the time elapsed to obtain accurate clock
void Waiting::entry(gridVector & grid)
{
	clock.restart();
}
//waits 2 seconds in this state before returning to the driving state 
void Waiting::update(Car & car)
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 2)
	{
		transition = true;
		nextState = new Driving(_x, _y, true, car.currentPos);
	}
}

bool Waiting::shouldTransition()
{
	return transition;
}

State * Waiting::newState()
{
	return nextState;
}

int Waiting::getRandomRoute()
{
	std::uniform_int_distribution<int> intDistribution(1, 4);
	std::random_device randomDevice;
	return int(intDistribution(randomDevice));
}


