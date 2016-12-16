#pragma once
#include <SFML/Graphics.hpp>
#include "Util.h"
#include "Driving.h"
#include "Waiting.h"
#include <vector>
#include <random>

class State;

class Car
{

private:

	sf::Vector2i destination;
	void drawText(sf::Text &textDisplay, const char *text, sf::Vector2i pos);

public:

	sf::Vector2i currentPos;

	sf::Texture txtrCar;
	sf::Sprite sprCar;
	bool initialize(gridVector &grid);
	void setPosition(const sf::Vector2f &position);
	void draw(sf::RenderWindow &window);
	void update(sf::RenderWindow &window);
	void reset();
	gridVector levelGrid;
	sf::FloatRect getBounds();

	std::vector<sf::Vector2i> destinationList;
	std::vector<sf::Vector2i> startList;

	sf::Vector2i getDestination() const { return destination; }
	sf::Vector2f getPosition() const;
	sf::Vector2i getTilePosition() const;

	sf::Color getRandomColour();
	int getRandomInt(const int &min, const int &max);

	State* currentState;

	sf::String state = "Driving";
	sf::String coord = "?,?";
	sf::String current = "?,?";
	sf::Vector2i target;
	sf::Font myFont;
};

