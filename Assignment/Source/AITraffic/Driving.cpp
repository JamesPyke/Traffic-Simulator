#include "Driving.h"
#include "Car.h"

class Waiting;

//Constructor of the class initializing x and y values and passing in the positionof the car and junction function
Driving::Driving(int x, int y, bool atJunction, sf::Vector2i &currentPos)
{
	_x = x;
	_y = y;
	this->currentPos = &currentPos;
	this->atJunction = atJunction;
}
//passes in the current position and level grid upoon entry into the state
void Driving::entry(gridVector &grid)
{
	currentPos->x = _x;
	currentPos->y = _y;
	levelGrid = grid;
	transition = false;
}
//Checks the bound of the grid
bool Driving::isCellWithinBounds(const sf::Vector2i &cell)
{
	return cell.x >= 0 && cell.x < GRID_SIZE_X && cell.y >= 0 && cell.y < GRID_SIZE_Y;
}
//Update state of the car
void Driving::update(Car &car)
{
	car.state = "Driving";

	sf::Vector2i nextPos;
	//Junction condition, checks if you are at one
	if (atJunction)
	{
		nextPos = getNextTile(car);
		atJunction = false;
	}
	else
	{
		 nextPos = getNextTile();
	}
	if (nextPos != outOfBounds)
	{
		//checks the grid to see if the next tile is a junction and, if true, puts the car into it's waiting state
		if (levelGrid[nextPos.x][nextPos.y] == 3)
		{
			transition = true;
			nextState = new Waiting(nextPos.x, nextPos.y);
			return;
		}
		//checks the direction the car is travelling and rotates the sprite accordingly
		if (nextPos.y < currentPos->y)
		{
			car.sprCar.setRotation(-90);
		}
		else if (nextPos.x > currentPos->x)
		{
			car.sprCar.setRotation(0);
		}
		else if (nextPos.y > currentPos->y)
		{
			car.sprCar.setRotation(90);
		}
		else if (nextPos.x < currentPos->x)
		{
			car.sprCar.setRotation(180);
		}
		//sets the current position the the previous to stop the car going back on itself
		prevPos = *currentPos;
		*currentPos = nextPos;

		car.current = std::to_string(car.currentPos.x) + ", " + std::to_string(car.currentPos.y);
	}
	else
	{
		car.reset();
	}
	//Scales the cars position according to the size of the grid
	car.setPosition(sf::Vector2f(currentPos->x * TILE_SIZE + TILE_SIZE / 2, currentPos->y * TILE_SIZE + TILE_SIZE / 2));
}
//checks whether the should transition
bool Driving::shouldTransition()
{
	return transition;
}

State * Driving::newState()
{
	return nextState;
}
//based on parameters, decides the direction the car should travel
sf::Vector2i Driving::getNextTile()
{
	sf::Vector2i northCell(currentPos->x, currentPos->y - 1);
	if ((isCellWithinBounds(northCell)) && (levelGrid[northCell.x][northCell.y] > 0) && (northCell != prevPos))
	{
			return northCell;
	}
	sf::Vector2i eastCell(currentPos->x + 1, currentPos->y);
	if ((isCellWithinBounds(eastCell)) && (levelGrid[eastCell.x][eastCell.y] > 0) && (eastCell != prevPos))
	{
			return eastCell;
	}
	sf::Vector2i southCell(currentPos->x, currentPos->y + 1);
	if ((isCellWithinBounds(southCell)) && (levelGrid[southCell.x][southCell.y] > 0) && (southCell != prevPos))
	{
			return southCell;
	}
	sf::Vector2i westCell(currentPos->x - 1, currentPos->y);
	if ((isCellWithinBounds(westCell)) && (levelGrid[westCell.x][westCell.y] > 0) && (westCell != prevPos))
	{
			return westCell;
	}
	return outOfBounds;
}


//gets the magnitude of two vectors
float Driving::getDistance(sf::Vector2i destination, sf::Vector2i otherCell)
{
	float A = otherCell.x - destination.x;
	float B = otherCell.y - destination.y;
	return sqrt(A * A + B * B);
}

//Goes through each cell(north,south,east and west) and checks which direction is the shortest
sf::Vector2i Driving::getNextTile(Car & car)
{
	sf::Vector2i northCell(currentPos->x, currentPos->y - 1);
	sf::Vector2i eastCell(currentPos->x + 1, currentPos->y);
	sf::Vector2i southCell(currentPos->x, currentPos->y + 1);
	sf::Vector2i westCell(currentPos->x - 1, currentPos->y);

	sf::Vector2i shortest = sf::Vector2i(0,0);
	float minDist = FLT_MAX;

	// check north
	if (getDistance(car.getDestination(), northCell) < minDist)
	{
		shortest = northCell;
		minDist = getDistance(car.getDestination(), northCell);
	}

	// east
	if (getDistance(car.getDestination(), eastCell) < minDist)
	{
		shortest = eastCell;
		minDist = getDistance(car.getDestination(), eastCell);
	}

	// south
	if (getDistance(car.getDestination(), southCell) < minDist)
	{
		shortest = southCell;
		minDist = getDistance(car.getDestination(), southCell);
	}
	// west
	if (getDistance(car.getDestination(), westCell) < minDist)
	{
		shortest = westCell;
		minDist = getDistance(car.getDestination(), westCell);
	}
	return shortest;
}

