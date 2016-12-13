#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include "Util.h"
#include "Car.h"
#include "Seek.h"

//Generates the grid
gridVector levelGrid =
{
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0 },
};

// Car Pointer for UI
Car* selectedCar;

//initializes font and text
sf::Font myFont;
sf::Text atext;

sf::String state1 = "State: ";
sf::String coord = "Dest: ";
sf::String current = "Current: ";

//creates a list of cars from our car class
std::vector<Car*> carsList;
std::vector<Bird*> birdList;
//Checks whether a point is within a square on the grid
bool isPointWithinRect(const sf::Vector2i &point, const sf::FloatRect &rect)
{
	return point.x >= rect.left && point.x <= rect.left + rect.width && point.y >= rect.top && point.y <= rect.top + rect.height;
}
//initializes the textures
bool initialize(sf::Texture &txtrGrass, sf::Texture &txtrRoad, sf::Texture &txtrJunct)
{
	if (!txtrGrass.loadFromFile("grassb.png"))
	{
		return false;
	}
	if (!txtrRoad.loadFromFile("road.png"))
	{
		return false;
	}
	if (!myFont.loadFromFile("OpenSans-Semibold.ttf")) 
	{
		return false;
	}
	if (!txtrJunct.loadFromFile("junction.png")) 
	{
		return false;
	}
	//Creates a list for the cars passed in
	for (int i = 0; i < 1; i++)
	{
		carsList.push_back(new Car());
		carsList[i]->initialize(levelGrid);
	}
	return true;
}

void update(sf::RenderWindow &window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		for (unsigned int i = 0; i < carsList.size(); ++i)
		{
			if (isPointWithinRect(mousePosition, carsList[i]->getBounds()))
			{
				selectedCar = carsList[i];
			}
		}
	}

	if (selectedCar != nullptr)
	{
		state1 = "State: \n" + selectedCar->state;
		coord = "Dest: \n" + selectedCar->coord;
		current = "Cur: \n" + selectedCar->current;
	}

	//checks is the right mouse button is clicked
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Seek *bird = new Seek();
		bird->Initialize();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//checks whether the mouse is within a grid square and generates a car into the car list on a right click 
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2i mouseGridPosition(mousePosition.x / TILE_SIZE, mousePosition.y / TILE_SIZE);
		Car *newCar = new Car();
		newCar->initialize(levelGrid);
		newCar->sprCar.setPosition(sf::Vector2f(mouseGridPosition.x * TILE_SIZE, mouseGridPosition.y * TILE_SIZE));
		carsList.push_back(newCar);
	}

	for (auto car : carsList)
	{
		car->update(window);
	}

	for (auto bird : Bird::Renderables)
	{
		bird->Think();
	}
}

void draw(sf::RenderWindow &window, sf::Texture &txtrGrass, sf::Texture &txtrRoad, sf::Texture &txtrJunct)
{
	for (int x = 0; x < GRID_SIZE_X; ++x)
	{
		for (int y = 0; y < GRID_SIZE_Y; ++y)
		{
			sf::Sprite sprCurrentSection;
			sprCurrentSection.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
			switch (levelGrid[x][y])
			{
				case 0:
					sprCurrentSection.setTexture(txtrGrass);
					break;
				case 1:
					sprCurrentSection.setTexture(txtrRoad);
					break;
				case 3:
					sprCurrentSection.setTexture(txtrJunct);
			}
			window.draw(sprCurrentSection);
		}
	}
	
	for (auto car : carsList)
	{
		car->draw(window);
	}

	for (auto bird : Bird::Renderables)
	{
		window.draw(bird->GetSprite(), bird->getTransform());
	}
}

void drawText(sf::Text &textDisplay, const char *text, sf::Vector2i pos)
{
	textDisplay.setFont(myFont);
	textDisplay.setString(text);
	textDisplay.setCharacterSize(40);
	textDisplay.setPosition(pos.x, pos.y);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIN_X, WIN_Y), WIN_TITLE, sf::Style::Close);

	sf::Texture txtrGrass;
	sf::Texture txtrRoad;
	sf::Texture txtrJunct;

	////Hides the console
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);

	if (!initialize(txtrGrass, txtrRoad, txtrJunct))
	{
		puts("Error: Failed to initialize");
		getchar();
		return 1;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		sf::Text stateString;
		drawText(stateString, state1.toAnsiString().c_str(), sf::Vector2i(650, 10));
		sf::Text coordString;
		drawText(coordString, coord.toAnsiString().c_str(), sf::Vector2i(650, 400));
		sf::Text curcoordString;

		drawText(curcoordString, current.toAnsiString().c_str(), sf::Vector2i(650, 200));

		update(window);
		window.clear(sf::Color(50, 50, 50));
		draw(window, txtrGrass, txtrRoad, txtrJunct);
		window.draw(coordString);
		window.draw(stateString);
		window.draw(curcoordString);
		window.display();
		Sleep(100);
	}
	return 0;
}