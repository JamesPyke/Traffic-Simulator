#include "Bird.h"

std::vector<Bird*> Bird::Renderables;

void Bird::Think()
{
	// build a new position vector by adding a scaled version of the velocity vector
	sf::Vector2f pos = (velocity * 0.005f) + getPosition();
	// update our position
	setPosition(pos);
}

void Bird::Initialize()
{
	// set a default position - could be randomised.
	setPosition(getRandomInt(0, 600), 640);

	// load the texture into memory
	texture.loadFromFile("bird2.png");
	texture.setSmooth(true);
	// and provide the sprite with a pointer to the texture object
	// if the texture object is destroyed (goes out of scope etc) then the sprite will display weirdly
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
	// select a random angle
	float angle = 90;
	//UtilRandom::instance()->GetRange(0, 361);
	// set our rotation value
	setRotation(angle);
	// and assign a velocity, we need to convert angle to radians so it plays nicely with cos and sin.
	velocity = sf::Vector2f(cos(angle), sin(angle));
	// add the entity to the list of renderables.
	Renderables.push_back(this);

	toDestroy = false;
}

int Bird::getRandomInt(const int & min, const int & max)
{
	std::uniform_int_distribution<int> intDistribution(min, max);
	std::random_device randomDevice;
	return int(intDistribution(randomDevice));
}
