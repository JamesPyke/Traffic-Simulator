#pragma once
#include "Bird.h"

class Seek :
	public Bird
{
private:
	sf::Vector2f Normalize(sf::Vector2f);
	sf::Vector2f target;

public:
	void Think();
	int getRandomInt(const int &min, const int &max);
	void Initialize() override;
};

