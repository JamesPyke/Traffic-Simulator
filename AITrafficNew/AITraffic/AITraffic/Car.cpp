#include "Car.h"

void Car::drawText(sf::Text & textDisplay, const char * text, sf::Vector2i pos)
{
	textDisplay.setFont(myFont);
	textDisplay.setString(text);
	textDisplay.setCharacterSize(40);
	textDisplay.setPosition(pos.x, pos.y);
}

//Initializes the car 
bool Car::initialize(gridVector &grid)
{
	if (!myFont.loadFromFile("OpenSans-Semibold.ttf"))
	{
		return false;
	}
	//Creates a list of Destinations for the cars to get to
	if (destinationList.empty())
	{
		destinationList.push_back(sf::Vector2i(17, 0));
		destinationList.push_back(sf::Vector2i(11, 0));
		destinationList.push_back(sf::Vector2i(4, 0));
		destinationList.push_back(sf::Vector2i(19, 4));
		destinationList.push_back(sf::Vector2i(19, 10));
		destinationList.push_back(sf::Vector2i(19, 16));
	}
	//Creates a list of starting locations
	if (startList.empty()) 
	{
		startList.push_back(sf::Vector2i(0, 4));
		startList.push_back(sf::Vector2i(0, 11));
		startList.push_back(sf::Vector2i(0, 17));
		startList.push_back(sf::Vector2i(4, 19));
		startList.push_back(sf::Vector2i(11, 19));
		startList.push_back(sf::Vector2i(17, 19));
	}

	levelGrid = grid;
	//Makes sure the car sprite is loaded 
	if (!txtrCar.loadFromFile("car.png"))
	{
		return false;
	}
	//Creates sprite based on the texture
	sprCar.setTexture(txtrCar);
	//Sets the origin of the car sprite to it's center 
	sprCar.setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
	
	reset();

	return true;
}

//Resets the car 
void Car::reset()
{
	//Resets the car to a random starting point after reaching it's destination
	currentPos =startList[getRandomInt(0, startList.size() - 1)];
	//At reset the car is initialized into the driving state
	currentState = new Driving(currentPos.x, currentPos.y, false, currentPos);
	currentState->entry(levelGrid);
	//Picks a radnom location for the car to get to 
	destination = destinationList[getRandomInt(0, destinationList.size() - 1)];
	//Sets a random colour on  the car
	sprCar.setColor(getRandomColour());
}
//Gets the car sprites position on the grid
sf::Vector2f Car::getPosition() const
{
	return sprCar.getPosition();
}
//Returns the coordinates of the grid
sf::Vector2i Car::getTilePosition() const
{
	return sf::Vector2i(getPosition().x / TILE_SIZE, getPosition().y / TILE_SIZE);
}
//Random generator for the cars colour
sf::Color Car::getRandomColour()
{
	std::uniform_int_distribution<int> intDistribution(0, 255);
	std::random_device randomDevice;
	return sf::Color(intDistribution(randomDevice), intDistribution(randomDevice), intDistribution(randomDevice));
}
//Random generator for an INT (used to generate a number for destination and start location)
int Car::getRandomInt(const int & min, const int & max)
{
	std::uniform_int_distribution<int> intDistribution(min, max);
	std::random_device randomDevice;
	return int(intDistribution(randomDevice));
}
//Sets the cars position
void Car::setPosition(const sf::Vector2f & position)
{
	sprCar.setPosition(position);
}
//Draws that car based on the window
void Car::draw(sf::RenderWindow & window)
{
	target = sf::Vector2i(sprCar.getPosition().x, sprCar.getPosition().y);
	window.draw(sprCar);
	sf::Text stateString;
	drawText(stateString, state.toAnsiString().c_str(), sf::Vector2i(700, 100));
	window.draw(stateString);
	sf::Text coordString;
	drawText(coordString, coord.toAnsiString().c_str(), sf::Vector2i(700, 500));
	window.draw(coordString);
	sf::Text currentString;
	drawText(currentString, current.toAnsiString().c_str(), sf::Vector2i(700, 300));
	window.draw(currentString);
}
//Updates the car's state using a transition condition
void Car::update(sf::RenderWindow &window)
{
	currentState->update(*this);

	if (currentState->shouldTransition())
	{
		currentState = currentState->newState();
		currentState->entry(levelGrid);
	}
}
