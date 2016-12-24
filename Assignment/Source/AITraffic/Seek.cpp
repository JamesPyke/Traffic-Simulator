#include "Seek.h"

//Runs the seek function, gathering a direction and a target location then forming 
//a direction vector based on the starting location

void Seek::Think()
{
	sf::Vector2f direction = Normalize(target - getPosition());
	sprite.setRotation(atan2(direction.y, direction.x) * 180 / M_PI + 90);
	sf::Vector2f desired_velocity = (Normalize(target - getPosition()) * 5.f);
	sf::Vector2f steering = desired_velocity - velocity;
	velocity += steering;
	sf::Vector2f pos = getPosition();
	setPosition(pos + velocity);

	if (getPosition().y < -25 && !toDestroy)
	{
		toDestroy = true;
	}
}

sf::Vector2f Seek::Normalize(sf::Vector2f norm) 
{
	float mag = sqrt((norm.x * norm.x) + (norm.y * norm.y));
	if (mag != 0)
		return sf::Vector2f(norm.x / mag, norm.y / mag);
	else
		return norm;
}

void Seek::Initialize()
{
	Bird::Initialize();
	target = sf::Vector2f(getRandomInt(0, 600), -50);
}

int Seek::getRandomInt(const int & min, const int & max)
{
	std::uniform_int_distribution<int> intDistribution(min, max);
	std::random_device randomDevice;
	return int(intDistribution(randomDevice));
}
