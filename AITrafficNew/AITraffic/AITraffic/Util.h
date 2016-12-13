#pragma once

#include <vector>
#include "SFML\Graphics.hpp"

const int TILE_SIZE = 32;
const int GRID_SIZE_X = 20;
const int GRID_SIZE_Y = 20;
const int WIN_X = TILE_SIZE * GRID_SIZE_X + 200;
const int WIN_Y = TILE_SIZE * GRID_SIZE_Y;
const char WIN_TITLE[] = "AI Traffic";

const sf::Vector2i outOfBounds(-1, -1);

typedef std::vector<std::vector<int>> gridVector;