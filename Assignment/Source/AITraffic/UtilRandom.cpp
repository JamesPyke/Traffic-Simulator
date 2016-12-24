#include "UtilRandom.h"

// declare and initialize the private static instance variable
UtilRandom *UtilRandom::_instance = 0;

float UtilRandom::GetRange(float min, float max)
{
	// generate a uniform distribution of floats between min and max
	std::uniform_real_distribution<float> dist(min, max);
	// return a value from that distribution.
	return dist(mt);
}
