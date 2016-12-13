#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <random>
#include "Util.h"

class Bird : public sf::Transformable
{

public:

	static std::vector<Bird*> Renderables;

	Bird();
	virtual void Think();
	virtual void Initialize();
	sf::Sprite GetSprite() { return sprite; }

	int getRandomInt(const int &min, const int &max);

	bool toDestroy;

protected:
	std::string filename;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f velocity;
};